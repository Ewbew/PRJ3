/**
 * @file motor_control.h
 * @brief Motor control interface for BattleBot project.
 *
 * Provides functions and macros for controlling the speed and direction of two DC motors
 * using PWM signals. Includes initialization and emergency stop functionality.
 */
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "project.h"  /**< Include your PSoC project header */

/**
 * @def PWM_MAX_DUTY
 * @brief Maximum absolute PWM-value from controller (range for speed input).
 */
#define PWM_MAX_DUTY 50

/**
 * @brief Sets the speed and direction of Motor A.
 *
 * @param speedA_ Signed 8-bit value for speed and direction. Positive for forward, negative for backward.
 */
void set_speedA(int8_t speedA_);

/**
 * @brief Sets the speed and direction of Motor B.
 *
 * @param speedB_ Signed 8-bit value for speed and direction. Positive for forward, negative for backward.
 */
void set_speedB(int8_t speedB_);

#endif /* MOTOR_CONTROL_H */

