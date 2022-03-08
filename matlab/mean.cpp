#include "mean.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include <string.h>

namespace coder {
void mean(const ::coder::array<double, 2U> &x, double y_data[], int *y_size)
{
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

double mean(const ::coder::array<double, 2U> &x)
{
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

} // namespace coder
