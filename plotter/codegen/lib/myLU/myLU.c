/*
 * File: myLU.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 30-Mar-2022 02:29:25
 */

/* Include Files */
#include "myLU.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double A_data[]
 *                const int A_size[2]
 *                double L_data[]
 *                int L_size[2]
 *                double invL_data[]
 *                int invL_size[2]
 * Return Type  : void
 */
void myLU(const double A_data[], const int A_size[2], double L_data[], int
          L_size[2], double invL_data[], int invL_size[2])
{
  double x_data[10];
  double z1_data[10];
  double sums;
  double y;
  int b_i;
  int c_i;
  int i;
  int i1;
  int j;
  int k;
  int loop_ub;
  int x_size_idx_1;
  L_size[0] = A_size[0];
  L_size[1] = A_size[0];
  loop_ub = A_size[0] * A_size[0];
  if (0 <= loop_ub - 1) {
    memset(&L_data[0], 0, loop_ub * sizeof(double));
  }

  i = A_size[0];
  for (j = 0; j < i; j++) {
    i1 = A_size[0] - j;
    for (b_i = 0; b_i < i1; b_i++) {
      c_i = j + b_i;
      if (c_i + 1 == j + 1) {
        loop_ub = j + 1;
        for (k = 0; k <= j; k++) {
          y = L_data[c_i + L_size[0] * k];
          z1_data[k] = y * y;
        }

        y = z1_data[0];
        for (k = 2; k <= loop_ub; k++) {
          y += z1_data[k - 1];
        }

        L_data[c_i + L_size[0] * j] = sqrt(A_data[c_i + A_size[0] * j] - y);
      } else {
        x_size_idx_1 = j + 1;
        for (k = 0; k <= j; k++) {
          loop_ub = L_size[0] * k;
          x_data[k] = L_data[c_i + loop_ub] * L_data[j + loop_ub];
        }

        y = x_data[0];
        for (k = 2; k <= x_size_idx_1; k++) {
          y += x_data[k - 1];
        }

        loop_ub = L_size[0] * j;
        L_data[c_i + loop_ub] = (A_data[c_i + A_size[0] * j] - y) / L_data[j +
          loop_ub];
      }
    }
  }

  invL_size[0] = A_size[0];
  invL_size[1] = A_size[0];
  loop_ub = A_size[0] * A_size[0];
  if (0 <= loop_ub - 1) {
    memcpy(&invL_data[0], &L_data[0], loop_ub * sizeof(double));
  }

  i = A_size[0];
  for (b_i = 0; b_i < i; b_i++) {
    y = L_data[b_i + L_size[0] * b_i];
    invL_data[b_i + invL_size[0] * b_i] = 1.0 / y;
    for (j = 0; j < b_i; j++) {
      sums = 0.0;
      i1 = b_i - j;
      for (k = 0; k < i1; k++) {
        loop_ub = j + k;
        sums += invL_data[b_i + invL_size[0] * loop_ub] * invL_data[loop_ub +
          invL_size[0] * j];
      }

      invL_data[b_i + invL_size[0] * j] = -sums / y;
    }
  }
}

/*
 * File trailer for myLU.c
 *
 * [EOF]
 */
