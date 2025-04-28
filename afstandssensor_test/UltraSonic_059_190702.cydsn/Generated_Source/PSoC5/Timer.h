/*******************************************************************************
* File Name: Timer.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Timer_H)
#define CY_PWM_Timer_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Timer_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Timer_Resolution                     (16u)
#define Timer_UsingFixedFunction             (0u)
#define Timer_DeadBandMode                   (0u)
#define Timer_KillModeMinTime                (0u)
#define Timer_KillMode                       (0u)
#define Timer_PWMMode                        (0u)
#define Timer_PWMModeIsCenterAligned         (0u)
#define Timer_DeadBandUsed                   (0u)
#define Timer_DeadBand2_4                    (0u)

#if !defined(Timer_PWMUDB_genblk8_stsreg__REMOVED)
    #define Timer_UseStatus                  (1u)
#else
    #define Timer_UseStatus                  (0u)
#endif /* !defined(Timer_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Timer_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Timer_UseControl                 (1u)
#else
    #define Timer_UseControl                 (0u)
#endif /* !defined(Timer_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Timer_UseOneCompareMode              (1u)
#define Timer_MinimumKillTime                (1u)
#define Timer_EnableMode                     (0u)

#define Timer_CompareMode1SW                 (0u)
#define Timer_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Timer__B_PWM__DISABLED 0
#define Timer__B_PWM__ASYNCHRONOUS 1
#define Timer__B_PWM__SINGLECYCLE 2
#define Timer__B_PWM__LATCHED 3
#define Timer__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Timer__B_PWM__DBMDISABLED 0
#define Timer__B_PWM__DBM_2_4_CLOCKS 1
#define Timer__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Timer__B_PWM__ONE_OUTPUT 0
#define Timer__B_PWM__TWO_OUTPUTS 1
#define Timer__B_PWM__DUAL_EDGE 2
#define Timer__B_PWM__CENTER_ALIGN 3
#define Timer__B_PWM__DITHER 5
#define Timer__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Timer__B_PWM__LESS_THAN 1
#define Timer__B_PWM__LESS_THAN_OR_EQUAL 2
#define Timer__B_PWM__GREATER_THAN 3
#define Timer__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Timer__B_PWM__EQUAL 0
#define Timer__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Timer_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Timer_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Timer_PWMModeIsCenterAligned) */
        #if (Timer_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Timer_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Timer_DeadBandMode == Timer__B_PWM__DBM_256_CLOCKS || \
            Timer_DeadBandMode == Timer__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Timer_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Timer_KillModeMinTime) */

        /* Backup control register */
        #if(Timer_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Timer_UseControl) */

    #endif /* (!Timer_UsingFixedFunction) */

}Timer_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Timer_Start(void) ;
void    Timer_Stop(void) ;

#if (Timer_UseStatus || Timer_UsingFixedFunction)
    void  Timer_SetInterruptMode(uint8 interruptMode) ;
    uint8 Timer_ReadStatusRegister(void) ;
#endif /* (Timer_UseStatus || Timer_UsingFixedFunction) */

#define Timer_GetInterruptSource() Timer_ReadStatusRegister()

#if (Timer_UseControl)
    uint8 Timer_ReadControlRegister(void) ;
    void  Timer_WriteControlRegister(uint8 control)
          ;
#endif /* (Timer_UseControl) */

#if (Timer_UseOneCompareMode)
   #if (Timer_CompareMode1SW)
       void    Timer_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Timer_CompareMode1SW) */
#else
    #if (Timer_CompareMode1SW)
        void    Timer_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Timer_CompareMode1SW) */
    #if (Timer_CompareMode2SW)
        void    Timer_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Timer_CompareMode2SW) */
#endif /* (Timer_UseOneCompareMode) */

#if (!Timer_UsingFixedFunction)
    uint16   Timer_ReadCounter(void) ;
    uint16 Timer_ReadCapture(void) ;

    #if (Timer_UseStatus)
            void Timer_ClearFIFO(void) ;
    #endif /* (Timer_UseStatus) */

    void    Timer_WriteCounter(uint16 counter)
            ;
#endif /* (!Timer_UsingFixedFunction) */

void    Timer_WritePeriod(uint16 period)
        ;
uint16 Timer_ReadPeriod(void) ;

#if (Timer_UseOneCompareMode)
    void    Timer_WriteCompare(uint16 compare)
            ;
    uint16 Timer_ReadCompare(void) ;
#else
    void    Timer_WriteCompare1(uint16 compare)
            ;
    uint16 Timer_ReadCompare1(void) ;
    void    Timer_WriteCompare2(uint16 compare)
            ;
    uint16 Timer_ReadCompare2(void) ;
#endif /* (Timer_UseOneCompareMode) */


#if (Timer_DeadBandUsed)
    void    Timer_WriteDeadTime(uint8 deadtime) ;
    uint8   Timer_ReadDeadTime(void) ;
#endif /* (Timer_DeadBandUsed) */

#if ( Timer_KillModeMinTime)
    void Timer_WriteKillTime(uint8 killtime) ;
    uint8 Timer_ReadKillTime(void) ;
#endif /* ( Timer_KillModeMinTime) */

void Timer_Init(void) ;
void Timer_Enable(void) ;
void Timer_Sleep(void) ;
void Timer_Wakeup(void) ;
void Timer_SaveConfig(void) ;
void Timer_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Timer_INIT_PERIOD_VALUE          (65535u)
#define Timer_INIT_COMPARE_VALUE1        (65535u)
#define Timer_INIT_COMPARE_VALUE2        (63u)
#define Timer_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Timer_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Timer_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(1u <<  \
                                                    Timer_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Timer_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Timer_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Timer_CTRL_CMPMODE2_SHIFT)
#define Timer_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Timer_CTRL_CMPMODE1_SHIFT)
#define Timer_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Timer_UsingFixedFunction)
   #define Timer_PERIOD_LSB              (*(reg16 *) Timer_PWMHW__PER0)
   #define Timer_PERIOD_LSB_PTR          ( (reg16 *) Timer_PWMHW__PER0)
   #define Timer_COMPARE1_LSB            (*(reg16 *) Timer_PWMHW__CNT_CMP0)
   #define Timer_COMPARE1_LSB_PTR        ( (reg16 *) Timer_PWMHW__CNT_CMP0)
   #define Timer_COMPARE2_LSB            (0x00u)
   #define Timer_COMPARE2_LSB_PTR        (0x00u)
   #define Timer_COUNTER_LSB             (*(reg16 *) Timer_PWMHW__CNT_CMP0)
   #define Timer_COUNTER_LSB_PTR         ( (reg16 *) Timer_PWMHW__CNT_CMP0)
   #define Timer_CAPTURE_LSB             (*(reg16 *) Timer_PWMHW__CAP0)
   #define Timer_CAPTURE_LSB_PTR         ( (reg16 *) Timer_PWMHW__CAP0)
   #define Timer_RT1                     (*(reg8 *)  Timer_PWMHW__RT1)
   #define Timer_RT1_PTR                 ( (reg8 *)  Timer_PWMHW__RT1)

#else
   #if (Timer_Resolution == 8u) /* 8bit - PWM */

       #if(Timer_PWMModeIsCenterAligned)
           #define Timer_PERIOD_LSB      (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Timer_PERIOD_LSB_PTR  ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Timer_PERIOD_LSB      (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Timer_PERIOD_LSB_PTR  ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Timer_PWMModeIsCenterAligned) */

       #define Timer_COMPARE1_LSB        (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Timer_COMPARE1_LSB_PTR    ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Timer_COMPARE2_LSB        (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Timer_COMPARE2_LSB_PTR    ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Timer_COUNTERCAP_LSB      (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Timer_COUNTERCAP_LSB_PTR  ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Timer_COUNTER_LSB         (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Timer_COUNTER_LSB_PTR     ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Timer_CAPTURE_LSB         (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Timer_CAPTURE_LSB_PTR     ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Timer_PWMModeIsCenterAligned)
               #define Timer_PERIOD_LSB      (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Timer_PERIOD_LSB_PTR  ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Timer_PERIOD_LSB      (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Timer_PERIOD_LSB_PTR  ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Timer_PWMModeIsCenterAligned) */

            #define Timer_COMPARE1_LSB       (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Timer_COMPARE1_LSB_PTR   ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Timer_COMPARE2_LSB       (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Timer_COMPARE2_LSB_PTR   ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Timer_COUNTERCAP_LSB     (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Timer_COUNTERCAP_LSB_PTR ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Timer_COUNTER_LSB        (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Timer_COUNTER_LSB_PTR    ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Timer_CAPTURE_LSB        (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Timer_CAPTURE_LSB_PTR    ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Timer_PWMModeIsCenterAligned)
               #define Timer_PERIOD_LSB      (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Timer_PERIOD_LSB_PTR  ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Timer_PERIOD_LSB      (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Timer_PERIOD_LSB_PTR  ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Timer_PWMModeIsCenterAligned) */

            #define Timer_COMPARE1_LSB       (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Timer_COMPARE1_LSB_PTR   ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Timer_COMPARE2_LSB       (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Timer_COMPARE2_LSB_PTR   ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Timer_COUNTERCAP_LSB     (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Timer_COUNTERCAP_LSB_PTR ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Timer_COUNTER_LSB        (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Timer_COUNTER_LSB_PTR    ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Timer_CAPTURE_LSB        (*(reg16 *) Timer_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Timer_CAPTURE_LSB_PTR    ((reg16 *)  Timer_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Timer_AUX_CONTROLDP1          (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Timer_AUX_CONTROLDP1_PTR      ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Timer_Resolution == 8) */

   #define Timer_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Timer_AUX_CONTROLDP0          (*(reg8 *)  Timer_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Timer_AUX_CONTROLDP0_PTR      ((reg8 *)   Timer_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Timer_UsingFixedFunction) */

#if(Timer_KillModeMinTime )
    #define Timer_KILLMODEMINTIME        (*(reg8 *)  Timer_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Timer_KILLMODEMINTIME_PTR    ((reg8 *)   Timer_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Timer_KillModeMinTime ) */

#if(Timer_DeadBandMode == Timer__B_PWM__DBM_256_CLOCKS)
    #define Timer_DEADBAND_COUNT         (*(reg8 *)  Timer_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Timer_DEADBAND_COUNT_PTR     ((reg8 *)   Timer_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Timer_DEADBAND_LSB_PTR       ((reg8 *)   Timer_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Timer_DEADBAND_LSB           (*(reg8 *)  Timer_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Timer_DeadBandMode == Timer__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Timer_UsingFixedFunction)
        #define Timer_DEADBAND_COUNT         (*(reg8 *)  Timer_PWMHW__CFG0)
        #define Timer_DEADBAND_COUNT_PTR     ((reg8 *)   Timer_PWMHW__CFG0)
        #define Timer_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Timer_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Timer_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Timer_DEADBAND_COUNT         (*(reg8 *)  Timer_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Timer_DEADBAND_COUNT_PTR     ((reg8 *)   Timer_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Timer_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Timer_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Timer_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Timer_UsingFixedFunction) */
#endif /* (Timer_DeadBandMode == Timer__B_PWM__DBM_256_CLOCKS) */



#if (Timer_UsingFixedFunction)
    #define Timer_STATUS                 (*(reg8 *) Timer_PWMHW__SR0)
    #define Timer_STATUS_PTR             ((reg8 *) Timer_PWMHW__SR0)
    #define Timer_STATUS_MASK            (*(reg8 *) Timer_PWMHW__SR0)
    #define Timer_STATUS_MASK_PTR        ((reg8 *) Timer_PWMHW__SR0)
    #define Timer_CONTROL                (*(reg8 *) Timer_PWMHW__CFG0)
    #define Timer_CONTROL_PTR            ((reg8 *) Timer_PWMHW__CFG0)
    #define Timer_CONTROL2               (*(reg8 *) Timer_PWMHW__CFG1)
    #define Timer_CONTROL3               (*(reg8 *) Timer_PWMHW__CFG2)
    #define Timer_GLOBAL_ENABLE          (*(reg8 *) Timer_PWMHW__PM_ACT_CFG)
    #define Timer_GLOBAL_ENABLE_PTR      ( (reg8 *) Timer_PWMHW__PM_ACT_CFG)
    #define Timer_GLOBAL_STBY_ENABLE     (*(reg8 *) Timer_PWMHW__PM_STBY_CFG)
    #define Timer_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Timer_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Timer_BLOCK_EN_MASK          (Timer_PWMHW__PM_ACT_MSK)
    #define Timer_BLOCK_STBY_EN_MASK     (Timer_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Timer_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Timer_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Timer_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Timer_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Timer_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Timer_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Timer_CTRL_ENABLE            (uint8)((uint8)0x01u << Timer_CTRL_ENABLE_SHIFT)
    #define Timer_CTRL_RESET             (uint8)((uint8)0x01u << Timer_CTRL_RESET_SHIFT)
    #define Timer_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Timer_CTRL_CMPMODE2_SHIFT)
    #define Timer_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Timer_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Timer_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Timer_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Timer_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Timer_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Timer_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Timer_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Timer_STATUS_TC_INT_EN_MASK_SHIFT            (Timer_STATUS_TC_SHIFT - 4u)
    #define Timer_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Timer_STATUS_CMP1_INT_EN_MASK_SHIFT          (Timer_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Timer_STATUS_TC              (uint8)((uint8)0x01u << Timer_STATUS_TC_SHIFT)
    #define Timer_STATUS_CMP1            (uint8)((uint8)0x01u << Timer_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Timer_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Timer_STATUS_TC >> 4u)
    #define Timer_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Timer_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Timer_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Timer_RT1_MASK              (uint8)((uint8)0x03u << Timer_RT1_SHIFT)
    #define Timer_SYNC                  (uint8)((uint8)0x03u << Timer_RT1_SHIFT)
    #define Timer_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Timer_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Timer_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Timer_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Timer_SYNCDSI_SHIFT)


#else
    #define Timer_STATUS                (*(reg8 *)   Timer_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Timer_STATUS_PTR            ((reg8 *)    Timer_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Timer_STATUS_MASK           (*(reg8 *)   Timer_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Timer_STATUS_MASK_PTR       ((reg8 *)    Timer_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Timer_STATUS_AUX_CTRL       (*(reg8 *)   Timer_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Timer_CONTROL               (*(reg8 *)   Timer_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Timer_CONTROL_PTR           ((reg8 *)    Timer_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Timer_CTRL_ENABLE_SHIFT      (0x07u)
    #define Timer_CTRL_RESET_SHIFT       (0x06u)
    #define Timer_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Timer_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Timer_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Timer_CTRL_ENABLE            (uint8)((uint8)0x01u << Timer_CTRL_ENABLE_SHIFT)
    #define Timer_CTRL_RESET             (uint8)((uint8)0x01u << Timer_CTRL_RESET_SHIFT)
    #define Timer_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Timer_CTRL_CMPMODE2_SHIFT)
    #define Timer_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Timer_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Timer_STATUS_KILL_SHIFT          (0x05u)
    #define Timer_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Timer_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Timer_STATUS_TC_SHIFT            (0x02u)
    #define Timer_STATUS_CMP2_SHIFT          (0x01u)
    #define Timer_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Timer_STATUS_KILL_INT_EN_MASK_SHIFT          (Timer_STATUS_KILL_SHIFT)
    #define Timer_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Timer_STATUS_FIFONEMPTY_SHIFT)
    #define Timer_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Timer_STATUS_FIFOFULL_SHIFT)
    #define Timer_STATUS_TC_INT_EN_MASK_SHIFT            (Timer_STATUS_TC_SHIFT)
    #define Timer_STATUS_CMP2_INT_EN_MASK_SHIFT          (Timer_STATUS_CMP2_SHIFT)
    #define Timer_STATUS_CMP1_INT_EN_MASK_SHIFT          (Timer_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Timer_STATUS_KILL            (uint8)((uint8)0x00u << Timer_STATUS_KILL_SHIFT )
    #define Timer_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Timer_STATUS_FIFOFULL_SHIFT)
    #define Timer_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Timer_STATUS_FIFONEMPTY_SHIFT)
    #define Timer_STATUS_TC              (uint8)((uint8)0x01u << Timer_STATUS_TC_SHIFT)
    #define Timer_STATUS_CMP2            (uint8)((uint8)0x01u << Timer_STATUS_CMP2_SHIFT)
    #define Timer_STATUS_CMP1            (uint8)((uint8)0x01u << Timer_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Timer_STATUS_KILL_INT_EN_MASK            (Timer_STATUS_KILL)
    #define Timer_STATUS_FIFOFULL_INT_EN_MASK        (Timer_STATUS_FIFOFULL)
    #define Timer_STATUS_FIFONEMPTY_INT_EN_MASK      (Timer_STATUS_FIFONEMPTY)
    #define Timer_STATUS_TC_INT_EN_MASK              (Timer_STATUS_TC)
    #define Timer_STATUS_CMP2_INT_EN_MASK            (Timer_STATUS_CMP2)
    #define Timer_STATUS_CMP1_INT_EN_MASK            (Timer_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Timer_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Timer_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Timer_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Timer_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Timer_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Timer_UsingFixedFunction */

#endif  /* CY_PWM_Timer_H */


/* [] END OF FILE */
