/*******************************************************************************
* File Name: fireStepPin.h  
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

#if !defined(CY_PINS_fireStepPin_H) /* Pins fireStepPin_H */
#define CY_PINS_fireStepPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "fireStepPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 fireStepPin__PORT == 15 && ((fireStepPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    fireStepPin_Write(uint8 value);
void    fireStepPin_SetDriveMode(uint8 mode);
uint8   fireStepPin_ReadDataReg(void);
uint8   fireStepPin_Read(void);
void    fireStepPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   fireStepPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the fireStepPin_SetDriveMode() function.
     *  @{
     */
        #define fireStepPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define fireStepPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define fireStepPin_DM_RES_UP          PIN_DM_RES_UP
        #define fireStepPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define fireStepPin_DM_OD_LO           PIN_DM_OD_LO
        #define fireStepPin_DM_OD_HI           PIN_DM_OD_HI
        #define fireStepPin_DM_STRONG          PIN_DM_STRONG
        #define fireStepPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define fireStepPin_MASK               fireStepPin__MASK
#define fireStepPin_SHIFT              fireStepPin__SHIFT
#define fireStepPin_WIDTH              1u

/* Interrupt constants */
#if defined(fireStepPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in fireStepPin_SetInterruptMode() function.
     *  @{
     */
        #define fireStepPin_INTR_NONE      (uint16)(0x0000u)
        #define fireStepPin_INTR_RISING    (uint16)(0x0001u)
        #define fireStepPin_INTR_FALLING   (uint16)(0x0002u)
        #define fireStepPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define fireStepPin_INTR_MASK      (0x01u) 
#endif /* (fireStepPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define fireStepPin_PS                     (* (reg8 *) fireStepPin__PS)
/* Data Register */
#define fireStepPin_DR                     (* (reg8 *) fireStepPin__DR)
/* Port Number */
#define fireStepPin_PRT_NUM                (* (reg8 *) fireStepPin__PRT) 
/* Connect to Analog Globals */                                                  
#define fireStepPin_AG                     (* (reg8 *) fireStepPin__AG)                       
/* Analog MUX bux enable */
#define fireStepPin_AMUX                   (* (reg8 *) fireStepPin__AMUX) 
/* Bidirectional Enable */                                                        
#define fireStepPin_BIE                    (* (reg8 *) fireStepPin__BIE)
/* Bit-mask for Aliased Register Access */
#define fireStepPin_BIT_MASK               (* (reg8 *) fireStepPin__BIT_MASK)
/* Bypass Enable */
#define fireStepPin_BYP                    (* (reg8 *) fireStepPin__BYP)
/* Port wide control signals */                                                   
#define fireStepPin_CTL                    (* (reg8 *) fireStepPin__CTL)
/* Drive Modes */
#define fireStepPin_DM0                    (* (reg8 *) fireStepPin__DM0) 
#define fireStepPin_DM1                    (* (reg8 *) fireStepPin__DM1)
#define fireStepPin_DM2                    (* (reg8 *) fireStepPin__DM2) 
/* Input Buffer Disable Override */
#define fireStepPin_INP_DIS                (* (reg8 *) fireStepPin__INP_DIS)
/* LCD Common or Segment Drive */
#define fireStepPin_LCD_COM_SEG            (* (reg8 *) fireStepPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define fireStepPin_LCD_EN                 (* (reg8 *) fireStepPin__LCD_EN)
/* Slew Rate Control */
#define fireStepPin_SLW                    (* (reg8 *) fireStepPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define fireStepPin_PRTDSI__CAPS_SEL       (* (reg8 *) fireStepPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define fireStepPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) fireStepPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define fireStepPin_PRTDSI__OE_SEL0        (* (reg8 *) fireStepPin__PRTDSI__OE_SEL0) 
#define fireStepPin_PRTDSI__OE_SEL1        (* (reg8 *) fireStepPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define fireStepPin_PRTDSI__OUT_SEL0       (* (reg8 *) fireStepPin__PRTDSI__OUT_SEL0) 
#define fireStepPin_PRTDSI__OUT_SEL1       (* (reg8 *) fireStepPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define fireStepPin_PRTDSI__SYNC_OUT       (* (reg8 *) fireStepPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(fireStepPin__SIO_CFG)
    #define fireStepPin_SIO_HYST_EN        (* (reg8 *) fireStepPin__SIO_HYST_EN)
    #define fireStepPin_SIO_REG_HIFREQ     (* (reg8 *) fireStepPin__SIO_REG_HIFREQ)
    #define fireStepPin_SIO_CFG            (* (reg8 *) fireStepPin__SIO_CFG)
    #define fireStepPin_SIO_DIFF           (* (reg8 *) fireStepPin__SIO_DIFF)
#endif /* (fireStepPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(fireStepPin__INTSTAT)
    #define fireStepPin_INTSTAT            (* (reg8 *) fireStepPin__INTSTAT)
    #define fireStepPin_SNAP               (* (reg8 *) fireStepPin__SNAP)
    
	#define fireStepPin_0_INTTYPE_REG 		(* (reg8 *) fireStepPin__0__INTTYPE)
#endif /* (fireStepPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_fireStepPin_H */


/* [] END OF FILE */
