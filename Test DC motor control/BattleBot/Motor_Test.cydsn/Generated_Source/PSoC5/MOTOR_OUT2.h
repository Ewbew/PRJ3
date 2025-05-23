/*******************************************************************************
* File Name: MOTOR_OUT2.h  
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

#if !defined(CY_PINS_MOTOR_OUT2_H) /* Pins MOTOR_OUT2_H */
#define CY_PINS_MOTOR_OUT2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOTOR_OUT2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MOTOR_OUT2__PORT == 15 && ((MOTOR_OUT2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MOTOR_OUT2_Write(uint8 value);
void    MOTOR_OUT2_SetDriveMode(uint8 mode);
uint8   MOTOR_OUT2_ReadDataReg(void);
uint8   MOTOR_OUT2_Read(void);
void    MOTOR_OUT2_SetInterruptMode(uint16 position, uint16 mode);
uint8   MOTOR_OUT2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MOTOR_OUT2_SetDriveMode() function.
     *  @{
     */
        #define MOTOR_OUT2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MOTOR_OUT2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MOTOR_OUT2_DM_RES_UP          PIN_DM_RES_UP
        #define MOTOR_OUT2_DM_RES_DWN         PIN_DM_RES_DWN
        #define MOTOR_OUT2_DM_OD_LO           PIN_DM_OD_LO
        #define MOTOR_OUT2_DM_OD_HI           PIN_DM_OD_HI
        #define MOTOR_OUT2_DM_STRONG          PIN_DM_STRONG
        #define MOTOR_OUT2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MOTOR_OUT2_MASK               MOTOR_OUT2__MASK
#define MOTOR_OUT2_SHIFT              MOTOR_OUT2__SHIFT
#define MOTOR_OUT2_WIDTH              1u

/* Interrupt constants */
#if defined(MOTOR_OUT2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOTOR_OUT2_SetInterruptMode() function.
     *  @{
     */
        #define MOTOR_OUT2_INTR_NONE      (uint16)(0x0000u)
        #define MOTOR_OUT2_INTR_RISING    (uint16)(0x0001u)
        #define MOTOR_OUT2_INTR_FALLING   (uint16)(0x0002u)
        #define MOTOR_OUT2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MOTOR_OUT2_INTR_MASK      (0x01u) 
#endif /* (MOTOR_OUT2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOTOR_OUT2_PS                     (* (reg8 *) MOTOR_OUT2__PS)
/* Data Register */
#define MOTOR_OUT2_DR                     (* (reg8 *) MOTOR_OUT2__DR)
/* Port Number */
#define MOTOR_OUT2_PRT_NUM                (* (reg8 *) MOTOR_OUT2__PRT) 
/* Connect to Analog Globals */                                                  
#define MOTOR_OUT2_AG                     (* (reg8 *) MOTOR_OUT2__AG)                       
/* Analog MUX bux enable */
#define MOTOR_OUT2_AMUX                   (* (reg8 *) MOTOR_OUT2__AMUX) 
/* Bidirectional Enable */                                                        
#define MOTOR_OUT2_BIE                    (* (reg8 *) MOTOR_OUT2__BIE)
/* Bit-mask for Aliased Register Access */
#define MOTOR_OUT2_BIT_MASK               (* (reg8 *) MOTOR_OUT2__BIT_MASK)
/* Bypass Enable */
#define MOTOR_OUT2_BYP                    (* (reg8 *) MOTOR_OUT2__BYP)
/* Port wide control signals */                                                   
#define MOTOR_OUT2_CTL                    (* (reg8 *) MOTOR_OUT2__CTL)
/* Drive Modes */
#define MOTOR_OUT2_DM0                    (* (reg8 *) MOTOR_OUT2__DM0) 
#define MOTOR_OUT2_DM1                    (* (reg8 *) MOTOR_OUT2__DM1)
#define MOTOR_OUT2_DM2                    (* (reg8 *) MOTOR_OUT2__DM2) 
/* Input Buffer Disable Override */
#define MOTOR_OUT2_INP_DIS                (* (reg8 *) MOTOR_OUT2__INP_DIS)
/* LCD Common or Segment Drive */
#define MOTOR_OUT2_LCD_COM_SEG            (* (reg8 *) MOTOR_OUT2__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOTOR_OUT2_LCD_EN                 (* (reg8 *) MOTOR_OUT2__LCD_EN)
/* Slew Rate Control */
#define MOTOR_OUT2_SLW                    (* (reg8 *) MOTOR_OUT2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOTOR_OUT2_PRTDSI__CAPS_SEL       (* (reg8 *) MOTOR_OUT2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOTOR_OUT2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOTOR_OUT2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOTOR_OUT2_PRTDSI__OE_SEL0        (* (reg8 *) MOTOR_OUT2__PRTDSI__OE_SEL0) 
#define MOTOR_OUT2_PRTDSI__OE_SEL1        (* (reg8 *) MOTOR_OUT2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOTOR_OUT2_PRTDSI__OUT_SEL0       (* (reg8 *) MOTOR_OUT2__PRTDSI__OUT_SEL0) 
#define MOTOR_OUT2_PRTDSI__OUT_SEL1       (* (reg8 *) MOTOR_OUT2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOTOR_OUT2_PRTDSI__SYNC_OUT       (* (reg8 *) MOTOR_OUT2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MOTOR_OUT2__SIO_CFG)
    #define MOTOR_OUT2_SIO_HYST_EN        (* (reg8 *) MOTOR_OUT2__SIO_HYST_EN)
    #define MOTOR_OUT2_SIO_REG_HIFREQ     (* (reg8 *) MOTOR_OUT2__SIO_REG_HIFREQ)
    #define MOTOR_OUT2_SIO_CFG            (* (reg8 *) MOTOR_OUT2__SIO_CFG)
    #define MOTOR_OUT2_SIO_DIFF           (* (reg8 *) MOTOR_OUT2__SIO_DIFF)
#endif /* (MOTOR_OUT2__SIO_CFG) */

/* Interrupt Registers */
#if defined(MOTOR_OUT2__INTSTAT)
    #define MOTOR_OUT2_INTSTAT            (* (reg8 *) MOTOR_OUT2__INTSTAT)
    #define MOTOR_OUT2_SNAP               (* (reg8 *) MOTOR_OUT2__SNAP)
    
	#define MOTOR_OUT2_0_INTTYPE_REG 		(* (reg8 *) MOTOR_OUT2__0__INTTYPE)
#endif /* (MOTOR_OUT2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MOTOR_OUT2_H */


/* [] END OF FILE */
