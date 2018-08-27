/*
 * Test_Camera.c
 *
 *  Created on: 2018. 7. 2.
 *      Author: kdh95
 */

#include "Test_Camera.h"
#include "Test_Pwm.h"

cam_infomation cam_info[LINES];
int nowIndex;
int debugLine[SIZE];
int centerMedian[5];
int cntTotal, cntLeft;
bool isDashLine;
enum DIRECTION whereDashLine;

void Camera_Initialization() {
   int i=0, j=0;
   for(i=0; i < LINES; i++) {
      cam_info[i].center = 64;
      for(j=0; j<SIZE; j++)
         cam_info[i].cam_scan[j] = 0;
   }

   nowIndex = 0;
   whereDashLine = E_NONE;
   isDashLine = false;
   cntTotal = 0;
   cntLeft = 0;
}

int GetCameraCenter() {
   int i=0;

   GetCamera(&cam_info[nowIndex]);

   Stretching(&(cam_info[nowIndex].cam_scan), 4096);
   MedianFiltering(&cam_info[nowIndex].cam_scan);
   Sharpening(&cam_info[nowIndex].cam_scan);
   Stretching(&(cam_info[nowIndex].cam_scan), 100000);

   cam_info[nowIndex].center = FindCenter(&(cam_info[nowIndex].cam_scan));

   if(cam_info[nowIndex].center == -1 || cam_info[nowIndex].center == 0) {
      CopyPrevLine(&(cam_info[nowIndex]), cam_info[(nowIndex + LINES - 1) % LINES]);
      cam_info[nowIndex].center = cam_info[(nowIndex + LINES - 1) % LINES].center;
   }

   for(i=0; i<SIZE; i++)
	   debugLine[i] = cam_info[nowIndex].cam_scan[i];

   nowIndex = (nowIndex+1)%LINES;

   return cam_info[0].center;
}
enum DIRECTION  GetCameraDash() {
   return whereDashLine;
}
void EnterSchoolArea() {
   if(isDashLine == false) {
      isDashLine = true;
      whereDashLine = 0;
      cntLeft = 0;
   }
}
void GetCamera(cam_infomation * _cam_info) {
   int i;

   IfxPort_setPinState(&MODULE_P14, 6, IfxPort_State_high);
   IfxPort_setPinState(&MODULE_P22, 1, IfxPort_State_high);
   waitTime(3 * TimeConst_100us);

   IfxPort_setPinState(&MODULE_P14, 6, IfxPort_State_low);
   IfxPort_setPinState(&MODULE_P22, 1, IfxPort_State_low);
   waitTime(3 * TimeConst_100us);


   for(i=0; i<SIZE; i++) {
      IfxPort_setPinState(&MODULE_P22, 1, IfxPort_State_high);
      waitTime(TimeConst_100us);
      IfxPort_setPinState(&MODULE_P22, 1, IfxPort_State_low);
      waitTime(TimeConst_100us);

      Test_VadcAutoScan(IfxVadc_GroupId_1);
      _cam_info->cam_scan[i] = Adc_Result_Scan[CAMERA_GROUP][CAMERA_INDEX];

      waitTime(TimeConst_100us);
   }
   waitTime(6 * TimeConst_100us);

   _cam_info->center = 64;
}

void CopyPrevLine(cam_infomation * _cam_info, cam_infomation _prev_info) {
   int i;
   for (i = 0; i < SIZE; i++)
      _cam_info->cam_scan[i] = _prev_info.cam_scan[i];
   _cam_info->center = _prev_info.center;
}

int GetMedian(int _array[5]) {
   int i, j, temp;
   for (i = 0; i < 5; i++) {
      for (j = i; j < 5; j++) {
         if (_array[i] > _array[j]) {
            temp = _array[i];
            _array[i] = _array[j];
            _array[j] = temp;
         }
      }
   }
   return _array[2];
}

void Stretching(int(*_line)[SIZE], int _max) {
   int i, max = (*_line)[0], min = (*_line)[0];

   for (i = 0; i < SIZE; i++) {
      max = ((*_line)[i] > max) ? (*_line)[i] : max;
      min = ((*_line)[i] < min) ? (*_line)[i] : min;
   }
   for (i = 0; i < SIZE; i++)
      (*_line)[i] = ((float)_max / (float)(max - min)) * ((*_line)[i] - min);
}

void MedianFiltering(int(*_line)[SIZE]) {
   int i, j, t;
   int array[5];
   for (i = 0 + 2; i < MAX - 2; i++) {
      for (j = -2, t = 0; j <= 2; j++, t++)
         array[t] = (*_line)[i + j];
      (*_line)[i] = GetMedian(array);
   }
}
void Sharpening(int(*_line)[SIZE]) {
	int i, j;
	int minus, add, square;
	int temp[SIZE];

	for (i = 0; i < 128; i++) {
	      (*_line)[i] = MAX - (*_line)[i];
	      temp[i] = (*_line)[i];
	}

	for(i=3; i<125; i++) {
		minus = 0, add = 0, square = 0;
		for(j = -3; j <= 3; j++) {
			if(j <= -2 || j >= 2) minus += ((*_line)[i+j] * (-3));
			if(j == -1 || j == 1) add += ((*_line)[i+j] * 3);
			if(j == 0) square += ((*_line)[i+j] * 6);
		}
		temp[i] = minus + add + square;
	}

	for(i=0; i<128; i++)
		(*_line)[i] = temp[i];
}

int FindCenter(int(*_line)[SIZE]) {
   int i, index = 0, leftIndex = 0, rightIndex = 127, zeroCount = 0;

   for (i = 0; i < SIZE; i++) {
      if((*_line)[i] < 0)
         (*_line)[i] = 0;
      if ((*_line)[i] < THRESHOLD) {
    	  zeroCount++;
         (*_line)[i] = 0;
      }
   }

   if(zeroCount <= 120) return -1;

   for(i=1; i<75; i++) {
      if((75 - i - 1) >= 1) {
         if(leftIndex == 0 && (*_line)[75 - i] != 0 && (*_line)[75 - i - 1] == 0)
        	 leftIndex = 75 - i;
      }
      if((75 + i + 1) <= 126) {
         if(rightIndex == 127 && (*_line)[75 + i] != 0 && (*_line)[75 + i + 1] == 0)
        	 rightIndex = 75 + i;
      }
   }

   if(cntTotal < LEFTMAXCOUNT && isDashLine == true) {
	   cntTotal += 1;
	   if(leftIndex != 0)
		   cntLeft += 1;
	   if(cntTotal == LEFTMAXCOUNT) {
		   if(cntLeft >= LEFTTHRESHOLD)
			   whereDashLine = E_RIGHT;
		   else if(cntLeft < LEFTTHRESHOLD)
			   whereDashLine = E_LEFT;
	   }
   }

   if(leftIndex >= 5) {
      index = leftIndex + 62;
      if(leftIndex >= 70) index = -1;
   }
   else if(rightIndex <= 124) {
      index = rightIndex - 62;
      if(rightIndex <= 80) index = -1;
   }
   else if(leftIndex != 0 && rightIndex != 127)
	   index = (leftIndex + rightIndex) / 2;
   else
	   index = -1;
   if(index <= 10 || index >= 118)
	   index = -1;

   return index;
}
