/*
 * rdivide.cpp
 *
 * Code generation for function 'rdivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "rdivide.h"

/* Function Definitions */
void rdivide(const double x_data[], const int x_size[1], const double y_data[],
             double z_data[], int z_size[1])
{
  int loop_ub;
  int i1;
  z_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    z_data[i1] = x_data[i1] / y_data[i1];
  }
}

/* End of code generation (rdivide.cpp) */
