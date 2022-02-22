//
// File: mean.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
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
    double mean(const ::coder::array<double, 1U> &x);

    void mean(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);

    void mean(const ::coder::array<double, 2U> &x, double y[12]);

    double mean(const ::coder::array<double, 2U> &x);

} // namespace coder

#endif
//
// File trailer for mean.h
//
// [EOF]
//
