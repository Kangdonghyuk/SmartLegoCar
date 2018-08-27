/*
 * Test_Adc.c
 *
 *  Created on: 2015. 3. 26.
 *      Author: kimwayne
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include <stdio.h>
#include "Tricore/Cpu/Std/Ifx_Types.h"
#include "Test_Adc.h"
#include <Cpu/Std/IfxCpu.h>
/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
App_VadcAutoScan VadcAutoScan; /**< \brief Demo information */

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/
void Vadc_InitConfig(IfxVadc_GroupId GroupId,App_VadcAutoScan *Vadc);
void Vadc_ChConfig(IfxVadc_GroupId GroupId, App_VadcAutoScan *VadcAutoScan);
/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
uint32 	Adc_Result_Scan[MaxModuleNum][MaxChNum]	= {{0},{0}};
const uint8 adc_ch_cfg[][MaxChNum] =
{
	  /*  { CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH10, CH11 } */
 /*G0*/   { OFF , OFF , OFF , OFF , OFF, OFF, OFF, OFF, OFF, ON , ON  , ON   },
 	  /*  { AN0, AN1, AN2, AN3, AN4, AN5, AN6, AN7, AN8, AN9, AN10, AN11 } */
 /*G1*/   { OFF , ON , ON, OFF , ON , OFF , OFF, OFF, ON , ON , OFF , OFF  }
 	  /*  { AN12, AN13, AN14, AN15, AN16, AN17, AN18, AN19, AN20, AN21, AN22, AN23 } */

};

IfxVadc_Adc_Channel       adcChannel[MaxModuleNum][MaxChNum];

/** \brief Demo init API
 *
 * This function is called from main during initialization phase
 */
void Adc_Initialization(void)
{
	 Vadc_InitConfig(IfxVadc_GroupId_0,&VadcAutoScan);
	 Vadc_ChConfig(IfxVadc_GroupId_0,&VadcAutoScan);

	 Vadc_InitConfig(IfxVadc_GroupId_1,&VadcAutoScan);
	 Vadc_ChConfig(IfxVadc_GroupId_1,&VadcAutoScan);
}



void Vadc_InitConfig(IfxVadc_GroupId GroupId,App_VadcAutoScan *Vadc){

    /* VADC Configuration */

    /* create configuration */
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    /* initialize module */
    IfxVadc_Adc_initModule(&Vadc->vadc, &adcConfig);

    /* create group config */
    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &Vadc->vadc);

    /* with group 0 */
    adcGroupConfig.groupId = GroupId;
    adcGroupConfig.master  = adcGroupConfig.groupId;

    /* enable scan source */
    adcGroupConfig.arbiter.requestSlotScanEnabled = TRUE;

    /* enable auto scan */
    adcGroupConfig.scanRequest.autoscanEnabled = TRUE;

    /* enable all gates in "always" mode (no edge detection) */
    adcGroupConfig.scanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    /* initialize the group */
    /*IfxVadc_Adc_Group adcGroup;*/    //declared globally
    IfxVadc_Adc_initGroup(&Vadc->adcGroup[GroupId], &adcGroupConfig);



}
void Vadc_ChConfig(IfxVadc_GroupId GroupId, App_VadcAutoScan *VadcAutoScan){

    volatile uint8  chnIxNum = MaxChNum;
    volatile uint32 chnIx;
    /* create channel config */
    IfxVadc_Adc_ChannelConfig adcChannelConfig[chnIxNum];


    for (chnIx = 0; chnIx < chnIxNum; ++chnIx)
    {

    	if(adc_ch_cfg[GroupId][chnIx] != OFF){
        IfxVadc_Adc_initChannelConfig(&adcChannelConfig[chnIx], &VadcAutoScan->adcGroup[GroupId]);

        adcChannelConfig[chnIx].channelId      = (IfxVadc_ChannelId)(chnIx);
        adcChannelConfig[chnIx].resultRegister = (IfxVadc_ChannelResult)(chnIx);  /* use dedicated result register */
        adcChannelConfig[chnIx].backgroundChannel = TRUE;

        /* initialize the channel */
        IfxVadc_Adc_initChannel(&adcChannel[GroupId][chnIx], &adcChannelConfig[chnIx]);

        /* add to scan */
        unsigned channels = (1 << adcChannelConfig[chnIx].channelId);
        unsigned mask     = channels;
        IfxVadc_Adc_setScan( &VadcAutoScan->adcGroup[GroupId], channels, mask);
    	}

    }

}


/** \brief Demo run API
 *
 * This function is called from main, background loop
 */
void Test_VadcAutoScan(IfxVadc_GroupId GroupId)
{
    volatile uint32  chnIx;
    volatile uint8 	chnIxNum = MaxChNum;
        /* start autoscan */
        IfxVadc_Adc_startScan(&VadcAutoScan.adcGroup[GroupId]);

        /* check results */
        for (chnIx = 0; chnIx < chnIxNum; ++chnIx)
        {

        	if(adc_ch_cfg[GroupId][chnIx] != OFF){
            unsigned     group   = adcChannel[GroupId][chnIx].group->groupId;
            unsigned     channel = adcChannel[GroupId][chnIx].channel;

            /* wait for valid result */
            Ifx_VADC_RES conversionResult;

            do
            {
                conversionResult = IfxVadc_Adc_getResult(&adcChannel[GroupId][chnIx]);
            } while (!conversionResult.B.VF);

            Adc_Result_Scan[GroupId][chnIx] = conversionResult.B.RESULT;
        	}

        }

}
