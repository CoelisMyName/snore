//
// File: vad_wave.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef VAD_WAVE_H
#define VAD_WAVE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void vad_wave(const coder::array<double, 1U> &array,
              const coder::array<long long, 1U> &starts,
              const coder::array<long long, 1U> &ends,
              coder::array<long long, 1U> &ostarts,
              coder::array<long long, 1U> &oends);

#endif
//
// File trailer for vad_wave.h
//
// [EOF]
//
