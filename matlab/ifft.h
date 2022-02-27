//
// File: ifft.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef IFFT_H
#define IFFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y);

    void ifft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y);

} // namespace coder

#endif
//
// File trailer for ifft.h
//
// [EOF]
//
