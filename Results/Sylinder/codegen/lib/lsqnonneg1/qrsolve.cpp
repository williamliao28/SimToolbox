/*
 * qrsolve.cpp
 *
 * Code generation for function 'qrsolve'
 *
 */

/* Include files */
#include <cmath>
#include <string.h>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "qrsolve.h"
#include "lsqnonneg1_emxutil.h"
#include "xgeqp3.h"

/* Function Declarations */
static int rankFromQR(const emxArray_real_T *A);

/* Function Definitions */
static int rankFromQR(const emxArray_real_T *A)
{
  int r;
  int minmn;
  int maxmn;
  double tol;
  r = 0;
  if (2400 < A->size[1]) {
    minmn = 2400;
    maxmn = A->size[1];
  } else {
    minmn = A->size[1];
    maxmn = 2400;
  }

  if (minmn > 0) {
    tol = (double)maxmn * std::abs(A->data[0]) * 2.2204460492503131E-16;
    while ((r < minmn) && (!(std::abs(A->data[r + A->size[0] * r]) <= tol))) {
      r++;
    }
  }

  return r;
}

void qrsolve(const emxArray_real_T *A, const double B[2400], double Y_data[],
             int Y_size[1])
{
  emxArray_real_T *b_A;
  int mn;
  int loop_ub;
  double tau_data[2400];
  int tau_size[1];
  int jpvt_data[3202];
  int jpvt_size[2];
  int rankA;
  double b_B[2400];
  short unnamed_idx_0;
  int i;
  double wj;
  emxInit_real_T1(&b_A, 2);
  mn = b_A->size[0] * b_A->size[1];
  b_A->size[0] = 2400;
  b_A->size[1] = A->size[1];
  emxEnsureCapacity_real_T1(b_A, mn);
  loop_ub = A->size[0] * A->size[1];
  for (mn = 0; mn < loop_ub; mn++) {
    b_A->data[mn] = A->data[mn];
  }

  xgeqp3(b_A, tau_data, tau_size, jpvt_data, jpvt_size);
  rankA = rankFromQR(b_A);
  memcpy(&b_B[0], &B[0], 2400U * sizeof(double));
  unnamed_idx_0 = (short)b_A->size[1];
  Y_size[0] = unnamed_idx_0;
  loop_ub = unnamed_idx_0;
  if (0 <= loop_ub - 1) {
    memset(&Y_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  mn = b_A->size[1];
  if (2400 < mn) {
    mn = 2400;
  }

  for (loop_ub = 0; loop_ub < mn; loop_ub++) {
    if (tau_data[loop_ub] != 0.0) {
      wj = b_B[loop_ub];
      for (i = loop_ub + 1; i < 2400; i++) {
        wj += b_A->data[i + b_A->size[0] * loop_ub] * b_B[i];
      }

      wj *= tau_data[loop_ub];
      if (wj != 0.0) {
        b_B[loop_ub] -= wj;
        for (i = loop_ub + 1; i < 2400; i++) {
          b_B[i] -= b_A->data[i + b_A->size[0] * loop_ub] * wj;
        }
      }
    }
  }

  for (i = 0; i < rankA; i++) {
    Y_data[jpvt_data[i] - 1] = b_B[i];
  }

  for (loop_ub = rankA - 1; loop_ub + 1 > 0; loop_ub--) {
    Y_data[jpvt_data[loop_ub] - 1] /= b_A->data[loop_ub + b_A->size[0] * loop_ub];
    for (i = 0; i < loop_ub; i++) {
      Y_data[jpvt_data[i] - 1] -= Y_data[jpvt_data[loop_ub] - 1] * b_A->data[i +
        b_A->size[0] * loop_ub];
    }
  }

  emxFree_real_T(&b_A);
}

/* End of code generation (qrsolve.cpp) */
