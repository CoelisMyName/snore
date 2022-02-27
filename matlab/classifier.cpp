//
// File: classifier.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "classifier.h"
#include "BARKenergy.h"
#include "CompactClassificationEnsemble.h"
#include "CrestFactor.h"
#include "FeatureTimeZeroCrossingRate.h"
#include "HENR.h"
#include "LPCFeature.h"
#include "PR800.h"
#include "abs.h"
#include "combineVectorElements.h"
#include "fix.h"
#include "mean.h"
#include "mfcc_m.h"
#include "minOrMax.h"
#include "pitch.h"
#include "rt_nonfinite.h"
#include "var.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// function [predict_label] = classifier(x, fs, w_starts, w_ends)
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs
//                const coder::array<long long, 1U> &w_starts
//                const coder::array<long long, 1U> &w_ends
//                coder::array<double, 1U> &predict_label
// Return Type  : void
//
void classifier(const coder::array<double, 1U> &x, double fs,
                const coder::array<long long, 1U> &w_starts,
                const coder::array<long long, 1U> &w_ends,
                coder::array<double, 1U> &predict_label) {
    static const signed char b_iv[23] = {3, 18, 19, 1, 46, 47, 53, 34,
                                         50, 30, 31, 51, 33, 42, 54, 29,
                                         28, 32, 53, 7, 52, 27, 36};
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
    coder::array<double, 2U> r;
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
    coder::array<double, 1U> r1;
    coder::array<double, 1U> r2;
    coder::array<double, 1U> r3;
    coder::array<double, 1U> r4;
    coder::array<double, 1U> r5;
    coder::array<double, 1U> r6;
    coder::array<double, 1U> r7;
    coder::array<double, 1U> sig;
    coder::array<double, 1U> varargin_10;
    coder::array<double, 1U> varargin_11;
    coder::array<double, 1U> varargin_12;
    coder::array<double, 1U> varargin_13;
    coder::array<double, 1U> varargin_14;
    coder::array<double, 1U> varargin_4;
    coder::array<double, 1U> varargin_5;
    coder::array<double, 1U> varargin_6;
    coder::array<double, 1U> varargin_7;
    coder::array<double, 1U> varargin_8;
    coder::array<double, 1U> varargin_9;
    coder::array<boolean_T, 2U> b_vzc;
    double a__3[17];
    double a__4[17];
    double b_dv[17];
    double LPC_mean[12];
    double a__6[12];
    double a__7[12];
    double a__8[12];
    double N;
    double a__1;
    double maxval;
    double wlen_tmp;
    int tmp_size[2];
    int i;
    int i1;
    int loop_ub;
    int result;
    int result_idx_1_tmp;
    int sizes_idx_1;
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
    //  x(inf,1) w_starts(inf,1) w_ends(inf,1) fs(1,1) predict_label(1,1)
    // 'classifier:3' N = min(length(w_starts), length(w_ends));
    N = coder::internal::minimum2(static_cast<double>(w_starts.size(0)),
                                  static_cast<double>(w_ends.size(0)));
    // 'classifier:5' period_mean = zeros(1, N);
    period_mean.set_size(1, static_cast<int>(N));
    // 'classifier:6' period_min = zeros(1, N);
    period_min.set_size(1, static_cast<int>(N));
    // 'classifier:7' period_max = zeros(1, N);
    period_max.set_size(1, static_cast<int>(N));
    // 'classifier:8' period_var = zeros(1, N);
    period_var.set_size(1, static_cast<int>(N));
    // 'classifier:9' mfcc_new = zeros(16, N);
    mfcc_new.set_size(16, static_cast<int>(N));
    loop_ub = static_cast<int>(N) << 4;
    for (i = 0; i < loop_ub; i++) {
        mfcc_new[i] = 0.0;
    }
    // 'classifier:10' Crest_Factor = zeros(1, N);
    Crest_Factor.set_size(1, static_cast<int>(N));
    // 'classifier:11' HZCRR = zeros(1, N);
    HZCRR.set_size(1, static_cast<int>(N));
    // 'classifier:12' Eh = zeros(1, N);
    Eh.set_size(1, static_cast<int>(N));
    // 'classifier:13' BARKEE = zeros(17, N);
    BARKEE.set_size(17, static_cast<int>(N));
    // 'classifier:14' LPCmean = zeros(12, N);
    LPCmean.set_size(12, static_cast<int>(N));
    // 'classifier:15' PR800mean = zeros(1, N);
    PR800mean.set_size(1, static_cast<int>(N));
    // 'classifier:16' PR800max = zeros(1, N);
    PR800max.set_size(1, static_cast<int>(N));
    // 'classifier:17' PR800min = zeros(1, N);
    PR800min.set_size(1, static_cast<int>(N));
    // 'classifier:18' PR800var = zeros(1, N);
    PR800var.set_size(1, static_cast<int>(N));
    // 'classifier:20' for i = 1:N
    i = static_cast<int>(N);
    for (int b_i = 0; b_i < i; b_i++) {
        double zcr_m;
        // 'classifier:21' wlen = fix(0.02 * fs);
        wlen_tmp = 0.02 * fs;
        coder::b_fix(&wlen_tmp);
        // 'classifier:22' inc = fix(0.5 * wlen);
        // 'classifier:23' sig = x(w_starts(i):w_ends(i));
        if (w_starts[b_i] > w_ends[b_i]) {
            i1 = 0;
            result = 0;
        } else {
            i1 = static_cast<int>(w_starts[b_i]) - 1;
            result = static_cast<int>(w_ends[b_i]);
        }
        loop_ub = result - i1;
        sig.set_size(loop_ub);
        for (result = 0; result < loop_ub; result++) {
            sig[result] = x[i1 + result];
        }
        // 'classifier:24' sig = sig - mean(sig);
        maxval = coder::mean(sig);
        loop_ub = sig.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
            sig[i1] = sig[i1] - maxval;
        }
        // 'classifier:25' sig = sig / max(abs(sig));
        coder::b_abs(sig, varargin_4);
        maxval = coder::internal::maximum(varargin_4);
        loop_ub = sig.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
            sig[i1] = sig[i1] / maxval;
        }
        // 'classifier:26' sig1 = sig;
        // 'classifier:28' [Eh1, ~] = HENR(sig1, fs);
        HENR(sig, fs, &Eh[b_i], &a__1);
        // 'classifier:29' Eh(i) = Eh1;
        // 'classifier:30' f0 = [];
        f0.set_size(0, 0);
        //  适配Coder
        // 'classifier:32' switch fs
        switch (static_cast<int>(fs)) {
            case 8000:
                // 'classifier:33' case 8000
                // 'classifier:34' f0 = pitch(sig1, 8000, 'WindowLength', 400,
                // 'OverlapLength', 200);
                coder::pitch(sig, r1);
                b_f0.set_size(r1.size(0));
                loop_ub = r1.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    b_f0[i1] = r1[i1];
                }
                f0.set_size(b_f0.size(0), 1);
                loop_ub = b_f0.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    f0[i1] = b_f0[i1];
                }
                break;
            case 11025:
                // 'classifier:35' case 11025
                // 'classifier:36' f0 = pitch(sig1, 11025, 'WindowLength', 551,
                // 'OverlapLength', 276);
                coder::b_pitch(sig, r2);
                c_f0.set_size(r2.size(0));
                loop_ub = r2.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    c_f0[i1] = r2[i1];
                }
                f0.set_size(c_f0.size(0), 1);
                loop_ub = c_f0.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    f0[i1] = c_f0[i1];
                }
                break;
            case 12000:
                // 'classifier:37' case 12000
                // 'classifier:38' f0 = pitch(sig1, 12000, 'WindowLength', 600,
                // 'OverlapLength', 300);
                coder::c_pitch(sig, r3);
                d_f0.set_size(r3.size(0));
                loop_ub = r3.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    d_f0[i1] = r3[i1];
                }
                f0.set_size(d_f0.size(0), 1);
                loop_ub = d_f0.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    f0[i1] = d_f0[i1];
                }
                break;
            case 22050:
                // 'classifier:39' case 22050
                // 'classifier:40' f0 = pitch(sig1, 22050, 'WindowLength', 1103,
                // 'OverlapLength', 551);
                coder::d_pitch(sig, r4);
                e_f0.set_size(r4.size(0));
                loop_ub = r4.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    e_f0[i1] = r4[i1];
                }
                f0.set_size(e_f0.size(0), 1);
                loop_ub = e_f0.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    f0[i1] = e_f0[i1];
                }
                break;
            case 24000:
                // 'classifier:41' case 24000
                // 'classifier:42' f0 = pitch(sig1, 24000, 'WindowLength', 1200,
                // 'OverlapLength', 600);
                coder::e_pitch(sig, r5);
                f_f0.set_size(r5.size(0));
                loop_ub = r5.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    f_f0[i1] = r5[i1];
                }
                f0.set_size(f_f0.size(0), 1);
                loop_ub = f_f0.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    f0[i1] = f_f0[i1];
                }
                break;
            case 44100:
                // 'classifier:43' case 44100
                // 'classifier:44' f0 = pitch(sig1, 44100, 'WindowLength', 2205,
                // 'OverlapLength', 1103);
                coder::f_pitch(sig, r6);
                g_f0.set_size(r6.size(0));
                loop_ub = r6.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    g_f0[i1] = r6[i1];
                }
                f0.set_size(g_f0.size(0), 1);
                loop_ub = g_f0.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    f0[i1] = g_f0[i1];
                }
                break;
            case 48000:
                // 'classifier:45' case 48000
                // 'classifier:46' f0 = pitch(sig1, 48000, 'WindowLength', 2400,
                // 'OverlapLength', 1200);
                coder::g_pitch(sig, r7);
                h_f0.set_size(r7.size(0));
                loop_ub = r7.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    h_f0[i1] = r7[i1];
                }
                f0.set_size(h_f0.size(0), 1);
                loop_ub = h_f0.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    f0[i1] = h_f0[i1];
                }
                break;
        }
        // 'classifier:49' period_mean(i) = mean(f0);
        coder::mean(f0, r);
        period_mean[b_i] = r[0];
        // 计算基音周期的平均值
        // 'classifier:50' period_min(i) = min(f0);
        coder::internal::minimum(f0, (double *) &maxval, tmp_size);
        period_min[b_i] = maxval;
        // 计算基音周期的最小值
        // 'classifier:51' period_max(i) = max(f0);
        coder::internal::maximum(f0, (double *) &maxval, tmp_size);
        period_max[b_i] = maxval;
        // 计算基音周期的最大值
        // 'classifier:52' period_var(i) = var(f0);
        coder::var(f0, (double *) &maxval, tmp_size);
        period_var[b_i] = maxval;
        // 计算基音周期的方差
        // 'classifier:54' [vzc, ~] = FeatureTimeZeroCrossingRate(sig1, wlen,
        // inc, fs);
        maxval = 0.5 * wlen_tmp;
        coder::b_fix(&maxval);
        FeatureTimeZeroCrossingRate(sig, wlen_tmp, maxval, fs, vzc, a__2);
        // 'classifier:55' zcr_m = 1.5 * mean(vzc);
        zcr_m = 1.5 * coder::mean(vzc);
        // 'classifier:56' HZCRR(i) = sum(vzc > zcr_m) / length(vzc);
        b_vzc.set_size(1, vzc.size(1));
        loop_ub = vzc.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_vzc[i1] = (vzc[i1] > zcr_m);
        }
        HZCRR[b_i] =
                static_cast<double>(coder::b_combineVectorElements(b_vzc)) /
                static_cast<double>(vzc.size(1));
        // 'classifier:58' framesize = fix(0.02 * fs);
        // 帧长20ms，帧移0.25 使用这个
        // 'classifier:59' inc = fix(0.25 * framesize);
        // 'classifier:60' ccc1 = mfcc_m(sig1, fs, 16, framesize, inc);
        maxval = 0.25 * wlen_tmp;
        coder::b_fix(&maxval);
        mfcc_m(sig, fs, wlen_tmp, maxval, r8);
        ccc1.set_size(r8.size(0), r8.size(1));
        loop_ub = r8.size(0) * r8.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            ccc1[i1] = r8[i1];
        }
        // sig1
        // 'classifier:61' ccc = mean(ccc1)';
        // sig1
        // 'classifier:62' mfcc_new(:, i) = ccc;
        coder::mean(ccc1, r);
        varargin_5.set_size(r.size(1));
        loop_ub = r.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            varargin_5[i1] = r[i1];
        }
        for (i1 = 0; i1 < 16; i1++) {
            mfcc_new[i1 + 16 * b_i] = varargin_5[i1];
        }
        // 'classifier:64' [CF_mean] = CrestFactor(sig1, fs);
        Crest_Factor[b_i] = CrestFactor(sig, fs);
        // sig1
        // 'classifier:65' Crest_Factor(i) = CF_mean;
        // 'classifier:67' [BARK1, ~, ~] = BARKenergy(sig1, fs);
        BARKenergy(sig, fs, b_dv, a__3, a__4);
        memcpy(&(*(double (*)[17]) &BARKEE[17 * b_i])[0], &b_dv[0],
               17U * sizeof(double));
        //
        //  BARKse(:,i) =BPSE1;
        // 'classifier:69' BARKEE(:, i) = BARK1;
        // ----------------------提取LPC特征----------------------------
        // 'classifier:71' [~, LPC_mean, ~, ~, ~] = LPCFeature(sig1, fs);
        LPCFeature(sig, fs, a__5, LPC_mean, a__6, a__7, a__8);
        // 'classifier:72' LPCmean(:, i) = LPC_mean';
        for (i1 = 0; i1 < 12; i1++) {
            LPCmean[i1 + 12 * b_i] = LPC_mean[i1];
        }
        //  %---------------------PR800-----------------------------------
        // 'classifier:74' [PR800_mean, PR800_max, PR800_min, PR800_var] =
        // PR800(sig1, fs);
        PR800(sig, fs, &PR800mean[b_i], &PR800max[b_i], &PR800min[b_i],
              &PR800var[b_i]);
        // 'classifier:75' PR800mean(i) = PR800_mean;
        // 'classifier:76' PR800max(i) = PR800_max;
        // 'classifier:77' PR800min(i) = PR800_min;
        // 'classifier:78' PR800var(i) = PR800_var;
    }
    // 'classifier:81' feature1 = [mfcc_new', BARKEE', LPCmean', period_mean',
    // period_min', period_max', period_var', Crest_Factor', HZCRR', Eh',
    // PR800mean', PR800max', PR800min', PR800var'];
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
    varargin_4.set_size(period_mean.size(1));
    loop_ub = period_mean.size(1);
    for (i = 0; i < loop_ub; i++) {
        varargin_4[i] = period_mean[i];
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
        result = varargin_1.size(0);
    } else if (varargin_2.size(0) != 0) {
        result = varargin_2.size(0);
    } else if (varargin_3.size(0) != 0) {
        result = varargin_3.size(0);
    } else if (varargin_4.size(0) != 0) {
        result = varargin_4.size(0);
    } else if (varargin_5.size(0) != 0) {
        result = varargin_5.size(0);
    } else if (varargin_6.size(0) != 0) {
        result = varargin_6.size(0);
    } else if (varargin_7.size(0) != 0) {
        result = varargin_7.size(0);
    } else if (varargin_8.size(0) != 0) {
        result = varargin_8.size(0);
    } else if (varargin_9.size(0) != 0) {
        result = varargin_9.size(0);
    } else if (varargin_10.size(0) != 0) {
        result = varargin_10.size(0);
    } else if (varargin_11.size(0) != 0) {
        result = varargin_11.size(0);
    } else if (varargin_12.size(0) != 0) {
        result = varargin_12.size(0);
    } else if (varargin_13.size(0) != 0) {
        result = varargin_13.size(0);
    } else if (varargin_14.size(0) != 0) {
        result = varargin_14.size(0);
    } else {
        result = 0;
    }
    empty_non_axis_sizes = (result == 0);
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
    if (empty_non_axis_sizes || (varargin_4.size(0) != 0)) {
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
        sizes_idx_1 = 1;
    } else {
        sizes_idx_1 = 0;
    }
    result_idx_1_tmp = b_input_sizes_idx_1;
    feature1.set_size(result,
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
                       m_input_sizes_idx_1) +
                      sizes_idx_1);
    loop_ub = input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature1[i1 + feature1.size(0) * i] = varargin_1[i1 + result * i];
        }
    }
    for (i = 0; i < result_idx_1_tmp; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature1[i1 + feature1.size(0) * (i + input_sizes_idx_1)] =
                    varargin_2[i1 + varargin_2.size(0) * i];
        }
    }
    loop_ub = c_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature1[i1 + feature1.size(0) *
                          ((i + input_sizes_idx_1) + b_input_sizes_idx_1)] =
                    varargin_3[i1 + result * i];
        }
    }
    loop_ub = d_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature1[i1 + feature1.size(0) *
                          ((input_sizes_idx_1 + b_input_sizes_idx_1) +
                           c_input_sizes_idx_1)] = varargin_4[i1];
        }
    }
    loop_ub = e_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature1[i1 + feature1.size(0) *
                          (((input_sizes_idx_1 + b_input_sizes_idx_1) +
                            c_input_sizes_idx_1) +
                           d_input_sizes_idx_1)] = varargin_5[i1];
        }
    }
    loop_ub = f_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < result; i1++) {
            feature1[i1 + feature1.size(0) *
                          ((((input_sizes_idx_1 + b_input_sizes_idx_1) +
                             c_input_sizes_idx_1) +
                            d_input_sizes_idx_1) +
                           e_input_sizes_idx_1)] = varargin_6[i1];
        }
    }
    loop_ub = g_input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < result; i1++) {
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
        for (i1 = 0; i1 < result; i1++) {
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
        for (i1 = 0; i1 < result; i1++) {
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
        for (i1 = 0; i1 < result; i1++) {
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
        for (i1 = 0; i1 < result; i1++) {
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
        for (i1 = 0; i1 < result; i1++) {
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
        for (i1 = 0; i1 < result; i1++) {
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
    for (i = 0; i < sizes_idx_1; i++) {
        for (i1 = 0; i1 < result; i1++) {
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
    // 'classifier:83' feature = feature1(:, [3, 18, 19, 1, 46, 47, 53, 34, 50,
    // 30, 31, 51, 33, 42, 54, 29, 28, 32, 53, 7, 52, 27, 36]);
    loop_ub = feature1.size(0);
    feature.set_size(feature1.size(0), 23);
    for (i = 0; i < 23; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            feature[i1 + feature.size(0) * i] =
                    feature1[i1 + feature1.size(0) * (b_iv[i] - 1)];
        }
    }
    // 'classifier:84' my_model = loadLearnerForCoder('compacted_model');
    // 'classifier:85' predict_label = predict(my_model, feature);
    r9.init();
    r9.predict(feature, predict_label);
}

//
// File trailer for classifier.cpp
//
// [EOF]
//
