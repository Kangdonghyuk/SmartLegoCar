/**
 * \file Cpu0_Main.c
 * \brief Main function definition for Cpu core 0 .
 *
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
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
 *
 */

#include "Tricore/Cpu/Std/Ifx_Types.h"
#include "Tricore/Cpu/Std/IfxCpu_Intrinsics.h"
#include "Tricore/Scu/Std/IfxScuWdt.h"
#include <Stm/Std/IfxStm.h>
#include <Port/Std/IfxPort.h>
#include "Test_Irq.h"
#include "Test_ModuleInit.h"
#include "Test_Pwm.h"
#include "Test_Adc.h"
#include "TLF35584Demo.h"
#include "Sensor.h"

#include "Test_Encoder.h"
#include "Test_Camera.h"
#include "Test_Uart.h"

#include "UserDefine.h"

#define CENTER          633
#define LEFT            528
#define RIGHT           720
#define MS				100000

void ControlSpeed();
void ControlSchool();
void AvoidObstacle();

enum AREA nowArea = E_READY;
enum DIRECTION willDirection = E_NONE;

bool isDetectingSchoolLine = true;
int cntDetectingShoolLine = 0;
bool isAvoidingObstacle = false;
int cntAvoidingObstacle = 0;
int cntReady = 3;

int obsstate = 0;
uint16 servo = 0;
int test_servo = 64;
int cnt_servo = 0;
int test_prev_servo = 64;
int Obstacle_flag = 0;

int _dash = 0;
int before = 0;
int obscnt=0;
int isBackPWM;

double nowPid;

void FrontControl(uint16 Angle){
	Pwm_StepDutyUpdate(IfxGtm_TOM1_0_TOUT32_P33_10_OUT,Angle);
}
void CarRuning(uint16 Speed,uint16 Direction){
	Pwm_MotorDutyAndDirectionControl(Speed, Direction);
}

void SecondTimer_Initialization(void)
{
    //volatile float       stm_freq;
    Ifx_STM             *stm = &MODULE_STM0;
    IfxStm_CompareConfig stmCompareConfig;
    IfxStm_enableOcdsSuspend(stm);
    //stm_freq = IfxScuCcu_getStmFrequency();
    IfxStm_initCompareConfig(&stmCompareConfig);
	stmCompareConfig.triggerPriority = ISR_PRIORITY_STM;
	stmCompareConfig.ticks = 1000 * MS;
	stmCompareConfig.typeOfService = IfxSrc_Tos_cpu0;
    IfxStm_initCompare(stm, &stmCompareConfig);
}

IFX_INTERRUPT (SecondTimer_Isr, 0, ISR_PRIORITY_STM);
void SecondTimer_Isr(void)
{
    Ifx_STM *stm = &MODULE_STM0;
    IfxStm_updateCompare(stm, IfxStm_Comparator_0, IfxStm_getLower(stm) + 1000 * MS);

    if(cntDetectingShoolLine >= 1 && isDetectingSchoolLine == 0) {
    	cntDetectingShoolLine -= 1;
    	if(cntDetectingShoolLine == 0)
    		isDetectingSchoolLine = 1;
    }

    if(cntReady >= 1 && nowArea == E_READY) {
    	cntReady -= 1;
    	if(cntReady == 0)
    		nowArea = E_SPEED;
    }

    __enable();
}

void core0_main (void)
{
	int i, j, temp;
    __enable ();
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());
    IfxScuWdt_disableSafetyWatchdog (IfxScuWdt_getSafetyWatchdogPassword ());
    Test_ModuleInit();
    Delay_ms(2000);
    cntReady = 3;
    isDetectingSchoolLine = 1;
    isBackPWM = 0;
    nowPid = 0;

	FrontControl(CENTER);

    while (1)
    {
    	UpdateSensor(); // 센서 감지
    	//Obstacle_flag = IsObstacle(); // 언덕 장애물 구분
    	test_servo = GetCameraCenter();
    	if(test_servo <= 0 || test_servo >= 200)
    		test_servo = test_prev_servo;

    	if(nowArea == E_READY) {

    	}

    	else if(nowArea == E_SPEED) ControlSpeed();
    	else if(nowArea == E_SCHOOL) ControlSchool();
    	else if(nowArea == E_STOP) {
        	//PID(get_encoder(), 1.1);
    	}


    	if(isDetectingSchoolLine == 1 && (nowArea == E_SPEED || nowArea == E_SCHOOL)) {
    		if(IsSchoolLine() == 1) {
    			cntDetectingShoolLine = 5;
    			isDetectingSchoolLine = 0;
    			if(nowArea == E_SPEED) {
    				//nowArea = E_SCHOOL;
    				EnterSchoolArea();
    			}
    			else if(nowArea == E_SCHOOL) {
    				//nowArea = E_SPEED;
    			}
    		}
   		}
    }
}

int __abs__(int n) {
	if(n < 0)
		return -n;
	return n;
}

void ControlServoSpeed() {

		nowPid = 1.5;
		if(test_servo >= 75 || test_servo<=60){ // 넘어가는 경우
			nowPid = 0.8;

			if(__abs__(test_servo - test_prev_servo) >= 30) {
				cnt_servo+=1;
				if(cnt_servo >= 5) {
					test_prev_servo = test_servo;
					cnt_servo = 0;
				}
				test_servo = test_prev_servo;
			}
			else
				cnt_servo = 0;

			if(test_servo <= 60)
				servo = 633+(2) * ((test_servo) - 67);
			else if(test_servo >= 75) {
				servo = 633+(2) * ((test_servo) - 67);
			}

			cntDetectingShoolLine = 2;
			isDetectingSchoolLine = 0;

			if(servo<488)		servo=488;
			else if(servo>732)	servo=732;

			test_prev_servo = test_servo;
		}
		else{
			servo = 633+(2)*((test_servo)-67);
			if(servo<488)		servo=488;
			else if(servo>732)	servo=732;
		}

		PID(get_encoder(), nowPid);
		FrontControl(servo);
		before = servo;
}

void ControlServoSchool(){
	servo = 633+2*((test_servo)-64);
}

void ControlSpeed() {

	if(Obstacle_flag==2){
		if(isBackPWM == 0) {
			CarRuning(1000, 1);
			isBackPWM = 1;
		}
		 CarRuning(0,1);
	}
	else{
		isBackPWM = 0;
		ControlServoSpeed();
	}
}

void ControlSchool() {
	ControlServoSchool();
  	AvoidObstacle();
    FrontControl(servo);
	PID(get_encoder(), 0.8);
}


void AvoidObstacle() {
	if(Obstacle_flag == 2){
		obsstate=1;
    	cntDetectingShoolLine = 3;
    	isDetectingSchoolLine = 0;
	}
	if(obsstate==1){
		if(_dash == 0){
			_dash = GetCameraDash();
		}
		else if(_dash == -1){

			if(0<=obscnt && obscnt<=150){
				servo = 528;
				obscnt++;
			}
			else if(150<obscnt && obscnt<=250){
				servo = 720;
				obscnt++;
			}
			else if(obscnt>210){
				obscnt=0;
				obsstate=0;
				_dash = 1;
			}
		}
		else if(_dash == 1){

			if(0<=obscnt && obscnt<=205){
				servo = 720;
				obscnt++;
			}
			else if(205<obscnt && obscnt<=265){
				servo = 528;
				obscnt++;
			}
			else if(obscnt>265){
				obscnt=0;
				obsstate=0;
				_dash = -1;
			}

		}
	}
}



