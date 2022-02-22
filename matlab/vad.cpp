//
// File: vad.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "vad.h"
#include "amax_group.h"
#include "fix.h"
#include "hist.h"
#include "mean.h"
#include "median_filter.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sum_group.h"
#include "vad_below_threshold.h"
#include "vad_length_filter.h"
#include "vad_threshold.h"
#include "vad_wave.h"
#include "coder_array.h"

// Function Definitions
//
// function [w_starts, w_ends] = vad(x, fs)
//
// %% -------------------音频最小长度60秒---------------------------
//
// Arguments    : coder::array<double, 2U> &x
//                double fs
//                coder::array<double, 2U> &w_starts
//                coder::array<double, 2U> &w_ends
// Return Type  : void
//
void vad(coder::array<double, 2U> &x, double fs,
         coder::array<double, 2U> &w_starts, coder::array<double, 2U> &w_ends) {
    coder::array<double, 2U> b_maxs;
    coder::array<double, 2U> maxs;
    coder::array<double, 2U> nx3;
    coder::array<double, 2U> nx4;
    coder::array<double, 2U> sums;
    double a__1[200];
    double bins[200];
    double MIN_LEN;
    int i;
    int iindx;
    int unnamed_idx_1;
    //  只接受1分钟长度的音频，多的截去，少的补0
    // 'vad:5' MIN_LEN = 60 * fs;
    MIN_LEN = 60.0 * fs;
    // 'vad:6' if(length(x) > MIN_LEN)
    if (x.size(1) > MIN_LEN) {
        // 'vad:7' x = x(1:MIN_LEN);
        if (1.0 > MIN_LEN) {
            i = 0;
        } else {
            i = static_cast<int>(MIN_LEN);
        }
        x.set_size(x.size(0), i);
    }
    // 'vad:9' if(length(x) < MIN_LEN)
    if (x.size(1) < MIN_LEN) {
        // 'vad:10' x = [x zeros(1,MIN_LEN - length(x))];
        unnamed_idx_1 = static_cast<int>(MIN_LEN - static_cast<double>(x.size(1)));
        i = x.size(1);
        x.set_size(1, x.size(1) + unnamed_idx_1);
        for (iindx = 0; iindx < unnamed_idx_1; iindx++) {
            x[iindx + i] = 0.0;
        }
    }
    // 'vad:13' maxs = amax_group(x, 50);
    amax_group(x, maxs);
    // 'vad:14' sums = sum_group(maxs, 50);
    sum_group(maxs, sums);
    // 'vad:15' sums = median_filter(sums, 10);
    maxs.set_size(1, sums.size(1));
    unnamed_idx_1 = sums.size(0) * sums.size(1) - 1;
    for (i = 0; i <= unnamed_idx_1; i++) {
        maxs[i] = sums[i];
    }
    median_filter(maxs, sums);
    // 'vad:17' [bins, ~] = hist(sums, 200);
    coder::hist(sums, bins, a__1);
    // 'vad:18' [~, position] = max(bins);
    coder::internal::maximum(bins, &MIN_LEN, &iindx);
    // 'vad:19' bins = sort(bins);
    coder::internal::sort(bins);
    // 'vad:20' tis = bins(end) / bins(end - 1);
    // 'vad:21' sorted_sums = sort(sums);
    maxs.set_size(1, sums.size(1));
    unnamed_idx_1 = sums.size(1);
    for (i = 0; i < unnamed_idx_1; i++) {
        maxs[i] = sums[i];
    }
    coder::internal::sort(maxs);
    // 前60%的平均值
    // 'vad:23' ddth = mean(sorted_sums(1:fix(length(sorted_sums) * 0.6)));
    MIN_LEN = static_cast<double>(maxs.size(1)) * 0.6;
    coder::b_fix(&MIN_LEN);
    if (1.0 > MIN_LEN) {
        unnamed_idx_1 = 0;
    } else {
        unnamed_idx_1 = static_cast<int>(MIN_LEN);
    }
    // 取阈值？
    // 'vad:26' dth = vad_threshold(tis, sorted_sums, position);
    MIN_LEN =
            vad_threshold(bins[199] / bins[198], maxs, static_cast<double>(iindx));
    // 'vad:28' w_starts = [];
    w_starts.set_size(0, 0);
    // 'vad:29' w_ends = [];
    w_ends.set_size(0, 0);
    // 'vad:30' coder.varsize('w_starts');
    // 'vad:31' coder.varsize('w_ends');
    // 'vad:33' if max(sorted_sums) >= ddth * 5
    b_maxs.set_size(1, unnamed_idx_1);
    for (i = 0; i < unnamed_idx_1; i++) {
        b_maxs[i] = maxs[i];
    }
    if (coder::internal::maximum(maxs) >= coder::mean(b_maxs) * 5.0) {
        // 'vad:34' [nx1, nx2] = vad_below_threshold(sums, dth, 6);
        vad_below_threshold(sums, MIN_LEN, maxs, b_maxs);
        // 'vad:35' [nx3, nx4] = vad_wave(sums, nx1, nx2);
        vad_wave(sums, maxs, b_maxs, nx3, nx4);
        //  映射至实际区间
        // 'vad:37' w_starts = (nx3 - 1) * 2500 + 1;
        w_starts.set_size(1, nx3.size(1));
        unnamed_idx_1 = nx3.size(1);
        for (i = 0; i < unnamed_idx_1; i++) {
            w_starts[i] = (nx3[i] - 1.0) * 2500.0 + 1.0;
        }
        // 'vad:38' w_ends = nx4 * 2500;
        w_ends.set_size(1, nx4.size(1));
        unnamed_idx_1 = nx4.size(1);
        for (i = 0; i < unnamed_idx_1; i++) {
            w_ends[i] = nx4[i] * 2500.0;
        }
    }
    // 截取段过滤
    // 'vad:41' [w_starts, w_ends] = vad_length_filter(w_starts, w_ends, 0.03 *
    // fs, 5 * fs);
    vad_length_filter(w_starts, w_ends, 0.03 * fs, 5.0 * fs, maxs, b_maxs);
    w_starts.set_size(1, maxs.size(1));
    unnamed_idx_1 = maxs.size(1);
    for (i = 0; i < unnamed_idx_1; i++) {
        w_starts[i] = maxs[i];
    }
    w_ends.set_size(1, b_maxs.size(1));
    unnamed_idx_1 = b_maxs.size(1);
    for (i = 0; i < unnamed_idx_1; i++) {
        w_ends[i] = b_maxs[i];
    }
}

//
// File trailer for vad.cpp
//
// [EOF]
//
