/*******************************************************************************
* File Name: dial_isr_timer.h
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
#if !defined(CY_ISR_dial_isr_timer_H)
#define CY_ISR_dial_isr_timer_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void dial_isr_timer_Start(void);
void dial_isr_timer_StartEx(cyisraddress address);
void dial_isr_timer_Stop(void);

CY_ISR_PROTO(dial_isr_timer_Interrupt);

void dial_isr_timer_SetVector(cyisraddress address);
cyisraddress dial_isr_timer_GetVector(void);

void dial_isr_timer_SetPriority(uint8 priority);
uint8 dial_isr_timer_GetPriority(void);

void dial_isr_timer_Enable(void);
uint8 dial_isr_timer_GetState(void);
void dial_isr_timer_Disable(void);

void dial_isr_timer_SetPending(void);
void dial_isr_timer_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the dial_isr_timer ISR. */
#define dial_isr_timer_INTC_VECTOR            ((reg32 *) dial_isr_timer__INTC_VECT)

/* Address of the dial_isr_timer ISR priority. */
#define dial_isr_timer_INTC_PRIOR             ((reg8 *) dial_isr_timer__INTC_PRIOR_REG)

/* Priority of the dial_isr_timer interrupt. */
#define dial_isr_timer_INTC_PRIOR_NUMBER      dial_isr_timer__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable dial_isr_timer interrupt. */
#define dial_isr_timer_INTC_SET_EN            ((reg32 *) dial_isr_timer__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the dial_isr_timer interrupt. */
#define dial_isr_timer_INTC_CLR_EN            ((reg32 *) dial_isr_timer__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the dial_isr_timer interrupt state to pending. */
#define dial_isr_timer_INTC_SET_PD            ((reg32 *) dial_isr_timer__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the dial_isr_timer interrupt. */
#define dial_isr_timer_INTC_CLR_PD            ((reg32 *) dial_isr_timer__INTC_CLR_PD_REG)


#endif /* CY_ISR_dial_isr_timer_H */


/* [] END OF FILE */
