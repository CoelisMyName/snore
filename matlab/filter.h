//
// File: filter.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
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
    void b_filter(const ::coder::array<double, 1U> &x,
                  ::coder::array<double, 1U> &y);

    void filter(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &y);

    void filter(const double b[7], const double a[7],
                const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);

} // namespace coder

#endif
//
// File trailer for filter.h
//
// [EOF]
//
