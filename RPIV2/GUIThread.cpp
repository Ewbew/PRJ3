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
    setAttribute(Qt::WA_AcceptTouchEvents);  // Enable touch input events

    // Main vertical layout and title
    layout = new QVBoxLayout(this);
    modeTitle = new QLabel(this);
    layout->addWidget(modeTitle);

    // Horizontal layout for control widgets (drive/shoot)
    controlWidgetLayout = new QHBoxLayout();
    layout->addLayout(controlWidgetLayout);

    // Mode toggle and shoot buttons
    toggleModeButton = new QPushButton("Switch Mode", this);
    toggleShootStateButton = new QPushButton("Shoot!", this);
    toggleShootStateButton->setVisible(false); // Hidden unless in shoot mode
    layout->addWidget(toggleModeButton);
    layout->addWidget(toggleShootStateButton);

    // Warning label for obstruction/socket issues
    warningLabel = new QLabel("You're about to hit a wall, one second.", this);
    warningLabel->setStyleSheet("color: red; font-weight: bold;");
    warningLabel->setVisible(false);
    layout->addWidget(warningLabel);

    // Drive mode widgets
    driveLabel1 = new QLabel("Left wheel", this);
    driveSlider1 = new QSlider(Qt::Vertical, this);
    driveSlider1->setRange(-50, 50);
    driveSlider1->setFixedWidth(100);
    driveSlider1->setStyleSheet(R"(...)");
    connect(driveSlider1, &QSlider::valueChanged, this, [=](int value){
        VarHandler_->setVar1DriveMode(value);
    });

    driveLabel2 = new QLabel("Right wheel", this);
    driveSlider2 = new QSlider(Qt::Vertical, this);
    driveSlider2->setRange(-50, 50);
    driveSlider2->setFixedWidth(100);
    driveSlider2->setStyleSheet(driveSlider1->styleSheet());
    connect(driveSlider2, &QSlider::valueChanged, this, [=](int value){
        VarHandler_->setVar2DriveMode(value);
    });

    // Add drive sliders to layouts
    QVBoxLayout* driveLayout1 = new QVBoxLayout();
    driveLayout1->addWidget(driveLabel1);
    driveLayout1->addWidget(driveSlider1);

    QVBoxLayout* driveLayout2 = new QVBoxLayout();
    driveLayout2->addWidget(driveLabel2);
    driveLayout2->addWidget(driveSlider2);

    controlWidgetLayout->addLayout(driveLayout1);
    controlWidgetLayout->addLayout(driveLayout2);

    // Shoot mode widgets
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
    shootSlider->setStyleSheet(driveSlider1->styleSheet());
    connect(shootSlider, &QSlider::valueChanged, this, [=](int value){
        VarHandler_->setVar2ShootMode(value);
    });

    // Add shoot controls to layouts
    QVBoxLayout* shootLayout1 = new QVBoxLayout();
    shootLayout1->addWidget(shootDialLabel);
    shootLayout1->addWidget(shootDial);

    QVBoxLayout* shootLayout2 = new QVBoxLayout();
    shootLayout2->addWidget(shootSliderLabel);
    shootLayout2->addWidget(shootSlider);

    controlWidgetLayout->addLayout(shootLayout1);
    controlWidgetLayout->addLayout(shootLayout2);

    // Connect button actions
    connect(toggleModeButton, &QPushButton::clicked, this, &SliderWindow::toggleMode);
    connect(toggleShootStateButton, &QPushButton::clicked, this, [=]() {
        VarHandler_->setShootState(true); // Only sets to true, reset handled externally
    });

    // Status timer to update warnings or reconnect messages
    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &SliderWindow::printStatus);
    statusTimer->start(1000);

    setLayout(layout);
    setWindowTitle("SWEET BATTLEBOT");

    VarHandler_->setControlMode(2);  // Start in drive mode
    updateMode(); // Sync UI with initial mode
}

void SliderWindow::updateMode() {
    int mode = VarHandler_->getControlMode();
    bool isDrive = (mode == 2);
    bool isShoot = (mode == 3);

    // Update mode title and visibility of relevant controls
    modeTitle->setText(isDrive ? "Drive Mode" : "Shoot Mode");
    toggleShootStateButton->setVisible(isShoot);

    driveLabel1->setVisible(isDrive);
    driveSlider1->setVisible(isDrive);
    driveLabel2->setVisible(isDrive);
    driveSlider2->setVisible(isDrive);

    shootDialLabel->setVisible(isShoot);
    shootDial->setVisible(isShoot);
    shootSliderLabel->setVisible(isShoot);
    shootSlider->setVisible(isShoot);

    // Sync slider/dial values with handler state
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

    // Reset drive speeds if leaving drive mode
    if (current == 2) {
        VarHandler_->setVar1DriveMode(0);
        VarHandler_->setVar2DriveMode(0);
        std::cout << "Drive mode variables reset to 0." << std::endl;
    }

    // Toggle between drive and shoot mode
    VarHandler_->setControlMode(current == 2 ? 3 : 2);
    updateMode(); // Refresh UI
}

void SliderWindow::printStatus() {
    int mode = VarHandler_->getControlMode();

    // Show warning and stop motion on obstruction
    if (VarHandler_->getObstructionState() == 1) {
        warningLabel->setText("You're about to hit a wall, one second.");
        warningLabel->setVisible(true);
        VarHandler_->setVar1DriveMode(0);
        VarHandler_->setVar2DriveMode(0);
        driveSlider1->setValue(0);
        driveSlider2->setValue(0);
    }

    // Show message if socket is disconnected
    if (VarHandler_->isSocketDisconnected()) {
        warningLabel->setText("Socket disconnected. Attempting to reconnect...");
        warningLabel->setVisible(true);
    }

    // Hide warning if everything is fine
    if (VarHandler_->getObstructionState() != 1 && !VarHandler_->isSocketDisconnected()) {
        warningLabel->setVisible(false);
    }
}

bool SliderWindow::event(QEvent* event)
{
    // Handle touch events for sliders
    if (event->type() == QEvent::TouchBegin ||
        event->type() == QEvent::TouchUpdate ||
        event->type() == QEvent::TouchEnd) {

        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        const QList<QTouchEvent::TouchPoint>& points = touchEvent->touchPoints();

        bool handled = false;
        for (const QTouchEvent::TouchPoint& point : points) {
            QPointF pos = point.pos();
            QWidget* targetWidget = childAt(pos.toPoint());
            if (!targetWidget) continue;

            // Adjust driveSlider1 based on touch position
            if (driveSlider1->isVisible() && driveSlider1->geometry().contains(pos.toPoint())) {
                int sliderY = driveSlider1->mapFrom(this, pos.toPoint()).y();
                int sliderHeight = driveSlider1->height();
                int range = driveSlider1->maximum() - driveSlider1->minimum();
                int value = driveSlider1->maximum() - (sliderY * range / sliderHeight);
                driveSlider1->setValue(value);
                handled = true;
            }
            // Adjust driveSlider2
            else if (driveSlider2->isVisible() && driveSlider2->geometry().contains(pos.toPoint())) {
                int sliderY = driveSlider2->mapFrom(this, pos.toPoint()).y();
                int sliderHeight = driveSlider2->height();
                int range = driveSlider2->maximum() - driveSlider2->minimum();
                int value = driveSlider2->maximum() - (sliderY * range / sliderHeight);
                driveSlider2->setValue(value);
                handled = true;
            }
            // Adjust shootSlider
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

    return QWidget::event(event); // Default fallback for unhandled events
}

void SliderWindow::keyPressEvent(QKeyEvent* event) {
    // Exit fullscreen on ESC
    if (event->key() == Qt::Key_Escape) {
        this->showNormal();
    }
    QWidget::keyPressEvent(event);
}
