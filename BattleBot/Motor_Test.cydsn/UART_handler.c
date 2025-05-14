#include "UART_handler.h"
#include "motor_control.h"
#include "firing.h"
#include "stepper.h"
#include "distanceSensor.h"
// #include "shootVarHandler.h" // THis is probably deprecated, since we can just call the functions from
                                // firing.c directly on the variables read from the RPI message

#include <stdio.h>
#include <string.h>

// UART RX interrupt service routine for Bluetooth
CY_ISR(ISR_UART_rx_handler_BT)
{
    static char btBuffer[50];     // Buffer for the incoming string
    static uint8_t index = 0;
    int temp1, temp2, tempBool;
    char tempMode;
    char message[150];
    
    int8_t VAR1, VAR2;

    while (UART_BT_GetRxBufferSize() > 0)
    {
        char byteReceived = UART_BT_ReadRxData();

        // Store the byte if we have room
        if ((index < sizeof(btBuffer) - 1) && byteReceived != 'X')
        {
            btBuffer[index++] = byteReceived;
        }

        // Message is considered done if we get \n, \r, or if buffer is full
        if (byteReceived == 'X' || index >= sizeof(btBuffer) - 1)
        {
            btBuffer[index] = '\0';  // Null-terminate the string
            
            /* Debugging code
            snprintf(message, sizeof(message), "[BT Response] %s\r\n", btBuffer);
            UART_PC_PutString(message);
            */

            // Try to parse the format: <char>,<int>,<int>,<int>
            if (sscanf(btBuffer, "%c,%d,%d,%d", &tempMode, &temp1, &temp2, &tempBool) == 4)
            {
                snprintf(message, sizeof(message), "ACK,%dX", get_obstruct());
                UART_BT_PutString(message);
                int obstruct = get_obstruct();
                char PC_dbg_msg[50];
                snprintf(PC_dbg_msg, sizeof(PC_dbg_msg), "Obstruction is: %d\r\n", obstruct);
                UART_PC_PutString(PC_dbg_msg);

                if (get_obstruct()) {
                    UART_PC_PutString("Speed change ignored due to obstacle\r\n");
                } else if (tempMode == '$') {
                    VAR1 = (int8_t)temp1;
                    VAR2 = (int8_t)temp2;                    
                    set_speedA(VAR1);
                    set_speedB(VAR2);
                    // Debugging code
                    // UART_PC_PutString("Speed successfully set\r\n");
                }
                else if (tempMode == '@') {
                    set_speedA(0);
                    set_speedB(0);
                    VAR1 = (int8_t)temp1;
                    VAR2 = (int8_t)temp2; 
                    setStepperTargets(VAR1, VAR2);
                    if(tempBool) fireMechanism();
                    // Debugging code
                    // UART_PC_PutString("Turret direction and shoot mode successfully set\r\n");
                }
            }
            else if (strncmp(btBuffer, "AT+", 3) == 0)
            {
                // It's a valid AT command or response — not a control command (used for debugging)
                snprintf(message, sizeof(message), "[BT Info] AT Command or response received: %s\r\n", btBuffer);
                UART_PC_PutString(message);
            }
            else
            {       
                UART_PC_PutString("Parsing error - sending NACK to RPI\r\n");
                snprintf(message, sizeof(message), "NACK,%dX", get_obstruct());
                UART_BT_PutString(message);
                char PC_dbg_msg[50];
                snprintf(PC_dbg_msg, sizeof(PC_dbg_msg), "Msg sent to RPI is: %s\r\n", message);
                UART_PC_PutString(PC_dbg_msg);
            }

            index = 0; // Reset buffer for next message
            memset(btBuffer, 0, sizeof(btBuffer));
        }
    }
}




// UART RX interrupt service routine for PC
CY_ISR(ISR_UART_rx_handler_PC)
{
    uint8_t bytesToRead = UART_PC_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_PC_ReadRxData();
        UART_PC_WriteTxData(byteReceived); // Echo back the received byte

        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

void handleByteReceived(uint8_t byteReceived)
{
    // A static variable to keep track of the current speed.
    // Valid range is from -PWM_MAX_DUTY to PWM_MAX_DUTY.
    static int8_t currentSpeed = 0;
    char command_ACK[] = "AT\r\n";
    char command_addr[] = "AT+ADDR?\r\n";
    char command_UART[] = "AT+UART?\r\n";
    
    switch(byteReceived)
    {
        case '1':
            // Increase speed by 5, ensuring we do not exceed PWM_MAX_DUTY.
            if (currentSpeed < PWM_MAX_DUTY)
            {
                UART_PC_PutString("Increase speed\r\n");
                currentSpeed += 5;
                if (currentSpeed > PWM_MAX_DUTY)
                {
                    currentSpeed = PWM_MAX_DUTY;
                }
                set_speedA(currentSpeed);
                set_speedB(currentSpeed);
                if (currentSpeed == PWM_MAX_DUTY)
                {
                    UART_PC_PutString("Max forward speed reached\r\n");
                }
            }
            else
            {
                UART_PC_PutString("Already at max forward speed\r\n");
            }
            break;
            
        case '2':
            // Decrease speed by 5, ensuring we do not drop below -PWM_MAX_DUTY.
            if (currentSpeed > -PWM_MAX_DUTY)
            {
                UART_PC_PutString("Decrease speed\r\n");
                currentSpeed -= 5;
                if (currentSpeed < -PWM_MAX_DUTY)
                {
                    currentSpeed = -PWM_MAX_DUTY;
                }
                set_speedA(currentSpeed);
                set_speedB(currentSpeed);
                if (currentSpeed == -PWM_MAX_DUTY)
                {
                    UART_PC_PutString("Max reverse speed reached\r\n");
                }
            }
            else
            {
                UART_PC_PutString("Already at max reverse speed\r\n");
            }
            break;
            
        case '0':
            // Stop the motors by setting current speed to 0.
            currentSpeed = 0;
            stop();
            break;
        
        case 'a':
           // Asks for the address (IT SHOULD BE 98d3:51:fe6f30)
            UART_PC_PutString("Fetching MAC address of Bluetooth module\r\n");
            UART_BT_PutString(command_addr);
            break;
            
        case 'u':
            UART_PC_PutString("Fecthing UART info from Bluetooth module\r\n");
            UART_BT_PutString(command_UART);
            break;
        
        case 't':
            // Test
            UART_PC_PutString("Testing for response from BT module\r\n");
            UART_BT_PutString(command_ACK);
            break;
            
        default:
            // Do nothing for unrecognized commands.
            break;
    }
}
