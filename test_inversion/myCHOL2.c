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
void CHOL2(const float A_data[N*N], float L_data[N*N], float invL_data[N*N])
{
  float x_data[N], z1_data[N], sums, y;
  short b_i, c_i, i, i1, j, k, loop_ub, x_size_idx_1;

  loop_ub = N*N;

  memset(&L_data[0], 0, loop_ub * sizeof(float));

  i = N;

  for (j = 0; j < i; j++)
  {
      i1 = N - j;
      for (b_i = 0; b_i < i1; b_i++)
      {
          c_i = j + b_i;
          if (c_i + 1 == j + 1)
          {
              loop_ub = j + 1;
              for (k = 0; k <= j; k++)
              {
                  y = L_data[c_i + N * k];
                  z1_data[k] = y * y;
              }
              y = z1_data[0];
              for (k = 2; k <= loop_ub; k++)
              {
                  y += z1_data[k - 1];
              }
              L_data[c_i + N * j] = sqrt(A_data[c_i + N * j] - y);
          }
          else
          {
              x_size_idx_1 = j + 1;
              for (k = 0; k <= j; k++)
              {
                  loop_ub = N * k;
                  x_data[k] = L_data[c_i + loop_ub] * L_data[j + loop_ub];
              }
              y = x_data[0];
              for (k = 2; k <= x_size_idx_1; k++)
              {
                  y += x_data[k - 1];
              }
              loop_ub = N * j;
              L_data[c_i + loop_ub] = (A_data[c_i + N * j] - y) / L_data[j + loop_ub];
          }
      }
  }
  loop_ub = N*N;

  memcpy(&invL_data[0], &L_data[0], loop_ub * sizeof(float));

  i = N;
  for (b_i = 0; b_i < i; b_i++)
  {
      y = L_data[b_i + N * b_i];
      invL_data[b_i + N * b_i] = 1.0 / y;
      for (j = 0; j < b_i; j++)
      {
          sums = 0.0;
          i1 = b_i - j;
          for (k = 0; k < i1; k++)
          {
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
