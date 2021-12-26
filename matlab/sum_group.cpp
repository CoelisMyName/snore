//
// File: sum_group.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "sum_group.h"
#include "combineVectorElements.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [result] = sum_group(array, width)
//
// Arguments    : const coder::array<double, 2U> &array
//                coder::array<double, 2U> &result
// Return Type  : void
//
void sum_group(const coder::array<double, 2U> &array,
               coder::array<double, 2U> &result)
{
  coder::array<double, 2U> b_array;
  int b_i;
  int i;
  int i1;
  int i2;
  int loop_ub;
  // 给定宽度求和
  // 'sum_group:3' result = zeros(1, floor(length(array) / width));
  i = static_cast<int>(std::floor(static_cast<double>(array.size(1)) / 50.0));
  // 'sum_group:5' for i = 1:length(result)
  result.set_size(1, i);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    b_array, i1, i2, b_i, loop_ub)

  for (b_i = 0; b_i < i; b_i++) {
    // 'sum_group:6' result(i) = sum(array((i - 1) * width + 1:i * width));
    i2 = b_i * 50;
    i1 = (b_i + 1) * 50;
    if (i2 + 1 > i1) {
      i2 = 0;
      i1 = 0;
    }
    loop_ub = i1 - i2;
    b_array.set_size(1, loop_ub);
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_array[i1] = array[i2 + i1];
    }
    result[b_i] = coder::combineVectorElements(b_array);
  }
}

//
// File trailer for sum_group.cpp
//
// [EOF]
//
