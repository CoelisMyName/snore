//
// File: pitch_feat.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef PITCH_FEAT_H
#define PITCH_FEAT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void pitch_feat(const coder::array<double, 1U> &sig, double fs,
                       double *period_mean, double *period_min,
                       double *period_max, double *period_var);

#endif
//
// File trailer for pitch_feat.h
//
// [EOF]
//
