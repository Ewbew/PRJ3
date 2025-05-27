#include "firing.h"
#include "stepper.h"



// Motorens interne tilstande
volatile int16 fireStepsRemaining = 0;
volatile int8 fireDirection = 1;
volatile uint8 fireStepPhase = 0;
volatile uint8 fireInProgress = 0;

//Start affyringssekvens
void fireMechanism(void)
{
    fireStepPhase = 0;
    fireDirection = 1;
    fireInProgress = 1;

    FIRE_DIR_PIN_FORWARD;
    fireStepsRemaining = FIRE_MAX_STEPS_FORWARD;

    Timer_1_Stop();
    Timer_1_WritePeriod(TIMER_PERIOD_FORWARD);
    Timer_1_WriteCounter(0);
    Timer_1_Start();
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
        Timer_Stepper_Stop();
        Timer_Stepper_WritePeriod(TIMER_PERIOD_BACKWARD);
        Timer_Stepper_WriteCounter(0);
        Timer_Stepper_Start();
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

void initFiringPins(void)
{
    fireStepPin_Write(0);
    fireDirPin_Write(0);
}
