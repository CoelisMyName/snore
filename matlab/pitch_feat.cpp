//
// File: pitch_feat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "pitch_feat.h"
#include "mean.h"
#include "minOrMax.h"
#include "pitch.h"
#include "rt_nonfinite.h"
#include "var.h"
#include "coder_array.h"

// Function Definitions
//
// function [period_mean, period_min, period_max, period_var] = pitch_feat(sig,
// fs)
//
// Arguments    : const coder::array<double, 1U> &sig
//                double fs
//                double *period_mean
//                double *period_min
//                double *period_max
//                double *period_var
// Return Type  : void
//
void pitch_feat(const coder::array<double, 1U> &sig, double fs,
                double *period_mean, double *period_min, double *period_max,
                double *period_var) {
    coder::array<double, 1U> f0;
    coder::array<double, 1U> r;
    // 'pitch_feat:2' f0 = [0];
    f0.set_size(1);
    f0[0] = 0.0;
    //  适配Coder
    // 'pitch_feat:4' switch fs
    switch (static_cast<int>(fs)) {
        case 8000: {
            int loop_ub;
            // 'pitch_feat:5' case 8000
            // 'pitch_feat:6' f0 = pitch(sig, 8000, 'WindowLength', 400,
            // 'OverlapLength', 200);
            coder::pitch(sig, r);
            f0.set_size(r.size(0));
            loop_ub = r.size(0);
            for (int i = 0; i < loop_ub; i++) {
                f0[i] = r[i];
            }
        }
            break;
        case 11025: {
            int loop_ub;
            // 'pitch_feat:7' case 11025
            // 'pitch_feat:8' f0 = pitch(sig, 11025, 'WindowLength', 551,
            // 'OverlapLength', 276);
            coder::b_pitch(sig, r);
            f0.set_size(r.size(0));
            loop_ub = r.size(0);
            for (int i = 0; i < loop_ub; i++) {
                f0[i] = r[i];
            }
        }
            break;
        case 12000: {
            int loop_ub;
            // 'pitch_feat:9' case 12000
            // 'pitch_feat:10' f0 = pitch(sig, 12000, 'WindowLength', 600,
            // 'OverlapLength', 300);
            coder::c_pitch(sig, r);
            f0.set_size(r.size(0));
            loop_ub = r.size(0);
            for (int i = 0; i < loop_ub; i++) {
                f0[i] = r[i];
            }
        }
            break;
        case 22050: {
            int loop_ub;
            // 'pitch_feat:11' case 22050
            // 'pitch_feat:12' f0 = pitch(sig, 22050, 'WindowLength', 1103,
            // 'OverlapLength', 551);
            coder::d_pitch(sig, r);
            f0.set_size(r.size(0));
            loop_ub = r.size(0);
            for (int i = 0; i < loop_ub; i++) {
                f0[i] = r[i];
            }
        }
            break;
        case 24000: {
            int loop_ub;
            // 'pitch_feat:13' case 24000
            // 'pitch_feat:14' f0 = pitch(sig, 24000, 'WindowLength', 1200,
            // 'OverlapLength', 600);
            coder::e_pitch(sig, r);
            f0.set_size(r.size(0));
            loop_ub = r.size(0);
            for (int i = 0; i < loop_ub; i++) {
                f0[i] = r[i];
            }
        }
            break;
        case 44100: {
            int loop_ub;
            // 'pitch_feat:15' case 44100
            // 'pitch_feat:16' f0 = pitch(sig, 44100, 'WindowLength', 2205,
            // 'OverlapLength', 1103);
            coder::f_pitch(sig, r);
            f0.set_size(r.size(0));
            loop_ub = r.size(0);
            for (int i = 0; i < loop_ub; i++) {
                f0[i] = r[i];
            }
        }
            break;
        case 48000: {
            int loop_ub;
            // 'pitch_feat:17' case 48000
            // 'pitch_feat:18' f0 = pitch(sig, 48000, 'WindowLength', 2400,
            // 'OverlapLength', 1200);
            coder::g_pitch(sig, r);
            f0.set_size(r.size(0));
            loop_ub = r.size(0);
            for (int i = 0; i < loop_ub; i++) {
                f0[i] = r[i];
            }
        }
            break;
    }
    // 'pitch_feat:20' period_mean = mean(f0);
    *period_mean = coder::mean(f0);
    // 计算基音周期的平均值
    // 'pitch_feat:21' period_min = min(f0);
    *period_min = coder::internal::minimum(f0);
    // 计算基音周期的最小值
    // 'pitch_feat:22' period_max = max(f0);
    *period_max = coder::internal::maximum(f0);
    // 计算基音周期的最大值
    // 'pitch_feat:23' period_var = var(f0);
    *period_var = coder::var(f0);
    // 计算基音周期的方差
}

//
// File trailer for pitch_feat.cpp
//
// [EOF]
//
