/*
 * xswap.cpp
 *
 * Code generation for function 'xswap'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "xswap.h"

/* Function Definitions */
void b_xswap(emxArray_real_T *x, int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 2400; k++) {
    temp = x->data[ix];
    x->data[ix] = x->data[iy];
    x->data[iy] = temp;
    ix++;
    iy++;
  }
}

void xswap(emxArray_real_T *x, int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 2400; k++) {
    temp = x->data[ix];
    x->data[ix] = x->data[iy];
    x->data[iy] = temp;
    ix += 2400;
    iy += 2400;
  }
}

/* End of code generation (xswap.cpp) */
