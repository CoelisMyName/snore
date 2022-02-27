//
// File: noise_segment.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "noise_segment.h"
#include "eml_i64relops.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [ostart, olength] = noise_segment(starts, ends, fs, min_gap, margin)
//
// Arguments    : const coder::array<long long, 1U> &starts
//                const coder::array<long long, 1U> &ends
//                double fs
//                double min_gap
//                double margin
//                double *ostart
//                double *olength
// Return Type  : void
//
void noise_segment(const coder::array<long long, 1U> &starts,
                   const coder::array<long long, 1U> &ends, double fs,
                   double min_gap, double margin, double *ostart,
                   double *olength) {
    double d;
    int i;
    boolean_T exitg1;
    //  输入有声片段数组，返回无声段起点（秒）和长度（秒），-1则找不到符合的无声段
    // 'noise_segment:3' len = min(length(starts), length(ends));
    // 'noise_segment:4' ostart = -1.0;
    *ostart = -1.0;
    // 'noise_segment:5' olength = -1.0;
    *olength = -1.0;
    // 'noise_segment:7' for i = 1:len - 1
    d = coder::internal::minimum2(static_cast<double>(starts.size(0)),
                                  static_cast<double>(ends.size(0))) -
        1.0;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i <= static_cast<int>(d) - 1)) {
        long long q0;
        long long q1;
        // 'noise_segment:9' if starts(i + 1) - ends(i) > margin
        q0 = starts[static_cast<int>((static_cast<double>(i) + 1.0) + 1.0) - 1];
        q1 = ends[i];
        if ((q0 >= 0LL) && (q1 < q0 - MAX_int64_T)) {
            q0 = MAX_int64_T;
        } else if ((q0 < 0LL) && (q1 > q0 - MIN_int64_T)) {
            q0 = MIN_int64_T;
        } else {
            q0 -= q1;
        }
        if (coder::eml_i64relops(q0, margin)) {
            // 'noise_segment:10' oend = (double(starts(i + 1)) - min_gap) / fs;
            // 'noise_segment:11' ostart = (double(ends(i)) + min_gap) / fs;
            *ostart = (static_cast<double>(ends[i]) + min_gap) / fs;
            // 'noise_segment:12' olength = oend - ostart;
            *olength =
                    (static_cast<double>(starts[i + 1]) - min_gap) / fs - *ostart;
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
