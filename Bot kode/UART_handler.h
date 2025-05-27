/**
 * @file UART_handler.h
 * @brief UART communication handler for BattleBot project.
 *
 * Provides interrupt service routines and utility functions for handling UART communication
 * with both the PC and Bluetooth modules, as well as a communication timeout watchdog.
 */
#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include "project.h"  /**< Include your PSoC project header */
#include "motor_control.h"
#include <project.h>

/**
 * @brief UART RX interrupt service routine for the PC UART interface.
 *
 * Handles incoming bytes from the PC for debugging and control purposes.
 */
CY_ISR_PROTO(ISR_UART_rx_handler_PC);

/**
 * @brief UART RX interrupt service routine for the Bluetooth UART interface.
 *
 * Handles incoming bytes from the Bluetooth module and processes control messages.
 */
CY_ISR_PROTO(ISR_UART_rx_handler_BT);

/**
 * @brief Communication timeout timer interrupt service routine.
 *
 * Called periodically to check if a valid message has been received within the timeout period.
 * Stops the motors if no message was received.
 */
CY_ISR_PROTO(ISR_comm_timeout_tc_handler);

/**
 * @brief Handles a received byte from the PC UART interface.
 *
 * This function is called from the PC UART ISR to process received commands or data.
 * @param byteReceived The received byte to process.
 */
void handleByteReceived(uint8_t byteReceived);

/**
 * @brief Initializes the communication timeout timer and attaches its ISR.
 *
 * Starts the timer and sets up the interrupt for the communication watchdog.
 */
void init_comm_timer(void);

#endif /* UART_HANDLER_H */