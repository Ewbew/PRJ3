#include "distanceSensor.h"
#include <stdio.h>
#define MACH    343.4    /* Mach 1.0 at 20.0 */

static volatile uint16_t duration = 0 ;
static volatile int     echo_flag = 0 ;
static volatile int     timerFlag = 0; // Flag to indicate if the timer has triggered
static int              obstruct = 0; // 1 if distance is below the threshold, 0 otherwise
char str[128] ; // print buffer

CY_ISR(ISR_DS_echo)
{
    isr_echo_int_ClearPending() ;
    isr_echo_int_Disable() ;
    duration = Counter_ReadCounter() ;
    echo_flag = 1 ;
}

int get_obstruct(void)
{
    return obstruct;
}

void set_obstruct(int value)
{
    obstruct = value;
}

CY_ISR(ISR_timer_DS_tc_handler)
{
    isr_timer_DS_ClearPending(); // Clear the interrupt flag
    set_timerFlag(1); // Set the timer flag to indicate the timer has triggere
    }


int get_timerFlag(void)
{
    //char debugStr[50];
    
    return timerFlag;
}

void set_timerFlag(int value)
{
    timerFlag = value;
}

void init_DS_hardware(void)
    /* Enable global interrupts. */{
    CyGlobalIntEnable;
    
    // Hardware init for the the trigger/pulse functionality
    Trigger_Write(0);
    Clock_24MHz_Start();
    isr_echo_int_ClearPending();
    isr_echo_int_StartEx(ISR_DS_echo);
    Counter_Init(); // Initialize the counter
    Counter_Start(); // Start the counter
    UART_PC_PutString("Counter initialised\r\n");
    
    // Hardware init for Timer (that drives the periodic obstacle check)
    Clock_timer_DS_Start(); // Start the clock
    Timer_DS_Start(); // Start the timer UNCOMMENT THIS WHEN THE PERIODIC DISTANCE CHECK SHOULD BE USED
    isr_timer_DS_ClearPending(), // Clear any pending interrupts
    isr_timer_DS_StartEx(ISR_timer_DS_tc_handler); // Attach the ISR to the timer interrupt (which is connected  
                                        // to the TC output pin).
    UART_PC_PutString("Timer initialized.\r\n");
}

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
}

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