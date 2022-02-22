//
// File: sum.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "sum.h"
#include "blockedSummation.h"
#include "combineVectorElements.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const double x[17]
// Return Type  : double
//
namespace coder {
    double b_sum(const double x[17]) {
        double y;
        y = x[0];
        for (int k = 0; k < 16; k++) {
            y += x[k + 1];
        }
        return y;
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double y[17]
// Return Type  : void
//
    void sum(const ::coder::array<double, 2U> &x, double y[17]) {
        combineVectorElements(x, y);
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
    double sum(const ::coder::array<double, 1U> &x) {
        return blockedSummation(x, x.size(0));
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
    double sum(const ::coder::array<double, 2U> &x) {
        return combineVectorElements(x);
    }

//
// Arguments    : const double x[8]
// Return Type  : double
//
    double sum(const double x[8]) {
        double y;
        y = x[0];
        for (int k = 0; k < 7; k++) {
            y += x[k + 1];
        }
        return y;
    }

} // namespace coder

//
// File trailer for sum.cpp
//
// [EOF]
//
