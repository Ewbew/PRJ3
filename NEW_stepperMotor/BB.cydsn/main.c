#include "project.h"
#include <stdlib.h>  // for abs()

//Dette kode skulle meget gerne virke. Bruger Timer interrupt til at styre alle steppermotorer, hvilket gør, at de alle sammen kan opdateres live med nye kommandoer.

// === Makroer til kontrol af A4988 stepperdriverens signaler ===
// Makroer for dial-motoren
#define DIAL_STEP_PIN_STEP    dialStepPin_Write(1)
#define DIAL_STEP_PIN_RESET   dialStepPin_Write(0)
#define DIAL_DIR_PIN_FORWARD  dialDirPin_Write(1)
#define DIAL_DIR_PIN_BACKWARD dialDirPin_Write(0)

// Makroer for angle-motoren
#define ANGLE_STEP_PIN_STEP    angleStepPin_Write(1)
#define ANGLE_STEP_PIN_RESET   angleStepPin_Write(0)
#define ANGLE_DIR_PIN_FORWARD  angleDirPin_Write(1)
#define ANGLE_DIR_PIN_BACKWARD angleDirPin_Write(0)

// Makroer for affyringsmotoren
#define FIRE_STEP_PIN_STEP    fireStepPin_Write(1)
#define FIRE_STEP_PIN_RESET   fireStepPin_Write(0)
#define FIRE_DIR_PIN_FORWARD  fireDirPin_Write(1)
#define FIRE_DIR_PIN_BACKWARD fireDirPin_Write(0)

// === Konfiguration ===
#define DIAL_MAX_POSITION 100               // Maksimalt logisk mål for dial-motoren
#define DIAL_MIN_POSITION -100              // Minimum logisk mål for dial-motoren
#define ANGLE_MAX_POSITION 50               // Maksimalt logisk mål for angle-motoren
#define ANGLE_MIN_POSITION 0               // Minimum logisk mål for angle-motoren
#define FIRE_MAX_STEPS 70                  // Antal steps affyringsmotoren skal tage pr. aktivering
#define TIMER_PERIOD 25                    // Fælles periodetid for alle steppermotorer

// === Globale variabler for dial motor ===
volatile int8 dialCurrentPosition = 0;     // Nuværende logiske position
volatile int8 dialTargetPosition = 0;      // Ønsket logisk målposition
volatile int16 dialStepsRemaining = 0;     // Steps tilbage til målet
volatile int8 dialDirection = 1;           // 1 = frem, -1 = tilbage

// === Globale variabler for angle motor ===
volatile int8 angleCurrentPosition = 0;    // Nuværende logiske position
volatile int8 angleTargetPosition = 0;     // Ønsket logisk målposition
volatile int16 angleStepsRemaining = 0;    // Steps tilbage til målet
volatile int8 angleDirection = 1;          // 1 = frem, -1 = tilbage

// === Globale variabler for affyringsmekanisme ===
volatile int16 fireStepsRemaining = 0;     // Steps tilbage i nuværende bevægelse
volatile int8 fireDirection = 1;           // 1 = frem, -1 = tilbage
volatile uint8 fireStepPhase = 0;          // 0 = fremad, 1 = retur
volatile uint8 fireInProgress = 0;         // Flag: kører affyringssekvens?

// === TIMER ISR: kaldes hver gang Timer_1 udløber ===
// Håndterer alle tre motorers step-pulser
CY_ISR(Stepper_Timer_ISR_Handler)
{
    Timer_1_ReadStatusRegister(); // Ryd interrupt-flag ved at læse status

    // --- Dial motor ---
    if (dialStepsRemaining > 0)
    {
        DIAL_STEP_PIN_STEP;
        CyDelayUs(50); // kort puls
        DIAL_STEP_PIN_RESET;
        dialStepsRemaining--;
        dialCurrentPosition += dialDirection;
    }

    // --- Angle motor ---
    if (angleStepsRemaining > 0)
    {
        ANGLE_STEP_PIN_STEP;
        CyDelayUs(50);
        ANGLE_STEP_PIN_RESET;
        angleStepsRemaining--;
        angleCurrentPosition += angleDirection;
    }

    // --- Affyringsmotor ---
    if (fireStepsRemaining > 0)
    {
        FIRE_STEP_PIN_STEP;
        CyDelayUs(50);
        FIRE_STEP_PIN_RESET;
        fireStepsRemaining--;
    }
    else if (fireInProgress && fireStepPhase == 0)
    {
        // Skift til retur når første fase (frem) er færdig
        fireStepPhase = 1;
        fireDirection = -1;
        FIRE_DIR_PIN_BACKWARD;
        fireStepsRemaining = FIRE_MAX_STEPS;
    }
    else if (fireInProgress && fireStepPhase == 1)
    {
        // Hele affyringssekvensen er færdig (frem + retur)
        fireInProgress = 0;
    }

    // --- Stop timeren hvis INGEN motorer er aktive ---
    if (dialStepsRemaining == 0 && angleStepsRemaining == 0 && fireStepsRemaining == 0 && !fireInProgress)
    {
        Timer_1_Stop();
    }
}

// === Funktion: styrer dial og angle motorer ===
// Input: ønsket dial- og angle-position
void setStepperTargets(int8 dialTarget, int8 angleTarget)
{
    // --- Dial ---
    if (dialTarget > DIAL_MAX_POSITION) dialTarget = DIAL_MAX_POSITION;
    if (dialTarget < DIAL_MIN_POSITION) dialTarget = DIAL_MIN_POSITION;
    int16 dialDelta = dialTarget - dialCurrentPosition;
    dialDirection = (dialDelta > 0) ? 1 : -1;
    dialStepsRemaining = abs(dialDelta);
    dialTargetPosition = dialTarget;
    if (dialDirection > 0) DIAL_DIR_PIN_FORWARD; else DIAL_DIR_PIN_BACKWARD;

    // --- Angle ---
    if (angleTarget > ANGLE_MAX_POSITION) angleTarget = ANGLE_MAX_POSITION;
    if (angleTarget < ANGLE_MIN_POSITION) angleTarget = ANGLE_MIN_POSITION;
    int16 angleDelta = angleTarget - angleCurrentPosition;
    angleDirection = (angleDelta > 0) ? 1 : -1;
    angleStepsRemaining = abs(angleDelta);
    angleTargetPosition = angleTarget;
    if (angleDirection > 0) ANGLE_DIR_PIN_FORWARD; else ANGLE_DIR_PIN_BACKWARD;

    // --- Start timer hvis noget skal bevæge sig ---
    if (dialStepsRemaining > 0 || angleStepsRemaining > 0)
    {
        Timer_1_Stop();
        Timer_1_WritePeriod(TIMER_PERIOD);
        Timer_1_WriteCounter(0);
        Timer_1_Start();
    }
}

// === Funktion: aktiver affyringsmekanismen (frem og tilbage) ===
// Kalder du denne, starter en komplet sekvens
void fireMechanism(void)
{
    fireStepPhase = 0;             // Start med fremad
    fireDirection = 1;
    fireInProgress = 1;            // Flag: aktiv sekvens
    FIRE_DIR_PIN_FORWARD;
    fireStepsRemaining = FIRE_MAX_STEPS;

    Timer_1_Stop();
    Timer_1_WritePeriod(TIMER_PERIOD);
    Timer_1_WriteCounter(0);
    Timer_1_Start();
}

// === Main-program: testsekvens ===
int main(void)
{
    CyGlobalIntEnable; // Aktiver globale interrupts

    // Initier alle STEP/DIR pins lav
    dialStepPin_Write(0);
    dialDirPin_Write(0);
    angleStepPin_Write(0);
    angleDirPin_Write(0);
    fireStepPin_Write(0);
    fireDirPin_Write(0);

    // Start timeren og registrer interrupt handler
    Timer_1_Start();
    Timer_1_Stop();
    stepper_isr_timer_StartEx(Stepper_Timer_ISR_Handler);

    // === Testsekvens ===
    for (;;)
    {
        setStepperTargets(0, 0);           // Midterposition
        CyDelay(500);

        setStepperTargets(100, 50);        // Øvre positioner
        CyDelay(500);

        setStepperTargets(-100, 0);        // Nedre positioner
        CyDelay(500);

        setStepperTargets(100, 55);        // Vrid + løft
        CyDelay(1500);

        fireMechanism();                   // Affyr (frem og tilbage)
        CyDelay(3000);
    }
}
