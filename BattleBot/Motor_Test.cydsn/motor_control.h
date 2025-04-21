#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "project.h"  // Include your PSoC project header

// Define PWM limit.
#define PWM_MAX_DUTY 50 // Maximum absolute PWM-value from controller

// Function prototypes for motor control
void set_speedA(int8_t speedA_);
void set_speedB(int8_t speedB_);
void set_directionA(int8_t speedA_);
void set_directionB(int8_t speedB_);
void stop(void);

#endif /* MOTOR_CONTROL_H */

