//
// File: LPCFeature.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef LPCFEATURE_H
#define LPCFEATURE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void LPCFeature(const coder::array<double, 1U> &x, double Fs,
                coder::array<double, 2U> &LPC, double LPC_mean[12],
                double LPC_max[12], double LPC_min[12], double LPC_var[12]);

#endif
//
// File trailer for LPCFeature.h
//
// [EOF]
//
