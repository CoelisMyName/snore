//
// File: filter.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef FILTER_H
#define FILTER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void b_filter(const ::coder::array<double, 2U> &x,
                  ::coder::array<double, 2U> &y);

    void b_filter(const ::coder::array<double, 1U> &x,
                  ::coder::array<double, 1U> &y);

    void filter(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);

    void filter(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &y);

    void filter(double b[3], double a[3], const ::coder::array<double, 1U> &x,
                const double zi[2], ::coder::array<double, 1U> &y, double zf[2]);

    void filter(const double b[7], const double a[7],
                const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &y);

} // namespace coder

#endif
//
// File trailer for filter.h
//
// [EOF]
//
