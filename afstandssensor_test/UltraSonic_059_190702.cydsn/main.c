/* ========================================
 * HC-SR04 test program for CY8CKIT-059
 * For this appliation, VDD must be set to 5V
 * ========================================
*/

#include "project.h"
#include <stdio.h>


// Reference
/* https://keisan.casio.jp/exec/system/1231998943 */
#define MACH    343.4    /* Mach 1.0 at 20.0 */
// Tester

volatile uint16_t duration = 0 ;
volatile int      echo_flag = 0 ;

char str[128] ; /* print buffer */

CY_ISR(echo_isr)
{
    isr_echo_int_ClearPending() ;
    isr_echo_int_Disable() ;
    duration = Counter_ReadCounter() ;
    echo_flag = 1 ;
}

void init_hardware(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Trigger_Write(0) ;
    Clock_24MHz_Start() ;
    UART_Start() ;
    isr_echo_int_ClearPending() ;
    isr_echo_int_StartEx(echo_isr) ;
    Counter_Init() ;
}

/**
 * pulse_trigger
 * Generate 10us high pulse from trigger pin
 */
void pulse_trigger(void)
{
    Counter_Reset_Write(1) ; // reset counter
    CyDelayUs(10) ;
    Counter_Reset_Write(0) ; // release reset counter

    isr_echo_int_ClearPending() ;
    isr_echo_int_Enable() ;
    
    Trigger_Write(1) ;  // trigger pulse HIGH
    CyDelayUs(10) ;
    Trigger_Write(0) ; // trigger pulse LOW
    
    Counter_Enable() ;
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
    UART_PutString(str) ;
}

void splash(void)
{
    sprintf(str, "HC-SR04 Test CY8CKIT-059 (%s %s)\r\n", __DATE__, __TIME__) ;
    UART_PutString(str) ;
}

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

/* [] END OF FILE */
