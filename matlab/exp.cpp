//
// File: exp.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "exp.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double x[4]
// Return Type  : void
//
namespace coder {
    void b_exp(double x[4]) {
        x[0] = exp(x[0]);
        x[1] = exp(x[1]);
        x[2] = exp(x[2]);
        x[3] = exp(x[3]);
    }

} // namespace coder

//
// File trailer for exp.cpp
//
// [EOF]
//
