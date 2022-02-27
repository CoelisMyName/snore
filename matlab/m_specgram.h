//
// File: m_specgram.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef M_SPECGRAM_H
#define M_SPECGRAM_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void m_specgram(coder::array<double, 1U> &x, double nfft,
                const coder::array<double, 2U> &window, double noverlap,
                coder::array<creal_T, 2U> &yo);

#endif
//
// File trailer for m_specgram.h
//
// [EOF]
//
