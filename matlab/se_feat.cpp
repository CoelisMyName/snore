#include "se_feat.h"
#include "blockedSummation.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "spectralEntropy.h"
#include "vvarstd.h"
#include "coder_array.h"
#include <math.h>

void se_feat(const coder::array<double, 1U> &sig, double fs, double *SE_mean,
             double *SE_max, double *SE_min, double *SE_var)
{
    coder::array<double, 2U> SE;
    coder::array<double, 1U> b_SE;
    double inc;
    double wlen;
    double x;
    int i;
    int loop_ub_tmp;
    wlen = 0.02 * fs;
    if (wlen < 0.0) {
        wlen = ceil(wlen);
    } else {
        wlen = floor(wlen);
    }
    inc = 0.5 * wlen;
    if (inc < 0.0) {
        inc = ceil(inc);
    } else {
        inc = floor(inc);
    }
    x = ceil(static_cast<double>(sig.size(0)) / inc);
    loop_ub_tmp = static_cast<int>(x);
    SE.set_size(1, loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        SE[i] = 0.0;
    }
    switch (static_cast<int>(fs)) {
    case 8000:
        coder::spectralEntropy(sig, b_SE);
        SE.set_size(b_SE.size(0), 1);
        loop_ub_tmp = b_SE.size(0);
        for (i = 0; i < loop_ub_tmp; i++) {
            SE[i] = b_SE[i];
        }
        break;
    case 11025:
        coder::b_spectralEntropy(sig, b_SE);
        SE.set_size(b_SE.size(0), 1);
        loop_ub_tmp = b_SE.size(0);
        for (i = 0; i < loop_ub_tmp; i++) {
            SE[i] = b_SE[i];
        }
        break;
    case 12000:
        coder::c_spectralEntropy(sig, b_SE);
        SE.set_size(b_SE.size(0), 1);
        loop_ub_tmp = b_SE.size(0);
        for (i = 0; i < loop_ub_tmp; i++) {
            SE[i] = b_SE[i];
        }
        break;
    case 22050:
        coder::d_spectralEntropy(sig, b_SE);
        SE.set_size(b_SE.size(0), 1);
        loop_ub_tmp = b_SE.size(0);
        for (i = 0; i < loop_ub_tmp; i++) {
            SE[i] = b_SE[i];
        }
        break;
    case 24000:
        coder::e_spectralEntropy(sig, b_SE);
        SE.set_size(b_SE.size(0), 1);
        loop_ub_tmp = b_SE.size(0);
        for (i = 0; i < loop_ub_tmp; i++) {
            SE[i] = b_SE[i];
        }
        break;
    case 44100:
        coder::f_spectralEntropy(sig, b_SE);
        SE.set_size(b_SE.size(0), 1);
        loop_ub_tmp = b_SE.size(0);
        for (i = 0; i < loop_ub_tmp; i++) {
            SE[i] = b_SE[i];
        }
        break;
    case 48000:
        coder::g_spectralEntropy(sig, b_SE);
        SE.set_size(b_SE.size(0), 1);
        loop_ub_tmp = b_SE.size(0);
        for (i = 0; i < loop_ub_tmp; i++) {
            SE[i] = b_SE[i];
        }
        break;
    }
    loop_ub_tmp = SE.size(0) * SE.size(1);
    b_SE = SE.reshape(loop_ub_tmp);
    *SE_mean = coder::blockedSummation(b_SE, SE.size(0) * SE.size(1)) /
               static_cast<double>(SE.size(0) * SE.size(1));
    loop_ub_tmp = SE.size(0) * SE.size(1);
    b_SE = SE.reshape(loop_ub_tmp);
    *SE_max = coder::internal::maximum(b_SE);
    loop_ub_tmp = SE.size(0) * SE.size(1);
    b_SE = SE.reshape(loop_ub_tmp);
    *SE_min = coder::internal::minimum(b_SE);
    loop_ub_tmp = SE.size(0) * SE.size(1);
    b_SE = SE.reshape(loop_ub_tmp);
    *SE_var = coder::vvarstd(b_SE, SE.size(0) * SE.size(1));
}
