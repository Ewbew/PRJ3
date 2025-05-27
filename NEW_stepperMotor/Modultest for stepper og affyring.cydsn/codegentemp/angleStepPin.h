/*******************************************************************************
* File Name: angleStepPin.h  
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

#if !defined(CY_PINS_angleStepPin_H) /* Pins angleStepPin_H */
#define CY_PINS_angleStepPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "angleStepPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 angleStepPin__PORT == 15 && ((angleStepPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    angleStepPin_Write(uint8 value);
void    angleStepPin_SetDriveMode(uint8 mode);
uint8   angleStepPin_ReadDataReg(void);
uint8   angleStepPin_Read(void);
void    angleStepPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   angleStepPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the angleStepPin_SetDriveMode() function.
     *  @{
     */
        #define angleStepPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define angleStepPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define angleStepPin_DM_RES_UP          PIN_DM_RES_UP
        #define angleStepPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define angleStepPin_DM_OD_LO           PIN_DM_OD_LO
        #define angleStepPin_DM_OD_HI           PIN_DM_OD_HI
        #define angleStepPin_DM_STRONG          PIN_DM_STRONG
        #define angleStepPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define angleStepPin_MASK               angleStepPin__MASK
#define angleStepPin_SHIFT              angleStepPin__SHIFT
#define angleStepPin_WIDTH              1u

/* Interrupt constants */
#if defined(angleStepPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in angleStepPin_SetInterruptMode() function.
     *  @{
     */
        #define angleStepPin_INTR_NONE      (uint16)(0x0000u)
        #define angleStepPin_INTR_RISING    (uint16)(0x0001u)
        #define angleStepPin_INTR_FALLING   (uint16)(0x0002u)
        #define angleStepPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define angleStepPin_INTR_MASK      (0x01u) 
#endif /* (angleStepPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define angleStepPin_PS                     (* (reg8 *) angleStepPin__PS)
/* Data Register */
#define angleStepPin_DR                     (* (reg8 *) angleStepPin__DR)
/* Port Number */
#define angleStepPin_PRT_NUM                (* (reg8 *) angleStepPin__PRT) 
/* Connect to Analog Globals */                                                  
#define angleStepPin_AG                     (* (reg8 *) angleStepPin__AG)                       
/* Analog MUX bux enable */
#define angleStepPin_AMUX                   (* (reg8 *) angleStepPin__AMUX) 
/* Bidirectional Enable */                                                        
#define angleStepPin_BIE                    (* (reg8 *) angleStepPin__BIE)
/* Bit-mask for Aliased Register Access */
#define angleStepPin_BIT_MASK               (* (reg8 *) angleStepPin__BIT_MASK)
/* Bypass Enable */
#define angleStepPin_BYP                    (* (reg8 *) angleStepPin__BYP)
/* Port wide control signals */                                                   
#define angleStepPin_CTL                    (* (reg8 *) angleStepPin__CTL)
/* Drive Modes */
#define angleStepPin_DM0                    (* (reg8 *) angleStepPin__DM0) 
#define angleStepPin_DM1                    (* (reg8 *) angleStepPin__DM1)
#define angleStepPin_DM2                    (* (reg8 *) angleStepPin__DM2) 
/* Input Buffer Disable Override */
#define angleStepPin_INP_DIS                (* (reg8 *) angleStepPin__INP_DIS)
/* LCD Common or Segment Drive */
#define angleStepPin_LCD_COM_SEG            (* (reg8 *) angleStepPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define angleStepPin_LCD_EN                 (* (reg8 *) angleStepPin__LCD_EN)
/* Slew Rate Control */
#define angleStepPin_SLW                    (* (reg8 *) angleStepPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define angleStepPin_PRTDSI__CAPS_SEL       (* (reg8 *) angleStepPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define angleStepPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) angleStepPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define angleStepPin_PRTDSI__OE_SEL0        (* (reg8 *) angleStepPin__PRTDSI__OE_SEL0) 
#define angleStepPin_PRTDSI__OE_SEL1        (* (reg8 *) angleStepPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define angleStepPin_PRTDSI__OUT_SEL0       (* (reg8 *) angleStepPin__PRTDSI__OUT_SEL0) 
#define angleStepPin_PRTDSI__OUT_SEL1       (* (reg8 *) angleStepPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define angleStepPin_PRTDSI__SYNC_OUT       (* (reg8 *) angleStepPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(angleStepPin__SIO_CFG)
    #define angleStepPin_SIO_HYST_EN        (* (reg8 *) angleStepPin__SIO_HYST_EN)
    #define angleStepPin_SIO_REG_HIFREQ     (* (reg8 *) angleStepPin__SIO_REG_HIFREQ)
    #define angleStepPin_SIO_CFG            (* (reg8 *) angleStepPin__SIO_CFG)
    #define angleStepPin_SIO_DIFF           (* (reg8 *) angleStepPin__SIO_DIFF)
#endif /* (angleStepPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(angleStepPin__INTSTAT)
    #define angleStepPin_INTSTAT            (* (reg8 *) angleStepPin__INTSTAT)
    #define angleStepPin_SNAP               (* (reg8 *) angleStepPin__SNAP)
    
	#define angleStepPin_0_INTTYPE_REG 		(* (reg8 *) angleStepPin__0__INTTYPE)
#endif /* (angleStepPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_angleStepPin_H */


/* [] END OF FILE */
