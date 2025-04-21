#include "project.h"
#include "motor_control.h"
#include "UART_handler.h"

int main(void)
{
    CyGlobalIntEnable;  /* Enable global interrupts. */

    // Start the UART RX ISR and UART component
    isr_uart_rx_StartEx(ISR_UART_rx_handler_PC);
    isr_uart_rx_BT_StartEx(ISR_UART_rx_handler_BT);
    UART_Start();
    UART_BT_Start();
    PWM_A_Start();
    PWM_B_Start();
    UART_PutString("Starting program...\r\n");
    // Optionally initialize motor enable signals if needed:
    // A_ENABLE_Write(0);
    // B_ENABLE_Write(0);

    for(;;)
    {
        // Place your application code here.
    }
}
