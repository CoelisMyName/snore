#include "gtcc_feat.h"
#include "SnoringRecognition_types.h"
#include "combineVectorElements.h"
#include "gtcc.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include <math.h>

void gtcc_feat(SnoringRecognitionStackData *SD,
               const coder::array<double, 1U> &sig, double fs,
               coder::array<double, 2U> &GTCCmean)
{
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
    coder::array<double, 2U> r;
    coder::array<double, 1U> a__12;
    coder::array<double, 1U> a__15;
    coder::array<double, 1U> a__18;
    coder::array<double, 1U> a__21;
    coder::array<double, 1U> a__3;
    coder::array<double, 1U> a__6;
    coder::array<double, 1U> a__9;
    double u0;
    int i;
    int loop_ub;
    u0 = ceil(static_cast<double>(sig.size(0)) / (0.01 * fs));
    if (!(u0 > 20.0)) {
        u0 = 20.0;
    }
    coeffs.set_size(static_cast<int>(u0), 20);
    loop_ub = static_cast<int>(u0) * 20;
    for (i = 0; i < loop_ub; i++) {
        coeffs[i] = 0.0;
    }
    switch (static_cast<int>(fs)) {
    case 8000:
        coder::gtcc(sig, b_coeffs, a__1, a__2, a__3);
        coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
        loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
        for (i = 0; i < loop_ub; i++) {
            coeffs[i] = b_coeffs[i];
        }
        break;
    case 11025:
        coder::b_gtcc(sig, b_coeffs, a__4, a__5, a__6);
        coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
        loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
        for (i = 0; i < loop_ub; i++) {
            coeffs[i] = b_coeffs[i];
        }
        break;
    case 12000:
        coder::c_gtcc(sig, b_coeffs, a__7, a__8, a__9);
        coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
        loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
        for (i = 0; i < loop_ub; i++) {
            coeffs[i] = b_coeffs[i];
        }
        break;
    case 22050:
        coder::gtcc(SD, sig, b_coeffs, a__10, a__11, a__12);
        coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
        loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
        for (i = 0; i < loop_ub; i++) {
            coeffs[i] = b_coeffs[i];
        }
        break;
    case 24000:
        coder::b_gtcc(SD, sig, b_coeffs, a__13, a__14, a__15);
        coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
        loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
        for (i = 0; i < loop_ub; i++) {
            coeffs[i] = b_coeffs[i];
        }
        break;
    case 44100:
        coder::c_gtcc(SD, sig, b_coeffs, a__16, a__17, a__18);
        coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
        loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
        for (i = 0; i < loop_ub; i++) {
            coeffs[i] = b_coeffs[i];
        }
        break;
    case 48000:
        coder::d_gtcc(SD, sig, b_coeffs, a__19, a__20, a__21);
        coeffs.set_size(b_coeffs.size(0), b_coeffs.size(1));
        loop_ub = b_coeffs.size(0) * b_coeffs.size(1);
        for (i = 0; i < loop_ub; i++) {
            coeffs[i] = b_coeffs[i];
        }
        break;
    }
    coder::combineVectorElements(coeffs, r);
    GTCCmean.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
        GTCCmean[i] = r[i] / static_cast<double>(coeffs.size(0));
    }
}
