#ifndef STEPPER_H
#define STEPPER_H

#include <project.h>
#include <stdint.h>
#include <stdbool.h>

#define DIAL_MAX_POSITION 100
#define DIAL_MIN_POSITION -100
#define ANGLE_MAX_POSITION 50
#define ANGLE_MIN_POSITION 0

#define STEPPER_TIMER_PERIOD 50

// Variabler
extern volatile int8 dialCurrentPosition;
extern volatile int8 dialStepsRemaining;
extern volatile int8 dialDirection;

extern volatile int8 angleCurrentPosition;
extern volatile int8 angleStepsRemaining;
extern volatile int8 angleDirection;

// Funktioner
void setStepperTargets(int8 dialTarget, int8 angleTarget);
void initStepperPins(void);
void stepperTick(void);
uint8 stepperIsIdle(void);

#endif // STEPPER_H
