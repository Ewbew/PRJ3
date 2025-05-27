/**
 * @file firing.h
 * @brief Control and interface for the firing mechanism (stepper-based) in BattleBot.
 *
 * This header provides macros and function declarations for controlling the firing stepper motor,
 * including initialization, firing sequence, and status queries.
 */
#ifndef FIRING_H
#define FIRING_H

#include <project.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @name Pin control macros
 * Macros for controlling the firing stepper motor pins.
 */
///@{
#define FIRE_STEP_PIN_STEP    fireStepPin_Write(1)   /**< Set step pin HIGH (perform a step) */
#define FIRE_STEP_PIN_RESET   fireStepPin_Write(0)   /**< Set step pin LOW (reset after step) */
#define FIRE_DIR_PIN_FORWARD  fireDirPin_Write(1)    /**< Set direction pin to forward */
#define FIRE_DIR_PIN_BACKWARD fireDirPin_Write(0)    /**< Set direction pin to backward */
///@}

/**
 * @name Timing parameters
 * Macros for controlling the number of steps and timer periods for the firing sequence.
 */
///@{
#define FIRE_MAX_STEPS_FORWARD 50      /**< Number of steps for forward firing motion */
#define FIRE_TIMER_PERIOD_FORWARD 80   /**< Timer period for forward motion (us or timer ticks) */
#define FIRE_MAX_STEPS_BACKWARD 30     /**< Number of steps for backward return motion */
#define FIRE_TIMER_PERIOD_BACKWARD 25  /**< Timer period for backward motion (us or timer ticks) */
///@}

/**
 * @brief Initiates the firing sequence for the firing mechanism.
 *
 * This function starts the forward motion of the firing stepper motor.
 */
void fireMechanism(void);

/**
 * @brief Handles a single tick of the firing stepper motor sequence.
 *
 * This function should be called periodically (e.g., from a timer ISR) to advance the firing sequence.
 */
void firingStepperTick(void);

/**
 * @brief Checks if the firing mechanism is idle (not firing or returning).
 *
 * @return uint8 1 if the firing mechanism is idle, 0 otherwise.
 */
uint8 firingIsIdle(void);

/**
 * @brief Initializes the output pins for the firing stepper motor.
 *
 * This function sets the step and direction pins to their default states.
 */
void initFiringPins(void);

#endif // FIRING_H
