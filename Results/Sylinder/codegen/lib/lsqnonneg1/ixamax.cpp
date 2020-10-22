/*
 * ixamax.cpp
 *
 * Code generation for function 'ixamax'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "ixamax.h"

/* Function Definitions */
int ixamax(int n, const double x_data[], int ix0)
{
  int idxmax;
  int ix;
  double smax;
  int k;
  double s;
  if (n < 1) {
    idxmax = 0;
  } else {
    idxmax = 1;
    if (n > 1) {
      ix = ix0 - 1;
      smax = std::abs(x_data[ix0 - 1]);
      for (k = 2; k <= n; k++) {
        ix++;
        s = std::abs(x_data[ix]);
        if (s > smax) {
          idxmax = k;
          smax = s;
        }
      }
    }
  }

  return idxmax;
}

/* End of code generation (ixamax.cpp) */
