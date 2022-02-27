//
// File: round.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "round.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : double *x
// Return Type  : void
//
namespace coder {
    void b_round(double *x) {
        *x = rt_roundd_snf(*x);
    }

} // namespace coder

//
// File trailer for round.cpp
//
// [EOF]
//
