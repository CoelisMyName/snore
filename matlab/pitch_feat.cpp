#include "pitch_feat.h"
#include "blockedSummation.h"
#include "minOrMax.h"
#include "pitch.h"
#include "rt_nonfinite.h"
#include "vvarstd.h"
#include "coder_array.h"

void pitch_feat(const coder::array<double, 1U> &sig, double fs,
                double *period_mean, double *period_max, double *period_min,
                double *period_var)
{
    coder::array<double, 1U> f0;
    coder::array<double, 1U> r;
    f0.set_size(1);
    f0[0] = 0.0;
    switch (static_cast<int>(fs)) {
    case 8000: {
        int loop_ub;
        coder::pitch(sig, r);
        f0.set_size(r.size(0));
        loop_ub = r.size(0);
        for (int i = 0; i < loop_ub; i++) {
            f0[i] = r[i];
        }
    } break;
    case 11025: {
        int loop_ub;
        coder::b_pitch(sig, r);
        f0.set_size(r.size(0));
        loop_ub = r.size(0);
        for (int i = 0; i < loop_ub; i++) {
            f0[i] = r[i];
        }
    } break;
    case 12000: {
        int loop_ub;
        coder::c_pitch(sig, r);
        f0.set_size(r.size(0));
        loop_ub = r.size(0);
        for (int i = 0; i < loop_ub; i++) {
            f0[i] = r[i];
        }
    } break;
    case 22050: {
        int loop_ub;
        coder::d_pitch(sig, r);
        f0.set_size(r.size(0));
        loop_ub = r.size(0);
        for (int i = 0; i < loop_ub; i++) {
            f0[i] = r[i];
        }
    } break;
    case 24000: {
        int loop_ub;
        coder::e_pitch(sig, r);
        f0.set_size(r.size(0));
        loop_ub = r.size(0);
        for (int i = 0; i < loop_ub; i++) {
            f0[i] = r[i];
        }
    } break;
    case 44100: {
        int loop_ub;
        coder::f_pitch(sig, r);
        f0.set_size(r.size(0));
        loop_ub = r.size(0);
        for (int i = 0; i < loop_ub; i++) {
            f0[i] = r[i];
        }
    } break;
    case 48000: {
        int loop_ub;
        coder::g_pitch(sig, r);
        f0.set_size(r.size(0));
        loop_ub = r.size(0);
        for (int i = 0; i < loop_ub; i++) {
            f0[i] = r[i];
        }
    } break;
    }
    *period_mean = coder::blockedSummation(f0, f0.size(0)) /
                   static_cast<double>(f0.size(0));
    *period_max = coder::internal::maximum(f0);
    *period_min = coder::internal::minimum(f0);
    *period_var = coder::vvarstd(f0, f0.size(0));
}
