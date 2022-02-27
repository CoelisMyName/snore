//
// File: xdlapy3.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "xdlapy3.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double x1
//                double x2
//                double x3
// Return Type  : double
//
namespace coder {
    namespace internal {
        double xdlapy3(double x1, double x2, double x3) {
            double a;
            double b;
            double c;
            double y;
            a = fabs(x1);
            b = fabs(x2);
            c = fabs(x3);
            if ((a > b) || rtIsNaN(b)) {
                y = a;
            } else {
                y = b;
            }
            if (c > y) {
                y = c;
            }
            if ((y > 0.0) && (!rtIsInf(y))) {
                a /= y;
                b /= y;
                c /= y;
                y *= sqrt((a * a + c * c) + b * b);
            } else {
                y = (a + b) + c;
            }
            return y;
        }

    } // namespace internal
} // namespace coder

//
// File trailer for xdlapy3.cpp
//
// [EOF]
//
