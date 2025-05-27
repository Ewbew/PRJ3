#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include "project.h"

/**
 * @def MACH
 * @brief Speed of sound in air at 20°C (m/s)
 */
#define MACH 343.4

/**
 * @brief ISR prototype for the echo signal from the ultrasonic sensor.
 */
CY_ISR_PROTO(ISR_DS_echo);

/**
 * @brief ISR prototype for the periodic timer interrupt for distance measurement.
 */
CY_ISR_PROTO(ISR_timer_DS_tc_handler);

/**
 * @brief Initializes the hardware components required for the distance sensor.
 *
 * This function enables global interrupts, initializes the trigger pin, clocks, counter,
 * and sets up the ISRs for echo and periodic timer interrupts.
 */
void init_DS_hardware(void);

/**
 * @brief Sends a 10 µs trigger pulse to the ultrasonic sensor and enables echo capture.
 *
 * This function resets the counter, enables the echo interrupt, and generates a 10 µs pulse
 * on the trigger pin to start a distance measurement.
 */
void pulse_trigger(void);

/**
 * @brief Measures the distance using the ultrasonic sensor.
 *
 * This function triggers the sensor, waits for the echo or a timeout, and calculates the distance
 * in centimeters. If the echo is not received within the timeout, it returns -1.
 *
 * @return double The measured distance in centimeters, or -1 if a timeout occurred.
 */
double measure_distance(void);

/**
 * @brief Gets the current value of the obstruction flag.
 *
 * @return int 1 if an obstruction is detected, 0 otherwise.
 */
int get_obstruct(void);

/**
 * @brief Sets the value of the obstruction flag.
 *
 * @param value 1 to indicate obstruction, 0 otherwise.
 */
void set_obstruct(int value);

/**
 * @brief Gets the current value of the timer flag.
 *
 * @return int 1 if the timer has triggered, 0 otherwise.
 */
int get_timerFlag(void);

/**
 * @brief Sets the value of the timer flag.
 *
 * @param value 1 to indicate the timer has triggered, 0 otherwise.
 */
void set_timerFlag(int value);

#endif /* DISTANCE_SENSOR_H */