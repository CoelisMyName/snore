//
// File: median_filter.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "median_filter.h"
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [output] = median_filter(array, window)
//
// Arguments    : const coder::array<double, 2U> &array
//                coder::array<double, 2U> &output
// Return Type  : void
//
void median_filter(const coder::array<double, 2U> &array,
                   coder::array<double, 2U> &output)
{
  double temp[10];
  double b;
  double m;
  int b_index;
  int i;
  int ilast;
  int j;
  // 'median_filter:2' len = length(array);
  // 'median_filter:3' output = zeros(1, len);
  output.set_size(1, array.size(1));
  // 'median_filter:4' temp = zeros(1, window);
  // 'median_filter:5' lm = -floor(window / 2);
  // 'median_filter:6' rm = floor((window - 1) / 2);
  // 'median_filter:8' for i = 1:len
  i = array.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    // 'median_filter:10' for j = lm:rm
    for (j = 0; j < 10; j++) {
      // 'median_filter:11' index = i + j;
      b_index = (b_i + j) - 4;
      // 'median_filter:12' tindex = j - lm + 1;
      // 'median_filter:14' if index < 1
      if (b_index < 1) {
        // 'median_filter:15' temp(tindex) = 0;
        temp[j] = 0.0;
      } else if (b_index > array.size(1)) {
        // 'median_filter:16' elseif index > len
        // 'median_filter:17' temp(tindex) = 0;
        temp[j] = 0.0;
      } else {
        // 'median_filter:18' else
        // 'median_filter:19' temp(tindex) = array(index);
        temp[j] = array[b_index - 1];
      }
    }
    // 'median_filter:24' output(i) = median(temp);
    b_index = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (b_index < 10) {
        if (std::isnan(temp[b_index])) {
          output[b_i] = rtNaN;
          exitg1 = 1;
        } else {
          b_index++;
        }
      } else {
        coder::internal::quickselect(temp, 6, 10, &m, &b_index, &ilast);
        output[b_i] = m;
        if (5 < b_index) {
          coder::internal::quickselect(temp, 5, ilast - 1, &b, &b_index, &j);
          if (std::isinf(m)) {
            output[b_i] = (m + b) / 2.0;
          } else {
            output[b_i] = m + (b - m) / 2.0;
          }
        }
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

//
// File trailer for median_filter.cpp
//
// [EOF]
//
