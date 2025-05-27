#include "control.h"
#include "stepper.h"
#include "firing.h"

// Timer ISR – ét step ad gangen
CY_ISR(Stepper_Timer_ISR_Handler)
{
    Timer_1_ReadStatusRegister();

    // Dial
    if (dialStepsRemaining > 0)
    {
        dialStepPin_Write(1);
        CyDelayUs(50);
        dialStepPin_Write(0);
        dialStepsRemaining--;
        dialCurrentPosition += dialDirection;
    }

    // Angle
    if (angleStepsRemaining > 0)
    {
        angleStepPin_Write(1);
        CyDelayUs(50);
        angleStepPin_Write(0);
        angleStepsRemaining--;
        angleCurrentPosition += angleDirection;
    }

    // Fire
   firingStepperTick();

    // Stop timer hvis alt er færdigt
    if (dialStepsRemaining == 0 && angleStepsRemaining == 0 && fireStepsRemaining == 0 && !fireInProgress)
    {
        
        Timer_1_Stop();
    }
}

void initControlTimer(void)
{
    Timer_1_Start();
    Timer_1_Stop();
    stepper_isr_timer_StartEx(Stepper_Timer_ISR_Handler);
}
