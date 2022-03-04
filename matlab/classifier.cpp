#include "classifier.h"
#include "BARKenergy.h"
#include "CompactClassificationEnsemble.h"
#include "CrestFactor.h"
#include "FeatureTimeZeroCrossingRate.h"
#include "HENR.h"
#include "LPCFeature.h"
#include "PR800.h"
#include "blockedSummation.h"
#include "combineVectorElements.h"
#include "mean.h"
#include "mfcc_m.h"
#include "minOrMax.h"
#include "pitch.h"
#include "rt_nonfinite.h"
#include "var.h"
#include "coder_array.h"
#include <math.h>
#include <string.h>

void classifier(const coder::array<double, 1U> &x, double fs,
                const coder::array<long long, 1U> &w_starts,
                const coder::array<long long, 1U> &w_ends,
                coder::array<double, 1U> &predict_label)
{
    static const signed char b_iv[23] = {3,  18, 19, 1,  46, 47, 53, 34,
                                         50, 30, 31, 51, 33, 42, 54, 29,
                                         28, 32, 53, 7,  52, 27, 36};
    coder::classreg::learning::classif::CompactClassificationEnsemble r9;
    coder::array<double, 2U> BARKEE;
    coder::array<double, 2U> Crest_Factor;
    coder::array<double, 2U> Eh;
    coder::array<double, 2U> HZCRR;
    coder::array<double, 2U> LPCmean;
    coder::array<double, 2U> PR800max;
    coder::array<double, 2U> PR800mean;
    coder::array<double, 2U> PR800min;
    coder::array<double, 2U> PR800var;
    coder::array<double, 2U> a__2;
    coder::array<double, 2U> a__5;
    coder::array<double, 2U> ccc1;
    coder::array<double, 2U> f0;
    coder::array<double, 2U> feature;
    coder::array<double, 2U> feature1;
    coder::array<double, 2U> mfcc_new;
    coder::array<double, 2U> period_max;
    coder::array<double, 2U> period_mean;
    coder::array<double, 2U> period_min;
    coder::array<double, 2U> period_var;
    coder::array<double, 2U> r7;
    coder::array<double, 2U> r8;
    coder::array<double, 2U> varargin_1;
    coder::array<double, 2U> varargin_2;
    coder::array<double, 2U> varargin_3;
    coder::array<double, 2U> vzc;
    coder::array<double, 1U> b_f0;
    coder::array<double, 1U> c_f0;
    coder::array<double, 1U> d_f0;
    coder::array<double, 1U> e_f0;
    coder::array<double, 1U> f_f0;
    coder::array<double, 1U> g_f0;
    coder::array<double, 1U> h_f0;
    coder::array<double, 1U> r;
    coder::array<double, 1U> r1;
    coder::array<double, 1U> r2;
    coder::array<double, 1U> r3;
    coder::array<double, 1U> r4;
    coder::array<double, 1U> r5;
    coder::array<double, 1U> r6;
    coder::array<double, 1U> sig;
    coder::array<double, 1U> varargin_10;
    coder::array<double, 1U> varargin_11;
    coder::array<double, 1U> varargin_12;
    coder::array<double, 1U> varargin_13;
    coder::array<double, 1U> varargin_14;
    coder::array<double, 1U> varargin_5;
    coder::array<double, 1U> varargin_6;
    coder::array<double, 1U> varargin_7;
    coder::array<double, 1U> varargin_8;
    coder::array<double, 1U> varargin_9;
    coder::array<double, 1U> y;
    coder::array<boolean_T, 2U> b_x;
    double a__3[17];
    double a__4[17];
    double b_dv[17];
    double LPC_mean[12];
    double a__6[12];
    double a__7[12];
    double a__8[12];
    double a__1;
    int tmp_size[2];
    int N;
    int i;
    int i1;
    int k;
    int loop_ub;
    int nx;
    int vlen;
    signed char b_input_sizes_idx_1;
    signed char c_input_sizes_idx_1;
    signed char d_input_sizes_idx_1;
    signed char e_input_sizes_idx_1;
    signed char f_input_sizes_idx_1;
    signed char g_input_sizes_idx_1;
    signed char h_input_sizes_idx_1;
    signed char i_input_sizes_idx_1;
    signed char input_sizes_idx_1;
    signed char j_input_sizes_idx_1;
    signed char k_input_sizes_idx_1;
    signed char l_input_sizes_idx_1;
    signed char m_input_sizes_idx_1;
    boolean_T empty_non_axis_sizes;
    nx = w_starts.size(0);
    vlen = w_ends.size(0);
    if (nx < vlen) {
        N = nx;
    } else {
        N = vlen;
    }
    period_mean.set_size(1, N);
    period_min.set_size(1, N);
    period_max.set_size(1, N);
    period_var.set_size(1, N);
    mfcc_new.set_size(16, N);
    loop_ub = N << 4;
    for (i = 0; i < loop_ub; i++) {
        mfcc_new[i] = 0.0;
    }
    Crest_Factor.set_size(1, N);
    HZCRR.set_size(1, N);
    Eh.set_size(1, N);
    BARKEE.set_size(17, N);
    LPCmean.set_size(12, N);
    PR800mean.set_size(1, N);
    PR800max.set_size(1, N);
    PR800min.set_size(1, N);
    PR800var.set_size(1, N);
    for (int b_i = 0; b_i < N; b_i++) {
        double b_y;
        double inc;
        double wlen_tmp;
        double zcr_m;
        wlen_tmp = 0.02 * fs;
        if (wlen_tmp < 0.0) {
            wlen_tmp = ceil(wlen_tmp);
        } else {
            wlen_tmp = floor(wlen_tmp);
        }
        inc = 0.5 * wlen_tmp;
        if (inc < 0.0) {
            inc = ceil(inc);
        } else {
            inc = floor(inc);
        }
        if (w_starts[b_i] > w_ends[b_i]) {
            i = 0;
            i1 = 0;
        } else {
            i = static_cast<int>(w_starts[b_i]) - 1;
            i1 = static_cast<int>(w_ends[b_i]);
        }
        loop_ub = i1 - i;
        sig.set_size(loop_ub);
        for (i1 = 0; i1 < loop_ub; i1++) {
            sig[i1] = x[i + i1];
        }
        b_y = coder::blockedSummation(sig, loop_ub) /
              static_cast<double>(loop_ub);
        loop_ub = sig.size(0);
        for (i = 0; i < loop_ub; i++) {
            sig[i] = sig[i] - b_y;
        }
        nx = sig.size(0);
        y.set_size(sig.size(0));
        for (k = 0; k < nx; k++) {
            y[k] = fabs(sig[k]);
        }
        b_y = coder::internal::maximum(y);
        loop_ub = sig.size(0);
        for (i = 0; i < loop_ub; i++) {
            sig[i] = sig[i] / b_y;
        }
        HENR(sig, fs, &Eh[b_i], &a__1);
        f0.set_size(0, 0);
        switch (static_cast<int>(fs)) {
        case 8000:
            coder::pitch(sig, r);
            b_f0.set_size(r.size(0));
            loop_ub = r.size(0);
            for (i = 0; i < loop_ub; i++) {
                b_f0[i] = r[i];
            }
            f0.set_size(b_f0.size(0), 1);
            loop_ub = b_f0.size(0);
            for (i = 0; i < loop_ub; i++) {
                f0[i] = b_f0[i];
            }
            break;
        case 11025:
            coder::b_pitch(sig, r1);
            c_f0.set_size(r1.size(0));
            loop_ub = r1.size(0);
            for (i = 0; i < loop_ub; i++) {
                c_f0[i] = r1[i];
            }
            f0.set_size(c_f0.size(0), 1);
            loop_ub = c_f0.size(0);
            for (i = 0; i < loop_ub; i++) {
                f0[i] = c_f0[i];
            }
            break;
        case 12000:
            coder::c_pitch(sig, r2);
            d_f0.set_size(r2.size(0));
            loop_ub = r2.size(0);
            for (i = 0; i < loop_ub; i++) {
                d_f0[i] = r2[i];
            }
            f0.set_size(d_f0.size(0), 1);
            loop_ub = d_f0.size(0);
            for (i = 0; i < loop_ub; i++) {
                f0[i] = d_f0[i];
            }
            break;
        case 22050:
            coder::d_pitch(sig, r3);
            e_f0.set_size(r3.size(0));
            loop_ub = r3.size(0);
            for (i = 0; i < loop_ub; i++) {
                e_f0[i] = r3[i];
            }
            f0.set_size(e_f0.size(0), 1);
            loop_ub = e_f0.size(0);
            for (i = 0; i < loop_ub; i++) {
                f0[i] = e_f0[i];
            }
            break;
        case 24000:
            coder::e_pitch(sig, r4);
            f_f0.set_size(r4.size(0));
            loop_ub = r4.size(0);
            for (i = 0; i < loop_ub; i++) {
                f_f0[i] = r4[i];
            }
            f0.set_size(f_f0.size(0), 1);
            loop_ub = f_f0.size(0);
            for (i = 0; i < loop_ub; i++) {
                f0[i] = f_f0[i];
            }
            break;
        case 44100:
            coder::f_pitch(sig, r5);
            g_f0.set_size(r5.size(0));
            loop_ub = r5.size(0);
            for (i = 0; i < loop_ub; i++) {
                g_f0[i] = r5[i];
            }
            f0.set_size(g_f0.size(0), 1);
            loop_ub = g_f0.size(0);
            for (i = 0; i < loop_ub; i++) {
                f0[i] = g_f0[i];
            }
            break;
        case 48000:
            coder::g_pitch(sig, r6);
            h_f0.set_size(r6.size(0));
            loop_ub = r6.size(0);
            for (i = 0; i < loop_ub; i++) {
                h_f0[i] = r6[i];
            }
            f0.set_size(h_f0.size(0), 1);
            loop_ub = h_f0.size(0);
            for (i = 0; i < loop_ub; i++) {
                f0[i] = h_f0[i];
            }
            break;
        }
        coder::combineVectorElements(f0, r7);
        period_mean[b_i] = r7[0] / static_cast<double>(f0.size(0));
        coder::internal::minimum(f0, (double *)&b_y, tmp_size);
        period_min[b_i] = b_y;
        coder::internal::maximum(f0, (double *)&b_y, tmp_size);
        period_max[b_i] = b_y;
        coder::var(f0, (double *)&b_y, tmp_size);
        period_var[b_i] = b_y;
        FeatureTimeZeroCrossingRate(sig, wlen_tmp, inc, fs, vzc, a__2);
        zcr_m = 1.5 * coder::mean(vzc);
        b_x.set_size(1, vzc.size(1));
        loop_ub = vzc.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_x[i] = (vzc[i] > zcr_m);
        }
        vlen = b_x.size(1);
        if (b_x.size(1) == 0) {
            nx = 0;
        } else {
            nx = b_x[0];
            for (k = 2; k <= vlen; k++) {
                nx += b_x[k - 1];
            }
        }
        HZCRR[b_i] = static_cast<double>(nx) / static_cast<double>(vzc.size(1));
        inc = 0.25 * wlen_tmp;
        if (inc < 0.0) {
            inc = ceil(inc);
        } else {
            inc = floor(inc);
        }
        mfcc_m(sig, fs, wlen_tmp, inc, r8);
        ccc1.set_size(r8.size(0), r8.size(1));
        loop_ub = r8.size(0) * r8.size(1);
        for (i = 0; i < loop_ub; i++) {
            ccc1[i] = r8[i];
        }
        coder::combineVectorElements(ccc1, r7);
        varargin_5.set_size(r7.size(1));
        loop_ub = r7.size(1);
        for (i = 0; i < loop_ub; i++) {
            varargin_5[i] = r7[i] / static_cast<double>(ccc1.size(0));
        }
        for (i = 0; i < 16; i++) {
            mfcc_new[i + 16 * b_i] = varargin_5[i];
        }
        Crest_Factor[b_i] = CrestFactor(sig, fs);
        BARKenergy(sig, fs, b_dv, a__3, a__4);
        memcpy(&(*(double(*)[17]) & BARKEE[17 * b_i])[0], &b_dv[0],
               17U * sizeof(double));
        LPCFeature(sig, fs, a__5, LPC_mean, a__6, a__7, a__8);
        for (i = 0; i < 12; i++) {
            LPCmean[i + 12 * b_i] = LPC_mean[i];
        }
        PR800(sig, fs, &PR800mean[b_i], &PR800max[b_i], &PR800min[b_i],
              &PR800var[b_i]);
    }
    varargin_1.set_size(mfcc_new.size(1), 16);
    loop_ub = mfcc_new.size(1);
    for (i = 0; i < 16; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            varargin_1[i1 + varargin_1.size(0) * i] = mfcc_new[i + 16 * i1];
        }
    }
    varargin_2.set_size(BARKEE.size(1), 17);
    loop_ub = BARKEE.size(1);
    for (i = 0; i < 17; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            varargin_2[i1 + varargin_2.size(0) * i] = BARKEE[i + 17 * i1];
        }
    }
    varargin_3.set_size(LPCmean.size(1), 12);
    loop_ub = LPCmean.size(1);
    for (i = 0; i < 12; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            varargin_3[i1 + varargin_3.size(0) * i] = LPCmean[i + 12 * i1];
        }
    }
    y.set_size(period_mean.size(1));
    loop_ub = period_mean.size(1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = period_mean[i];
    }
    varargin_5.set_size(period_min.size(1));
    loop_ub = period_min.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_5[i] = period_min[i];
    }
    varargin_6.set_size(period_max.size(1));
    loop_ub = period_max.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_6[i] = period_max[i];
    }
    varargin_7.set_size(period_var.size(1));
    loop_ub = period_var.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_7[i] = period_var[i];
    }
    varargin_8.set_size(Crest_Factor.size(1));
    loop_ub = Crest_Factor.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_8[i] = Crest_Factor[i];
    }
    varargin_9.set_size(HZCRR.size(1));
    loop_ub = HZCRR.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_9[i] = HZCRR[i];
    }
    varargin_10.set_size(Eh.size(1));
    loop_ub = Eh.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_10[i] = Eh[i];
    }
    varargin_11.set_size(PR800mean.size(1));
    loop_ub = PR800mean.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_11[i] = PR800mean[i];
    }
    varargin_12.set_size(PR800max.size(1));
    loop_ub = PR800max.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_12[i] = PR800max[i];
    }
    varargin_13.set_size(PR800min.size(1));
    loop_ub = PR800min.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_13[i] = PR800min[i];
    }
    varargin_14.set_size(PR800var.size(1));
    loop_ub = PR800var.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_14[i] = PR800var[i];
    }
    if (varargin_1.size(0) != 0) {
        nx = varargin_1.size(0);
    } else if (varargin_2.size(0) != 0) {
        nx = varargin_2.size(0);
    } else if (varargin_3.size(0) != 0) {
        nx = varargin_3.size(0);
    } else if (y.size(0) != 0) {
        nx = y.size(0);
    } else if (varargin_5.size(0) != 0) {
        nx = varargin_5.size(0);
    } else if (varargin_6.size(0) != 0) {
        nx = varargin_6.size(0);
    } else if (varargin_7.size(0) != 0) {
        nx = varargin_7.size(0);
    } else if (varargin_8.size(0) != 0) {
        nx = varargin_8.size(0);
    } else if (varargin_9.size(0) != 0) {
        nx = varargin_9.size(0);
    } else if (varargin_10.size(0) != 0) {
        nx = varargin_10.size(0);
    } else if (varargin_11.size(0) != 0) {
        nx = varargin_11.size(0);
    } else if (varargin_12.size(0) != 0) {
        nx = varargin_12.size(0);
    } else if (varargin_13.size(0) != 0) {
        nx = varargin_13.size(0);
    } else if (varargin_14.size(0) != 0) {
        nx = varargin_14.size(0);
    } else {
        nx = 0;
    }
    empty_non_axis_sizes = (nx == 0);
    if (empty_non_axis_sizes || (varargin_1.size(0) != 0)) {
        input_sizes_idx_1 = 16;
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_2.size(0) != 0)) {
        b_input_sizes_idx_1 = 17;
    } else {
        b_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_3.size(0) != 0)) {
        c_input_sizes_idx_1 = 12;
    } else {
        c_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (y.size(0) != 0)) {
        d_input_sizes_idx_1 = 1;
    } else {
        d_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_5.size(0) != 0)) {
        e_input_sizes_idx_1 = 1;
    } else {
        e_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_6.size(0) != 0)) {
        f_input_sizes_idx_1 = 1;
    } else {
        f_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_7.size(0) != 0)) {
        g_input_sizes_idx_1 = 1;
    } else {
        g_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_8.size(0) != 0)) {
        h_input_sizes_idx_1 = 1;
    } else {
        h_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_9.size(0) != 0)) {
        i_input_sizes_idx_1 = 1;
    } else {
        i_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_10.size(0) != 0)) {
        j_input_sizes_idx_1 = 1;
    } else {
        j_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_11.size(0) != 0)) {
        k_input_sizes_idx_1 = 1;
    } else {
        k_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_12.size(0) != 0)) {
        l_input_sizes_idx_1 = 1;
    } else {
        l_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_13.size(0) != 0)) {
        m_input_sizes_idx_1 = 1;
    } else {
        m_input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (varargin_14.size(0) != 0)) {
        vlen = 1;
    } else {
        vlen = 0;
    }
    k = b_input_sizes_idx_1;
    feature1.set_size(nx, ((((((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                     c_input_sizes_idx_1) +
                                    d_input_sizes_idx_1) +
                                   e_input_sizes_idx_1) +
                                  f_input_sizes_idx_1) +
                                 g_input_sizes_idx_1) +
                                h_input_sizes_idx_1) +
                               i_input_sizes_idx_1) +
                              j_input_sizes_idx_1) +
                             k_input_sizes_idx_1) +
                            l_input_sizes_idx_1) +
                           m_input_sizes_idx_1) +
                              vlen);
    loop_ub = input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) * i] = varargin_1[i1 + nx * i];
        }
    }
    for (i = 0; i < k; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) * (i + input_sizes_idx_1)] =
                varargin_2[i1 + varargin_2.size(0) * i];
        }
    }
    loop_ub = c_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) *
                              ((i + input_sizes_idx_1) + b_input_sizes_idx_1)] =
                varargin_3[i1 + nx * i];
        }
    }
    loop_ub = d_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) *
                              ((input_sizes_idx_1 + b_input_sizes_idx_1) +
                               c_input_sizes_idx_1)] = y[i1];
        }
    }
    loop_ub = e_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) *
                              (((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                c_input_sizes_idx_1) +
                               d_input_sizes_idx_1)] = varargin_5[i1];
        }
    }
    loop_ub = f_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) *
                              ((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                 c_input_sizes_idx_1) +
                                d_input_sizes_idx_1) +
                               e_input_sizes_idx_1)] = varargin_6[i1];
        }
    }
    loop_ub = g_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) *
                              (((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                  c_input_sizes_idx_1) +
                                 d_input_sizes_idx_1) +
                                e_input_sizes_idx_1) +
                               f_input_sizes_idx_1)] = varargin_7[i1];
        }
    }
    loop_ub = h_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) *
                              ((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                   c_input_sizes_idx_1) +
                                  d_input_sizes_idx_1) +
                                 e_input_sizes_idx_1) +
                                f_input_sizes_idx_1) +
                               g_input_sizes_idx_1)] = varargin_8[i1];
        }
    }
    loop_ub = i_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) *
                              (((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                    c_input_sizes_idx_1) +
                                   d_input_sizes_idx_1) +
                                  e_input_sizes_idx_1) +
                                 f_input_sizes_idx_1) +
                                g_input_sizes_idx_1) +
                               h_input_sizes_idx_1)] = varargin_9[i1];
        }
    }
    loop_ub = j_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) *
                              ((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                     c_input_sizes_idx_1) +
                                    d_input_sizes_idx_1) +
                                   e_input_sizes_idx_1) +
                                  f_input_sizes_idx_1) +
                                 g_input_sizes_idx_1) +
                                h_input_sizes_idx_1) +
                               i_input_sizes_idx_1)] = varargin_10[i1];
        }
    }
    loop_ub = k_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) * (((((((((input_sizes_idx_1 +
                                                      b_input_sizes_idx_1) +
                                                     c_input_sizes_idx_1) +
                                                    d_input_sizes_idx_1) +
                                                   e_input_sizes_idx_1) +
                                                  f_input_sizes_idx_1) +
                                                 g_input_sizes_idx_1) +
                                                h_input_sizes_idx_1) +
                                               i_input_sizes_idx_1) +
                                              j_input_sizes_idx_1)] =
                varargin_11[i1];
        }
    }
    loop_ub = l_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 + feature1.size(0) * ((((((((((input_sizes_idx_1 +
                                                       b_input_sizes_idx_1) +
                                                      c_input_sizes_idx_1) +
                                                     d_input_sizes_idx_1) +
                                                    e_input_sizes_idx_1) +
                                                   f_input_sizes_idx_1) +
                                                  g_input_sizes_idx_1) +
                                                 h_input_sizes_idx_1) +
                                                i_input_sizes_idx_1) +
                                               j_input_sizes_idx_1) +
                                              k_input_sizes_idx_1)] =
                varargin_12[i1];
        }
    }
    loop_ub = m_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 +
                     feature1.size(0) *
                         (((((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                   c_input_sizes_idx_1) +
                                  d_input_sizes_idx_1) +
                                 e_input_sizes_idx_1) +
                                f_input_sizes_idx_1) +
                               g_input_sizes_idx_1) +
                              h_input_sizes_idx_1) +
                             i_input_sizes_idx_1) +
                            j_input_sizes_idx_1) +
                           k_input_sizes_idx_1) +
                          l_input_sizes_idx_1)] = varargin_13[i1];
        }
    }
    for (i = 0; i < vlen; i++) {
        for (i1 = 0; i1 < nx; i1++) {
            feature1[i1 +
                     feature1.size(0) *
                         ((((((((((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                                    c_input_sizes_idx_1) +
                                   d_input_sizes_idx_1) +
                                  e_input_sizes_idx_1) +
                                 f_input_sizes_idx_1) +
                                g_input_sizes_idx_1) +
                               h_input_sizes_idx_1) +
                              i_input_sizes_idx_1) +
                             j_input_sizes_idx_1) +
                            k_input_sizes_idx_1) +
                           l_input_sizes_idx_1) +
                          m_input_sizes_idx_1)] = varargin_14[i1];
        }
    }
    loop_ub = feature1.size(0);
    feature.set_size(feature1.size(0), 23);
    for (i = 0; i < 23; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            feature[i1 + feature.size(0) * i] =
                feature1[i1 + feature1.size(0) * (b_iv[i] - 1)];
        }
    }
    r9.init();
    r9.predict(feature, predict_label);
}
