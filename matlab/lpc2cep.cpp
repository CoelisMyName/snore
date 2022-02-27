//
// File: lpc2cep.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "lpc2cep.h"
#include "log.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function features = lpc2cep(a, nout)
//
// features = lpc2cep(lpcas,nout)
//     Convert the LPC 'a' coefficients in each column of lpcas
//     into frames of cepstra.
//     nout is number of cepstra to produce, defaults to size(lpcas,1)
//  2003-04-11 dpwe@ee.columbia.edu
//
// Arguments    : coder::array<double, 2U> &a
//                coder::array<double, 2U> &features
// Return Type  : void
//
void lpc2cep(coder::array<double, 2U> &a, coder::array<double, 2U> &features) {
    coder::array<double, 2U> b_a;
    coder::array<double, 2U> r;
    coder::array<double, 2U> sum;
    int i;
    int loop_ub;
    int ncol;
    // 'lpc2cep:8' [nin, ncol] = size(a);
    ncol = a.size(1);
    // 'lpc2cep:10' order = nin - 1;
    // 'lpc2cep:12' if nargin < 2
    // 'lpc2cep:16' c = zeros(nout, ncol);
    features.set_size(13, a.size(1));
    loop_ub = 13 * a.size(1);
    for (i = 0; i < loop_ub; i++) {
        features[i] = 0.0;
    }
    //  Code copied from HSigP.c: LPC2Cepstrum
    //  First cep is log(Error) from Durbin
    // 'lpc2cep:21' c(1, :) = -log(a(1, :));
    loop_ub = a.size(1);
    b_a.set_size(1, a.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_a[i] = a[13 * i];
    }
    coder::b_log(b_a);
    loop_ub = b_a.size(1);
    for (i = 0; i < loop_ub; i++) {
        features[13 * i] = -b_a[i];
    }
    //  Renormalize lpc A coeffs
    // 'lpc2cep:24' a = a ./ repmat(a(1, :), nin, 1);
    loop_ub = a.size(1);
    b_a.set_size(1, a.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_a[i] = a[13 * i];
    }
    coder::repmat(b_a, r);
    loop_ub = 13 * a.size(1);
    a.set_size(13, a.size(1));
    for (i = 0; i < loop_ub; i++) {
        a[i] = a[i] / r[i];
    }
    // 'lpc2cep:26' for n = 2:nout
    loop_ub = a.size(1);
    for (int n = 0; n < 12; n++) {
        // 'lpc2cep:27' sum = zeros(1, ncol);
        sum.set_size(1, ncol);
        for (i = 0; i < ncol; i++) {
            sum[i] = 0.0;
        }
        // 'lpc2cep:28' for m = 2:n
        for (int m = 0; m <= n; m++) {
            int a_tmp;
            int b_loop_ub;
            // 'lpc2cep:29' sum = sum + (n - m) * a(m, :) .* c(n - m + 1, :);
            a_tmp = n - m;
            b_loop_ub = features.size(1);
            b_a.set_size(1, features.size(1));
            for (i = 0; i < b_loop_ub; i++) {
                b_a[i] = features[a_tmp + 13 * i];
            }
            sum.set_size(1, sum.size(1));
            b_loop_ub = sum.size(1);
            for (i = 0; i < b_loop_ub; i++) {
                sum[i] = sum[i] + static_cast<double>(a_tmp) *
                                  a[(m + 13 * i) + 1] * b_a[i];
            }
        }
        // 'lpc2cep:31' c(n, :) =- (a(n, :) + sum / (n - 1));
        for (i = 0; i < loop_ub; i++) {
            features[(n + 13 * i) + 1] =
                    -(a[(n + 13 * i) + 1] +
                      sum[i] / ((static_cast<double>(n) + 2.0) - 1.0));
        }
    }
    // 'lpc2cep:34' features = c;
}

//
// File trailer for lpc2cep.cpp
//
// [EOF]
//
