/*
 * File: myCHOLMATLAB.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 30-Mar-2022 04:35:44
 */

/* Include Files */
#include "myCHOLMATLAB.h"
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
void myCHOLMATLAB(const double A_data[], const int A_size[2], double L_data[],
                  int L_size[2], double invL_data[], int invL_size[2])
{
  double x_data[25];
  double c;
  double ssq;
  int ipiv_data[5];
  int p_data[5];
  int i;
  int i1;
  int iac;
  int idxAjj;
  int idxAjp1j;
  int ipiv_size_idx_1;
  int ix;
  int iy;
  int j;
  int jj;
  int jmax;
  int jp1j;
  int k;
  int ldap1;
  int n;
  int u1;
  int x_size_idx_0;
  int yk;
  boolean_T exitg1;
  L_size[0] = A_size[0];
  L_size[1] = A_size[1];
  jmax = A_size[0] * A_size[1];
  if (0 <= jmax - 1) {
    memcpy(&L_data[0], &A_data[0], jmax * sizeof(double));
  }

  n = A_size[1];
  if (A_size[1] != 0) {
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
          jmax = (n - j) - 1;
          yk = j + 2;
          idxAjp1j = idxAjj + 2;
          if ((jmax != 0) && (j != 0)) {
            ix = j;
            i = (j + n * (j - 1)) + 2;
            for (iac = yk; n < 0 ? iac >= i : iac <= i; iac += n) {
              c = -L_data[ix];
              iy = idxAjj + 1;
              i1 = (iac + jmax) - 1;
              for (jj = iac; jj <= i1; jj++) {
                L_data[iy] += L_data[jj - 1] * c;
                iy++;
              }

              ix += n;
            }
          }

          ssq = 1.0 / ssq;
          i = idxAjj + jmax;
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
      jmax = A_size[1];
    } else {
      jmax = jp1j - 1;
    }

    for (j = 2; j <= jmax; j++) {
      for (idxAjj = 0; idxAjj <= j - 2; idxAjj++) {
        L_data[idxAjj + L_size[0] * (j - 1)] = 0.0;
      }
    }
  }

  if ((A_size[0] == 0) || (A_size[1] == 0)) {
    invL_size[0] = A_size[0];
    invL_size[1] = A_size[1];
    jmax = A_size[0] * A_size[1];
    if (0 <= jmax - 1) {
      memcpy(&invL_data[0], &L_data[0], jmax * sizeof(double));
    }
  } else {
    n = A_size[0];
    invL_size[0] = A_size[0];
    invL_size[1] = A_size[1];
    jmax = A_size[0] * A_size[1];
    if (0 <= jmax - 1) {
      memset(&invL_data[0], 0, jmax * sizeof(double));
    }

    x_size_idx_0 = A_size[0];
    if (0 <= jmax - 1) {
      memcpy(&x_data[0], &L_data[0], jmax * sizeof(double));
    }

    jmax = A_size[0];
    ipiv_size_idx_1 = A_size[0];
    ipiv_data[0] = 1;
    yk = 1;
    for (k = 2; k <= jmax; k++) {
      yk++;
      ipiv_data[k - 1] = yk;
    }

    ldap1 = A_size[0];
    jmax = A_size[0] - 1;
    u1 = A_size[0];
    if (jmax < u1) {
      u1 = jmax;
    }

    for (j = 0; j < u1; j++) {
      iac = n - j;
      yk = j * (n + 1);
      jj = j * (ldap1 + 1);
      jp1j = yk + 2;
      if (iac < 1) {
        jmax = -1;
      } else {
        jmax = 0;
        if (iac > 1) {
          ix = yk;
          ssq = fabs(x_data[jj]);
          for (k = 2; k <= iac; k++) {
            ix++;
            c = fabs(x_data[ix]);
            if (c > ssq) {
              jmax = k - 1;
              ssq = c;
            }
          }
        }
      }

      if (x_data[jj + jmax] != 0.0) {
        if (jmax != 0) {
          iy = j + jmax;
          ipiv_data[j] = iy + 1;
          ix = j;
          for (k = 0; k < n; k++) {
            ssq = x_data[ix];
            x_data[ix] = x_data[iy];
            x_data[iy] = ssq;
            ix += n;
            iy += n;
          }
        }

        i = jj + iac;
        for (idxAjj = jp1j; idxAjj <= i; idxAjj++) {
          x_data[idxAjj - 1] /= x_data[jj];
        }
      }

      jmax = yk + n;
      yk = jj + ldap1;
      for (idxAjj = 0; idxAjj <= iac - 2; idxAjj++) {
        ssq = x_data[jmax];
        if (x_data[jmax] != 0.0) {
          ix = jj + 1;
          i = yk + 2;
          i1 = iac + yk;
          for (idxAjp1j = i; idxAjp1j <= i1; idxAjp1j++) {
            x_data[idxAjp1j - 1] += x_data[ix] * -ssq;
            ix++;
          }
        }

        jmax += n;
        yk += n;
      }
    }

    jmax = A_size[0];
    p_data[0] = 1;
    yk = 1;
    for (k = 2; k <= jmax; k++) {
      yk++;
      p_data[k - 1] = yk;
    }

    for (k = 0; k < ipiv_size_idx_1; k++) {
      i = ipiv_data[k];
      if (i > k + 1) {
        jmax = p_data[i - 1];
        p_data[i - 1] = p_data[k];
        p_data[k] = jmax;
      }
    }

    for (k = 0; k < n; k++) {
      i = p_data[k];
      jmax = invL_size[0] * (i - 1);
      invL_data[k + jmax] = 1.0;
      for (j = k + 1; j <= n; j++) {
        if (invL_data[(j + jmax) - 1] != 0.0) {
          i1 = j + 1;
          for (idxAjj = i1; idxAjj <= n; idxAjj++) {
            yk = (idxAjj + invL_size[0] * (i - 1)) - 1;
            invL_data[yk] -= invL_data[(j + invL_size[0] * (i - 1)) - 1] *
              x_data[(idxAjj + x_size_idx_0 * (j - 1)) - 1];
          }
        }
      }
    }

    for (j = 0; j < n; j++) {
      jmax = n * j - 1;
      for (k = n; k >= 1; k--) {
        yk = n * (k - 1) - 1;
        i = k + jmax;
        if (invL_data[i] != 0.0) {
          invL_data[i] /= x_data[k + yk];
          for (idxAjj = 0; idxAjj <= k - 2; idxAjj++) {
            i1 = (idxAjj + jmax) + 1;
            invL_data[i1] -= invL_data[i] * x_data[(idxAjj + yk) + 1];
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
