/*
 *	Test_Uart.c
 *
 *	Created on: 2017. 4. 3.
 *		Author: Lee Henry
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "Tricore/Cpu/Std/IfxCpu_Intrinsics.h"

#include "Test_Uart.h"
#include "Test_Irq.h"

/******************************************************************************/
/*-----------------------------------Macros 매크로-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations 열거형--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures 데이터 구조--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables 전역 변수------------------------------*/
/******************************************************************************/

App_AsclinAsc g_AsclinAsc; /**< \brief Demo information @간단한 데모정보*/

/******************************************************************************/
/*-------------------------Function Prototypes @기능의 프로토타입--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Demo_AsclinAsc_SrcDoc_Main_Interrupt
 * \{ */

/** \name Interrupts for Transmit @전송을 위한 이름 인터럽트
 * \{ */

/// 하드웨어의 신호를 소프트웨어에게 보내줌 똑같은 기능을 하는건 CAn통신이라는게 잇음

IFX_INTERRUPT(asclin0TxISR, 0, ISR_PRIORITY_ASCLIN0_TX);
void asclin0TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_AsclinAsc.drivers.asc0);
	g_AsclinAsc.TxComplete++;
}

/** \} */

/** \name Interrupts for Receive
 * \{ */

IFX_INTERRUPT(asclin0RxISR, 0, ISR_PRIORITY_ASCLIN0_RX);
void asclin0RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_AsclinAsc.drivers.asc0);
    g_AsclinAsc.RxComplete++;
}

void Uart_Initialization(void)
{
	 /* disable interrupts */
	boolean              interruptState = IfxCpu_disableInterrupts();

	/* create module config */
	IfxAsclin_Asc_Config ascConfig;
	IfxAsclin_Asc_initModuleConfig(&ascConfig, &MODULE_ASCLIN0);

	/* set the desired baudrate */
	ascConfig.baudrate.prescaler    = 1;
	ascConfig.baudrate.baudrate     = 115200; /* FDR values will be calculated in initModule */
	ascConfig.baudrate.oversampling = IfxAsclin_OversamplingFactor_4;

	/* ISR priorities and interrupt target */
	ascConfig.interrupt.txPriority    = ISR_PRIORITY_ASCLIN0_TX;
	ascConfig.interrupt.rxPriority    = ISR_PRIORITY_ASCLIN0_RX;
//	ascConfig.interrupt.erPriority    = ISR_PRIORITY_ASCLIN1_ER;
	ascConfig.interrupt.typeOfService = (IfxSrc_Tos)IfxCpu_getCoreIndex();

	/* FIFO configuration */
	ascConfig.txBuffer     = g_AsclinAsc.ascBuffer.tx;
	ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;

	ascConfig.rxBuffer     = g_AsclinAsc.ascBuffer.rx;
	ascConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;

	/* pin configuration */
	const IfxAsclin_Asc_Pins pins = {
		NULL_PTR,					IfxPort_InputMode_pullUp,        /* CTS pin not used */
		&IfxAsclin0_RXA_P14_1_IN, 	IfxPort_InputMode_pullUp,        /* Rx pin */
		NULL_PTR,					IfxPort_OutputMode_pushPull,     /* RTS pin not used */
		&IfxAsclin0_TX_P14_0_OUT,	IfxPort_OutputMode_pushPull,     /* Tx pin */
		IfxPort_PadDriver_cmosAutomotiveSpeed1
	};
	ascConfig.pins = &pins;

	/* initialize module */
	IfxAsclin_Asc_initModule(&g_AsclinAsc.drivers.asc0, &ascConfig);

	/* enable interrupts again */
	IfxCpu_restoreInterrupts(interruptState);
}

void Uart_TEST(void)
{
	uint32 i;

	g_AsclinAsc.count = UART_TEST_DATA_SIZE;

	for (i=0; i<UART_TEST_DATA_SIZE; ++i)
	{
		g_AsclinAsc.txData[i] = i + '0';
		g_AsclinAsc.rxData[i] = 0;
	}

	IfxAsclin_Asc_write(&g_AsclinAsc.drivers.asc0, g_AsclinAsc.txData, &g_AsclinAsc.count, TIME_INFINITE);

//	IfxAsclin_Asc_read(&g_AsclinAsc.drivers.asc0, g_AsclinAsc.rxData, &g_AsclinAsc.count, 0xFF);
}
