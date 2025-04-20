#pragma once

/*
We need to install QT libraries on the RPi for the sliders to work.

Type the following in the terminal:

sudo apt-get update
sudo apt-get install qt5-default qtcreator

to use the QSlider and QWidget classes :) 
*/


#include <QObject>
#include <QSlider>
#include <QWidget>
#include <thread>
#include <mutex>

class VarHandler : public QObject { // Renamed from SpeedController to VarHandler
    Q_OBJECT

public:
    VarHandler(QWidget* parent = nullptr); // Renamed constructor
    ~VarHandler();

    int getSpeed1() const;
    int getSpeed2() const;

    QSlider* getSlider1() const;
    QSlider* getSlider2() const;

public slots:
    void setSpeed1(int speed);
    void setSpeed2(int speed);

    void sendSpeedValues();

private:
    int speed1_;
    int speed2_;

    QSlider* slider1_;
    QSlider* slider2_;

    std::thread thread1_;
    std::thread thread2_;

    std::mutex mutex_;

    void runThread1();
    void runThread2();
};