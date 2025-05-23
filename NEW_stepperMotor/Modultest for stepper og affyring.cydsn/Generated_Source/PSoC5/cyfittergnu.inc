/*******************************************************************************
* File Name: cyfittergnu.inc
* 
* PSoC Creator  4.4
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

.ifndef INCLUDED_CYFITTERGNU_INC
.set INCLUDED_CYFITTERGNU_INC, 1
.include "cydevicegnu.inc"
.include "cydevicegnu_trm.inc"

/* Clock_1 */
.set Clock_1__CFG0, CYREG_CLKDIST_DCFG0_CFG0
.set Clock_1__CFG1, CYREG_CLKDIST_DCFG0_CFG1
.set Clock_1__CFG2, CYREG_CLKDIST_DCFG0_CFG2
.set Clock_1__CFG2_SRC_SEL_MASK, 0x07
.set Clock_1__INDEX, 0x00
.set Clock_1__PM_ACT_CFG, CYREG_PM_ACT_CFG2
.set Clock_1__PM_ACT_MSK, 0x01
.set Clock_1__PM_STBY_CFG, CYREG_PM_STBY_CFG2
.set Clock_1__PM_STBY_MSK, 0x01

/* Timer_1 */
.set Timer_1_TimerUDB_rstSts_stsreg__0__MASK, 0x01
.set Timer_1_TimerUDB_rstSts_stsreg__0__POS, 0
.set Timer_1_TimerUDB_rstSts_stsreg__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB11_12_ACTL
.set Timer_1_TimerUDB_rstSts_stsreg__16BIT_STATUS_REG, CYREG_B0_UDB11_12_ST
.set Timer_1_TimerUDB_rstSts_stsreg__2__MASK, 0x04
.set Timer_1_TimerUDB_rstSts_stsreg__2__POS, 2
.set Timer_1_TimerUDB_rstSts_stsreg__3__MASK, 0x08
.set Timer_1_TimerUDB_rstSts_stsreg__3__POS, 3
.set Timer_1_TimerUDB_rstSts_stsreg__MASK, 0x0D
.set Timer_1_TimerUDB_rstSts_stsreg__MASK_REG, CYREG_B0_UDB11_MSK
.set Timer_1_TimerUDB_rstSts_stsreg__MASK_ST_AUX_CTL_REG, CYREG_B0_UDB11_MSK_ACTL
.set Timer_1_TimerUDB_rstSts_stsreg__PER_ST_AUX_CTL_REG, CYREG_B0_UDB11_MSK_ACTL
.set Timer_1_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG, CYREG_B0_UDB11_ACTL
.set Timer_1_TimerUDB_rstSts_stsreg__STATUS_CNT_REG, CYREG_B0_UDB11_ST_CTL
.set Timer_1_TimerUDB_rstSts_stsreg__STATUS_CONTROL_REG, CYREG_B0_UDB11_ST_CTL
.set Timer_1_TimerUDB_rstSts_stsreg__STATUS_REG, CYREG_B0_UDB11_ST
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_AUX_CTL_REG, CYREG_B0_UDB11_12_ACTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_CONTROL_REG, CYREG_B0_UDB11_12_CTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_COUNT_REG, CYREG_B0_UDB11_12_CTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_CONTROL_REG, CYREG_B0_UDB11_12_CTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_COUNT_REG, CYREG_B0_UDB11_12_CTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_MASK_REG, CYREG_B0_UDB11_12_MSK
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_PERIOD_REG, CYREG_B0_UDB11_12_MSK
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_MASK_REG, CYREG_B0_UDB11_12_MSK
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_PERIOD_REG, CYREG_B0_UDB11_12_MSK
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__7__MASK, 0x80
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__7__POS, 7
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_AUX_CTL_REG, CYREG_B0_UDB11_ACTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG, CYREG_B0_UDB11_CTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_ST_REG, CYREG_B0_UDB11_ST_CTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_REG, CYREG_B0_UDB11_CTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_ST_REG, CYREG_B0_UDB11_ST_CTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__MASK, 0x80
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__MASK_CTL_AUX_CTL_REG, CYREG_B0_UDB11_MSK_ACTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__PER_CTL_AUX_CTL_REG, CYREG_B0_UDB11_MSK_ACTL
.set Timer_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__PERIOD_REG, CYREG_B0_UDB11_MSK
.set Timer_1_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG, CYREG_B0_UDB11_12_A0
.set Timer_1_TimerUDB_sT8_timerdp_u0__16BIT_A1_REG, CYREG_B0_UDB11_12_A1
.set Timer_1_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG, CYREG_B0_UDB11_12_D0
.set Timer_1_TimerUDB_sT8_timerdp_u0__16BIT_D1_REG, CYREG_B0_UDB11_12_D1
.set Timer_1_TimerUDB_sT8_timerdp_u0__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB11_12_ACTL
.set Timer_1_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG, CYREG_B0_UDB11_12_F0
.set Timer_1_TimerUDB_sT8_timerdp_u0__16BIT_F1_REG, CYREG_B0_UDB11_12_F1
.set Timer_1_TimerUDB_sT8_timerdp_u0__A0_A1_REG, CYREG_B0_UDB11_A0_A1
.set Timer_1_TimerUDB_sT8_timerdp_u0__A0_REG, CYREG_B0_UDB11_A0
.set Timer_1_TimerUDB_sT8_timerdp_u0__A1_REG, CYREG_B0_UDB11_A1
.set Timer_1_TimerUDB_sT8_timerdp_u0__D0_D1_REG, CYREG_B0_UDB11_D0_D1
.set Timer_1_TimerUDB_sT8_timerdp_u0__D0_REG, CYREG_B0_UDB11_D0
.set Timer_1_TimerUDB_sT8_timerdp_u0__D1_REG, CYREG_B0_UDB11_D1
.set Timer_1_TimerUDB_sT8_timerdp_u0__DP_AUX_CTL_REG, CYREG_B0_UDB11_ACTL
.set Timer_1_TimerUDB_sT8_timerdp_u0__F0_F1_REG, CYREG_B0_UDB11_F0_F1
.set Timer_1_TimerUDB_sT8_timerdp_u0__F0_REG, CYREG_B0_UDB11_F0
.set Timer_1_TimerUDB_sT8_timerdp_u0__F1_REG, CYREG_B0_UDB11_F1
.set Timer_1_TimerUDB_sT8_timerdp_u0__MSK_DP_AUX_CTL_REG, CYREG_B0_UDB11_MSK_ACTL
.set Timer_1_TimerUDB_sT8_timerdp_u0__PER_DP_AUX_CTL_REG, CYREG_B0_UDB11_MSK_ACTL

/* dialDirPin */
.set dialDirPin__0__INTTYPE, CYREG_PICU2_INTTYPE5
.set dialDirPin__0__MASK, 0x20
.set dialDirPin__0__PC, CYREG_PRT2_PC5
.set dialDirPin__0__PORT, 2
.set dialDirPin__0__SHIFT, 5
.set dialDirPin__AG, CYREG_PRT2_AG
.set dialDirPin__AMUX, CYREG_PRT2_AMUX
.set dialDirPin__BIE, CYREG_PRT2_BIE
.set dialDirPin__BIT_MASK, CYREG_PRT2_BIT_MASK
.set dialDirPin__BYP, CYREG_PRT2_BYP
.set dialDirPin__CTL, CYREG_PRT2_CTL
.set dialDirPin__DM0, CYREG_PRT2_DM0
.set dialDirPin__DM1, CYREG_PRT2_DM1
.set dialDirPin__DM2, CYREG_PRT2_DM2
.set dialDirPin__DR, CYREG_PRT2_DR
.set dialDirPin__INP_DIS, CYREG_PRT2_INP_DIS
.set dialDirPin__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU2_BASE
.set dialDirPin__LCD_COM_SEG, CYREG_PRT2_LCD_COM_SEG
.set dialDirPin__LCD_EN, CYREG_PRT2_LCD_EN
.set dialDirPin__MASK, 0x20
.set dialDirPin__PORT, 2
.set dialDirPin__PRT, CYREG_PRT2_PRT
.set dialDirPin__PRTDSI__CAPS_SEL, CYREG_PRT2_CAPS_SEL
.set dialDirPin__PRTDSI__DBL_SYNC_IN, CYREG_PRT2_DBL_SYNC_IN
.set dialDirPin__PRTDSI__OE_SEL0, CYREG_PRT2_OE_SEL0
.set dialDirPin__PRTDSI__OE_SEL1, CYREG_PRT2_OE_SEL1
.set dialDirPin__PRTDSI__OUT_SEL0, CYREG_PRT2_OUT_SEL0
.set dialDirPin__PRTDSI__OUT_SEL1, CYREG_PRT2_OUT_SEL1
.set dialDirPin__PRTDSI__SYNC_OUT, CYREG_PRT2_SYNC_OUT
.set dialDirPin__PS, CYREG_PRT2_PS
.set dialDirPin__SHIFT, 5
.set dialDirPin__SLW, CYREG_PRT2_SLW

/* fireDirPin */
.set fireDirPin__0__INTTYPE, CYREG_PICU3_INTTYPE1
.set fireDirPin__0__MASK, 0x02
.set fireDirPin__0__PC, CYREG_PRT3_PC1
.set fireDirPin__0__PORT, 3
.set fireDirPin__0__SHIFT, 1
.set fireDirPin__AG, CYREG_PRT3_AG
.set fireDirPin__AMUX, CYREG_PRT3_AMUX
.set fireDirPin__BIE, CYREG_PRT3_BIE
.set fireDirPin__BIT_MASK, CYREG_PRT3_BIT_MASK
.set fireDirPin__BYP, CYREG_PRT3_BYP
.set fireDirPin__CTL, CYREG_PRT3_CTL
.set fireDirPin__DM0, CYREG_PRT3_DM0
.set fireDirPin__DM1, CYREG_PRT3_DM1
.set fireDirPin__DM2, CYREG_PRT3_DM2
.set fireDirPin__DR, CYREG_PRT3_DR
.set fireDirPin__INP_DIS, CYREG_PRT3_INP_DIS
.set fireDirPin__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set fireDirPin__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set fireDirPin__LCD_EN, CYREG_PRT3_LCD_EN
.set fireDirPin__MASK, 0x02
.set fireDirPin__PORT, 3
.set fireDirPin__PRT, CYREG_PRT3_PRT
.set fireDirPin__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set fireDirPin__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set fireDirPin__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set fireDirPin__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set fireDirPin__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set fireDirPin__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set fireDirPin__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set fireDirPin__PS, CYREG_PRT3_PS
.set fireDirPin__SHIFT, 1
.set fireDirPin__SLW, CYREG_PRT3_SLW

/* angleDirPin */
.set angleDirPin__0__INTTYPE, CYREG_PICU1_INTTYPE7
.set angleDirPin__0__MASK, 0x80
.set angleDirPin__0__PC, CYREG_PRT1_PC7
.set angleDirPin__0__PORT, 1
.set angleDirPin__0__SHIFT, 7
.set angleDirPin__AG, CYREG_PRT1_AG
.set angleDirPin__AMUX, CYREG_PRT1_AMUX
.set angleDirPin__BIE, CYREG_PRT1_BIE
.set angleDirPin__BIT_MASK, CYREG_PRT1_BIT_MASK
.set angleDirPin__BYP, CYREG_PRT1_BYP
.set angleDirPin__CTL, CYREG_PRT1_CTL
.set angleDirPin__DM0, CYREG_PRT1_DM0
.set angleDirPin__DM1, CYREG_PRT1_DM1
.set angleDirPin__DM2, CYREG_PRT1_DM2
.set angleDirPin__DR, CYREG_PRT1_DR
.set angleDirPin__INP_DIS, CYREG_PRT1_INP_DIS
.set angleDirPin__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU1_BASE
.set angleDirPin__LCD_COM_SEG, CYREG_PRT1_LCD_COM_SEG
.set angleDirPin__LCD_EN, CYREG_PRT1_LCD_EN
.set angleDirPin__MASK, 0x80
.set angleDirPin__PORT, 1
.set angleDirPin__PRT, CYREG_PRT1_PRT
.set angleDirPin__PRTDSI__CAPS_SEL, CYREG_PRT1_CAPS_SEL
.set angleDirPin__PRTDSI__DBL_SYNC_IN, CYREG_PRT1_DBL_SYNC_IN
.set angleDirPin__PRTDSI__OE_SEL0, CYREG_PRT1_OE_SEL0
.set angleDirPin__PRTDSI__OE_SEL1, CYREG_PRT1_OE_SEL1
.set angleDirPin__PRTDSI__OUT_SEL0, CYREG_PRT1_OUT_SEL0
.set angleDirPin__PRTDSI__OUT_SEL1, CYREG_PRT1_OUT_SEL1
.set angleDirPin__PRTDSI__SYNC_OUT, CYREG_PRT1_SYNC_OUT
.set angleDirPin__PS, CYREG_PRT1_PS
.set angleDirPin__SHIFT, 7
.set angleDirPin__SLW, CYREG_PRT1_SLW

/* dialStepPin */
.set dialStepPin__0__INTTYPE, CYREG_PICU2_INTTYPE4
.set dialStepPin__0__MASK, 0x10
.set dialStepPin__0__PC, CYREG_PRT2_PC4
.set dialStepPin__0__PORT, 2
.set dialStepPin__0__SHIFT, 4
.set dialStepPin__AG, CYREG_PRT2_AG
.set dialStepPin__AMUX, CYREG_PRT2_AMUX
.set dialStepPin__BIE, CYREG_PRT2_BIE
.set dialStepPin__BIT_MASK, CYREG_PRT2_BIT_MASK
.set dialStepPin__BYP, CYREG_PRT2_BYP
.set dialStepPin__CTL, CYREG_PRT2_CTL
.set dialStepPin__DM0, CYREG_PRT2_DM0
.set dialStepPin__DM1, CYREG_PRT2_DM1
.set dialStepPin__DM2, CYREG_PRT2_DM2
.set dialStepPin__DR, CYREG_PRT2_DR
.set dialStepPin__INP_DIS, CYREG_PRT2_INP_DIS
.set dialStepPin__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU2_BASE
.set dialStepPin__LCD_COM_SEG, CYREG_PRT2_LCD_COM_SEG
.set dialStepPin__LCD_EN, CYREG_PRT2_LCD_EN
.set dialStepPin__MASK, 0x10
.set dialStepPin__PORT, 2
.set dialStepPin__PRT, CYREG_PRT2_PRT
.set dialStepPin__PRTDSI__CAPS_SEL, CYREG_PRT2_CAPS_SEL
.set dialStepPin__PRTDSI__DBL_SYNC_IN, CYREG_PRT2_DBL_SYNC_IN
.set dialStepPin__PRTDSI__OE_SEL0, CYREG_PRT2_OE_SEL0
.set dialStepPin__PRTDSI__OE_SEL1, CYREG_PRT2_OE_SEL1
.set dialStepPin__PRTDSI__OUT_SEL0, CYREG_PRT2_OUT_SEL0
.set dialStepPin__PRTDSI__OUT_SEL1, CYREG_PRT2_OUT_SEL1
.set dialStepPin__PRTDSI__SYNC_OUT, CYREG_PRT2_SYNC_OUT
.set dialStepPin__PS, CYREG_PRT2_PS
.set dialStepPin__SHIFT, 4
.set dialStepPin__SLW, CYREG_PRT2_SLW

/* fireStepPin */
.set fireStepPin__0__INTTYPE, CYREG_PICU3_INTTYPE0
.set fireStepPin__0__MASK, 0x01
.set fireStepPin__0__PC, CYREG_PRT3_PC0
.set fireStepPin__0__PORT, 3
.set fireStepPin__0__SHIFT, 0
.set fireStepPin__AG, CYREG_PRT3_AG
.set fireStepPin__AMUX, CYREG_PRT3_AMUX
.set fireStepPin__BIE, CYREG_PRT3_BIE
.set fireStepPin__BIT_MASK, CYREG_PRT3_BIT_MASK
.set fireStepPin__BYP, CYREG_PRT3_BYP
.set fireStepPin__CTL, CYREG_PRT3_CTL
.set fireStepPin__DM0, CYREG_PRT3_DM0
.set fireStepPin__DM1, CYREG_PRT3_DM1
.set fireStepPin__DM2, CYREG_PRT3_DM2
.set fireStepPin__DR, CYREG_PRT3_DR
.set fireStepPin__INP_DIS, CYREG_PRT3_INP_DIS
.set fireStepPin__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set fireStepPin__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set fireStepPin__LCD_EN, CYREG_PRT3_LCD_EN
.set fireStepPin__MASK, 0x01
.set fireStepPin__PORT, 3
.set fireStepPin__PRT, CYREG_PRT3_PRT
.set fireStepPin__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set fireStepPin__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set fireStepPin__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set fireStepPin__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set fireStepPin__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set fireStepPin__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set fireStepPin__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set fireStepPin__PS, CYREG_PRT3_PS
.set fireStepPin__SHIFT, 0
.set fireStepPin__SLW, CYREG_PRT3_SLW

/* angleStepPin */
.set angleStepPin__0__INTTYPE, CYREG_PICU1_INTTYPE6
.set angleStepPin__0__MASK, 0x40
.set angleStepPin__0__PC, CYREG_PRT1_PC6
.set angleStepPin__0__PORT, 1
.set angleStepPin__0__SHIFT, 6
.set angleStepPin__AG, CYREG_PRT1_AG
.set angleStepPin__AMUX, CYREG_PRT1_AMUX
.set angleStepPin__BIE, CYREG_PRT1_BIE
.set angleStepPin__BIT_MASK, CYREG_PRT1_BIT_MASK
.set angleStepPin__BYP, CYREG_PRT1_BYP
.set angleStepPin__CTL, CYREG_PRT1_CTL
.set angleStepPin__DM0, CYREG_PRT1_DM0
.set angleStepPin__DM1, CYREG_PRT1_DM1
.set angleStepPin__DM2, CYREG_PRT1_DM2
.set angleStepPin__DR, CYREG_PRT1_DR
.set angleStepPin__INP_DIS, CYREG_PRT1_INP_DIS
.set angleStepPin__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU1_BASE
.set angleStepPin__LCD_COM_SEG, CYREG_PRT1_LCD_COM_SEG
.set angleStepPin__LCD_EN, CYREG_PRT1_LCD_EN
.set angleStepPin__MASK, 0x40
.set angleStepPin__PORT, 1
.set angleStepPin__PRT, CYREG_PRT1_PRT
.set angleStepPin__PRTDSI__CAPS_SEL, CYREG_PRT1_CAPS_SEL
.set angleStepPin__PRTDSI__DBL_SYNC_IN, CYREG_PRT1_DBL_SYNC_IN
.set angleStepPin__PRTDSI__OE_SEL0, CYREG_PRT1_OE_SEL0
.set angleStepPin__PRTDSI__OE_SEL1, CYREG_PRT1_OE_SEL1
.set angleStepPin__PRTDSI__OUT_SEL0, CYREG_PRT1_OUT_SEL0
.set angleStepPin__PRTDSI__OUT_SEL1, CYREG_PRT1_OUT_SEL1
.set angleStepPin__PRTDSI__SYNC_OUT, CYREG_PRT1_SYNC_OUT
.set angleStepPin__PS, CYREG_PRT1_PS
.set angleStepPin__SHIFT, 6
.set angleStepPin__SLW, CYREG_PRT1_SLW

/* stepper_isr_timer */
.set stepper_isr_timer__INTC_CLR_EN_REG, CYREG_NVIC_CLRENA0
.set stepper_isr_timer__INTC_CLR_PD_REG, CYREG_NVIC_CLRPEND0
.set stepper_isr_timer__INTC_MASK, 0x01
.set stepper_isr_timer__INTC_NUMBER, 0
.set stepper_isr_timer__INTC_PRIOR_NUM, 7
.set stepper_isr_timer__INTC_PRIOR_REG, CYREG_NVIC_PRI_0
.set stepper_isr_timer__INTC_SET_EN_REG, CYREG_NVIC_SETENA0
.set stepper_isr_timer__INTC_SET_PD_REG, CYREG_NVIC_SETPEND0

/* Miscellaneous */
.set BCLK__BUS_CLK__HZ, 24000000
.set BCLK__BUS_CLK__KHZ, 24000
.set BCLK__BUS_CLK__MHZ, 24
.set CYDEV_CHIP_DIE_LEOPARD, 1
.set CYDEV_CHIP_DIE_PSOC4A, 26
.set CYDEV_CHIP_DIE_PSOC5LP, 2
.set CYDEV_CHIP_DIE_PSOC5TM, 3
.set CYDEV_CHIP_DIE_TMA4, 4
.set CYDEV_CHIP_DIE_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_FM0P, 5
.set CYDEV_CHIP_FAMILY_FM3, 6
.set CYDEV_CHIP_FAMILY_FM4, 7
.set CYDEV_CHIP_FAMILY_PSOC3, 1
.set CYDEV_CHIP_FAMILY_PSOC4, 2
.set CYDEV_CHIP_FAMILY_PSOC5, 3
.set CYDEV_CHIP_FAMILY_PSOC6, 4
.set CYDEV_CHIP_FAMILY_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_USED, CYDEV_CHIP_FAMILY_PSOC5
.set CYDEV_CHIP_JTAG_ID, 0x2E161069
.set CYDEV_CHIP_MEMBER_3A, 1
.set CYDEV_CHIP_MEMBER_4A, 26
.set CYDEV_CHIP_MEMBER_4AA, 25
.set CYDEV_CHIP_MEMBER_4AB, 30
.set CYDEV_CHIP_MEMBER_4AC, 14
.set CYDEV_CHIP_MEMBER_4AD, 15
.set CYDEV_CHIP_MEMBER_4AE, 16
.set CYDEV_CHIP_MEMBER_4D, 20
.set CYDEV_CHIP_MEMBER_4E, 6
.set CYDEV_CHIP_MEMBER_4F, 27
.set CYDEV_CHIP_MEMBER_4G, 4
.set CYDEV_CHIP_MEMBER_4H, 24
.set CYDEV_CHIP_MEMBER_4I, 32
.set CYDEV_CHIP_MEMBER_4J, 21
.set CYDEV_CHIP_MEMBER_4K, 22
.set CYDEV_CHIP_MEMBER_4L, 31
.set CYDEV_CHIP_MEMBER_4M, 29
.set CYDEV_CHIP_MEMBER_4N, 11
.set CYDEV_CHIP_MEMBER_4O, 8
.set CYDEV_CHIP_MEMBER_4P, 28
.set CYDEV_CHIP_MEMBER_4Q, 17
.set CYDEV_CHIP_MEMBER_4R, 9
.set CYDEV_CHIP_MEMBER_4S, 12
.set CYDEV_CHIP_MEMBER_4T, 10
.set CYDEV_CHIP_MEMBER_4U, 5
.set CYDEV_CHIP_MEMBER_4V, 23
.set CYDEV_CHIP_MEMBER_4W, 13
.set CYDEV_CHIP_MEMBER_4X, 7
.set CYDEV_CHIP_MEMBER_4Y, 18
.set CYDEV_CHIP_MEMBER_4Z, 19
.set CYDEV_CHIP_MEMBER_5A, 3
.set CYDEV_CHIP_MEMBER_5B, 2
.set CYDEV_CHIP_MEMBER_6A, 33
.set CYDEV_CHIP_MEMBER_FM3, 37
.set CYDEV_CHIP_MEMBER_FM4, 38
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1, 34
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2, 35
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3, 36
.set CYDEV_CHIP_MEMBER_UNKNOWN, 0
.set CYDEV_CHIP_MEMBER_USED, CYDEV_CHIP_MEMBER_5B
.set CYDEV_CHIP_DIE_EXPECT, CYDEV_CHIP_MEMBER_USED
.set CYDEV_CHIP_DIE_ACTUAL, CYDEV_CHIP_DIE_EXPECT
.set CYDEV_CHIP_REV_LEOPARD_ES1, 0
.set CYDEV_CHIP_REV_LEOPARD_ES2, 1
.set CYDEV_CHIP_REV_LEOPARD_ES3, 3
.set CYDEV_CHIP_REV_LEOPARD_PRODUCTION, 3
.set CYDEV_CHIP_REV_PSOC4A_ES0, 17
.set CYDEV_CHIP_REV_PSOC4A_PRODUCTION, 17
.set CYDEV_CHIP_REV_PSOC5LP_ES0, 0
.set CYDEV_CHIP_REV_PSOC5LP_PRODUCTION, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES0, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES1, 1
.set CYDEV_CHIP_REV_PSOC5TM_PRODUCTION, 1
.set CYDEV_CHIP_REV_TMA4_ES, 17
.set CYDEV_CHIP_REV_TMA4_ES2, 33
.set CYDEV_CHIP_REV_TMA4_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_3A_ES1, 0
.set CYDEV_CHIP_REVISION_3A_ES2, 1
.set CYDEV_CHIP_REVISION_3A_ES3, 3
.set CYDEV_CHIP_REVISION_3A_PRODUCTION, 3
.set CYDEV_CHIP_REVISION_4A_ES0, 17
.set CYDEV_CHIP_REVISION_4A_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4AA_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AB_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AC_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AD_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AE_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4D_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD, 0
.set CYDEV_CHIP_REVISION_4E_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256K, 0
.set CYDEV_CHIP_REVISION_4G_ES, 17
.set CYDEV_CHIP_REVISION_4G_ES2, 33
.set CYDEV_CHIP_REVISION_4G_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4H_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4I_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4J_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4K_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4L_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4M_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4N_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4O_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4P_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Q_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4R_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4S_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4T_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4U_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4V_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4W_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4X_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Y_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Z_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_5A_ES0, 0
.set CYDEV_CHIP_REVISION_5A_ES1, 1
.set CYDEV_CHIP_REVISION_5A_PRODUCTION, 1
.set CYDEV_CHIP_REVISION_5B_ES0, 0
.set CYDEV_CHIP_REVISION_5B_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_6A_ES, 17
.set CYDEV_CHIP_REVISION_6A_NO_UDB, 33
.set CYDEV_CHIP_REVISION_6A_PRODUCTION, 33
.set CYDEV_CHIP_REVISION_FM3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_FM4_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_USED, CYDEV_CHIP_REVISION_5B_PRODUCTION
.set CYDEV_CHIP_REV_EXPECT, CYDEV_CHIP_REVISION_USED
.set CYDEV_CONFIG_FASTBOOT_ENABLED, 1
.set CYDEV_CONFIG_UNUSED_IO_AllowButWarn, 0
.set CYDEV_CONFIG_UNUSED_IO, CYDEV_CONFIG_UNUSED_IO_AllowButWarn
.set CYDEV_CONFIG_UNUSED_IO_AllowWithInfo, 1
.set CYDEV_CONFIG_UNUSED_IO_Disallowed, 2
.set CYDEV_CONFIGURATION_COMPRESSED, 1
.set CYDEV_CONFIGURATION_DMA, 0
.set CYDEV_CONFIGURATION_ECC, 1
.set CYDEV_CONFIGURATION_IMOENABLED, CYDEV_CONFIG_FASTBOOT_ENABLED
.set CYDEV_CONFIGURATION_MODE_COMPRESSED, 0
.set CYDEV_CONFIGURATION_MODE, CYDEV_CONFIGURATION_MODE_COMPRESSED
.set CYDEV_CONFIGURATION_MODE_DMA, 2
.set CYDEV_CONFIGURATION_MODE_UNCOMPRESSED, 1
.set CYDEV_DEBUG_ENABLE_MASK, 0x20
.set CYDEV_DEBUG_ENABLE_REGISTER, CYREG_MLOGIC_DEBUG
.set CYDEV_DEBUGGING_DPS_Disable, 3
.set CYDEV_DEBUGGING_DPS_JTAG_4, 1
.set CYDEV_DEBUGGING_DPS_JTAG_5, 0
.set CYDEV_DEBUGGING_DPS_SWD, 2
.set CYDEV_DEBUGGING_DPS_SWD_SWV, 6
.set CYDEV_DEBUGGING_DPS, CYDEV_DEBUGGING_DPS_SWD_SWV
.set CYDEV_DEBUGGING_ENABLE, 1
.set CYDEV_DEBUGGING_XRES, 0
.set CYDEV_DMA_CHANNELS_AVAILABLE, 24
.set CYDEV_ECC_ENABLE, 0
.set CYDEV_HEAP_SIZE, 0x80
.set CYDEV_INSTRUCT_CACHE_ENABLED, 1
.set CYDEV_INTR_RISING, 0x00000001
.set CYDEV_IS_EXPORTING_CODE, 0
.set CYDEV_IS_IMPORTING_CODE, 0
.set CYDEV_PROJ_TYPE, 0
.set CYDEV_PROJ_TYPE_BOOTLOADER, 1
.set CYDEV_PROJ_TYPE_LAUNCHER, 5
.set CYDEV_PROJ_TYPE_LOADABLE, 2
.set CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER, 4
.set CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER, 3
.set CYDEV_PROJ_TYPE_STANDARD, 0
.set CYDEV_PROTECTION_ENABLE, 0
.set CYDEV_STACK_SIZE, 0x0800
.set CYDEV_USE_BUNDLED_CMSIS, 1
.set CYDEV_VARIABLE_VDDA, 0
.set CYDEV_VDDA_MV, 5000
.set CYDEV_VDDD_MV, 5000
.set CYDEV_VDDIO0_MV, 5000
.set CYDEV_VDDIO1_MV, 5000
.set CYDEV_VDDIO2_MV, 5000
.set CYDEV_VDDIO3_MV, 5000
.set CYDEV_VIO0_MV, 5000
.set CYDEV_VIO1_MV, 5000
.set CYDEV_VIO2_MV, 5000
.set CYDEV_VIO3_MV, 5000
.set CYIPBLOCK_ARM_CM3_VERSION, 0
.set CYIPBLOCK_P3_ANAIF_VERSION, 0
.set CYIPBLOCK_P3_CAN_VERSION, 0
.set CYIPBLOCK_P3_CAPSENSE_VERSION, 0
.set CYIPBLOCK_P3_COMP_VERSION, 0
.set CYIPBLOCK_P3_DECIMATOR_VERSION, 0
.set CYIPBLOCK_P3_DFB_VERSION, 0
.set CYIPBLOCK_P3_DMA_VERSION, 0
.set CYIPBLOCK_P3_DRQ_VERSION, 0
.set CYIPBLOCK_P3_DSM_VERSION, 0
.set CYIPBLOCK_P3_EMIF_VERSION, 0
.set CYIPBLOCK_P3_I2C_VERSION, 0
.set CYIPBLOCK_P3_LCD_VERSION, 0
.set CYIPBLOCK_P3_LPF_VERSION, 0
.set CYIPBLOCK_P3_OPAMP_VERSION, 0
.set CYIPBLOCK_P3_PM_VERSION, 0
.set CYIPBLOCK_P3_SCCT_VERSION, 0
.set CYIPBLOCK_P3_TIMER_VERSION, 0
.set CYIPBLOCK_P3_USB_VERSION, 0
.set CYIPBLOCK_P3_VIDAC_VERSION, 0
.set CYIPBLOCK_P3_VREF_VERSION, 0
.set CYIPBLOCK_S8_GPIO_VERSION, 0
.set CYIPBLOCK_S8_IRQ_VERSION, 0
.set CYIPBLOCK_S8_SAR_VERSION, 0
.set CYIPBLOCK_S8_SIO_VERSION, 0
.set CYIPBLOCK_S8_UDB_VERSION, 0
.set DMA_CHANNELS_USED__MASK0, 0x00000000
.set CYDEV_BOOTLOADER_ENABLE, 0
.endif
