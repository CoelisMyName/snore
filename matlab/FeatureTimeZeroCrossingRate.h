//
// File: FeatureTimeZeroCrossingRate.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef FEATURETIMEZEROCROSSINGRATE_H
#define FEATURETIMEZEROCROSSINGRATE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void FeatureTimeZeroCrossingRate(const coder::array<double, 1U> &x,
                                 double iBlockLength, double iHopLength,
                                 double f_s, coder::array<double, 2U> &vzc,
                                 coder::array<double, 2U> &t);

#endif
//
// File trailer for FeatureTimeZeroCrossingRate.h
//
// [EOF]
//
