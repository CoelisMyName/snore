//
// File: HENR.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "HENR.h"
#include "combineVectorElements.h"
#include "enframe.h"
#include "fix.h"
#include "hanning.h"
#include "mean.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [Eh, En_mean] = HENR(x, fs)
//
// 高能量帧比率，计算一段声音信号中短时能量大于平均短时能量*0.5的比率
//  输入x为信号，fs为采样率
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs
//                double *Eh
//                double *En_mean
// Return Type  : void
//
void HENR(const coder::array<double, 1U> &x, double fs, double *Eh,
          double *En_mean) {
    coder::array<double, 2U> En;
    coder::array<double, 2U> r1;
    coder::array<double, 2U> y;
    coder::array<double, 1U> r;
    coder::array<boolean_T, 2U> b_En;
    double d;
    double wlen;
    int i;
    int i1;
    int loop_ub;
    // 'HENR:4' wlen = fix(0.02 * fs);
    wlen = 0.02 * fs;
    coder::b_fix(&wlen);
    // 'HENR:5' inc = fix(0.5 * wlen);
    // 'HENR:6' wnd = hanning(wlen);
    // 'HENR:7' y = enframe(x, wnd, inc)';
    d = 0.5 * wlen;
    coder::b_fix(&d);
    coder::hanning(wlen, r);
    enframe(x, r, d, r1);
    y.set_size(r1.size(1), r1.size(0));
    loop_ub = r1.size(0);
    for (i = 0; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = r1.size(1);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            y[i1 + y.size(0) * i] = r1[i + r1.size(0) * i1];
        }
    }
    // 'HENR:8' fn = size(y, 2);
    // 'HENR:9' En = zeros(1, fn);
    En.set_size(1, y.size(1));
    // 'HENR:11' for i = 1:fn
    i = y.size(1);
    for (int b_i = 0; b_i < i; b_i++) {
        double b_y;
        // 'HENR:12' Y = y(:, i);
        // 'HENR:13' En(i) = Y' * Y;
        loop_ub = y.size(0);
        b_y = 0.0;
        for (i1 = 0; i1 < loop_ub; i1++) {
            d = y[i1 + y.size(0) * b_i];
            b_y += d * d;
        }
        En[b_i] = b_y;
    }
    // 'HENR:16' En_mean = mean(En);
    *En_mean = coder::mean(En);
    // 求取频率能量
    // 'HENR:17' Eh = sum(En > (0.5 * En_mean)) / fn;
    d = 0.5 * *En_mean;
    b_En.set_size(1, En.size(1));
    loop_ub = En.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_En[i] = (En[i] > d);
    }
    *Eh = static_cast<double>(coder::b_combineVectorElements(b_En)) /
          static_cast<double>(y.size(1));
}

//
// File trailer for HENR.cpp
//
// [EOF]
//
