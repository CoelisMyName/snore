//
// File: pitch.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "pitch.h"
#include "FFTImplementationCallback.h"
#include "NCF.h"
#include "SnoringRecognition_rtwutil.h"
#include "getCandidates.h"
#include "pitchValidator.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
namespace coder {
    void b_pitch(const ::coder::array<double, 1U> &x,
                 ::coder::array<double, 1U> &f0) {
        array<creal_T, 2U> b_y;
        array<double, 2U> Rt;
        array<double, 2U> b_c1;
        array<double, 2U> c1;
        array<double, 2U> c_y;
        array<double, 2U> d_y;
        array<double, 2U> y;
        array<double, 2U> yRMS;
        array<double, 1U> peak;
        array<int, 1U> b_r;
        array<int, 1U> r1;
        double edge[2];
        int hop;
        int i;
        int i1;
        int loop_ub;
        int r;
        int sz_idx_0;
        int varargin_1_tmp;
        unsigned char input_sizes_idx_0;
        boolean_T empty_non_axis_sizes;
        r = x.size(0);
        sz_idx_0 =
                static_cast<int>(ceil((static_cast<double>(x.size(0)) - 551.0) / 275.0));
        y.set_size(551, sz_idx_0 + 1);
        loop_ub = 551 * (sz_idx_0 + 1);
        for (i = 0; i < loop_ub; i++) {
            y[i] = 0.0;
        }
        for (hop = 0; hop <= sz_idx_0; hop++) {
            unsigned int u0;
            unsigned int u1;
            i = 275 * hop;
            u0 = 275 * hop + 551U;
            u1 = static_cast<unsigned int>(r);
            if (u0 < u1) {
                u1 = u0;
            }
            if (static_cast<unsigned int>(i + 1) > u1) {
                i = 0;
                i1 = -1;
            } else {
                i1 = static_cast<int>(u1) - 1;
            }
            loop_ub = i1 - i;
            for (i1 = 0; i1 <= loop_ub; i1++) {
                y[i1 + 551 * hop] = x[i + i1];
            }
        }
        edge[0] = 28.0;
        edge[1] = 221.0;
        if (y.size(1) == 0) {
            b_y.set_size(2048, 0);
        } else {
            r = y.size(1);
            b_y.set_size(2048, y.size(1));
            loop_ub = 2048 * y.size(1);
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.0;
                b_y[i].im = 0.0;
            }
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                for (i = 0; i < 2048; i++) {
                    b_y[i + 2048 * sz_idx_0].re = 0.0;
                    b_y[i + 2048 * sz_idx_0].im = 0.0;
                }
                internal::FFTImplementationCallback::c_doHalfLengthRadix2(
                        y, sz_idx_0 * 551, *(creal_T(*)[2048]) &b_y[2048 * sz_idx_0]);
            }
        }
        r = b_y.size(1) << 11;
        c1.set_size(2048, b_y.size(1));
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c1[sz_idx_0] = rt_hypotd_snf(b_y[sz_idx_0].re, b_y[sz_idx_0].im);
        }
        c_y.set_size(2048, c1.size(1));
        r = c1.size(1) << 11;
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c_y[sz_idx_0] = c1[sz_idx_0] * c1[sz_idx_0];
        }
        if (c_y.size(1) == 0) {
            b_y.set_size(2048, 0);
        } else {
            r = c_y.size(1);
            b_y.set_size(2048, c_y.size(1));
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                internal::FFTImplementationCallback::d_doHalfLengthRadix2(
                        c_y, sz_idx_0 << 11, *(creal_T(*)[2048]) &b_y[2048 * sz_idx_0]);
            }
            loop_ub = 2048 * b_y.size(1);
            b_y.set_size(2048, b_y.size(1));
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.00048828125 * b_y[i].re;
                b_y[i].im = 0.00048828125 * b_y[i].im;
            }
        }
        c1.set_size(2048, b_y.size(1));
        loop_ub = 2048 * b_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            c1[i] = b_y[i].re / 45.254833995939045;
        }
        d_y.set_size(1, 221);
        for (i = 0; i < 221; i++) {
            d_y[i] = static_cast<double>(i) + 1.0;
        }
        loop_ub = c1.size(1);
        yRMS.set_size(221, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 221; i1++) {
                yRMS[i1 + yRMS.size(0) * i] =
                        c1[(static_cast<int>(d_y[i1] + 1827.0) + 2048 * i) - 1];
            }
        }
        if (c1.size(1) != 0) {
            r = c1.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            input_sizes_idx_0 = 221U;
        } else {
            input_sizes_idx_0 = 0U;
        }
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            sz_idx_0 = 222;
        } else {
            sz_idx_0 = 0;
        }
        hop = input_sizes_idx_0;
        loop_ub = c1.size(1);
        b_c1.set_size(222, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 222; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 2048 * i];
            }
        }
        Rt.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < hop; i1++) {
                Rt[i1 + Rt.size(0) * i] = yRMS[i1 + input_sizes_idx_0 * i];
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] = b_c1[i1 + sz_idx_0 * i];
            }
        }
        if (250 > Rt.size(0)) {
            i = -1;
            i1 = -1;
        } else {
            i = 248;
            i1 = Rt.size(0) - 1;
        }
        loop_ub = Rt.size(1);
        d_y.set_size(1, Rt.size(1));
        for (r = 0; r < loop_ub; r++) {
            d_y[r] = Rt[Rt.size(0) * r + 221];
        }
        r = Rt.size(1) - 1;
        for (sz_idx_0 = 0; sz_idx_0 <= r; sz_idx_0++) {
            d_y[sz_idx_0] = sqrt(d_y[sz_idx_0]);
        }
        varargin_1_tmp = i1 - i;
        yRMS.set_size(varargin_1_tmp, d_y.size(1));
        r = d_y.size(1);
        for (hop = 0; hop < r; hop++) {
            sz_idx_0 = hop * varargin_1_tmp;
            for (loop_ub = 0; loop_ub < varargin_1_tmp; loop_ub++) {
                yRMS[sz_idx_0 + loop_ub] = d_y[hop];
            }
        }
        loop_ub = Rt.size(1);
        yRMS.set_size(varargin_1_tmp, Rt.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            for (r = 0; r < varargin_1_tmp; r++) {
                yRMS[r + yRMS.size(0) * i1] =
                        Rt[((i + r) + Rt.size(0) * i1) + 1] / yRMS[r + yRMS.size(0) * i1];
            }
        }
        if (yRMS.size(1) != 0) {
            r = yRMS.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (yRMS.size(1) != 0)) {
            input_sizes_idx_0 = 27U;
        } else {
            input_sizes_idx_0 = 0U;
        }
        if (empty_non_axis_sizes || ((yRMS.size(0) != 0) && (yRMS.size(1) != 0))) {
            sz_idx_0 = yRMS.size(0);
        } else {
            sz_idx_0 = 0;
        }
        b_c1.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            loop_ub = input_sizes_idx_0;
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = 0.0;
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                b_c1[(i1 + input_sizes_idx_0) + b_c1.size(0) * i] =
                        yRMS[i1 + sz_idx_0 * i];
            }
        }
        audio::internal::pitch::getCandidates(b_c1, edge, 1.0, peak, f0);
        loop_ub = f0.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[i] = 11025.0 / f0[i];
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                r++;
            }
        }
        b_r.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                b_r[r] = hop + 1;
                r++;
            }
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[b_r[i] - 1] = 50.0;
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r++;
            }
        }
        r1.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r1[r] = hop + 1;
                r++;
            }
        }
        loop_ub = r1.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[r1[i] - 1] = 400.0;
        }
        r = static_cast<int>(
                    floor((static_cast<double>(x.size(0)) - 551.0) / 275.0)) +
            1;
        if (1 > r) {
            r = 0;
        }
        f0.set_size(r);
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
    void c_pitch(const ::coder::array<double, 1U> &x,
                 ::coder::array<double, 1U> &f0) {
        array<creal_T, 2U> b_y;
        array<double, 2U> Rt;
        array<double, 2U> b_c1;
        array<double, 2U> c1;
        array<double, 2U> c_y;
        array<double, 2U> d_y;
        array<double, 2U> y;
        array<double, 2U> yRMS;
        array<double, 1U> peak;
        array<int, 1U> b_r;
        array<int, 1U> r1;
        double edge[2];
        int hop;
        int i;
        int i1;
        int loop_ub;
        int r;
        int sz_idx_0;
        int varargin_1_tmp;
        unsigned char input_sizes_idx_0;
        boolean_T empty_non_axis_sizes;
        r = x.size(0);
        sz_idx_0 =
                static_cast<int>(ceil((static_cast<double>(x.size(0)) - 600.0) / 300.0));
        y.set_size(600, sz_idx_0 + 1);
        loop_ub = 600 * (sz_idx_0 + 1);
        for (i = 0; i < loop_ub; i++) {
            y[i] = 0.0;
        }
        for (hop = 0; hop <= sz_idx_0; hop++) {
            unsigned int u0;
            unsigned int u1;
            i = 300 * hop;
            u0 = 300 * hop + 600U;
            u1 = static_cast<unsigned int>(r);
            if (u0 < u1) {
                u1 = u0;
            }
            if (static_cast<unsigned int>(i + 1) > u1) {
                i = 0;
                i1 = -1;
            } else {
                i1 = static_cast<int>(u1) - 1;
            }
            loop_ub = i1 - i;
            for (i1 = 0; i1 <= loop_ub; i1++) {
                y[i1 + 600 * hop] = x[i + i1];
            }
        }
        edge[0] = 30.0;
        edge[1] = 240.0;
        if (y.size(1) == 0) {
            b_y.set_size(2048, 0);
        } else {
            r = y.size(1);
            b_y.set_size(2048, y.size(1));
            loop_ub = 2048 * y.size(1);
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.0;
                b_y[i].im = 0.0;
            }
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                for (i = 0; i < 2048; i++) {
                    b_y[i + 2048 * sz_idx_0].re = 0.0;
                    b_y[i + 2048 * sz_idx_0].im = 0.0;
                }
                internal::FFTImplementationCallback::e_doHalfLengthRadix2(
                        y, sz_idx_0 * 600, *(creal_T(*)[2048]) &b_y[2048 * sz_idx_0]);
            }
        }
        r = b_y.size(1) << 11;
        c1.set_size(2048, b_y.size(1));
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c1[sz_idx_0] = rt_hypotd_snf(b_y[sz_idx_0].re, b_y[sz_idx_0].im);
        }
        c_y.set_size(2048, c1.size(1));
        r = c1.size(1) << 11;
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c_y[sz_idx_0] = c1[sz_idx_0] * c1[sz_idx_0];
        }
        if (c_y.size(1) == 0) {
            b_y.set_size(2048, 0);
        } else {
            r = c_y.size(1);
            b_y.set_size(2048, c_y.size(1));
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                internal::FFTImplementationCallback::d_doHalfLengthRadix2(
                        c_y, sz_idx_0 << 11, *(creal_T(*)[2048]) &b_y[2048 * sz_idx_0]);
            }
            loop_ub = 2048 * b_y.size(1);
            b_y.set_size(2048, b_y.size(1));
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.00048828125 * b_y[i].re;
                b_y[i].im = 0.00048828125 * b_y[i].im;
            }
        }
        c1.set_size(2048, b_y.size(1));
        loop_ub = 2048 * b_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            c1[i] = b_y[i].re / 45.254833995939045;
        }
        d_y.set_size(1, 240);
        for (i = 0; i < 240; i++) {
            d_y[i] = static_cast<double>(i) + 1.0;
        }
        loop_ub = c1.size(1);
        yRMS.set_size(240, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 240; i1++) {
                yRMS[i1 + yRMS.size(0) * i] =
                        c1[(static_cast<int>(d_y[i1] + 1808.0) + 2048 * i) - 1];
            }
        }
        if (c1.size(1) != 0) {
            r = c1.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            input_sizes_idx_0 = 240U;
        } else {
            input_sizes_idx_0 = 0U;
        }
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            sz_idx_0 = 241;
        } else {
            sz_idx_0 = 0;
        }
        hop = input_sizes_idx_0;
        loop_ub = c1.size(1);
        b_c1.set_size(241, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 241; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 2048 * i];
            }
        }
        Rt.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < hop; i1++) {
                Rt[i1 + Rt.size(0) * i] = yRMS[i1 + input_sizes_idx_0 * i];
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] = b_c1[i1 + sz_idx_0 * i];
            }
        }
        if (271 > Rt.size(0)) {
            i = -1;
            i1 = -1;
        } else {
            i = 269;
            i1 = Rt.size(0) - 1;
        }
        loop_ub = Rt.size(1);
        d_y.set_size(1, Rt.size(1));
        for (r = 0; r < loop_ub; r++) {
            d_y[r] = Rt[Rt.size(0) * r + 240];
        }
        r = Rt.size(1) - 1;
        for (sz_idx_0 = 0; sz_idx_0 <= r; sz_idx_0++) {
            d_y[sz_idx_0] = sqrt(d_y[sz_idx_0]);
        }
        varargin_1_tmp = i1 - i;
        yRMS.set_size(varargin_1_tmp, d_y.size(1));
        r = d_y.size(1);
        for (hop = 0; hop < r; hop++) {
            sz_idx_0 = hop * varargin_1_tmp;
            for (loop_ub = 0; loop_ub < varargin_1_tmp; loop_ub++) {
                yRMS[sz_idx_0 + loop_ub] = d_y[hop];
            }
        }
        loop_ub = Rt.size(1);
        yRMS.set_size(varargin_1_tmp, Rt.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            for (r = 0; r < varargin_1_tmp; r++) {
                yRMS[r + yRMS.size(0) * i1] =
                        Rt[((i + r) + Rt.size(0) * i1) + 1] / yRMS[r + yRMS.size(0) * i1];
            }
        }
        if (yRMS.size(1) != 0) {
            r = yRMS.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (yRMS.size(1) != 0)) {
            input_sizes_idx_0 = 29U;
        } else {
            input_sizes_idx_0 = 0U;
        }
        if (empty_non_axis_sizes || ((yRMS.size(0) != 0) && (yRMS.size(1) != 0))) {
            sz_idx_0 = yRMS.size(0);
        } else {
            sz_idx_0 = 0;
        }
        b_c1.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            loop_ub = input_sizes_idx_0;
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = 0.0;
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                b_c1[(i1 + input_sizes_idx_0) + b_c1.size(0) * i] =
                        yRMS[i1 + sz_idx_0 * i];
            }
        }
        audio::internal::pitch::getCandidates(b_c1, edge, 1.0, peak, f0);
        loop_ub = f0.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[i] = 12000.0 / f0[i];
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                r++;
            }
        }
        b_r.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                b_r[r] = hop + 1;
                r++;
            }
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[b_r[i] - 1] = 50.0;
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r++;
            }
        }
        r1.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r1[r] = hop + 1;
                r++;
            }
        }
        loop_ub = r1.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[r1[i] - 1] = 400.0;
        }
        r = static_cast<int>(
                    floor((static_cast<double>(x.size(0)) - 600.0) / 300.0)) +
            1;
        if (1 > r) {
            r = 0;
        }
        f0.set_size(r);
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
    void d_pitch(const ::coder::array<double, 1U> &x,
                 ::coder::array<double, 1U> &f0) {
        array<creal_T, 2U> b_y;
        array<double, 2U> Rt;
        array<double, 2U> b_c1;
        array<double, 2U> c1;
        array<double, 2U> c_y;
        array<double, 2U> d_y;
        array<double, 2U> y;
        array<double, 2U> yRMS;
        array<double, 1U> peak;
        array<int, 1U> b_r;
        array<int, 1U> r1;
        double edge[2];
        int hop;
        int i;
        int i1;
        int loop_ub;
        int r;
        int sz_idx_0;
        int varargin_1_tmp;
        short input_sizes_idx_0;
        boolean_T empty_non_axis_sizes;
        r = x.size(0);
        sz_idx_0 =
                static_cast<int>(ceil((static_cast<double>(x.size(0)) - 1103.0) / 552.0));
        y.set_size(1103, sz_idx_0 + 1);
        loop_ub = 1103 * (sz_idx_0 + 1);
        for (i = 0; i < loop_ub; i++) {
            y[i] = 0.0;
        }
        for (hop = 0; hop <= sz_idx_0; hop++) {
            unsigned int u0;
            unsigned int u1;
            i = 552 * hop;
            u0 = 552 * hop + 1103U;
            u1 = static_cast<unsigned int>(r);
            if (u0 < u1) {
                u1 = u0;
            }
            if (static_cast<unsigned int>(i + 1) > u1) {
                i = 0;
                i1 = -1;
            } else {
                i1 = static_cast<int>(u1) - 1;
            }
            loop_ub = i1 - i;
            for (i1 = 0; i1 <= loop_ub; i1++) {
                y[i1 + 1103 * hop] = x[i + i1];
            }
        }
        edge[0] = 55.0;
        edge[1] = 441.0;
        if (y.size(1) == 0) {
            b_y.set_size(4096, 0);
        } else {
            r = y.size(1);
            b_y.set_size(4096, y.size(1));
            loop_ub = 4096 * y.size(1);
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.0;
                b_y[i].im = 0.0;
            }
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                for (i = 0; i < 4096; i++) {
                    b_y[i + 4096 * sz_idx_0].re = 0.0;
                    b_y[i + 4096 * sz_idx_0].im = 0.0;
                }
                internal::FFTImplementationCallback::f_doHalfLengthRadix2(
                        y, sz_idx_0 * 1103, *(creal_T(*)[4096]) &b_y[4096 * sz_idx_0]);
            }
        }
        r = b_y.size(1) << 12;
        c1.set_size(4096, b_y.size(1));
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c1[sz_idx_0] = rt_hypotd_snf(b_y[sz_idx_0].re, b_y[sz_idx_0].im);
        }
        c_y.set_size(4096, c1.size(1));
        r = c1.size(1) << 12;
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c_y[sz_idx_0] = c1[sz_idx_0] * c1[sz_idx_0];
        }
        if (c_y.size(1) == 0) {
            b_y.set_size(4096, 0);
        } else {
            r = c_y.size(1);
            b_y.set_size(4096, c_y.size(1));
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                internal::FFTImplementationCallback::g_doHalfLengthRadix2(
                        c_y, sz_idx_0 << 12, *(creal_T(*)[4096]) &b_y[4096 * sz_idx_0]);
            }
            loop_ub = 4096 * b_y.size(1);
            b_y.set_size(4096, b_y.size(1));
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.000244140625 * b_y[i].re;
                b_y[i].im = 0.000244140625 * b_y[i].im;
            }
        }
        c1.set_size(4096, b_y.size(1));
        loop_ub = 4096 * b_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            c1[i] = b_y[i].re / 64.0;
        }
        d_y.set_size(1, 441);
        for (i = 0; i < 441; i++) {
            d_y[i] = static_cast<double>(i) + 1.0;
        }
        loop_ub = c1.size(1);
        yRMS.set_size(441, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 441; i1++) {
                yRMS[i1 + yRMS.size(0) * i] =
                        c1[(static_cast<int>(d_y[i1] + 3655.0) + 4096 * i) - 1];
            }
        }
        if (c1.size(1) != 0) {
            r = c1.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            input_sizes_idx_0 = 441;
        } else {
            input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            sz_idx_0 = 442;
        } else {
            sz_idx_0 = 0;
        }
        hop = input_sizes_idx_0;
        loop_ub = c1.size(1);
        b_c1.set_size(442, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 442; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 4096 * i];
            }
        }
        Rt.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < hop; i1++) {
                Rt[i1 + Rt.size(0) * i] = yRMS[i1 + input_sizes_idx_0 * i];
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] = b_c1[i1 + sz_idx_0 * i];
            }
        }
        if (497 > Rt.size(0)) {
            i = -1;
            i1 = -1;
        } else {
            i = 495;
            i1 = Rt.size(0) - 1;
        }
        loop_ub = Rt.size(1);
        d_y.set_size(1, Rt.size(1));
        for (r = 0; r < loop_ub; r++) {
            d_y[r] = Rt[Rt.size(0) * r + 441];
        }
        r = Rt.size(1) - 1;
        for (sz_idx_0 = 0; sz_idx_0 <= r; sz_idx_0++) {
            d_y[sz_idx_0] = sqrt(d_y[sz_idx_0]);
        }
        varargin_1_tmp = i1 - i;
        yRMS.set_size(varargin_1_tmp, d_y.size(1));
        r = d_y.size(1);
        for (hop = 0; hop < r; hop++) {
            sz_idx_0 = hop * varargin_1_tmp;
            for (loop_ub = 0; loop_ub < varargin_1_tmp; loop_ub++) {
                yRMS[sz_idx_0 + loop_ub] = d_y[hop];
            }
        }
        loop_ub = Rt.size(1);
        yRMS.set_size(varargin_1_tmp, Rt.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            for (r = 0; r < varargin_1_tmp; r++) {
                yRMS[r + yRMS.size(0) * i1] =
                        Rt[((i + r) + Rt.size(0) * i1) + 1] / yRMS[r + yRMS.size(0) * i1];
            }
        }
        if (yRMS.size(1) != 0) {
            r = yRMS.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (yRMS.size(1) != 0)) {
            input_sizes_idx_0 = 54;
        } else {
            input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || ((yRMS.size(0) != 0) && (yRMS.size(1) != 0))) {
            sz_idx_0 = yRMS.size(0);
        } else {
            sz_idx_0 = 0;
        }
        b_c1.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            loop_ub = input_sizes_idx_0;
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = 0.0;
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                b_c1[(i1 + input_sizes_idx_0) + b_c1.size(0) * i] =
                        yRMS[i1 + sz_idx_0 * i];
            }
        }
        audio::internal::pitch::getCandidates(b_c1, edge, 1.0, peak, f0);
        loop_ub = f0.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[i] = 22050.0 / f0[i];
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                r++;
            }
        }
        b_r.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                b_r[r] = hop + 1;
                r++;
            }
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[b_r[i] - 1] = 50.0;
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r++;
            }
        }
        r1.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r1[r] = hop + 1;
                r++;
            }
        }
        loop_ub = r1.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[r1[i] - 1] = 400.0;
        }
        r = static_cast<int>(
                    floor((static_cast<double>(x.size(0)) - 1103.0) / 552.0)) +
            1;
        if (1 > r) {
            r = 0;
        }
        f0.set_size(r);
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
    void e_pitch(const ::coder::array<double, 1U> &x,
                 ::coder::array<double, 1U> &f0) {
        array<creal_T, 2U> b_y;
        array<double, 2U> Rt;
        array<double, 2U> b_c1;
        array<double, 2U> c1;
        array<double, 2U> c_y;
        array<double, 2U> d_y;
        array<double, 2U> y;
        array<double, 2U> yRMS;
        array<double, 1U> peak;
        array<int, 1U> b_r;
        array<int, 1U> r1;
        double edge[2];
        int hop;
        int i;
        int i1;
        int loop_ub;
        int r;
        int sz_idx_0;
        int varargin_1_tmp;
        short input_sizes_idx_0;
        boolean_T empty_non_axis_sizes;
        r = x.size(0);
        sz_idx_0 =
                static_cast<int>(ceil((static_cast<double>(x.size(0)) - 1200.0) / 600.0));
        y.set_size(1200, sz_idx_0 + 1);
        loop_ub = 1200 * (sz_idx_0 + 1);
        for (i = 0; i < loop_ub; i++) {
            y[i] = 0.0;
        }
        for (hop = 0; hop <= sz_idx_0; hop++) {
            unsigned int u0;
            unsigned int u1;
            i = 600 * hop;
            u0 = 600 * hop + 1200U;
            u1 = static_cast<unsigned int>(r);
            if (u0 < u1) {
                u1 = u0;
            }
            if (static_cast<unsigned int>(i + 1) > u1) {
                i = 0;
                i1 = -1;
            } else {
                i1 = static_cast<int>(u1) - 1;
            }
            loop_ub = i1 - i;
            for (i1 = 0; i1 <= loop_ub; i1++) {
                y[i1 + 1200 * hop] = x[i + i1];
            }
        }
        edge[0] = 60.0;
        edge[1] = 480.0;
        if (y.size(1) == 0) {
            b_y.set_size(4096, 0);
        } else {
            r = y.size(1);
            b_y.set_size(4096, y.size(1));
            loop_ub = 4096 * y.size(1);
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.0;
                b_y[i].im = 0.0;
            }
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                for (i = 0; i < 4096; i++) {
                    b_y[i + 4096 * sz_idx_0].re = 0.0;
                    b_y[i + 4096 * sz_idx_0].im = 0.0;
                }
                internal::FFTImplementationCallback::h_doHalfLengthRadix2(
                        y, sz_idx_0 * 1200, *(creal_T(*)[4096]) &b_y[4096 * sz_idx_0]);
            }
        }
        r = b_y.size(1) << 12;
        c1.set_size(4096, b_y.size(1));
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c1[sz_idx_0] = rt_hypotd_snf(b_y[sz_idx_0].re, b_y[sz_idx_0].im);
        }
        c_y.set_size(4096, c1.size(1));
        r = c1.size(1) << 12;
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c_y[sz_idx_0] = c1[sz_idx_0] * c1[sz_idx_0];
        }
        if (c_y.size(1) == 0) {
            b_y.set_size(4096, 0);
        } else {
            r = c_y.size(1);
            b_y.set_size(4096, c_y.size(1));
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                internal::FFTImplementationCallback::g_doHalfLengthRadix2(
                        c_y, sz_idx_0 << 12, *(creal_T(*)[4096]) &b_y[4096 * sz_idx_0]);
            }
            loop_ub = 4096 * b_y.size(1);
            b_y.set_size(4096, b_y.size(1));
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.000244140625 * b_y[i].re;
                b_y[i].im = 0.000244140625 * b_y[i].im;
            }
        }
        c1.set_size(4096, b_y.size(1));
        loop_ub = 4096 * b_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            c1[i] = b_y[i].re / 64.0;
        }
        d_y.set_size(1, 480);
        for (i = 0; i < 480; i++) {
            d_y[i] = static_cast<double>(i) + 1.0;
        }
        loop_ub = c1.size(1);
        yRMS.set_size(480, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 480; i1++) {
                yRMS[i1 + yRMS.size(0) * i] =
                        c1[(static_cast<int>(d_y[i1] + 3616.0) + 4096 * i) - 1];
            }
        }
        if (c1.size(1) != 0) {
            r = c1.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            input_sizes_idx_0 = 480;
        } else {
            input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            sz_idx_0 = 481;
        } else {
            sz_idx_0 = 0;
        }
        hop = input_sizes_idx_0;
        loop_ub = c1.size(1);
        b_c1.set_size(481, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 481; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 4096 * i];
            }
        }
        Rt.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < hop; i1++) {
                Rt[i1 + Rt.size(0) * i] = yRMS[i1 + input_sizes_idx_0 * i];
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] = b_c1[i1 + sz_idx_0 * i];
            }
        }
        if (541 > Rt.size(0)) {
            i = -1;
            i1 = -1;
        } else {
            i = 539;
            i1 = Rt.size(0) - 1;
        }
        loop_ub = Rt.size(1);
        d_y.set_size(1, Rt.size(1));
        for (r = 0; r < loop_ub; r++) {
            d_y[r] = Rt[Rt.size(0) * r + 480];
        }
        r = Rt.size(1) - 1;
        for (sz_idx_0 = 0; sz_idx_0 <= r; sz_idx_0++) {
            d_y[sz_idx_0] = sqrt(d_y[sz_idx_0]);
        }
        varargin_1_tmp = i1 - i;
        yRMS.set_size(varargin_1_tmp, d_y.size(1));
        r = d_y.size(1);
        for (hop = 0; hop < r; hop++) {
            sz_idx_0 = hop * varargin_1_tmp;
            for (loop_ub = 0; loop_ub < varargin_1_tmp; loop_ub++) {
                yRMS[sz_idx_0 + loop_ub] = d_y[hop];
            }
        }
        loop_ub = Rt.size(1);
        yRMS.set_size(varargin_1_tmp, Rt.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            for (r = 0; r < varargin_1_tmp; r++) {
                yRMS[r + yRMS.size(0) * i1] =
                        Rt[((i + r) + Rt.size(0) * i1) + 1] / yRMS[r + yRMS.size(0) * i1];
            }
        }
        if (yRMS.size(1) != 0) {
            r = yRMS.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (yRMS.size(1) != 0)) {
            input_sizes_idx_0 = 59;
        } else {
            input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || ((yRMS.size(0) != 0) && (yRMS.size(1) != 0))) {
            sz_idx_0 = yRMS.size(0);
        } else {
            sz_idx_0 = 0;
        }
        b_c1.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            loop_ub = input_sizes_idx_0;
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = 0.0;
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                b_c1[(i1 + input_sizes_idx_0) + b_c1.size(0) * i] =
                        yRMS[i1 + sz_idx_0 * i];
            }
        }
        audio::internal::pitch::getCandidates(b_c1, edge, 1.0, peak, f0);
        loop_ub = f0.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[i] = 24000.0 / f0[i];
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                r++;
            }
        }
        b_r.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                b_r[r] = hop + 1;
                r++;
            }
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[b_r[i] - 1] = 50.0;
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r++;
            }
        }
        r1.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r1[r] = hop + 1;
                r++;
            }
        }
        loop_ub = r1.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[r1[i] - 1] = 400.0;
        }
        r = static_cast<int>(
                    floor((static_cast<double>(x.size(0)) - 1200.0) / 600.0)) +
            1;
        if (1 > r) {
            r = 0;
        }
        f0.set_size(r);
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
    void f_pitch(const ::coder::array<double, 1U> &x,
                 ::coder::array<double, 1U> &f0) {
        array<creal_T, 2U> b_y;
        array<double, 2U> Rt;
        array<double, 2U> b_c1;
        array<double, 2U> c1;
        array<double, 2U> c_y;
        array<double, 2U> d_y;
        array<double, 2U> y;
        array<double, 2U> yRMS;
        array<double, 1U> peak;
        array<int, 1U> b_r;
        array<int, 1U> r1;
        double edge[2];
        int hop;
        int i;
        int i1;
        int loop_ub;
        int r;
        int sz_idx_0;
        int varargin_1_tmp;
        short input_sizes_idx_0;
        boolean_T empty_non_axis_sizes;
        r = x.size(0);
        sz_idx_0 = static_cast<int>(
                ceil((static_cast<double>(x.size(0)) - 2205.0) / 1102.0));
        y.set_size(2205, sz_idx_0 + 1);
        loop_ub = 2205 * (sz_idx_0 + 1);
        for (i = 0; i < loop_ub; i++) {
            y[i] = 0.0;
        }
        for (hop = 0; hop <= sz_idx_0; hop++) {
            unsigned int u0;
            unsigned int u1;
            i = 1102 * hop;
            u0 = 1102 * hop + 2205U;
            u1 = static_cast<unsigned int>(r);
            if (u0 < u1) {
                u1 = u0;
            }
            if (static_cast<unsigned int>(i + 1) > u1) {
                i = 0;
                i1 = -1;
            } else {
                i1 = static_cast<int>(u1) - 1;
            }
            loop_ub = i1 - i;
            for (i1 = 0; i1 <= loop_ub; i1++) {
                y[i1 + 2205 * hop] = x[i + i1];
            }
        }
        edge[0] = 110.0;
        edge[1] = 882.0;
        if (y.size(1) == 0) {
            b_y.set_size(8192, 0);
        } else {
            r = y.size(1);
            b_y.set_size(8192, y.size(1));
            loop_ub = 8192 * y.size(1);
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.0;
                b_y[i].im = 0.0;
            }
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                for (i = 0; i < 8192; i++) {
                    b_y[i + 8192 * sz_idx_0].re = 0.0;
                    b_y[i + 8192 * sz_idx_0].im = 0.0;
                }
                internal::FFTImplementationCallback::i_doHalfLengthRadix2(
                        y, sz_idx_0 * 2205, *(creal_T(*)[8192]) &b_y[8192 * sz_idx_0]);
            }
        }
        r = b_y.size(1) << 13;
        c1.set_size(8192, b_y.size(1));
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c1[sz_idx_0] = rt_hypotd_snf(b_y[sz_idx_0].re, b_y[sz_idx_0].im);
        }
        c_y.set_size(8192, c1.size(1));
        r = c1.size(1) << 13;
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c_y[sz_idx_0] = c1[sz_idx_0] * c1[sz_idx_0];
        }
        if (c_y.size(1) == 0) {
            b_y.set_size(8192, 0);
        } else {
            r = c_y.size(1);
            b_y.set_size(8192, c_y.size(1));
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                internal::FFTImplementationCallback::j_doHalfLengthRadix2(
                        c_y, sz_idx_0 << 13, *(creal_T(*)[8192]) &b_y[8192 * sz_idx_0]);
            }
            loop_ub = 8192 * b_y.size(1);
            b_y.set_size(8192, b_y.size(1));
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.0001220703125 * b_y[i].re;
                b_y[i].im = 0.0001220703125 * b_y[i].im;
            }
        }
        c1.set_size(8192, b_y.size(1));
        loop_ub = 8192 * b_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            c1[i] = b_y[i].re / 90.509667991878089;
        }
        d_y.set_size(1, 882);
        for (i = 0; i < 882; i++) {
            d_y[i] = static_cast<double>(i) + 1.0;
        }
        loop_ub = c1.size(1);
        yRMS.set_size(882, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 882; i1++) {
                yRMS[i1 + yRMS.size(0) * i] =
                        c1[(static_cast<int>(d_y[i1] + 7310.0) + 8192 * i) - 1];
            }
        }
        if (c1.size(1) != 0) {
            r = c1.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            input_sizes_idx_0 = 882;
        } else {
            input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            sz_idx_0 = 883;
        } else {
            sz_idx_0 = 0;
        }
        hop = input_sizes_idx_0;
        loop_ub = c1.size(1);
        b_c1.set_size(883, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 883; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 8192 * i];
            }
        }
        Rt.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < hop; i1++) {
                Rt[i1 + Rt.size(0) * i] = yRMS[i1 + input_sizes_idx_0 * i];
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] = b_c1[i1 + sz_idx_0 * i];
            }
        }
        if (993 > Rt.size(0)) {
            i = -1;
            i1 = -1;
        } else {
            i = 991;
            i1 = Rt.size(0) - 1;
        }
        loop_ub = Rt.size(1);
        d_y.set_size(1, Rt.size(1));
        for (r = 0; r < loop_ub; r++) {
            d_y[r] = Rt[Rt.size(0) * r + 882];
        }
        r = Rt.size(1) - 1;
        for (sz_idx_0 = 0; sz_idx_0 <= r; sz_idx_0++) {
            d_y[sz_idx_0] = sqrt(d_y[sz_idx_0]);
        }
        varargin_1_tmp = i1 - i;
        yRMS.set_size(varargin_1_tmp, d_y.size(1));
        r = d_y.size(1);
        for (hop = 0; hop < r; hop++) {
            sz_idx_0 = hop * varargin_1_tmp;
            for (loop_ub = 0; loop_ub < varargin_1_tmp; loop_ub++) {
                yRMS[sz_idx_0 + loop_ub] = d_y[hop];
            }
        }
        loop_ub = Rt.size(1);
        yRMS.set_size(varargin_1_tmp, Rt.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            for (r = 0; r < varargin_1_tmp; r++) {
                yRMS[r + yRMS.size(0) * i1] =
                        Rt[((i + r) + Rt.size(0) * i1) + 1] / yRMS[r + yRMS.size(0) * i1];
            }
        }
        if (yRMS.size(1) != 0) {
            r = yRMS.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (yRMS.size(1) != 0)) {
            input_sizes_idx_0 = 109;
        } else {
            input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || ((yRMS.size(0) != 0) && (yRMS.size(1) != 0))) {
            sz_idx_0 = yRMS.size(0);
        } else {
            sz_idx_0 = 0;
        }
        b_c1.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            loop_ub = input_sizes_idx_0;
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = 0.0;
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                b_c1[(i1 + input_sizes_idx_0) + b_c1.size(0) * i] =
                        yRMS[i1 + sz_idx_0 * i];
            }
        }
        audio::internal::pitch::getCandidates(b_c1, edge, 1.0, peak, f0);
        loop_ub = f0.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[i] = 44100.0 / f0[i];
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                r++;
            }
        }
        b_r.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                b_r[r] = hop + 1;
                r++;
            }
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[b_r[i] - 1] = 50.0;
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r++;
            }
        }
        r1.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r1[r] = hop + 1;
                r++;
            }
        }
        loop_ub = r1.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[r1[i] - 1] = 400.0;
        }
        r = static_cast<int>(
                    floor((static_cast<double>(x.size(0)) - 2205.0) / 1102.0)) +
            1;
        if (1 > r) {
            r = 0;
        }
        f0.set_size(r);
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
    void g_pitch(const ::coder::array<double, 1U> &x,
                 ::coder::array<double, 1U> &f0) {
        array<creal_T, 2U> b_y;
        array<double, 2U> Rt;
        array<double, 2U> b_c1;
        array<double, 2U> c1;
        array<double, 2U> c_y;
        array<double, 2U> d_y;
        array<double, 2U> y;
        array<double, 2U> yRMS;
        array<double, 1U> peak;
        array<int, 1U> b_r;
        array<int, 1U> r1;
        double edge[2];
        int hop;
        int i;
        int i1;
        int loop_ub;
        int r;
        int sz_idx_0;
        int varargin_1_tmp;
        short input_sizes_idx_0;
        boolean_T empty_non_axis_sizes;
        r = x.size(0);
        sz_idx_0 = static_cast<int>(
                ceil((static_cast<double>(x.size(0)) - 2400.0) / 1200.0));
        y.set_size(2400, sz_idx_0 + 1);
        loop_ub = 2400 * (sz_idx_0 + 1);
        for (i = 0; i < loop_ub; i++) {
            y[i] = 0.0;
        }
        for (hop = 0; hop <= sz_idx_0; hop++) {
            unsigned int u0;
            unsigned int u1;
            i = 1200 * hop;
            u0 = 1200 * hop + 2400U;
            u1 = static_cast<unsigned int>(r);
            if (u0 < u1) {
                u1 = u0;
            }
            if (static_cast<unsigned int>(i + 1) > u1) {
                i = 0;
                i1 = -1;
            } else {
                i1 = static_cast<int>(u1) - 1;
            }
            loop_ub = i1 - i;
            for (i1 = 0; i1 <= loop_ub; i1++) {
                y[i1 + 2400 * hop] = x[i + i1];
            }
        }
        edge[0] = 120.0;
        edge[1] = 960.0;
        if (y.size(1) == 0) {
            b_y.set_size(8192, 0);
        } else {
            r = y.size(1);
            b_y.set_size(8192, y.size(1));
            loop_ub = 8192 * y.size(1);
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.0;
                b_y[i].im = 0.0;
            }
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                for (i = 0; i < 8192; i++) {
                    b_y[i + 8192 * sz_idx_0].re = 0.0;
                    b_y[i + 8192 * sz_idx_0].im = 0.0;
                }
                internal::FFTImplementationCallback::k_doHalfLengthRadix2(
                        y, sz_idx_0 * 2400, *(creal_T(*)[8192]) &b_y[8192 * sz_idx_0]);
            }
        }
        r = b_y.size(1) << 13;
        c1.set_size(8192, b_y.size(1));
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c1[sz_idx_0] = rt_hypotd_snf(b_y[sz_idx_0].re, b_y[sz_idx_0].im);
        }
        c_y.set_size(8192, c1.size(1));
        r = c1.size(1) << 13;
        for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
            c_y[sz_idx_0] = c1[sz_idx_0] * c1[sz_idx_0];
        }
        if (c_y.size(1) == 0) {
            b_y.set_size(8192, 0);
        } else {
            r = c_y.size(1);
            b_y.set_size(8192, c_y.size(1));
            for (sz_idx_0 = 0; sz_idx_0 < r; sz_idx_0++) {
                internal::FFTImplementationCallback::j_doHalfLengthRadix2(
                        c_y, sz_idx_0 << 13, *(creal_T(*)[8192]) &b_y[8192 * sz_idx_0]);
            }
            loop_ub = 8192 * b_y.size(1);
            b_y.set_size(8192, b_y.size(1));
            for (i = 0; i < loop_ub; i++) {
                b_y[i].re = 0.0001220703125 * b_y[i].re;
                b_y[i].im = 0.0001220703125 * b_y[i].im;
            }
        }
        c1.set_size(8192, b_y.size(1));
        loop_ub = 8192 * b_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            c1[i] = b_y[i].re / 90.509667991878089;
        }
        d_y.set_size(1, 960);
        for (i = 0; i < 960; i++) {
            d_y[i] = static_cast<double>(i) + 1.0;
        }
        loop_ub = c1.size(1);
        yRMS.set_size(960, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 960; i1++) {
                yRMS[i1 + yRMS.size(0) * i] =
                        c1[(static_cast<int>(d_y[i1] + 7232.0) + 8192 * i) - 1];
            }
        }
        if (c1.size(1) != 0) {
            r = c1.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            input_sizes_idx_0 = 960;
        } else {
            input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || (c1.size(1) != 0)) {
            sz_idx_0 = 961;
        } else {
            sz_idx_0 = 0;
        }
        hop = input_sizes_idx_0;
        loop_ub = c1.size(1);
        b_c1.set_size(961, c1.size(1));
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < 961; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = c1[i1 + 8192 * i];
            }
        }
        Rt.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < hop; i1++) {
                Rt[i1 + Rt.size(0) * i] = yRMS[i1 + input_sizes_idx_0 * i];
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                Rt[(i1 + input_sizes_idx_0) + Rt.size(0) * i] = b_c1[i1 + sz_idx_0 * i];
            }
        }
        if (1081 > Rt.size(0)) {
            i = -1;
            i1 = -1;
        } else {
            i = 1079;
            i1 = Rt.size(0) - 1;
        }
        loop_ub = Rt.size(1);
        d_y.set_size(1, Rt.size(1));
        for (r = 0; r < loop_ub; r++) {
            d_y[r] = Rt[Rt.size(0) * r + 960];
        }
        r = Rt.size(1) - 1;
        for (sz_idx_0 = 0; sz_idx_0 <= r; sz_idx_0++) {
            d_y[sz_idx_0] = sqrt(d_y[sz_idx_0]);
        }
        varargin_1_tmp = i1 - i;
        yRMS.set_size(varargin_1_tmp, d_y.size(1));
        r = d_y.size(1);
        for (hop = 0; hop < r; hop++) {
            sz_idx_0 = hop * varargin_1_tmp;
            for (loop_ub = 0; loop_ub < varargin_1_tmp; loop_ub++) {
                yRMS[sz_idx_0 + loop_ub] = d_y[hop];
            }
        }
        loop_ub = Rt.size(1);
        yRMS.set_size(varargin_1_tmp, Rt.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            for (r = 0; r < varargin_1_tmp; r++) {
                yRMS[r + yRMS.size(0) * i1] =
                        Rt[((i + r) + Rt.size(0) * i1) + 1] / yRMS[r + yRMS.size(0) * i1];
            }
        }
        if (yRMS.size(1) != 0) {
            r = yRMS.size(1);
        } else {
            r = 0;
        }
        empty_non_axis_sizes = (r == 0);
        if (empty_non_axis_sizes || (yRMS.size(1) != 0)) {
            input_sizes_idx_0 = 119;
        } else {
            input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || ((yRMS.size(0) != 0) && (yRMS.size(1) != 0))) {
            sz_idx_0 = yRMS.size(0);
        } else {
            sz_idx_0 = 0;
        }
        b_c1.set_size(input_sizes_idx_0 + sz_idx_0, r);
        for (i = 0; i < r; i++) {
            loop_ub = input_sizes_idx_0;
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_c1[i1 + b_c1.size(0) * i] = 0.0;
            }
        }
        for (i = 0; i < r; i++) {
            for (i1 = 0; i1 < sz_idx_0; i1++) {
                b_c1[(i1 + input_sizes_idx_0) + b_c1.size(0) * i] =
                        yRMS[i1 + sz_idx_0 * i];
            }
        }
        audio::internal::pitch::getCandidates(b_c1, edge, 1.0, peak, f0);
        loop_ub = f0.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[i] = 48000.0 / f0[i];
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                r++;
            }
        }
        b_r.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] < 50.0) {
                b_r[r] = hop + 1;
                r++;
            }
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[b_r[i] - 1] = 50.0;
        }
        sz_idx_0 = f0.size(0) - 1;
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r++;
            }
        }
        r1.set_size(r);
        r = 0;
        for (hop = 0; hop <= sz_idx_0; hop++) {
            if (f0[hop] > 400.0) {
                r1[r] = hop + 1;
                r++;
            }
        }
        loop_ub = r1.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[r1[i] - 1] = 400.0;
        }
        r = static_cast<int>(
                    floor((static_cast<double>(x.size(0)) - 2400.0) / 1200.0)) +
            1;
        if (1 > r) {
            r = 0;
        }
        f0.set_size(r);
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
    void pitch(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &f0) {
        audio::internal::pitchValidator params;
        array<double, 2U> y;
        array<int, 1U> b_r;
        array<int, 1U> r1;
        int b_x;
        int i;
        int loop_ub;
        int r;
        params.Range[0] = 50.0;
        params.Range[1] = 400.0;
        r = x.size(0);
        b_x =
                static_cast<int>(ceil((static_cast<double>(x.size(0)) - 400.0) / 200.0));
        y.set_size(400, b_x + 1);
        loop_ub = 400 * (b_x + 1);
        for (i = 0; i < loop_ub; i++) {
            y[i] = 0.0;
        }
        for (int hop = 0; hop <= b_x; hop++) {
            int i1;
            unsigned int u0;
            unsigned int u1;
            i = 200 * hop;
            u0 = 200 * hop + 400U;
            u1 = static_cast<unsigned int>(r);
            if (u0 < u1) {
                u1 = u0;
            }
            if (static_cast<unsigned int>(i + 1) > u1) {
                i = 0;
                i1 = -1;
            } else {
                i1 = static_cast<int>(u1) - 1;
            }
            loop_ub = i1 - i;
            for (i1 = 0; i1 <= loop_ub; i1++) {
                y[i1 + 400 * hop] = x[i + i1];
            }
        }
        audio::internal::pitch::NCF(y, params, f0);
        b_x = f0.size(0) - 1;
        r = 0;
        for (loop_ub = 0; loop_ub <= b_x; loop_ub++) {
            if (f0[loop_ub] < 50.0) {
                r++;
            }
        }
        b_r.set_size(r);
        r = 0;
        for (loop_ub = 0; loop_ub <= b_x; loop_ub++) {
            if (f0[loop_ub] < 50.0) {
                b_r[r] = loop_ub + 1;
                r++;
            }
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[b_r[i] - 1] = 50.0;
        }
        b_x = f0.size(0) - 1;
        r = 0;
        for (loop_ub = 0; loop_ub <= b_x; loop_ub++) {
            if (f0[loop_ub] > 400.0) {
                r++;
            }
        }
        r1.set_size(r);
        r = 0;
        for (loop_ub = 0; loop_ub <= b_x; loop_ub++) {
            if (f0[loop_ub] > 400.0) {
                r1[r] = loop_ub + 1;
                r++;
            }
        }
        loop_ub = r1.size(0);
        for (i = 0; i < loop_ub; i++) {
            f0[r1[i] - 1] = 400.0;
        }
        r = static_cast<int>(
                    floor((static_cast<double>(x.size(0)) - 400.0) / 200.0)) +
            1;
        if (1 > r) {
            r = 0;
        }
        f0.set_size(r);
    }

} // namespace coder

//
// File trailer for pitch.cpp
//
// [EOF]
//
