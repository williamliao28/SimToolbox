/*
 * xgetrf.cpp
 *
 * Code generation for function 'xgetrf'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "xgetrf.h"
#include "xswap.h"

/* Function Definitions */
void xgetrf(emxArray_real_T *A, int ipiv[2400], int *info)
{
  int i2;
  int j;
  int c;
  int jA;
  int ix;
  double smax;
  int jy;
  double s;
  int b_j;
  int ijA;
  for (i2 = 0; i2 < 2400; i2++) {
    ipiv[i2] = 1 + i2;
  }

  *info = 0;
  for (j = 0; j < 2399; j++) {
    c = j * 2401;
    jA = 1;
    ix = c;
    smax = std::abs(A->data[c]);
    for (jy = 2; jy <= 2400 - j; jy++) {
      ix++;
      s = std::abs(A->data[ix]);
      if (s > smax) {
        jA = jy;
        smax = s;
      }
    }

    if (A->data[(c + jA) - 1] != 0.0) {
      if (jA - 1 != 0) {
        ipiv[j] = j + jA;
        xswap(A, j + 1, j + jA);
      }

      i2 = (c - j) + 2400;
      for (jA = c + 1; jA < i2; jA++) {
        A->data[jA] /= A->data[c];
      }
    } else {
      *info = j + 1;
    }

    jA = c + 2401;
    jy = c + 2400;
    for (b_j = 1; b_j <= 2399 - j; b_j++) {
      smax = A->data[jy];
      if (A->data[jy] != 0.0) {
        ix = c + 1;
        i2 = (jA - j) + 2399;
        for (ijA = jA; ijA < i2; ijA++) {
          A->data[ijA] += A->data[ix] * -smax;
          ix++;
        }
      }

      jy += 2400;
      jA += 2400;
    }
  }

  if ((*info == 0) && (!(A->data[2399 + A->size[0] * 2399] != 0.0))) {
    *info = 2400;
  }
}

/* End of code generation (xgetrf.cpp) */
