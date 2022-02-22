//
// File: mean.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "mean.h"
#include "blockedSummation.h"
#include "combineVectorElements.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
namespace coder {
    double mean(const ::coder::array<double, 1U> &x) {
        return blockedSummation(x, x.size(0)) / static_cast<double>(x.size(0));
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
    void mean(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y) {
        int firstBlockLength;
        int npages;
        if ((x.size(0) == 0) || (x.size(1) == 0)) {
            y.set_size(1, x.size(1));
            npages = x.size(1);
            for (firstBlockLength = 0; firstBlockLength < npages; firstBlockLength++) {
                y[firstBlockLength] = 0.0;
            }
        } else {
            int lastBlockLength;
            int nblocks;
            npages = x.size(1);
            y.set_size(1, x.size(1));
            if (x.size(0) <= 1024) {
                firstBlockLength = x.size(0);
                lastBlockLength = 0;
                nblocks = 1;
            } else {
                firstBlockLength = 1024;
                nblocks = x.size(0) / 1024;
                lastBlockLength = x.size(0) - (nblocks << 10);
                if (lastBlockLength > 0) {
                    nblocks++;
                } else {
                    lastBlockLength = 1024;
                }
            }
            for (int xi = 0; xi < npages; xi++) {
                int k;
                int xpageoffset;
                xpageoffset = xi * x.size(0);
                y[xi] = x[xpageoffset];
                for (k = 2; k <= firstBlockLength; k++) {
                    y[xi] = y[xi] + x[(xpageoffset + k) - 1];
                }
                for (int ib = 2; ib <= nblocks; ib++) {
                    double bsum;
                    int hi;
                    int xblockoffset;
                    xblockoffset = xpageoffset + ((ib - 1) << 10);
                    bsum = x[xblockoffset];
                    if (ib == nblocks) {
                        hi = lastBlockLength;
                    } else {
                        hi = 1024;
                    }
                    for (k = 2; k <= hi; k++) {
                        bsum += x[(xblockoffset + k) - 1];
                    }
                    y[xi] = y[xi] + bsum;
                }
            }
        }
        y.set_size(1, y.size(1));
        npages = y.size(1) - 1;
        for (firstBlockLength = 0; firstBlockLength <= npages; firstBlockLength++) {
            y[firstBlockLength] = y[firstBlockLength] / static_cast<double>(x.size(0));
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double y[12]
// Return Type  : void
//
    void mean(const ::coder::array<double, 2U> &x, double y[12]) {
        int firstBlockLength;
        if (x.size(0) == 0) {
            memset(&y[0], 0, 12U * sizeof(double));
        } else {
            int lastBlockLength;
            int nblocks;
            if (x.size(0) <= 1024) {
                firstBlockLength = x.size(0);
                lastBlockLength = 0;
                nblocks = 1;
            } else {
                firstBlockLength = 1024;
                nblocks = x.size(0) / 1024;
                lastBlockLength = x.size(0) - (nblocks << 10);
                if (lastBlockLength > 0) {
                    nblocks++;
                } else {
                    lastBlockLength = 1024;
                }
            }
            for (int xi = 0; xi < 12; xi++) {
                int k;
                int xpageoffset;
                xpageoffset = xi * x.size(0);
                y[xi] = x[xpageoffset];
                for (k = 2; k <= firstBlockLength; k++) {
                    y[xi] += x[(xpageoffset + k) - 1];
                }
                for (int ib = 2; ib <= nblocks; ib++) {
                    double bsum;
                    int hi;
                    int xblockoffset;
                    xblockoffset = xpageoffset + ((ib - 1) << 10);
                    bsum = x[xblockoffset];
                    if (ib == nblocks) {
                        hi = lastBlockLength;
                    } else {
                        hi = 1024;
                    }
                    for (k = 2; k <= hi; k++) {
                        bsum += x[(xblockoffset + k) - 1];
                    }
                    y[xi] += bsum;
                }
            }
        }
        for (firstBlockLength = 0; firstBlockLength < 12; firstBlockLength++) {
            y[firstBlockLength] /= static_cast<double>(x.size(0));
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
    double mean(const ::coder::array<double, 2U> &x) {
        return combineVectorElements(x) / static_cast<double>(x.size(1));
    }

} // namespace coder

//
// File trailer for mean.cpp
//
// [EOF]
//
