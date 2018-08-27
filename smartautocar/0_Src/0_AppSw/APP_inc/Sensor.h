/*
 * Sensor.h
 *
 *  Created on: 2018. 6. 27.
 *      Author: Keith_Lee
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#define NEAR_THRESHOLD 1000
#define FAR_THRESHOLD 700

#define NEAR_GROUP 0
#define NEAR_INDEX 9

#define FAR_GROUP 1
#define FAR_INDEX 4

#define OPTICAL_GROUP 2
#define OPTICAL_INDEX 9
#define OPTICAL_SIZE 5

void UpdateSensor(void);
int IsOptical(void);
int IsObstacle(void);
int IsSchoolLine(void);

#endif /* 0_SRC_0_APPSW_APP_INC_SENSOR_H_ */
