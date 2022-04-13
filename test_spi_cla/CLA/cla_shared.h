#ifndef CLA_CLA_SHARED_H_
#define CLA_CLA_SHARED_H_

//
// Included Files
//
#include <stdint.h>
//#include "f2838x_device.h"
#include "f28x_project.h" //MAYBE NOT NEEDED

#define READ_CLOCK(X) __meallow();\
EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE;\
X = EPwm1Regs.TBCTR;\
__medis();

#define RESTART_CLOCK __meallow();\
EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE;\
EPwm1Regs.TBCTR = 0;\
EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;\
__medis();

extern float g_SensBurst[11];
extern float test[11];
extern uint32_t ulCycleCount1;
extern float SENS;


extern void cla_test_func();

__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();


#endif /* CLA_CLA_SHARED_H_ */
