#include "firing.h"
#include "stepper.h"

#define FIRE_STEP_PIN_STEP    fireStepPin_Write(1)
#define FIRE_STEP_PIN_RESET   fireStepPin_Write(0)
#define FIRE_DIR_PIN_FORWARD  fireDirPin_Write(1)
#define FIRE_DIR_PIN_BACKWARD fireDirPin_Write(0)

// Motorens interne tilstande
volatile int16 fireStepsRemaining = 0;
volatile int8 fireDirection = 1;
volatile uint8 fireStepPhase = 0;
volatile uint8 fireInProgress = 0;

void fireMechanism(void)
{
    fireStepPhase = 0;
    fireDirection = 1;
    fireInProgress = 1;

    FIRE_DIR_PIN_FORWARD;
    fireStepsRemaining = FIRE_MAX_STEPS;

    Timer_1_Stop();
    Timer_1_WritePeriod(TIMER_PERIOD);
    Timer_1_WriteCounter(0);
    Timer_1_Start();
}

void initFiringPins(void)
{
    fireStepPin_Write(0);
    fireDirPin_Write(0);
}
