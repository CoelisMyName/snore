//
// File: histcounts.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "histcounts.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &n
//                ::coder::array<double, 2U> &edges
// Return Type  : void
//
namespace coder {
    void histcounts(const ::coder::array<double, 2U> &x,
                    ::coder::array<double, 2U> &n,
                    ::coder::array<double, 2U> &edges) {
        array<int, 2U> ni;
        double HighLimit;
        double LowLimit;
        double binWidth;
        double epsxScale;
        double leftEdge;
        double xScale;
        int high_i;
        int k;
        int low_i;
        int low_ip1;
        int mid_i;
        int nx;
        nx = x.size(1);
        k = 0;
        while ((k + 1 <= nx) && (rtIsInf(x[k]) || rtIsNaN(x[k]))) {
            k++;
        }
        if (k + 1 > x.size(1)) {
            LowLimit = 0.0;
            high_i = 0;
        } else {
            LowLimit = x[k];
            high_i = 1;
        }
        HighLimit = LowLimit;
        mid_i = k + 2;
        for (k = mid_i; k <= nx; k++) {
            xScale = x[k - 1];
            if ((!rtIsInf(xScale)) && (!rtIsNaN(xScale))) {
                if (xScale < LowLimit) {
                    LowLimit = xScale;
                } else if (xScale > HighLimit) {
                    HighLimit = xScale;
                }
                high_i++;
            }
        }
        binWidth = HighLimit - LowLimit;
        leftEdge = binWidth / 20.0;
        if (high_i > 0) {
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
                    frexp(xScale, &low_i);
                    epsxScale = ldexp(1.0, low_i - 53);
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
                binWidth = epsxScale / 20.0;
                epsxScale = rt_powd_snf(10.0, floor(log10(epsxScale / 19.0 - binWidth)));
                binWidth = epsxScale * ceil(binWidth / epsxScale);
                u0 = leftEdge + 20.0 * binWidth;
                if ((u0 > HighLimit) || rtIsNaN(HighLimit)) {
                    epsxScale = u0;
                } else {
                    epsxScale = HighLimit;
                }
                if (!(epsxScale < 1.7976931348623157E+308)) {
                    epsxScale = 1.7976931348623157E+308;
                }
            } else {
                if (b && b1) {
                    if (xScale <= 2.2250738585072014E-308) {
                        epsxScale = 4.94065645841247E-324;
                    } else {
                        frexp(xScale, &low_ip1);
                        epsxScale = ldexp(1.0, low_ip1 - 53);
                    }
                } else {
                    epsxScale = rtNaN;
                }
                epsxScale = ceil(20.0 * epsxScale);
                if ((1.0 > epsxScale) || rtIsNaN(epsxScale)) {
                    epsxScale = 1.0;
                }
                leftEdge = floor(2.0 * (LowLimit - epsxScale / 4.0)) / 2.0;
                epsxScale = ceil(2.0 * (HighLimit + epsxScale / 4.0)) / 2.0;
                binWidth = (epsxScale - leftEdge) / 20.0;
            }
            if ((!rtIsInf(binWidth)) && (!rtIsNaN(binWidth))) {
                edges.set_size(1, 21);
                for (mid_i = 0; mid_i < 21; mid_i++) {
                    edges[mid_i] = 0.0;
                }
                edges[0] = leftEdge;
                for (high_i = 0; high_i < 19; high_i++) {
                    edges[high_i + 1] =
                            leftEdge + (static_cast<double>(high_i) + 1.0) * binWidth;
                }
                edges[20] = epsxScale;
            } else {
                edges.set_size(1, 21);
                edges[20] = epsxScale;
                edges[0] = leftEdge;
                if (leftEdge == -epsxScale) {
                    epsxScale /= 20.0;
                    for (k = 0; k < 19; k++) {
                        edges[k + 1] =
                                ((2.0 * (static_cast<double>(k) + 2.0) - 21.0) - 1.0) * epsxScale;
                    }
                    edges[10] = 0.0;
                } else if (((leftEdge < 0.0) != (epsxScale < 0.0)) &&
                           ((fabs(leftEdge) > 8.9884656743115785E+307) ||
                            (fabs(epsxScale) > 8.9884656743115785E+307))) {
                    binWidth = leftEdge / 20.0;
                    epsxScale /= 20.0;
                    for (k = 0; k < 19; k++) {
                        edges[k + 1] =
                                (leftEdge + epsxScale * (static_cast<double>(k) + 1.0)) -
                                binWidth * (static_cast<double>(k) + 1.0);
                    }
                } else {
                    binWidth = (epsxScale - leftEdge) / 20.0;
                    for (k = 0; k < 19; k++) {
                        edges[k + 1] = leftEdge + (static_cast<double>(k) + 1.0) * binWidth;
                    }
                }
            }
        } else {
            edges.set_size(1, 21);
            for (k = 0; k < 21; k++) {
                edges[k] = k;
            }
        }
        ni.set_size(1, 20);
        for (mid_i = 0; mid_i < 20; mid_i++) {
            ni[mid_i] = 0;
        }
        nx = x.size(1);
        leftEdge = edges[0];
        epsxScale = edges[1] - edges[0];
        for (k = 0; k < nx; k++) {
            xScale = x[k];
            if ((xScale >= leftEdge) && (xScale <= edges[20])) {
                binWidth = ceil((xScale - leftEdge) / epsxScale);
                if ((binWidth >= 1.0) && (binWidth < 21.0) &&
                    (xScale >= edges[static_cast<int>(binWidth) - 1]) &&
                    (xScale < edges[static_cast<int>(binWidth)])) {
                    ni[static_cast<int>(binWidth) - 1] =
                            ni[static_cast<int>(binWidth) - 1] + 1;
                } else {
                    high_i = 21;
                    low_i = 1;
                    low_ip1 = 2;
                    while (high_i > low_ip1) {
                        mid_i = (low_i >> 1) + (high_i >> 1);
                        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
                            mid_i++;
                        }
                        if (x[k] >= edges[mid_i - 1]) {
                            low_i = mid_i;
                            low_ip1 = mid_i + 1;
                        } else {
                            high_i = mid_i;
                        }
                    }
                    ni[low_i - 1] = ni[low_i - 1] + 1;
                }
            }
        }
        n.set_size(1, 20);
        for (mid_i = 0; mid_i < 20; mid_i++) {
            n[mid_i] = ni[mid_i];
        }
    }

} // namespace coder

//
// File trailer for histcounts.cpp
//
// [EOF]
//
