/*******************************************************************************
* File Name: DirPin.h  
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

#if !defined(CY_PINS_DirPin_H) /* Pins DirPin_H */
#define CY_PINS_DirPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DirPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DirPin__PORT == 15 && ((DirPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DirPin_Write(uint8 value);
void    DirPin_SetDriveMode(uint8 mode);
uint8   DirPin_ReadDataReg(void);
uint8   DirPin_Read(void);
void    DirPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   DirPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DirPin_SetDriveMode() function.
     *  @{
     */
        #define DirPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DirPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DirPin_DM_RES_UP          PIN_DM_RES_UP
        #define DirPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define DirPin_DM_OD_LO           PIN_DM_OD_LO
        #define DirPin_DM_OD_HI           PIN_DM_OD_HI
        #define DirPin_DM_STRONG          PIN_DM_STRONG
        #define DirPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DirPin_MASK               DirPin__MASK
#define DirPin_SHIFT              DirPin__SHIFT
#define DirPin_WIDTH              1u

/* Interrupt constants */
#if defined(DirPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DirPin_SetInterruptMode() function.
     *  @{
     */
        #define DirPin_INTR_NONE      (uint16)(0x0000u)
        #define DirPin_INTR_RISING    (uint16)(0x0001u)
        #define DirPin_INTR_FALLING   (uint16)(0x0002u)
        #define DirPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DirPin_INTR_MASK      (0x01u) 
#endif /* (DirPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DirPin_PS                     (* (reg8 *) DirPin__PS)
/* Data Register */
#define DirPin_DR                     (* (reg8 *) DirPin__DR)
/* Port Number */
#define DirPin_PRT_NUM                (* (reg8 *) DirPin__PRT) 
/* Connect to Analog Globals */                                                  
#define DirPin_AG                     (* (reg8 *) DirPin__AG)                       
/* Analog MUX bux enable */
#define DirPin_AMUX                   (* (reg8 *) DirPin__AMUX) 
/* Bidirectional Enable */                                                        
#define DirPin_BIE                    (* (reg8 *) DirPin__BIE)
/* Bit-mask for Aliased Register Access */
#define DirPin_BIT_MASK               (* (reg8 *) DirPin__BIT_MASK)
/* Bypass Enable */
#define DirPin_BYP                    (* (reg8 *) DirPin__BYP)
/* Port wide control signals */                                                   
#define DirPin_CTL                    (* (reg8 *) DirPin__CTL)
/* Drive Modes */
#define DirPin_DM0                    (* (reg8 *) DirPin__DM0) 
#define DirPin_DM1                    (* (reg8 *) DirPin__DM1)
#define DirPin_DM2                    (* (reg8 *) DirPin__DM2) 
/* Input Buffer Disable Override */
#define DirPin_INP_DIS                (* (reg8 *) DirPin__INP_DIS)
/* LCD Common or Segment Drive */
#define DirPin_LCD_COM_SEG            (* (reg8 *) DirPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define DirPin_LCD_EN                 (* (reg8 *) DirPin__LCD_EN)
/* Slew Rate Control */
#define DirPin_SLW                    (* (reg8 *) DirPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DirPin_PRTDSI__CAPS_SEL       (* (reg8 *) DirPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DirPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DirPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DirPin_PRTDSI__OE_SEL0        (* (reg8 *) DirPin__PRTDSI__OE_SEL0) 
#define DirPin_PRTDSI__OE_SEL1        (* (reg8 *) DirPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DirPin_PRTDSI__OUT_SEL0       (* (reg8 *) DirPin__PRTDSI__OUT_SEL0) 
#define DirPin_PRTDSI__OUT_SEL1       (* (reg8 *) DirPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DirPin_PRTDSI__SYNC_OUT       (* (reg8 *) DirPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DirPin__SIO_CFG)
    #define DirPin_SIO_HYST_EN        (* (reg8 *) DirPin__SIO_HYST_EN)
    #define DirPin_SIO_REG_HIFREQ     (* (reg8 *) DirPin__SIO_REG_HIFREQ)
    #define DirPin_SIO_CFG            (* (reg8 *) DirPin__SIO_CFG)
    #define DirPin_SIO_DIFF           (* (reg8 *) DirPin__SIO_DIFF)
#endif /* (DirPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(DirPin__INTSTAT)
    #define DirPin_INTSTAT            (* (reg8 *) DirPin__INTSTAT)
    #define DirPin_SNAP               (* (reg8 *) DirPin__SNAP)
    
	#define DirPin_0_INTTYPE_REG 		(* (reg8 *) DirPin__0__INTTYPE)
#endif /* (DirPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DirPin_H */


/* [] END OF FILE */
