#include "project.h"
#include <stdio.h>
#include "motor_control.h"
#include "UART_handler.h"
#include "shootVarHandler.h"
#include "stepperMotor.h"
#include "distanceSensor.h" // Include the distance sensor module

int main(void)
{
    CyGlobalIntEnable;  /* Enable global interrupts. */
    shootVarHandler shootVarObject;

    // Initialize hardware for distance sensor
    init_hardware();

    // Initialize the timer for periodic distance checks
    init_timer();

    // Start the UART RX ISR and UART component
    uartHandler_init(&shootVarObject);
    isr_uart_rx_PC_StartEx(ISR_UART_rx_handler_PC);
    isr_uart_rx_BT_StartEx(ISR_UART_rx_handler_BT);
    UART_PC_Start();
    UART_BT_Start();
    PWM_A_Start();
    PWM_B_Start();
    UART_PC_PutString("Starting program...\r\n");
    // Optionally initialize motor enable signals if needed:
    // A_ENABLE_Write(0);
    // B_ENABLE_Write(0);

    splash(); // Print splash message for distance sensor

    for (;;)
    {
        // Main loop can perform other tasks
        if (get_obstruct()) {
            UART_PC_PutString("Obstacle detected!\r\n");
        } else {
            UART_PC_PutString("No obstacle.\r\n");
        }

        CyDelay(500); // Delay for demonstration purposes
    }
}
