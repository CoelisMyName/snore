//
// File: m_lpc.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "m_lpc.h"
#include "SnoringRecognition_data.h"
#include "abs.h"
#include "fft.h"
#include "ifft.h"
#include "levinson.h"
#include "mpower.h"
#include "nextpow2.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [a, e] = m_lpc(x, N)
//
// Arguments    : const coder::array<double, 1U> &x
//                coder::array<double, 2U> &a
// Return Type  : void
//
void m_lpc(const coder::array<double, 1U> &x, coder::array<double, 2U> &a) {
    coder::array<creal_T, 2U> b_a;
    coder::array<creal_T, 1U> X;
    coder::array<double, 2U> e;
    coder::array<double, 1U> r;
    coder::array<double, 1U> r1;
    int i;
    int loop_ub;
    int x_re;
    // 'm_lpc:2' [m, n] = size(x);
    // 'm_lpc:4' if (n > 1) && (m == 1)
    // 'm_lpc:9' X = fft(x, 2^nextpow2(2 * size(x, 1) - 1));
    coder::fft(
            x,
            coder::mpower(
                    2.0, coder::nextpow2(2.0 * static_cast<double>(x.size(0)) - 1.0)),
            X);
    // 'm_lpc:10' R = ifft(abs(X).^2);
    coder::b_abs(X, r);
    coder::power(r, r1);
    coder::ifft(r1, X);
    // 'm_lpc:11' R = R ./ m;
    x_re = x.size(0);
    loop_ub = X.size(0);
    for (i = 0; i < loop_ub; i++) {
        double ai;
        double im;
        double re;
        im = X[i].re;
        ai = X[i].im;
        if (ai == 0.0) {
            re = im / static_cast<double>(x_re);
            im = 0.0;
        } else if (im == 0.0) {
            re = 0.0;
            im = ai / static_cast<double>(x_re);
        } else {
            re = im / static_cast<double>(x_re);
            im = ai / static_cast<double>(x_re);
        }
        X[i].re = re;
        X[i].im = im;
    }
    //  Biased autocorrelation estimate
    // 'm_lpc:13' [a, e] = levinson(R, N);
    coder::levinson(X, b_a, e);
    // 'm_lpc:15' a = real(a);
    a.set_size(b_a.size(0), b_a.size(1));
    loop_ub = b_a.size(0) * b_a.size(1);
    for (i = 0; i < loop_ub; i++) {
        a[i] = b_a[i].re;
    }
}

//
// File trailer for m_lpc.cpp
//
// [EOF]
//
