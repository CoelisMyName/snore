#ifndef CEPSTRALCOEFFICIENTS_H
#define CEPSTRALCOEFFICIENTS_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void cepstralCoefficients(::coder::array<double, 2U> &S,
                          ::coder::array<double, 2U> &coeffs);

}

#endif
