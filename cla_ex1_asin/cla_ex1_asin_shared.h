#ifndef _CLA_ASIN_SHARED_H_
#define _CLA_ASIN_SHARED_H_


//
// Included Files
//
#include <stdint.h>
#include "f28x_project.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//
#define READ_CLOCK(X) __meallow();\
EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE;\
X = EPwm1Regs.TBCTR;\
__medis();

#define RESTART_CLOCK __meallow();\
EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE;\
EPwm1Regs.TBCTR = 0;\
EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;\
__medis();

#define N   3
typedef float m_elem;

extern m_elem x[N][N];
extern m_elem y[N][N];
extern m_elem z[N][N];
extern m_elem K[N][N];

extern uint32_t ulCycleCount;
extern uint32_t kk;


//
// Globals
//

//
//Task 1 (C) Variables
//

//
//Task 2 (C) Variables
//

//
//Task 3 (C) Variables
//

//
//Task 4 (C) Variables
//

//
//Task 5 (C) Variables
//

//
//Task 6 (C) Variables
//

//
//Task 7 (C) Variables
//

//
//Task 8 (C) Variables
//

//
//Common (C) Variables
//
//extern void matmul(m_elem A[][N], m_elem B[][N], m_elem C[][N]);

//
// Function Prototypes
//
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.
//
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _CLA_ASIN_SHARED_H_ definition

//
// End of file
//
