#ifndef LEVINSON_H
#define LEVINSON_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void levinson(const ::coder::array<double, 2U> &R,
              ::coder::array<double, 2U> &A, ::coder::array<double, 1U> &E);

}

#endif
