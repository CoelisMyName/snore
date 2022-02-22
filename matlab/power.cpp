//
// File: power.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "power.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &a
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace coder {
    void power(const ::coder::array<double, 1U> &a, ::coder::array<double, 1U> &y) {
        int nx;
        y.set_size(a.size(0));
        nx = a.size(0);
        for (int k = 0; k < nx; k++) {
            y[k] = a[k] * a[k];
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
    void power(const ::coder::array<double, 2U> &a, ::coder::array<double, 2U> &y) {
        int nx;
        y.set_size(1, a.size(1));
        nx = a.size(1);
        for (int k = 0; k < nx; k++) {
            double d;
            d = a[k];
            y[k] = d * d;
        }
    }

//
// Arguments    : double a
//                const double b[8]
//                double y[8]
// Return Type  : void
//
    void power(double a, const double b[8], double y[8]) {
        for (int k = 0; k < 8; k++) {
            y[k] = rt_powd_snf(a, b[k]);
        }
    }

} // namespace coder

//
// File trailer for power.cpp
//
// [EOF]
//
