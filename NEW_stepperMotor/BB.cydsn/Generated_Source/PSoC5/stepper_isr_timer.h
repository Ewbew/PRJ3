/*******************************************************************************
* File Name: stepper_isr_timer.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_stepper_isr_timer_H)
#define CY_ISR_stepper_isr_timer_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void stepper_isr_timer_Start(void);
void stepper_isr_timer_StartEx(cyisraddress address);
void stepper_isr_timer_Stop(void);

CY_ISR_PROTO(stepper_isr_timer_Interrupt);

void stepper_isr_timer_SetVector(cyisraddress address);
cyisraddress stepper_isr_timer_GetVector(void);

void stepper_isr_timer_SetPriority(uint8 priority);
uint8 stepper_isr_timer_GetPriority(void);

void stepper_isr_timer_Enable(void);
uint8 stepper_isr_timer_GetState(void);
void stepper_isr_timer_Disable(void);

void stepper_isr_timer_SetPending(void);
void stepper_isr_timer_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the stepper_isr_timer ISR. */
#define stepper_isr_timer_INTC_VECTOR            ((reg32 *) stepper_isr_timer__INTC_VECT)

/* Address of the stepper_isr_timer ISR priority. */
#define stepper_isr_timer_INTC_PRIOR             ((reg8 *) stepper_isr_timer__INTC_PRIOR_REG)

/* Priority of the stepper_isr_timer interrupt. */
#define stepper_isr_timer_INTC_PRIOR_NUMBER      stepper_isr_timer__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable stepper_isr_timer interrupt. */
#define stepper_isr_timer_INTC_SET_EN            ((reg32 *) stepper_isr_timer__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the stepper_isr_timer interrupt. */
#define stepper_isr_timer_INTC_CLR_EN            ((reg32 *) stepper_isr_timer__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the stepper_isr_timer interrupt state to pending. */
#define stepper_isr_timer_INTC_SET_PD            ((reg32 *) stepper_isr_timer__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the stepper_isr_timer interrupt. */
#define stepper_isr_timer_INTC_CLR_PD            ((reg32 *) stepper_isr_timer__INTC_CLR_PD_REG)


#endif /* CY_ISR_stepper_isr_timer_H */


/* [] END OF FILE */
