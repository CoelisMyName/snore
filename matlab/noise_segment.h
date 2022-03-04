#ifndef NOISE_SEGMENT_H
#define NOISE_SEGMENT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void noise_segment(const coder::array<long long, 1U> &starts,
                          const coder::array<long long, 1U> &ends, double fs,
                          double min_gap, double margin, double *ostart,
                          double *olength);

#endif
