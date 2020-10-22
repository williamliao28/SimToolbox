/*
 * lusolve.cpp
 *
 * Code generation for function 'lusolve'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "lusolve.h"
#include "lsqnonneg1_emxutil.h"
#include "xtrsm.h"
#include "xgetrf.h"

/* Function Definitions */
void lusolve(const emxArray_real_T *A, double B[2400])
{
  emxArray_real_T *b_A;
  int info;
  int loop_ub;
  int ipiv[2400];
  double temp;
  emxInit_real_T1(&b_A, 2);
  info = b_A->size[0] * b_A->size[1];
  b_A->size[0] = 2400;
  b_A->size[1] = A->size[1];
  emxEnsureCapacity_real_T1(b_A, info);
  loop_ub = A->size[0] * A->size[1];
  for (info = 0; info < loop_ub; info++) {
    b_A->data[info] = A->data[info];
  }

  xgetrf(b_A, ipiv, &info);
  for (info = 0; info < 2399; info++) {
    if (ipiv[info] != info + 1) {
      temp = B[info];
      B[info] = B[ipiv[info] - 1];
      B[ipiv[info] - 1] = temp;
    }
  }

  xtrsm(b_A, B);
  b_xtrsm(b_A, B);
  emxFree_real_T(&b_A);
}

/* End of code generation (lusolve.cpp) */
