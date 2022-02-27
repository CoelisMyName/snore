//
// File: pr800_feat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "pr800_feat.h"
#include "PR800.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [PR800_mean, PR800_max, PR800_min, PR800_var] = pr800_feat(sig, fs)
//
// Arguments    : const coder::array<double, 1U> &sig
//                double fs
//                double *PR800_mean
//                double *PR800_max
//                double *PR800_min
//                double *PR800_var
// Return Type  : void
//
void pr800_feat(const coder::array<double, 1U> &sig, double fs,
                double *PR800_mean, double *PR800_max, double *PR800_min,
                double *PR800_var) {
    // 'pr800_feat:2' [PR800_mean, PR800_max, PR800_min, PR800_var] = PR800(sig,
    // fs);
    PR800(sig, fs, PR800_mean, PR800_max, PR800_min, PR800_var);
}

//
// File trailer for pr800_feat.cpp
//
// [EOF]
//
