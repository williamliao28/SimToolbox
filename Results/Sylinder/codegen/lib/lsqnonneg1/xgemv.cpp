/*
 * xgemv.cpp
 *
 * Code generation for function 'xgemv'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "xgemv.h"

/* Function Definitions */
void xgemv(int m, int n, const emxArray_real_T *A, int ia0, const
           emxArray_real_T *x, int ix0, double y_data[])
{
  int iy;
  int i4;
  int iac;
  int ix;
  double c;
  int i5;
  int ia;
  if (n != 0) {
    for (iy = 1; iy <= n; iy++) {
      y_data[iy - 1] = 0.0;
    }

    iy = 0;
    i4 = ia0 + 2400 * (n - 1);
    for (iac = ia0; iac <= i4; iac += 2400) {
      ix = ix0;
      c = 0.0;
      i5 = (iac + m) - 1;
      for (ia = iac; ia <= i5; ia++) {
        c += A->data[ia - 1] * x->data[ix - 1];
        ix++;
      }

      y_data[iy] += c;
      iy++;
    }
  }
}

/* End of code generation (xgemv.cpp) */
