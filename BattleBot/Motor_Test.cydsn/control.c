#include "control.h"
#include "stepper.h"
#include "firing.h"

// === TIMER ISR ===
// Denne interrupt kaldes periodisk af Timer_Stepper.
// Den kalder nu kun én funktion per subsystem, som hver især håndterer deres eget tick.
CY_ISR(Stepper_Timer_ISR_Handler)
{
    Timer_Stepper_ReadStatusRegister();  // Ryd interrupt-flag

    // Håndter et step for dial og angle motorer
    stepperTick();

    // Håndter et step for affyringsmekanisme
    firingStepperTick();

    // Stop timeren hvis alt arbejde er færdigt
    if (isControlIdle())
    {
        stopStepperTimer();
    }
}

// Initialiser timer og tilknyt ISR
void initControlTimer(void)
{
    Timer_Stepper_Start();  // Start én gang for init
    Timer_Stepper_Stop();   // Stop med det samme
    stepper_isr_timer_StartEx(Stepper_Timer_ISR_Handler);
}

// Start timeren med ny periode og nulstil tæller
void startStepperTimerWithPeriod(uint16_t period)
{
    Timer_Stepper_Stop();
    Timer_Stepper_WritePeriod(period);
    Timer_Stepper_WriteCounter(0);
    Timer_Stepper_Start();
}

// Stop timeren
void stopStepperTimer(void)
{
    Timer_Stepper_Stop();
}

// Returnerer 1 hvis alle subsystemer er færdige (idle), ellers 0
uint8 isControlIdle(void)
{
    return (stepperIsIdle() && firingIsIdle()) ? 1 : 0;
}

