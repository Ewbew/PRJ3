/*******************************************************************************
* File Name: dialDirPin.h  
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

#if !defined(CY_PINS_dialDirPin_H) /* Pins dialDirPin_H */
#define CY_PINS_dialDirPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dialDirPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dialDirPin__PORT == 15 && ((dialDirPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    dialDirPin_Write(uint8 value);
void    dialDirPin_SetDriveMode(uint8 mode);
uint8   dialDirPin_ReadDataReg(void);
uint8   dialDirPin_Read(void);
void    dialDirPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   dialDirPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the dialDirPin_SetDriveMode() function.
     *  @{
     */
        #define dialDirPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define dialDirPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define dialDirPin_DM_RES_UP          PIN_DM_RES_UP
        #define dialDirPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define dialDirPin_DM_OD_LO           PIN_DM_OD_LO
        #define dialDirPin_DM_OD_HI           PIN_DM_OD_HI
        #define dialDirPin_DM_STRONG          PIN_DM_STRONG
        #define dialDirPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define dialDirPin_MASK               dialDirPin__MASK
#define dialDirPin_SHIFT              dialDirPin__SHIFT
#define dialDirPin_WIDTH              1u

/* Interrupt constants */
#if defined(dialDirPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in dialDirPin_SetInterruptMode() function.
     *  @{
     */
        #define dialDirPin_INTR_NONE      (uint16)(0x0000u)
        #define dialDirPin_INTR_RISING    (uint16)(0x0001u)
        #define dialDirPin_INTR_FALLING   (uint16)(0x0002u)
        #define dialDirPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define dialDirPin_INTR_MASK      (0x01u) 
#endif /* (dialDirPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dialDirPin_PS                     (* (reg8 *) dialDirPin__PS)
/* Data Register */
#define dialDirPin_DR                     (* (reg8 *) dialDirPin__DR)
/* Port Number */
#define dialDirPin_PRT_NUM                (* (reg8 *) dialDirPin__PRT) 
/* Connect to Analog Globals */                                                  
#define dialDirPin_AG                     (* (reg8 *) dialDirPin__AG)                       
/* Analog MUX bux enable */
#define dialDirPin_AMUX                   (* (reg8 *) dialDirPin__AMUX) 
/* Bidirectional Enable */                                                        
#define dialDirPin_BIE                    (* (reg8 *) dialDirPin__BIE)
/* Bit-mask for Aliased Register Access */
#define dialDirPin_BIT_MASK               (* (reg8 *) dialDirPin__BIT_MASK)
/* Bypass Enable */
#define dialDirPin_BYP                    (* (reg8 *) dialDirPin__BYP)
/* Port wide control signals */                                                   
#define dialDirPin_CTL                    (* (reg8 *) dialDirPin__CTL)
/* Drive Modes */
#define dialDirPin_DM0                    (* (reg8 *) dialDirPin__DM0) 
#define dialDirPin_DM1                    (* (reg8 *) dialDirPin__DM1)
#define dialDirPin_DM2                    (* (reg8 *) dialDirPin__DM2) 
/* Input Buffer Disable Override */
#define dialDirPin_INP_DIS                (* (reg8 *) dialDirPin__INP_DIS)
/* LCD Common or Segment Drive */
#define dialDirPin_LCD_COM_SEG            (* (reg8 *) dialDirPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define dialDirPin_LCD_EN                 (* (reg8 *) dialDirPin__LCD_EN)
/* Slew Rate Control */
#define dialDirPin_SLW                    (* (reg8 *) dialDirPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dialDirPin_PRTDSI__CAPS_SEL       (* (reg8 *) dialDirPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dialDirPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dialDirPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dialDirPin_PRTDSI__OE_SEL0        (* (reg8 *) dialDirPin__PRTDSI__OE_SEL0) 
#define dialDirPin_PRTDSI__OE_SEL1        (* (reg8 *) dialDirPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dialDirPin_PRTDSI__OUT_SEL0       (* (reg8 *) dialDirPin__PRTDSI__OUT_SEL0) 
#define dialDirPin_PRTDSI__OUT_SEL1       (* (reg8 *) dialDirPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dialDirPin_PRTDSI__SYNC_OUT       (* (reg8 *) dialDirPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(dialDirPin__SIO_CFG)
    #define dialDirPin_SIO_HYST_EN        (* (reg8 *) dialDirPin__SIO_HYST_EN)
    #define dialDirPin_SIO_REG_HIFREQ     (* (reg8 *) dialDirPin__SIO_REG_HIFREQ)
    #define dialDirPin_SIO_CFG            (* (reg8 *) dialDirPin__SIO_CFG)
    #define dialDirPin_SIO_DIFF           (* (reg8 *) dialDirPin__SIO_DIFF)
#endif /* (dialDirPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(dialDirPin__INTSTAT)
    #define dialDirPin_INTSTAT            (* (reg8 *) dialDirPin__INTSTAT)
    #define dialDirPin_SNAP               (* (reg8 *) dialDirPin__SNAP)
    
	#define dialDirPin_0_INTTYPE_REG 		(* (reg8 *) dialDirPin__0__INTTYPE)
#endif /* (dialDirPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dialDirPin_H */


/* [] END OF FILE */
