#include "project.h"
#include <stdlib.h>  // for abs()

// === Makroer til kontrol af A4988 stepperdriverens signaler ===
#define DIAL_STEP_PIN_STEP    dialStepPin_Write(1)
#define DIAL_STEP_PIN_RESET   dialStepPin_Write(0)
#define DIAL_DIR_PIN_FORWARD  dialDirPin_Write(1)
#define DIAL_DIR_PIN_BACKWARD dialDirPin_Write(0)

#define ANGLE_STEP_PIN_STEP    angleStepPin_Write(1)
#define ANGLE_STEP_PIN_RESET   angleStepPin_Write(0)
#define ANGLE_DIR_PIN_FORWARD  angleDirPin_Write(1)
#define ANGLE_DIR_PIN_BACKWARD angleDirPin_Write(0)

// === Konfiguration ===
#define DIAL_MAX_POSITION 100
#define DIAL_MIN_POSITION -100
#define ANGLE_MAX_POSITION 50
#define ANGLE_MIN_POSITION 0

// === Globale tilstandvariabler for begge motorer ===
volatile int8 dialCurrentPosition = 0;
volatile int8 dialTargetPosition = 0;
volatile int16 dialStepsRemaining = 0;
volatile int8 dialDirection = 1;

volatile int8 angleCurrentPosition = 0;
volatile int8 angleTargetPosition = 0;
volatile int16 angleStepsRemaining = 0;
volatile int8 angleDirection = 1;

// === Fælles timer ISR der håndterer begge steppermotorer ===
CY_ISR(Stepper_Timer_ISR_Handler)
{
    Timer_1_ReadStatusRegister();

    // --- Dial motor ---
    if (dialStepsRemaining > 0)
    {
        DIAL_STEP_PIN_STEP;
        CyDelayUs(50);
        DIAL_STEP_PIN_RESET;
        dialStepsRemaining--;
        dialCurrentPosition += dialDirection;
    }

    // --- Angle motor ---
    if (angleStepsRemaining > 0)
    {
        ANGLE_STEP_PIN_STEP;
        CyDelayUs(50);
        ANGLE_STEP_PIN_RESET;
        angleStepsRemaining--;
        angleCurrentPosition += angleDirection;
    }

    // Stop timer hvis begge motorer er færdige
    if (dialStepsRemaining == 0 && angleStepsRemaining == 0)
    {
        Timer_1_Stop();
    }
}

// === Funktion til at sætte mål for begge motorer og starte fælles timer ===
void setStepperTargets(int8 dialTarget, int8 angleTarget, uint16 timerPeriod)
{
    // --- Dial motor ---
    if (dialTarget > DIAL_MAX_POSITION) dialTarget = DIAL_MAX_POSITION;
    if (dialTarget < DIAL_MIN_POSITION) dialTarget = DIAL_MIN_POSITION;

    int16 dialDelta = dialTarget - dialCurrentPosition;
    dialDirection = (dialDelta > 0) ? 1 : -1;
    dialStepsRemaining = abs(dialDelta);
    dialTargetPosition = dialTarget;

    if (dialDirection > 0)
        DIAL_DIR_PIN_FORWARD;
    else
        DIAL_DIR_PIN_BACKWARD;

    // --- Angle motor ---
    if (angleTarget > ANGLE_MAX_POSITION) angleTarget = ANGLE_MAX_POSITION;
    if (angleTarget < ANGLE_MIN_POSITION) angleTarget = ANGLE_MIN_POSITION;

    int16 angleDelta = angleTarget - angleCurrentPosition;
    angleDirection = (angleDelta > 0) ? 1 : -1;
    angleStepsRemaining = abs(angleDelta);
    angleTargetPosition = angleTarget;

    if (angleDirection > 0)
        ANGLE_DIR_PIN_FORWARD;
    else
        ANGLE_DIR_PIN_BACKWARD;

    // Start fælles timer hvis mindst én motor skal bevæge sig
    if (dialStepsRemaining > 0 || angleStepsRemaining > 0)
    {
        Timer_1_Stop();
        Timer_1_WritePeriod(timerPeriod);
        Timer_1_WriteCounter(0);
        Timer_1_Start();
    }
}

int main(void)
{
    CyGlobalIntEnable;

    dialStepPin_Write(0);
    dialDirPin_Write(0);
    angleStepPin_Write(0);
    angleDirPin_Write(0);

    Timer_1_Start();
    Timer_1_Stop();
    stepper_isr_timer_StartEx(Stepper_Timer_ISR_Handler);

    for (;;)
    {
        setStepperTargets(0, 0, 25);
        CyDelay(500);

        setStepperTargets(100, 50, 25);
        CyDelay(500);

        setStepperTargets(-100, 0, 25);
        CyDelay(500);

        setStepperTargets(100, 55, 25);
        CyDelay(1500);
    }
}
