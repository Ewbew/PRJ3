#include "project.h"
#include "stepper.h"
#include "firing.h"
#include "control.h"

int main(void)
{
    CyGlobalIntEnable;

    // Initialiser hardware for motorer og affyring
    initStepperPins();
    initFiringPins();
    initControlTimer();

    // Testsekvens
    for (;;)
    {
        setStepperTargets(0, 0);         // 
        CyDelay(500);

        setStepperTargets(50, 50);      //
        CyDelay(500);

        setStepperTargets(0, 0);      //
        CyDelay(500);

        setStepperTargets(50, 50);      //
        CyDelay(1500);
        
        setStepperTargets(25, 25);      // 
        CyDelay(1500);

        fireMechanism();                 // Kør affyringssekvens (frem og tilbage)
        CyDelay(3000);
    }
}
