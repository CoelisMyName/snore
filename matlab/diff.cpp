//
// File: diff.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
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
        array<double, 1U> work;
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
                work.set_size(1);
                y.set_size(x.size(0) - 1);
                if (x.size(0) - 1 != 0) {
                    work[0] = x[0];
                    for (u0 = 2; u0 <= dimSize; u0++) {
                        double tmp1;
                        tmp1 = x[u0 - 1];
                        for (int k = 0; k < 1; k++) {
                            double tmp2;
                            tmp2 = work[0];
                            work[0] = tmp1;
                            tmp1 -= tmp2;
                        }
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
