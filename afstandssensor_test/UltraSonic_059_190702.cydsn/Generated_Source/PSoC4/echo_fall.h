/*******************************************************************************
* File Name: echo_fall.h
* Version 1.70
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
#if !defined(CY_ISR_echo_fall_H)
#define CY_ISR_echo_fall_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void echo_fall_Start(void);
void echo_fall_StartEx(cyisraddress address);
void echo_fall_Stop(void);

CY_ISR_PROTO(echo_fall_Interrupt);

void echo_fall_SetVector(cyisraddress address);
cyisraddress echo_fall_GetVector(void);

void echo_fall_SetPriority(uint8 priority);
uint8 echo_fall_GetPriority(void);

void echo_fall_Enable(void);
uint8 echo_fall_GetState(void);
void echo_fall_Disable(void);

void echo_fall_SetPending(void);
void echo_fall_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the echo_fall ISR. */
#define echo_fall_INTC_VECTOR            ((reg32 *) echo_fall__INTC_VECT)

/* Address of the echo_fall ISR priority. */
#define echo_fall_INTC_PRIOR             ((reg32 *) echo_fall__INTC_PRIOR_REG)

/* Priority of the echo_fall interrupt. */
#define echo_fall_INTC_PRIOR_NUMBER      echo_fall__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable echo_fall interrupt. */
#define echo_fall_INTC_SET_EN            ((reg32 *) echo_fall__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the echo_fall interrupt. */
#define echo_fall_INTC_CLR_EN            ((reg32 *) echo_fall__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the echo_fall interrupt state to pending. */
#define echo_fall_INTC_SET_PD            ((reg32 *) echo_fall__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the echo_fall interrupt. */
#define echo_fall_INTC_CLR_PD            ((reg32 *) echo_fall__INTC_CLR_PD_REG)



#endif /* CY_ISR_echo_fall_H */


/* [] END OF FILE */
