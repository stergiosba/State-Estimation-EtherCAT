/*
 * File: myCHOL1.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 29-Mar-2022 00:22:52
 */

/* Include Files */
#include <math.h>
#include <myCHOL1.h>
#include <string.h>
#include <stdint.h>

/* Function Definitions */
/*
 * Arguments    : const float A_data[]
 *                float L_data[]
 *                float invL_data[]
 * Return Type  : void
 */
void CHOL1(const float A_data[N*N], float L_data[N*N], float invL_data[N*N])
{
  float b_x_data[N*N], x_data[N], z1_data[N], s, smax;
  int16_t ipiv_data[N], p_data[N], b_i, b_n, i, i1, ipiv_size_idx_1, ix, j, jj, jp1j, k, ldap1, mmj_tmp, n, u1, x_size_idx_0, yk;
  n = N * N;
  if (0 <= n - 1) {
    memset(&L_data[0], 0, n * sizeof(float));
  }

  i = N;
  for (j = 0; j < i; j++)
  {
      i1 = N - j;
      for (ix = 0; ix < i1; ix++)
      {
          b_i = j + ix;
          if (b_i + 1 == j + 1)
          {
              n = j + 1;
              for (k = 0; k <= j; k++)
              {
                  smax = L_data[b_i + N * k];
                  z1_data[k] = smax * smax;
              }
              smax = z1_data[0];
              for (k = 2; k <= n; k++)
              {
                  smax += z1_data[k - 1];
              }
              L_data[b_i + N * j] = sqrt(A_data[b_i + N * j] - smax);
          }
          else
          {
              yk = j + 1;
              for (jp1j = 0; jp1j <= j; jp1j++)
              {
                  n = N * jp1j;
                  x_data[jp1j] = L_data[b_i + n] * L_data[j + n];
              }
              smax = x_data[0];
              for (k = 2; k <= yk; k++)
              {
                  smax += x_data[k - 1];
              }
              n = N * j;
              L_data[b_i + n] = (A_data[b_i + N * j] - smax) / L_data[j + n];
          }
      }
  }

  b_n = N;
  n = N * N;
  if (0 <= n - 1)
  {
      memset(&invL_data[0], 0, n * sizeof(float));
  }
  x_size_idx_0 = N;
  if (0 <= n - 1)
  {
      memcpy(&b_x_data[0], &L_data[0], n * sizeof(float));
  }

  n = N;
  ipiv_size_idx_1 = N;
  ipiv_data[0] = 1;
  yk = 1;
  for (k = 2; k <= n; k++)
  {
      yk++;
      ipiv_data[k - 1] = yk;
  }

  ldap1 = N;
  n = N - 1;
  u1 = N;
  if (n < u1)
  {
      u1 = n;
  }

  for (j = 0; j < u1; j++)
  {
      mmj_tmp = b_n - j;
      yk = j * (b_n + 1);
      jj = j * (ldap1 + 1);
      jp1j = yk + 2;
      if (mmj_tmp < 1)
      {
          n = -1;
      }
      else
      {
          n = 0;
          if (mmj_tmp > 1)
          {
              ix = yk;
              smax = fabs(b_x_data[jj]);
              for (k = 2; k <= mmj_tmp; k++)
              {
                  ix++;
                  s = fabs(b_x_data[ix]);
                  if (s > smax)
                  {
                      n = k - 1;
                      smax = s;
                  }
              }
          }
      }

      if (b_x_data[jj + n] != 0.0)
      {
          if (n != 0)
          {
              n += j;
              ipiv_data[j] = n + 1;
              ix = j;
              for (k = 0; k < b_n; k++)
              {
                  smax = b_x_data[ix];
                  b_x_data[ix] = b_x_data[n];
                  b_x_data[n] = smax;
                  ix += b_n;
                  n += b_n;
              }
          }
          i = jj + mmj_tmp;
          for (ix = jp1j; ix <= i; ix++)
          {
              b_x_data[ix - 1] /= b_x_data[jj];
          }
      }

      n = yk + b_n;
      yk = jj + ldap1;
      for (b_i = 0; b_i <= mmj_tmp - 2; b_i++)
      {
          smax = b_x_data[n];
          if (b_x_data[n] != 0.0)
          {
              ix = jj + 1;
              i = yk + 2;
              i1 = mmj_tmp + yk;
              for (jp1j = i; jp1j <= i1; jp1j++)
              {
                  b_x_data[jp1j - 1] += b_x_data[ix] * -smax;
                  ix++;
              }
          }
          n += b_n;
          yk += b_n;
      }
  }

  n = N;
  p_data[0] = 1;
  yk = 1;
  for (k = 2; k <= n; k++)
  {
      yk++;
      p_data[k - 1] = yk;
  }

  for (k = 0; k < ipiv_size_idx_1; k++)
  {
      i = ipiv_data[k];
      if (i > k + 1)
      {
          n = p_data[i - 1];
          p_data[i - 1] = p_data[k];
          p_data[k] = n;
      }
  }

  for (k = 0; k < b_n; k++)
  {
      i = p_data[k];
      n = N * (i - 1);
      invL_data[k + n] = 1.0;
      for (j = k + 1; j <= b_n; j++)
      {
          if (invL_data[(j + n) - 1] != 0.0)
          {
              i1 = j + 1;
              for (ix = i1; ix <= b_n; ix++)
              {
                  yk = (ix + N * (i - 1)) - 1;
                  invL_data[yk] -= invL_data[(j + N * (i - 1)) - 1] *b_x_data[(ix + x_size_idx_0 * (j - 1)) - 1];
              }
          }
      }
  }

  for (j = 0; j < b_n; j++)
  {
      n = b_n * j - 1;
      for (k = b_n; k >= 1; k--)
      {
          yk = b_n * (k - 1) - 1;
          i = k + n;
          if (invL_data[i] != 0.0)
          {
              invL_data[i] /= b_x_data[k + yk];
              for (ix = 0; ix <= k - 2; ix++)
              {
                  i1 = (ix + n) + 1;
                  invL_data[i1] -= invL_data[i] * b_x_data[(ix + yk) + 1];
              }
          }
      }
  }

}

/*
 * File trailer for myCHOL1.c
 *
 * [EOF]
 */
