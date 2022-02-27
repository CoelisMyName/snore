//
// File: permute.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef PERMUTE_H
#define PERMUTE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void b_permute(const ::coder::array<double, 3U> &a,
                   ::coder::array<double, 3U> &b);

    void b_permute(const ::coder::array<double, 2U> &a,
                   ::coder::array<double, 2U> &b);

    void permute(const ::coder::array<double, 2U> &a,
                 ::coder::array<double, 2U> &b);

    void permute(const ::coder::array<double, 3U> &a,
                 ::coder::array<double, 3U> &b);

    void permute(const ::coder::array<double, 2U> &a,
                 ::coder::array<double, 1U> &b);

} // namespace coder

#endif
//
// File trailer for permute.h
//
// [EOF]
//
