#ifndef CONTROL_H
#define CONTROL_H

#include <project.h>
#include <stdbool.h>  // For bool-type

// Initialiser timer og ISR
void initControlTimer(void);

// Start og stop af timer
void startStepperTimerWithPeriod(uint16_t period);
void stopStepperTimer(void);

// Hjælpefunktion: Er hele systemet inaktivt?
uint8 isControlIdle(void);

// ISR prototype
CY_ISR_PROTO(Stepper_Timer_ISR_Handler);

#endif // CONTROL_H
