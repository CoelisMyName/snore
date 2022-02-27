//
// File: fmt_feat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "fmt_feat.h"
#include "formantfeature.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [Formant1, Formant2, Formant3] = fmt_feat(sig, fs)
//
// Arguments    : const coder::array<double, 1U> &sig
//                double fs
//                double *Formant1
//                double *Formant2
//                double *Formant3
// Return Type  : void
//
void fmt_feat(const coder::array<double, 1U> &sig, double fs, double *Formant1,
              double *Formant2, double *Formant3) {
    // 'fmt_feat:2' [Formant1, Formant2, Formant3] = formantfeature(sig, fs);
    formantfeature(sig, fs, Formant1, Formant2, Formant3);
}

//
// File trailer for fmt_feat.cpp
//
// [EOF]
//
