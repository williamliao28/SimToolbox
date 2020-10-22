/*
 * sparse.cpp
 *
 * Code generation for function 'sparse'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "lsqnonneg1.h"
#include "sparse.h"
#include "lsqnonneg1_emxutil.h"

/* Function Declarations */
static void sparse_sparse(int nzmaxval, emxArray_real_T *this_d,
  emxArray_int32_T *this_colidx, emxArray_int32_T *this_rowidx);

/* Function Definitions */
static void sparse_sparse(int nzmaxval, emxArray_real_T *this_d,
  emxArray_int32_T *this_colidx, emxArray_int32_T *this_rowidx)
{
  int numalloc;
  int i0;
  if (nzmaxval >= 1) {
    numalloc = nzmaxval;
  } else {
    numalloc = 1;
  }

  i0 = this_d->size[0];
  this_d->size[0] = numalloc;
  emxEnsureCapacity_real_T(this_d, i0);
  for (i0 = 0; i0 < numalloc; i0++) {
    this_d->data[i0] = 0.0;
  }

  i0 = this_colidx->size[0];
  this_colidx->size[0] = 2401;
  emxEnsureCapacity_int32_T(this_colidx, i0);
  this_colidx->data[0] = 1;
  i0 = this_rowidx->size[0];
  this_rowidx->size[0] = numalloc;
  emxEnsureCapacity_int32_T(this_rowidx, i0);
  for (i0 = 0; i0 < numalloc; i0++) {
    this_rowidx->data[i0] = 0;
  }

  for (numalloc = 0; numalloc < 2400; numalloc++) {
    this_colidx->data[numalloc + 1] = 1;
  }

  for (numalloc = 1; numalloc < 2401; numalloc++) {
    this_colidx->data[numalloc - 1] = 1;
  }

  this_colidx->data[2400] = 1;
}

void sparse_ctranspose(const emxArray_real_T *this_d, const emxArray_int32_T
  *this_colidx, const emxArray_int32_T *this_rowidx, emxArray_real_T *y_d,
  emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx)
{
  int loop_ub;
  int idx;
  int counts[2400];
  int outridx;
  sparse_sparse(this_colidx->data[this_colidx->size[0] - 1] - 1, y_d, y_colidx,
                y_rowidx);
  loop_ub = y_colidx->size[0];
  idx = y_colidx->size[0];
  y_colidx->size[0] = loop_ub;
  emxEnsureCapacity_int32_T(y_colidx, idx);
  for (idx = 0; idx < loop_ub; idx++) {
    y_colidx->data[idx] = 0;
  }

  for (loop_ub = 0; loop_ub < this_colidx->data[this_colidx->size[0] - 1] - 1;
       loop_ub++) {
    y_colidx->data[this_rowidx->data[loop_ub]]++;
  }

  y_colidx->data[0] = 1;
  for (loop_ub = 0; loop_ub < 2400; loop_ub++) {
    y_colidx->data[loop_ub + 1] += y_colidx->data[loop_ub];
  }

  memset(&counts[0], 0, 2400U * sizeof(int));
  for (loop_ub = 0; loop_ub < 3202; loop_ub++) {
    for (idx = this_colidx->data[loop_ub] - 1; idx + 1 < this_colidx->
         data[loop_ub + 1]; idx++) {
      outridx = (counts[this_rowidx->data[idx] - 1] + y_colidx->data
                 [this_rowidx->data[idx] - 1]) - 1;
      y_d->data[outridx] = this_d->data[idx];
      y_rowidx->data[outridx] = loop_ub + 1;
      counts[this_rowidx->data[idx] - 1]++;
    }
  }
}

void sparse_full(const emxArray_real_T *this_d, const emxArray_int32_T
                 *this_colidx, const emxArray_int32_T *this_rowidx, int this_n,
                 emxArray_real_T *y)
{
  int c;
  int loop_ub;
  c = y->size[0] * y->size[1];
  y->size[0] = 2400;
  y->size[1] = this_n;
  emxEnsureCapacity_real_T1(y, c);
  loop_ub = 2400 * this_n;
  for (c = 0; c < loop_ub; c++) {
    y->data[c] = 0.0;
  }

  for (c = 1; c <= this_n; c++) {
    for (loop_ub = this_colidx->data[c - 1]; loop_ub < this_colidx->data[c];
         loop_ub++) {
      y->data[(this_rowidx->data[loop_ub - 1] + y->size[0] * (c - 1)) - 1] =
        this_d->data[loop_ub - 1];
    }
  }
}

void sparse_parenReference(const emxArray_real_T *this_d, const emxArray_int32_T
  *this_colidx, const emxArray_int32_T *this_rowidx, const double
  varargin_2_data[], const int varargin_2_size[1], coder_internal_sparse_2 *s)
{
  int sn;
  int nd;
  int cidx;
  int colstart;
  int colNnz;
  int k;
  sn = varargin_2_size[0];
  nd = 0;
  for (cidx = 0; cidx < sn; cidx++) {
    nd = (nd + this_colidx->data[(int)varargin_2_data[cidx]]) -
      this_colidx->data[(int)varargin_2_data[cidx] - 1];
  }

  if (nd == 0) {
    s->n = varargin_2_size[0];
    colstart = s->d->size[0];
    s->d->size[0] = 1;
    emxEnsureCapacity_real_T(s->d, colstart);
    s->d->data[0] = 0.0;
    colstart = s->colidx->size[0];
    s->colidx->size[0] = varargin_2_size[0] + 1;
    emxEnsureCapacity_int32_T(s->colidx, colstart);
    nd = varargin_2_size[0];
    for (colstart = 0; colstart <= nd; colstart++) {
      s->colidx->data[colstart] = 1;
    }

    colstart = s->rowidx->size[0];
    s->rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(s->rowidx, colstart);
    s->rowidx->data[0] = 1;
  } else {
    colstart = s->d->size[0];
    s->d->size[0] = nd;
    emxEnsureCapacity_real_T(s->d, colstart);
    colstart = s->rowidx->size[0];
    s->rowidx->size[0] = nd;
    emxEnsureCapacity_int32_T(s->rowidx, colstart);
    colstart = s->colidx->size[0];
    s->colidx->size[0] = varargin_2_size[0] + 1;
    emxEnsureCapacity_int32_T(s->colidx, colstart);
    s->colidx->data[0] = 1;
    s->n = varargin_2_size[0];
    nd = 0;
    for (cidx = 0; cidx < sn; cidx++) {
      colstart = this_colidx->data[(int)varargin_2_data[cidx] - 1] - 2;
      colNnz = this_colidx->data[(int)varargin_2_data[cidx]] - this_colidx->
        data[(int)varargin_2_data[cidx] - 1];
      for (k = 1; k <= colNnz; k++) {
        s->d->data[nd] = this_d->data[colstart + k];
        s->rowidx->data[nd] = this_rowidx->data[colstart + k];
        nd++;
      }

      s->colidx->data[cidx + 1] = s->colidx->data[cidx] + colNnz;
    }
  }
}

/* End of code generation (sparse.cpp) */
