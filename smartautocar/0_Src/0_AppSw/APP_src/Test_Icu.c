// ------------------------------------- DISCLAIMER -----------------------------------------//
// THE INFORMATION GIVEN IN THE DOCUMENTS (APPLICATION NOTE, SOFTWARE PROGRAM ETC.)
// IS GIVEN AS A HINT FOR THE IMPLEMENTATION OF THE INFINEON TECHNOLOGIES COMPONENT ONLY
// AND SHALL NOT BE REGARDED AS ANY DESCRIPTION OR WARRANTY OF A CERTAIN FUNCTIONALITY,
// CONDITION OR QUALITY OF THE INFINEON TECHNOLOGIES COMPONENT.
// YOU MUST VERIFY ANY FUNCTION DESCRIBED IN THE DOCUMENTS IN THE REAL APPLICATION.
// INFINEON TECHNOLOGIES AG HEREBY DISCLAIMS ANY AND ALL WARRANTIES AND LIABILITIES OF ANY KIND
// (INCLUDING WITHOUT LIMITATION WARRANTIES OF NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS
// OF ANY THIRD PARTY) WITH RESPECT TO ANY AND ALL INFORMATION GIVEN IN THE DOCUMENTS.
// ------------------------------------------------ -----------------------------------------//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2013)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Test_Icu.c                                                    **
**                                                                            **
**  VERSION   : 0.0.1                                                         **
**                                                                            **
**  DATE      : 2013-08-14                                                    **
**                                                                            **
**  VARIANT   : VariantPB                                                     **
**                                                                            **
**  PLATFORM  : Aurix                                                         **
**                                                                            **
**  COMPILER  : Tasking				                                          **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : This file contains                                         **
**                                                                            **
**  SPECIFICATION(S) :                                                        **
**                                                                            **
**  MAY BE CHANGED BY USER [Yes/No]: Yes                                      **
*******************************************************************************/
/*******************************************************************************
**                      Author(s) Identity                                    **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
**	SHW			Sung Hoon, Wayne     										  **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IfxGtm_reg.h"
#include "IfxGtm_tim.h"
#include "Test_Icu.h"
#include <stdio.h>
#include <Ifx_Types.h>
#include <Cpu/Std/Platform_Types.h>
#include "Test_Irq.h"

/*******************************************************************************
**            			Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private  Constant Definitions                         **
*******************************************************************************/

/*******************************************************************************
**                     Private  Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
void Icu_Initialization(void);

void GtmTim_InitConfig(Icu_TimCh_Config *pTimChCfg,IfxGtm_Tim_TinMap  *pTimPins,Ifx_Priority IsrPriority);
void GtmTim_ChCtrlConfig(Ifx_GTM_TIM_CH *pTimChCtrlReg, Icu_TimCh_Config *pTimChCfg);
void GtmTim_ChannelEnable(Icu_TimCh_Config *pTimChCfg, IfxGtm_Tim_TinMap  *pTimPins);


uint16							Icu_NotificationCount[4]={0};

/* TIM channel control register setting */
Icu_ChCtrl_Reg stTim0Ch0_CtrlReg =
{
	.GPR0_SEL   = IfxGtm_Tim_GprSel_tbuTs0,
	.GPR1_SEL   = IfxGtm_Tim_GprSel_tbuTs0,
	.CNTS_SEL   = IfxGtm_Tim_CntsSel_cntReg,
	.DSL        = Gtm_Tim_Measurement_with_RisingEdge,
	.ISL        = Gtm_Tim_ActSignalLevel_Is_BothEdges,
	.FLT_EN     = FALSE,
	.FLT_CNT_FRQ= 0,
	.FLT_MODE_RE= 0,
	.FLT_CTR_RE = 0,
	.FLT_MODE_FE= 0,
	.FLT_CTR_FE = 0,
	.CLK_SEL    = Gtm_Tim_ChClkSrc_CmuClk0,
	.TOCTRL     = Gtm_Tim_Timeout_Disabled
};

/* TIM channel configuration */
Icu_TimCh_Config  stIcu_Config =
{
	.pGtm         = &MODULE_GTM,
	.TIM_MODE     = IfxGtm_Tim_Mode_inputEvent,
	.NewVal_Irq   = TRUE,
	.Ecnt_OFl_Irq = FALSE,
	.Cnt_OFl_Irq  = FALSE,
	.Gpr_OFl_Irq  = FALSE,
	.TimeOut_Irq  = FALSE,
	.GlitchDet_Irq= FALSE,
	.Irq_Mode     = IfxGtm_IrqMode_pulseNotify,
    .IsrProvider  = IfxSrc_Tos_cpu0,
    .pstTimChCfg  = &stTim0Ch0_CtrlReg

};

//*********************************************************************************************
// @Function	 	void Icu_Initialization(void)
// @Description   	Initialize Input Capture
// @Returnvalue		None
// @Parameters    	None
//*********************************************************************************************
void Icu_Initialization(void)
{
	/*****************************/
	/* GTM Module initialization */
	/*****************************/

    	IfxGtm_enable(&MODULE_GTM);


	/**************************************************************
	 * CMU initialization : All configurable clocks will be enabled
	 *  - Global clock dividers(Num,Den) will be left unchanged. (divide by 1)
	 ***************************************************************/

//     IF you do not use other Module of GTM, you must Need ICU clock Enable.  Wayne
    	/* frequency must be set before clock is enabled */
//    	IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, GTM_CMU_CLK0_FREQUENCY);
//    	IfxGtm_Cmu_enableClocks(&MODULE_GTM, CMU_CLK_EN_Bit);


	/**********************/
	/* TBU initialization */
	/**********************/
    /* Step.1 configure TBU channels first
	 * Other TBU registers are left unchanged
	 *  1) TBU channels uses lower counter bits (bit 0 to 23)
	 *  2) CMU_CLK0 is selected as clock source of TBU channels
	 *  3) All channels are free-running mode
	 * */

        IfxGtm_Tbu_enableChannel(&MODULE_GTM, IfxGtm_Tbu_Ts_0);
        IfxGtm_Tbu_enableChannel(&MODULE_GTM, IfxGtm_Tbu_Ts_1);
        IfxGtm_Tbu_enableChannel(&MODULE_GTM, IfxGtm_Tbu_Ts_2);

	/**********************/
	/* TIM initialization */
    /**********************/

    /* Tim Channel configuration */
    GtmTim_InitConfig(&stIcu_Config, &IfxGtm_TIM0_0_TIN34_P33_12_IN	  ,ISR_PRIORITY_GTM_TIM0_0_ICU);
    GtmTim_InitConfig(&stIcu_Config, &IfxGtm_TIM0_1_TIN27_P33_5_IN   ,ISR_PRIORITY_GTM_TIM0_1_ICU);
    GtmTim_InitConfig(&stIcu_Config, &IfxGtm_TIM0_2_TIN33_P33_11_IN   ,ISR_PRIORITY_GTM_TIM0_2_ICU);
    GtmTim_InitConfig(&stIcu_Config, &IfxGtm_TIM0_6_TIN24_P33_2_IN  ,ISR_PRIORITY_GTM_TIM0_6_ICU);

    /* Enable channel */
    GtmTim_ChannelEnable(&stIcu_Config, &IfxGtm_TIM0_0_TIN34_P33_12_IN	 );
    GtmTim_ChannelEnable(&stIcu_Config, &IfxGtm_TIM0_1_TIN27_P33_5_IN   );
    GtmTim_ChannelEnable(&stIcu_Config, &IfxGtm_TIM0_2_TIN33_P33_11_IN   );
    GtmTim_ChannelEnable(&stIcu_Config, &IfxGtm_TIM0_6_TIN24_P33_2_IN  );

} /* Icu_Initialization */

/*******************************************************************************
* Local Function Start
*******************************************************************************/


/**
 * \brief  TIM channel control register configuration
 * \param  Ifx_GTM_TIM_CH - TIM channel CTRL register pointer
 *         Icu_TimCh_Config - user configuration
 * \return void
 */
void GtmTim_ChCtrlConfig(Ifx_GTM_TIM_CH *pTimChCtrlReg, Icu_TimCh_Config *pTimChCfg)
{
	pTimChCtrlReg->CTRL.B.TIM_MODE   = pTimChCfg->TIM_MODE;
	pTimChCtrlReg->CTRL.B.GPR0_SEL   = pTimChCfg->pstTimChCfg->GPR0_SEL;
	pTimChCtrlReg->CTRL.B.GPR1_SEL   = pTimChCfg->pstTimChCfg->GPR1_SEL;
	pTimChCtrlReg->CTRL.B.CNTS_SEL   = pTimChCfg->pstTimChCfg->CNTS_SEL;
	pTimChCtrlReg->CTRL.B.DSL        = pTimChCfg->pstTimChCfg->DSL;
	pTimChCtrlReg->CTRL.B.ISL        = pTimChCfg->pstTimChCfg->ISL;
	pTimChCtrlReg->CTRL.B.FLT_EN     = pTimChCfg->pstTimChCfg->FLT_EN;
	pTimChCtrlReg->CTRL.B.FLT_CNT_FRQ= pTimChCfg->pstTimChCfg->FLT_CNT_FRQ;
	pTimChCtrlReg->CTRL.B.FLT_MODE_RE= pTimChCfg->pstTimChCfg->FLT_MODE_RE;
	pTimChCtrlReg->CTRL.B.FLT_CTR_RE = pTimChCfg->pstTimChCfg->FLT_CTR_RE;
	pTimChCtrlReg->CTRL.B.FLT_MODE_FE= pTimChCfg->pstTimChCfg->FLT_MODE_FE;
	pTimChCtrlReg->CTRL.B.FLT_CTR_FE = pTimChCfg->pstTimChCfg->FLT_CTR_FE;
	pTimChCtrlReg->CTRL.B.CLK_SEL    = pTimChCfg->pstTimChCfg->CLK_SEL;
	pTimChCtrlReg->CTRL.B.TOCTRL     = pTimChCfg->pstTimChCfg->TOCTRL;
}

/**
 * \brief  TIM channel interrupt configuration
 * \param  Icu_TimCh_Config - user configuration
 * \return void
 */
void GtmTim_InitConfig(Icu_TimCh_Config *pTimChCfg, IfxGtm_Tim_TinMap  *pTimPins,Ifx_Priority IsrPriority)
{
	Ifx_GTM_TIM_CH *pTimChReg;


	/* find channel register pointer */
	pTimChReg  = (Ifx_GTM_TIM_CH *)((uint32)&pTimChCfg->pGtm->TIM[pTimPins->tim].CH0+ ((0x80) * (pTimPins->channel)));

	/* config channel control register */
	GtmTim_ChCtrlConfig(pTimChReg, pTimChCfg);

	/* config pin mapping */
	IfxGtm_PinMap_setTimTin(pTimPins, IfxPort_InputMode_noPullDevice);

	/* find channel register pointer */
	pTimChReg  = (Ifx_GTM_TIM_CH *)((uint32)&pTimChCfg->pGtm->TIM[pTimPins->tim].CH0 + (0x80 *pTimPins->channel));

    /* configure interrupt enable bits */
	pTimChReg->IRQ_EN.B.CNTOFL_IRQ_EN    = pTimChCfg->Cnt_OFl_Irq;
	pTimChReg->IRQ_EN.B.NEWVAL_IRQ_EN    = pTimChCfg->NewVal_Irq;
	pTimChReg->IRQ_EN.B.ECNTOFL_IRQ_EN   = pTimChCfg->Ecnt_OFl_Irq;
	pTimChReg->IRQ_EN.B.CNTOFL_IRQ_EN    = pTimChCfg->Cnt_OFl_Irq;
	//pTimChReg->IRQ_EN.B.GPROFL_IRQ_EN    = pTimChCfg->Gpr_OFl_Irq;
	pTimChReg->IRQ_EN.B.TODET_IRQ_EN     = pTimChCfg->TimeOut_Irq;
	pTimChReg->IRQ_EN.B.GLITCHDET_IRQ_EN = pTimChCfg->GlitchDet_Irq;

    /* configure IRQ mode */
	pTimChReg->IRQ_MODE.B.IRQ_MODE       = pTimChCfg->Irq_Mode;

	/* Enable INT SRC */
	if(pTimChReg->IRQ_EN.U)
    {
		volatile Ifx_SRC_SRCR *src;
	    src = &MODULE_SRC.GTM.GTM[0].TIM[pTimPins->tim][pTimPins->channel];

		IfxSrc_init(src, pTimChCfg->IsrProvider, IsrPriority);
		IfxSrc_enable(src);
    }
}

/**
 * \brief  TIM channel enable
 * \param  Icu_TimCh_Config - user configuration
 * \return void
 */
void GtmTim_ChannelEnable(Icu_TimCh_Config *pTimChCfg, IfxGtm_Tim_TinMap  *pTimPins)
{
	Ifx_GTM_TIM_CH *pTimCh;

	/* find channel register pointer */
	pTimCh  = (Ifx_GTM_TIM_CH *)((uint32)&pTimChCfg->pGtm->TIM[pTimPins->tim].CH0+(0x80 * pTimPins->channel));

	/* enable TIM channel */
	pTimCh->CTRL.B.TIM_EN = 1;
}


/**
 * \brief        This interrupt is raised by the TIM channel
 * \isrProvider  ISR_PROVIDER_GTM_ICU
 * \isrPriority  ISR_PRIORITY_GTM_TIM_ICU
 */
IFX_INTERRUPT (Icu_GtmTim0_Ch0, 0, ISR_PRIORITY_GTM_TIM0_0_ICU);
void Icu_GtmTim0_Ch0(void)
{
	Icu_NotificationCount[0]++;
   /* Clear the Notify for receiving new interrupt requests */
    GTM_TIM0_CH0_IRQ_NOTIFY.U = GTM_CLEAR_TIM_INTERRUPT;
}

/**
 * \brief        This interrupt is raised by the TIM channel
 * \isrProvider  ISR_PROVIDER_GTM_ICU
 * \isrPriority  ISR_PRIORITY_GTM_TIM_ICU
 */
IFX_INTERRUPT (Icu_GtmTim0_Ch1, 0, ISR_PRIORITY_GTM_TIM0_1_ICU);
void Icu_GtmTim0_Ch1(void)
{
	Icu_NotificationCount[1]++;
   /* Clear the Notify for receiving new interrupt requests */
    GTM_TIM0_CH1_IRQ_NOTIFY.U = GTM_CLEAR_TIM_INTERRUPT;
}
/**
 * \brief        This interrupt is raised by the TIM channel
 * \isrProvider  ISR_PROVIDER_GTM_ICU
 * \isrPriority  ISR_PRIORITY_GTM_TIM_ICU
 */
IFX_INTERRUPT (Icu_GtmTim0_Ch2, 0, ISR_PRIORITY_GTM_TIM0_2_ICU);
void Icu_GtmTim0_Ch2(void)
{
	Icu_NotificationCount[2]++;
   /* Clear the Notify for receiving new interrupt requests */
    GTM_TIM0_CH2_IRQ_NOTIFY.U = GTM_CLEAR_TIM_INTERRUPT;
}
/**
 * \brief        This interrupt is raised by the TIM channel
 * \isrProvider  ISR_PROVIDER_GTM_ICU
 * \isrPriority  ISR_PRIORITY_GTM_TIM_ICU
 */
IFX_INTERRUPT (Icu_GtmTim0_Ch6, 0, ISR_PRIORITY_GTM_TIM0_6_ICU);
void Icu_GtmTim0_Ch6(void)
{
	Icu_NotificationCount[3]++;
   /* Clear the Notify for receiving new interrupt requests */
    GTM_TIM0_CH6_IRQ_NOTIFY.U = GTM_CLEAR_TIM_INTERRUPT;
}
