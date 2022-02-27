//
// File: LPCFeature.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "LPCFeature.h"
#include "enframe.h"
#include "filter.h"
#include "fix.h"
#include "hamming.h"
#include "m_lpc.h"
#include "mean.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "var.h"
#include "coder_array.h"

// Function Definitions
//
// function [LPC, LPC_mean, LPC_max, LPC_min, LPC_var] = LPCFeature(x, Fs)
//
// UNTITLED2 此处显示有关此函数的摘要
//    此处显示详细说明
//
// Arguments    : const coder::array<double, 1U> &x
//                double Fs
//                coder::array<double, 2U> &LPC
//                double LPC_mean[12]
//                double LPC_max[12]
//                double LPC_min[12]
//                double LPC_var[12]
// Return Type  : void
//
void LPCFeature(const coder::array<double, 1U> &x, double Fs,
                coder::array<double, 2U> &LPC, double LPC_mean[12],
                double LPC_max[12], double LPC_min[12], double LPC_var[12]) {
    coder::array<double, 2U> b_LPC;
    coder::array<double, 2U> c_LPC;
    coder::array<double, 2U> d_LPC;
    coder::array<double, 2U> r1;
    coder::array<double, 2U> y;
    coder::array<double, 1U> b_y;
    coder::array<double, 1U> r;
    double tmp_data[13];
    double d;
    double wlen;
    int tmp_size[2];
    int b_loop_ub;
    int i;
    int i1;
    int loop_ub;
    // 'LPCFeature:4' wlen = fix(0.02 * Fs);
    wlen = 0.02 * Fs;
    coder::b_fix(&wlen);
    // 'LPCFeature:5' inc = fix(0.5 * wlen);
    // 'LPCFeature:6' wind = hamming(wlen);
    // 'LPCFeature:7' y = enframe(x, wind, inc)';
    d = 0.5 * wlen;
    coder::b_fix(&d);
    coder::hamming(wlen, r);
    enframe(x, r, d, r1);
    y.set_size(r1.size(1), r1.size(0));
    loop_ub = r1.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_loop_ub = r1.size(1);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            y[i1 + y.size(0) * i] = r1[i + r1.size(0) * i1];
        }
    }
    // 分帧
    // 'LPCFeature:8' fn = size(y, 2);
    // 总帧数
    // 'LPCFeature:9' LPC = zeros(13, fn);
    b_LPC.set_size(13, y.size(1));
    loop_ub = 13 * y.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_LPC[i] = 0.0;
    }
    // 'LPCFeature:11' for i = 1:fn
    i = y.size(1);
    for (int b_i = 0; b_i < i; b_i++) {
        // 'LPCFeature:12' YY = y(:, i);
        // 取一帧数据
        // 'LPCFeature:13' z_new = filter([1 -0.99], 1, YY);
        // 预加重
        // 'LPCFeature:14' LPC(:, i) = m_lpc(z_new, 12);
        loop_ub = y.size(0);
        b_y.set_size(y.size(0));
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_y[i1] = y[i1 + y.size(0) * b_i];
        }
        coder::b_filter(b_y, r);
        m_lpc(r, tmp_data, tmp_size);
        for (i1 = 0; i1 < 13; i1++) {
            b_LPC[i1 + 13 * b_i] = tmp_data[i1];
        }
    }
    // 'LPCFeature:17' LPC = LPC';
    c_LPC.set_size(b_LPC.size(1), 13);
    loop_ub = b_LPC.size(1);
    for (i = 0; i < 13; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            c_LPC[i1 + c_LPC.size(0) * i] = b_LPC[i + 13 * i1];
        }
    }
    // 每一行有13个系数
    // 'LPCFeature:18' LPC = LPC(:, 2:13);
    loop_ub = c_LPC.size(0);
    LPC.set_size(c_LPC.size(0), 12);
    // 'LPCFeature:19' LPC_mean = mean(LPC);
    b_loop_ub = c_LPC.size(0);
    d_LPC.set_size(c_LPC.size(0), 12);
    for (i = 0; i < 12; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            LPC[i1 + LPC.size(0) * i] = c_LPC[i1 + c_LPC.size(0) * (i + 1)];
        }
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            d_LPC[i1 + d_LPC.size(0) * i] = c_LPC[i1 + c_LPC.size(0) * (i + 1)];
        }
    }
    coder::mean(d_LPC, LPC_mean);
    // 'LPCFeature:20' LPC_max = max(LPC);
    loop_ub = c_LPC.size(0);
    d_LPC.set_size(c_LPC.size(0), 12);
    for (i = 0; i < 12; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            d_LPC[i1 + d_LPC.size(0) * i] = c_LPC[i1 + c_LPC.size(0) * (i + 1)];
        }
    }
    coder::internal::maximum(d_LPC, LPC_max);
    // 'LPCFeature:21' LPC_min = min(LPC);
    loop_ub = c_LPC.size(0);
    d_LPC.set_size(c_LPC.size(0), 12);
    for (i = 0; i < 12; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            d_LPC[i1 + d_LPC.size(0) * i] = c_LPC[i1 + c_LPC.size(0) * (i + 1)];
        }
    }
    coder::internal::minimum(d_LPC, LPC_min);
    // 'LPCFeature:22' LPC_var = var(LPC);
    loop_ub = c_LPC.size(0);
    d_LPC.set_size(c_LPC.size(0), 12);
    for (i = 0; i < 12; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            d_LPC[i1 + d_LPC.size(0) * i] = c_LPC[i1 + c_LPC.size(0) * (i + 1)];
        }
    }
    coder::var(d_LPC, LPC_var);
}

//
// File trailer for LPCFeature.cpp
//
// [EOF]
//
