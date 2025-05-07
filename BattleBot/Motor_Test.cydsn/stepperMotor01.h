#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "project.h"  // Required for PSoC-specific functions like CyDelayUs

// Constants (optional to expose)
#define MAX_POSITION 100
#define MIN_POSITION -100
#define STEPS_PER_REVOLUTION 200

// Function declarations
void StepMotor(int steps, int direction);
void GoToPosition(int targetPosition);

#endif // STEPPERMOTOR_H
