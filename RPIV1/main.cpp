#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "BluetoothThread.h"
#include "VarHandler.h"
#include "GUIThread.h"

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>



using namespace std;




// Global stop signal
atomic<bool> keepRunning(true);

int main(int argc, char *argv[]) {
    VarHandler handler;
    string targetBluetoothAddress = "00:1A:7D:DA:71:13"; // REPLACE WITH MAC ADRESS OF PSOC
    //THIS IS SUPER IMPORTANT OR IT WILL NOT WORK

    // Start Bluetooth sender in its own thread
    thread btThread(bluetoothSenderLoop, targetBluetoothAddress, &handler);

    QApplication app(argc, argv);

    SliderWindow window(&handler);
    window.resize(800, 600);
    window.show();

    

    // Stop the Bluetooth loop
    keepRunning = false;
    btThread.join();

    cout << "Program complete." << endl;
    return app.exec();
}








