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
    init_DS_hardware();

    // Initialize the timer for periodic distance checks
    //init_timer(); Commented out while debugging

    // Start the UART RX ISR and UART component
    uartHandler_init(&shootVarObject);
    isr_uart_rx_PC_StartEx(ISR_UART_rx_handler_PC);
    isr_uart_rx_BT_StartEx(ISR_UART_rx_handler_BT);
    UART_PC_Start();
    UART_BT_Start();
    PWM_A_Start();
    PWM_B_Start();
    Timer_DS_Start();
    UART_PC_PutString("Starting program...\r\n");
    // Optionally initialize motor enable signals if needed:
    // A_ENABLE_Write(0);
    // B_ENABLE_Write(0);

    splash(); // Print splash message for distance sensor

    for (;;)
    {
        if (get_timerFlag()) { // Check if the timer has triggered
            set_timerFlag(0); // Reset the timer flag
            UART_PC_PutString("Timer triggered - measuring distance...\r\n");
    
            double distance = measure_distance(); // Measure the distance
            char distanceStr[50];
            snprintf(distanceStr, sizeof(distanceStr), "Distance: %.2f cm\r\n", distance);
            UART_PC_PutString(distanceStr); // Print the distance to the UART
            

            // Check if the distance is below the threshold
            if (distance >= 0 && distance < 30.0) { // Example threshold: 30 cm
                set_obstruct(1); // Set obstruct to true
                UART_PC_PutString("Obstacle detected\r\n");
            } else {
                set_obstruct(0); // Set obstruct to false
                UART_PC_PutString("No obstacle detected\r\n");
            }
        }
    
        // Other tasks can be performed here
    }
}
