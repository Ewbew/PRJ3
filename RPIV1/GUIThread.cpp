#include "GUIThread.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDial>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QEvent>
#include <QTouchEvent>
#include <QApplication>
#include <QPoint>
#include <iostream>

SliderWindow::SliderWindow(VarHandler* handler, QWidget *parent)
    : QWidget(parent), VarHandler_(handler)
{
    setAttribute(Qt::WA_AcceptTouchEvents);  // Enable touch input

    
    layout = new QVBoxLayout(this);
    modeTitle = new QLabel(this);
    layout->addWidget(modeTitle);

    controlWidgetLayout = new QHBoxLayout();
    layout->addLayout(controlWidgetLayout);

    toggleModeButton = new QPushButton("Switch Mode", this);
    toggleShootStateButton = new QPushButton("Shoot!", this);
    toggleShootStateButton->setVisible(false);
    layout->addWidget(toggleModeButton);
    layout->addWidget(toggleShootStateButton);

    warningLabel = new QLabel("You're about to hit a wall, one second.", this);
    warningLabel->setStyleSheet("color: red; font-weight: bold;");
    warningLabel->setVisible(false);
    layout->addWidget(warningLabel);

    // DRIVE MODE
    driveLabel1 = new QLabel("Left wheel", this);
    driveSlider1 = new QSlider(Qt::Vertical, this);
    driveSlider1->setRange(-50, 50);
    driveSlider1->setFixedWidth(100);
    driveSlider1->setStyleSheet(R"(
        QSlider::groove:vertical {
            background: #cccccc;
            width: 100px;
            border: 1px solid #999999;
        }
        QSlider::handle:vertical {
            background: #66ccff;
            border: 1px solid #3399ff;
            width: 100px;
            height: 100px;
            margin: 0 -10px;
            border-radius: 6px;
        }
    )");
    connect(driveSlider1, &QSlider::valueChanged, this, [=](int value){
        VarHandler_->setVar1DriveMode(value);
    });

    driveLabel2 = new QLabel("Right wheel", this);
    driveSlider2 = new QSlider(Qt::Vertical, this);
    driveSlider2->setRange(-50, 50);
    driveSlider2->setFixedWidth(100);
    driveSlider2->setStyleSheet(driveSlider1->styleSheet());  // reuse style
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
    shootDialLabel = new QLabel("Turret angle (horizontal))", this);
    shootDial = new QDial(this);
    shootDial->setRange(-100, 100);
    connect(shootDial, &QDial::valueChanged, this, [=](int value){
        VarHandler_->setVar1ShootMode(value);
    });

    shootSliderLabel = new QLabel("Turret angle (vertical)", this);
    shootSlider = new QSlider(Qt::Vertical, this);
    shootSlider->setRange(0, 50);
    shootSlider->setFixedWidth(100);
    shootSlider->setStyleSheet(driveSlider1->styleSheet());  // reuse style
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

    connect(toggleShootStateButton, &QPushButton::clicked, this, [=]() {
        VarHandler_->setShootState(true);
    });

    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &SliderWindow::printStatus);
    statusTimer->start(1000);

    setLayout(layout);
    setWindowTitle("SWEET BATTLEBOT");

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

    // If switching from drive mode to shoot mode, reset speed variables
    if (current == 2) { // Drive mode
        VarHandler_->setVar1DriveMode(0); // Reset Drive Var1 to 0
        VarHandler_->setVar2DriveMode(0); // Reset Drive Var2 to 0
        std::cout << "Drive mode variables reset to 0." << std::endl;
    }

    // Toggle between drive mode (2) and shoot mode (3)
    VarHandler_->setControlMode(current == 2 ? 3 : 2);
    updateMode();
}

void SliderWindow::printStatus() {
    int mode = VarHandler_->getControlMode();
    // std::cout << "[Status] Mode: " << mode;

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

    // Show warning if obstruction is detected
    if (VarHandler_->getObstructionState() == 1) {
        warningLabel->setText("You're about to hit a wall, one second.");
        warningLabel->setVisible(true);
    }

    // Show warning if the socket is disconnected
    if (VarHandler_->isSocketDisconnected()) {
        warningLabel->setText("Socket disconnected. Attempting to reconnect...");
        warningLabel->setVisible(true);
    }

    // Hide the warning label if no issues are present
    if (VarHandler_->getObstructionState() != 1 && !VarHandler_->isSocketDisconnected()) {
        warningLabel->setVisible(false);
    }
}



bool SliderWindow::event(QEvent* event)
{
    if (event->type() == QEvent::TouchBegin ||
        event->type() == QEvent::TouchUpdate ||
        event->type() == QEvent::TouchEnd) {

        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        const QList<QTouchEvent::TouchPoint>& points = touchEvent->touchPoints();

        bool handled = false;
        for (const QTouchEvent::TouchPoint& point : points) {
            QPointF pos = point.pos(); // touch position
            QWidget* targetWidget = childAt(pos.toPoint()); // Ensure pos is converted to QPoint

            if (!targetWidget) continue;

            // Handle drive sliders
            if (driveSlider1->isVisible() && driveSlider1->geometry().contains(pos.toPoint())) {
                int sliderY = driveSlider1->mapFrom(this, pos.toPoint()).y();
                int sliderHeight = driveSlider1->height();
                int range = driveSlider1->maximum() - driveSlider1->minimum();
                int value = driveSlider1->maximum() - (sliderY * range / sliderHeight);
                driveSlider1->setValue(value);
                handled = true;
            }
            else if (driveSlider2->isVisible() && driveSlider2->geometry().contains(pos.toPoint())) {
                int sliderY = driveSlider2->mapFrom(this, pos.toPoint()).y();
                int sliderHeight = driveSlider2->height();
                int range = driveSlider2->maximum() - driveSlider2->minimum();
                int value = driveSlider2->maximum() - (sliderY * range / sliderHeight);
                driveSlider2->setValue(value);
                handled = true;
            }

            // Handle shoot slider
            else if (shootSlider->isVisible() && shootSlider->geometry().contains(pos.toPoint())) {
                int sliderY = shootSlider->mapFrom(this, pos.toPoint()).y();
                int sliderHeight = shootSlider->height();
                int range = shootSlider->maximum() - shootSlider->minimum();
                int value = shootSlider->maximum() - (sliderY * range / sliderHeight);
                shootSlider->setValue(value);
                handled = true;
            }
        }

        if (handled)
            return true;
    }

    return QWidget::event(event); // fallback
}
