/*
 * sum.cpp
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "sum.h"

/* Function Definitions */
double sum(const double x[2400])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 2399; k++) {
    y += x[k + 1];
  }

  return y;
}

/* End of code generation (sum.cpp) */
