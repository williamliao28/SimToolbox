/*
 * xzlarfg.cpp
 *
 * Code generation for function 'xzlarfg'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "xzlarfg.h"
#include "xnrm2.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

double xzlarfg(int n, double *alpha1, emxArray_real_T *x, int ix0)
{
  double tau;
  double xnorm;
  int knt;
  int i3;
  int k;
  tau = 0.0;
  xnorm = b_xnrm2(n - 1, x, ix0);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(*alpha1, xnorm);
    if (*alpha1 >= 0.0) {
      xnorm = -xnorm;
    }

    if (std::abs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      i3 = (ix0 + n) - 2;
      do {
        knt++;
        for (k = ix0; k <= i3; k++) {
          x->data[k - 1] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        *alpha1 *= 9.9792015476736E+291;
      } while (!(std::abs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(*alpha1, b_xnrm2(n - 1, x, ix0));
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      tau = (xnorm - *alpha1) / xnorm;
      *alpha1 = 1.0 / (*alpha1 - xnorm);
      i3 = (ix0 + n) - 2;
      for (k = ix0; k <= i3; k++) {
        x->data[k - 1] *= *alpha1;
      }

      for (k = 1; k <= knt; k++) {
        xnorm *= 1.0020841800044864E-292;
      }

      *alpha1 = xnorm;
    } else {
      tau = (xnorm - *alpha1) / xnorm;
      *alpha1 = 1.0 / (*alpha1 - xnorm);
      i3 = (ix0 + n) - 2;
      for (k = ix0; k <= i3; k++) {
        x->data[k - 1] *= *alpha1;
      }

      *alpha1 = xnorm;
    }
  }

  return tau;
}

/* End of code generation (xzlarfg.cpp) */
