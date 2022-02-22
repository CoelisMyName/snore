//
// File: vad_length_filter.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef VAD_LENGTH_FILTER_H
#define VAD_LENGTH_FILTER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void vad_length_filter(const coder::array<double, 2U> &starts,
                       const coder::array<double, 2U> &ends, double min_len,
                       double max_len, coder::array<double, 2U> &fstarts,
                       coder::array<double, 2U> &fends);

#endif
//
// File trailer for vad_length_filter.h
//
// [EOF]
//
