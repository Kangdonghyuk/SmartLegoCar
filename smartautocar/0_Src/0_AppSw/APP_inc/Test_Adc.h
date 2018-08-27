/*
 * Test_Adc.h
 *
 *  Created on: 2015. 3. 26.
 *      Author: kimwayne
 */

#ifndef TEST_ADC_H_
#define TEST_ADC_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include <Vadc/Std/IfxVadc.h>
#include <Vadc/Adc/IfxVadc_Adc.h>

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
#define MaxChNum            (12U)
#define MaxModuleNum        (2U)

typedef struct
{
    IfxVadc_Adc vadc; /* VADC handle */
    IfxVadc_Adc_Group adcGroup[MaxModuleNum];
} App_VadcAutoScan;



#define ON  1
#define OFF 0

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
IFX_EXTERN App_VadcAutoScan VadcAutoScan;
IFX_EXTERN uint32 Adc_Result_Scan[MaxModuleNum][MaxChNum];

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

IFX_EXTERN void Test_VadcAutoScan(IfxVadc_GroupId GroupId);

#endif /* TEST_ADC_H_ */
