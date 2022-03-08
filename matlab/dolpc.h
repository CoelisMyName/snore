#ifndef DOLPC_H
#define DOLPC_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void dolpc(const coder::array<double, 2U> &x, coder::array<double, 2U> &y);

#endif
