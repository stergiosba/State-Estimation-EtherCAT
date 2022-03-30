#ifndef _CLA_ASIN_SHARED_H_
#define _CLA_ASIN_SHARED_H_


//
// Included Files
//
#include <stdint.h>
#include "f28x_project.h"
#include "CLAmath.h"

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

typedef float m_elem;

typedef struct
{
    m_elem p;
    m_elem q;
    m_elem r;
    m_elem phi;
    m_elem th;
} State;

typedef union
{
    m_elem     *ptr;
    uint32_t    padd;
}CLA_FPTR;

#define N                   128
#define STATE_SIZE          10
#define STATE_SYM_SIZE      STATE_SIZE*(STATE_SIZE+1)/2
#define OBSV_SIZE           2
#define OBSV_SYM_SIZE       OBSV_SIZE*(OBSV_SIZE+1)/2

/*
 * A priori State Covariance Matrix
 */
extern m_elem Pxx_[STATE_SYM_SIZE];

/*
 * A posteriori State Covariance Matrix
 */
extern m_elem Pxx[STATE_SYM_SIZE];

/*
 * State Jacobian Matrix
 */
extern m_elem Jfx[STATE_SIZE][STATE_SIZE];

/*
 * Observation Jacobian Matrix
 */
extern m_elem Hx[OBSV_SIZE][OBSV_SIZE];

/*
 * Process Noise Covariance Matrix
 */
extern m_elem Q[STATE_SYM_SIZE];

/*
 * Measurement Noise Covariance Matrix
 */
extern m_elem R[OBSV_SYM_SIZE];

/*
 * Kalman Gain Matrix
 */
extern m_elem K_EKF[STATE_SIZE][OBSV_SIZE];

extern m_elem A[STATE_SIZE*STATE_SIZE];
extern m_elem invA[STATE_SIZE*STATE_SIZE];
extern m_elem L[STATE_SIZE*STATE_SIZE];
extern m_elem invL[STATE_SIZE*STATE_SIZE];

extern State state;

extern uint32_t ulCycleCount1;
extern uint32_t ulCycleCount2;
extern uint32_t kk;


//extern void cholesky();
//extern void cholesky_inverse(const m_elem L_data[], m_elem invL_data[]);

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
//extern void __eke(m_elem r,m_elem q,m_elem phi,m_elem th);

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
