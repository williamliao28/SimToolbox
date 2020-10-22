/*
 * xtrsm.cpp
 *
 * Code generation for function 'xtrsm'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "xtrsm.h"

/* Function Definitions */
void b_xtrsm(const emxArray_real_T *A, double B[2400])
{
  int k;
  int kAcol;
  int i;
  for (k = 2399; k >= 0; k--) {
    kAcol = 2400 * k;
    if (B[k] != 0.0) {
      B[k] /= A->data[k + kAcol];
      for (i = 0; i < k; i++) {
        B[i] -= B[k] * A->data[i + kAcol];
      }
    }
  }
}

void xtrsm(const emxArray_real_T *A, double B[2400])
{
  int k;
  int kAcol;
  int i;
  for (k = 0; k < 2400; k++) {
    kAcol = 2400 * k;
    if (B[k] != 0.0) {
      for (i = k + 1; i + 1 < 2401; i++) {
        B[i] -= B[k] * A->data[i + kAcol];
      }
    }
  }
}

/* End of code generation (xtrsm.cpp) */
