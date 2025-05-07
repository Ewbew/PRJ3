#include "control.h"
#include "stepper.h"
#include "firing.h"

// Timer ISR – ét step ad gangen
CY_ISR(Stepper_Timer_ISR_Handler)
{
    Timer_Stepper_ReadStatusRegister();

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
    if (fireStepsRemaining > 0)
    {
        fireStepPin_Write(1);
        CyDelayUs(50);
        fireStepPin_Write(0);
        fireStepsRemaining--;
    }
    else if (fireInProgress && fireStepPhase == 0)
    {
        fireStepPhase = 1;
        fireDirection = -1;
        fireDirPin_Write(0);
        fireStepsRemaining = FIRE_MAX_STEPS;
    }
    else if (fireInProgress && fireStepPhase == 1)
    {
        fireInProgress = 0;
    }

    // Stop timer hvis alt er færdigt
    if (dialStepsRemaining == 0 && angleStepsRemaining == 0 && fireStepsRemaining == 0 && !fireInProgress)
    {
        Timer_Stepper_Stop();
    }
}

void initControlTimer(void)
{
    Timer_Stepper_Start();
    Timer_Stepper_Stop();
    stepper_isr_timer_StartEx(Stepper_Timer_ISR_Handler);
}
