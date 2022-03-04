#ifndef BLOCKEDSUMMATION_H
#define BLOCKEDSUMMATION_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
double blockedSummation(const ::coder::array<double, 1U> &x, int vlen);

}

#endif
