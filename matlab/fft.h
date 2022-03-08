#ifndef FFT_H
#define FFT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void b_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y);

void c_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y);

void fft(const ::coder::array<double, 1U> &x, double varargin_1,
         ::coder::array<creal_T, 1U> &y);

void fft(const ::coder::array<double, 2U> &x, double varargin_1,
         ::coder::array<creal_T, 2U> &y);

void fft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y);

void fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y);

} // namespace coder

#endif
