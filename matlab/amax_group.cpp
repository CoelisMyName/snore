//
// File: amax_group.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "amax_group.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [result] = amax_group(array, width)
//
// Arguments    : const coder::array<double, 2U> &array
//                coder::array<double, 2U> &result
// Return Type  : void
//
void amax_group(const coder::array<double, 2U> &array,
                coder::array<double, 2U> &result)
{
  coder::array<double, 2U> varargin_1;
  int b_i;
  int i;
  int i1;
  int k;
  int nx;
  // 给定宽度内绝对值最大值
  // 'amax_group:3' result = zeros(1, floor(length(array) / width));
  i = static_cast<int>(std::floor(static_cast<double>(array.size(1)) / 50.0));
  // 'amax_group:5' for i = 1:length(result)
  result.set_size(1, i);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    varargin_1, k, nx, i1, b_i)

  for (b_i = 0; b_i < i; b_i++) {
    // 'amax_group:6' result(i) = max(abs(array((i - 1) * width + 1:i *
    // width)));
    i1 = b_i * 50;
    k = (b_i + 1) * 50;
    if (i1 + 1 > k) {
      i1 = -1;
      k = -1;
    } else {
      i1--;
      k--;
    }
    k -= i1;
    nx = k - 1;
    varargin_1.set_size(1, k);
    for (k = 0; k <= nx; k++) {
      varargin_1[k] = std::abs(array[(i1 + k) + 1]);
    }
    result[b_i] = coder::internal::maximum(varargin_1);
  }
}

//
// File trailer for amax_group.cpp
//
// [EOF]
//
