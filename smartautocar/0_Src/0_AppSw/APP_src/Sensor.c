/*
 * Sensor.c
 *
 *  Created on: 2018. 6. 27.
 *      Author: Keith_Lee
 */

#include "Sensor.h"
#include "Tricore/Cpu/Std/Ifx_Types.h"
#include "Test_Adc.h"

uint8 j = 0;

volatile uint16 distance = 0;
uint16 distanceResult = 0;
uint16 distanceVector[5] = {0, };

volatile uint16 hill = 0;
uint16 hillResult = 0;
uint16 hillVector[5] = {0, };
uint16 zonedetect [3] = {0, };
volatile uint8 runState = 0;

void UpdateSensor(void){
	int a, b;
	int distTemp, hillTemp;

	Test_VadcAutoScan(IfxVadc_GroupId_0);
	Test_VadcAutoScan(IfxVadc_GroupId_1);

	distance = Adc_Result_Scan[0][9];
	hill = Adc_Result_Scan[1][4];
	distanceVector[j] = distance;
	hillVector[j] = hill;
	//zonedetect[0] = Adc_Result_Scan[0][10]/1000; //¿ÞÂÊ
	zonedetect[1] = Adc_Result_Scan[1][2]/1000;
	zonedetect[2] = Adc_Result_Scan[1][9]/1000;
	//zonedetect[1] = Adc_Result_Scan[0][11]/1000; // ¿À¸¥ÂÊ

	if(j == 2){
		for(a=0; a<4; a++){
			for(b=a+1; b<5; b++){
				if(distanceVector[a] > distanceVector[b]){
					distTemp = distanceVector[a];
					distanceVector[a] = distanceVector[b];
					distanceVector[b] = distTemp;
				}
				if(hillVector[a] > hillVector[b]){
					hillTemp = hillVector[a];
					hillVector[a] = hillVector[b];
					hillVector[b] = hillTemp;
				}
			}
		}
		distanceResult = distanceVector[2];
		hillResult = hillVector[2];
	}
	j++;

	if(j > 4){
		j = 0;
	}
}

int IsOptical(void) {
	int i;
	for(i=OPTICAL_INDEX; i<=OPTICAL_SIZE; i++)
		if(Adc_Result_Scan[OPTICAL_GROUP][i] == 0)
			return 1;
	return 0;
}

int IsObstacle(void) {
	runState = 0;
	if(distanceResult > FAR_THRESHOLD)
		runState = 2;
	else if(hillResult >= NEAR_THRESHOLD)
		runState = 1;

	return runState;
}

int IsSchoolLine(void){
	if(zonedetect[1] == 0 || zonedetect[2] == 0 ){
		return 1;
	}
	else{
		return 0;
	}
}


