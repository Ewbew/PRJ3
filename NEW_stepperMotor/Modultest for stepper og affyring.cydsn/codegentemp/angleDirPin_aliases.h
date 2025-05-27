/*******************************************************************************
* File Name: angleDirPin.h  
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

#if !defined(CY_PINS_angleDirPin_ALIASES_H) /* Pins angleDirPin_ALIASES_H */
#define CY_PINS_angleDirPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define angleDirPin_0			(angleDirPin__0__PC)
#define angleDirPin_0_INTR	((uint16)((uint16)0x0001u << angleDirPin__0__SHIFT))

#define angleDirPin_INTR_ALL	 ((uint16)(angleDirPin_0_INTR))

#endif /* End Pins angleDirPin_ALIASES_H */


/* [] END OF FILE */
