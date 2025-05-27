#include "firing.h"
#include "control.h" // For startStepperTimerWithPeriod

// === INTERN STATUS ===
volatile int16 fireStepsRemaining = 0;
volatile int8 fireDirection = 1;
volatile uint8 fireStepPhase = 0;
volatile uint8 fireInProgress = 0;

// Start affyringssekvens
void fireMechanism(void)
{
    fireStepPhase = 0;
    fireDirection = 1;
    fireInProgress = 1;

    FIRE_DIR_PIN_FORWARD;
    fireStepsRemaining = FIRE_MAX_STEPS_FORWARD;

    startStepperTimerWithPeriod(FIRE_TIMER_PERIOD_FORWARD);
}

// Kaldes én gang per tick fra fælles timer
void firingStepperTick(void)
{
    if (fireStepsRemaining > 0)
    {
        FIRE_STEP_PIN_STEP;
        CyDelayUs(50);
        FIRE_STEP_PIN_RESET;
        fireStepsRemaining--;
    }
    else if (fireInProgress && fireStepPhase == 0)
    {
        // Skift til returbevægelse
        startStepperTimerWithPeriod(FIRE_TIMER_PERIOD_BACKWARD);
        FIRE_DIR_PIN_BACKWARD;
        fireStepPhase = 1;
        fireStepsRemaining = FIRE_MAX_STEPS_BACKWARD;
    }
    else if (fireInProgress && fireStepPhase == 1)
    {
        // Sekvens er færdig
        fireInProgress = 0;
    }
}

// Initialiser output pins
void initFiringPins(void)
{
    fireStepPin_Write(0);
    fireDirPin_Write(0);
}

// Bruges af kontrol-logik til at spørge om affyring er færdig
uint8 firingIsIdle(void)
{
    return (fireStepsRemaining == 0 && fireInProgress == 0) ? 1 : 0;
}

