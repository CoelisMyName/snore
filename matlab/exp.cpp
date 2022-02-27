//
// File: exp.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "exp.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : ::coder::array<creal_T, 2U> &x
// Return Type  : void
//
namespace coder {
    void b_exp(::coder::array<creal_T, 2U> &x) {
        int nx;
        nx = x.size(0) * 13;
        for (int k = 0; k < nx; k++) {
            if (x[k].im == 0.0) {
                x[k].re = exp(x[k].re);
                x[k].im = 0.0;
            } else if (rtIsInf(x[k].im) && rtIsInf(x[k].re) && (x[k].re < 0.0)) {
                x[k].re = 0.0;
                x[k].im = 0.0;
            } else {
                double d;
                double r;
                r = exp(x[k].re / 2.0);
                d = x[k].im;
                x[k].re = r * (r * cos(x[k].im));
                x[k].im = r * (r * sin(d));
            }
        }
    }

//
// Arguments    : double x[4]
// Return Type  : void
//
    void b_exp(double x[4]) {
        x[0] = exp(x[0]);
        x[1] = exp(x[1]);
        x[2] = exp(x[2]);
        x[3] = exp(x[3]);
    }

//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
    void b_exp(::coder::array<double, 2U> &x) {
        int nx;
        nx = 31 * x.size(1);
        for (int k = 0; k < nx; k++) {
            x[k] = exp(x[k]);
        }
    }

} // namespace coder

//
// File trailer for exp.cpp
//
// [EOF]
//
