/*
 * Test_Icu.h
 *
 *  Created on: 2015. 3. 23.
 *      Author: kimwayne
 */

#ifndef TEST_ICU_H_
#define TEST_ICU_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include "IfxGtm_PinMap.h"

/*******************************************************************************
* Macro & Constant Definitions
*******************************************************************************/
#define CMU_CLK_EN_Bit      0x0000AAAA // all configurable clocks are enabled

/**
 * GTM user configuration
 */
#define GTM_CMU_CLK0_FREQUENCY		(100000000.0) /* 100MHz */

/*******************************************************************************
* Typedef Declarations
*******************************************************************************/
typedef enum
{
    Gtm_Tim_Measurement_with_FallingEdge = 0,
    Gtm_Tim_Measurement_with_RisingEdge
} Icu_Tim_DslSel;

typedef enum
{
    Gtm_Tim_ActSignalLevel_Is_DSL = 0,
    Gtm_Tim_ActSignalLevel_Is_BothEdges
} Icu_Tim_IslSel;

typedef enum
{
    Gtm_Tim_FltCnt_CmuClk0 = 0,
    Gtm_Tim_FltCnt_CmuClk1 = 1,
    Gtm_Tim_FltCnt_CmuClk6 = 2,
    Gtm_Tim_FltCnt_CmuClk7 = 3
} Icu_Tim_FltCntSel;

typedef enum
{
    Gtm_Tim_ChClkSrc_CmuClk0 = 0,
    Gtm_Tim_ChClkSrc_CmuClk1,
    Gtm_Tim_ChClkSrc_CmuClk2,
    Gtm_Tim_ChClkSrc_CmuClk3,
    Gtm_Tim_ChClkSrc_CmuClk4,
    Gtm_Tim_ChClkSrc_CmuClk5,
    Gtm_Tim_ChClkSrc_CmuClk6,
    Gtm_Tim_ChClkSrc_CmuClk7
} Icu_Tim_ClkSrcSel;

typedef enum
{
    Gtm_Tim_Timeout_Disabled = 0,
    Gtm_Tim_Timeout_BothEdge_En,
    Gtm_Tim_Timeout_RisEdge_En,
    Gtm_Tim_Timeout_FallEdge_En
} Icu_Tim_TimeOutSel;


/** \brief TIM channel configuration structure
 */
typedef struct
{
	IfxGtm_Tim_GprSel GPR0_SEL;          /**< Selection for GPR0 register (rw) */
	IfxGtm_Tim_GprSel GPR1_SEL;          /**< Selection for GPR1 register (rw) */
	IfxGtm_Tim_CntsSel CNTS_SEL;         /**< Selection for CNTS register (rw) */
	Icu_Tim_DslSel DSL;               /**< Signal level control (rw) */
	Icu_Tim_IslSel ISL;               /**< Signal level control (rw) */
    boolean FLT_EN;                      /**< Filter enable for channel x (x:0...7) (rw) */
    Icu_Tim_FltCntSel FLT_CNT_FRQ;    /**< Filter counter frequency select (rw) */
    IfxGtm_Tim_FilterMode FLT_MODE_RE;   /**< Filter mode for rising edge (rw) */
    IfxGtm_Tim_FilterCounter FLT_CTR_RE; /**< Filter counter mode for rising edge (rw) */
    IfxGtm_Tim_FilterMode FLT_MODE_FE;   /**< Filter mode for falling edge (rw) */
    IfxGtm_Tim_FilterCounter FLT_CTR_FE; /**< Filter counter mode for falling edge (rw) */
    Icu_Tim_ClkSrcSel CLK_SEL;        /**< CMU clock source select for channel (rw) */
    Icu_Tim_TimeOutSel TOCTRL;        /**< Timeout control (rw) */
} Icu_ChCtrl_Reg;


/** \brief Module configuration structure
 */
typedef struct
{
	Ifx_GTM             *pGtm;          /**< \brief Pointer to GTM module registers */
	IfxGtm_Tim_Mode     TIM_MODE;       /**< TIM channel x (x:0...7) mode (rw) */
    boolean             NewVal_Irq;
    boolean             Ecnt_OFl_Irq;
    boolean             Cnt_OFl_Irq;
    boolean             Gpr_OFl_Irq;
    boolean             TimeOut_Irq;
    boolean             GlitchDet_Irq;
    IfxGtm_IrqMode      Irq_Mode;
    IfxSrc_Tos          IsrProvider;    // Trigger match interrupt service provider
    Icu_ChCtrl_Reg   *pstTimChCfg;
} Icu_TimCh_Config;


#define GTM_CLEAR_TIM_INTERRUPT (0x3FUL)

/*******************************************************************************
* External Functions for Other Modules
*******************************************************************************/
extern void GtmTim_ChCtrlConfig(Ifx_GTM_TIM_CH *pTimChCtrlReg, Icu_TimCh_Config *pTimChCfg);
extern void GtmTim_ChannelEnable(Icu_TimCh_Config *pTimChCfg, IfxGtm_Tim_TinMap  *pTimPins);
extern void GtmTim_InitConfig(Icu_TimCh_Config *pTimChCfg,IfxGtm_Tim_TinMap  *pTimPins,Ifx_Priority IsrPriority);


#endif /* TEST_ICU_H_ */
