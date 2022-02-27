//
// File: vvarstd.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "vvarstd.h"
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &v
//                int n
// Return Type  : double
//
namespace coder {
    double vvarstd(const ::coder::array<double, 1U> &v, int n) {
        double s;
        if (n == 0) {
            s = rtNaN;
        } else if (n == 1) {
            if ((!rtIsInf(v[0])) && (!rtIsNaN(v[0]))) {
                s = 0.0;
            } else {
                s = rtNaN;
            }
        } else {
            double xbar;
            xbar = blockedSummation(v, n) / static_cast<double>(n);
            s = 0.0;
            for (int k = 0; k < n; k++) {
                double t;
                t = v[k] - xbar;
                s += t * t;
            }
            s /= static_cast<double>(n - 1);
        }
        return s;
    }

} // namespace coder

//
// File trailer for vvarstd.cpp
//
// [EOF]
//
