//
// File: vad_below_threshold.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "vad_below_threshold.h"
#include "ceil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [ostarts, oends] = vad_below_threshold(xn, dth, width)
//
// Arguments    : const coder::array<double, 1U> &xn
//                double dth
//                coder::array<long long, 1U> &ostarts
//                coder::array<long long, 1U> &oends
// Return Type  : void
//
void vad_below_threshold(const coder::array<double, 1U> &xn, double dth,
                         coder::array<long long, 1U> &ostarts,
                         coder::array<long long, 1U> &oends) {
    coder::array<long long, 1U> b_ostarts;
    double count;
    double d;
    long long i1;
    long long len;
    long long qY;
    int i;
    int loop_ub_tmp;
    //  获取高于阈值的段 x数组，dth阈值，width宽度
    // 'vad_below_threshold:3' bufferHeight = ceil(length(xn) / width) + 1;
    d = static_cast<double>(xn.size(0)) / 6.0;
    coder::b_ceil(&d);
    // 'vad_below_threshold:4' ostarts = zeros(bufferHeight, 1, 'int64');
    loop_ub_tmp = static_cast<int>(d + 1.0);
    ostarts.set_size(loop_ub_tmp);
    // 'vad_below_threshold:5' oends = zeros(bufferHeight, 1, 'int64');
    oends.set_size(loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        ostarts[i] = 0LL;
        oends[i] = 0LL;
    }
    // 'vad_below_threshold:6' len = int64(0);
    len = 0LL;
    // 'vad_below_threshold:7' count = 0;
    count = 0.0;
    // 'vad_below_threshold:8' coder.varsize('ostarts');
    // 'vad_below_threshold:9' coder.varsize('oends');
    // 'vad_below_threshold:11' for i = 1:length(xn)
    i = xn.size(0);
    for (int b_i = 0; b_i < i; b_i++) {
        // 'vad_below_threshold:13' if xn(i) > dth
        if (xn[b_i] > dth) {
            // 'vad_below_threshold:14' count = count + 1;
            count++;
        }
        // 'vad_below_threshold:17' if xn(i) <= dth && count >= width
        if ((xn[b_i] <= dth) && (count >= 6.0)) {
            // 'vad_below_threshold:18' len = len + 1;
            if (len > 9223372036854775806LL) {
                qY = MAX_int64_T;
            } else {
                qY = len + 1LL;
            }
            len = qY;
            // 'vad_below_threshold:19' ostarts(len) = i - count;
            d = (static_cast<double>(b_i) + 1.0) - count;
            if (d >= -9.2233720368547758E+18) {
                i1 = static_cast<long long>(d);
            } else {
                i1 = MIN_int64_T;
            }
            ostarts[static_cast<int>(qY) - 1] = i1;
            // 'vad_below_threshold:20' oends(len) = i - 1;
            oends[static_cast<int>(qY) - 1] = b_i;
        }
        // 'vad_below_threshold:23' if xn(i) <= dth
        if (xn[b_i] <= dth) {
            // 'vad_below_threshold:24' count = 0;
            count = 0.0;
        }
    }
    //  到末尾，有声段可能大于
    // 'vad_below_threshold:30' if count >= width
    if (count >= 6.0) {
        // 'vad_below_threshold:31' len = len + 1;
        if (len > 9223372036854775806LL) {
            qY = MAX_int64_T;
        } else {
            qY = len + 1LL;
        }
        len = qY;
        // 'vad_below_threshold:32' ostarts(len) = length(xn) - count + 1;
        d = (static_cast<double>(xn.size(0)) - count) + 1.0;
        if (d >= -9.2233720368547758E+18) {
            i1 = static_cast<long long>(d);
        } else {
            i1 = MIN_int64_T;
        }
        ostarts[static_cast<int>(qY) - 1] = i1;
        // 'vad_below_threshold:33' oends(len) = length(xn);
        oends[static_cast<int>(qY) - 1] = xn.size(0);
    }
    // 'vad_below_threshold:36' ostarts = ostarts(1:len);
    if (1LL > len) {
        loop_ub_tmp = 0;
    } else {
        loop_ub_tmp = static_cast<int>(len);
    }
    b_ostarts.set_size(loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        b_ostarts[i] = ostarts[i];
    }
    ostarts.set_size(b_ostarts.size(0));
    loop_ub_tmp = b_ostarts.size(0);
    for (i = 0; i < loop_ub_tmp; i++) {
        ostarts[i] = b_ostarts[i];
    }
    // 'vad_below_threshold:37' oends = oends(1:len);
    if (1LL > len) {
        loop_ub_tmp = 0;
    } else {
        loop_ub_tmp = static_cast<int>(len);
    }
    b_ostarts.set_size(loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        b_ostarts[i] = oends[i];
    }
    oends.set_size(b_ostarts.size(0));
    loop_ub_tmp = b_ostarts.size(0);
    for (i = 0; i < loop_ub_tmp; i++) {
        oends[i] = b_ostarts[i];
    }
}

//
// File trailer for vad_below_threshold.cpp
//
// [EOF]
//
