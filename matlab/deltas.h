#ifndef DELTAS_H
#define DELTAS_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void deltas(const coder::array<double, 2U> &x, coder::array<double, 2U> &d);

#endif
