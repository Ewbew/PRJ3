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

/* Old code; removed while debugging
// Global stop signal
atomic<bool> keepRunning(true);

int main(int argc, char *argv[]) {
    VarHandler handler;
    string targetBluetoothAddress = "98:D3:51:FE:6F:30"; // REPLACE WITH MAC ADRESS OF PSOC
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

*/


atomic<bool> keepRunning(true);


int main(int argc, char *argv[]) {
    VarHandler handler;
    string targetBluetoothAddress = "98:D3:51:FE:6F:30"; // REPLACE WITH MAC ADRESS OF PSOC

    // Start Bluetooth sender in its own thread
    thread btThread(bluetoothSenderLoop, targetBluetoothAddress, &handler);

    // Commenting the two lines below out while debugging
    //QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, false);
    //QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // optional but good for touch screens

    QApplication app(argc, argv);

    SliderWindow window(&handler);
    window.resize(800, 600);
    window.showFullScreen();

    // Keep the application runnings
    int result = app.exec();

    // Stop the Bluetooth loop after the application exits
    keepRunning = false;
    btThread.join();

    cout << "Program complete." << endl;
    return result;
}









