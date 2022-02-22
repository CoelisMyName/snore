//
// File: NCF.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "NCF.h"
#include "FFTImplementationCallback.h"
#include "SnoringRecognition_rtwutil.h"
#include "getCandidates.h"
#include "pitchValidator.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &y
//                const pitchValidator params
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
namespace coder {
    namespace audio {
        namespace internal {
            namespace pitch {
                void NCF(const ::coder::array<double, 2U> &y, const pitchValidator params,
                         ::coder::array<double, 1U> &f0) {
                    array<creal_T, 2U> b_y;
                    array<double, 2U> Rt;
                    array<double, 2U> b_c1;
                    array<double, 2U> c1;
                    array<double, 2U> c_y;
                    array<double, 2U> d_y;
                    array<double, 2U> yRMS;
                    array<double, 1U> peak;
                    double edge[2];
                    double mxl;
                    int i;
                    int i1;
                    int ibmat;
                    int loop_ub;
                    int nChan;
                    int result;
                    int sz_idx_0;
                    int varargin_1_tmp;
                    short input_sizes_idx_0;
                    boolean_T empty_non_axis_sizes;
                    edge[0] = rt_roundd_snf(8000.0 / params.Range[1]);
                    edge[1] = rt_roundd_snf(8000.0 / params.Range[0]);
                    mxl = edge[1];
                    if (!(mxl < 399.0)) {
                        mxl = 399.0;
                    }
                    if (y.size(1) == 0) {
                        b_y.set_size(1024, 0);
                    } else {
                        nChan = y.size(1);
                        b_y.set_size(1024, y.size(1));
                        loop_ub = 1024 * y.size(1);
                        for (i = 0; i < loop_ub; i++) {
                            b_y[i].re = 0.0;
                            b_y[i].im = 0.0;
                        }
                        for (ibmat = 0; ibmat < nChan; ibmat++) {
                            for (i = 0; i < 1024; i++) {
                                b_y[i + 1024 * ibmat].re = 0.0;
                                b_y[i + 1024 * ibmat].im = 0.0;
                            }
                            ::coder::internal::FFTImplementationCallback::doHalfLengthRadix2(
                                    y, ibmat * 400, *(creal_T(*)[1024]) &b_y[1024 * ibmat]);
                        }
                    }
                    nChan = b_y.size(1) << 10;
                    c1.set_size(1024, b_y.size(1));
                    for (ibmat = 0; ibmat < nChan; ibmat++) {
                        c1[ibmat] = rt_hypotd_snf(b_y[ibmat].re, b_y[ibmat].im);
                    }
                    c_y.set_size(1024, c1.size(1));
                    nChan = c1.size(1) << 10;
                    for (ibmat = 0; ibmat < nChan; ibmat++) {
                        c_y[ibmat] = c1[ibmat] * c1[ibmat];
                    }
                    if (c_y.size(1) == 0) {
                        b_y.set_size(1024, 0);
                    } else {
                        nChan = c_y.size(1);
                        b_y.set_size(1024, c_y.size(1));
                        for (ibmat = 0; ibmat < nChan; ibmat++) {
                            ::coder::internal::FFTImplementationCallback::b_doHalfLengthRadix2(
                                    c_y, ibmat << 10, *(creal_T(*)[1024]) &b_y[1024 * ibmat]);
                        }
                        loop_ub = 1024 * b_y.size(1);
                        b_y.set_size(1024, b_y.size(1));
                        for (i = 0; i < loop_ub; i++) {
                            b_y[i].re = 0.0009765625 * b_y[i].re;
                            b_y[i].im = 0.0009765625 * b_y[i].im;
                        }
                    }
                    c1.set_size(1024, b_y.size(1));
                    loop_ub = 1024 * b_y.size(1);
                    for (i = 0; i < loop_ub; i++) {
                        c1[i] = b_y[i].re / 32.0;
                    }
                    if (1.0 > mxl + 1.0) {
                        loop_ub = 0;
                    } else {
                        loop_ub = static_cast<int>(mxl + 1.0);
                    }
                    if (mxl < 1.0) {
                        d_y.set_size(1, 0);
                    } else {
                        i = static_cast<int>(mxl);
                        d_y.set_size(1, i);
                        ibmat = i - 1;
                        for (i = 0; i <= ibmat; i++) {
                            d_y[i] = static_cast<double>(i) + 1.0;
                        }
                    }
                    ibmat = c1.size(1);
                    yRMS.set_size(d_y.size(1), c1.size(1));
                    for (i = 0; i < ibmat; i++) {
                        nChan = d_y.size(1);
                        for (i1 = 0; i1 < nChan; i1++) {
                            yRMS[i1 + yRMS.size(0) * i] =
                                    c1[(static_cast<int>((1024.0 - mxl) + d_y[i1]) + 1024 * i) - 1];
                        }
                    }
                    if ((d_y.size(1) != 0) && (c1.size(1) != 0)) {
                        result = c1.size(1);
                    } else if ((loop_ub != 0) && (c1.size(1) != 0)) {
                        result = c1.size(1);
                    } else {
                        if (c1.size(1) > 0) {
                            result = c1.size(1);
                        } else {
                            result = 0;
                        }
                        if (c1.size(1) > result) {
                            result = c1.size(1);
                        }
                    }
                    empty_non_axis_sizes = (result == 0);
                    if (empty_non_axis_sizes || ((d_y.size(1) != 0) && (c1.size(1) != 0))) {
                        input_sizes_idx_0 = static_cast<short>(d_y.size(1));
                    } else {
                        input_sizes_idx_0 = 0;
                    }
                    if (empty_non_axis_sizes || ((loop_ub != 0) && (c1.size(1) != 0))) {
                        sz_idx_0 = loop_ub;
                    } else {
                        sz_idx_0 = 0;
                    }
                    nChan = input_sizes_idx_0;
                    ibmat = c1.size(1);
                    b_c1.set_size(loop_ub, c1.size(1));
                    for (i = 0; i < ibmat; i++) {
                        for (i1 = 0; i1 < loop_ub; i1++) {
                            b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 1024 * i];
                        }
                    }
                    Rt.set_size(input_sizes_idx_0 + sz_idx_0, result);
                    for (i = 0; i < result; i++) {
                        for (i1 = 0; i1 < nChan; i1++) {
                            Rt[i1 + Rt.size(0) * i] = yRMS[i1 + input_sizes_idx_0 * i];
                        }
                    }
                    for (i = 0; i < result; i++) {
                        for (i1 = 0; i1 < sz_idx_0; i1++) {
                            Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] = b_c1[i1 + sz_idx_0 * i];
                        }
                    }
                    mxl = (edge[1] + 1.0) + edge[0];
                    if (mxl > Rt.size(0)) {
                        i = -1;
                        i1 = -1;
                    } else {
                        i = static_cast<int>(mxl) - 2;
                        i1 = Rt.size(0) - 1;
                    }
                    loop_ub = Rt.size(1);
                    d_y.set_size(1, Rt.size(1));
                    for (nChan = 0; nChan < loop_ub; nChan++) {
                        d_y[nChan] = Rt[(static_cast<int>(edge[1] + 1.0) + Rt.size(0) * nChan) - 1];
                    }
                    nChan = Rt.size(1) - 1;
                    for (ibmat = 0; ibmat <= nChan; ibmat++) {
                        d_y[ibmat] = sqrt(d_y[ibmat]);
                    }
                    varargin_1_tmp = i1 - i;
                    yRMS.set_size(varargin_1_tmp, d_y.size(1));
                    nChan = d_y.size(1);
                    for (result = 0; result < nChan; result++) {
                        ibmat = result * varargin_1_tmp;
                        for (sz_idx_0 = 0; sz_idx_0 < varargin_1_tmp; sz_idx_0++) {
                            yRMS[ibmat + sz_idx_0] = d_y[result];
                        }
                    }
                    loop_ub = Rt.size(1);
                    yRMS.set_size(varargin_1_tmp, Rt.size(1));
                    for (i1 = 0; i1 < loop_ub; i1++) {
                        for (nChan = 0; nChan < varargin_1_tmp; nChan++) {
                            yRMS[nChan + yRMS.size(0) * i1] =
                                    Rt[((i + nChan) + Rt.size(0) * i1) + 1] /
                                    yRMS[nChan + yRMS.size(0) * i1];
                        }
                    }
                    if ((static_cast<int>(edge[0] - 1.0) != 0) && (yRMS.size(1) != 0)) {
                        result = yRMS.size(1);
                    } else if ((yRMS.size(0) != 0) && (yRMS.size(1) != 0)) {
                        result = yRMS.size(1);
                    } else {
                        result = yRMS.size(1);
                    }
                    empty_non_axis_sizes = (result == 0);
                    if (empty_non_axis_sizes ||
                        ((static_cast<int>(edge[0] - 1.0) != 0) && (yRMS.size(1) != 0))) {
                        nChan = static_cast<int>(edge[0] - 1.0);
                    } else {
                        nChan = 0;
                    }
                    if (empty_non_axis_sizes || ((yRMS.size(0) != 0) && (yRMS.size(1) != 0))) {
                        sz_idx_0 = yRMS.size(0);
                    } else {
                        sz_idx_0 = 0;
                    }
                    b_c1.set_size(nChan + sz_idx_0, result);
                    for (i = 0; i < result; i++) {
                        for (i1 = 0; i1 < nChan; i1++) {
                            b_c1[i1 + b_c1.size(0) * i] = 0.0;
                        }
                    }
                    for (i = 0; i < result; i++) {
                        for (i1 = 0; i1 < sz_idx_0; i1++) {
                            b_c1[(i1 + nChan) + b_c1.size(0) * i] = yRMS[i1 + sz_idx_0 * i];
                        }
                    }
                    getCandidates(b_c1, edge, 1.0, peak, f0);
                    loop_ub = f0.size(0);
                    for (i = 0; i < loop_ub; i++) {
                        f0[i] = 8000.0 / f0[i];
                    }
                }

            } // namespace pitch
        } // namespace internal
    } // namespace audio
} // namespace coder

//
// File trailer for NCF.cpp
//
// [EOF]
//
