#include "BluetoothThread.h"
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
//https://people.csail.mit.edu/albert/bluez-intro/c33.html
using namespace std;

extern atomic<bool> keepRunning;

void bluetoothSenderLoop(const string& destAddr, VarHandler* handler) {
    struct sockaddr_rc addr = { 0 };
    int s;

    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t)1;
    str2ba(destAddr.c_str(), &addr.rc_bdaddr);

    // Try to connect, retrying if it fails
    while (keepRunning) {
        s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        if (s < 0) {
            perror("Socket creation failed");
            handler->setSocketDisconnected(true);
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }

        if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("Connection failed");
            close(s);
            handler->setSocketDisconnected(true);
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }

        // Connected successfully
        handler->setSocketDisconnected(false);
        cout << "Connected to " << destAddr << " - starting send/receive loop." << endl;
        break;
    }

    char buffer[1024]; // Temporary buffer for receiving data
    string receivedMessageBuffer; // Accumulate received bytes here
    string lastSentMessage; // Store the last sent message
    bool resendLastMessage = false; // Flag to indicate if the last message should be resent

    // Add a retry limit for resending messages
    int retryCount = 0;
    const int maxRetries = 5;

    while (keepRunning) {
        // Check if the socket is still valid
        if (s < 0) {
            cerr << "Socket disconnected. Attempting to reconnect..." << endl;
            handler->setSocketDisconnected(true); // Notify VarHandler about the disconnection

            // Attempt to reconnect
            s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
            if (s < 0) {
                perror("Socket creation failed during reconnection");
                this_thread::sleep_for(chrono::seconds(1)); // Wait before retrying
                continue;
            }

            if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("Reconnection failed");
                close(s);
                s = -1; // Mark socket as invalid
                this_thread::sleep_for(chrono::seconds(1)); // Wait before retrying
                continue;
            }

            cout << "Reconnected to " << destAddr << endl;
            handler->setSocketDisconnected(false); // Clear the disconnection flag
        }

        string dataToSend;

        // Determine what to send
        if (resendLastMessage) {
            dataToSend = lastSentMessage; // Resend the last message
        } else {
            string newMessage = handler->getMessage();
            if (!newMessage.empty() && (lastSentMessage.empty() || lastSentMessage != newMessage)) {
                lastSentMessage = newMessage; // Update the last sent message
            }
            dataToSend = lastSentMessage; // Send the new message
        }

        // Write the data to the socket
        int status = write(s, dataToSend.c_str(), dataToSend.length());
        if (status < 0) {
            perror("Write failed");
            close(s);
            s = -1; // Mark socket as invalid
            continue; // Attempt to reconnect in the next iteration
        }

        cout << "Sent: " << dataToSend << endl;

        // Wait for response
        auto startTime = chrono::steady_clock::now();
        bool responseReceived = false;

        while (chrono::steady_clock::now() - startTime < chrono::milliseconds(500)) {
            memset(buffer, 0, sizeof(buffer)); // Clear the temporary buffer
            int bytesRead = read(s, buffer, sizeof(buffer) - 1);

            if (bytesRead > 0) {
                // Append received bytes to the accumulated buffer
                receivedMessageBuffer.append(buffer, bytesRead);

                // Check if the termination character 'X' is present
                size_t endPos = receivedMessageBuffer.find('X');
                if (endPos != string::npos) {
                    // Full message received
                    string fullMessage = receivedMessageBuffer.substr(0, endPos);
                    receivedMessageBuffer.erase(0, endPos + 1); // Remove processed message

                    size_t commaPos = fullMessage.find(',');
                    if (commaPos != string::npos) {
                        string StatusPart = fullMessage.substr(0, commaPos); // ACK or NACK
                        string ObstructionPart = fullMessage.substr(commaPos + 1);

                        int ObstructionState = stoi(ObstructionPart); // Corrected variable name
                        handler->setObstructionState(ObstructionState); // Set the obstruction state in the handler

                        /*
                        if (ObstructionState == 1) { // Corrected variable name
                            cout << "Obstruction detected!" << endl;
                        } else {
                            cout << "No obstruction detected." << endl; // Most of the time
                        }
                        */

                        if (StatusPart == "ACK") {
                            // cout << "ACK received." << endl;

                            string ackMessage = "ACK," + to_string(ObstructionState) + "X"; 

                            // Only reset if lastSentMessage had shootState=1
                            if (!lastSentMessage.empty()) {
                                // Assuming your message format is "$,x,y,shootStateX"
                                size_t lastComma = lastSentMessage.rfind(',');
                                if (lastComma != std::string::npos && lastSentMessage[lastComma + 1] == '1') {
                                    handler->setShootState(false);
                                    cout << "Shoot state reset to false after ACK." << endl;
                                }
                            }

                            lastSentMessage.clear(); 
                            resendLastMessage = false;
                            responseReceived = true;
                            break;

                        } else if (StatusPart == "NACK") { 
                            // cout << "NACK received." << endl;

                            string nackMessage = "NACK," + to_string(ObstructionState) + "X"; 

                            // Resend, since the PSoC didn't correctly receive the data
                            resendLastMessage = true;
                            responseReceived = true;
                            break;
                        } else {
                            cout << "Unexpected message received: " << StatusPart << endl;
                            // Do nothing, keep waiting for ACK/NACK
                        }
                    } else {
                        cout << "Invalid message format received: " << fullMessage << endl;
                    }
                }
            } else if (bytesRead < 0) {
                perror("Read failed");
                close(s);
                s = -1; // Mark socket as invalid
                continue; // Attempt to reconnect in the next iteration
            }
            this_thread::sleep_for(chrono::milliseconds(100)); // Avoid busy-waiting
        }
    
        // Timeout handling
        if (!responseReceived) {
            cout << "Timeout waiting for ACK/NACK. Treating as NACK and resending the last message." << endl;
            resendLastMessage = true;
            retryCount++;

            if (retryCount >= maxRetries) {
                cerr << "Max retries reached." << endl;
                break;
            }
        } else {
            retryCount = 0; // Reset retry count on successful response
        }

        this_thread::sleep_for(chrono::milliseconds(400)); // Avoid busy-waiting
    }
    
    cout << "Stopping Bluetooth sender/receiver loop." << endl;
    close(s);
}