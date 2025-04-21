#include "motor_control.h"
#include <stdlib.h>
#include <stdio.h>


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
    static int8_t currentSpeed = 0;
    char command_address[] = "AT+MAC\r\n";
    char command_baud[] = "AT+BAUD\r\n";
    char command_status[] = "AT+STAT\r\n";
    
    switch(byteReceived)
    {
        case '1':
            // Increase speed by 5, ensuring we do not exceed PWM_MAX_DUTY.
            if (currentSpeed < PWM_MAX_DUTY)
            {
                UART_PutString("Increase speed\r\n");
                currentSpeed += 5;
                if (currentSpeed > PWM_MAX_DUTY)
                {
                    currentSpeed = PWM_MAX_DUTY;
                }
                set_speedA(currentSpeed);
                set_speedB(currentSpeed);
                if (currentSpeed == PWM_MAX_DUTY)
                {
                    UART_PutString("Max forward speed reached\r\n");
                }
            }
            else
            {
                UART_PutString("Already at max forward speed\r\n");
            }
            break;
            
        case '2':
            // Decrease speed by 5, ensuring we do not drop below -PWM_MAX_DUTY.
            if (currentSpeed > -PWM_MAX_DUTY)
            {
                UART_PutString("Decrease speed\r\n");
                currentSpeed -= 5;
                if (currentSpeed < -PWM_MAX_DUTY)
                {
                    currentSpeed = -PWM_MAX_DUTY;
                }
                set_speedA(currentSpeed);
                set_speedB(currentSpeed);
                if (currentSpeed == -PWM_MAX_DUTY)
                {
                    UART_PutString("Max reverse speed reached\r\n");
                }
            }
            else
            {
                UART_PutString("Already at max reverse speed\r\n");
            }
            break;
            
        case '0':
            // Stop the motors by setting current speed to 0.
            currentSpeed = 0;
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



CY_ISR(ISR_UART_rx_handler_BT)
{
    static char btBuffer[50];     // Buffer for the incoming string
    static uint8_t index = 0;
    int temp1, temp2;
    int8_t VAR1, VAR2;

    while (UART_BT_GetRxBufferSize() > 0)
    {
        char byteReceived = UART_BT_ReadRxData();

        // Store the byte if we have room
        if (index < sizeof(btBuffer) - 1)
        {
            btBuffer[index++] = byteReceived;
        }

        // Message is considered done if we get \n, \r, or if buffer is full
        if (byteReceived == '\n' || byteReceived == '\r' || index >= 49)
        {
            btBuffer[index] = '\0';  // Null-terminate the string

            UART_PutString("\r\n[BT Response] ");
            UART_PutString(btBuffer);
            UART_PutString("\r\n");

            // Try to parse the format: "-39,45"
            if (sscanf(btBuffer, "%d,%d", &temp1, &temp2) == 2)
            {
                VAR1 = (int8_t)temp1;
                VAR2 = (int8_t)temp2;
                set_speedA(VAR1);
                set_speedB(VAR2);
                
                UART_PutString("SkrrtMoney, loop entered");
            }
            else
            {
                /*
                char msg[50];
                snprintf(msg,sizeof(msg), "VAR 1 is: %d, VAR 2 is: %d\r\n", temp1, temp2);
                */
                UART_PutString(btBuffer);
                UART_PutString("\r\n Parse error :((( \r\n");
                
            }

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

void set_speedA(int8_t var1)
{    
    uint8_t dutyCycle = (uint16_t)((abs(var1) * 255UL) / PWM_MAX_DUTY);

    
    if (var1 >= 0) {
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

void set_speedB(int8_t var2)
{
    uint8_t dutyCycle = (uint16_t)((abs(var2) * 255UL) / PWM_MAX_DUTY);
    
    if (var2 >= 0) {
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
