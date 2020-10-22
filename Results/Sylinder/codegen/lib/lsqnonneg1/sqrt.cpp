/*
 * sqrt.cpp
 *
 * Code generation for function 'sqrt'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "sqrt.h"

/* Function Definitions */
void b_sqrt(double *x)
{
  *x = std::sqrt(*x);
}

/* End of code generation (sqrt.cpp) */
