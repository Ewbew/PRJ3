/*******************************************************************************
* File Name: fireDirPin.h  
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

#if !defined(CY_PINS_fireDirPin_H) /* Pins fireDirPin_H */
#define CY_PINS_fireDirPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "fireDirPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 fireDirPin__PORT == 15 && ((fireDirPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    fireDirPin_Write(uint8 value);
void    fireDirPin_SetDriveMode(uint8 mode);
uint8   fireDirPin_ReadDataReg(void);
uint8   fireDirPin_Read(void);
void    fireDirPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   fireDirPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the fireDirPin_SetDriveMode() function.
     *  @{
     */
        #define fireDirPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define fireDirPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define fireDirPin_DM_RES_UP          PIN_DM_RES_UP
        #define fireDirPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define fireDirPin_DM_OD_LO           PIN_DM_OD_LO
        #define fireDirPin_DM_OD_HI           PIN_DM_OD_HI
        #define fireDirPin_DM_STRONG          PIN_DM_STRONG
        #define fireDirPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define fireDirPin_MASK               fireDirPin__MASK
#define fireDirPin_SHIFT              fireDirPin__SHIFT
#define fireDirPin_WIDTH              1u

/* Interrupt constants */
#if defined(fireDirPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in fireDirPin_SetInterruptMode() function.
     *  @{
     */
        #define fireDirPin_INTR_NONE      (uint16)(0x0000u)
        #define fireDirPin_INTR_RISING    (uint16)(0x0001u)
        #define fireDirPin_INTR_FALLING   (uint16)(0x0002u)
        #define fireDirPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define fireDirPin_INTR_MASK      (0x01u) 
#endif /* (fireDirPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define fireDirPin_PS                     (* (reg8 *) fireDirPin__PS)
/* Data Register */
#define fireDirPin_DR                     (* (reg8 *) fireDirPin__DR)
/* Port Number */
#define fireDirPin_PRT_NUM                (* (reg8 *) fireDirPin__PRT) 
/* Connect to Analog Globals */                                                  
#define fireDirPin_AG                     (* (reg8 *) fireDirPin__AG)                       
/* Analog MUX bux enable */
#define fireDirPin_AMUX                   (* (reg8 *) fireDirPin__AMUX) 
/* Bidirectional Enable */                                                        
#define fireDirPin_BIE                    (* (reg8 *) fireDirPin__BIE)
/* Bit-mask for Aliased Register Access */
#define fireDirPin_BIT_MASK               (* (reg8 *) fireDirPin__BIT_MASK)
/* Bypass Enable */
#define fireDirPin_BYP                    (* (reg8 *) fireDirPin__BYP)
/* Port wide control signals */                                                   
#define fireDirPin_CTL                    (* (reg8 *) fireDirPin__CTL)
/* Drive Modes */
#define fireDirPin_DM0                    (* (reg8 *) fireDirPin__DM0) 
#define fireDirPin_DM1                    (* (reg8 *) fireDirPin__DM1)
#define fireDirPin_DM2                    (* (reg8 *) fireDirPin__DM2) 
/* Input Buffer Disable Override */
#define fireDirPin_INP_DIS                (* (reg8 *) fireDirPin__INP_DIS)
/* LCD Common or Segment Drive */
#define fireDirPin_LCD_COM_SEG            (* (reg8 *) fireDirPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define fireDirPin_LCD_EN                 (* (reg8 *) fireDirPin__LCD_EN)
/* Slew Rate Control */
#define fireDirPin_SLW                    (* (reg8 *) fireDirPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define fireDirPin_PRTDSI__CAPS_SEL       (* (reg8 *) fireDirPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define fireDirPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) fireDirPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define fireDirPin_PRTDSI__OE_SEL0        (* (reg8 *) fireDirPin__PRTDSI__OE_SEL0) 
#define fireDirPin_PRTDSI__OE_SEL1        (* (reg8 *) fireDirPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define fireDirPin_PRTDSI__OUT_SEL0       (* (reg8 *) fireDirPin__PRTDSI__OUT_SEL0) 
#define fireDirPin_PRTDSI__OUT_SEL1       (* (reg8 *) fireDirPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define fireDirPin_PRTDSI__SYNC_OUT       (* (reg8 *) fireDirPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(fireDirPin__SIO_CFG)
    #define fireDirPin_SIO_HYST_EN        (* (reg8 *) fireDirPin__SIO_HYST_EN)
    #define fireDirPin_SIO_REG_HIFREQ     (* (reg8 *) fireDirPin__SIO_REG_HIFREQ)
    #define fireDirPin_SIO_CFG            (* (reg8 *) fireDirPin__SIO_CFG)
    #define fireDirPin_SIO_DIFF           (* (reg8 *) fireDirPin__SIO_DIFF)
#endif /* (fireDirPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(fireDirPin__INTSTAT)
    #define fireDirPin_INTSTAT            (* (reg8 *) fireDirPin__INTSTAT)
    #define fireDirPin_SNAP               (* (reg8 *) fireDirPin__SNAP)
    
	#define fireDirPin_0_INTTYPE_REG 		(* (reg8 *) fireDirPin__0__INTTYPE)
#endif /* (fireDirPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_fireDirPin_H */


/* [] END OF FILE */
