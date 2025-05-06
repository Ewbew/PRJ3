/*******************************************************************************
* File Name: dialStepPin.h  
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

#if !defined(CY_PINS_dialStepPin_H) /* Pins dialStepPin_H */
#define CY_PINS_dialStepPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dialStepPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dialStepPin__PORT == 15 && ((dialStepPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    dialStepPin_Write(uint8 value);
void    dialStepPin_SetDriveMode(uint8 mode);
uint8   dialStepPin_ReadDataReg(void);
uint8   dialStepPin_Read(void);
void    dialStepPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   dialStepPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the dialStepPin_SetDriveMode() function.
     *  @{
     */
        #define dialStepPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define dialStepPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define dialStepPin_DM_RES_UP          PIN_DM_RES_UP
        #define dialStepPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define dialStepPin_DM_OD_LO           PIN_DM_OD_LO
        #define dialStepPin_DM_OD_HI           PIN_DM_OD_HI
        #define dialStepPin_DM_STRONG          PIN_DM_STRONG
        #define dialStepPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define dialStepPin_MASK               dialStepPin__MASK
#define dialStepPin_SHIFT              dialStepPin__SHIFT
#define dialStepPin_WIDTH              1u

/* Interrupt constants */
#if defined(dialStepPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in dialStepPin_SetInterruptMode() function.
     *  @{
     */
        #define dialStepPin_INTR_NONE      (uint16)(0x0000u)
        #define dialStepPin_INTR_RISING    (uint16)(0x0001u)
        #define dialStepPin_INTR_FALLING   (uint16)(0x0002u)
        #define dialStepPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define dialStepPin_INTR_MASK      (0x01u) 
#endif /* (dialStepPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dialStepPin_PS                     (* (reg8 *) dialStepPin__PS)
/* Data Register */
#define dialStepPin_DR                     (* (reg8 *) dialStepPin__DR)
/* Port Number */
#define dialStepPin_PRT_NUM                (* (reg8 *) dialStepPin__PRT) 
/* Connect to Analog Globals */                                                  
#define dialStepPin_AG                     (* (reg8 *) dialStepPin__AG)                       
/* Analog MUX bux enable */
#define dialStepPin_AMUX                   (* (reg8 *) dialStepPin__AMUX) 
/* Bidirectional Enable */                                                        
#define dialStepPin_BIE                    (* (reg8 *) dialStepPin__BIE)
/* Bit-mask for Aliased Register Access */
#define dialStepPin_BIT_MASK               (* (reg8 *) dialStepPin__BIT_MASK)
/* Bypass Enable */
#define dialStepPin_BYP                    (* (reg8 *) dialStepPin__BYP)
/* Port wide control signals */                                                   
#define dialStepPin_CTL                    (* (reg8 *) dialStepPin__CTL)
/* Drive Modes */
#define dialStepPin_DM0                    (* (reg8 *) dialStepPin__DM0) 
#define dialStepPin_DM1                    (* (reg8 *) dialStepPin__DM1)
#define dialStepPin_DM2                    (* (reg8 *) dialStepPin__DM2) 
/* Input Buffer Disable Override */
#define dialStepPin_INP_DIS                (* (reg8 *) dialStepPin__INP_DIS)
/* LCD Common or Segment Drive */
#define dialStepPin_LCD_COM_SEG            (* (reg8 *) dialStepPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define dialStepPin_LCD_EN                 (* (reg8 *) dialStepPin__LCD_EN)
/* Slew Rate Control */
#define dialStepPin_SLW                    (* (reg8 *) dialStepPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dialStepPin_PRTDSI__CAPS_SEL       (* (reg8 *) dialStepPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dialStepPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dialStepPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dialStepPin_PRTDSI__OE_SEL0        (* (reg8 *) dialStepPin__PRTDSI__OE_SEL0) 
#define dialStepPin_PRTDSI__OE_SEL1        (* (reg8 *) dialStepPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dialStepPin_PRTDSI__OUT_SEL0       (* (reg8 *) dialStepPin__PRTDSI__OUT_SEL0) 
#define dialStepPin_PRTDSI__OUT_SEL1       (* (reg8 *) dialStepPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dialStepPin_PRTDSI__SYNC_OUT       (* (reg8 *) dialStepPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(dialStepPin__SIO_CFG)
    #define dialStepPin_SIO_HYST_EN        (* (reg8 *) dialStepPin__SIO_HYST_EN)
    #define dialStepPin_SIO_REG_HIFREQ     (* (reg8 *) dialStepPin__SIO_REG_HIFREQ)
    #define dialStepPin_SIO_CFG            (* (reg8 *) dialStepPin__SIO_CFG)
    #define dialStepPin_SIO_DIFF           (* (reg8 *) dialStepPin__SIO_DIFF)
#endif /* (dialStepPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(dialStepPin__INTSTAT)
    #define dialStepPin_INTSTAT            (* (reg8 *) dialStepPin__INTSTAT)
    #define dialStepPin_SNAP               (* (reg8 *) dialStepPin__SNAP)
    
	#define dialStepPin_0_INTTYPE_REG 		(* (reg8 *) dialStepPin__0__INTTYPE)
#endif /* (dialStepPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dialStepPin_H */


/* [] END OF FILE */
