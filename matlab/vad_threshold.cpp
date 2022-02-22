//
// File: vad_threshold.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "vad_threshold.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "yuzhiSpeci.h"
#include "coder_array.h"

// Function Definitions
//
// function [dth] = vad_threshold(tis, sorted_sums, position)
//
// Arguments    : double tis
//                const coder::array<double, 2U> &sorted_sums
//                double position
// Return Type  : double
//
double vad_threshold(double tis, const coder::array<double, 2U> &sorted_sums,
                     double position) {
    double dth;
    // 阈值生成
    // 'vad_threshold:4' if tis > 50
    if (tis > 50.0) {
        // 'vad_threshold:5' dth = yuzhiSpeci(sorted_sums, position);
        dth = yuzhiSpeci(sorted_sums, position);
    } else if (tis > 20.0) {
        double minval_tmp;
        // 'vad_threshold:6' elseif tis > 20
        // 'vad_threshold:7' dth = ((max(sorted_sums) - min(sorted_sums)) / 200) *
        // (position + 1.5) + min(sorted_sums);
        minval_tmp = coder::internal::minimum(sorted_sums);
        dth = (coder::internal::maximum(sorted_sums) - minval_tmp) / 200.0 *
              (position + 1.5) +
              minval_tmp;
    } else if (tis > 7.0) {
        double minval_tmp;
        // 'vad_threshold:8' elseif tis > 7
        // 'vad_threshold:9' dth = ((max(sorted_sums) - min(sorted_sums)) / 200) *
        // (-1/13 * tis + 20/13 + position + 2.5) + min(sorted_sums);
        minval_tmp = coder::internal::minimum(sorted_sums);
        dth = (coder::internal::maximum(sorted_sums) - minval_tmp) / 200.0 *
              (((-0.076923076923076927 * tis + 1.5384615384615385) + position) +
               2.5) +
              minval_tmp;
    } else if (tis > 2.0) {
        double minval_tmp;
        // 'vad_threshold:10' elseif tis > 2
        // 'vad_threshold:11' dth = ((max(sorted_sums) - min(sorted_sums)) / 200) *
        // (position + (-0.6 * tis + 5.2) + 2.5) + min(sorted_sums);
        minval_tmp = coder::internal::minimum(sorted_sums);
        dth = (coder::internal::maximum(sorted_sums) - minval_tmp) / 200.0 *
              ((position + (-0.6 * tis + 5.2)) + 2.5) +
              minval_tmp;
    } else {
        double minval_tmp;
        // 'vad_threshold:12' else
        // 'vad_threshold:13' dth = ((max(sorted_sums) - min(sorted_sums)) / 200) *
        // (position + 6.5) + min(sorted_sums);
        minval_tmp = coder::internal::minimum(sorted_sums);
        dth = (coder::internal::maximum(sorted_sums) - minval_tmp) / 200.0 *
              (position + 6.5) +
              minval_tmp;
    }
    return dth;
}

//
// File trailer for vad_threshold.cpp
//
// [EOF]
//
