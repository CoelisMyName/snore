#ifndef VAD_H
#define VAD_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void vad(const coder::array<double, 1U> &x, double fs,
                coder::array<long long, 1U> &w_starts,
                coder::array<long long, 1U> &w_ends);

#endif
