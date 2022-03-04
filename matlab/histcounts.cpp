#include "histcounts.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

namespace coder {
void histcounts(const ::coder::array<double, 1U> &x, double n_data[],
                int n_size[2], double edges_data[], int edges_size[2])
{
    double HighLimit;
    double LowLimit;
    double binWidth;
    double epsxScale;
    double leftEdge;
    double xScale;
    int ni_data[20];
    int high_i;
    int i;
    int k;
    int low_i;
    int low_ip1;
    int mid_i;
    int nx;
    nx = x.size(0);
    k = 0;
    while ((k + 1 <= nx) && (rtIsInf(x[k]) || rtIsNaN(x[k]))) {
        k++;
    }
    if (k + 1 > x.size(0)) {
        LowLimit = 0.0;
        low_i = 0;
    } else {
        LowLimit = x[k];
        low_i = 1;
    }
    HighLimit = LowLimit;
    i = k + 2;
    for (low_ip1 = i; low_ip1 <= nx; low_ip1++) {
        epsxScale = x[low_ip1 - 1];
        if ((!rtIsInf(epsxScale)) && (!rtIsNaN(epsxScale))) {
            if (epsxScale < LowLimit) {
                LowLimit = epsxScale;
            } else if (epsxScale > HighLimit) {
                HighLimit = epsxScale;
            }
            low_i++;
        }
    }
    binWidth = HighLimit - LowLimit;
    leftEdge = binWidth / 20.0;
    if (low_i > 0) {
        double u0;
        boolean_T b;
        boolean_T b1;
        u0 = fabs(LowLimit);
        epsxScale = fabs(HighLimit);
        if ((u0 > epsxScale) || rtIsNaN(epsxScale)) {
            xScale = u0;
        } else {
            xScale = epsxScale;
        }
        b = !rtIsInf(xScale);
        b1 = !rtIsNaN(xScale);
        if (b && b1) {
            if (xScale <= 2.2250738585072014E-308) {
                epsxScale = 4.94065645841247E-324;
            } else {
                frexp(xScale, &high_i);
                epsxScale = ldexp(1.0, high_i - 53);
            }
        } else {
            epsxScale = rtNaN;
        }
        if ((!(leftEdge > epsxScale)) && (!rtIsNaN(epsxScale))) {
            leftEdge = epsxScale;
        }
        u0 = sqrt(epsxScale);
        if (!(u0 > 2.2250738585072014E-308)) {
            u0 = 2.2250738585072014E-308;
        }
        if (binWidth > u0) {
            epsxScale = rt_powd_snf(10.0, floor(log10(leftEdge)));
            binWidth = epsxScale * floor(leftEdge / epsxScale);
            u0 = binWidth * floor(LowLimit / binWidth);
            if ((u0 < LowLimit) || rtIsNaN(LowLimit)) {
                leftEdge = u0;
            } else {
                leftEdge = LowLimit;
            }
            if (!(leftEdge > -1.7976931348623157E+308)) {
                leftEdge = -1.7976931348623157E+308;
            }
            epsxScale = HighLimit - leftEdge;
            xScale = epsxScale / 20.0;
            epsxScale =
                rt_powd_snf(10.0, floor(log10(epsxScale / 19.0 - xScale)));
            binWidth = epsxScale * ceil(xScale / epsxScale);
            u0 = leftEdge + 20.0 * binWidth;
            if ((u0 > HighLimit) || rtIsNaN(HighLimit)) {
                xScale = u0;
            } else {
                xScale = HighLimit;
            }
            if (!(xScale < 1.7976931348623157E+308)) {
                xScale = 1.7976931348623157E+308;
            }
        } else {
            if (b && b1) {
                if (xScale <= 2.2250738585072014E-308) {
                    epsxScale = 4.94065645841247E-324;
                } else {
                    frexp(xScale, &mid_i);
                    epsxScale = ldexp(1.0, mid_i - 53);
                }
            } else {
                epsxScale = rtNaN;
            }
            epsxScale = ceil(20.0 * epsxScale);
            if ((1.0 > epsxScale) || rtIsNaN(epsxScale)) {
                epsxScale = 1.0;
            }
            leftEdge = floor(2.0 * (LowLimit - epsxScale / 4.0)) / 2.0;
            xScale = ceil(2.0 * (HighLimit + epsxScale / 4.0)) / 2.0;
            binWidth = (xScale - leftEdge) / 20.0;
        }
        if ((!rtIsInf(binWidth)) && (!rtIsNaN(binWidth))) {
            edges_size[0] = 1;
            edges_size[1] = 21;
            memset(&edges_data[0], 0, 21U * sizeof(double));
            edges_data[0] = leftEdge;
            for (low_i = 0; low_i < 19; low_i++) {
                edges_data[low_i + 1] =
                    leftEdge + (static_cast<double>(low_i) + 1.0) * binWidth;
            }
            edges_data[20] = xScale;
        } else {
            edges_size[0] = 1;
            edges_size[1] = 21;
            edges_data[20] = xScale;
            edges_data[0] = leftEdge;
            if (leftEdge == -xScale) {
                epsxScale = xScale / 20.0;
                for (k = 0; k < 19; k++) {
                    edges_data[k + 1] =
                        (2.0 * (static_cast<double>(k) + 2.0) - 22.0) *
                        epsxScale;
                }
                edges_data[10] = 0.0;
            } else if (((leftEdge < 0.0) != (xScale < 0.0)) &&
                       ((fabs(leftEdge) > 8.9884656743115785E+307) ||
                        (fabs(xScale) > 8.9884656743115785E+307))) {
                binWidth = leftEdge / 20.0;
                epsxScale = xScale / 20.0;
                for (k = 0; k < 19; k++) {
                    edges_data[k + 1] =
                        (leftEdge +
                         epsxScale * (static_cast<double>(k) + 1.0)) -
                        binWidth * (static_cast<double>(k) + 1.0);
                }
            } else {
                binWidth = (xScale - leftEdge) / 20.0;
                for (k = 0; k < 19; k++) {
                    edges_data[k + 1] =
                        leftEdge + (static_cast<double>(k) + 1.0) * binWidth;
                }
            }
        }
    } else {
        edges_size[0] = 1;
        edges_size[1] = 21;
        for (k = 0; k < 21; k++) {
            edges_data[k] = k;
        }
    }
    memset(&ni_data[0], 0, 20U * sizeof(int));
    nx = x.size(0);
    leftEdge = edges_data[0];
    epsxScale = edges_data[1] - edges_data[0];
    for (k = 0; k < nx; k++) {
        if ((x[k] >= leftEdge) && (x[k] <= edges_data[20])) {
            boolean_T guard1 = false;
            xScale = ceil((x[k] - leftEdge) / epsxScale);
            guard1 = false;
            if ((xScale >= 1.0) && (xScale < 21.0)) {
                i = static_cast<int>(xScale);
                if ((x[k] >= edges_data[i - 1]) && (x[k] < edges_data[i])) {
                    ni_data[i - 1]++;
                } else {
                    guard1 = true;
                }
            } else {
                guard1 = true;
            }
            if (guard1) {
                low_i = 1;
                low_ip1 = 2;
                high_i = 21;
                while (high_i > low_ip1) {
                    mid_i = (low_i >> 1) + (high_i >> 1);
                    if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
                        mid_i++;
                    }
                    if (x[k] >= edges_data[mid_i - 1]) {
                        low_i = mid_i;
                        low_ip1 = mid_i + 1;
                    } else {
                        high_i = mid_i;
                    }
                }
                ni_data[low_i - 1]++;
            }
        }
    }
    n_size[0] = 1;
    n_size[1] = 20;
    for (i = 0; i < 20; i++) {
        n_data[i] = ni_data[i];
    }
}

} // namespace coder
