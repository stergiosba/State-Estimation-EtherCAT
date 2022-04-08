#ifndef CLA_CLA_INIT_H_
#define CLA_CLA_INIT_H_

//
// Included Files
//
#include "CLA_shared.h"
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define WAITSTEP     asm(" RPT #255 || NOP")

void CLA_runTest(void);
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);
void initEPWM1(void);
__interrupt void cla1Isr1();
__interrupt void cla1Isr2();
__interrupt void cla1Isr3();
__interrupt void cla1Isr4();
__interrupt void cla1Isr5();
__interrupt void cla1Isr6();
__interrupt void cla1Isr7();
__interrupt void cla1Isr8();

#endif /* CLA_CLA_INIT_H_ */
