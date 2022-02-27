//
// File: vad_below_threshold.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef VAD_BELOW_THRESHOLD_H
#define VAD_BELOW_THRESHOLD_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void vad_below_threshold(const coder::array<double, 1U> &xn, double dth,
                         coder::array<long long, 1U> &ostarts,
                         coder::array<long long, 1U> &oends);

#endif
//
// File trailer for vad_below_threshold.h
//
// [EOF]
//
