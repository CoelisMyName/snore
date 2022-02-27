//
// File: formantfeature.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "formantfeature.h"
#include "enframe.h"
#include "fix.h"
#include "hanning.h"
#include "isnan.h"
#include "nanmean.h"
#include "rt_nonfinite.h"
#include "seekfmts1.h"
#include "coder_array.h"

// Function Definitions
//
// function [fmt1_mean, fmt2_mean, fmt3_mean] = formantfeature(x, Fs)
//
// 提取共振峰特征
//
// Arguments    : const coder::array<double, 1U> &x
//                double Fs
//                double *fmt1_mean
//                double *fmt2_mean
//                double *fmt3_mean
// Return Type  : void
//
void formantfeature(const coder::array<double, 1U> &x, double Fs,
                    double *fmt1_mean, double *fmt2_mean, double *fmt3_mean) {
    coder::array<double, 2U> b_fmt;
    coder::array<double, 2U> fmt;
    coder::array<double, 2U> r1;
    coder::array<double, 1U> r;
    double b_tmp;
    double wlen;
    int i;
    int loop_ub;
    // 'formantfeature:3' wlen = fix(0.02 * Fs);
    wlen = 0.02 * Fs;
    coder::b_fix(&wlen);
    // 'formantfeature:4' wind = hanning(wlen);
    // 'formantfeature:5' inc = fix(0.5 * wlen);
    // 'formantfeature:6' y = enframe(x, wind, inc)';
    b_tmp = 0.5 * wlen;
    coder::b_fix(&b_tmp);
    coder::hanning(wlen, r);
    enframe(x, r, b_tmp, r1);
    // 'formantfeature:7' fn = size(y, 2);
    // 'formantfeature:8' fmt = seekfmts1(x, fn, Fs, 10);
    seekfmts1(x, static_cast<double>(r1.size(0)), Fs, fmt);
    // 'formantfeature:9' fmt1 = (fmt(1, :)) * (Fs / 2);
    b_tmp = Fs / 2.0;
    // 'formantfeature:10' fmt2 = (fmt(2, :)) * (Fs / 2);
    // 'formantfeature:11' fmt3 = (fmt(3, :)) * (Fs / 2);
    // 'formantfeature:12' fmt1_mean = nanmean(fmt1);
    loop_ub = fmt.size(1);
    b_fmt.set_size(1, fmt.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_fmt[i] = fmt[3 * i] * b_tmp;
    }
    *fmt1_mean = coder::nanmean(b_fmt);
    // 'formantfeature:13' fmt2_mean = nanmean(fmt2);
    loop_ub = fmt.size(1);
    b_fmt.set_size(1, fmt.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_fmt[i] = fmt[3 * i + 1] * b_tmp;
    }
    *fmt2_mean = coder::nanmean(b_fmt);
    // 'formantfeature:14' fmt3_mean = nanmean(fmt3);
    loop_ub = fmt.size(1);
    b_fmt.set_size(1, fmt.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_fmt[i] = fmt[3 * i + 2] * b_tmp;
    }
    *fmt3_mean = coder::nanmean(b_fmt);
    // 'formantfeature:16' if isnan(fmt1_mean)
    if (coder::b_isnan(*fmt1_mean)) {
        // 'formantfeature:17' fmt1_mean = 0;
        *fmt1_mean = 0.0;
    }
    // 'formantfeature:20' if isnan(fmt2_mean)
    if (coder::b_isnan(*fmt2_mean)) {
        // 'formantfeature:21' fmt2_mean = 0;
        *fmt2_mean = 0.0;
    }
    // 'formantfeature:24' if isnan(fmt3_mean)
    if (coder::b_isnan(*fmt3_mean)) {
        // 'formantfeature:25' fmt3_mean = 0;
        *fmt3_mean = 0.0;
    }
}

//
// File trailer for formantfeature.cpp
//
// [EOF]
//
