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
        string dataToSend = handler->GetVar();

        int status = write(s, dataToSend.c_str(), dataToSend.length());
        if (status < 0) {
            perror("Write failed");
            break;
        }

        cout << "Sent: " << dataToSend << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    cout << "Stopping Bluetooth sender loop." << endl;
    close(s);
}
