/**
 * @file control.h
 * @brief Control module for stepper and firing subsystems.
 *
 * This header provides initialization, timer control, and idle state checking
 * for the stepper and firing mechanisms in the BattleBot project.
 */
#ifndef CONTROL_H
#define CONTROL_H

#include <project.h>
#include <stdbool.h>  // For bool-type

/**
 * @brief Initializes the control timer and attaches the ISR.
 *
 * This function starts and immediately stops the stepper timer, then attaches
 * the Stepper_Timer_ISR_Handler interrupt service routine.
 */
void initControlTimer(void);

/**
 * @brief Starts the stepper timer with a new period and resets the counter.
 *
 * @param period The timer period to set (in timer ticks).
 */
void startStepperTimerWithPeriod(uint16_t period);

/**
 * @brief Stops the stepper timer.
 */
void stopStepperTimer(void);

/**
 * @brief Checks if all control subsystems are idle.
 *
 * @return uint8 Returns 1 if both the stepper and firing subsystems are idle, 0 otherwise.
 */
uint8 isControlIdle(void);

/**
 * @brief ISR prototype for the stepper timer interrupt handler.
 *
 * This ISR is called periodically by the stepper timer and handles ticks for
 * both the stepper and firing mechanisms.
 */
CY_ISR_PROTO(Stepper_Timer_ISR_Handler);

#endif // CONTROL_H
