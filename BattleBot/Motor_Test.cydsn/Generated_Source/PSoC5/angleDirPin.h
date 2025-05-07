/*******************************************************************************
* File Name: angleDirPin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_angleDirPin_H) /* Pins angleDirPin_H */
#define CY_PINS_angleDirPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "angleDirPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 angleDirPin__PORT == 15 && ((angleDirPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    angleDirPin_Write(uint8 value);
void    angleDirPin_SetDriveMode(uint8 mode);
uint8   angleDirPin_ReadDataReg(void);
uint8   angleDirPin_Read(void);
void    angleDirPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   angleDirPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the angleDirPin_SetDriveMode() function.
     *  @{
     */
        #define angleDirPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define angleDirPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define angleDirPin_DM_RES_UP          PIN_DM_RES_UP
        #define angleDirPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define angleDirPin_DM_OD_LO           PIN_DM_OD_LO
        #define angleDirPin_DM_OD_HI           PIN_DM_OD_HI
        #define angleDirPin_DM_STRONG          PIN_DM_STRONG
        #define angleDirPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define angleDirPin_MASK               angleDirPin__MASK
#define angleDirPin_SHIFT              angleDirPin__SHIFT
#define angleDirPin_WIDTH              1u

/* Interrupt constants */
#if defined(angleDirPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in angleDirPin_SetInterruptMode() function.
     *  @{
     */
        #define angleDirPin_INTR_NONE      (uint16)(0x0000u)
        #define angleDirPin_INTR_RISING    (uint16)(0x0001u)
        #define angleDirPin_INTR_FALLING   (uint16)(0x0002u)
        #define angleDirPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define angleDirPin_INTR_MASK      (0x01u) 
#endif /* (angleDirPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define angleDirPin_PS                     (* (reg8 *) angleDirPin__PS)
/* Data Register */
#define angleDirPin_DR                     (* (reg8 *) angleDirPin__DR)
/* Port Number */
#define angleDirPin_PRT_NUM                (* (reg8 *) angleDirPin__PRT) 
/* Connect to Analog Globals */                                                  
#define angleDirPin_AG                     (* (reg8 *) angleDirPin__AG)                       
/* Analog MUX bux enable */
#define angleDirPin_AMUX                   (* (reg8 *) angleDirPin__AMUX) 
/* Bidirectional Enable */                                                        
#define angleDirPin_BIE                    (* (reg8 *) angleDirPin__BIE)
/* Bit-mask for Aliased Register Access */
#define angleDirPin_BIT_MASK               (* (reg8 *) angleDirPin__BIT_MASK)
/* Bypass Enable */
#define angleDirPin_BYP                    (* (reg8 *) angleDirPin__BYP)
/* Port wide control signals */                                                   
#define angleDirPin_CTL                    (* (reg8 *) angleDirPin__CTL)
/* Drive Modes */
#define angleDirPin_DM0                    (* (reg8 *) angleDirPin__DM0) 
#define angleDirPin_DM1                    (* (reg8 *) angleDirPin__DM1)
#define angleDirPin_DM2                    (* (reg8 *) angleDirPin__DM2) 
/* Input Buffer Disable Override */
#define angleDirPin_INP_DIS                (* (reg8 *) angleDirPin__INP_DIS)
/* LCD Common or Segment Drive */
#define angleDirPin_LCD_COM_SEG            (* (reg8 *) angleDirPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define angleDirPin_LCD_EN                 (* (reg8 *) angleDirPin__LCD_EN)
/* Slew Rate Control */
#define angleDirPin_SLW                    (* (reg8 *) angleDirPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define angleDirPin_PRTDSI__CAPS_SEL       (* (reg8 *) angleDirPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define angleDirPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) angleDirPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define angleDirPin_PRTDSI__OE_SEL0        (* (reg8 *) angleDirPin__PRTDSI__OE_SEL0) 
#define angleDirPin_PRTDSI__OE_SEL1        (* (reg8 *) angleDirPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define angleDirPin_PRTDSI__OUT_SEL0       (* (reg8 *) angleDirPin__PRTDSI__OUT_SEL0) 
#define angleDirPin_PRTDSI__OUT_SEL1       (* (reg8 *) angleDirPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define angleDirPin_PRTDSI__SYNC_OUT       (* (reg8 *) angleDirPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(angleDirPin__SIO_CFG)
    #define angleDirPin_SIO_HYST_EN        (* (reg8 *) angleDirPin__SIO_HYST_EN)
    #define angleDirPin_SIO_REG_HIFREQ     (* (reg8 *) angleDirPin__SIO_REG_HIFREQ)
    #define angleDirPin_SIO_CFG            (* (reg8 *) angleDirPin__SIO_CFG)
    #define angleDirPin_SIO_DIFF           (* (reg8 *) angleDirPin__SIO_DIFF)
#endif /* (angleDirPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(angleDirPin__INTSTAT)
    #define angleDirPin_INTSTAT            (* (reg8 *) angleDirPin__INTSTAT)
    #define angleDirPin_SNAP               (* (reg8 *) angleDirPin__SNAP)
    
	#define angleDirPin_0_INTTYPE_REG 		(* (reg8 *) angleDirPin__0__INTTYPE)
#endif /* (angleDirPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_angleDirPin_H */


/* [] END OF FILE */
