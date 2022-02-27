//
// File: PR800.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "PR800.h"
#include "abs.h"
#include "enframe.h"
#include "fft.h"
#include "fix.h"
#include "hamming.h"
#include "log10.h"
#include "mean.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "var.h"
#include "coder_array.h"

// Function Definitions
//
// function [PR800_mean, PR800_max, PR800_min, PR800_var] = PR800(x, Fs)
//
// UNTITLED4 此处显示有关此函数的摘要
//    此处显示详细说明
//
// Arguments    : const coder::array<double, 1U> &x
//                double Fs
//                double *PR800_mean
//                double *PR800_max
//                double *PR800_min
//                double *PR800_var
// Return Type  : void
//
void PR800(const coder::array<double, 1U> &x, double Fs, double *PR800_mean,
           double *PR800_max, double *PR800_min, double *PR800_var) {
    coder::array<creal_T, 1U> Z;
    coder::array<double, 2U> b_PR800;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> r;
    coder::array<double, 1U> mag;
    coder::array<double, 1U> y;
    double d;
    double f1;
    double f2;
    double wlen;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int i;
    int i1;
    int i2;
    int i3;
    int i4;
    int i5;
    int loop_ub;
    // 'PR800:4' wlen = fix(0.02 * Fs);
    wlen = 0.02 * Fs;
    coder::b_fix(&wlen);
    // 'PR800:5' inc = fix(0.5 * wlen);
    // 'PR800:6' wind = hamming(wlen);
    // 'PR800:7' y = enframe(x, wind, inc)';
    d = 0.5 * wlen;
    coder::b_fix(&d);
    coder::hamming(wlen, y);
    enframe(x, y, d, r);
    b_y.set_size(r.size(1), r.size(0));
    loop_ub = r.size(0);
    for (i = 0; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = r.size(1);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            b_y[i1 + b_y.size(0) * i] = r[i + r.size(0) * i1];
        }
    }
    double ds;
    // 'PR800:8' fn = size(y, 2);
    // 总帧数
    // 'PR800:9' PR800 = zeros(1, fn);
    b_PR800.set_size(1, b_y.size(1));
    // 'PR800:10' ds = Fs / wlen;
    ds = Fs / wlen;
    // 'PR800:11' f1 = 800 / ds + 1;
    f1 = 800.0 / ds + 1.0;
    // 'PR800:12' f2 = 8000 / ds + 1;
    f2 = 8000.0 / ds + 1.0;
    // 'PR800:14' for i = 1:fn
    i = b_y.size(1);
    if (0 <= b_y.size(1) - 1) {
        i2 = b_y.size(0);
        c_loop_ub = b_y.size(0);
        if (1.0 > f1) {
            d_loop_ub = 0;
        } else {
            d_loop_ub = static_cast<int>(f1);
        }
        if (f1 > f2) {
            i3 = 0;
            i4 = 0;
            i5 = 1;
        } else {
            i3 = static_cast<int>(f1) - 1;
            i4 = static_cast<int>(f2);
            i5 = static_cast<int>(f1);
        }
        e_loop_ub = i4 - i3;
    }
    for (int b_i = 0; b_i < i; b_i++) {
        // 'PR800:15' YY = y(:, i);
        // 取一帧数据
        // 'PR800:16' n = 0:length(YY) - 1;
        // 'PR800:17' Z = fft(YY);
        y.set_size(i2);
        for (i1 = 0; i1 < c_loop_ub; i1++) {
            y[i1] = b_y[i1 + b_y.size(0) * b_i];
        }
        coder::fft(y, Z);
        // 'PR800:18' f = n * Fs / length(YY);
        // 'PR800:19' mag = abs(Z);
        coder::b_abs(Z, mag);
        // 'PR800:20' PR800(i) = log10(sum(mag(1:f1) .* mag(1:f1)) /
        // sum(mag(f1:f2) .* mag(f1:f2)));
        y.set_size(d_loop_ub);
        for (i1 = 0; i1 < d_loop_ub; i1++) {
            y[i1] = mag[i1] * mag[i1];
        }
        for (i1 = 0; i1 < e_loop_ub; i1++) {
            mag[i1] = mag[i3 + i1] * mag[(i5 + i1) - 1];
        }
        mag.set_size(i4 - i3);
        b_PR800[b_i] = coder::sum(y) / coder::sum(mag);
        coder::b_log10(&b_PR800[b_i]);
    }
    //  for i = 1:fn
    //      YY = y(:,i);  %取一帧数据
    //      n = 0:length(YY)-1;
    //      Z=fft(YY);
    //      f=n*Fs/length(YY);
    //      mag=abs(Z);
    //      PR800(i)=log10(sum(mag(1:17).*mag(1:17))/sum(mag(17:161).*mag(17:161)));
    //  end
    // 'PR800:31' PR800_mean = mean(PR800);
    *PR800_mean = coder::mean(b_PR800);
    // 'PR800:32' PR800_max = max(PR800);
    *PR800_max = coder::internal::maximum(b_PR800);
    // 'PR800:33' PR800_min = min(PR800);
    *PR800_min = coder::internal::minimum(b_PR800);
    // 'PR800:34' PR800_var = var(PR800);
    *PR800_var = coder::var(b_PR800);
}

//
// File trailer for PR800.cpp
//
// [EOF]
//
