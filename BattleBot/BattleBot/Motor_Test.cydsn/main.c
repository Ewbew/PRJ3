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
#include "project.h"

// Declaration of global variables
#define PWM_MAX_DUTY 100 // Maksimal Duty cycle
#define PWM_MIN_DUTY 0   // Minimum Duty cycle

// Initialisering af funktioner
CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);
// void decreaseSpeed(void);
// void increaseSpeed(void);
void driveForwards(void);
void driveBackwards(void);
void stop(void);



int main(void)
{
    CyGlobalIntEnable;                        /* Enable global interrupts. */
    isr_uart_rx_StartEx(ISR_UART_rx_handler); // Start af Interrupt Service Routine for UART_Rx
    UART_Start();                           // Initialisering af UART_1
    // A_ENABLE_Write(0);
    // B_ENABLE_Write(0);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_ReadRxData();
        UART_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

void handleByteReceived(uint8_t byteReceived)
{
       switch(byteReceived) // Switch statements til UART kommunikation med keyboard knapper.
    {
        case '1' :
        {
            driveForwards();
        }
        break;
        case '2' :
        {
            driveBackwards();
        }
        break;
        case '0' :
        {
            stop();
            
        }
        break;
        default :
        {
            // nothing
        }
        break;
    }
}

void driveForwards()
{
    // Sætter koerselsretning til fremad
    UART_PutString("Set direction: Forwards\r\n");
    IN1_Write(0);
    IN2_Write(1);
    IN3_Write(0);
    IN4_Write(1);
}

void driveBackwards()
{
    // Sætter koerselsretning til baglaens
    UART_PutString("Set direction: Backwards\r\n");
    IN1_Write(1);
    IN2_Write(0);
    IN3_Write(1);
    IN4_Write(0);
    
}

void stop() {
    // Sætter alle LOGIC_Inputs til 1 for at stoppe/bremse.
    UART_PutString("Stop \r\n");
    IN1_Write(1);
    IN2_Write(1);
    IN3_Write(1);
    IN4_Write(1);
    
}

/* [] END OF FILE */
