/**
 * @file stepper.h
 * @brief Stepper motor control interface for BattleBot project.
 *
 * Provides macros, global variables, and function declarations for controlling
 * the dial and angle stepper motors, including initialization, target setting,
 * and status queries.
 */
#ifndef STEPPER_H
#define STEPPER_H

#include <project.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @name Stepper position limits
 * Macros for the allowed range of dial and angle stepper positions.
 */
///@{
#define DIAL_MAX_POSITION 100   /**< Maximum position for the dial stepper motor */
#define DIAL_MIN_POSITION -100  /**< Minimum position for the dial stepper motor */
#define ANGLE_MAX_POSITION 50   /**< Maximum position for the angle stepper motor */
#define ANGLE_MIN_POSITION 0    /**< Minimum position for the angle stepper motor */
///@}

/**
 * @brief Timer period for stepper motor control (in timer ticks or microseconds).
 */
#define STEPPER_TIMER_PERIOD 50

/**
 * @name Global stepper state variables
 * Extern declarations for current position, steps remaining, and direction for both motors.
 */
///@{
extern volatile int8 dialCurrentPosition;    /**< Current position of the dial stepper motor */
extern volatile int8 dialStepsRemaining;     /**< Steps remaining for the dial stepper motor */
extern volatile int8 dialDirection;          /**< Direction of the dial stepper motor (1 or -1) */

extern volatile int8 angleCurrentPosition;   /**< Current position of the angle stepper motor */
extern volatile int8 angleStepsRemaining;    /**< Steps remaining for the angle stepper motor */
extern volatile int8 angleDirection;         /**< Direction of the angle stepper motor (1 or -1) */
///@}

/**
 * @brief Sets the target positions for the dial and angle stepper motors.
 *
 * @param dialTarget Target position for the dial stepper motor.
 * @param angleTarget Target position for the angle stepper motor.
 */
void setStepperTargets(int8 dialTarget, int8 angleTarget);

/**
 * @brief Initializes the output pins for the stepper motors.
 *
 * This function sets the step and direction pins to their default states.
 */
void initStepperPins(void);

/**
 * @brief Handles a single tick for both stepper motors.
 *
 * This function should be called periodically (e.g., from a timer ISR) to advance the motors.
 */
void stepperTick(void);

/**
 * @brief Checks if both stepper motors are idle (no steps remaining).
 *
 * @return uint8 1 if both motors are idle, 0 otherwise.
 */
uint8 stepperIsIdle(void);

#endif // STEPPER_H
