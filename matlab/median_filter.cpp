//
// File: median_filter.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "median_filter.h"
#include "median.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [output] = median_filter(array, window)
//
// Arguments    : const coder::array<double, 2U> &array
//                coder::array<double, 2U> &output
// Return Type  : void
//
void median_filter(const coder::array<double, 2U> &array,
                   coder::array<double, 2U> &output) {
    double temp[10];
    int i;
    // 'median_filter:2' len = length(array);
    // 'median_filter:3' output = zeros(1, len);
    output.set_size(1, array.size(1));
    // 'median_filter:4' temp = zeros(1, window);
    // 'median_filter:5' lm = -floor(window / 2);
    // 'median_filter:6' rm = floor((window - 1) / 2);
    // 'median_filter:8' for i = 1:len
    i = array.size(1);
    for (int b_i = 0; b_i < i; b_i++) {
        // 'median_filter:10' for j = lm:rm
        for (int j = 0; j < 10; j++) {
            double b_index;
            // 'median_filter:11' index = i + j;
            b_index =
                    (static_cast<double>(b_i) + 1.0) + (static_cast<double>(j) + -5.0);
            // 'median_filter:12' tindex = j - lm + 1;
            // 'median_filter:14' if index < 1
            if (b_index < 1.0) {
                // 'median_filter:15' temp(tindex) = 0;
                temp[j] = 0.0;
            } else if (static_cast<unsigned int>(b_index) >
                       static_cast<unsigned int>(array.size(1))) {
                // 'median_filter:16' elseif index > len
                // 'median_filter:17' temp(tindex) = 0;
                temp[j] = 0.0;
            } else {
                // 'median_filter:18' else
                // 'median_filter:19' temp(tindex) = array(index);
                temp[j] = array[static_cast<int>(b_index) - 1];
            }
        }
        // 'median_filter:24' output(i) = median(temp);
        output[b_i] = coder::median(temp);
    }
}

//
// File trailer for median_filter.cpp
//
// [EOF]
//
