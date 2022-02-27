//
// File: sum.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
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
// Arguments    : const double x[4160]
//                double y[32]
// Return Type  : void
//
    void sum(const double x[4160], double y[32]) {
        for (int xi = 0; xi < 32; xi++) {
            double d;
            int xpageoffset;
            xpageoffset = xi * 130;
            d = x[xpageoffset];
            for (int k = 0; k < 129; k++) {
                d += x[(xpageoffset + k) + 1];
            }
            y[xi] = d;
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
    void sum(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y) {
        if (x.size(1) == 0) {
            y.set_size(1, 0);
        } else {
            int npages;
            npages = x.size(1);
            y.set_size(1, x.size(1));
            for (int xi = 0; xi < npages; xi++) {
                double d;
                int xpageoffset;
                xpageoffset = xi * 31;
                d = x[xpageoffset];
                for (int k = 0; k < 30; k++) {
                    d += x[(xpageoffset + k) + 1];
                }
                y[xi] = d;
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
    double sum(const ::coder::array<double, 1U> &x) {
        return blockedSummation(x, x.size(0));
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
