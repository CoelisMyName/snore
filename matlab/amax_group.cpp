//
// File: amax_group.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
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
// Arguments    : const coder::array<double, 2U> &array
//                coder::array<double, 2U> &result
// Return Type  : void
//
void amax_group(const coder::array<double, 2U> &array,
                coder::array<double, 2U> &result) {
    coder::array<double, 2U> b_array;
    coder::array<double, 2U> r;
    double d;
    int i;
    // 给定宽度内绝对值最大值
    // 'amax_group:3' result = zeros(1, floor(length(array) / width));
    d = static_cast<double>(array.size(1)) / 50.0;
    coder::b_floor(&d);
    // 'amax_group:5' for i = 1:length(result)
    i = static_cast<int>(d);
    result.set_size(1, i);
    for (int b_i = 0; b_i < i; b_i++) {
        double d1;
        int i1;
        int i2;
        int loop_ub;
        // 'amax_group:6' result(i) = max(abs(array((i - 1) * width + 1:i *
        // width)));
        d = ((static_cast<double>(b_i) + 1.0) - 1.0) * 50.0 + 1.0;
        d1 = (static_cast<double>(b_i) + 1.0) * 50.0;
        if (d > d1) {
            i1 = 0;
            i2 = 0;
        } else {
            i1 = static_cast<int>(d) - 1;
            i2 = static_cast<int>(d1);
        }
        loop_ub = i2 - i1;
        b_array.set_size(1, loop_ub);
        for (i2 = 0; i2 < loop_ub; i2++) {
            b_array[i2] = array[i1 + i2];
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
