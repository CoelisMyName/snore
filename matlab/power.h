//
// File: power.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef POWER_H
#define POWER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void b_power(const ::coder::array<double, 2U> &b,
                 ::coder::array<double, 2U> &y);

    void c_power(const ::coder::array<double, 2U> &a,
                 ::coder::array<double, 2U> &y);

    void d_power(const ::coder::array<double, 2U> &a,
                 ::coder::array<double, 2U> &y);

    void power(const ::coder::array<double, 2U> &a, ::coder::array<double, 2U> &y);

    void power(const ::coder::array<double, 1U> &a, ::coder::array<double, 1U> &y);

    void power(const double b[8], double y[8]);

} // namespace coder

#endif
//
// File trailer for power.h
//
// [EOF]
//
