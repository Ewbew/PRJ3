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

    // Start the UART RX ISR and UART component
    uartHandler_init(&shootVarObject);
    isr_uart_rx_PC_StartEx(ISR_UART_rx_handler_PC);
    isr_uart_rx_BT_StartEx(ISR_UART_rx_handler_BT);
    UART_PC_Start();
    UART_BT_Start();
    PWM_A_Start();
    PWM_B_Start();
    UART_PC_PutString("Starting program...\r\n");

    splash(); // Print splash message for distance sensor

    for (;;)
    {
        // Measure distance
        double distance = measure_distance();

        if (distance >= 0)
        {
            char str[50];
            // sprintf(str, "Distance: %.2f cm\r\n", distance);
            //UART_PC_PutString(str);
        }
        else
        {
            //UART_PC_PutString("Timeout\r\n");
        }

        // Wait 500 ms before the next reading
        CyDelay(500);
    }
}

/* Old code, removed while debugging
int main(void)
{
    CyGlobalIntEnable;  // Enable global interrupts. 
    shootVarHandler shootVarObject;
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

    for(;;)
    {
        shootVarHandler_getDesiredPos1();
        
        // Place your application code here.
    }
}

*/