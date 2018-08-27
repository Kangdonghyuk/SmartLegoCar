#ifndef Test_Encoder_H_
#define	Test_Encoder_H_

#include "Gtm/Tom/Timer/IfxGtm_Tom_Timer.h"

void Encoder_Initialization(void);
extern uint32 get_encoder(void);
extern void PID(uint16 encodercheck, double goal);

extern volatile uint16 duty;

#endif /* 0_SRC_0_APPSW_APP_INC_TPIM_H_ */
