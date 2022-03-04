#ifndef STFT_H
#define STFT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace audio {
namespace internal {
namespace spectralDescriptors {
void b_stft(const ::coder::array<double, 1U> &x,
            ::coder::array<double, 2U> &Yb);

void c_stft(const ::coder::array<double, 1U> &x,
            ::coder::array<double, 2U> &Yb);

void d_stft(const ::coder::array<double, 1U> &x,
            ::coder::array<double, 2U> &Yb);

void e_stft(const ::coder::array<double, 1U> &x,
            ::coder::array<double, 2U> &Yb);

void f_stft(const ::coder::array<double, 1U> &x,
            ::coder::array<double, 2U> &Yb);

void g_stft(const ::coder::array<double, 1U> &x,
            ::coder::array<double, 2U> &Yb);

void stft(const ::coder::array<double, 1U> &x, ::coder::array<double, 2U> &Yb);

} // namespace spectralDescriptors
} // namespace internal
} // namespace audio
} // namespace coder

#endif
