#include "FeatureTimeZeroCrossingRate.h"
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

void FeatureTimeZeroCrossingRate(const coder::array<double, 1U> &x,
                                 double iBlockLength, double iHopLength,
                                 double f_s, coder::array<double, 2U> &vzc,
                                 coder::array<double, 2U> &t)
{
    coder::array<double, 2U> y;
    coder::array<double, 1U> b_x;
    coder::array<double, 1U> b_y1;
    double iNumOfBlocks;
    double work_data;
    int dimSize;
    int i;
    iNumOfBlocks = ceil(static_cast<double>(x.size(0)) / iHopLength);
    if (rtIsNaN(iNumOfBlocks - 1.0)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (iNumOfBlocks - 1.0 < 0.0) {
        y.set_size(1, 0);
    } else if (rtIsInf(iNumOfBlocks - 1.0) && (0.0 == iNumOfBlocks - 1.0)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else {
        y.set_size(1, static_cast<int>(iNumOfBlocks - 1.0) + 1);
        dimSize = static_cast<int>(iNumOfBlocks - 1.0);
        for (i = 0; i <= dimSize; i++) {
            y[i] = i;
        }
    }
    t.set_size(1, y.size(1));
    work_data = iBlockLength / 2.0;
    dimSize = y.size(1);
    for (i = 0; i < dimSize; i++) {
        t[i] = (y[i] * iHopLength + work_data) / f_s;
    }
    vzc.set_size(1, static_cast<int>(iNumOfBlocks));
    i = static_cast<int>(iNumOfBlocks);
    for (int n = 0; n < i; n++) {
        double i_start;
        double i_stop;
        int k;
        int nx;
        i_start = ((static_cast<double>(n) + 1.0) - 1.0) * iHopLength + 1.0;
        work_data = (i_start + iBlockLength) - 1.0;
        if ((x.size(0) < work_data) || rtIsNaN(work_data)) {
            i_stop = x.size(0);
        } else {
            i_stop = work_data;
        }
        if (i_start > i_stop) {
            nx = 1;
            k = 0;
        } else {
            nx = static_cast<int>(i_start);
            k = static_cast<int>(i_stop);
        }
        dimSize = k - nx;
        b_x.set_size(dimSize + 1);
        for (k = 0; k <= dimSize; k++) {
            b_x[k] = x[(nx + k) - 1];
        }
        for (k = 0; k <= dimSize; k++) {
            work_data = b_x[k];
            if (b_x[k] < 0.0) {
                work_data = -1.0;
            } else if (b_x[k] > 0.0) {
                work_data = 1.0;
            } else if (b_x[k] == 0.0) {
                work_data = 0.0;
            }
            b_x[k] = work_data;
        }
        dimSize = b_x.size(0);
        if (b_x.size(0) == 0) {
            b_y1.set_size(0);
        } else {
            nx = b_x.size(0) - 1;
            if (nx >= 1) {
                nx = 1;
            }
            if (nx < 1) {
                b_y1.set_size(0);
            } else {
                b_y1.set_size(b_x.size(0) - 1);
                if (b_x.size(0) - 1 != 0) {
                    work_data = b_x[0];
                    for (nx = 2; nx <= dimSize; nx++) {
                        double d;
                        double tmp1;
                        tmp1 = b_x[nx - 1];
                        d = tmp1;
                        tmp1 -= work_data;
                        work_data = d;
                        b_y1[nx - 2] = tmp1;
                    }
                }
            }
        }
        nx = b_y1.size(0);
        b_x.set_size(b_y1.size(0));
        for (k = 0; k < nx; k++) {
            b_x[k] = fabs(b_y1[k]);
        }
        vzc[n] = 0.5 * (coder::blockedSummation(b_x, b_x.size(0)) /
                        static_cast<double>(b_x.size(0)));
    }
}
