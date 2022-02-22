//
// File: CrestFactor.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "CrestFactor.h"
#include "abs.h"
#include "fix.h"
#include "floor.h"
#include "hamming.h"
#include "mean.h"
#include "minOrMax.h"
#include "rms.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "v_enframe.h"
#include "coder_array.h"

// Function Definitions
//
// function [CF_mean] = CrestFactor(x, fs)
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs
// Return Type  : double
//
double CrestFactor(const coder::array<double, 1U> &x, double fs) {
    coder::array<double, 2U> Crest_Factor;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> r;
    coder::array<double, 1U> wnd;
    coder::array<double, 1U> y;
    double d;
    double wlen;
    int b_loop_ub;
    int i;
    int i1;
    int loop_ub;
    // 'CrestFactor:3' wlen = fix(0.02 * fs);
    wlen = 0.02 * fs;
    coder::b_fix(&wlen);
    // 'CrestFactor:4' wnd = hamming(wlen);
    // 'CrestFactor:5' inc = fix(0.5 * wlen);
    // 'CrestFactor:6' y = v_enframe(x, wnd, inc)';
    d = 0.5 * wlen;
    coder::b_fix(&d);
    coder::hamming(wlen, y);
    v_enframe(x, y, d, r);
    b_y.set_size(r.size(1), r.size(0));
    loop_ub = r.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_loop_ub = r.size(1);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            b_y[i1 + b_y.size(0) * i] = r[i + r.size(0) * i1];
        }
    }
    // 'CrestFactor:7' fn = size(y, 2);
    // 'CrestFactor:8' Crest_Factor = zeros(1, fn);
    Crest_Factor.set_size(1, b_y.size(1));
    // 'CrestFactor:10' for i = 1:fn
    i = b_y.size(1);
    for (int b_i = 0; b_i < i; b_i++) {
        int i2;
        // 'CrestFactor:11' YY = y(:, i);
        // 取一帧数据
        // 'CrestFactor:12' V90th = sort(abs(YY));
        loop_ub = b_y.size(0);
        y.set_size(b_y.size(0));
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1] = b_y[i1 + b_y.size(0) * b_i];
        }
        coder::b_abs(y, wnd);
        coder::internal::sort(wnd);
        // 从小到大排列
        // 'CrestFactor:13' V90 = max(V90th(1:end - floor(length(V90th) * 0.1)));
        d = static_cast<double>(wnd.size(0)) * 0.1;
        coder::b_floor(&d);
        d = static_cast<double>(wnd.size(0)) - d;
        if (1.0 > d) {
            loop_ub = 0;
        } else {
            loop_ub = static_cast<int>(d);
        }
        // 前90 %d的最大值
        // 'CrestFactor:14' V10th = V90th(floor(length(V90th) * 0.1):end -
        // floor(length(V90th) * 0.1));
        d = static_cast<double>(wnd.size(0)) * 0.1;
        coder::b_floor(&d);
        wlen = static_cast<double>(wnd.size(0)) * 0.1;
        coder::b_floor(&wlen);
        wlen = static_cast<double>(wnd.size(0)) - wlen;
        if (d > wlen) {
            i1 = 0;
            i2 = 0;
        } else {
            i1 = static_cast<int>(d) - 1;
            i2 = static_cast<int>(wlen);
        }
        //  10 %到90 %之间的值
        // 'CrestFactor:15' Vrms = rms(V10th);
        // 'CrestFactor:16' Crest_Factor(i) = V90 / Vrms;
        y.set_size(loop_ub);
        for (b_loop_ub = 0; b_loop_ub < loop_ub; b_loop_ub++) {
            y[b_loop_ub] = wnd[b_loop_ub];
        }
        b_loop_ub = i2 - i1;
        for (i2 = 0; i2 < b_loop_ub; i2++) {
            wnd[i2] = wnd[i1 + i2];
        }
        wnd.set_size(b_loop_ub);
        Crest_Factor[b_i] = coder::internal::maximum(y) / coder::rms(wnd);
    }
    // 'CrestFactor:19' CF_mean = mean(Crest_Factor);
    return coder::mean(Crest_Factor);
}

//
// File trailer for CrestFactor.cpp
//
// [EOF]
//
