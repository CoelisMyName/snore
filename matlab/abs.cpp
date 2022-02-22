//
// File: abs.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "abs.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace coder {
    void b_abs(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &y) {
        int nx;
        nx = x.size(0);
        y.set_size(x.size(0));
        for (int k = 0; k < nx; k++) {
            y[k] = fabs(x[k]);
        }
    }

//
// Arguments    : const ::coder::array<creal_T, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
    void b_abs(const ::coder::array<creal_T, 2U> &x, ::coder::array<double, 2U> &y) {
        int nx;
        nx = x.size(0) * x.size(1);
        y.set_size(x.size(0), x.size(1));
        for (int k = 0; k < nx; k++) {
            y[k] = rt_hypotd_snf(x[k].re, x[k].im);
        }
    }

//
// Arguments    : const ::coder::array<creal_T, 1U> &x
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
    void b_abs(const ::coder::array<creal_T, 1U> &x, ::coder::array<double, 1U> &y) {
        int nx;
        nx = x.size(0);
        y.set_size(x.size(0));
        for (int k = 0; k < nx; k++) {
            y[k] = rt_hypotd_snf(x[k].re, x[k].im);
        }
    }

//
// Arguments    : const double x[2]
//                double y[2]
// Return Type  : void
//
    void b_abs(const double x[2], double y[2]) {
        y[0] = fabs(x[0]);
        y[1] = fabs(x[1]);
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
    void b_abs(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y) {
        int nx;
        nx = x.size(1);
        y.set_size(1, x.size(1));
        for (int k = 0; k < nx; k++) {
            y[k] = fabs(x[k]);
        }
    }

//
// Arguments    : double x
// Return Type  : double
//
    double b_abs(double x) {
        return fabs(x);
    }

//
// Arguments    : const double x[4]
//                double y[4]
// Return Type  : void
//
    void c_abs(const double x[4], double y[4]) {
        y[0] = fabs(x[0]);
        y[1] = fabs(x[1]);
        y[2] = fabs(x[2]);
        y[3] = fabs(x[3]);
    }

} // namespace coder

//
// File trailer for abs.cpp
//
// [EOF]
//
