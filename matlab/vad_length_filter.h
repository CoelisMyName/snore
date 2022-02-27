//
// File: vad_length_filter.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef VAD_LENGTH_FILTER_H
#define VAD_LENGTH_FILTER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void vad_length_filter(const coder::array<long long, 1U> &starts,
                       const coder::array<long long, 1U> &ends, double min_len,
                       double max_len, coder::array<long long, 1U> &ostarts,
                       coder::array<long long, 1U> &oends);

#endif
//
// File trailer for vad_length_filter.h
//
// [EOF]
//
