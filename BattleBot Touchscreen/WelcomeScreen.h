#pragma once

/*
We need to install QT libraries on the RPi for the sliders to work.

Type the following in the terminal:

sudo apt-get update
sudo apt-get install qt5-default qtcreator

to use the QSlider and QWidget classes :)
*/



#include <QWidget>

class WelcomeScreen : public QWidget {
    Q_OBJECT

public:
    WelcomeScreen(QWidget* parent = nullptr);
    ~WelcomeScreen();
};