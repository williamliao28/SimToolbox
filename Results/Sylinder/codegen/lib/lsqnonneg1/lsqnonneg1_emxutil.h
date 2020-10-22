/*
 * lsqnonneg1_emxutil.h
 *
 * Code generation for function 'lsqnonneg1_emxutil'
 *
 */

#ifndef LSQNONNEG1_EMXUTIL_H
#define LSQNONNEG1_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "lsqnonneg1_types.h"

/* Function Declarations */
extern void c_emxFreeStruct_coder_internal_(coder_internal_sparse_2 *pStruct);
extern void c_emxInitStruct_coder_internal_(coder_internal_sparse_2 *pStruct);
extern void d_emxFreeStruct_coder_internal_(coder_internal_sparse *pStruct);
extern void d_emxInitStruct_coder_internal_(coder_internal_sparse *pStruct);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T1(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_real_T1(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (lsqnonneg1_emxutil.h) */
