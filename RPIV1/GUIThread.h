#pragma once

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include "VarHandler.h"

class SliderWindow : public QWidget {
    Q_OBJECT

public:
    SliderWindow(VarHandler* handler,QWidget *parent = nullptr);

private slots:
    void updateVar1(int value);

    void updateVar2(int value);

private:
    int var1, var2;
    VarHandler* VarHandler_;
    QLabel *label1, *label2;
    QSlider *slider1, *slider2;
};

