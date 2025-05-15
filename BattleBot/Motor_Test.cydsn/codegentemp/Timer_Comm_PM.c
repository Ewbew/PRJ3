/*******************************************************************************
* File Name: Timer_Comm_PM.c
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

#include "Timer_Comm.h"

static Timer_Comm_backupStruct Timer_Comm_backup;


/*******************************************************************************
* Function Name: Timer_Comm_SaveConfig
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
*  Timer_Comm_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Comm_SaveConfig(void) 
{
    #if (!Timer_Comm_UsingFixedFunction)
        Timer_Comm_backup.TimerUdb = Timer_Comm_ReadCounter();
        Timer_Comm_backup.InterruptMaskValue = Timer_Comm_STATUS_MASK;
        #if (Timer_Comm_UsingHWCaptureCounter)
            Timer_Comm_backup.TimerCaptureCounter = Timer_Comm_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Comm_UDB_CONTROL_REG_REMOVED)
            Timer_Comm_backup.TimerControlRegister = Timer_Comm_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Comm_RestoreConfig
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
*  Timer_Comm_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Comm_RestoreConfig(void) 
{   
    #if (!Timer_Comm_UsingFixedFunction)

        Timer_Comm_WriteCounter(Timer_Comm_backup.TimerUdb);
        Timer_Comm_STATUS_MASK =Timer_Comm_backup.InterruptMaskValue;
        #if (Timer_Comm_UsingHWCaptureCounter)
            Timer_Comm_SetCaptureCount(Timer_Comm_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Comm_UDB_CONTROL_REG_REMOVED)
            Timer_Comm_WriteControlRegister(Timer_Comm_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Comm_Sleep
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
*  Timer_Comm_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Comm_Sleep(void) 
{
    #if(!Timer_Comm_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Comm_CTRL_ENABLE == (Timer_Comm_CONTROL & Timer_Comm_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Comm_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Comm_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Comm_Stop();
    Timer_Comm_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Comm_Wakeup
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
*  Timer_Comm_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Comm_Wakeup(void) 
{
    Timer_Comm_RestoreConfig();
    #if(!Timer_Comm_UDB_CONTROL_REG_REMOVED)
        if(Timer_Comm_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Comm_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
