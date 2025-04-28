/*******************************************************************************
* File Name: Timer_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Timer.h"

static Timer_backupStruct Timer_backup;


/*******************************************************************************
* Function Name: Timer_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_SaveConfig(void) 
{

    #if(!Timer_UsingFixedFunction)
        #if(!Timer_PWMModeIsCenterAligned)
            Timer_backup.PWMPeriod = Timer_ReadPeriod();
        #endif /* (!Timer_PWMModeIsCenterAligned) */
        Timer_backup.PWMUdb = Timer_ReadCounter();
        #if (Timer_UseStatus)
            Timer_backup.InterruptMaskValue = Timer_STATUS_MASK;
        #endif /* (Timer_UseStatus) */

        #if(Timer_DeadBandMode == Timer__B_PWM__DBM_256_CLOCKS || \
            Timer_DeadBandMode == Timer__B_PWM__DBM_2_4_CLOCKS)
            Timer_backup.PWMdeadBandValue = Timer_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Timer_KillModeMinTime)
             Timer_backup.PWMKillCounterPeriod = Timer_ReadKillTime();
        #endif /* (Timer_KillModeMinTime) */

        #if(Timer_UseControl)
            Timer_backup.PWMControlRegister = Timer_ReadControlRegister();
        #endif /* (Timer_UseControl) */
    #endif  /* (!Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_RestoreConfig(void) 
{
        #if(!Timer_UsingFixedFunction)
            #if(!Timer_PWMModeIsCenterAligned)
                Timer_WritePeriod(Timer_backup.PWMPeriod);
            #endif /* (!Timer_PWMModeIsCenterAligned) */

            Timer_WriteCounter(Timer_backup.PWMUdb);

            #if (Timer_UseStatus)
                Timer_STATUS_MASK = Timer_backup.InterruptMaskValue;
            #endif /* (Timer_UseStatus) */

            #if(Timer_DeadBandMode == Timer__B_PWM__DBM_256_CLOCKS || \
                Timer_DeadBandMode == Timer__B_PWM__DBM_2_4_CLOCKS)
                Timer_WriteDeadTime(Timer_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Timer_KillModeMinTime)
                Timer_WriteKillTime(Timer_backup.PWMKillCounterPeriod);
            #endif /* (Timer_KillModeMinTime) */

            #if(Timer_UseControl)
                Timer_WriteControlRegister(Timer_backup.PWMControlRegister);
            #endif /* (Timer_UseControl) */
        #endif  /* (!Timer_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Timer_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Timer_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Sleep(void) 
{
    #if(Timer_UseControl)
        if(Timer_CTRL_ENABLE == (Timer_CONTROL & Timer_CTRL_ENABLE))
        {
            /*Component is enabled */
            Timer_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Timer_backup.PWMEnableState = 0u;
        }
    #endif /* (Timer_UseControl) */

    /* Stop component */
    Timer_Stop();

    /* Save registers configuration */
    Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Timer_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Wakeup(void) 
{
     /* Restore registers values */
    Timer_RestoreConfig();

    if(Timer_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Timer_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
