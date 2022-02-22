//
// File: SnoringRecognition_initialize.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "SnoringRecognition_initialize.h"
#include "SnoringRecognition_types.h"
#include "frq2mel.h"
#include "mel2frq.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : SnoringRecognitionStackData *SD
// Return Type  : void
//
void SnoringRecognition_initialize(SnoringRecognitionStackData *SD) {
    rt_InitInfAndNaN();
    frq2mel_init(SD);
    mel2frq_init(SD);
}

//
// File trailer for SnoringRecognition_initialize.cpp
//
// [EOF]
//
