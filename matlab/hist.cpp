//
// File: hist.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "hist.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &Y
//                double no[200]
//                double xo[200]
// Return Type  : void
//
namespace coder {
    void hist(const ::coder::array<double, 2U> &Y, double no[200], double xo[200]) {
        double edges[201];
        double nn[201];
        int low_ip1;
        if (Y.size(1) == 0) {
            for (int i = 0; i < 200; i++) {
                xo[i] = static_cast<double>(i) + 1.0;
                no[i] = 0.0;
            }
        } else {
            double delta2;
            double maxy;
            double miny;
            int b_k;
            int i;
            unsigned int k;
            int ny;
            boolean_T exitg1;
            ny = Y.size(1);
            k = 1U;
            exitg1 = false;
            while ((!exitg1) && (k <= static_cast<unsigned int>(ny))) {
                delta2 = Y[static_cast<int>(k) - 1];
                if ((!rtIsInf(delta2)) && (!rtIsNaN(delta2))) {
                    exitg1 = true;
                } else {
                    k++;
                }
            }
            if (k > static_cast<unsigned int>(Y.size(1))) {
                miny = 0.0;
                maxy = 0.0;
            } else {
                miny = Y[static_cast<int>(k) - 1];
                maxy = Y[static_cast<int>(k) - 1];
                while (k <= static_cast<unsigned int>(ny)) {
                    delta2 = Y[static_cast<int>(k) - 1];
                    if ((!rtIsInf(delta2)) && (!rtIsNaN(delta2))) {
                        if (delta2 < miny) {
                            miny = Y[static_cast<int>(k) - 1];
                        }
                        if (delta2 > maxy) {
                            maxy = delta2;
                        }
                    }
                    k++;
                }
            }
            if (miny == maxy) {
                miny = (miny - 100.0) - 0.5;
                maxy = (maxy + 100.0) - 0.5;
            }
            edges[200] = maxy;
            edges[0] = miny;
            if (miny == -maxy) {
                delta2 = maxy / 200.0;
                for (b_k = 0; b_k < 199; b_k++) {
                    edges[b_k + 1] =
                            (2.0 * (static_cast<double>(b_k) + 2.0) - 202.0) * delta2;
                }
                edges[100] = 0.0;
            } else if (((miny < 0.0) != (maxy < 0.0)) &&
                       ((fabs(miny) > 8.9884656743115785E+307) ||
                        (fabs(maxy) > 8.9884656743115785E+307))) {
                double delta1;
                delta1 = miny / 200.0;
                delta2 = maxy / 200.0;
                for (b_k = 0; b_k < 199; b_k++) {
                    edges[b_k + 1] = (miny + delta2 * (static_cast<double>(b_k) + 1.0)) -
                                     delta1 * (static_cast<double>(b_k) + 1.0);
                }
            } else {
                double delta1;
                delta1 = (maxy - miny) / 200.0;
                for (b_k = 0; b_k < 199; b_k++) {
                    edges[b_k + 1] = miny + (static_cast<double>(b_k) + 1.0) * delta1;
                }
            }
            delta2 = (edges[1] - edges[0]) / 2.0;
            for (i = 0; i < 200; i++) {
                xo[i] = edges[i] + delta2;
            }
            edges[0] = rtMinusInf;
            edges[200] = rtInf;
            for (b_k = 0; b_k < 199; b_k++) {
                maxy = edges[b_k + 1];
                delta2 = fabs(maxy);
                if ((!rtIsInf(delta2)) && (!rtIsNaN(delta2))) {
                    if (delta2 <= 2.2250738585072014E-308) {
                        delta2 = 4.94065645841247E-324;
                    } else {
                        frexp(delta2, &low_ip1);
                        delta2 = ldexp(1.0, low_ip1 - 53);
                    }
                } else {
                    delta2 = rtNaN;
                }
                edges[b_k + 1] = maxy + delta2;
            }
            memset(&nn[0], 0, 201U * sizeof(double));
            ny = 1;
            int exitg2;
            do {
                exitg2 = 0;
                if (ny + 1 < 202) {
                    if (!(edges[ny] >= edges[ny - 1])) {
                        for (ny = 0; ny < 201; ny++) {
                            nn[ny] = rtNaN;
                        }
                        exitg2 = 1;
                    } else {
                        ny++;
                    }
                } else {
                    i = Y.size(1);
                    for (b_k = 0; b_k < i; b_k++) {
                        ny = 0;
                        delta2 = Y[b_k];
                        if (!rtIsNaN(delta2)) {
                            if ((delta2 >= edges[0]) && (delta2 < edges[200])) {
                                int high_i;
                                ny = 1;
                                low_ip1 = 2;
                                high_i = 201;
                                while (high_i > low_ip1) {
                                    int mid_i;
                                    mid_i = (ny + high_i) >> 1;
                                    if (Y[b_k] >= edges[mid_i - 1]) {
                                        ny = mid_i;
                                        low_ip1 = mid_i + 1;
                                    } else {
                                        high_i = mid_i;
                                    }
                                }
                            }
                            if (Y[b_k] == edges[200]) {
                                ny = 201;
                            }
                        }
                        if (ny > 0) {
                            nn[ny - 1]++;
                        }
                    }
                    exitg2 = 1;
                }
            } while (exitg2 == 0);
            memcpy(&no[0], &nn[0], 200U * sizeof(double));
            no[199] += nn[200];
        }
    }

} // namespace coder

//
// File trailer for hist.cpp
//
// [EOF]
//
