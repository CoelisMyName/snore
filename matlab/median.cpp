//
// File: median.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "median.h"
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const double x[10]
// Return Type  : double
//
namespace coder {
    double median(const double x[10]) {
        double v[10];
        double b;
        double y;
        int a__3;
        int ilast;
        int k;
        k = 0;
        int exitg1;
        do {
            exitg1 = 0;
            if (k < 10) {
                if (rtIsNaN(x[k])) {
                    y = rtNaN;
                    exitg1 = 1;
                } else {
                    k++;
                }
            } else {
                memcpy(&v[0], &x[0], 10U * sizeof(double));
                internal::quickselect(v, 6, 10, &y, &k, &ilast);
                if (5 < k) {
                    internal::quickselect(v, 5, ilast - 1, &b, &k, &a__3);
                    if (((y < 0.0) != (b < 0.0)) || rtIsInf(y)) {
                        y = (y + b) / 2.0;
                    } else {
                        y += (b - y) / 2.0;
                    }
                }
                exitg1 = 1;
            }
        } while (exitg1 == 0);
        return y;
    }

} // namespace coder

//
// File trailer for median.cpp
//
// [EOF]
//
