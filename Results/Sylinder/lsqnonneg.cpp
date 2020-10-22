/*
LSQNONNEG Linear least squares with nonnegativity constraints.
*/

#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<mkl.h>

void lsqnonneg(double *X, int flops, double *C, int C_nrow, int C_ncol, double *d, int d_len
, double tol){
    double resid;

    //Set tolerance
    if (tol > 1.0)
    {
        tol = 1e-6;
    }
    //Initial res

}