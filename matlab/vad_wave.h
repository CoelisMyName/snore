//
// File: vad_wave.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef VAD_WAVE_H
#define VAD_WAVE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void vad_wave(const coder::array<double, 2U> &array,
              const coder::array<double, 2U> &s_starts,
              const coder::array<double, 2U> &s_ends,
              coder::array<double, 2U> &w_starts,
              coder::array<double, 2U> &w_ends);

#endif
//
// File trailer for vad_wave.h
//
// [EOF]
//
