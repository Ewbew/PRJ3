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

    // Create a Bluetooth socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (s < 0) {
        perror("Socket creation failed");
        return;
    }

    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t)1;
    str2ba(destAddr.c_str(), &addr.rc_bdaddr);

    // Connect to the Bluetooth device
    if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connection failed");
        close(s);
        return;
    }

    cout << "Connected to " << destAddr << " - starting send/receive loop." << endl;

    char buffer[1024]; // Temporary buffer for receiving data
    string receivedMessageBuffer; // Accumulate received bytes here
    string lastSentMessage; // Store the last sent message
    bool resendLastMessage = false; // Flag to indicate if the last message should be resent

    while (keepRunning) {
        // Send data
        string dataToSendCombined;
        if (!resendLastMessage) {
            dataToSendCombined = handler->getMessage();
            if (lastSentMessage.empty() || lastSentMessage != dataToSendCombined) {
                lastSentMessage = dataToSendCombined; // Update the last sent message
            }
        }

        int status = write(s, lastSentMessage.c_str(), lastSentMessage.length());
        if (status < 0) {
            perror("Write failed");
            break;
        }

        cout << "Sent: " << lastSentMessage << endl;

        // Wait for ACK/NACK with timeout
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

                    cout << "Received: " << fullMessage << endl;

                    // Handle ACK/NACK
                    if (fullMessage == "ACK") {
                        cout << "ACK received. Preparing to send the next message." << endl;
                        handler->setLastMessageAcknowledged(true); // Mark the last message as acknowledged
                        lastSentMessage.clear(); // Clear the last sent message to fetch new data
                        resendLastMessage = false; // Allow sending the next message
                        responseReceived = true;
                        break;
                    } else if (fullMessage == "NACK") {
                        cout << "NACK received. Resending the last message." << endl;
                        handler->setLastMessageAcknowledged(false); // Mark the last message as not acknowledged
                        resendLastMessage = true; // Keep resending the last message
                        responseReceived = true;
                        break;
                    } else {
                        cout << "Unexpected message received: " << fullMessage << endl;
                        // Do nothing, keep waiting for ACK/NACK
                    }
                }
            } else if (bytesRead < 0) {
                perror("Read failed");
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(100)); // Avoid busy-waiting
        }

        // Timeout handling
        if (!responseReceived) {
            cout << "Timeout waiting for ACK/NACK. Treating as NACK and resending the last message." << endl;
            resendLastMessage = true; // Resend the last message
        }
    }

    cout << "Stopping Bluetooth sender/receiver loop." << endl;
    close(s);
}
