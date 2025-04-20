#include "SpeedController.h"

VarHandler::VarHandler(QWidget* parent) : QObject(parent), speed1_(0), speed2_(0) {
    slider1_ = new QSlider(Qt::Horizontal, parent);
    slider2_ = new QSlider(Qt::Horizontal, parent);

    slider1_->setRange(0, 100);
    slider2_->setRange(0, 100);

    slider1_->setValue(0);
    slider2_->setValue(0);

    connect(slider1_, &QSlider::valueChanged, this, &VarHandler::setSpeed1);
    connect(slider2_, &QSlider::valueChanged, this, &VarHandler::setSpeed2);

    thread1_ = std::thread(&VarHandler::runThread1, this);
    thread2_ = std::thread(&VarHandler::runThread2, this);
}

VarHandler::~VarHandler() {
    thread1_.join();
    thread2_.join();
    delete slider1_;
    delete slider2_;
}

int VarHandler::getSpeed1() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return speed1_;
}

int VarHandler::getSpeed2() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return speed2_;
}

QSlider* VarHandler::getSlider1() const {
    return slider1_;
}

QSlider* VarHandler::getSlider2() const {
    return slider2_;
}

void VarHandler::setSpeed1(int speed) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        speed1_ = speed;
    }
    sendSpeedValues();
}

void VarHandler::setSpeed2(int speed) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        speed2_ = speed;
    }
    sendSpeedValues();
}

void VarHandler::sendSpeedValues() {
    // Send the speed values over Bluetooth
    // (replace with your Bluetooth communication code)
    qDebug() << "Sending speed values over Bluetooth: Speed1=" << getSpeed1() << ", Speed2=" << getSpeed2();
}

void VarHandler::runThread1() {
    while (true) {
        // Motor control logic for motor 1 using getSpeed1()
        // (replace with your motor control code)
        qDebug() << "Thread 1: Motor 1 speed is " << getSpeed1();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust as needed
    }
}

void VarHandler::runThread2() {
    while (true) {
        // Motor control logic for motor 2 using getSpeed2()
        // (replace with your motor control code)
        qDebug() << "Thread 2: Motor 2 speed is " << getSpeed2();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust as needed
    }
}