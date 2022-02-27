//
// File: vad_threshold.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef VAD_THRESHOLD_H
#define VAD_THRESHOLD_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
double vad_threshold(double tis, const coder::array<double, 1U> &sorted_sums,
                     double position);

#endif
//
// File trailer for vad_threshold.h
//
// [EOF]
//
