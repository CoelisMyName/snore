#ifndef SPECTRALENTROPY_H
#define SPECTRALENTROPY_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void b_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy);

void c_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy);

void d_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy);

void spectralEntropy(const ::coder::array<double, 1U> &x,
                     ::coder::array<double, 1U> &entropy);

} // namespace coder

#endif
