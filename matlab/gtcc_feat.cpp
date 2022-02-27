//
// File: gtcc_feat.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "gtcc_feat.h"
#include "SnoringRecognition_types.h"
#include "ceil.h"
#include "gtcc.h"
#include "mean.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function GTCCmean = gtcc_feat(sig, fs)
//
// Arguments    : SnoringRecognitionStackData *SD
//                const coder::array<double, 1U> &sig
//                double fs
//                coder::array<double, 2U> &GTCCmean
// Return Type  : void
//
void gtcc_feat(SnoringRecognitionStackData *SD,
               const coder::array<double, 1U> &sig, double fs,
               coder::array<double, 2U> &GTCCmean) {
    coder::array<double, 2U> a__1;
    coder::array<double, 2U> a__10;
    coder::array<double, 2U> a__11;
    coder::array<double, 2U> a__13;
    coder::array<double, 2U> a__14;
    coder::array<double, 2U> a__16;
    coder::array<double, 2U> a__17;
    coder::array<double, 2U> a__19;
    coder::array<double, 2U> a__2;
    coder::array<double, 2U> a__20;
    coder::array<double, 2U> a__4;
    coder::array<double, 2U> a__5;
    coder::array<double, 2U> a__7;
    coder::array<double, 2U> a__8;
    coder::array<double, 2U> b_coeffs;
    coder::array<double, 2U> coeffs;
    coder::array<double, 1U> a__12;
    coder::array<double, 1U> a__15;
    coder::array<double, 1U> a__18;
    coder::array<double, 1U> a__21;
    coder::array<double, 1U> a__3;
    coder::array<double, 1U> a__6;
    coder::array<double, 1U> a__9;
    double maxval;
    int i;
    int loop_ub;
    // 'gtcc_feat:2' coeffs = zeros(max(ceil(length(sig) / (0.01 * fs)),20),
    // 20);
    maxval = static_cast<double>(sig.size(0)) / (0.01 * fs);
    coder::b_ceil(&maxval);
    maxval = coder::internal::maximum2(maxval, 20.0);
    coeffs.set_size(static_cast<int>(maxval), 20);
    loop_ub = static_cast<int>(maxval) * 20;
    for (i = 0; i < loop_ub; i++) {
        coeffs[i] = 0.0;
    }
    // 'gtcc_feat:3' switch fs
    switch (static_cast<int>(fs)) {
        case 8000:
            // 'gtcc_feat:4' case 8000
            // 'gtcc_feat:5' [coeffs, ~, ~, ~] = gtcc(sig, 8000, 'NumCoeffs',
            // 20,'Window', hann(160),... 'gtcc_feat:6'             'OverlapLength',
            // 80, 'LogEnergy', 'Replace','FilterDomain', 'Time');
            coder::gtcc(sig, b_coeffs, a__1, a__2, a__3);
            coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
            loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
            for (i = 0; i < loop_ub; i++) {
                coeffs[i] = b_coeffs[i];
            }
            break;
        case 11025:
            // 'gtcc_feat:7' case 11025
            // 'gtcc_feat:8' [coeffs, ~, ~, ~] = gtcc(sig, 11025, 'NumCoeffs',
            // 20,'Window', hann(221),... 'gtcc_feat:9' 'OverlapLength',
            // 110,'LogEnergy', 'Replace','FilterDomain', 'Time');
            coder::b_gtcc(sig, b_coeffs, a__4, a__5, a__6);
            coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
            loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
            for (i = 0; i < loop_ub; i++) {
                coeffs[i] = b_coeffs[i];
            }
            break;
        case 12000:
            // 'gtcc_feat:10' case 12000
            // 'gtcc_feat:11' [coeffs, ~, ~, ~] = gtcc(sig, 12000, 'NumCoeffs',
            // 20,'Window', hann(240),... 'gtcc_feat:12' 'OverlapLength',
            // 120,'LogEnergy', 'Replace','FilterDomain', 'Time');
            coder::c_gtcc(sig, b_coeffs, a__7, a__8, a__9);
            coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
            loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
            for (i = 0; i < loop_ub; i++) {
                coeffs[i] = b_coeffs[i];
            }
            break;
        case 22050:
            // 'gtcc_feat:13' case 22050
            // 'gtcc_feat:14' [coeffs, ~, ~, ~] = gtcc(sig, 22050, 'NumCoeffs',
            // 20,'Window', hann(441),... 'gtcc_feat:15' 'OverlapLength',
            // 221,'LogEnergy', 'Replace','FilterDomain', 'Time');
            coder::gtcc(SD, sig, b_coeffs, a__10, a__11, a__12);
            coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
            loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
            for (i = 0; i < loop_ub; i++) {
                coeffs[i] = b_coeffs[i];
            }
            break;
        case 24000:
            // 'gtcc_feat:16' case 24000
            // 'gtcc_feat:17' [coeffs, ~, ~, ~] = gtcc(sig, 24000, 'NumCoeffs',
            // 20,'Window', hann(480),... 'gtcc_feat:18' 'OverlapLength',
            // 240,'LogEnergy', 'Replace','FilterDomain', 'Time');
            coder::b_gtcc(SD, sig, b_coeffs, a__13, a__14, a__15);
            coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
            loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
            for (i = 0; i < loop_ub; i++) {
                coeffs[i] = b_coeffs[i];
            }
            break;
        case 44100:
            // 'gtcc_feat:19' case 44100
            // 'gtcc_feat:20' [coeffs, ~, ~, ~] = gtcc(sig, 44100, 'NumCoeffs',
            // 20,'Window', hann(882),... 'gtcc_feat:21' 'OverlapLength',
            // 441,'LogEnergy', 'Replace','FilterDomain', 'Time');
            coder::c_gtcc(SD, sig, b_coeffs, a__16, a__17, a__18);
            coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
            loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
            for (i = 0; i < loop_ub; i++) {
                coeffs[i] = b_coeffs[i];
            }
            break;
        case 48000:
            // 'gtcc_feat:22' case 48000
            // 'gtcc_feat:23' [coeffs, ~, ~, ~] = gtcc(sig, 48000, 'NumCoeffs',
            // 20,'Window', hann(960),... 'gtcc_feat:24' 'OverlapLength',
            // 480,'LogEnergy', 'Replace','FilterDomain', 'Time');
            coder::d_gtcc(SD, sig, b_coeffs, a__19, a__20, a__21);
            coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
            loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
            for (i = 0; i < loop_ub; i++) {
                coeffs[i] = b_coeffs[i];
            }
            break;
    }
    // 'gtcc_feat:26' GTCCmean = mean(coeffs);
    coder::mean(coeffs, GTCCmean);
}

//
// File trailer for gtcc_feat.cpp
//
// [EOF]
//
