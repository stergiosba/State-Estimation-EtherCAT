/*
 * File: _coder_myLU_mex.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 30-Mar-2022 02:29:25
 */

#ifndef _CODER_MYLU_MEX_H
#define _CODER_MYLU_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T
    nrhs, const mxArray *prhs[]);
  emlrtCTX mexFunctionCreateRootTLS(void);
  void myLU_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T nrhs, const
                        mxArray *prhs[1]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_myLU_mex.h
 *
 * [EOF]
 */
