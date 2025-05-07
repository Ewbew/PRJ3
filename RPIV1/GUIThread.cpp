#include "GUIThread.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDial>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <iostream>

SliderWindow::SliderWindow(VarHandler* handler, QWidget *parent)
    : QWidget(parent), VarHandler_(handler)
{
    layout = new QVBoxLayout(this);
    modeTitle = new QLabel(this);
    layout->addWidget(modeTitle);

    controlWidgetLayout = new QHBoxLayout();
    layout->addLayout(controlWidgetLayout);

    toggleModeButton = new QPushButton("Switch Mode", this);
    toggleShootStateButton = new QPushButton("Toggle ShootState", this);
    toggleShootStateButton->setVisible(false);
    layout->addWidget(toggleModeButton);
    layout->addWidget(toggleShootStateButton);

    // DRIVE MODE
    driveLabel1 = new QLabel("Drive Var1", this);
    driveSlider1 = new QSlider(Qt::Vertical, this);
    driveSlider1->setRange(-50, 50);
    connect(driveSlider1, &QSlider::valueChanged, this, [=](int value){
        VarHandler_->setVar1DriveMode(value);
    });

    driveLabel2 = new QLabel("Drive Var2", this);
    driveSlider2 = new QSlider(Qt::Vertical, this);
    driveSlider2->setRange(-50, 50);
    connect(driveSlider2, &QSlider::valueChanged, this, [=](int value){
        VarHandler_->setVar2DriveMode(value);
    });

    QVBoxLayout* driveLayout1 = new QVBoxLayout();
    driveLayout1->addWidget(driveLabel1);
    driveLayout1->addWidget(driveSlider1);

    QVBoxLayout* driveLayout2 = new QVBoxLayout();
    driveLayout2->addWidget(driveLabel2);
    driveLayout2->addWidget(driveSlider2);

    controlWidgetLayout->addLayout(driveLayout1);
    controlWidgetLayout->addLayout(driveLayout2);

    // SHOOT MODE
    shootDialLabel = new QLabel("Shoot Var1 (Angle)", this);
    shootDial = new QDial(this);
    shootDial->setRange(-100, 100);
    connect(shootDial, &QDial::valueChanged, this, [=](int value){
        VarHandler_->setVar1ShootMode(value);
    });

    shootSliderLabel = new QLabel("Shoot Var2 (Elevation)", this);
    shootSlider = new QSlider(Qt::Vertical, this);
    shootSlider->setRange(0, 50);
    connect(shootSlider, &QSlider::valueChanged, this, [=](int value){
        VarHandler_->setVar2ShootMode(value);
    });

    QVBoxLayout* shootLayout1 = new QVBoxLayout();
    shootLayout1->addWidget(shootDialLabel);
    shootLayout1->addWidget(shootDial);

    QVBoxLayout* shootLayout2 = new QVBoxLayout();
    shootLayout2->addWidget(shootSliderLabel);
    shootLayout2->addWidget(shootSlider);

    controlWidgetLayout->addLayout(shootLayout1);
    controlWidgetLayout->addLayout(shootLayout2);

    connect(toggleModeButton, &QPushButton::clicked, this, &SliderWindow::toggleMode);

    // Update: Hold button to shoot
    connect(toggleShootStateButton, &QPushButton::pressed, this, [=]() {
        VarHandler_->setShootState(true);
    });
    connect(toggleShootStateButton, &QPushButton::released, this, [=]() {
        VarHandler_->setShootState(false);
    });

    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &SliderWindow::printStatus);
    statusTimer->start(1000);

    setLayout(layout);
    setWindowTitle("Slider Mode Example");

    VarHandler_->setControlMode(2);  // Default to Drive Mode
    updateMode();
}

void SliderWindow::updateMode() {
    int mode = VarHandler_->getControlMode();
    bool isDrive = (mode == 2);
    bool isShoot = (mode == 3);

    modeTitle->setText(isDrive ? "Drive Mode" : "Shoot Mode");
    toggleShootStateButton->setVisible(isShoot);

    // Show/Hide Drive Widgets
    driveLabel1->setVisible(isDrive);
    driveSlider1->setVisible(isDrive);
    driveLabel2->setVisible(isDrive);
    driveSlider2->setVisible(isDrive);

    // Show/Hide Shoot Widgets
    shootDialLabel->setVisible(isShoot);
    shootDial->setVisible(isShoot);
    shootSliderLabel->setVisible(isShoot);
    shootSlider->setVisible(isShoot);

    // Sync values
    if (isDrive) {
        driveSlider1->setValue(VarHandler_->getVar1DriveMode());
        driveSlider2->setValue(VarHandler_->getVar2DriveMode());
    } else if (isShoot) {
        shootDial->setValue(VarHandler_->getVar1ShootMode());
        shootSlider->setValue(VarHandler_->getVar2ShootMode());
    }
}

void SliderWindow::toggleMode() {
    int current = VarHandler_->getControlMode();
    VarHandler_->setControlMode(current == 2 ? 3 : 2);
    updateMode();
}

void SliderWindow::printStatus() {
    int mode = VarHandler_->getControlMode();
    std::cout << "[Status] Mode: " << mode;

    if (mode == 2) {
        int v1 = VarHandler_->getVar1DriveMode();
        int v2 = VarHandler_->getVar2DriveMode();
        std::cout << " | Drive Var1: " << v1 << " | Drive Var2: " << v2 << std::endl;
    } else if (mode == 3) {
        int v1 = VarHandler_->getVar1ShootMode();
        int v2 = VarHandler_->getVar2ShootMode();
        bool shootState = VarHandler_->getShootState();
        std::cout << " | Shoot Var1: " << v1
                  << " | Shoot Var2: " << v2
                  << " | ShootState: " << (shootState ? "ON" : "OFF")
                  << std::endl;
    } else {
        std::cout << " | Unknown mode" << std::endl;
    }
}
