//
// File: SnoringRecognition_initialize.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "SnoringRecognition_initialize.h"
#include "SnoringRecognition_data.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void SnoringRecognition_initialize()
{
  omp_init_nest_lock(&emlrtNestLockGlobal);
  isInitialized_SnoringRecognition = true;
}

//
// File trailer for SnoringRecognition_initialize.cpp
//
// [EOF]
//
