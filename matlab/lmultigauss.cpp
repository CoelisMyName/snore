//
// File: lmultigauss.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "lmultigauss.h"
#include "dot.h"
#include "log.h"
#include "lsum.h"
#include "permute.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// function [YM, Y] = lmultigauss(x, mus, sigm, c)
//
// [lYM,lY]=lmultigauss(X,mu,sigm,c)
//
//  computes multigaussian log-likelihood
//
//  X   : (LxT) data (columnwise vectors)
//  sigm: (LxM) variances vector  (diagonal of the covariance matrix)
//  mu  : (LxM) means
//  c   : (Mx1) the weights
//
// Arguments    : const coder::array<double, 2U> &x
//                const double mus[4160]
//                const double sigm[4160]
//                const double c[32]
//                coder::array<double, 2U> &YM
//                coder::array<double, 1U> &Y
// Return Type  : void
//
void lmultigauss(const coder::array<double, 2U> &x, const double mus[4160],
                 const double sigm[4160], const double c[32],
                 coder::array<double, 2U> &YM, coder::array<double, 1U> &Y) {
    coder::array<double, 3U> b_x_tmp;
    coder::array<double, 3U> r;
    coder::array<double, 3U> r1;
    coder::array<double, 3U> r2;
    coder::array<double, 3U> x_tmp;
    coder::array<double, 2U> b_x;
    coder::array<double, 2U> r3;
    coder::array<double, 2U> r4;
    double b_dv2[4160];
    double b_dv1[32];
    double b_dv3[32];
    double b_dv[3];
    double c_x[2];
    int i;
    int loop_ub;
    // 'lmultigauss:11' [L, T] = size(x);
    // 'lmultigauss:12' M = size(c, 1);
    //  repeating, changing dimensions:
    // 'lmultigauss:15' X = permute(repmat(x', [1, 1, M]), [1, 3, 2]);
    //  (T,L) -> (T,M,L) one per mixture
    // 'lmultigauss:17' Sigm = permute(repmat(sigm, [1, 1, T]), [3, 2, 1]);
    //  (L,M) -> (T,M,L)
    // 'lmultigauss:19' Mu = permute(repmat(mus, [1, 1, T]), [3, 2, 1]);
    //  (L,M) -> (T,M,L)
    // Y=squeeze(exp( 0.5.*dot(X-Mu,(X-Mu)./Sigm))) % L dissapears: (L,T,M) ->
    // (T,M) 'lmultigauss:22' lY = -0.5 .* dot(X - Mu, (X - Mu) ./ Sigm, 3);
    b_x.set_size(x.size(1), 130);
    loop_ub = x.size(1);
    for (i = 0; i < 130; i++) {
        for (int i1 = 0; i1 < loop_ub; i1++) {
            b_x[i1 + b_x.size(0) * i] = x[i + 130 * i1];
        }
    }
    coder::repmat(b_x, r);
    coder::permute(r, x_tmp);
    b_dv[0] = 1.0;
    b_dv[1] = 1.0;
    b_dv[2] = x.size(1);
    coder::repmat(mus, b_dv, r1);
    coder::b_permute(r1, r2);
    loop_ub = x_tmp.size(0) * 32 * 130;
    x_tmp.set_size(x_tmp.size(0), 32, 130);
    for (i = 0; i < loop_ub; i++) {
        x_tmp[i] = x_tmp[i] - r2[i];
    }
    //  c,const -> (T,M) and then multiply by old Y
    // 'lmultigauss:24' lcoi = log(2 .* pi) .* (L ./ 2) + 0.5 .* sum(log(sigm),
    // 1);
    //  c,const -> (T,M)
    // 'lmultigauss:25' lcoef = repmat(log(c') - lcoi, [T, 1]);
    // 'lmultigauss:27' YM = lcoef + lY;
    memcpy(&b_dv1[0], &c[0], 32U * sizeof(double));
    coder::e_log(b_dv1);
    memcpy(&b_dv2[0], &sigm[0], 4160U * sizeof(double));
    coder::d_log(b_dv2);
    coder::sum(b_dv2, b_dv3);
    for (i = 0; i < 32; i++) {
        b_dv1[i] -= 0.5 * b_dv3[i] + 119.46200931660745;
    }
    c_x[0] = x.size(1);
    c_x[1] = 1.0;
    coder::repmat(b_dv1, c_x, r3);
    b_dv[0] = 1.0;
    b_dv[1] = 1.0;
    b_dv[2] = x.size(1);
    coder::repmat(sigm, b_dv, r1);
    coder::b_permute(r1, r2);
    b_x_tmp.set_size(x_tmp.size(0), 32, 130);
    loop_ub = x_tmp.size(0) * 32 * 130;
    for (i = 0; i < loop_ub; i++) {
        b_x_tmp[i] = x_tmp[i] / r2[i];
    }
    coder::dot(x_tmp, b_x_tmp, r4);
    YM.set_size(r3.size(0), 32);
    loop_ub = r3.size(0) * 32;
    for (i = 0; i < loop_ub; i++) {
        YM[i] = r3[i] + -0.5 * r4[i];
    }
    //  ( T,M ) one mixture per column
    // 'lmultigauss:28' Y = lsum(YM, 2);
    lsum(YM, Y);
    //  add mixtures
}

//
// File trailer for lmultigauss.cpp
//
// [EOF]
//
