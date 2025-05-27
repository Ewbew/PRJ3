#include "motor_control.h"
#include <stdlib.h>
#include <stdio.h>

// Stops the motors by setting all direction pins to logic high
void stop(void)
{
    UART_PC_PutString("Stop \r\n");
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