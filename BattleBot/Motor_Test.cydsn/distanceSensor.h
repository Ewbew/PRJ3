#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include "project.h"

// Define the speed of sound in air (Mach 1.0 at 20°C)
#define MACH 343.4

// Function prototypes
void init_hardware(void);
void pulse_trigger(void);
double measure_distance(void);
void print_value(uint32_t duration);
void splash(void);

#endif /* DISTANCE_SENSOR_H */