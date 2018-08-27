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
**  FILENAME  : TaskScheduler.h                                               **
**                                                                            **
**  VERSION   : 1.0.0                                                         **
**                                                                            **
**  DATE      : 2013-06-22                                                    **
**                                                                            **
**  PLATFORM  : Aurix                                                         **
**                                                                            **
**  COMPILER  : Tasking                                 		              **
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

#include "Tricore/Cpu/Std/Ifx_Types.h"
#include "Tricore/Cpu/Std/IfxCpu_Intrinsics.h"
#include "Tricore/Scu/Std/IfxScuWdt.h"
#include "IfxPort_reg.h"
#include "IfxPort.h"

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
uint8	Dio_LevelInput[4] = {0};
uint8	Dio_LevelOutput[4] ={0};

/*******************************************************************************
**                      Private  Constant Definitions                         **
*******************************************************************************/
#define LED_TEST	STD_ON
/*******************************************************************************
**                     Private  Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
void Dio_ToggleOutput(void);
void Dio_ReadOutput(void);
void Dio_ReadInput(void);
void Dio_Initialization(void);
void Dio_Configuration(Ifx_P *port, uint8 pinIndex, IfxPort_Mode Mode,IfxPort_PadDriver PadType,IfxPort_State State);

void Dio_Initialization(void){

#if(LED_TEST == STD_ON)
	//Initialization LED Port Pin on TC237 TFT-Board
	Dio_Configuration(&MODULE_P13, 0, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);
	Dio_Configuration(&MODULE_P13, 1, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);
	Dio_Configuration(&MODULE_P13, 2, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);
	Dio_Configuration(&MODULE_P13, 3, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);
#endif
	//Initialization BTN8962 INH
	Dio_Configuration(&MODULE_P02, 0, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);
	Dio_Configuration(&MODULE_P02, 2, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);
	Dio_Configuration(&MODULE_P00, 2, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);
	Dio_Configuration(&MODULE_P33, 5, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);

	P02_OUT.B.P0 = 0;
	P00_OUT.B.P2 = 0;
	P02_OUT.B.P2 = 0;
	P33_OUT.B.P5 = 0;

	//will remove
	Dio_Configuration(&MODULE_P14, 6, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_low);
	Dio_Configuration(&MODULE_P22, 0, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_low);
	Dio_Configuration(&MODULE_P22, 1, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_low);
	Dio_Configuration(&MODULE_P22, 2, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_low);
	Dio_Configuration(&MODULE_P22, 3, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_low);//Initialization servo motor
	Dio_Configuration(&MODULE_P33, 10, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_high);
	Dio_Configuration(&MODULE_P15, 6, IfxPort_Mode_outputPushPullGeneral,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_low);
	//Dio_Configuration(&MODULE_P14, 5, IfxPort_Mode_inputPullDown,IfxPort_PadDriver_cmosAutomotiveSpeed1,IfxPort_State_low);
}




//******************************************************************************
// @Function	 	void Dio_ReadOutput(void)
// @Description   	Read digital output
// @Returnvalue		None
// @Parameters    	None
//******************************************************************************
void Dio_ReadOutput(void)
{
	// Read level of all the Digital Output pins
	Dio_LevelOutput[0]= IfxPort_getPinState(&MODULE_P13, 0 );
	Dio_LevelOutput[1]= IfxPort_getPinState(&MODULE_P13, 1 );
	Dio_LevelOutput[2]= IfxPort_getPinState(&MODULE_P13, 2 );
	Dio_LevelOutput[3]= IfxPort_getPinState(&MODULE_P13, 3 );

} /* Dio_ReadOutput */

//******************************************************************************
// @Function	 	void Dio_ReadInput(void)
// @Description   	Read digital input
// @Returnvalue		None
// @Parameters    	None
//******************************************************************************
void Dio_ReadInput(void)
{
	// Read Digital Input pins
	Dio_LevelInput[0]= IfxPort_getPinState(&MODULE_P33,8       );

} /* Dio_ReadInput */


//******************************************************************************
// @Function	 	void Dio_ToggleOutput(void)
// @Description   	Toggle digital input
// @Returnvalue		None
// @Parameters    	None
//******************************************************************************

void Dio_ToggleOutput(void)
{
	IfxPort_togglePin(&MODULE_P13, 0 );
	IfxPort_togglePin(&MODULE_P13, 1 );
	IfxPort_togglePin(&MODULE_P13, 2 );
	IfxPort_togglePin(&MODULE_P13, 3 );

} /* Dio_ToggleOutput */

void Dio_Configuration(Ifx_P *port, uint8 pinIndex, IfxPort_Mode Mode,IfxPort_PadDriver PadType,IfxPort_State State)
{

	IfxPort_setPinMode(port, pinIndex, Mode);
	IfxPort_setPinPadDriver(port, pinIndex, PadType);
	IfxPort_setPinState(port, pinIndex, State);

}


