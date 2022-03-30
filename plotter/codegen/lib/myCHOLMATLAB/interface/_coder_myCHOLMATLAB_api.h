/*
 * File: _coder_myCHOLMATLAB_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 30-Mar-2022 04:35:44
 */

#ifndef _CODER_MYCHOLMATLAB_API_H
#define _CODER_MYCHOLMATLAB_API_H

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
  void myCHOLMATLAB(real_T A_data[], int32_T A_size[2], real_T L_data[], int32_T
                    L_size[2], real_T invL_data[], int32_T invL_size[2]);
  void myCHOLMATLAB_api(const mxArray * const prhs[1], int32_T nlhs, const
                        mxArray *plhs[2]);
  void myCHOLMATLAB_atexit(void);
  void myCHOLMATLAB_initialize(void);
  void myCHOLMATLAB_terminate(void);
  void myCHOLMATLAB_xil_shutdown(void);
  void myCHOLMATLAB_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_myCHOLMATLAB_api.h
 *
 * [EOF]
 */
