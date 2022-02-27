//
// File: m_lpc.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
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
//                double a_data[]
//                int a_size[2]
// Return Type  : void
//
void b_m_lpc(const coder::array<double, 1U> &x, double a_data[], int a_size[2]) {
    coder::array<creal_T, 1U> R;
    coder::array<creal_T, 1U> X;
    coder::array<double, 1U> r;
    coder::array<double, 1U> r1;
    creal_T b_a_data[11];
    double im;
    int b_a_size[2];
    int e_size[2];
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
    coder::ifft(r1, R);
    // 'm_lpc:11' R = R ./ m;
    x_re = x.size(0);
    loop_ub = R.size(0);
    for (i = 0; i < loop_ub; i++) {
        double ai;
        double re;
        im = R[i].re;
        ai = R[i].im;
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
        R[i].re = re;
        R[i].im = im;
    }
    //  Biased autocorrelation estimate
    // 'm_lpc:13' [a, e] = levinson(R, N);
    coder::b_levinson(R, b_a_data, b_a_size, (double *) &im, e_size);
    // 'm_lpc:15' a = real(a);
    a_size[0] = 1;
    a_size[1] = b_a_size[1];
    loop_ub = b_a_size[1];
    for (i = 0; i < loop_ub; i++) {
        a_data[i] = b_a_data[i].re;
    }
}

//
// function [a, e] = m_lpc(x, N)
//
// Arguments    : const coder::array<double, 1U> &x
//                double a_data[]
//                int a_size[2]
// Return Type  : void
//
void m_lpc(const coder::array<double, 1U> &x, double a_data[], int a_size[2]) {
    coder::array<creal_T, 1U> R;
    coder::array<creal_T, 1U> X;
    coder::array<double, 1U> r;
    coder::array<double, 1U> r1;
    creal_T b_a_data[13];
    double im;
    int b_a_size[2];
    int e_size[2];
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
    coder::ifft(r1, R);
    // 'm_lpc:11' R = R ./ m;
    x_re = x.size(0);
    loop_ub = R.size(0);
    for (i = 0; i < loop_ub; i++) {
        double ai;
        double re;
        im = R[i].re;
        ai = R[i].im;
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
        R[i].re = re;
        R[i].im = im;
    }
    //  Biased autocorrelation estimate
    // 'm_lpc:13' [a, e] = levinson(R, N);
    coder::levinson(R, b_a_data, b_a_size, (double *) &im, e_size);
    // 'm_lpc:15' a = real(a);
    a_size[0] = 1;
    a_size[1] = b_a_size[1];
    loop_ub = b_a_size[1];
    for (i = 0; i < loop_ub; i++) {
        a_data[i] = b_a_data[i].re;
    }
}

//
// File trailer for m_lpc.cpp
//
// [EOF]
//
