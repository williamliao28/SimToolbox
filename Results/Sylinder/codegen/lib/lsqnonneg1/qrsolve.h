/*
 * qrsolve.h
 *
 * Code generation for function 'qrsolve'
 *
 */

#ifndef QRSOLVE_H
#define QRSOLVE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "lsqnonneg1_types.h"

/* Function Declarations */
extern void qrsolve(const emxArray_real_T *A, const double B[2400], double
                    Y_data[], int Y_size[1]);

#endif

/* End of code generation (qrsolve.h) */
