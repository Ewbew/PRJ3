#ifndef STEPPER_H
#define STEPPER_H

#include <project.h>

void GoToPosition(int newTarget);
CY_ISR_PROTO(Timer_ISR_Handler);

extern volatile int currentPosition;
extern volatile int targetPosition;

#endif
