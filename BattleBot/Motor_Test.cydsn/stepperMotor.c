#include "project.h"
#include "stepperMotor.h"
#include <stdlib.h>

#define STEP_PIN_STEP    StepPin_Write(1)
#define STEP_PIN_RESET   StepPin_Write(0)
#define DIR_PIN_FORWARD  DirPin_Write(1)
#define DIR_PIN_BACKWARD DirPin_Write(0)

#define MAX_POSITION 100
#define MIN_POSITION -100
#define STEPS_PER_REVOLUTION 200

int currentPosition = 0;

void StepMotor(int steps, int direction)
{
    if (direction > 0)
        DIR_PIN_FORWARD;
    else
        DIR_PIN_BACKWARD;
    
    for (int i = 0; i < steps; i++)
    {
        STEP_PIN_STEP;
        CyDelayUs(1500); // 1500 us HIGH
        STEP_PIN_RESET;
        CyDelayUs(1500); // 1500 us LOW
    }
}

void GoToPosition(int targetPosition)
{
    if (targetPosition > MAX_POSITION)
        targetPosition = MAX_POSITION;
    if (targetPosition < MIN_POSITION)
        targetPosition = MIN_POSITION;
    
    int stepsToMove = (targetPosition - currentPosition);
    
    if (stepsToMove != 0)
    {
        int direction = (stepsToMove > 0) ? 1 : 0;
        StepMotor(abs(stepsToMove), direction);
        currentPosition = targetPosition;
    }
}


