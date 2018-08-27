
#ifndef USERDEFINE_H_
#define USERDEFINE_H_

enum AREA {
	E_READY = 0,
	E_STOP,
	E_SPEED,
	E_SCHOOL
};

enum DIRECTION {
	E_NONE = 0,
	E_LEFT = -1,
	E_RIGHT = 1
};

typedef int bool;
#define true (int)1
#define false (int)0

#endif /* 0_SRC_0_APPSW_APP_INC_USERDEFINE_H__H_ */
