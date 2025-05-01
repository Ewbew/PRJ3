/* ========================================
 * HC-SR04 test program for CY8CKIT-059
 * For this appliation, VDD must be set to 5V
 * ========================================
*/

#include "distanceSensor.h"
#include <stdio.h>


// Reference
/* https://keisan.casio.jp/exec/system/1231998943 */
#define MACH    343.4    /* Mach 1.0 at 20.0 */
// Tester

static volatile uint16_t duration = 0 ;
static volatile int      echo_flag = 0 ;

char str[128] ; /* print buffer */

CY_ISR(echo_isr)
{
    UART_PC_PutString("Interrupt triggered\r\n");
    isr_echo_int_ClearPending() ;
    isr_echo_int_Disable() ;
    duration = Counter_ReadCounter() ;
    snprintf(str, sizeof(str), "Echo received – duration: %d\r\n", duration) ;
    UART_PC_PutString(str);
    echo_flag = 1 ;
}

void init_hardware(void)
    /* Enable global interrupts. */{
    CYGlobalIntEnable;
    Trigger_Write(0);
    Clock_24MHz_Start();
    isr_echo_int_ClearPending();
    isr_echo_int_StartEx(echo_isr);
    Counter_Init(); // Initialize the counter
    Counter_Start(); // Start the counter
}

/**
 * pulse_trigger
 * Generate 10us high pulse from trigger pin
 */
void pulse_trigger(void)
{
    Counter_Reset_Write(1); // Reset counter
    CyDelayUs(10);
    Counter_Reset_Write(0); // Release reset counter

    isr_echo_int_ClearPending();
    isr_echo_int_Enable();

    Trigger_Write(1);  // Trigger pulse HIGH
    CyDelayUs(10);
    Trigger_Write(0);  // Trigger pulse LOW

    Counter_Enable();

    char debugStr[50];
    sprintf(debugStr, "Counter value: %u\r\n", Counter_ReadCounter());
    UART_PC_PutString(debugStr);
}

/**
 * measure_distance
 * Triggers the ultrasonic sensor, waits for the echo, and calculates the distance.
 * If the echo is not received within the timeout, it returns -1 to indicate a timeout.
 *
 * @return double - The measured distance in centimeters, or -1 if a timeout occurred.
 */
double measure_distance(void)
{
    uint16_t timeout_count = 0;
    double distance = -1.0; // Default to -1 to indicate timeout

    // Trigger the ultrasonic sensor
    pulse_trigger();

    // Wait for the echo or timeout
    while ((echo_flag == 0) && (timeout_count < 1000))
    {
        timeout_count++;
        CyDelay(1); // Wait 1 ms
    }

    if (echo_flag)
    {
        echo_flag = 0; // Reset the flag
        distance = (double)(duration) * MACH / 240000.0; // Calculate distance
    }

    return distance;
}

/**
 * print_value
 * Calculate distance from the duration
 * Since the duration include both way of the trip
 * to get the distance, the real duration is the half 
 * of the duration.
 *
 * distance = duration * MACH(m/s) * 100(cm) / (2 * 12000000(Hz)) ;
 *
 */
void print_value(uint32_t duration)
{
    double distance = 0.0 ;
    
    distance = (double)(duration) * MACH / 240000.0 ;
    sprintf(str, "%d.%02dcm\r\n", (int)distance, (int)(100 * distance)%100) ;
    UART_PC_PutString(str) ;
}

void splash(void)
{
    sprintf(str, "HC-SR04 Test CY8CKIT-059 (%s %s)\r\n", __DATE__, __TIME__) ;
    UART_PC_PutString(str) ;
}


/* Old code, removed while debugging
int main(void)
{
    uint16_t timeout_count = 0 ;
    
    init_hardware() ;
    
    splash() ;


    for(;;) {
        timeout_count = 0 ;
        pulse_trigger() ;

        while((echo_flag == 0)&&(timeout_count < 1000)) { 
            timeout_count++ ;
            CyDelay(1) ;
        }

        if (echo_flag) {
            echo_flag = 0 ;
            print_value(duration) ;
        } else {
                UART_PutString("Timeout\r\n") ;
        }
        CyDelay(1000) ;
    }
}
*/