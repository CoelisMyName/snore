//
// File: noise_segment.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "noise_segment.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [n_start, n_length] = noise_segment(w_starts, w_ends, fs, min_gap,
// margin)
//
// Arguments    : const coder::array<double, 2U> &w_starts
//                const coder::array<double, 2U> &w_ends
//                double fs
//                double min_gap
//                double margin
//                double *n_start
//                double *n_length
// Return Type  : void
//
void noise_segment(const coder::array<double, 2U> &w_starts,
                   const coder::array<double, 2U> &w_ends, double fs,
                   double min_gap, double margin, double *n_start,
                   double *n_length) {
    double d;
    int i;
    boolean_T exitg1;
    //  输入有声片段数组，返回无声段起点（秒）和长度（秒），-1则找不到符合的无声段
    // 'noise_segment:3' len = min(length(w_starts), length(w_ends));
    // 'noise_segment:4' n_start = -1;
    *n_start = -1.0;
    // 'noise_segment:5' n_length = -1;
    *n_length = -1.0;
    // 'noise_segment:7' for i = 1:len - 1
    d = coder::internal::minimum2(static_cast<double>(w_starts.size(1)),
                                  static_cast<double>(w_ends.size(1))) -
        1.0;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i <= static_cast<int>(d) - 1)) {
        // 'noise_segment:9' if w_starts(i + 1) - w_ends(i) > margin
        if (w_starts[static_cast<int>((static_cast<double>(i) + 1.0) + 1.0) - 1] -
            w_ends[i] >
            margin) {
            // 'noise_segment:10' n_end = (w_starts(i + 1) - min_gap) / fs;
            // 'noise_segment:11' n_start = (w_ends(i) + min_gap) / fs;
            *n_start = (w_ends[i] + min_gap) / fs;
            // 'noise_segment:12' n_length = n_end - n_start;
            *n_length = (w_starts[i + 1] - min_gap) / fs - *n_start;
            exitg1 = true;
        } else {
            i++;
        }
    }
}

//
// File trailer for noise_segment.cpp
//
// [EOF]
//
