//
// File: amax_group.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "amax_group.h"
#include "abs.h"
#include "floor.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [result] = amax_group(array, width)
//
// Arguments    : const coder::array<double, 1U> &array
//                coder::array<double, 1U> &result
// Return Type  : void
//
void amax_group(const coder::array<double, 1U> &array,
                coder::array<double, 1U> &result) {
    coder::array<double, 1U> b_array;
    coder::array<double, 1U> r;
    double d;
    int i;
    int loop_ub_tmp;
    // 给定宽度内绝对值最大值
    // 'amax_group:3' result = zeros(floor(length(array) / width), 1);
    d = static_cast<double>(array.size(0)) / 50.0;
    coder::b_floor(&d);
    loop_ub_tmp = static_cast<int>(d);
    result.set_size(loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        result[i] = 0.0;
    }
    // 'amax_group:5' for i = 1:length(result)
    d = static_cast<double>(array.size(0)) / 50.0;
    coder::b_floor(&d);
    i = static_cast<int>(d);
    for (int b_i = 0; b_i < i; b_i++) {
        int i1;
        int loop_ub;
        // 'amax_group:6' result(i) = max(abs(array((i - 1) * width + 1:i *
        // width)));
        loop_ub_tmp = b_i * 50;
        i1 = (b_i + 1) * 50;
        if (loop_ub_tmp + 1 > i1) {
            loop_ub_tmp = 0;
            i1 = 0;
        }
        loop_ub = i1 - loop_ub_tmp;
        b_array.set_size(loop_ub);
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_array[i1] = array[loop_ub_tmp + i1];
        }
        coder::b_abs(b_array, r);
        result[b_i] = coder::internal::maximum(r);
    }
}

//
// File trailer for amax_group.cpp
//
// [EOF]
//
