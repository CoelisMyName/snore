//
// File: ifft.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef IFFT_H
#define IFFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void b_ifft(const ::coder::array<double, 2U> &x,
            ::coder::array<creal_T, 2U> &y);

void c_ifft(const ::coder::array<double, 2U> &x,
            ::coder::array<creal_T, 2U> &y);

void d_ifft(const ::coder::array<double, 2U> &x,
            ::coder::array<creal_T, 2U> &y);

void ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y);

void ifft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y);

} // namespace coder

#endif
//
// File trailer for ifft.h
//
// [EOF]
//
