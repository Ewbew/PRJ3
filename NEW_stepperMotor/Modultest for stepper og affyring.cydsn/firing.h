#ifndef FIRING_H
#define FIRING_H

#include <project.h>
#include <stdint.h>

#define FIRE_MAX_STEPS_FORWARD 70
#define FIRE_MAX_STEPS_BACKWARD 50
#define TIMER_PERIOD_FORWARD 25
#define TIMER_PERIOD_BACKWARD 25

#define FIRE_STEP_PIN_STEP    fireStepPin_Write(1)
#define FIRE_STEP_PIN_RESET   fireStepPin_Write(0)
#define FIRE_DIR_PIN_FORWARD  fireDirPin_Write(1)
#define FIRE_DIR_PIN_BACKWARD fireDirPin_Write(0)

extern volatile int16 fireStepsRemaining;
extern volatile int8 fireDirection;
extern volatile uint8 fireStepPhase;
extern volatile uint8 fireInProgress;

void fireMechanism(void);
void firingStepperTick(void);
void initFiringPins(void);

#endif // FIRING_H
