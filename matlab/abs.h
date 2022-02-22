//
// File: abs.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef ABS_H
#define ABS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void b_abs(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &y);

    void b_abs(const ::coder::array<creal_T, 2U> &x, ::coder::array<double, 2U> &y);

    void b_abs(const ::coder::array<creal_T, 1U> &x, ::coder::array<double, 1U> &y);

    void b_abs(const double x[2], double y[2]);

    void b_abs(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);

    double b_abs(double x);

    void c_abs(const double x[4], double y[4]);

} // namespace coder

#endif
//
// File trailer for abs.h
//
// [EOF]
//
