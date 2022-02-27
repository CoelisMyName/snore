//
// File: lsum.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "lsum.h"
#include "exp.h"
#include "log.h"
#include "permute.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sum.h"
#include "coder_array.h"

// Function Definitions
//
// function lz = lsum(X, DIM)
//
// lz=lsum(X,DIM);
//
//  lz=log(x(1)+x(2)+....x(n))  X(i)= log(x(i)) ;
//
//  lsum(X)     sums along first dimension
//  lsum(X,DIM) sums along dimension DIM
//
// Arguments    : const coder::array<double, 2U> &X
//                coder::array<double, 1U> &lz
// Return Type  : void
//
void lsum(const coder::array<double, 2U> &X, coder::array<double, 1U> &lz) {
    coder::array<double, 2U> b_X;
    coder::array<double, 2U> c_X;
    coder::array<double, 2U> r;
    int i;
    int loop_ub;
    // 'lsum:9' if nargin == 1
    // 'lsum:13' s = size(X);
    // 'lsum:15' if DIM == 1
    // 'lsum:25' else
    //  we put DIM to first dimension and do the same as before
    // 'lsum:27' X = permute(X, [DIM, 1:DIM - 1, DIM + 1:length(s)]);
    //  ************************************************************
    // 'lsum:30' X = sort(X, 1);
    coder::b_permute(X, b_X);
    coder::internal::sort(b_X);
    // 'lsum:31' lz = X(end, :, :, :, :) + ...
    // 'lsum:32'             log(1 + sum(exp(X(1:end - 1, :, :, :, :) - ...
    // 'lsum:33'             repmat(X(end, :, :, :, :), [size(X, 1) - 1, 1, 1,
    // 1, 1])), 1));
    //  *************************************************************
    // 'lsum:36' lz = permute(lz, [2:DIM, 1, DIM + 1:length(s)]);
    loop_ub = b_X.size(1);
    c_X.set_size(1, b_X.size(1));
    for (i = 0; i < loop_ub; i++) {
        c_X[i] = b_X[32 * i + 31];
    }
    coder::b_repmat(c_X, r);
    loop_ub = b_X.size(1);
    r.set_size(31, b_X.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (int i1 = 0; i1 < 31; i1++) {
            r[i1 + 31 * i] = b_X[i1 + 32 * i] - r[i1 + 31 * i];
        }
    }
    coder::b_exp(r);
    coder::sum(r, c_X);
    c_X.set_size(1, c_X.size(1));
    loop_ub = c_X.size(1) - 1;
    for (i = 0; i <= loop_ub; i++) {
        c_X[i] = c_X[i] + 1.0;
    }
    coder::b_log(c_X);
    loop_ub = b_X.size(1);
    c_X.set_size(1, b_X.size(1));
    for (i = 0; i < loop_ub; i++) {
        c_X[i] = c_X[i] + b_X[32 * i + 31];
    }
    coder::permute(c_X, lz);
    //  we bring back dimesions
}

//
// File trailer for lsum.cpp
//
// [EOF]
//
