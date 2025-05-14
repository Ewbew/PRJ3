#ifndef SLIDERWINDOW_H
#define SLIDERWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QDial>
#include <QPushButton>
#include <QTimer>
#include <QEvent>
#include <QTouchEvent>
#include "VarHandler.h"

class SliderWindow : public QWidget {
    Q_OBJECT

public:
    explicit SliderWindow(VarHandler* handler, QWidget *parent = nullptr);

protected:
    bool event(QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override; // Add this line

private slots:
    void updateMode();
    void toggleMode();
    void printStatus();

private:
    VarHandler* VarHandler_;

    QLabel* warningLabel;
    QVBoxLayout* layout;
    QHBoxLayout* controlWidgetLayout;

    QLabel* modeTitle;
    QPushButton* toggleModeButton;
    QPushButton* toggleShootStateButton;
    QTimer* statusTimer;

    // Drive mode widgets
    QLabel* driveLabel1;
    QSlider* driveSlider1;
    QLabel* driveLabel2;
    QSlider* driveSlider2;

    // Shoot mode widgets
    QLabel* shootDialLabel;
    QDial* shootDial;
    QLabel* shootSliderLabel;
    QSlider* shootSlider;
};

#endif // SLIDERWINDOW_H
