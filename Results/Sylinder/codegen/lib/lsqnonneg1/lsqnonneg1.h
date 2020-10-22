/*
 * lsqnonneg1.h
 *
 * Code generation for function 'lsqnonneg1'
 *
 */

#ifndef LSQNONNEG1_H
#define LSQNONNEG1_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "lsqnonneg1_types.h"

/* Function Declarations */
extern void lsqnonneg1(const coder_internal_sparse C, const double d[2400],
  double tol, double x[3202], double *resnorm, double resid[2400], double
  *exitflag, double lambda[3202]);

#endif

/* End of code generation (lsqnonneg1.h) */
