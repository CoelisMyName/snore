//
// File: cos.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "cos.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double x[16]
// Return Type  : void
//
namespace coder {
    void b_cos(double x[16]) {
        for (int k = 0; k < 16; k++) {
            x[k] = cos(x[k]);
        }
    }

//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
    void b_cos(::coder::array<double, 2U> &x) {
        int nx;
        nx = x.size(1);
        for (int k = 0; k < nx; k++) {
            x[k] = cos(x[k]);
        }
    }

} // namespace coder

//
// File trailer for cos.cpp
//
// [EOF]
//
