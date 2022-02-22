//
// File: vad_below_threshold.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "vad_below_threshold.h"
#include "ceil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [starts, ends] = vad_below_threshold(xn, dth, width)
//
// Arguments    : const coder::array<double, 2U> &xn
//                double dth
//                coder::array<double, 2U> &starts
//                coder::array<double, 2U> &ends
// Return Type  : void
//
void vad_below_threshold(const coder::array<double, 2U> &xn, double dth,
                         coder::array<double, 2U> &starts,
                         coder::array<double, 2U> &ends) {
    coder::array<double, 2U> b_ends;
    double count;
    double d;
    int i;
    unsigned int len;
    int loop_ub_tmp;
    //  获取高于阈值的段 x数组，dth阈值，width宽度
    // 'vad_below_threshold:3' starts = zeros(1,ceil(length(xn) / width));
    d = static_cast<double>(xn.size(1)) / 6.0;
    coder::b_ceil(&d);
    loop_ub_tmp = static_cast<int>(d);
    starts.set_size(1, loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        starts[i] = 0.0;
    }
    // 'vad_below_threshold:4' ends = zeros(1,ceil(length(xn)/ width));
    d = static_cast<double>(xn.size(1)) / 6.0;
    coder::b_ceil(&d);
    loop_ub_tmp = static_cast<int>(d);
    ends.set_size(1, loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        ends[i] = 0.0;
    }
    // 'vad_below_threshold:5' len = 0;
    len = 0U;
    // 'vad_below_threshold:6' count = 0;
    count = 0.0;
    // 'vad_below_threshold:7' coder.varsize('starts');
    // 'vad_below_threshold:8' coder.varsize('ends');
    // 'vad_below_threshold:9' for i = 1:length(xn)
    i = xn.size(1);
    for (loop_ub_tmp = 0; loop_ub_tmp < i; loop_ub_tmp++) {
        // 'vad_below_threshold:11' if xn(i) > dth
        d = xn[loop_ub_tmp];
        if (d > dth) {
            // 'vad_below_threshold:12' count = count + 1;
            count++;
        }
        // 'vad_below_threshold:15' if xn(i) <= dth && count >= width
        if ((d <= dth) && (count >= 6.0)) {
            // 'vad_below_threshold:16' len = len + 1;
            len++;
            // 'vad_below_threshold:17' starts(len) = i - count;
            starts[static_cast<int>(len) - 1] =
                    (static_cast<double>(loop_ub_tmp) + 1.0) - count;
            // 'vad_below_threshold:18' ends(len) = i - 1;
            ends[static_cast<int>(len) - 1] =
                    (static_cast<double>(loop_ub_tmp) + 1.0) - 1.0;
        }
        // 'vad_below_threshold:21' if xn(i) <= dth
        if (d <= dth) {
            // 'vad_below_threshold:22' count = 0;
            count = 0.0;
        }
    }
    //  到末尾，有声段可能大于
    // 'vad_below_threshold:28' if count >= width
    if (count >= 6.0) {
        // 'vad_below_threshold:29' len = len + 1;
        len++;
        // 'vad_below_threshold:30' starts(len) = length(xn) - count + 1;
        starts[static_cast<int>(len) - 1] =
                (static_cast<double>(xn.size(1)) - count) + 1.0;
        // 'vad_below_threshold:31' ends(len) = length(xn);
        ends[static_cast<int>(len) - 1] = xn.size(1);
    }
    // 'vad_below_threshold:34' starts = starts(1:len);
    if (1 > static_cast<int>(len)) {
        i = 0;
    } else {
        i = static_cast<int>(len);
    }
    starts.set_size(starts.size(0), i);
    // 'vad_below_threshold:35' ends = ends(1:len);
    if (1 > static_cast<int>(len)) {
        loop_ub_tmp = 0;
    } else {
        loop_ub_tmp = static_cast<int>(len);
    }
    b_ends.set_size(1, loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        b_ends[i] = static_cast<unsigned int>(ends[i]);
    }
    ends.set_size(1, b_ends.size(1));
    loop_ub_tmp = b_ends.size(1);
    for (i = 0; i < loop_ub_tmp; i++) {
        ends[i] = b_ends[i];
    }
}

//
// File trailer for vad_below_threshold.cpp
//
// [EOF]
//
