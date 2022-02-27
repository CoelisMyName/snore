//
// File: getCandidates.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "getCandidates.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &domain
//                const double edge[2]
//                ::coder::array<double, 1U> &peaks
//                ::coder::array<double, 1U> &locs
// Return Type  : void
//
namespace coder {
    namespace audio {
        namespace internal {
            namespace pitch {
                void getCandidates(::coder::array<double, 2U> &domain, const double edge[2],
                                   ::coder::array<double, 1U> &peaks,
                                   ::coder::array<double, 1U> &locs) {
                    array<double, 2U> b_y;
                    array<double, 2U> y;
                    double varargin_1_data[941];
                    double lower;
                    double upper;
                    int tmp_data[941];
                    int i;
                    int last;
                    locs.set_size(domain.size(1));
                    last = domain.size(1);
                    for (i = 0; i < last; i++) {
                        locs[i] = 0.0;
                    }
                    peaks.set_size(domain.size(1));
                    last = domain.size(1);
                    for (i = 0; i < last; i++) {
                        peaks[i] = 0.0;
                    }
                    if (rtIsNaN(edge[0]) || rtIsNaN(edge[1])) {
                        y.set_size(1, 1);
                        y[0] = rtNaN;
                    } else if (edge[1] < edge[0]) {
                        y.set_size(1, 0);
                    } else if ((rtIsInf(edge[0]) || rtIsInf(edge[1])) && (edge[0] == edge[1])) {
                        y.set_size(1, 1);
                        y[0] = rtNaN;
                    } else if (floor(edge[0]) == edge[0]) {
                        last = static_cast<int>(floor(edge[1] - edge[0]));
                        y.set_size(1, last + 1);
                        for (i = 0; i <= last; i++) {
                            y[i] = edge[0] + static_cast<double>(i);
                        }
                    } else {
                        eml_float_colon(edge[0], edge[1], y);
                    }
                    lower = edge[0];
                    upper = edge[1];
                    i = domain.size(1);
                    for (int c = 0; c < i; c++) {
                        double a;
                        double ex;
                        int i1;
                        int iindx;
                        int k;
                        last = y.size(1);
                        for (i1 = 0; i1 < last; i1++) {
                            varargin_1_data[i1] =
                                    domain[(static_cast<int>(y[i1]) + domain.size(0) * c) - 1];
                        }
                        last = y.size(1);
                        if (y.size(1) <= 2) {
                            if (y.size(1) == 1) {
                                peaks[c] =
                                        domain[(static_cast<int>(y[0]) + domain.size(0) * c) - 1];
                                iindx = 1;
                            } else {
                                a = domain[(static_cast<int>(y[0]) + domain.size(0) * c) - 1];
                                if ((a < domain[(static_cast<int>(y[y.size(1) - 1]) +
                                                 domain.size(0) * c) -
                                                1]) ||
                                    (rtIsNaN(a) &&
                                     (!rtIsNaN(domain[(static_cast<int>(y[y.size(1) - 1]) +
                                                       domain.size(0) * c) -
                                                      1])))) {
                                    peaks[c] = domain[(static_cast<int>(y[y.size(1) - 1]) +
                                                       domain.size(0) * c) -
                                                      1];
                                    iindx = y.size(1);
                                } else {
                                    peaks[c] = a;
                                    iindx = 1;
                                }
                            }
                        } else {
                            if (!rtIsNaN(varargin_1_data[0])) {
                                iindx = 1;
                            } else {
                                boolean_T exitg1;
                                iindx = 0;
                                k = 2;
                                exitg1 = false;
                                while ((!exitg1) && (k <= last)) {
                                    if (!rtIsNaN(varargin_1_data[k - 1])) {
                                        iindx = k;
                                        exitg1 = true;
                                    } else {
                                        k++;
                                    }
                                }
                            }
                            if (iindx == 0) {
                                peaks[c] =
                                        domain[(static_cast<int>(y[0]) + domain.size(0) * c) - 1];
                                iindx = 1;
                            } else {
                                ex = varargin_1_data[iindx - 1];
                                i1 = iindx + 1;
                                for (k = i1; k <= last; k++) {
                                    a = varargin_1_data[k - 1];
                                    if (ex < a) {
                                        ex = a;
                                        iindx = k;
                                    }
                                }
                                peaks[c] = ex;
                            }
                        }
                        ex = (static_cast<double>(iindx) - 1.0) + lower;
                        if ((ex > lower) || rtIsNaN(lower)) {
                            a = ex;
                        } else {
                            a = lower;
                        }
                        ex = (static_cast<double>(iindx) + 1.0) + lower;
                        if ((!(ex < upper)) && (!rtIsNaN(upper))) {
                            ex = upper;
                        }
                        if (rtIsNaN(a) || rtIsNaN(ex)) {
                            b_y.set_size(1, 1);
                            b_y[0] = rtNaN;
                        } else if (ex < a) {
                            b_y.set_size(1, 0);
                        } else if ((rtIsInf(a) || rtIsInf(ex)) && (a == ex)) {
                            b_y.set_size(1, 1);
                            b_y[0] = rtNaN;
                        } else if (floor(a) == a) {
                            last = static_cast<int>(floor(ex - a));
                            b_y.set_size(1, last + 1);
                            for (i1 = 0; i1 <= last; i1++) {
                                b_y[i1] = a + static_cast<double>(i1);
                            }
                        } else {
                            eml_float_colon(a, ex, b_y);
                        }
                        k = b_y.size(1);
                        last = b_y.size(1);
                        for (i1 = 0; i1 < last; i1++) {
                            tmp_data[i1] = static_cast<int>(b_y[i1]);
                        }
                        for (i1 = 0; i1 < k; i1++) {
                            domain[(tmp_data[i1] + domain.size(0) * c) - 1] = rtNaN;
                        }
                        locs[c] = (lower + static_cast<double>(iindx)) - 1.0;
                    }
                }

            } // namespace pitch
        } // namespace internal
    } // namespace audio
} // namespace coder

//
// File trailer for getCandidates.cpp
//
// [EOF]
//
