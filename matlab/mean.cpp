//
// File: mean.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
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
// Arguments    : const ::coder::array<double, 2U> &x
//                double y_data[]
//                int *y_size
// Return Type  : void
//
namespace coder {
    void mean(const ::coder::array<double, 2U> &x, double y_data[], int *y_size) {
        double bsum_data[39];
        int firstBlockLength;
        if ((x.size(0) == 0) || (x.size(1) == 0)) {
            *y_size = x.size(0);
            firstBlockLength = x.size(0);
            if (0 <= firstBlockLength - 1) {
                memset(&y_data[0], 0, firstBlockLength * sizeof(double));
            }
        } else {
            int bvstride;
            int k;
            int lastBlockLength;
            int nblocks;
            int vstride;
            int xj;
            int xoffset;
            vstride = x.size(0) - 1;
            bvstride = x.size(0) << 10;
            *y_size = x.size(0);
            if (x.size(1) <= 1024) {
                firstBlockLength = x.size(1);
                lastBlockLength = 0;
                nblocks = 1;
            } else {
                firstBlockLength = 1024;
                nblocks = x.size(1) / 1024;
                lastBlockLength = x.size(1) - (nblocks << 10);
                if (lastBlockLength > 0) {
                    nblocks++;
                } else {
                    lastBlockLength = 1024;
                }
            }
            for (xj = 0; xj <= vstride; xj++) {
                y_data[xj] = x[xj];
                bsum_data[xj] = 0.0;
            }
            for (k = 2; k <= firstBlockLength; k++) {
                xoffset = (k - 1) * (vstride + 1);
                for (xj = 0; xj <= vstride; xj++) {
                    y_data[xj] += x[xoffset + xj];
                }
            }
            for (int ib = 2; ib <= nblocks; ib++) {
                int hi;
                firstBlockLength = (ib - 1) * bvstride;
                for (xj = 0; xj <= vstride; xj++) {
                    bsum_data[xj] = x[firstBlockLength + xj];
                }
                if (ib == nblocks) {
                    hi = lastBlockLength;
                } else {
                    hi = 1024;
                }
                for (k = 2; k <= hi; k++) {
                    xoffset = firstBlockLength + (k - 1) * (vstride + 1);
                    for (xj = 0; xj <= vstride; xj++) {
                        bsum_data[xj] += x[xoffset + xj];
                    }
                }
                for (xj = 0; xj <= vstride; xj++) {
                    y_data[xj] += bsum_data[xj];
                }
            }
        }
        for (firstBlockLength = 0; firstBlockLength < *y_size; firstBlockLength++) {
            y_data[firstBlockLength] /= static_cast<double>(x.size(1));
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
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
    void mean(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y) {
        int loop_ub;
        combineVectorElements(x, y);
        y.set_size(1, y.size(1));
        loop_ub = y.size(1) - 1;
        for (int i = 0; i <= loop_ub; i++) {
            y[i] = y[i] / static_cast<double>(x.size(0));
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
    double mean(const ::coder::array<double, 2U> &x) {
        double y;
        if (x.size(1) == 0) {
            y = 0.0;
        } else {
            int firstBlockLength;
            int k;
            int lastBlockLength;
            int nblocks;
            if (x.size(1) <= 1024) {
                firstBlockLength = x.size(1);
                lastBlockLength = 0;
                nblocks = 1;
            } else {
                firstBlockLength = 1024;
                nblocks = x.size(1) / 1024;
                lastBlockLength = x.size(1) - (nblocks << 10);
                if (lastBlockLength > 0) {
                    nblocks++;
                } else {
                    lastBlockLength = 1024;
                }
            }
            y = x[0];
            for (k = 2; k <= firstBlockLength; k++) {
                y += x[k - 1];
            }
            for (int ib = 2; ib <= nblocks; ib++) {
                double bsum;
                int hi;
                firstBlockLength = (ib - 1) << 10;
                bsum = x[firstBlockLength];
                if (ib == nblocks) {
                    hi = lastBlockLength;
                } else {
                    hi = 1024;
                }
                for (k = 2; k <= hi; k++) {
                    bsum += x[(firstBlockLength + k) - 1];
                }
                y += bsum;
            }
        }
        y /= static_cast<double>(x.size(1));
        return y;
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
    double mean(const ::coder::array<double, 1U> &x) {
        return blockedSummation(x, x.size(0)) / static_cast<double>(x.size(0));
    }

} // namespace coder

//
// File trailer for mean.cpp
//
// [EOF]
//
