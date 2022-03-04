#ifndef FEATURETIMEZEROCROSSINGRATE_H
#define FEATURETIMEZEROCROSSINGRATE_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void FeatureTimeZeroCrossingRate(const coder::array<double, 1U> &x,
                                 double iBlockLength, double iHopLength,
                                 double f_s, coder::array<double, 2U> &vzc,
                                 coder::array<double, 2U> &t);

#endif
