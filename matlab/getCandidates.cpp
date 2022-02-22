//
// File: getCandidates.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
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
//                double peakDistance
//                ::coder::array<double, 1U> &peaks
//                ::coder::array<double, 1U> &locs
// Return Type  : void
//
namespace coder {
    namespace audio {
        namespace internal {
            namespace pitch {
                void getCandidates(::coder::array<double, 2U> &domain, const double edge[2],
                                   double peakDistance, ::coder::array<double, 1U> &peaks,
                                   ::coder::array<double, 1U> &locs) {
                    array<double, 2U> idxToRemove;
                    array<double, 2U> range;
                    array<int, 1U> r;
                    double lower;
                    double upper;
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
                        range.set_size(1, 1);
                        range[0] = rtNaN;
                    } else if (edge[1] < edge[0]) {
                        range.set_size(1, 0);
                    } else if ((rtIsInf(edge[0]) || rtIsInf(edge[1])) && (edge[0] == edge[1])) {
                        range.set_size(1, 1);
                        range[0] = rtNaN;
                    } else if (floor(edge[0]) == edge[0]) {
                        last = static_cast<int>(floor(edge[1] - edge[0]));
                        range.set_size(1, last + 1);
                        for (i = 0; i <= last; i++) {
                            range[i] = edge[0] + static_cast<double>(i);
                        }
                    } else {
                        eml_float_colon(edge[0], edge[1], range);
                    }
                    lower = edge[0];
                    upper = edge[1];
                    i = domain.size(1);
                    for (int c = 0; c < i; c++) {
                        double a;
                        double ex;
                        int i1;
                        int idx;
                        last = range.size(1);
                        if (range.size(1) <= 2) {
                            if (range.size(1) == 0) {
                                peaks[c] = rtNaN;
                                idx = 1;
                            } else if (range.size(1) == 1) {
                                peaks[c] =
                                        domain[(static_cast<int>(range[0]) + domain.size(0) * c) - 1];
                                idx = 1;
                            } else {
                                i1 = static_cast<int>(range[0]) - 1;
                                a = domain[(static_cast<int>(range[1]) + domain.size(0) * c) - 1];
                                ex = domain[i1 + domain.size(0) * c];
                                if ((ex < a) ||
                                    (rtIsNaN(domain[i1 + domain.size(0) * c]) && (!rtIsNaN(a)))) {
                                    peaks[c] = a;
                                    idx = 2;
                                } else {
                                    peaks[c] = ex;
                                    idx = 1;
                                }
                            }
                        } else {
                            int k;
                            a = domain[(static_cast<int>(range[0]) + domain.size(0) * c) - 1];
                            if (!rtIsNaN(a)) {
                                idx = 1;
                            } else {
                                boolean_T exitg1;
                                idx = 0;
                                k = 2;
                                exitg1 = false;
                                while ((!exitg1) && (k <= last)) {
                                    if (!rtIsNaN(
                                            domain[(static_cast<int>(range[k - 1]) + domain.size(0) * c) -
                                                   1])) {
                                        idx = k;
                                        exitg1 = true;
                                    } else {
                                        k++;
                                    }
                                }
                            }
                            if (idx == 0) {
                                peaks[c] = a;
                                idx = 1;
                            } else {
                                ex =
                                        domain[(static_cast<int>(range[idx - 1]) + domain.size(0) * c) - 1];
                                i1 = idx + 1;
                                for (k = i1; k <= last; k++) {
                                    a = domain[(static_cast<int>(range[k - 1]) + domain.size(0) * c) - 1];
                                    if (ex < a) {
                                        ex = a;
                                        idx = k;
                                    }
                                }
                                peaks[c] = ex;
                            }
                        }
                        ex = (static_cast<double>(idx) - peakDistance) + lower;
                        if ((ex > lower) || rtIsNaN(lower)) {
                            a = ex;
                        } else {
                            a = lower;
                        }
                        ex = (static_cast<double>(idx) + peakDistance) + lower;
                        if ((!(ex < upper)) && (!rtIsNaN(upper))) {
                            ex = upper;
                        }
                        if (rtIsNaN(a) || rtIsNaN(ex)) {
                            idxToRemove.set_size(1, 1);
                            idxToRemove[0] = rtNaN;
                        } else if (ex < a) {
                            idxToRemove.set_size(1, 0);
                        } else if ((rtIsInf(a) || rtIsInf(ex)) && (a == ex)) {
                            idxToRemove.set_size(1, 1);
                            idxToRemove[0] = rtNaN;
                        } else if (floor(a) == a) {
                            last = static_cast<int>(floor(ex - a));
                            idxToRemove.set_size(1, last + 1);
                            for (i1 = 0; i1 <= last; i1++) {
                                idxToRemove[i1] = a + static_cast<double>(i1);
                            }
                        } else {
                            eml_float_colon(a, ex, idxToRemove);
                        }
                        r.set_size(idxToRemove.size(1));
                        last = idxToRemove.size(1);
                        for (i1 = 0; i1 < last; i1++) {
                            r[i1] = static_cast<int>(idxToRemove[i1]);
                        }
                        last = r.size(0);
                        for (i1 = 0; i1 < last; i1++) {
                            domain[(r[i1] + domain.size(0) * c) - 1] = rtNaN;
                        }
                        locs[c] = (lower + static_cast<double>(idx)) - 1.0;
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
