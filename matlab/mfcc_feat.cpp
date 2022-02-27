//
// File: mfcc_feat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "mfcc_feat.h"
#include "mean.h"
#include "mfcc.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function MFCC_feature = mfcc_feat(sig, fs)
//
// Arguments    : const coder::array<double, 1U> &sig
//                double fs
//                coder::array<double, 2U> &MFCC_feature
// Return Type  : void
//
void mfcc_feat(const coder::array<double, 1U> &sig, double fs,
               coder::array<double, 2U> &MFCC_feature) {
    coder::array<double, 2U> coeffs;
    coder::array<double, 2U> delta;
    coder::array<double, 2U> deltaDelta;
    coder::array<double, 2U> r;
    coder::array<double, 2U> r1;
    coder::array<double, 2U> r2;
    coder::array<double, 1U> a__1;
    int i;
    int loop_ub;
    // 'mfcc_feat:2' [coeffs, delta, deltaDelta, ~] = mfcc(sig, fs, 'LogEnergy',
    // 'Replace');
    coder::mfcc(sig, fs, coeffs, delta, deltaDelta, a__1);
    // 'mfcc_feat:3' coeffs_ = mean(coeffs);
    // 'mfcc_feat:4' delta_ = mean(delta);
    // 'mfcc_feat:5' deltaDelta_ = mean(deltaDelta);
    // 'mfcc_feat:6' MFCC_feature = [coeffs_, delta_, deltaDelta_];
    coder::mean(coeffs, r);
    coder::mean(delta, r1);
    coder::mean(deltaDelta, r2);
    MFCC_feature.set_size(1, (r.size(1) + r1.size(1)) + r2.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
        MFCC_feature[i] = r[i];
    }
    loop_ub = r1.size(1);
    for (i = 0; i < loop_ub; i++) {
        MFCC_feature[i + r.size(1)] = r1[i];
    }
    loop_ub = r2.size(1);
    for (i = 0; i < loop_ub; i++) {
        MFCC_feature[(i + r.size(1)) + r1.size(1)] = r2[i];
    }
}

//
// File trailer for mfcc_feat.cpp
//
// [EOF]
//
