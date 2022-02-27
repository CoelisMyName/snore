//
// File: diff.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "diff.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace coder {
    void diff(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &y) {
        int dimSize;
        dimSize = x.size(0);
        if (x.size(0) == 0) {
            y.set_size(0);
        } else {
            int u0;
            u0 = x.size(0) - 1;
            if (u0 >= 1) {
                u0 = 1;
            }
            if (u0 < 1) {
                y.set_size(0);
            } else {
                y.set_size(x.size(0) - 1);
                if (x.size(0) - 1 != 0) {
                    double work_data;
                    work_data = x[0];
                    for (u0 = 2; u0 <= dimSize; u0++) {
                        double d;
                        double tmp1;
                        tmp1 = x[u0 - 1];
                        d = tmp1;
                        tmp1 -= work_data;
                        work_data = d;
                        y[u0 - 2] = tmp1;
                    }
                }
            }
        }
    }

} // namespace coder

//
// File trailer for diff.cpp
//
// [EOF]
//
