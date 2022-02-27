//
// File: classifier.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void classifier(const coder::array<double, 1U> &x, double fs,
                       const coder::array<long long, 1U> &w_starts,
                       const coder::array<long long, 1U> &w_ends,
                       coder::array<double, 1U> &predict_label);

#endif
//
// File trailer for classifier.h
//
// [EOF]
//
