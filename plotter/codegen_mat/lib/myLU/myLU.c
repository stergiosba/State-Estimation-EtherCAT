/*
 * File: myLU.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 29-Mar-2022 00:22:52
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
  double b_x_data[100];
  double x_data[10];
  double z1_data[10];
  double s;
  double smax;
  int ipiv_data[10];
  int p_data[10];
  int b_i;
  int b_n;
  int i;
  int i1;
  int ipiv_size_idx_1;
  int ix;
  int j;
  int jj;
  int jp1j;
  int k;
  int ldap1;
  int mmj_tmp;
  int n;
  int u1;
  int x_size_idx_0;
  int yk;
  L_size[0] = A_size[0];
  L_size[1] = A_size[0];
  n = A_size[0] * A_size[0];
  if (0 <= n - 1) {
    memset(&L_data[0], 0, n * sizeof(double));
  }

  i = A_size[0];
  for (j = 0; j < i; j++) {
    i1 = A_size[0] - j;
    for (ix = 0; ix < i1; ix++) {
      b_i = j + ix;
      if (b_i + 1 == j + 1) {
        n = j + 1;
        for (k = 0; k <= j; k++) {
          smax = L_data[b_i + L_size[0] * k];
          z1_data[k] = smax * smax;
        }

        smax = z1_data[0];
        for (k = 2; k <= n; k++) {
          smax += z1_data[k - 1];
        }

        L_data[b_i + L_size[0] * j] = sqrt(A_data[b_i + A_size[0] * j] - smax);
      } else {
        yk = j + 1;
        for (jp1j = 0; jp1j <= j; jp1j++) {
          n = L_size[0] * jp1j;
          x_data[jp1j] = L_data[b_i + n] * L_data[j + n];
        }

        smax = x_data[0];
        for (k = 2; k <= yk; k++) {
          smax += x_data[k - 1];
        }

        n = L_size[0] * j;
        L_data[b_i + n] = (A_data[b_i + A_size[0] * j] - smax) / L_data[j + n];
      }
    }
  }

  if (A_size[0] == 0) {
    invL_size[0] = 0;
    invL_size[1] = 0;
  } else {
    b_n = A_size[0];
    invL_size[0] = A_size[0];
    invL_size[1] = A_size[0];
    n = A_size[0] * A_size[0];
    if (0 <= n - 1) {
      memset(&invL_data[0], 0, n * sizeof(double));
    }

    x_size_idx_0 = A_size[0];
    if (0 <= n - 1) {
      memcpy(&b_x_data[0], &L_data[0], n * sizeof(double));
    }

    n = A_size[0];
    ipiv_size_idx_1 = A_size[0];
    ipiv_data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      ipiv_data[k - 1] = yk;
    }

    ldap1 = A_size[0];
    n = A_size[0] - 1;
    u1 = A_size[0];
    if (n < u1) {
      u1 = n;
    }

    for (j = 0; j < u1; j++) {
      mmj_tmp = b_n - j;
      yk = j * (b_n + 1);
      jj = j * (ldap1 + 1);
      jp1j = yk + 2;
      if (mmj_tmp < 1) {
        n = -1;
      } else {
        n = 0;
        if (mmj_tmp > 1) {
          ix = yk;
          smax = fabs(b_x_data[jj]);
          for (k = 2; k <= mmj_tmp; k++) {
            ix++;
            s = fabs(b_x_data[ix]);
            if (s > smax) {
              n = k - 1;
              smax = s;
            }
          }
        }
      }

      if (b_x_data[jj + n] != 0.0) {
        if (n != 0) {
          n += j;
          ipiv_data[j] = n + 1;
          ix = j;
          for (k = 0; k < b_n; k++) {
            smax = b_x_data[ix];
            b_x_data[ix] = b_x_data[n];
            b_x_data[n] = smax;
            ix += b_n;
            n += b_n;
          }
        }

        i = jj + mmj_tmp;
        for (ix = jp1j; ix <= i; ix++) {
          b_x_data[ix - 1] /= b_x_data[jj];
        }
      }

      n = yk + b_n;
      yk = jj + ldap1;
      for (b_i = 0; b_i <= mmj_tmp - 2; b_i++) {
        smax = b_x_data[n];
        if (b_x_data[n] != 0.0) {
          ix = jj + 1;
          i = yk + 2;
          i1 = mmj_tmp + yk;
          for (jp1j = i; jp1j <= i1; jp1j++) {
            b_x_data[jp1j - 1] += b_x_data[ix] * -smax;
            ix++;
          }
        }

        n += b_n;
        yk += b_n;
      }
    }

    n = A_size[0];
    p_data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      p_data[k - 1] = yk;
    }

    for (k = 0; k < ipiv_size_idx_1; k++) {
      i = ipiv_data[k];
      if (i > k + 1) {
        n = p_data[i - 1];
        p_data[i - 1] = p_data[k];
        p_data[k] = n;
      }
    }

    for (k = 0; k < b_n; k++) {
      i = p_data[k];
      n = invL_size[0] * (i - 1);
      invL_data[k + n] = 1.0;
      for (j = k + 1; j <= b_n; j++) {
        if (invL_data[(j + n) - 1] != 0.0) {
          i1 = j + 1;
          for (ix = i1; ix <= b_n; ix++) {
            yk = (ix + invL_size[0] * (i - 1)) - 1;
            invL_data[yk] -= invL_data[(j + invL_size[0] * (i - 1)) - 1] *
              b_x_data[(ix + x_size_idx_0 * (j - 1)) - 1];
          }
        }
      }
    }

    for (j = 0; j < b_n; j++) {
      n = b_n * j - 1;
      for (k = b_n; k >= 1; k--) {
        yk = b_n * (k - 1) - 1;
        i = k + n;
        if (invL_data[i] != 0.0) {
          invL_data[i] /= b_x_data[k + yk];
          for (ix = 0; ix <= k - 2; ix++) {
            i1 = (ix + n) + 1;
            invL_data[i1] -= invL_data[i] * b_x_data[(ix + yk) + 1];
          }
        }
      }
    }
  }
}

/*
 * File trailer for myLU.c
 *
 * [EOF]
 */
