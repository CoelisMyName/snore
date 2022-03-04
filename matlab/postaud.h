#ifndef POSTAUD_H
#define POSTAUD_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void postaud(const coder::array<double, 2U> &x, double b_fmax,
             coder::array<double, 2U> &y);

#endif
