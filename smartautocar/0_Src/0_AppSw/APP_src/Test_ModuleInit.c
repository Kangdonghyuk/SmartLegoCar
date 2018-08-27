/*
 * Test_ModuleInit.c
 *
 *  Created on: 2015. 3. 19.
 *      Author: kimwayne
 */


/* \brief Template file for Test_ModuleInit.c
 *
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */

/*******************************************************************************
* Includes
*******************************************************************************/
#include "Test_ModuleInit.h"

/*******************************************************************************
* Global Function Prototype Declarations
*******************************************************************************/
void Test_ModuleInit(void);

/*******************************************************************************
* Local Function Prototype Declarations
*******************************************************************************/


/*******************************************************************************
* Global Variable Declarations
*******************************************************************************/


/*******************************************************************************
* Global Function Start
*******************************************************************************/


void Test_ModuleInit(void)
{

    /* Initialize the peripherals for this demo App */
    TLF35584Demo_Init();
	Dio_Initialization(); 					/* Initialize Dio 		  */
	Adc_Initialization();           		/* Initialization Adc     */
	Uart_Initialization();                  /* Initialization Uart  */

	SecondTimer_Initialization();
	Icu_Initialization();
	Pwm_Initialization();           		/* Initialization Pwm     */

	///////////////////////////////////

	Encoder_Initialization();
	Camera_Initialization();

	///////////////////////////////////
}
