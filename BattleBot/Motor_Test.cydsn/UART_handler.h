#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include "project.h"  // Include your PSoC project header
#include "motor_control.h"

#include <project.h>
#include "shootVarHandler.h"

void uartHandler_init(shootVarHandler* handler);  // Declare init function
// Prototype for the UART RX interrupt service routine for both UART to PC and to Bluetooth
CY_ISR_PROTO(ISR_UART_rx_handler_PC);
CY_ISR_PROTO(ISR_UART_rx_handler_BT);

// Function to handle received bytes
// This function will be called from the ISR for the PC to process the received byte
void handleByteReceived(uint8_t byteReceived);

#endif /* UART_HANDLER_H */