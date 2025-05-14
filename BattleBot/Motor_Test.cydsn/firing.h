#ifndef FIRING_H
#define FIRING_H

#include <project.h>
#include <stdint.h>
#include <stdbool.h>

// Makroer til pin kontrol
#define FIRE_STEP_PIN_STEP    fireStepPin_Write(1)
#define FIRE_STEP_PIN_RESET   fireStepPin_Write(0)
#define FIRE_DIR_PIN_FORWARD  fireDirPin_Write(1)
#define FIRE_DIR_PIN_BACKWARD fireDirPin_Write(0)

// Timing parametre
#define FIRE_MAX_STEPS_FORWARD 50
#define FIRE_TIMER_PERIOD_FORWARD 80

#define FIRE_MAX_STEPS_BACKWARD 30
#define FIRE_TIMER_PERIOD_BACKWARD 25

// Funktioner
void fireMechanism(void);
void firingStepperTick(void);
uint8 firingIsIdle(void);
void initFiringPins(void);

#endif // FIRING_H
