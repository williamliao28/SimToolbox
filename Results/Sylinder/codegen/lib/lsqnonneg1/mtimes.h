/*
 * mtimes.h
 *
 * Code generation for function 'mtimes'
 *
 */

#ifndef MTIMES_H
#define MTIMES_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "lsqnonneg1_types.h"

/* Function Declarations */
extern void b_sparse_mtimes(const emxArray_real_T *a_d, const emxArray_int32_T
  *a_colidx, const emxArray_int32_T *a_rowidx, const double b[2400], double c
  [3202]);
extern void sparse_mtimes(const emxArray_real_T *a_d, const emxArray_int32_T
  *a_colidx, const emxArray_int32_T *a_rowidx, const double b[3202], double c
  [2400]);

#endif

/* End of code generation (mtimes.h) */
