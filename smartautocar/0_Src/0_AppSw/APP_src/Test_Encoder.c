/*
 * Test_Encoder.c
 *
 */
#include "IfxGtm_tim.h"
#include "IfxGtm_PinMap.h"
#include "Test_Encoder.h"
#include "Test_Pwm.h"
#include "IfxPort.h"
#include "IfxGtm_Cmu.h"
#include "IfxPort_reg.h"
#include "IFxStm_reg.h"
#include "Test_Irq.h"

double PID_PWM = 0;
uint32 bfencoder=0;
uint32 encoder=0;
double current=0;

double Kp = 0.7 * 1.6;
double Ki = 0.14 * 1.6;
double Kd = 0.3 * 1.6;


/*double Kp = 0.525663009005757;
double Ki = 5.10529692127834;
double Kd = -0.0103472846844158;
*/

sint16 dc_duty;
double dt = 0.01;
double err, prev_err=0;  // ����. ���� ����
double I_err=0, D_err;    // ��������. �����̺�
double Kp_term, Ki_term, Kd_term;   // p��, i��, d��
uint8 ecstack=0;

IfxGtm_Tom_Timer Timer;
Ifx_GTM_TIM *tiem = &MODULE_GTM.TIM[0];
int state = 0;

int encount = 0;
int enarr[10000];
int dutyarr[10000];
int i = 0;

uint32 get_encoder(void)
{
	return encoder;
}

void Encoder_Initialization(void)
{
	/* GTM TOM configuration */
	IfxGtm_Tom_Timer_Config timerConfig;
	//IfxGtm_Tom_Timer timer;
	//App_GtmTomTimer timer;
	IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
	timerConfig.base.frequency       = 50;
	timerConfig.base.isrPriority     = ISR_PRIORITY_ENCODER;
	timerConfig.base.isrProvider     = 0;
	timerConfig.base.minResolution   = (1.0 / timerConfig.base.frequency) / 1000;
	timerConfig.base.trigger.enabled = FALSE;

	timerConfig.tom                  = IfxGtm_Tom_1;
	timerConfig.timerChannel         = IfxGtm_Tom_Ch_5;
	timerConfig.clock                = IfxGtm_Cmu_Fxclk_4;

	IfxGtm_Tom_Timer_init(&Timer, &timerConfig);
	GTM_TOM1_CH5_SR0.B.SR0 = 1000;
	IfxGtm_Tom_Timer_run(&Timer);
	IfxGtm_PinMap_setTimTin(&IfxGtm_TIM0_0_TIN77_P15_6_IN, IfxPort_InputMode_pullUp);
	tiem->CH0.CTRL.B.TIM_MODE 			= IfxGtm_Tim_Mode_inputEvent;
	tiem->CH0.CTRL.B.DSL				= 1;
	tiem->CH0.CTRL.B.ISL				= 0;
	tiem->CH0.CTRL.B.TIM_EN 			= 1;
	tiem->CH0.CTRL.B.CICTRL	 			= 0;
	tiem->CH0.IRQ_EN.B.NEWVAL_IRQ_EN	= 0;
}


void PID(uint16 encodercheck, double goal) // ���簪 , ��ǥġ
{
	//double dt = 0.01;
	//double err, prev_err=0;  // ����. ���� ����
//	double I_err=0, D_err;    // ��������. �����̺�
//	double Kp_term, Ki_term, Kd_term;   // p��, i��, d��


	current = encodercheck/(1.6*21.0*15);
	//current = encodercheck/(21.0*15);

	err = goal - current;   // ���� = ��ǥġ-���簪
	Kp_term = Kp * err;         // p�� = Kp*����

	I_err = err * dt;             // �������� += ����*dt
	Ki_term = Ki * I_err;        // i�� = Ki*��������

	D_err = (err-prev_err)/dt;  // �����̺� = (�������-��������)/dt
	Kd_term = Kd * D_err;      // d�� = Kd*�����̺�

	prev_err = err;   // ��������� ����������

	PID_PWM = (Kp_term + Ki_term + Kd_term);  // ��� = p��+i��+d��

	dc_duty += PID_PWM*10;
	//dc_duty += PID_PWM*27;
	if (dc_duty >= 2000)	dc_duty = 2000;


	if (dc_duty<0) {
		dc_duty = -dc_duty;
		Pwm_MotorDutyAndDirectionControl(dc_duty,0);
	}
	else Pwm_MotorDutyAndDirectionControl(dc_duty,1);


}

IFX_INTERRUPT (encoder_tick, 0, ISR_PRIORITY_ENCODER);
void encoder_tick(void)
{
	state+=1;
	encoder = (uint32)(tiem->CH0.CNT.U-bfencoder+8388607)%8388607;

	/*if(i<10000){
	enarr[i] = encoder/15;
	dutyarr[i] = duty;
	i++;
	}*/


	bfencoder = (uint32)tiem->CH0.CNT.U;
	IfxGtm_Tom_Timer_acknowledgeTimerIrq(&Timer);
	__enable();

}

