/*
 * File: _coder_myLU_mex.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 29-Mar-2022 00:22:52
 */

/* Include Files */
#include "_coder_myLU_mex.h"
#include "_coder_myLU_api.h"

/* Function Definitions */
/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[]
 *                int32_T nrhs
 *                const mxArray *prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&myLU_atexit);

  /* Module initialization. */
  myLU_initialize();

  /* Dispatch the entry-point. */
  myLU_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  myLU_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[2]
 *                int32_T nrhs
 *                const mxArray *prhs[1]
 * Return Type  : void
 */
void myLU_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T nrhs, const
                      mxArray *prhs[1])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  const mxArray *outputs[2];
  int32_T b_nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 4,
                        "myLU");
  }

  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 4,
                        "myLU");
  }

  /* Call the function. */
  myLU_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays((int16_T)b_nlhs, plhs, outputs);
}

/*
 * File trailer for _coder_myLU_mex.c
 *
 * [EOF]
 */
