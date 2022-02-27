//
// File: combineVectorElements.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "combineVectorElements.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
// Return Type  : int
//
namespace coder {
    int b_combineVectorElements(const ::coder::array<boolean_T, 2U> &x) {
        int vlen;
        int y;
        vlen = x.size(1);
        if (x.size(1) == 0) {
            y = 0;
        } else {
            y = x[0];
            for (int k = 2; k <= vlen; k++) {
                y += x[k - 1];
            }
        }
        return y;
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double y[17]
// Return Type  : void
//
    void combineVectorElements(const ::coder::array<double, 2U> &x, double y[17]) {
        if (x.size(0) == 0) {
            memset(&y[0], 0, 17U * sizeof(double));
        } else {
            int firstBlockLength;
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
            for (int xi = 0; xi < 17; xi++) {
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
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
    void combineVectorElements(const ::coder::array<double, 2U> &x,
                               ::coder::array<double, 2U> &y) {
        if ((x.size(0) == 0) || (x.size(1) == 0)) {
            int npages;
            y.set_size(1, x.size(1));
            npages = x.size(1);
            for (int firstBlockLength = 0; firstBlockLength < npages;
                 firstBlockLength++) {
                y[firstBlockLength] = 0.0;
            }
        } else {
            int firstBlockLength;
            int lastBlockLength;
            int nblocks;
            int npages;
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
    }

} // namespace coder

//
// File trailer for combineVectorElements.cpp
//
// [EOF]
//
