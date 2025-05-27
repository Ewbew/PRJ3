#include "project.h"
#include "stepper.h"

int main(void)
{
    CyGlobalIntEnable;

    StepPin_Write(0);
    DirPin_Write(0);

    Timer_1_Start();
    Timer_1_Stop();
    isr_timer_StartEx(Timer_ISR_Handler);

    for (;;)
    {
        GoToPosition(0);
        CyDelay(3000);
        
        GoToPosition(99);
        CyDelay(4000);

        GoToPosition(-99);
        CyDelay(4000);

        GoToPosition(99);
        CyDelay(500);

        GoToPosition(-99);
        CyDelay(500);

        GoToPosition(0);
        CyDelay(2000);
    }
}
