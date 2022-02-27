//
// File: bark_feat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "bark_feat.h"
#include "BARKenergy.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function barkee = bark_feat(sig, fs)
//
// Arguments    : const coder::array<double, 1U> &sig
//                double fs
//                double barkee[17]
// Return Type  : void
//
void bark_feat(const coder::array<double, 1U> &sig, double fs,
               double barkee[17]) {
    double a__1[17];
    double a__2[17];
    // 'bark_feat:2' [BARK1, ~, ~] = BARKenergy(sig, fs);
    BARKenergy(sig, fs, barkee, a__1, a__2);
    // 'bark_feat:3' barkee = BARK1';
}

//
// File trailer for bark_feat.cpp
//
// [EOF]
//
