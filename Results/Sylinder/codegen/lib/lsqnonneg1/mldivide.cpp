/*
 * mldivide.cpp
 *
 * Code generation for function 'mldivide'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "mldivide.h"
#include "lusolve.h"
#include "qrsolve.h"

/* Function Definitions */
void mldivide(const emxArray_real_T *A, const double B[2400], double Y_data[],
              int Y_size[1])
{
  double dv0[2400];
  if (A->size[1] == 0) {
    Y_size[0] = 0;
  } else if (2400 == A->size[1]) {
    memcpy(&dv0[0], &B[0], 2400U * sizeof(double));
    lusolve(A, dv0);
    Y_size[0] = 2400;
    memcpy(&Y_data[0], &dv0[0], 2400U * sizeof(double));
  } else {
    qrsolve(A, B, Y_data, Y_size);
  }
}

/* End of code generation (mldivide.cpp) */
