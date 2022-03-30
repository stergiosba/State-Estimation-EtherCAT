/*
 * File: myLU.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 30-Mar-2022 02:29:25
 */

/* Include Files */
#include "myCHOL2.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double A_data[]
 *                double L_data[]
 *                double invL_data[]
 * Return Type  : void
 */
void CHOL3(const float A_data[N*N], float L_data[N*N], float invL_data[N*N])
{
  float sums, y, c, ssq;
  int16_t idxAjj = N*N, idxA1j = N*N, b_i, i, i1, j, k, loop_ub, yk, ix, iy,  jj, jp1j , n, iac, idxAjp1j;
  bool exitg1;

  if (0 <= idxAjj - 1) {
    memcpy(&L_data[0], &A_data[0], idxAjj * sizeof(float));
  }

  n = N;
  if (N != 0) {
    jp1j = 0;
    j = 0;
    exitg1 = false;
    while ((!exitg1) && (j <= n - 1)) {
      idxAjj = j + j * n;
      ssq = 0.0;
      if (j >= 1) {
        ix = j;
        iy = j;
        for (k = 0; k < j; k++) {
          ssq += L_data[ix] * L_data[iy];
          ix += n;
          iy += n;
        }
      }

      ssq = L_data[idxAjj] - ssq;
      if (ssq > 0.0) {
        ssq = sqrt(ssq);
        L_data[idxAjj] = ssq;
        if (j + 1 < n) {
          idxA1j = (n - j) - 1;
          yk = j + 2;
          idxAjp1j = idxAjj + 2;
          if ((idxA1j != 0) && (j != 0)) {
            ix = j;
            i = (j + n * (j - 1)) + 2;
            for (iac = yk; n < 0 ? iac >= i : iac <= i; iac += n) {
              c = -L_data[ix];
              iy = idxAjj + 1;
              i1 = (iac + idxA1j) - 1;
              for (jj = iac; jj <= i1; jj++) {
                L_data[iy] += L_data[jj - 1] * c;
                iy++;
              }

              ix += n;
            }
          }

          ssq = 1.0 / ssq;
          i = idxAjj + idxA1j;
          for (k = idxAjp1j; k <= i + 1; k++) {
            L_data[k - 1] *= ssq;
          }
        }

        j++;
      } else {
        L_data[idxAjj] = ssq;
        jp1j = j + 1;
        exitg1 = true;
      }
    }

    if (jp1j == 0) {
      idxA1j = N;
    } else {
      idxA1j = jp1j - 1;
    }

    for (j = 2; j <= idxA1j; j++) {
      for (idxAjj = 0; idxAjj <= j - 2; idxAjj++) {
        L_data[idxAjj + N * (j - 1)] = 0.0;
      }
    }
  }
  loop_ub = N*N;

  memcpy(&invL_data[0], &L_data[0], loop_ub * sizeof(float));

  i = N;
  for (b_i = 0; b_i < i; b_i++) {
    y = L_data[b_i + N * b_i];
    invL_data[b_i + N * b_i] = 1.0 / y;
    for (j = 0; j < b_i; j++) {
      sums = 0.0;
      i1 = b_i - j;
      for (k = 0; k < i1; k++) {
        loop_ub = j + k;
        sums += invL_data[b_i + N * loop_ub] * invL_data[loop_ub + N * j];
      }

      invL_data[b_i + N * j] = -sums / y;
    }
  }
}

/*
 * File trailer for myLU.c
 *
 * [EOF]
 */
