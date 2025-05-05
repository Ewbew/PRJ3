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
static volatile int     echo_flag = 0 ;
static volatile int     timerFlag = 0; // Flag to indicate if the timer has triggered
static int              obstruct = 0; // 1 if distance is below the threshold, 0 otherwise


char str[128] ; /* print buffer */

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
    /*
    char debugStr[50];
    snprintf(debugStr, sizeof(debugStr), "Timer triggered: %d\r\n", timerFlag);
    UART_PC_PutString(debugStr); // Print the timer flag value to the UART
    */
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

/* Old ISR code for timer – commented out, since we are using a flag
   to trigger the distance measurement in the main loop
   instead of using a timer interrupt directly.
CY_ISR(ISR_timer_DS_tc_handler)
{
    isr_timer_DS_ClearPending(); // Clear the interrupt flag

    
    double distance = measure_distance(); // Measure the distance

    // Check if the distance is below the threshold
    if (distance >= 0 && distance < 30.0) { // Example threshold: 30 cm
        set_obstruct(1); // Set obstruct to true
        UART_PC_PutString("Obstacle detected\r\n");
    } else {
        set_obstruct(0); // Set obstruct to false
        UART_PC_PutString("No obstacle detected\r\n");
    }
    
}
*/


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
    Clock_5kHz_Start(); // Start the clock
    Timer_DS_Start(); // Start the timer
    isr_timer_DS_ClearPending(), // Clear any pending interrupts
    isr_timer_DS_StartEx(ISR_timer_DS_tc_handler); // Attach the ISR to the timer interrupt (which is connected  
                                        // to the TC output pin).
    UART_PC_PutString("Timer initialized.\r\n");
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

    //char debugStr[50];
    //sprintf(debugStr, "Counter value: %u\r\n", Counter_ReadCounter());
    //UART_PC_PutString(debugStr);
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

        // Debug print for calculated distance
        //char str[50];
        //sprintf(str, "Calculated Distance: %d cm\r\n", (int)distance);
        //UART_PC_PutString(str);
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