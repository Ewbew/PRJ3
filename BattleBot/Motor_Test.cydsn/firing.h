#ifndef FIRING_H
#define FIRING_H

#include <project.h>
#include <stdint.h>

#define FIRE_MAX_STEPS 100

extern volatile int16 fireStepsRemaining;
extern volatile int8 fireDirection;
extern volatile uint8 fireStepPhase;
extern volatile uint8 fireInProgress;

void fireMechanism(void);
void initFiringPins(void);

#endif // FIRING_H
