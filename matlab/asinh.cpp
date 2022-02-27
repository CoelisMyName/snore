//
// File: asinh.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "asinh.h"
#include "asinh1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
namespace coder {
    void b_asinh(::coder::array<double, 2U> &x) {
        int nx;
        nx = x.size(1);
        for (int k = 0; k < nx; k++) {
            internal::scalar::c_asinh(&x[k]);
        }
    }

//
// Arguments    : double *x
// Return Type  : void
//
    void b_asinh(double *x) {
        internal::scalar::c_asinh(x);
    }

} // namespace coder

//
// File trailer for asinh.cpp
//
// [EOF]
//
