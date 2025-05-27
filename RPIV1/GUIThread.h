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
 * @class SliderWindow
 * @brief GUI window for controlling drive and shoot modes.
 * 
 * This class provides a Qt-based GUI for interacting with the VarHandler,
 * allowing the user to control drive and shoot modes, toggle states, and view status.
 */
class SliderWindow : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the SliderWindow.
     * @param handler Pointer to the VarHandler instance.
     * @param parent Parent widget.
     */
    explicit SliderWindow(VarHandler* handler, QWidget *parent = nullptr);

protected:
    /**
     * @brief Handles Qt events (including touch events).
     * @param event The event to handle.
     * @return True if the event was handled, false otherwise.
     */
    bool event(QEvent* event) override;
    /**
     * @brief Handles key press events.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    /**
     * @brief Updates the mode display and state.
     */
    void updateMode();
    /**
     * @brief Toggles between drive and shoot modes.
     */
    void toggleMode();
    /**
     * @brief Prints the current status to the console or log.
     */
    void printStatus();

private:
    /**
     * @brief Pointer to the VarHandler instance.
     */
    VarHandler* VarHandler_;

    /**
     * @brief Label for displaying warnings.
     */
    QLabel* warningLabel;
    /**
     * @brief Main vertical layout.
     */
    QVBoxLayout* layout;
    /**
     * @brief Layout for control widgets.
     */
    QHBoxLayout* controlWidgetLayout;

    /**
     * @brief Label for the mode title.
     */
    QLabel* modeTitle;
    /**
     * @brief Button to toggle mode.
     */
    QPushButton* toggleModeButton;
    /**
     * @brief Button to toggle shoot state.
     */
    QPushButton* toggleShootStateButton;
    /**
     * @brief Timer for updating status.
     */
    QTimer* statusTimer;

    // Drive mode widgets
    /**
     * @brief Label for drive mode 1.
     */
    QLabel* driveLabel1;
    /**
     * @brief Slider for drive mode 1.
     */
    QSlider* driveSlider1;
    /**
     * @brief Label for drive mode 2.
     */
    QLabel* driveLabel2;
    /**
     * @brief Slider for drive mode 2.
     */
    QSlider* driveSlider2;

    // Shoot mode widgets
    /**
     * @brief Label for shoot dial.
     */
    QLabel* shootDialLabel;
    /**
     * @brief Dial for shoot mode.
     */
    QDial* shootDial;
    /**
     * @brief Label for shoot slider.
     */
    QLabel* shootSliderLabel;
    /**
     * @brief Slider for shoot mode.
     */
    QSlider* shootSlider;
};

#endif // SLIDERWINDOW_H
