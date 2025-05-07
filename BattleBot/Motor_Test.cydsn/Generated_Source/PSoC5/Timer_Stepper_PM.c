/*******************************************************************************
* File Name: Timer_Stepper_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Stepper.h"

static Timer_Stepper_backupStruct Timer_Stepper_backup;


/*******************************************************************************
* Function Name: Timer_Stepper_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Stepper_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Stepper_SaveConfig(void) 
{
    #if (!Timer_Stepper_UsingFixedFunction)
        Timer_Stepper_backup.TimerUdb = Timer_Stepper_ReadCounter();
        Timer_Stepper_backup.InterruptMaskValue = Timer_Stepper_STATUS_MASK;
        #if (Timer_Stepper_UsingHWCaptureCounter)
            Timer_Stepper_backup.TimerCaptureCounter = Timer_Stepper_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Stepper_UDB_CONTROL_REG_REMOVED)
            Timer_Stepper_backup.TimerControlRegister = Timer_Stepper_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Stepper_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Stepper_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Stepper_RestoreConfig(void) 
{   
    #if (!Timer_Stepper_UsingFixedFunction)

        Timer_Stepper_WriteCounter(Timer_Stepper_backup.TimerUdb);
        Timer_Stepper_STATUS_MASK =Timer_Stepper_backup.InterruptMaskValue;
        #if (Timer_Stepper_UsingHWCaptureCounter)
            Timer_Stepper_SetCaptureCount(Timer_Stepper_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Stepper_UDB_CONTROL_REG_REMOVED)
            Timer_Stepper_WriteControlRegister(Timer_Stepper_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Stepper_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Stepper_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Stepper_Sleep(void) 
{
    #if(!Timer_Stepper_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Stepper_CTRL_ENABLE == (Timer_Stepper_CONTROL & Timer_Stepper_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Stepper_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Stepper_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Stepper_Stop();
    Timer_Stepper_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Stepper_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Stepper_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Stepper_Wakeup(void) 
{
    Timer_Stepper_RestoreConfig();
    #if(!Timer_Stepper_UDB_CONTROL_REG_REMOVED)
        if(Timer_Stepper_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Stepper_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
