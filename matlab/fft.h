//
// File: fft.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef FFT_H
#define FFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y);

    void fft(const ::coder::array<double, 1U> &x, double varargin_1,
             ::coder::array<creal_T, 1U> &y);

    void fft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y);

} // namespace coder

#endif
//
// File trailer for fft.h
//
// [EOF]
//
