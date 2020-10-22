/*
 * lsqnonneg1_emxAPI.h
 *
 * Code generation for function 'lsqnonneg1_emxAPI'
 *
 */

#ifndef LSQNONNEG1_EMXAPI_H
#define LSQNONNEG1_EMXAPI_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "lsqnonneg1_types.h"

/* Function Declarations */
extern emxArray_int32_T *emxCreateND_int32_T(int numDimensions, int *size);
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_int32_T *emxCreateWrapperND_int32_T(int *data, int numDimensions,
  int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, int *size);
extern emxArray_int32_T *emxCreateWrapper_int32_T(int *data, int rows, int cols);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_int32_T *emxCreate_int32_T(int rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_int32_T(emxArray_int32_T *emxArray);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxDestroy_coder_internal_sparse(coder_internal_sparse emxArray);
extern void emxInit_coder_internal_sparse(coder_internal_sparse *pStruct);

#endif

/* End of code generation (lsqnonneg1_emxAPI.h) */
