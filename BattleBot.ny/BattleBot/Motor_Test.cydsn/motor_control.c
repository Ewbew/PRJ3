/* ========================================
Deprecated code; was the code pre sprint review 2
 * ========================================
*/

#include "motor_control.h"
#include <stdlib.h>


// UART RX interrupt service routine
CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_ReadRxData();
        UART_WriteTxData(byteReceived); // Echo back the received byte

        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

void handleByteReceived(uint8_t byteReceived)
{
    // A static variable to keep track of the current speed.
    // Valid range is from -PWM_MAX_DUTY to PWM_MAX_DUTY.
    static int8_t currentSpeedA = 0;
    static int8_t currentSpeedB = 0;
    char command_address[] = "AT+MAC\r\n";
    char command_baud[] = "AT+BAUD\r\n";
    char command_status[] = "AT+STAT\r\n";
    
    switch(byteReceived)
    {
        case '1':  // Increase forward speed on wheel A
            if (currentSpeedA < PWM_MAX_DUTY)
            {
                UART_PutString("Wheel A: Increase forward speed\r\n");
                currentSpeedA += 5;
                currentSpeedB += 5;
                if (currentSpeedA > PWM_MAX_DUTY)
                    currentSpeedA = PWM_MAX_DUTY;
                set_speedA(currentSpeedA);
                set_speedB(currentSpeedB);
                if (currentSpeedA == PWM_MAX_DUTY)
                    UART_PutString("Wheel A: Max forward speed reached\r\n");
            }
            else
            {
                UART_PutString("Wheel A already at max forward speed\r\n");
            }
            break;
            
        case '2':  // Increase forward speed on wheel B
            if (currentSpeedB < PWM_MAX_DUTY)
            {
                UART_PutString("Wheel B: Increase forward speed\r\n");
                currentSpeedB += 5;
                if (currentSpeedB > PWM_MAX_DUTY)
                    currentSpeedB = PWM_MAX_DUTY;
                set_speedB(currentSpeedB);
                if (currentSpeedB == PWM_MAX_DUTY)
                    UART_PutString("Wheel B: Max forward speed reached\r\n");
            }
            else
            {
                UART_PutString("Wheel B already at max forward speed\r\n");
            }
            break;

        case '3':  // Increase reverse speed on wheel A (make speed more negative)
            if (currentSpeedA > -PWM_MAX_DUTY)
            {
                UART_PutString("Wheel A: Increase reverse speed\r\n");
                currentSpeedA -= 5;
                currentSpeedB -= 5;
                if (currentSpeedA < -PWM_MAX_DUTY)
                    currentSpeedA = -PWM_MAX_DUTY;
                set_speedA(currentSpeedA);
                set_speedB(currentSpeedB);
                if (currentSpeedA == -PWM_MAX_DUTY)
                    UART_PutString("Wheel A: Max reverse speed reached\r\n");
            }
            else
            {
                UART_PutString("Wheel A already at max reverse speed\r\n");
            }
            break;
            
        case '4':  // Increase reverse speed on wheel B (make speed more negative)
            if (currentSpeedB > -PWM_MAX_DUTY)
            {
                UART_PutString("Wheel B: Increase reverse speed\r\n");
                currentSpeedB -= 5;
                if (currentSpeedB < -PWM_MAX_DUTY)
                    currentSpeedB = -PWM_MAX_DUTY;
                set_speedB(currentSpeedB);
                if (currentSpeedB == -PWM_MAX_DUTY)
                    UART_PutString("Wheel B: Max reverse speed reached\r\n");
            }
            else
            {
                UART_PutString("Wheel B already at max reverse speed\r\n");
            }
            break;
        case '0':
            // Stop the motors by setting current speed to 0.
            currentSpeedA = 0;
            currentSpeedB = 0;
            stop();
            break;
        
        case 'a':
           // Sends
            UART_PutString("Sending GetMACAddress command to Bluetooth module\r\n");
            UART_BT_PutString(command_address);
            break;
         
        case 'b':
           // Sends
            UART_PutString("Sending GetBAUDRate command to Bluetooth module\r\n");
            UART_BT_PutString(command_baud);
            break;
            
        case 's':
            UART_PutString("Sending GetStatus command to Bluetooth module\r\n");
            UART_BT_PutString(command_status);
            break;
        
        case 't':
            // Test
            UART_PutString("Testing for response from BT module\r\n");
            UART_BT_PutString("AT+VER\r\n");
            break;
            
        default:
            // Do nothing for unrecognized commands.
            break;
    }
}

/* Old code
// UART RX interrupt service routine for Bluetooth
CY_ISR(ISR_UART_rx_handler_BT)
{
    UART_PutString("\r\nReceived data from Bluetooth: \r\n");
    uint8_t bytesToRead = UART_BT_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_BT_ReadRxData();

        // Forward the received byte to the other UART (e.g., USB UART to PC)
        UART_PutChar(byteReceived);  // Use PutChar for single byte

        bytesToRead--;
    }
    UART_PutString("\r\n");
}
*/


CY_ISR(ISR_UART_rx_handler_BT)
{
    static char btBuffer[50];     // Enough space for typical JDY-23 responses
    static uint8_t index = 0;

    while (UART_BT_GetRxBufferSize() > 0)
    {
        char byteReceived = UART_BT_ReadRxData();

        // Store the byte if we have room
        if (index < sizeof(btBuffer) - 1)
        {
            btBuffer[index++] = byteReceived;
        }

        // Check if message looks done — JDY-23 usually ends with CR or fixed length
        if (byteReceived == '\n' || byteReceived == '\r' || index >= 30)  // adjust if needed
        {
            btBuffer[index] = '\0';  // Null-terminate the string

            UART_PutString("\r\n[BT Response] ");
            UART_PutString(btBuffer);
            UART_PutString("\r\n");

            index = 0; // Reset buffer for next message
        }
    }
}


// Stops the motors by setting all direction pins to logic high
void stop(void)
{
    UART_PutString("Stop \r\n");
     // Motor A: disable PWM and force both pins high.
    PWM_A_WriteCompare1(0);
    PWM_A_WriteCompare2(0);

    // Motor B: disable PWM and force both pins high.
    PWM_B_WriteCompare1(0);
    PWM_B_WriteCompare2(0);
}

void set_speedA(int8_t speedA_)
{    
    uint8_t dutyCycle = (uint16_t)((abs(speedA_) * 255UL) / PWM_MAX_DUTY);

    
    if (speedA_ >= 0) {
        // Output PWM on IN2 to go forward
        PWM_A_WriteCompare1(255 - dutyCycle);
        // Disable PWM output on IN1, IN1 is set high in direction function
        PWM_A_WriteCompare2(255);
    }
    else {
        // Output PWM on IN1 to go backwards
        PWM_A_WriteCompare2(255 - dutyCycle);
        // Disable PWM output on IN2, IN2 is set high in direction function
        PWM_A_WriteCompare1(255);
    }
}

void set_speedB(int8_t speedB_)
{
    uint8_t dutyCycle = (uint16_t)((abs(speedB_) * 255UL) / PWM_MAX_DUTY);
    
    if (speedB_ >= 0) {
        // Output PWM on IN4 to go forward
        PWM_B_WriteCompare1(255 - dutyCycle);
        // Disable PWM output on IN3, IN3 is set high in direction function
        PWM_B_WriteCompare2(255);
    }
    else {
        // Output PWM on IN3 to go backwards
        PWM_B_WriteCompare2(255 - dutyCycle);
        // Disable PWM output on IN4, IN4 is set high in direction function
        PWM_B_WriteCompare1(255);
    }
}

/* [] END OF FILE */
