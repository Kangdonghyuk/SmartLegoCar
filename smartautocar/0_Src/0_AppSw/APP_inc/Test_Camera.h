/*
 * Test_Camera.h
 *
 *  Created on: 2018. 7. 2.
 *      Author: kdh95
 */

#ifndef TEST_CAMERA_H_
#define TEST_CAMERA_H_

#include <Port/Std/IfxPort.h>
#include "Test_Adc.h"
#include "UserDefine.h"

#define LINES 5
#define SIZE 128
#define MAX 4096
#define DABS(n) ((n < 0) ? -n : n)
#define DSQUARE(n) (n*n)
#define THRESHOLD 85000
#define LEFTMAXCOUNT 300
#define LEFTTHRESHOLD 197

#define CAMERA_GROUP 1
#define CAMERA_INDEX 8

#define SI_0   P22_OUT.B.P0
#define CL_0   P22_OUT.B.P1
#define SI_1   P22_OUT.B.P2
#define CL_1   P22_OUT.B.P3

typedef struct CAM_INFOMATION {
   int cam_scan[SIZE];
   int center;
}cam_infomation;

void Camera_Initialization();
int GetCameraCenter();
enum DIRECTION GetCameraDash();

void GetCamera(cam_infomation * _cam_info);
void CopyPrevLine(cam_infomation * _cam_info, cam_infomation _prev_info);
void EnterSchoolArea();

int GetMedian(int _array[5]);
void Stretching(int(*_line)[SIZE], int _max);
void MedianFiltering(int(*_line)[SIZE]);
void Sharpening(int(*_line)[SIZE]);
int FindCenter(int(*line)[SIZE]);

#endif /* TEST_CAMERA_H_ */
