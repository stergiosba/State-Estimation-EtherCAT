/*
 * File: _coder_myLU_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 29-Mar-2022 00:22:52
 */

#ifndef _CODER_MYLU_API_H
#define _CODER_MYLU_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void myLU(real_T A_data[], int32_T A_size[2], real_T L_data[], int32_T L_size
            [2], real_T invL_data[], int32_T invL_size[2]);
  void myLU_api(const mxArray * const prhs[1], int32_T nlhs, const mxArray *
                plhs[2]);
  void myLU_atexit(void);
  void myLU_initialize(void);
  void myLU_terminate(void);
  void myLU_xil_shutdown(void);
  void myLU_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_myLU_api.h
 *
 * [EOF]
 */
