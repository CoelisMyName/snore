//
// File: asinh1.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "asinh1.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double *x
// Return Type  : void
//
namespace coder {
    namespace internal {
        namespace scalar {
            void c_asinh(double *x) {
                boolean_T xneg;
                xneg = (*x < 0.0);
                if (xneg) {
                    *x = -*x;
                }
                if (*x >= 2.68435456E+8) {
                    *x = log(*x) + 0.69314718055994529;
                } else if (*x > 2.0) {
                    *x = log(2.0 * *x + 1.0 / (sqrt(*x * *x + 1.0) + *x));
                } else {
                    double t;
                    t = *x * *x;
                    *x += t / (sqrt(t + 1.0) + 1.0);
                    t = fabs(*x);
                    if ((t > 4.503599627370496E+15) || (rtIsInf(*x) || rtIsNaN(*x))) {
                        (*x)++;
                        *x = log(*x);
                    } else if (!(t < 2.2204460492503131E-16)) {
                        *x = log(*x + 1.0) * (*x / ((*x + 1.0) - 1.0));
                    }
                }
                if (xneg) {
                    *x = -*x;
                }
            }

        } // namespace scalar
    } // namespace internal
} // namespace coder

//
// File trailer for asinh1.cpp
//
// [EOF]
//
