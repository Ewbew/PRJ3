/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "project.h"  // Include your PSoC project header

// Define PWM limit.
#define PWM_MAX_DUTY 50 // Maximum absolute PWM-value from controller

// Prototype for the UART RX interrupt service routine
CY_ISR_PROTO(ISR_UART_rx_handler);
CY_ISR_PROTO(ISR_UART_rx_handler_BT);

// Function prototypes for motor control based on UART commands
void handleByteReceived(uint8_t byteReceived);
void set_speedA(int8_t speedA_);
void set_speedB(int8_t speedB_);
void set_directionA(int8_t speedA_);
void set_directionB(int8_t speedB_);
void stop(void);

#endif /* MOTOR_CONTROL_H */


/* [] END OF FILE */
