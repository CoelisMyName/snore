#ifndef ENFRAME_H
#define ENFRAME_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void enframe(const coder::array<double, 1U> &x,
             const coder::array<double, 1U> &win, double inc,
             coder::array<double, 2U> &f);

#endif
