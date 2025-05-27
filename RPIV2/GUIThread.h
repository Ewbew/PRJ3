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

/**
 * @brief Main GUI window for controlling the robot.
 * 
 * Provides drive and shoot controls, mode switching, and status display.
 */
class SliderWindow : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Construct the SliderWindow.
     * @param handler Pointer to the VarHandler for state management.
     * @param parent Parent widget (optional).
     */
    explicit SliderWindow(VarHandler* handler, QWidget *parent = nullptr);

protected:
    /**
     * @brief Event handler for touch and other events.
     * @param event The event object.
     * @return True if event was handled.
     */
    bool event(QEvent* event) override;

    /**
     * @brief Handle key press events (e.g., ESC to exit fullscreen).
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent* event) override; // Add this line

private slots:
    /**
     * @brief Update the UI to reflect the current mode.
     */
    void updateMode();

    /**
     * @brief Toggle between drive and shoot modes.
     */
    void toggleMode();

    /**
     * @brief Print or update the status/warning label.
     */
    void printStatus();

private:
    VarHandler* VarHandler_;                ///< Pointer to the variable handler

    QLabel* warningLabel;                   ///< Warning/status label
    QVBoxLayout* layout;                    ///< Main vertical layout
    QHBoxLayout* controlWidgetLayout;       ///< Layout for control widgets

    QLabel* modeTitle;                      ///< Label for current mode
    QPushButton* toggleModeButton;          ///< Button to switch modes
    QPushButton* toggleShootStateButton;    ///< Button to trigger shooting
    QTimer* statusTimer;                    ///< Timer for status updates

    // Drive mode widgets
    QLabel* driveLabel1;                    ///< Label for right wheel
    QSlider* driveSlider1;                  ///< Slider for right wheel
    QLabel* driveLabel2;                    ///< Label for left wheel
    QSlider* driveSlider2;                  ///< Slider for left wheel

    // Shoot mode widgets
    QLabel* shootDialLabel;                 ///< Label for turret horizontal
    QDial* shootDial;                       ///< Dial for turret horizontal
    QLabel* shootSliderLabel;               ///< Label for turret vertical
    QSlider* shootSlider;                   ///< Slider for turret vertical
};

#endif // SLIDERWINDOW_H
