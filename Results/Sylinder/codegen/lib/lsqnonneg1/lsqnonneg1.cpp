/*
 * lsqnonneg1.cpp
 *
 * Code generation for function 'lsqnonneg1'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "lsqnonneg1_emxutil.h"
#include "sum.h"
#include "mldivide.h"
#include "sparse.h"
#include "abs.h"
#include "rdivide.h"
#include "mtimes.h"
#include "any1.h"

/* Function Definitions */
void lsqnonneg1(const coder_internal_sparse C, const double d[2400], double tol,
                double x[3202], double *resnorm, double resid[2400], double
                *exitflag, double lambda[3202])
{
  int i;
  static double ii_data[3202];
  static double wz[3202];
  boolean_T P[3202];
  int partialTrueCount;
  boolean_T Z[3202];
  emxArray_real_T *t0_d;
  emxArray_int32_T *t0_colidx;
  emxArray_int32_T *t0_rowidx;
  int iter;
  emxArray_real_T *t1_d;
  emxArray_int32_T *t1_colidx;
  emxArray_int32_T *t1_rowidx;
  emxArray_real_T *r0;
  coder_internal_sparse_2 expl_temp;
  boolean_T guard1 = false;
  int exitg2;
  int trueCount;
  int lambda_size[1];
  short tmp_data[3202];
  boolean_T lambda_data[3202];
  static double z[3202];
  boolean_T exitg3;
  double alpha;
  short b_ii_data[3202];
  int ii_size[1];
  int varargin_1_size[1];
  int exitg1;
  int z_size[1];
  short b_tmp_data[3202];
  boolean_T b_Z;
  int x_size[1];
  short c_tmp_data[3202];
  double b_resid[2400];
  static double x_data[3202];
  static double b_x_data[3202];
  int b_ii_size[1];

  /* LSQNONNEG Linear least squares with nonnegativity constraints. */
  /*    X = LSQNONNEG(C,d) returns the vector X that minimizes NORM(d-C*X) */
  /*    subject to X >= 0. C and d must be real. */
  /*  */
  /*    X = LSQNONNEG(C,d,OPTIONS) minimizes with the default optimization */
  /*    parameters replaced by values in the structure OPTIONS, an argument */
  /*    created with the OPTIMSET function.  See OPTIMSET for details. Used */
  /*    options are Display and TolX. (A default tolerance TolX of  */
  /*    10*MAX(SIZE(C))*NORM(C,1)*EPS is used.)  */
  /*     */
  /*    X = LSQNONNEG(PROBLEM) finds the minimum for PROBLEM. PROBLEM is a */
  /*    structure with the matrix 'C' in PROBLEM.C, the vector 'd' in */
  /*    PROBLEM.d, the options structure in PROBLEM.options, and solver name */
  /*    'lsqnonneg' in PROBLEM.solver.  */
  /*  */
  /*    [X,RESNORM] = LSQNONNEG(...) also returns the value of the squared 2-norm of  */
  /*    the residual: norm(d-C*X)^2. */
  /*  */
  /*    [X,RESNORM,RESIDUAL] = LSQNONNEG(...) also returns the value of the   */
  /*    residual: d-C*X. */
  /*     */
  /*    [X,RESNORM,RESIDUAL,EXITFLAG] = LSQNONNEG(...) returns an EXITFLAG that */
  /*    describes the exit condition. Possible values of EXITFLAG and the */
  /*    corresponding exit conditions are */
  /*  */
  /*     1  LSQNONNEG converged with a solution X. */
  /*     0  Iteration count was exceeded. Increasing the tolerance */
  /*        (OPTIONS.TolX) may lead to a solution. */
  /*    */
  /*    [X,RESNORM,RESIDUAL,EXITFLAG,OUTPUT] = LSQNONNEG(...) returns a structure */
  /*    OUTPUT with the number of steps taken in OUTPUT.iterations, the type of  */
  /*    algorithm used in OUTPUT.algorithm, and the exit message in OUTPUT.message. */
  /*  */
  /*    [X,RESNORM,RESIDUAL,EXITFLAG,OUTPUT,LAMBDA] = LSQNONNEG(...) returns  */
  /*    the dual vector LAMBDA  where LAMBDA(i) <= 0 when X(i) is (approximately) 0  */
  /*    and LAMBDA(i) is (approximately) 0 when X(i) > 0. */
  /*   */
  /*    See also LSCOV, SLASH. */
  /*    Copyright 1984-2016 The MathWorks, Inc.  */
  /*  Reference: */
  /*   Lawson and Hanson, "Solving Least Squares Problems", Prentice-Hall, 1974. */
  /*  Check if more inputs have been passed. In that case error. */
  /* if nargin > 4 */
  /*     error('MATLAB:lsqnonneg:TooManyInputs',... */
  /*         getString(message('MATLAB:optimfun:lsqnonneg:TooManyInputs'))); */
  /* end */
  /* defaultopt = struct('Display','notify','TolX','10*eps*norm(C,1)*length(C)'); */
  /*  If just 'defaults' passed in, return the default options in X */
  /* if nargin == 1 && nargout <= 1 && strcmpi(C,'defaults') */
  /*     x = defaultopt; */
  /*     return */
  /* end */
  /* if nargin < 3 */
  /*     options = []; */
  /* end */
  /* if nargin == 1 */
  /*  Detect problem structure input */
  /*     if isa(C,'struct') */
  /*         [C,d,options] = separateOptimStruct(C); */
  /*     else % Single input and non-structure. */
  /*         error('MATLAB:lsqnonneg:InputArg',... */
  /*             getString(message('MATLAB:optimfun:lsqnonneg:InputArg'))); */
  /*     end */
  /* end */
  /* if nargin == 0 */
  /*     error('MATLAB:lsqnonneg:NotEnoughInputs',... */
  /*         getString(message('MATLAB:optimfun:lsqnonneg:NotEnoughInputs'))); */
  /* end */
  /* if ~isreal(C) || ~isreal(d) */
  /*     error('MATLAB:lsqnonneg:ComplexCorD',... */
  /*         getString(message('MATLAB:optimfun:lsqnonneg:ComplexCorD'))); */
  /* end */
  /*  Check for non-double inputs */
  /* if ~isa(C,'double') || ~isa(d,'double') */
  /*     error('MATLAB:lsqnonneg:NonDoubleInput',... */
  /*         getString(message('MATLAB:optimfun:lsqnonneg:NonDoubleInput'))); */
  /* end */
  /*  Check if options was created with optimoptions */
  /* if ~isempty(options) && isa(options,'optim.options.SolverOptions') */
  /*     error('MATLAB:lsqnonneg:ArgNotStruct',... */
  /*         getString(message('MATLAB:optimfun:commonMessages:ArgNotStruct', 3))); */
  /* end */
  /*  Check for deprecated syntax */
  /* options = deprecateX0(options,nargin,varargin{:}); */
  /* printtype = optimget(options,'Display',defaultopt,'fast'); */
  /* tol = optimget(options,'TolX',defaultopt,'fast'); */
  /*  In case the defaults were gathered from calling: optimset('lsqnonneg'): */
  /* if ischar(tol) || (isstring(tol) && isscalar(tol)) */
  /*     if strcmpi(tol,'10*eps*norm(c,1)*length(c)') */
  /*         tol = 10*eps*length(C); */
  /*     else */
  /*         error('MATLAB:lsqnonneg:OptTolXNotPosScalar',... */
  /*             getString(message('MATLAB:optimfun:lsqnonneg:OptTolXNotPosScalar'))); */
  /*     end */
  /* end */
  /* switch printtype */
  /*     case {'notify','notify-detailed'} */
  /*         verbosity = 1; */
  /*     case {'none','off'} */
  /*         verbosity = 0; */
  /*     case {'iter','iter-detailed'} */
  /*         warning('MATLAB:lsqnonneg:InvalidDisplayValueIter',... */
  /*             getString(message('MATLAB:optimfun:lsqnonneg:InvalidDisplayValueIter'))); */
  /*         verbosity = 3; */
  /*     case {'final','final-detailed'} */
  /*         verbosity = 2; */
  /*     otherwise */
  /*         error('MATLAB:lsqnonneg:InvalidOptParamDisplay',... */
  /*             getString(message('MATLAB:optimfun:lsqnonneg:InvalidOptParamDisplay'))); */
  /* end */
  /*  Initialize vector of n zeros and Infs (to be used later) */
  /*  Initialize set of non-active columns to null */
  /*  Initialize set of active columns to all and the initial point to zeros */
  for (i = 0; i < 3202; i++) {
    wz[i] = 0.0;
    P[i] = false;
    Z[i] = true;
    x[i] = 0.0;
  }

  memset(&ii_data[0], 0, 3202U * sizeof(double));
  sparse_mtimes(C.d, C.colidx, C.rowidx, ii_data, resid);
  for (partialTrueCount = 0; partialTrueCount < 2400; partialTrueCount++) {
    resid[partialTrueCount] = d[partialTrueCount] - resid[partialTrueCount];
  }

  emxInit_real_T(&t0_d, 1);
  emxInit_int32_T(&t0_colidx, 1);
  emxInit_int32_T(&t0_rowidx, 1);
  sparse_ctranspose(C.d, C.colidx, C.rowidx, t0_d, t0_colidx, t0_rowidx);
  b_sparse_mtimes(t0_d, t0_colidx, t0_rowidx, resid, lambda);

  /*  Set up iteration criterion */
  iter = 0;
  *exitflag = 1.0;

  /*  Outer loop to put variables into set to hold positive coefficients */
  emxInit_real_T(&t1_d, 1);
  emxInit_int32_T(&t1_colidx, 1);
  emxInit_int32_T(&t1_rowidx, 1);
  emxInit_real_T1(&r0, 2);
  c_emxInitStruct_coder_internal_(&expl_temp);
  guard1 = false;
  do {
    exitg2 = 0;
    if (any(Z)) {
      trueCount = 0;
      for (i = 0; i < 3202; i++) {
        if (Z[i]) {
          trueCount++;
        }
      }

      partialTrueCount = 0;
      for (i = 0; i < 3202; i++) {
        if (Z[i]) {
          tmp_data[partialTrueCount] = (short)(i + 1);
          partialTrueCount++;
        }
      }

      lambda_size[0] = trueCount;
      for (partialTrueCount = 0; partialTrueCount < trueCount; partialTrueCount
           ++) {
        lambda_data[partialTrueCount] = (lambda[tmp_data[partialTrueCount] - 1] >
          tol);
      }

      if (b_any(lambda_data, lambda_size)) {
        /*  Reset intermediate solution z */
        /*  Create wz, a Lagrange multiplier vector of variables in the zero set. */
        /*  wz must have the same size as w to preserve the correct indices, so */
        /*  set multipliers to -Inf for variables outside of the zero set. */
        for (i = 0; i < 3202; i++) {
          z[i] = 0.0;
          if (P[i]) {
            wz[i] = rtMinusInf;
          }

          if (Z[i]) {
            wz[i] = lambda[i];
          }
        }

        /*  Find variable with largest Lagrange multiplier */
        if (!rtIsNaN(wz[0])) {
          partialTrueCount = 1;
        } else {
          partialTrueCount = 0;
          i = 2;
          exitg3 = false;
          while ((!exitg3) && (i < 3203)) {
            if (!rtIsNaN(wz[i - 1])) {
              partialTrueCount = i;
              exitg3 = true;
            } else {
              i++;
            }
          }
        }

        if (partialTrueCount != 0) {
          alpha = wz[partialTrueCount - 1];
          i = partialTrueCount - 1;
          while (partialTrueCount + 1 < 3203) {
            if (alpha < wz[partialTrueCount]) {
              alpha = wz[partialTrueCount];
              i = partialTrueCount;
            }

            partialTrueCount++;
          }

          partialTrueCount = i;
        }

        /*  Move variable t from zero set to positive set */
        P[partialTrueCount] = true;
        Z[partialTrueCount] = false;

        /*  Compute intermediate solution using only variables in positive set */
        partialTrueCount = 0;
        i = 1;
        exitg3 = false;
        while ((!exitg3) && (i < 3203)) {
          if (P[i - 1]) {
            partialTrueCount++;
            b_ii_data[partialTrueCount - 1] = (short)i;
            if (partialTrueCount >= 3202) {
              exitg3 = true;
            } else {
              i++;
            }
          } else {
            i++;
          }
        }

        if (1 > partialTrueCount) {
          i = 0;
        } else {
          i = partialTrueCount;
        }

        ii_size[0] = i;
        for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount++) {
          ii_data[partialTrueCount] = b_ii_data[partialTrueCount];
        }

        sparse_parenReference(C.d, C.colidx, C.rowidx, ii_data, ii_size,
                              &expl_temp);
        partialTrueCount = t1_d->size[0];
        t1_d->size[0] = expl_temp.d->size[0];
        emxEnsureCapacity_real_T(t1_d, partialTrueCount);
        i = expl_temp.d->size[0];
        for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount++) {
          t1_d->data[partialTrueCount] = expl_temp.d->data[partialTrueCount];
        }

        partialTrueCount = t1_colidx->size[0];
        t1_colidx->size[0] = expl_temp.colidx->size[0];
        emxEnsureCapacity_int32_T(t1_colidx, partialTrueCount);
        i = expl_temp.colidx->size[0];
        for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount++) {
          t1_colidx->data[partialTrueCount] = expl_temp.colidx->
            data[partialTrueCount];
        }

        partialTrueCount = t1_rowidx->size[0];
        t1_rowidx->size[0] = expl_temp.rowidx->size[0];
        emxEnsureCapacity_int32_T(t1_rowidx, partialTrueCount);
        i = expl_temp.rowidx->size[0];
        for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount++) {
          t1_rowidx->data[partialTrueCount] = expl_temp.rowidx->
            data[partialTrueCount];
        }

        sparse_full(t1_d, t1_colidx, t1_rowidx, expl_temp.n, r0);
        mldivide(r0, d, ii_data, varargin_1_size);
        partialTrueCount = 0;
        for (i = 0; i < 3202; i++) {
          if (P[i]) {
            z[i] = ii_data[partialTrueCount];
            partialTrueCount++;
          }
        }

        /*  inner loop to remove elements from the positive set which no longer belong */
        do {
          exitg1 = 0;
          trueCount = 0;
          for (i = 0; i < 3202; i++) {
            if (P[i]) {
              trueCount++;
            }
          }

          partialTrueCount = 0;
          for (i = 0; i < 3202; i++) {
            if (P[i]) {
              b_tmp_data[partialTrueCount] = (short)(i + 1);
              partialTrueCount++;
            }
          }

          z_size[0] = trueCount;
          for (partialTrueCount = 0; partialTrueCount < trueCount;
               partialTrueCount++) {
            lambda_data[partialTrueCount] = (z[b_tmp_data[partialTrueCount] - 1]
              <= 0.0);
          }

          if (b_any(lambda_data, z_size)) {
            iter++;
            if (iter > 9606) {
              /* msg = getString(message('MATLAB:optimfun:lsqnonneg:IterationCountExceeded')); */
              /* if verbosity */
              /*     disp(msg) */
              /* end */
              *exitflag = 0.0;

              /* output.iterations = outeriter; */
              /* output.message = msg; */
              /* output.algorithm = 'active-set'; */
              for (i = 0; i < 2400; i++) {
                b_resid[i] = resid[i] * resid[i];
              }

              *resnorm = sum(b_resid);
              memcpy(&x[0], &z[0], 3202U * sizeof(double));
              exitg1 = 1;
            } else {
              /*  Find indices where intermediate solution z is approximately negative */
              /*  Choose new x subject to keeping new x nonnegative */
              trueCount = 0;
              for (i = 0; i < 3202; i++) {
                b_Z = (z[i] <= 0.0);
                if (b_Z && P[i]) {
                  trueCount++;
                }

                lambda_data[i] = b_Z;
              }

              partialTrueCount = 0;
              for (i = 0; i < 3202; i++) {
                if (lambda_data[i] && P[i]) {
                  c_tmp_data[partialTrueCount] = (short)(i + 1);
                  partialTrueCount++;
                }
              }

              x_size[0] = trueCount;
              for (partialTrueCount = 0; partialTrueCount < trueCount;
                   partialTrueCount++) {
                x_data[partialTrueCount] = x[c_tmp_data[partialTrueCount] - 1];
              }

              for (partialTrueCount = 0; partialTrueCount < trueCount;
                   partialTrueCount++) {
                b_x_data[partialTrueCount] = x[c_tmp_data[partialTrueCount] - 1]
                  - z[c_tmp_data[partialTrueCount] - 1];
              }

              rdivide(x_data, x_size, b_x_data, ii_data, varargin_1_size);
              if (varargin_1_size[0] <= 2) {
                if (varargin_1_size[0] == 1) {
                  alpha = ii_data[0];
                } else if ((ii_data[0] > ii_data[1]) || (rtIsNaN(ii_data[0]) &&
                            (!rtIsNaN(ii_data[1])))) {
                  alpha = ii_data[1];
                } else {
                  alpha = ii_data[0];
                }
              } else {
                if (!rtIsNaN(ii_data[0])) {
                  partialTrueCount = 1;
                } else {
                  partialTrueCount = 0;
                  i = 2;
                  exitg3 = false;
                  while ((!exitg3) && (i <= varargin_1_size[0])) {
                    if (!rtIsNaN(ii_data[i - 1])) {
                      partialTrueCount = i;
                      exitg3 = true;
                    } else {
                      i++;
                    }
                  }
                }

                if (partialTrueCount == 0) {
                  alpha = ii_data[0];
                } else {
                  alpha = ii_data[partialTrueCount - 1];
                  while (partialTrueCount + 1 <= varargin_1_size[0]) {
                    if (alpha > ii_data[partialTrueCount]) {
                      alpha = ii_data[partialTrueCount];
                    }

                    partialTrueCount++;
                  }
                }
              }

              for (partialTrueCount = 0; partialTrueCount < 3202;
                   partialTrueCount++) {
                x[partialTrueCount] += alpha * (z[partialTrueCount] -
                  x[partialTrueCount]);
              }

              /*  Reset Z and P given intermediate values of x */
              b_abs(x, z);
              for (i = 0; i < 3202; i++) {
                b_Z = (((z[i] < tol) && P[i]) || Z[i]);
                z[i] = 0.0;
                P[i] = !b_Z;
                Z[i] = b_Z;
              }

              /*  Reset z */
              partialTrueCount = 0;
              i = 1;
              exitg3 = false;
              while ((!exitg3) && (i < 3203)) {
                if (P[i - 1]) {
                  partialTrueCount++;
                  b_ii_data[partialTrueCount - 1] = (short)i;
                  if (partialTrueCount >= 3202) {
                    exitg3 = true;
                  } else {
                    i++;
                  }
                } else {
                  i++;
                }
              }

              if (1 > partialTrueCount) {
                i = 0;
              } else {
                i = partialTrueCount;
              }

              b_ii_size[0] = i;
              for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount
                   ++) {
                ii_data[partialTrueCount] = b_ii_data[partialTrueCount];
              }

              sparse_parenReference(C.d, C.colidx, C.rowidx, ii_data, b_ii_size,
                                    &expl_temp);
              partialTrueCount = t1_d->size[0];
              t1_d->size[0] = expl_temp.d->size[0];
              emxEnsureCapacity_real_T(t1_d, partialTrueCount);
              i = expl_temp.d->size[0];
              for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount
                   ++) {
                t1_d->data[partialTrueCount] = expl_temp.d->
                  data[partialTrueCount];
              }

              partialTrueCount = t1_colidx->size[0];
              t1_colidx->size[0] = expl_temp.colidx->size[0];
              emxEnsureCapacity_int32_T(t1_colidx, partialTrueCount);
              i = expl_temp.colidx->size[0];
              for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount
                   ++) {
                t1_colidx->data[partialTrueCount] = expl_temp.colidx->
                  data[partialTrueCount];
              }

              partialTrueCount = t1_rowidx->size[0];
              t1_rowidx->size[0] = expl_temp.rowidx->size[0];
              emxEnsureCapacity_int32_T(t1_rowidx, partialTrueCount);
              i = expl_temp.rowidx->size[0];
              for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount
                   ++) {
                t1_rowidx->data[partialTrueCount] = expl_temp.rowidx->
                  data[partialTrueCount];
              }

              sparse_full(t1_d, t1_colidx, t1_rowidx, expl_temp.n, r0);
              mldivide(r0, d, ii_data, varargin_1_size);
              partialTrueCount = 0;
              for (i = 0; i < 3202; i++) {
                if (P[i]) {
                  z[i] = ii_data[partialTrueCount];
                  partialTrueCount++;
                }
              }

              /*  Re-solve for z */
            }
          } else {
            memcpy(&x[0], &z[0], 3202U * sizeof(double));
            sparse_mtimes(C.d, C.colidx, C.rowidx, z, resid);
            for (partialTrueCount = 0; partialTrueCount < 2400; partialTrueCount
                 ++) {
              resid[partialTrueCount] = d[partialTrueCount] -
                resid[partialTrueCount];
            }

            sparse_ctranspose(C.d, C.colidx, C.rowidx, t0_d, t0_colidx,
                              t0_rowidx);
            b_sparse_mtimes(t0_d, t0_colidx, t0_rowidx, resid, lambda);
            guard1 = false;
            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = 1;
        }
      } else {
        guard1 = true;
        exitg2 = 1;
      }
    } else {
      guard1 = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  if (guard1) {
    *resnorm = 0.0;
    for (partialTrueCount = 0; partialTrueCount < 2400; partialTrueCount++) {
      *resnorm += resid[partialTrueCount] * resid[partialTrueCount];
    }
  }

  c_emxFreeStruct_coder_internal_(&expl_temp);
  emxFree_real_T(&r0);
  emxFree_int32_T(&t1_rowidx);
  emxFree_int32_T(&t1_colidx);
  emxFree_real_T(&t1_d);
  emxFree_int32_T(&t0_rowidx);
  emxFree_int32_T(&t0_colidx);
  emxFree_real_T(&t0_d);

  /* output.iterations = outeriter; */
  /* output.algorithm = 'active-set'; */
  /* msg = getString(message('MATLAB:optimfun:lsqnonneg:OptimizationTerminated')); */
  /* if verbosity > 1 */
  /*     disp(msg) */
  /* end */
  /* output.message = msg; */
  /* -------------------------------------------------------------------------- */
  /* { */
  /* function options = deprecateX0(options,numInputs,varargin) */
  /*  Code to check if user has passed in x0. If so, ignore it and warn of its */
  /*  deprecation. Also check whether the options have been passed in either */
  /*  the 3rd or 4th input. */
  /* if numInputs == 4 */
  /*     % 4 inputs given; the 3rd (variable name "options") will be interpreted */
  /*     % as x0, and the 4th as options */
  /*     if ~isempty(options) */
  /*         % x0 is non-empty */
  /*         warning('MATLAB:lsqnonneg:ignoringX0',... */
  /*             getString(message('MATLAB:optimfun:lsqnonneg:ignoringX0'))); */
  /*     end */
  /*     % Take the 4th argument as the options */
  /*     options = varargin{1}; */
  /* elseif numInputs == 3 */
  /*     % Check if a non-empty or non-struct has been passed in for options */
  /*     % If so, assume that it's an attempt to pass x0 */
  /*     if ~isstruct(options) && ~isempty(options) */
  /*         warning('MATLAB:lsqnonneg:ignoringX0',... */
  /*             getString(message('MATLAB:optimfun:lsqnonneg:ignoringX0'))); */
  /*         % No options passed, set to empty */
  /*         options = []; */
  /*     end */
  /* end */
  /* } */
}

/* End of code generation (lsqnonneg1.cpp) */
