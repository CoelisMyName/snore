//
// File: any1.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "any1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : boolean_T x
// Return Type  : boolean_T
//
namespace coder {
    boolean_T any(boolean_T x) {
        return x;
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : boolean_T
//
    boolean_T b_any(const ::coder::array<double, 1U> &x) {
        int ix;
        boolean_T exitg1;
        boolean_T y;
        y = false;
        ix = 0;
        exitg1 = false;
        while ((!exitg1) && (ix + 1 <= x.size(0))) {
            if ((x[ix] == 0.0) || rtIsNaN(x[ix])) {
                ix++;
            } else {
                y = true;
                exitg1 = true;
            }
        }
        return y;
    }

} // namespace coder

//
// File trailer for any1.cpp
//
// [EOF]
//
