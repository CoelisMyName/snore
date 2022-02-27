//
// File: GMM_score.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef GMM_SCORE_H
#define GMM_SCORE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct SnoringRecognitionStackData;

// Function Declarations
double GMM_score(SnoringRecognitionStackData *SD,
                 const coder::array<double, 2U> &data_test);

#endif
//
// File trailer for GMM_score.h
//
// [EOF]
//
