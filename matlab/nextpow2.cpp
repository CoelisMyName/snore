//
// File: nextpow2.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "nextpow2.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double n
// Return Type  : double
//
namespace coder {
    double nextpow2(double n) {
        double p;
        int eint;
        p = fabs(n);
        if ((!rtIsInf(p)) && (!rtIsNaN(p))) {
            double f;
            f = frexp(p, &eint);
            p = eint;
            if (f == 0.5) {
                p = static_cast<double>(eint) - 1.0;
            }
        }
        return p;
    }

} // namespace coder

//
// File trailer for nextpow2.cpp
//
// [EOF]
//
