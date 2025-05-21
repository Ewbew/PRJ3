#include "BluetoothThread.h"
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;

extern atomic<bool> keepRunning;

class BluetoothSender {
public:
    BluetoothSender(const string& destAddr, VarHandler* handler)
        : destAddr(destAddr), handler(handler), s(-1), retryCount(0), resendLastMessage(false) {
        memset(&addr, 0, sizeof(addr));
        addr.rc_family = AF_BLUETOOTH;
        addr.rc_channel = (uint8_t)1;
        str2ba(destAddr.c_str(), &addr.rc_bdaddr);
    }

    void run() {
        connectLoop();
        while (keepRunning) {
            if (s < 0) {
                reconnect();
                if (s < 0) continue;
            }
            sendAndReceive();
        }
        cout << "Stopping Bluetooth sender/receiver loop." << endl;
        if (s >= 0) close(s);
    }

private:
    string destAddr;
    VarHandler* handler;
    struct sockaddr_rc addr;
    int s;
    char buffer[1024];
    string receivedMessageBuffer;
    string lastSentMessage;
    bool resendLastMessage;
    int retryCount;
    const int maxRetries = 5;

    void connectLoop() {
        while (keepRunning) {
            s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
            if (s < 0) {
                perror("Socket creation failed");
                handler->setSocketDisconnected(true);
                this_thread::sleep_for(chrono::milliseconds(500));
                continue;
            }
            if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("Connection failed");
                close(s);
                handler->setSocketDisconnected(true);
                this_thread::sleep_for(chrono::milliseconds(500));
                continue;
            }
            setTimeout();
            handler->setSocketDisconnected(false);
            cout << "Connected to " << destAddr << " - starting send/receive loop." << endl;
            break;
        }
    }

    void setTimeout() {
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 500000;
        setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    }

    void reconnect() {
        cerr << "Socket disconnected. Attempting to reconnect..." << endl;
        handler->setSocketDisconnected(true);
        s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        if (s < 0) {
            perror("Socket creation failed during reconnection");
            this_thread::sleep_for(chrono::seconds(1));
            return;
        }
        if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("Reconnection failed");
            close(s);
            s = -1;
            this_thread::sleep_for(chrono::seconds(1));
            return;
        }
        setTimeout();
        cout << "Reconnected to " << destAddr << endl;
        handler->setSocketDisconnected(false);
    }

    void sendAndReceive() {
        string dataToSend;
        if (resendLastMessage) {
            dataToSend = lastSentMessage;
        } else {
            string newMessage = handler->getMessage();
            if (!newMessage.empty() && (lastSentMessage.empty() || lastSentMessage != newMessage)) {
                lastSentMessage = newMessage;
            }
            dataToSend = lastSentMessage;
        }
        int status = write(s, dataToSend.c_str(), dataToSend.length());
        if (status < 0) {
            perror("Write failed");
            close(s);
            s = -1;
            return;
        }
        cout << "Sent: " << dataToSend << endl;

        auto startTime = chrono::steady_clock::now();
        bool responseReceived = false;
        while (chrono::steady_clock::now() - startTime < chrono::milliseconds(500)) {
            memset(buffer, 0, sizeof(buffer));
            int bytesRead = read(s, buffer, sizeof(buffer) - 1);
            if (bytesRead > 0) {
                receivedMessageBuffer.append(buffer, bytesRead);
                size_t endPos = receivedMessageBuffer.find('X');
                if (endPos != string::npos) {
                    string fullMessage = receivedMessageBuffer.substr(0, endPos);
                    receivedMessageBuffer.erase(0, endPos + 1);
                    size_t commaPos = fullMessage.find(',');
                    if (commaPos != string::npos) {
                        string StatusPart = fullMessage.substr(0, commaPos);
                        string ObstructionPart = fullMessage.substr(commaPos + 1);
                        int ObstructionState = stoi(ObstructionPart);
                        handler->setObstructionState(ObstructionState);
                        if (StatusPart == "ACK") {
                            if (!lastSentMessage.empty()) {
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
                            resendLastMessage = true;
                            responseReceived = true;
                            break;
                        } else {
                            cout << "Unexpected message received: " << StatusPart << endl;
                        }
                    } else {
                        cout << "Invalid message format received: " << fullMessage << endl;
                    }
                }
            } else if (bytesRead == 0) {
                cout << "Connection closed by remote device." << endl;
                close(s);
                s = -1;
                handler->setSocketDisconnected(true);
                break;
            } else if (bytesRead < 0) {
                perror("Read failed");
                close(s);
                s = -1;
                handler->setSocketDisconnected(true);
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        if (!responseReceived) {
            cout << "Timeout waiting for ACK/NACK. Treating as NACK and resending the last message." << endl;
            resendLastMessage = true;
            retryCount++;
            if (retryCount >= maxRetries) {
                cerr << "Max retries reached." << endl;
                keepRunning = false;
            }
        } else {
            retryCount = 0;
        }
    }
};

// Replace the old function with a wrapper
void bluetoothSenderLoop(const string& destAddr, VarHandler* handler) {
    BluetoothSender sender(destAddr, handler);
    sender.run();
}