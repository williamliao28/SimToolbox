/*
 * _coder_lsqnonneg1_api.h
 *
 * Code generation for function '_coder_lsqnonneg1_api'
 *
 */

#ifndef _CODER_LSQNONNEG1_API_H
#define _CODER_LSQNONNEG1_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_lsqnonneg1_api.h"

/* Type Definitions */
#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef typedef_coder_internal_sparse
#define typedef_coder_internal_sparse

typedef struct {
  emxArray_real_T *d;
  emxArray_int32_T *colidx;
  emxArray_int32_T *rowidx;
  int32_T maxnz;
} coder_internal_sparse;

#endif                                 /*typedef_coder_internal_sparse*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void lsqnonneg1(coder_internal_sparse C, real_T d[2400], real_T tol,
  real_T x[3202], real_T *resnorm, real_T resid[2400], real_T *exitflag, real_T
  lambda[3202]);
extern void lsqnonneg1_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[5]);
extern void lsqnonneg1_atexit(void);
extern void lsqnonneg1_initialize(void);
extern void lsqnonneg1_terminate(void);
extern void lsqnonneg1_xil_terminate(void);

#endif

/* End of code generation (_coder_lsqnonneg1_api.h) */
