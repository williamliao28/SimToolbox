/*
 * xgemv.h
 *
 * Code generation for function 'xgemv'
 *
 */

#ifndef XGEMV_H
#define XGEMV_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "lsqnonneg1_types.h"

/* Function Declarations */
extern void xgemv(int m, int n, const emxArray_real_T *A, int ia0, const
                  emxArray_real_T *x, int ix0, double y_data[]);

#endif

/* End of code generation (xgemv.h) */
