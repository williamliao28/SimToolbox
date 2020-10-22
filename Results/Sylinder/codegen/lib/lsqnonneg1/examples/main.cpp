/*
 * main.cpp
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "main.h"
#include "lsqnonneg1_terminate.h"
#include "lsqnonneg1_emxAPI.h"
#include "lsqnonneg1_initialize.h"

/* Function Declarations */
static void argInit_2400x1_real_T(double result[2400]);
static emxArray_int32_T *argInit_Unboundedx1_int32_T();
static emxArray_real_T *argInit_Unboundedx1_real_T();
static coder_internal_sparse argInit_coder_internal_sparse();
static int argInit_int32_T();
static double argInit_real_T();
static void main_lsqnonneg1();

/* Function Definitions */
static void argInit_2400x1_real_T(double result[2400])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2400; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static emxArray_int32_T *argInit_Unboundedx1_int32_T()
{
  emxArray_int32_T *result;
  static int iv1[1] = { 2 };

  int idx0;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_int32_T(1, iv1);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[idx0] = argInit_int32_T();
  }

  return result;
}

static emxArray_real_T *argInit_Unboundedx1_real_T()
{
  emxArray_real_T *result;
  static int iv0[1] = { 2 };

  int idx0;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real_T(1, iv0);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[idx0] = argInit_real_T();
  }

  return result;
}

static coder_internal_sparse argInit_coder_internal_sparse()
{
  coder_internal_sparse result;

  /* Set the value of each structure field.
     Change this value to the value that the application requires. */
  result.d = argInit_Unboundedx1_real_T();
  result.colidx = argInit_Unboundedx1_int32_T();
  result.rowidx = argInit_Unboundedx1_int32_T();
  result.maxnz = argInit_int32_T();
  return result;
}

static int argInit_int32_T()
{
  return 0;
}

static double argInit_real_T()
{
  return 0.0;
}

static void main_lsqnonneg1()
{
  coder_internal_sparse C;
  double dv1[2400];
  static double x[3202];
  double resnorm;
  double resid[2400];
  double exitflag;
  static double lambda[3202];

  /* Initialize function 'lsqnonneg1' input arguments. */
  /* Initialize function input argument 'C'. */
  C = argInit_coder_internal_sparse();

  /* Initialize function input argument 'd'. */
  /* Call the entry-point 'lsqnonneg1'. */
  argInit_2400x1_real_T(dv1);
  lsqnonneg1(C, dv1, argInit_real_T(), x, &resnorm, resid, &exitflag, lambda);
  emxDestroy_coder_internal_sparse(C);
}

int main(int, const char * const [])
{
  /* Initialize the application.
     You do not need to do this more than one time. */
  lsqnonneg1_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_lsqnonneg1();

  /* Terminate the application.
     You do not need to do this more than one time. */
  lsqnonneg1_terminate();
  return 0;
}

/* End of code generation (main.cpp) */
