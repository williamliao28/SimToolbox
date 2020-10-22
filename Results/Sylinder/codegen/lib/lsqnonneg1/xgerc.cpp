/*
 * xgerc.cpp
 *
 * Code generation for function 'xgerc'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "xgerc.h"

/* Function Definitions */
void xgerc(int m, int n, double alpha1, int ix0, const double y_data[],
           emxArray_real_T *A, int ia0)
{
  int jA;
  int jy;
  int j;
  double temp;
  int ix;
  int i6;
  int ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if (y_data[jy] != 0.0) {
        temp = y_data[jy] * alpha1;
        ix = ix0;
        i6 = m + jA;
        for (ijA = jA; ijA < i6; ijA++) {
          A->data[ijA] += A->data[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += 2400;
    }
  }
}

/* End of code generation (xgerc.cpp) */
