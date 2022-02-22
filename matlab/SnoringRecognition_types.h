//
// File: SnoringRecognition_types.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef SNORINGRECOGNITION_TYPES_H
#define SNORINGRECOGNITION_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct SnoringRecognitionPersistentData {
    double k;
    double b_k;
};

struct SnoringRecognitionStackData {
    SnoringRecognitionPersistentData *pd;
};

#endif
//
// File trailer for SnoringRecognition_types.h
//
// [EOF]
//
