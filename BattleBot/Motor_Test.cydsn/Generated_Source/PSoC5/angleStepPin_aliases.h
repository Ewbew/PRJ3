/*******************************************************************************
* File Name: angleStepPin.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_angleStepPin_ALIASES_H) /* Pins angleStepPin_ALIASES_H */
#define CY_PINS_angleStepPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define angleStepPin_0			(angleStepPin__0__PC)
#define angleStepPin_0_INTR	((uint16)((uint16)0x0001u << angleStepPin__0__SHIFT))

#define angleStepPin_INTR_ALL	 ((uint16)(angleStepPin_0_INTR))

#endif /* End Pins angleStepPin_ALIASES_H */


/* [] END OF FILE */
