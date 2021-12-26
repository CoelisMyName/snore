//
// File: mfcc_m.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef MFCC_M_H
#define MFCC_M_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void mfcc_m(const coder::array<double, 1U> &x, double fs, double frameSize,
            double inc, coder::array<double, 2U> &ccc);

#endif
//
// File trailer for mfcc_m.h
//
// [EOF]
//
