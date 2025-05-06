#ifndef CONTROL_H
#define CONTROL_H

#include <project.h>

void initControlTimer(void);
CY_ISR_PROTO(Stepper_Timer_ISR_Handler);

#endif // CONTROL_H
