/*
 * xgeqp3.cpp
 *
 * Code generation for function 'xgeqp3'
 *
 */

/* Include files */
#include <cmath>
#include <string.h>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "xgeqp3.h"
#include "xnrm2.h"
#include "sqrt.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "xswap.h"
#include "ixamax.h"

/* Function Definitions */
void xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int
            jpvt_data[], int jpvt_size[2])
{
  int n;
  int mn;
  int b_n;
  int yk;
  short unnamed_idx_0;
  int pvt;
  static double work_data[3202];
  int i;
  static double vn1_data[3202];
  double vn2_data[3202];
  int itemp;
  double temp1;
  double temp2;
  n = A->size[1];
  mn = A->size[1];
  if (2400 < mn) {
    mn = 2400;
  }

  tau_size[0] = (short)mn;
  if (A->size[1] < 1) {
    b_n = 0;
  } else {
    b_n = A->size[1];
  }

  jpvt_size[0] = 1;
  jpvt_size[1] = b_n;
  if (b_n > 0) {
    jpvt_data[0] = 1;
    yk = 1;
    for (pvt = 2; pvt <= b_n; pvt++) {
      yk++;
      jpvt_data[pvt - 1] = yk;
    }
  }

  if (A->size[1] != 0) {
    unnamed_idx_0 = (short)A->size[1];
    b_n = unnamed_idx_0;
    if (0 <= b_n - 1) {
      memset(&work_data[0], 0, (unsigned int)(b_n * (int)sizeof(double)));
    }

    pvt = 1;
    for (b_n = 0; b_n < n; b_n++) {
      vn1_data[b_n] = xnrm2(A, pvt);
      vn2_data[b_n] = vn1_data[b_n];
      pvt += 2400;
    }

    for (i = 1; i <= mn; i++) {
      b_n = (i + (i - 1) * 2400) - 1;
      yk = n - i;
      pvt = (i + ixamax(1 + yk, vn1_data, i)) - 2;
      if (pvt + 1 != i) {
        b_xswap(A, 1 + 2400 * pvt, 1 + 2400 * (i - 1));
        itemp = jpvt_data[pvt];
        jpvt_data[pvt] = jpvt_data[i - 1];
        jpvt_data[i - 1] = itemp;
        vn1_data[pvt] = vn1_data[i - 1];
        vn2_data[pvt] = vn2_data[i - 1];
      }

      if (i < 2400) {
        temp1 = A->data[b_n];
        tau_data[i - 1] = xzlarfg(2401 - i, &temp1, A, b_n + 2);
        A->data[b_n] = temp1;
      } else {
        tau_data[2399] = 0.0;
      }

      if (i < n) {
        temp1 = A->data[b_n];
        A->data[b_n] = 1.0;
        xzlarf(2401 - i, yk, b_n + 1, tau_data[i - 1], A, i + i * 2400,
               work_data);
        A->data[b_n] = temp1;
      }

      for (b_n = i; b_n < n; b_n++) {
        if (vn1_data[b_n] != 0.0) {
          temp1 = std::abs(A->data[(i + A->size[0] * b_n) - 1]) / vn1_data[b_n];
          temp1 = 1.0 - temp1 * temp1;
          if (temp1 < 0.0) {
            temp1 = 0.0;
          }

          temp2 = vn1_data[b_n] / vn2_data[b_n];
          temp2 = temp1 * (temp2 * temp2);
          if (temp2 <= 1.4901161193847656E-8) {
            if (i < 2400) {
              vn1_data[b_n] = b_xnrm2(2400 - i, A, (i + 2400 * b_n) + 1);
              vn2_data[b_n] = vn1_data[b_n];
            } else {
              vn1_data[b_n] = 0.0;
              vn2_data[b_n] = 0.0;
            }
          } else {
            b_sqrt(&temp1);
            vn1_data[b_n] *= temp1;
          }
        }
      }
    }
  }
}

/* End of code generation (xgeqp3.cpp) */
