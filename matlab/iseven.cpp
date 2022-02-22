//
// File: iseven.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "iseven.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double x
// Return Type  : boolean_T
//
namespace coder {
    boolean_T iseven(double x) {
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
        return r == 0.0;
    }

} // namespace coder

//
// File trailer for iseven.cpp
//
// [EOF]
//
