#include "project.h"
#include "motor_control.h"

int main(void)
{
    CyGlobalIntEnable;  /* Enable global interrupts. */

    // Start the UART RX ISR, PWM and UART component
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    isr_uart_rx_BT_StartEx(ISR_UART_rx_handler_BT);
    UART_Start();
    UART_BT_Start();
    PWM_A_Start();
    PWM_B_Start();
    UART_PutString("Starting program...\r\n");

    for(;;)
    {
        // Place your application code here.
    }
}
