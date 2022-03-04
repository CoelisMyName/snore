#ifndef MFCC_M_H
#define MFCC_M_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void mfcc_m(const coder::array<double, 1U> &x, double fs, double frameSize,
            double inc, coder::array<double, 2U> &ccc);

#endif
