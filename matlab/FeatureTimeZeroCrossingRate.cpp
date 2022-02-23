//
// File: FeatureTimeZeroCrossingRate.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "FeatureTimeZeroCrossingRate.h"
#include "abs.h"
#include "ceil.h"
#include "diff.h"
#include "isinf.h"
#include "isnan.h"
#include "mean.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sign.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// function [vzc, t] = FeatureTimeZeroCrossingRate(x, iBlockLength, iHopLength,
// f_s)
//
// number of results
//
// Arguments    : const coder::array<double, 1U> &x
//                double iBlockLength
//                double iHopLength
//                double f_s
//                coder::array<double, 2U> &vzc
//                coder::array<double, 2U> &t
// Return Type  : void
//
void FeatureTimeZeroCrossingRate(const coder::array<double, 1U> &x,
                                 double iBlockLength, double iHopLength,
                                 double f_s, coder::array<double, 2U> &vzc,
                                 coder::array<double, 2U> &t) {
    coder::array<double, 1U> r;
    coder::array<double, 1U> r1;
    double iNumOfBlocks;
    double i_stop;
    int i;
    int loop_ub;
    //  ======================================================================
    // > @brief computes the zero crossing rate from a time domain signal
    // > called by ::ComputeFeature
    // >
    // > @param x: audio signal
    // > @param iBlockLength: block length in samples
    // > @param iHopLength: hop length in samples
    // > @param f_s: sample rate of audio data (unused)
    // >
    // > @retval vzc zero crossing rate
    // > @retval t time stamp
    //  ======================================================================
    // 'FeatureTimeZeroCrossingRate:16' iNumOfBlocks = ceil (length(x) /
    // iHopLength);
    iNumOfBlocks = static_cast<double>(x.size(0)) / iHopLength;
    coder::b_ceil(&iNumOfBlocks);
    //  compute time stamps
    // 'FeatureTimeZeroCrossingRate:19' t = ((0:iNumOfBlocks - 1) * iHopLength +
    // (iBlockLength / 2)) / f_s;
    if (coder::b_isnan(iNumOfBlocks - 1.0)) {
        t.set_size(1, 1);
        t[0] = rtNaN;
    } else if (iNumOfBlocks - 1.0 < 0.0) {
        t.set_size(t.size(0), 0);
    } else if (coder::b_isinf(iNumOfBlocks - 1.0) &&
               (0.0 == iNumOfBlocks - 1.0)) {
        t.set_size(1, 1);
        t[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(iNumOfBlocks - 1.0));
        t.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            t[i] = i;
        }
    }
    t.set_size(1, t.size(1));
    i_stop = iBlockLength / 2.0;
    loop_ub = t.size(1) - 1;
    for (i = 0; i <= loop_ub; i++) {
        t[i] = (t[i] * iHopLength + i_stop) / f_s;
    }
    //  allocate memory
    // 'FeatureTimeZeroCrossingRate:22' vzc = zeros(1, iNumOfBlocks);
    i = static_cast<int>(iNumOfBlocks);
    vzc.set_size(1, i);
    // 'FeatureTimeZeroCrossingRate:24' for (n = 1:iNumOfBlocks
    for (int n = 0; n < i; n++) {
        int i1;
        int i2;
        // 'FeatureTimeZeroCrossingRate:25' i_start = (n - 1) * iHopLength + 1;
        iNumOfBlocks = ((static_cast<double>(n) + 1.0) - 1.0) * iHopLength + 1.0;
        // 'FeatureTimeZeroCrossingRate:26' i_stop = min(length(x), i_start +
        // iBlockLength - 1);
        i_stop = coder::internal::minimum2(static_cast<double>(x.size(0)),
                                           (iNumOfBlocks + iBlockLength) - 1.0);
        //  compute the zero crossing rate
        // 'FeatureTimeZeroCrossingRate:29' vzc(n) = 0.5 *
        // mean(abs(diff(sign(x(i_start:i_stop)))));
        if (iNumOfBlocks > i_stop) {
            i1 = 0;
            i2 = 0;
        } else {
            i1 = static_cast<int>(iNumOfBlocks) - 1;
            i2 = static_cast<int>(i_stop);
        }
        loop_ub = i2 - i1;
        r.set_size(loop_ub);
        for (i2 = 0; i2 < loop_ub; i2++) {
            r[i2] = x[i1 + i2];
        }
        coder::b_sign(r);
        coder::diff(r, r1);
        coder::b_abs(r1, r);
        vzc[n] = 0.5 * coder::mean(r);
    }
}

//
// File trailer for FeatureTimeZeroCrossingRate.cpp
//
// [EOF]
//
