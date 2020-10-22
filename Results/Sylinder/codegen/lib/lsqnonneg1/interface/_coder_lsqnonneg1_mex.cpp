/*
 * _coder_lsqnonneg1_mex.cpp
 *
 * Code generation for function '_coder_lsqnonneg1_mex'
 *
 */

/* Include files */
#include "_coder_lsqnonneg1_api.h"
#include "_coder_lsqnonneg1_mex.h"

/* Function Declarations */
static void lsqnonneg1_mexFunction(int32_T nlhs, mxArray *plhs[5], int32_T nrhs,
  const mxArray *prhs[3]);

/* Function Definitions */
static void lsqnonneg1_mexFunction(int32_T nlhs, mxArray *plhs[5], int32_T nrhs,
  const mxArray *prhs[3])
{
  const mxArray *outputs[5];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        10, "lsqnonneg1");
  }

  if (nlhs > 5) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 10,
                        "lsqnonneg1");
  }

  /* Call the function. */
  lsqnonneg1_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  lsqnonneg1_terminate();
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(lsqnonneg1_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  lsqnonneg1_initialize();

  /* Dispatch the entry-point. */
  lsqnonneg1_mexFunction(nlhs, plhs, nrhs, prhs);
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_lsqnonneg1_mex.cpp) */
