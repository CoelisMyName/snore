//
// File: rms.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "rms.h"
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
namespace coder {
    double rms(const ::coder::array<double, 1U> &x) {
        array<double, 1U> b_x;
        int loop_ub;
        b_x.set_size(x.size(0));
        loop_ub = x.size(0);
        for (int i = 0; i < loop_ub; i++) {
            b_x[i] = x[i] * x[i];
        }
        return sqrt(blockedSummation(b_x, b_x.size(0)) /
                    static_cast<double>(b_x.size(0)));
    }

} // namespace coder

//
// File trailer for rms.cpp
//
// [EOF]
//
