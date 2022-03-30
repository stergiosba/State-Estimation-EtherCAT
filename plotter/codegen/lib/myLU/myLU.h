/*
 * File: myLU.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 30-Mar-2022 02:29:25
 */

#ifndef MYLU_H
#define MYLU_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  extern void myLU(const double A_data[], const int A_size[2], double L_data[],
                   int L_size[2], double invL_data[], int invL_size[2]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for myLU.h
 *
 * [EOF]
 */
