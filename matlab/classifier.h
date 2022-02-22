//
// File: classifier.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

// Include Files
#include "SnoringRecognition_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void classifier(SnoringRecognitionStackData *SD,
                       const coder::array<double, 2U> &x,
                       const coder::array<double, 2U> &w_starts,
                       const coder::array<double, 2U> &w_ends, double fs,
                       coder::array<double, 2U> &predict_label);

#endif
//
// File trailer for classifier.h
//
// [EOF]
//
