//
// File: se_feat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "se_feat.h"
#include "ceil.h"
#include "fix.h"
#include "mean.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "spectralEntropy.h"
#include "var.h"
#include "coder_array.h"

// Function Definitions
//
// function [SE_mean, SE_max, SE_min, SE_var] = se_feat(sig, fs)
//
// Arguments    : const coder::array<double, 1U> &sig
//                double fs
//                double *SE_mean
//                double *SE_max
//                double *SE_min
//                double *SE_var
// Return Type  : void
//
void se_feat(const coder::array<double, 1U> &sig, double fs, double *SE_mean,
             double *SE_max, double *SE_min, double *SE_var) {
    coder::array<double, 2U> SE;
    coder::array<double, 1U> b_SE;
    double d;
    double inc;
    int i;
    int loop_ub_tmp;
    // 'se_feat:2' wlen = fix(0.02 * fs);
    // 'se_feat:3' inc = fix(0.5 * wlen);
    d = 0.02 * fs;
    coder::b_fix(&d);
    inc = 0.5 * d;
    coder::b_fix(&inc);
    // 'se_feat:4' SE = zeros(1, ceil(length(sig) / inc));
    d = static_cast<double>(sig.size(0)) / inc;
    coder::b_ceil(&d);
    loop_ub_tmp = static_cast<int>(d);
    SE.set_size(1, loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        SE[i] = 0.0;
    }
    // 'se_feat:5' switch fs
    switch (static_cast<int>(fs)) {
        case 8000:
            // 'se_feat:6' case 8000
            // 'se_feat:7' SE = spectralEntropy(sig, 8000, 'Window', hanning(160),
            // 'OverlapLength', 80);
            coder::spectralEntropy(sig, b_SE);
            SE.set_size(b_SE.size(0), 1);
            loop_ub_tmp = b_SE.size(0);
            for (i = 0; i < loop_ub_tmp; i++) {
                SE[i] = b_SE[i];
            }
            break;
        case 11025:
            // 'se_feat:8' case 11025
            // 'se_feat:9' SE = spectralEntropy(sig, 11025, 'Window', hanning(221),
            // 'OverlapLength', 110);
            coder::b_spectralEntropy(sig, b_SE);
            SE.set_size(b_SE.size(0), 1);
            loop_ub_tmp = b_SE.size(0);
            for (i = 0; i < loop_ub_tmp; i++) {
                SE[i] = b_SE[i];
            }
            break;
        case 12000:
            // 'se_feat:10' case 12000
            // 'se_feat:11' SE = spectralEntropy(sig, 12000, 'Window', hanning(240),
            // 'OverlapLength', 120);
            coder::c_spectralEntropy(sig, b_SE);
            SE.set_size(b_SE.size(0), 1);
            loop_ub_tmp = b_SE.size(0);
            for (i = 0; i < loop_ub_tmp; i++) {
                SE[i] = b_SE[i];
            }
            break;
        case 22050:
            // 'se_feat:12' case 22050
            // 'se_feat:13' SE = spectralEntropy(sig, 22050, 'Window', hanning(441),
            // 'OverlapLength', 221);
            coder::d_spectralEntropy(sig, b_SE);
            SE.set_size(b_SE.size(0), 1);
            loop_ub_tmp = b_SE.size(0);
            for (i = 0; i < loop_ub_tmp; i++) {
                SE[i] = b_SE[i];
            }
            break;
        case 24000:
            // 'se_feat:14' case 24000
            // 'se_feat:15' SE = spectralEntropy(sig, 24000, 'Window', hanning(480),
            // 'OverlapLength', 240);
            coder::e_spectralEntropy(sig, b_SE);
            SE.set_size(b_SE.size(0), 1);
            loop_ub_tmp = b_SE.size(0);
            for (i = 0; i < loop_ub_tmp; i++) {
                SE[i] = b_SE[i];
            }
            break;
        case 44100:
            // 'se_feat:16' case 44100
            // 'se_feat:17' SE = spectralEntropy(sig, 44100, 'Window', hanning(882),
            // 'OverlapLength', 441);
            coder::f_spectralEntropy(sig, b_SE);
            SE.set_size(b_SE.size(0), 1);
            loop_ub_tmp = b_SE.size(0);
            for (i = 0; i < loop_ub_tmp; i++) {
                SE[i] = b_SE[i];
            }
            break;
        case 48000:
            // 'se_feat:18' case 48000
            // 'se_feat:19' SE = spectralEntropy(sig, 48000, 'Window', hanning(960),
            // 'OverlapLength', 480);
            coder::g_spectralEntropy(sig, b_SE);
            SE.set_size(b_SE.size(0), 1);
            loop_ub_tmp = b_SE.size(0);
            for (i = 0; i < loop_ub_tmp; i++) {
                SE[i] = b_SE[i];
            }
            break;
    }
    // 'se_feat:21' SE_mean = mean(SE(:));
    loop_ub_tmp = SE.size(0) * SE.size(1);
    b_SE = SE.reshape(loop_ub_tmp);
    *SE_mean = coder::mean(b_SE);
    // 'se_feat:22' SE_max = max(SE(:));
    loop_ub_tmp = SE.size(0) * SE.size(1);
    b_SE = SE.reshape(loop_ub_tmp);
    *SE_max = coder::internal::maximum(b_SE);
    // 'se_feat:23' SE_min = min(SE(:));
    loop_ub_tmp = SE.size(0) * SE.size(1);
    b_SE = SE.reshape(loop_ub_tmp);
    *SE_min = coder::internal::minimum(b_SE);
    // 'se_feat:24' SE_var = var(SE(:));
    loop_ub_tmp = SE.size(0) * SE.size(1);
    b_SE = SE.reshape(loop_ub_tmp);
    *SE_var = coder::var(b_SE);
}

//
// File trailer for se_feat.cpp
//
// [EOF]
//
