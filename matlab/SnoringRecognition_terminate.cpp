//
// File: SnoringRecognition_terminate.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "SnoringRecognition_terminate.h"
#include "SnoringRecognition_data.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void SnoringRecognition_terminate()
{
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
  isInitialized_SnoringRecognition = false;
}

//
// File trailer for SnoringRecognition_terminate.cpp
//
// [EOF]
//
