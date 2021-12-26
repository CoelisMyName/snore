//
// File: vad.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef VAD_H
#define VAD_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void vad(coder::array<double, 2U> &x, double fs,
                coder::array<double, 2U> &w_starts,
                coder::array<double, 2U> &w_ends);

#endif
//
// File trailer for vad.h
//
// [EOF]
//
