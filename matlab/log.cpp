//
// File: log.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "log.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &x
// Return Type  : void
//
namespace coder {
    void b_log(::coder::array<double, 1U> &x) {
        int nx;
        nx = x.size(0);
        for (int k = 0; k < nx; k++) {
            x[k] = log(x[k]);
        }
    }

//
// Arguments    : double *x
// Return Type  : void
//
    void b_log(double *x) {
        *x = log(*x);
    }

//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
    void b_log(::coder::array<double, 2U> &x) {
        int nx;
        nx = x.size(1);
        for (int k = 0; k < nx; k++) {
            x[k] = log(x[k]);
        }
    }

//
// Arguments    : double x[2]
// Return Type  : void
//
    void c_log(double x[2]) {
        x[0] = log(x[0]);
        x[1] = log(x[1]);
    }

//
// Arguments    : double x[4160]
// Return Type  : void
//
    void d_log(double x[4160]) {
        for (int k = 0; k < 4160; k++) {
            x[k] = log(x[k]);
        }
    }

//
// Arguments    : double x[32]
// Return Type  : void
//
    void e_log(double x[32]) {
        for (int k = 0; k < 32; k++) {
            x[k] = log(x[k]);
        }
    }

} // namespace coder

//
// File trailer for log.cpp
//
// [EOF]
//
