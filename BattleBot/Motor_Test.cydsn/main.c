#include "project.h"
#include <stdio.h>
#include "motor_control.h"
#include "UART_handler.h"
#include "stepper.h"
#include "firing.h"
#include "control.h"
#include "distanceSensor.h" // Include the distance sensor module

#define obstacle_distance_threshold 30.0

int main(void)
{
    CyGlobalIntEnable;  /* Enable global interrupts. */
    splash(); // Print splash message for distance sensor

    // Initialize the timer for periodic distance checks
    // Initialiser hardware for motorer og affyring
    initStepperPins();
    initFiringPins();
    initControlTimer();

    // Start the UART RX ISR and UART component
    // TO-DO: Make the functions below into hardware start for comm and motor
    // TO-DO: Start the main by setting the speed variables to 0 (using the set_speedX() functions)
    // isr_uart_rx_PC_StartEx(ISR_UART_rx_handler_PC); // Removed while debugging – for some reason, 
                                                        // an AT command was sent to the BT module
   
    isr_uart_rx_BT_StartEx(ISR_UART_rx_handler_BT);
    UART_PC_Start();
    UART_BT_Start();
    PWM_A_Start();
    PWM_B_Start();
        // Initialize hardware for distance sensor
    init_DS_hardware(); // UNCOMMENT WHEN DONE DEBUGGING
    UART_PC_PutString("Starting program...\r\n");
    // Optionally initialize motor enable signals if needed:
    // A_ENABLE_Write(0);
    // B_ENABLE_Write(0);

    // Print flag value
    char flagStr[50];
    snprintf(flagStr, sizeof(flagStr), "Flag value: %d\r\n", get_timerFlag());
    UART_PC_PutString(flagStr); // Print the flag value to the UART

    splash(); // Print splash message for distance sensor

    for (;;)
    {
        if (get_timerFlag()) { // Check if the timer has triggered
            set_timerFlag(0); // Reset the timer flag
    
            double distance = measure_distance(); // Measure the distance

            int distance_print = (int)distance;
            char distanceStr[50];
            snprintf(distanceStr, sizeof(distanceStr), "Distance: %d cm\r\n", distance_print);
            UART_PC_PutString(distanceStr); // Print the distance to the UART
            CyDelay(10);
            

            // Check if the distance is below the threshold
            if (distance >= 0 && distance < obstacle_distance_threshold) { // Example threshold: 30 cm
                set_obstruct(1); // Set obstruct to true
                UART_PC_PutString("Obstacle detected\r\n");
                set_speedA(-30); // Set left motor speed
                set_speedB(30);  // Set right motor speed
            } else {
                set_obstruct(0); // Set obstruct to false
                 // Debugging message
                UART_PC_PutString("No obstacle detected\r\n");
            }
        }
    
        // Other tasks can be performed here
    }
}
