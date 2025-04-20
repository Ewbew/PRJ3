#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "BluetoothThread.h"
#include "VarHandler.h"

using namespace std;

// Global stop signal
atomic<bool> keepRunning(true);

int main() {
    VarHandler handler;
    string targetBluetoothAddress = "00:1A:7D:DA:71:13"; // REPLACE WITH MAC ADRESS OF PSOC
    //THIS IS SUPER IMPORTANT OR IT WILL NOT WORK

    // Start Bluetooth sender in its own thread
    thread btThread(bluetoothSenderLoop, targetBluetoothAddress, &handler);

    // Simulate main thread updating the variable
    for (int i = 0; i < 10; ++i) {
        handler.SetVar("VAR1"+ to_string(i)+"VAR2"+to_string(i));
        this_thread::sleep_for(chrono::seconds(3));
    }

    // Stop the Bluetooth loop
    keepRunning = false;
    btThread.join();

    cout << "Program complete." << endl;
    return 0;
}
