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

    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (s < 0) {
        perror("Socket creation failed");
        return;
    }

    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t)1;
    str2ba(destAddr.c_str(), &addr.rc_bdaddr);

    if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connection failed");
        close(s);
        return;
    }

    cout << "Connected to " << destAddr << " - starting send loop." << endl;

    while (keepRunning) {
        
        string dataToSendCombined = handler->getMessage();

        int status = write(s, dataToSendCombined.c_str(), dataToSendCombined.length());
        if (status < 0) {
            perror("Write failed");
            break;
        }

        cout << "Sent: " << dataToSendCombined << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << "Stopping Bluetooth sender loop." << endl;
    close(s);
}
