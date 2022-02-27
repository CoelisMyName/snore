//
// File: mod.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "mod.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double x
// Return Type  : double
//
namespace coder {
    double b_mod(double x) {
        double r;
        if (rtIsNaN(x) || rtIsInf(x)) {
            r = rtNaN;
        } else if (x == 0.0) {
            r = 0.0;
        } else {
            r = fmod(x, 2.0);
            if (r == 0.0) {
                r = 0.0;
            } else if (x < 0.0) {
                r += 2.0;
            }
        }
        return r;
    }

} // namespace coder

//
// File trailer for mod.cpp
//
// [EOF]
//
