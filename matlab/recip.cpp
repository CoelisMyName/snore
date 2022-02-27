//
// File: recip.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "recip.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const creal_T y
// Return Type  : creal_T
//
namespace coder {
    namespace internal {
        creal_T recip(const creal_T y) {
            creal_T z;
            double bim;
            double brm;
            brm = fabs(y.re);
            bim = fabs(y.im);
            if (y.im == 0.0) {
                z.re = 1.0 / y.re;
                z.im = 0.0;
            } else if (y.re == 0.0) {
                z.re = 0.0;
                z.im = -1.0 / y.im;
            } else if (brm > bim) {
                double d;
                bim = y.im / y.re;
                d = y.re + bim * y.im;
                z.re = 1.0 / d;
                z.im = -bim / d;
            } else if (brm == bim) {
                double d;
                bim = 0.5;
                if (y.re < 0.0) {
                    bim = -0.5;
                }
                d = 0.5;
                if (y.im < 0.0) {
                    d = -0.5;
                }
                z.re = bim / brm;
                z.im = -d / brm;
            } else {
                double d;
                bim = y.re / y.im;
                d = y.im + bim * y.re;
                z.re = bim / d;
                z.im = -1.0 / d;
            }
            return z;
        }

    } // namespace internal
} // namespace coder

//
// File trailer for recip.cpp
//
// [EOF]
//
