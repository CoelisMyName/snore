//
// File: floor.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "floor.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
namespace coder {
    void b_floor(::coder::array<double, 2U> &x) {
        int nx;
        nx = x.size(1);
        for (int k = 0; k < nx; k++) {
            x[k] = floor(x[k]);
        }
    }

//
// Arguments    : double *x
// Return Type  : void
//
    void b_floor(double *x) {
        *x = floor(*x);
    }

} // namespace coder

//
// File trailer for floor.cpp
//
// [EOF]
//
