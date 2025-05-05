/*******************************************************************************
* File Name: Timer_DS_PM.c
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

#include "Timer_DS.h"

static Timer_DS_backupStruct Timer_DS_backup;


/*******************************************************************************
* Function Name: Timer_DS_SaveConfig
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
*  Timer_DS_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_DS_SaveConfig(void) 
{
    #if (!Timer_DS_UsingFixedFunction)
        Timer_DS_backup.TimerUdb = Timer_DS_ReadCounter();
        Timer_DS_backup.InterruptMaskValue = Timer_DS_STATUS_MASK;
        #if (Timer_DS_UsingHWCaptureCounter)
            Timer_DS_backup.TimerCaptureCounter = Timer_DS_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_DS_UDB_CONTROL_REG_REMOVED)
            Timer_DS_backup.TimerControlRegister = Timer_DS_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_DS_RestoreConfig
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
*  Timer_DS_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_DS_RestoreConfig(void) 
{   
    #if (!Timer_DS_UsingFixedFunction)

        Timer_DS_WriteCounter(Timer_DS_backup.TimerUdb);
        Timer_DS_STATUS_MASK =Timer_DS_backup.InterruptMaskValue;
        #if (Timer_DS_UsingHWCaptureCounter)
            Timer_DS_SetCaptureCount(Timer_DS_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_DS_UDB_CONTROL_REG_REMOVED)
            Timer_DS_WriteControlRegister(Timer_DS_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_DS_Sleep
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
*  Timer_DS_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_DS_Sleep(void) 
{
    #if(!Timer_DS_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_DS_CTRL_ENABLE == (Timer_DS_CONTROL & Timer_DS_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_DS_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_DS_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_DS_Stop();
    Timer_DS_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_DS_Wakeup
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
*  Timer_DS_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_DS_Wakeup(void) 
{
    Timer_DS_RestoreConfig();
    #if(!Timer_DS_UDB_CONTROL_REG_REMOVED)
        if(Timer_DS_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_DS_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
