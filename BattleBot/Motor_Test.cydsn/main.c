#include "project.h"
#include "motor_control.h"
#include "UART_handler.h"
#include "shootVarHandler.h"


int main(void)
{
    CyGlobalIntEnable;  /* Enable global interrupts. */
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
        // Place your application code here.
    }
}
