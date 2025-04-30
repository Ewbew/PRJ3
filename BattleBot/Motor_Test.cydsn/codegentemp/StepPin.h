/*******************************************************************************
* File Name: StepPin.h  
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

#if !defined(CY_PINS_StepPin_H) /* Pins StepPin_H */
#define CY_PINS_StepPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "StepPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 StepPin__PORT == 15 && ((StepPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    StepPin_Write(uint8 value);
void    StepPin_SetDriveMode(uint8 mode);
uint8   StepPin_ReadDataReg(void);
uint8   StepPin_Read(void);
void    StepPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   StepPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the StepPin_SetDriveMode() function.
     *  @{
     */
        #define StepPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define StepPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define StepPin_DM_RES_UP          PIN_DM_RES_UP
        #define StepPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define StepPin_DM_OD_LO           PIN_DM_OD_LO
        #define StepPin_DM_OD_HI           PIN_DM_OD_HI
        #define StepPin_DM_STRONG          PIN_DM_STRONG
        #define StepPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define StepPin_MASK               StepPin__MASK
#define StepPin_SHIFT              StepPin__SHIFT
#define StepPin_WIDTH              1u

/* Interrupt constants */
#if defined(StepPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in StepPin_SetInterruptMode() function.
     *  @{
     */
        #define StepPin_INTR_NONE      (uint16)(0x0000u)
        #define StepPin_INTR_RISING    (uint16)(0x0001u)
        #define StepPin_INTR_FALLING   (uint16)(0x0002u)
        #define StepPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define StepPin_INTR_MASK      (0x01u) 
#endif /* (StepPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define StepPin_PS                     (* (reg8 *) StepPin__PS)
/* Data Register */
#define StepPin_DR                     (* (reg8 *) StepPin__DR)
/* Port Number */
#define StepPin_PRT_NUM                (* (reg8 *) StepPin__PRT) 
/* Connect to Analog Globals */                                                  
#define StepPin_AG                     (* (reg8 *) StepPin__AG)                       
/* Analog MUX bux enable */
#define StepPin_AMUX                   (* (reg8 *) StepPin__AMUX) 
/* Bidirectional Enable */                                                        
#define StepPin_BIE                    (* (reg8 *) StepPin__BIE)
/* Bit-mask for Aliased Register Access */
#define StepPin_BIT_MASK               (* (reg8 *) StepPin__BIT_MASK)
/* Bypass Enable */
#define StepPin_BYP                    (* (reg8 *) StepPin__BYP)
/* Port wide control signals */                                                   
#define StepPin_CTL                    (* (reg8 *) StepPin__CTL)
/* Drive Modes */
#define StepPin_DM0                    (* (reg8 *) StepPin__DM0) 
#define StepPin_DM1                    (* (reg8 *) StepPin__DM1)
#define StepPin_DM2                    (* (reg8 *) StepPin__DM2) 
/* Input Buffer Disable Override */
#define StepPin_INP_DIS                (* (reg8 *) StepPin__INP_DIS)
/* LCD Common or Segment Drive */
#define StepPin_LCD_COM_SEG            (* (reg8 *) StepPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define StepPin_LCD_EN                 (* (reg8 *) StepPin__LCD_EN)
/* Slew Rate Control */
#define StepPin_SLW                    (* (reg8 *) StepPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define StepPin_PRTDSI__CAPS_SEL       (* (reg8 *) StepPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define StepPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) StepPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define StepPin_PRTDSI__OE_SEL0        (* (reg8 *) StepPin__PRTDSI__OE_SEL0) 
#define StepPin_PRTDSI__OE_SEL1        (* (reg8 *) StepPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define StepPin_PRTDSI__OUT_SEL0       (* (reg8 *) StepPin__PRTDSI__OUT_SEL0) 
#define StepPin_PRTDSI__OUT_SEL1       (* (reg8 *) StepPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define StepPin_PRTDSI__SYNC_OUT       (* (reg8 *) StepPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(StepPin__SIO_CFG)
    #define StepPin_SIO_HYST_EN        (* (reg8 *) StepPin__SIO_HYST_EN)
    #define StepPin_SIO_REG_HIFREQ     (* (reg8 *) StepPin__SIO_REG_HIFREQ)
    #define StepPin_SIO_CFG            (* (reg8 *) StepPin__SIO_CFG)
    #define StepPin_SIO_DIFF           (* (reg8 *) StepPin__SIO_DIFF)
#endif /* (StepPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(StepPin__INTSTAT)
    #define StepPin_INTSTAT            (* (reg8 *) StepPin__INTSTAT)
    #define StepPin_SNAP               (* (reg8 *) StepPin__SNAP)
    
	#define StepPin_0_INTTYPE_REG 		(* (reg8 *) StepPin__0__INTTYPE)
#endif /* (StepPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_StepPin_H */


/* [] END OF FILE */
