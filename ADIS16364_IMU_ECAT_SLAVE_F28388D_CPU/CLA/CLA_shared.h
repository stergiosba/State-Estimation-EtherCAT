#ifndef CLA_CLA_SHARED_H_
#define CLA_CLA_SHARED_H_

//
// Included Files
//
#include <stdint.h>
#include "SPI_init.h"
#include "CLAmath.h"
#include "ADIS16364.h"
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
extern float g_Attitude[3];
extern float QGL[4];

extern uint16_t g_ActiveMode;
extern uint16_t g_ActiveDRng; //!< Active Dynamic Range Option
volatile extern uint16_t g_ActiveTaps; //!< Active Filtering Taps Option
extern uint16_t ulCycleCount1;
extern uint16_t ulCycleCount2;
extern uint32_t p_s;
extern float p_c;
extern float t_c;
extern float t_t;
extern uint16_t s_t;


//void Complimentary_Filter();

__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();


#endif /* CLA_CLA_SHARED_H_ */
