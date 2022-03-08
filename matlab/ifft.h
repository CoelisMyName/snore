#ifndef IFFT_H
#define IFFT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void b_ifft(const ::coder::array<double, 2U> &x,
            ::coder::array<creal_T, 2U> &y);

void c_ifft(const ::coder::array<double, 2U> &x,
            ::coder::array<creal_T, 2U> &y);

void ifft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y);

void ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y);

} // namespace coder

#endif
