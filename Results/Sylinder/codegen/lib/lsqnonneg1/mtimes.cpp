/*
 * mtimes.cpp
 *
 * Code generation for function 'mtimes'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "mtimes.h"

/* Function Definitions */
void b_sparse_mtimes(const emxArray_real_T *a_d, const emxArray_int32_T
                     *a_colidx, const emxArray_int32_T *a_rowidx, const double
                     b[2400], double c[3202])
{
  int acol;
  double bc;
  int nap;
  int apend1;
  memset(&c[0], 0, 3202U * sizeof(double));
  if (a_colidx->data[a_colidx->size[0] - 1] - 1 != 0) {
    for (acol = 0; acol < 2400; acol++) {
      bc = b[acol];
      nap = a_colidx->data[acol + 1] - a_colidx->data[acol];
      if (nap >= 4) {
        apend1 = ((a_colidx->data[acol + 1] - nap) + ((nap / 4) << 2)) - 1;
        for (nap = a_colidx->data[acol]; nap <= apend1; nap += 4) {
          c[a_rowidx->data[nap - 1] - 1] += a_d->data[nap - 1] * bc;
          c[a_rowidx->data[nap] - 1] += a_d->data[nap] * bc;
          c[a_rowidx->data[nap + 1] - 1] += a_d->data[nap + 1] * bc;
          c[a_rowidx->data[nap + 2] - 1] += a_d->data[nap + 2] * bc;
        }

        while (apend1 + 1 <= a_colidx->data[acol + 1] - 1) {
          c[a_rowidx->data[apend1] - 1] += a_d->data[apend1] * bc;
          apend1++;
        }
      } else {
        for (nap = a_colidx->data[acol] - 1; nap < a_colidx->data[acol + 1] - 1;
             nap++) {
          c[a_rowidx->data[nap] - 1] += a_d->data[nap] * bc;
        }
      }
    }
  }
}

void sparse_mtimes(const emxArray_real_T *a_d, const emxArray_int32_T *a_colidx,
                   const emxArray_int32_T *a_rowidx, const double b[3202],
                   double c[2400])
{
  int acol;
  double bc;
  int nap;
  int apend1;
  memset(&c[0], 0, 2400U * sizeof(double));
  if (a_colidx->data[a_colidx->size[0] - 1] - 1 != 0) {
    for (acol = 0; acol < 3202; acol++) {
      bc = b[acol];
      nap = a_colidx->data[acol + 1] - a_colidx->data[acol];
      if (nap >= 4) {
        apend1 = ((a_colidx->data[acol + 1] - nap) + ((nap / 4) << 2)) - 1;
        for (nap = a_colidx->data[acol]; nap <= apend1; nap += 4) {
          c[a_rowidx->data[nap - 1] - 1] += a_d->data[nap - 1] * bc;
          c[a_rowidx->data[nap] - 1] += a_d->data[nap] * bc;
          c[a_rowidx->data[nap + 1] - 1] += a_d->data[nap + 1] * bc;
          c[a_rowidx->data[nap + 2] - 1] += a_d->data[nap + 2] * bc;
        }

        while (apend1 + 1 <= a_colidx->data[acol + 1] - 1) {
          c[a_rowidx->data[apend1] - 1] += a_d->data[apend1] * bc;
          apend1++;
        }
      } else {
        for (nap = a_colidx->data[acol] - 1; nap < a_colidx->data[acol + 1] - 1;
             nap++) {
          c[a_rowidx->data[nap] - 1] += a_d->data[nap] * bc;
        }
      }
    }
  }
}

/* End of code generation (mtimes.cpp) */
