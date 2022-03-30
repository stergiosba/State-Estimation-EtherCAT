/*
 * File: myLU.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 30-Mar-2022 02:29:25
 */

#ifndef MYLU_H
#define MYLU_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define N 5
#ifdef __cplusplus

extern "C" {

#endif


  /* Function Declarations */
  extern void CHOL2(const float A_data[N*N], float L_data[N*N], float invL_data[N*N]);
  extern void CHOL3(const float A_data[N*N], float L_data[N*N], float invL_data[N*N]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for myLU.h
 *
 * [EOF]
 */
