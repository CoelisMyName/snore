//
// File: patient_classifier.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef PATIENT_CLASSIFIER_H
#define PATIENT_CLASSIFIER_H

// Include Files
#include "SnoringRecognition_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern double patient_classifier(SnoringRecognitionStackData *SD,
                                 const coder::array<double, 2U> &MFCC_feature,
                                 const coder::array<double, 2U> &BARKEE,
                                 const coder::array<double, 1U> &period_mean,
                                 const coder::array<double, 1U> &period_max,
                                 const coder::array<double, 1U> &period_min,
                                 const coder::array<double, 1U> &period_var,
                                 const coder::array<double, 2U> &cep,
                                 const coder::array<double, 1U> &Formant1,
                                 const coder::array<double, 1U> &Formant2,
                                 const coder::array<double, 1U> &Formant3,
                                 const coder::array<double, 2U> &GTCCmean,
                                 const coder::array<double, 1U> &PR800mean,
                                 const coder::array<double, 1U> &PR800max,
                                 const coder::array<double, 1U> &PR800min,
                                 const coder::array<double, 1U> &PR800var,
                                 const coder::array<double, 1U> &SE_mean,
                                 const coder::array<double, 1U> &SE_max,
                                 const coder::array<double, 1U> &SE_min,
                                 const coder::array<double, 1U> &SE_var);

#endif
//
// File trailer for patient_classifier.h
//
// [EOF]
//
