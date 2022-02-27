//
// File: mean.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef MEAN_H
#define MEAN_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void mean(const ::coder::array<double, 2U> &x, double y_data[], int *y_size);

    void mean(const ::coder::array<double, 2U> &x, double y[12]);

    void mean(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);

    double mean(const ::coder::array<double, 2U> &x);

    double mean(const ::coder::array<double, 1U> &x);

} // namespace coder

#endif
//
// File trailer for mean.h
//
// [EOF]
//
