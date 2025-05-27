#include "stepper.h"
#include <stdlib.h>

// === Makroer til kontrol af A4988 stepperdriverens signaler ===
#define STEP_PIN_STEP    StepPin_Write(1)     // Sæt STEP-pin høj
#define STEP_PIN_RESET   StepPin_Write(0)     // Sæt STEP-pin lav
#define DIR_PIN_FORWARD  DirPin_Write(1)      // Sæt DIR-pin høj (fremad)
#define DIR_PIN_BACKWARD DirPin_Write(0)      // Sæt DIR-pin lav (baglæns)

// === Konfiguration ===
#define MAX_POSITION 100                      // Maksimal logisk position
#define MIN_POSITION -100                     // Minimal logisk position
#define STEPS_PER_REVOLUTION 200              // Fysiske step per fuld rotation (1.8° pr step)
#define DEFAULT_TIMER_PERIOD 200              // Timerens periode (bestemmer hastighed)

// === Globale variabler til styring af motorens tilstand ===
volatile int currentPosition = 0;             // Nuvaerende logiske position
volatile int targetPosition = 0;              // Oensket logisk slutposition
volatile int stepsRemaining = 0;              // Antal fysiske step tilbage i bevægelsen
volatile int direction = 1;                   // Retning: 1 = frem, -1 = tilbage

// === Interrupt Service Routine kaldet af Timer_1 ved terminal count ===
CY_ISR(Timer_ISR_Handler)
{
    Timer_1_ReadStatusRegister(); // Ryd interrupt-flag

    if (stepsRemaining <= 0)
    {
        Timer_1_Stop();           // Stop timeren naar vi er faerdige
        currentPosition = targetPosition; // Opdater position, saa vi er "synkroniseret"
        return;
    }

    // Send ét STEP-signal (kort puls)
    STEP_PIN_STEP;
    CyDelayUs(100);              // Hold puls i 100 mikrosekunder
    STEP_PIN_RESET;

    stepsRemaining--;            // En step er udført
}

// === Starter en ny bevægelse til en ønsket logisk position ===
void GoToPosition(int newTarget)
{
    // Begræns målpositionen til inden for gyldigt område
    if (newTarget > MAX_POSITION)
        newTarget = MAX_POSITION;
    if (newTarget < MIN_POSITION)
        newTarget = MIN_POSITION;

    // Udregn antal steps der skal til for at nå målet
    int stepsToTarget = newTarget - currentPosition;

    if (stepsToTarget == 0)
        return; // Allerede ved målet

    // Bestem retning og antal steps der skal køres
    direction = (stepsToTarget > 0) ? 1 : 0;
    stepsRemaining = abs(stepsToTarget); // 1 logisk enhed = 1 step

    targetPosition = newTarget; // Gem ønsket målposition

    // Sæt DIR-pin afhængigt af retning
    if (direction > 0)
        DIR_PIN_FORWARD;
    else
        DIR_PIN_BACKWARD;

    // Klargør og start timeren til at udløse step-pulser
    Timer_1_Stop();
    Timer_1_WritePeriod(DEFAULT_TIMER_PERIOD); // Lavere værdi = hurtigere bevægelse
    Timer_1_WriteCounter(0);
    Timer_1_Start();
}
