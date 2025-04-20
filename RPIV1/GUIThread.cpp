#include "GUIThread.h"

SliderWindow::SliderWindow(VarHandler* handler, QWidget *parent)
    : QWidget(parent), VarHandler_(handler), var1(0), var2(0)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    label1 = new QLabel(QString("Variable 1: %1").arg(var1), this);
    slider1 = new QSlider(Qt::Horizontal, this);
    slider1->setRange(-50, 50);
    slider1->setValue(var1);

    label2 = new QLabel(QString("Variable 2: %1").arg(var2), this);
    slider2 = new QSlider(Qt::Horizontal, this);
    slider2->setRange(-50, 50);
    slider2->setValue(var2);

    layout->addWidget(label1);
    layout->addWidget(slider1);
    layout->addWidget(label2);
    layout->addWidget(slider2);

    setLayout(layout);
    setWindowTitle("Two Sliders Example");

    connect(slider1, &QSlider::valueChanged, this, &SliderWindow::updateVar1);
    connect(slider2, &QSlider::valueChanged, this, &SliderWindow::updateVar2);
}

void SliderWindow::updateVar1(int value) {
    var1 = value;
    VarHandler_->setVar1(value);
    label1->setText(QString("Variable 1: %1").arg(var1));
}

void SliderWindow::updateVar2(int value) {
    var2 = value;
    VarHandler_->setVar2(value);
    label2->setText(QString("Variable 2: %1").arg(var2));
}
