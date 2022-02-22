//
// File: frq2mel.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef FRQ2MEL_H
#define FRQ2MEL_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct SnoringRecognitionStackData;

// Function Declarations
void frq2mel(SnoringRecognitionStackData *SD,
             const coder::array<double, 2U> &frq,
             coder::array<double, 2U> &mel);

void frq2mel(SnoringRecognitionStackData *SD, const double frq[2],
             double mel[2]);

void frq2mel_init(SnoringRecognitionStackData *SD);

#endif
//
// File trailer for frq2mel.h
//
// [EOF]
//
