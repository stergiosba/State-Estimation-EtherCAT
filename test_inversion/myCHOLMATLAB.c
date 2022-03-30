/*
 * File: myCHOLMATLAB.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 30-Mar-2022 03:17:56
 */

/* Include Files */
#include "myCHOLMATLAB.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const float A_data[]
 *                float L_data[]
 *                float invL_data[]
 * Return Type  : void
 */
void CHOLMATLAB(const float A_data[N*N], float L_data[N*N], float invL_data[N*N])
{
  float b_A_data[N*N], c, ssq;
  int16_t ipiv_data[N], p_data[N], b_i, i, i1, ia, idxA1j, idxAjj, ix, iy, j, jj, jp1j, k , n, nmj;
  bool exitg1;
  idxAjj = N * N;
  if (0 <= idxAjj - 1) {
    memcpy(&b_A_data[0], &A_data[0], idxAjj * sizeof(float));
  }

  n = N;
  if (N != 0)
  {
    jj = -1;
    j = 0;
    exitg1 = false;
    while ((!exitg1) && (j <= n - 1))
    {
      idxA1j = j * n;
      idxAjj = idxA1j + j;
      ssq = 0.0;
      if (j >= 1)
      {
        ix = idxA1j;
        iy = idxA1j;
        for (k = 0; k < j; k++)
        {
          ssq += b_A_data[ix] * b_A_data[iy];
          ix++;
          iy++;
        }
      }

      ssq = b_A_data[idxAjj] - ssq;
      if (ssq > 0.0)
      {
        ssq = sqrt(ssq);
        b_A_data[idxAjj] = ssq;
        if (j + 1 < n)
        {
          nmj = (n - j) - 2;
          jp1j = (idxA1j + n) + 1;
          idxAjj += n;
          if ((j != 0) && (nmj + 1 != 0))
          {
            iy = idxAjj;
            i = jp1j + n * nmj;
            for (b_i = jp1j; n < 0 ? b_i >= i : b_i <= i; b_i += n)
            {
              ix = idxA1j;
              c = 0.0;
              i1 = (b_i + j) - 1;
              for (ia = b_i; ia <= i1; ia++)
              {
                c += b_A_data[ia - 1] * b_A_data[ix];
                ix++;
              }

              b_A_data[iy] += -c;
              iy += n;
            }
          }

          ssq = 1.0 / ssq;
          i = (idxAjj + n * nmj) + 1;
          for (k = idxAjj + 1; n < 0 ? k >= i : k <= i; k += n)
          {
            b_A_data[k - 1] *= ssq;
          }
        }

        j++;
      } else {
        b_A_data[idxAjj] = ssq;
        jj = j;
        exitg1 = true;
      }
    }

    if (jj + 1 == 0) {
      idxAjj = N;
    } else {
      idxAjj = jj;
    }

    for (j = 0; j < idxAjj; j++) {
      i = j + 2;
      for (b_i = i; b_i <= idxAjj; b_i++) {
        b_A_data[(b_i + N * j) - 1] = 0.0;
      }
    }
  }

  for (i = 0; i < N; i++) {
    for (i1 = 0; i1 < N; i1++) {
      L_data[i1 + N * i] = b_A_data[i + N * i1];
    }
  }

  if ((N == 0) || (N == 0)) {
    idxAjj = N * N;
    if (0 <= idxAjj - 1) {
      memcpy(&invL_data[0], &L_data[0], idxAjj * sizeof(float));
    }
  } else {
    n = N;
    idxAjj = N * N;
    if (0 <= idxAjj - 1) {
      memset(&invL_data[0], 0, idxAjj * sizeof(float));
    }

    if (0 <= idxAjj - 1) {
      memcpy(&b_A_data[0], &L_data[0], idxAjj * sizeof(float));
    }

    idxAjj = N;
    ipiv_data[0] = 1;
    nmj = 1;
    for (k = 2; k <= idxAjj; k++) {
      nmj++;
      ipiv_data[k - 1] = nmj;
    }

    idxAjj = N - 1;
    idxA1j = N;
    if (idxAjj < idxA1j) {
      idxA1j = idxAjj;
    }

    for (j = 0; j < idxA1j; j++) {
      ia = N - j;
      idxAjj = j * (N + 1);
      jj = j * (N + 1);
      jp1j = idxAjj + 2;
      if (ia < 1) {
        nmj = -1;
      } else {
        nmj = 0;
        if (ia > 1) {
          ix = idxAjj;
          ssq = fabs(b_A_data[jj]);
          for (k = 2; k <= ia; k++) {
            ix++;
            c = fabs(b_A_data[ix]);
            if (c > ssq) {
              nmj = k - 1;
              ssq = c;
            }
          }
        }
      }

      if (b_A_data[jj + nmj] != 0.0) {
        if (nmj != 0) {
          iy = j + nmj;
          ipiv_data[j] = iy + 1;
          ix = j;
          for (k = 0; k < n; k++) {
            ssq = b_A_data[ix];
            b_A_data[ix] = b_A_data[iy];
            b_A_data[iy] = ssq;
            ix += N;
            iy += N;
          }
        }

        i = jj + ia;
        for (b_i = jp1j; b_i <= i; b_i++) {
          b_A_data[b_i - 1] /= b_A_data[jj];
        }
      }

      nmj = idxAjj + N;
      idxAjj = jj + N;
      for (jp1j = 0; jp1j <= ia - 2; jp1j++) {
        ssq = b_A_data[nmj];
        if (b_A_data[nmj] != 0.0) {
          ix = jj + 1;
          i = idxAjj + 2;
          i1 = ia + idxAjj;
          for (b_i = i; b_i <= i1; b_i++) {
            b_A_data[b_i - 1] += b_A_data[ix] * -ssq;
            ix++;
          }
        }

        nmj += N;
        idxAjj += N;
      }
    }

    idxAjj = N;
    p_data[0] = 1;
    nmj = 1;
    for (k = 2; k <= idxAjj; k++) {
      nmj++;
      p_data[k - 1] = nmj;
    }

    for (k = 0; k < N; k++) {
      i = ipiv_data[k];
      if (i > k + 1) {
        idxAjj = p_data[i - 1];
        p_data[i - 1] = p_data[k];
        p_data[k] = idxAjj;
      }
    }

    for (k = 0; k < n; k++) {
      i = p_data[k];
      idxAjj = N * (i - 1);
      invL_data[k + idxAjj] = 1.0;
      for (j = k + 1; j <= n; j++) {
        if (invL_data[(j + idxAjj) - 1] != 0.0) {
          i1 = j + 1;
          for (b_i = i1; b_i <= n; b_i++) {
            nmj = (b_i + N * (i - 1)) - 1;
            invL_data[nmj] -= invL_data[(j + N * (i - 1)) - 1] *
              b_A_data[(b_i + N * (j - 1)) - 1];
          }
        }
      }
    }

    for (j = 0; j < n; j++) {
      idxAjj = N * j - 1;
      for (k = n; k >= 1; k--) {
        nmj = N * (k - 1) - 1;
        i = k + idxAjj;
        if (invL_data[i] != 0.0) {
          invL_data[i] /= b_A_data[k + nmj];
          for (b_i = 0; b_i <= k - 2; b_i++) {
            i1 = (b_i + idxAjj) + 1;
            invL_data[i1] -= invL_data[i] * b_A_data[(b_i + nmj) + 1];
          }
        }
      }
    }
  }
}

/*
 * File trailer for myCHOLMATLAB.c
 *
 * [EOF]
 */
