//
// File: fix.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "fix.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double *x
// Return Type  : void
//
namespace coder {
    void b_fix(double *x) {
        if (*x < 0.0) {
            *x = ceil(*x);
        } else {
            *x = floor(*x);
        }
    }

} // namespace coder

//
// File trailer for fix.cpp
//
// [EOF]
//
