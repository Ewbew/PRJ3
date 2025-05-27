#include "stepper.h"
#include "control.h" // For startStepperTimerWithPeriod
#include <stdlib.h>

// === PIN-MAKROER ===
#define DIAL_STEP_PIN_STEP    dialStepPin_Write(1)
#define DIAL_STEP_PIN_RESET   dialStepPin_Write(0)
#define DIAL_DIR_PIN_FORWARD  dialDirPin_Write(1)
#define DIAL_DIR_PIN_BACKWARD dialDirPin_Write(0)

#define ANGLE_STEP_PIN_STEP    angleStepPin_Write(1)
#define ANGLE_STEP_PIN_RESET   angleStepPin_Write(0)
#define ANGLE_DIR_PIN_FORWARD  angleDirPin_Write(1)
#define ANGLE_DIR_PIN_BACKWARD angleDirPin_Write(0)

// === GLOBALE VARIABLER ===
volatile int8 dialCurrentPosition = 0;
volatile int8 dialDirection = 1;
volatile int8 dialStepsRemaining = 0;

volatile int8 angleCurrentPosition = 0;
volatile int8 angleDirection = 1;
volatile int8 angleStepsRemaining = 0;

// Kaldes én gang per timer interrupt
void stepperTick(void)
{
    if (dialStepsRemaining > 0)
    {
        DIAL_STEP_PIN_STEP;
        CyDelayUs(50);
        DIAL_STEP_PIN_RESET;
        dialStepsRemaining--;
        dialCurrentPosition += dialDirection;
    }

    if (angleStepsRemaining > 0)
    {
        ANGLE_STEP_PIN_STEP;
        CyDelayUs(50);
        ANGLE_STEP_PIN_RESET;
        angleStepsRemaining--;
        angleCurrentPosition += angleDirection;
    }
}

// Initialiser retning og steps for dial og angle
void setStepperTargets(int8 dialTarget, int8 angleTarget)
{
    int16 delta;

    // === Dial motor ===
    if (dialTarget > DIAL_MAX_POSITION) dialTarget = DIAL_MAX_POSITION;
    if (dialTarget < DIAL_MIN_POSITION) dialTarget = DIAL_MIN_POSITION;

    delta = dialTarget - dialCurrentPosition;
    dialDirection = (delta > 0) ? 1 : -1;
    dialStepsRemaining = abs(delta);
    if (dialDirection > 0) DIAL_DIR_PIN_FORWARD; else DIAL_DIR_PIN_BACKWARD;

    // === Angle motor ===
    if (angleTarget > ANGLE_MAX_POSITION) angleTarget = ANGLE_MAX_POSITION;
    if (angleTarget < ANGLE_MIN_POSITION) angleTarget = ANGLE_MIN_POSITION;

    delta = angleTarget - angleCurrentPosition;
    angleDirection = (delta > 0) ? 1 : -1;
    angleStepsRemaining = abs(delta);
    if (angleDirection > 0) ANGLE_DIR_PIN_FORWARD; else ANGLE_DIR_PIN_BACKWARD;

    // Start timer hvis nødvendigt
    if (dialStepsRemaining > 0 || angleStepsRemaining > 0)
    {
        startStepperTimerWithPeriod(STEPPER_TIMER_PERIOD);
    }
}

// Returnerer 1 hvis begge motorer er færdige ellers 0
uint8 stepperIsIdle(void)
{
    return (dialStepsRemaining == 0 && angleStepsRemaining == 0) ? 1 : 0;
}


// Nulstil pins ved init
void initStepperPins(void)
{
    dialStepPin_Write(0);
    dialDirPin_Write(0);
    angleStepPin_Write(0);
    angleDirPin_Write(0);
}
