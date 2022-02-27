//
// File: linspace.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "linspace.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double d2
//                double n
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
    void linspace(double d2, double n, ::coder::array<double, 2U> &y) {
        double delta1;
        delta1 = floor(n);
        y.set_size(1, static_cast<int>(delta1));
        if (static_cast<int>(delta1) >= 1) {
            int y_tmp;
            y_tmp = static_cast<int>(delta1) - 1;
            y[static_cast<int>(delta1) - 1] = d2;
            if (y.size(1) >= 2) {
                y[0] = 0.0;
                if (y.size(1) >= 3) {
                    if ((0.0 == -d2) && (static_cast<int>(delta1) > 2)) {
                        double d2scaled;
                        d2scaled =
                                d2 /
                                (static_cast<double>(static_cast<int>(delta1)) - 1.0);
                        for (int k = 2; k <= y_tmp; k++) {
                            y[k - 1] =
                                    static_cast<double>(
                                            ((k << 1) - static_cast<int>(delta1)) - 1) *
                                    d2scaled;
                        }
                        if ((static_cast<int>(delta1) & 1) == 1) {
                            y[static_cast<int>(delta1) >> 1] = 0.0;
                        }
                    } else if ((d2 < 0.0) && (fabs(d2) > 8.9884656743115785E+307)) {
                        delta1 = d2 / (static_cast<double>(y.size(1)) - 1.0);
                        y_tmp = y.size(1);
                        for (int k = 0; k <= y_tmp - 3; k++) {
                            y[k + 1] = delta1 * (static_cast<double>(k) + 1.0);
                        }
                    } else {
                        delta1 = d2 / (static_cast<double>(y.size(1)) - 1.0);
                        y_tmp = y.size(1);
                        for (int k = 0; k <= y_tmp - 3; k++) {
                            y[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
                        }
                    }
                }
            }
        }
    }

} // namespace coder

//
// File trailer for linspace.cpp
//
// [EOF]
//
