#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include "project.h"

// Define the speed of sound in air (Mach 1.0 at 20°C)
#define MACH 343.4

CY_ISR_PROTO(ISR_DS_echo); // ISR for echo signal
CY_ISR_PROTO(ISR_timer_DS_tc_handler); // ISR for timer

// Function prototypes
/**
 * @brief Initializes the hardware components required for the distance sensor.
 */
void init_DS_hardware(void);

/**
 * @brief Initializes the timer for periodic distance checks.
 */
void init_timer(void);

/**
 * @brief Sends a 10 µs trigger pulse to the ultrasonic sensor.
 */
void pulse_trigger(void);

/**
 * @brief Measures the distance using the ultrasonic sensor.
 * 
 * @return double The measured distance in centimeters, or -1 if a timeout occurred.
 */
double measure_distance(void);

/**
 * @brief Gets the current value of the obstruct variable.
 * 
 * @return int The value of the obstruct variable (1 for true, 0 for false).
 */
int get_obstruct(void);

/**
 * @brief Sets the value of the obstruct variable.
 * 
 * @param value The new value for the obstruct variable (1 for true, 0 for false).
 */
void set_obstruct(int value);

/**
 * @brief Gets the current value of the timer flag.
 * 
 * @return int The value of the timer flag (1 for true, 0 for false).
 */
int get_timerFlag(void);

/**
 * @brief Sets the value of the timer flag.
 * 
 * @param value The new value for the timer flag (1 for true, 0 for false).
 */
void set_timerFlag(int value);

/**
 * @brief Prints the calculated distance based on the echo duration.
 * 
 * @param duration The duration of the echo signal in timer ticks.
 */
void print_value(uint32_t duration);

/**
 * @brief Prints a splash message with the build date and time.
 */
void splash(void);

#endif /* DISTANCE_SENSOR_H */