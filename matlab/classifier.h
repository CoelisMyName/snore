//
// File: classifier.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void classifier(const coder::array<double, 2U> &x,
                       const coder::array<double, 2U> &w_starts,
                       const coder::array<double, 2U> &w_ends, double fs,
                       coder::array<double, 2U> &predict_label);

#endif
//
// File trailer for classifier.h
//
// [EOF]
//
