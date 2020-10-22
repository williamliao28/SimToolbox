/*
 * abs.cpp
 *
 * Code generation for function 'abs'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "abs.h"

/* Function Definitions */
void b_abs(const double x[3202], double y[3202])
{
  int k;
  for (k = 0; k < 3202; k++) {
    y[k] = std::abs(x[k]);
  }
}

/* End of code generation (abs.cpp) */
