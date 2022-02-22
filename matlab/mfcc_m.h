//
// File: mfcc_m.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef MFCC_M_H
#define MFCC_M_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct SnoringRecognitionStackData;

// Function Declarations
void mfcc_m(SnoringRecognitionStackData *SD, const coder::array<double, 1U> &x,
            double fs, double frameSize, double inc,
            coder::array<double, 2U> &ccc);

#endif
//
// File trailer for mfcc_m.h
//
// [EOF]
//
