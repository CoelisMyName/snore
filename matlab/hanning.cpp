#include "hanning.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

namespace coder {
void hanning(double varargin_1, ::coder::array<double, 1U> &w)
{
    array<double, 2U> r;
    array<double, 1U> b_w;
    double n;
    int i;
    int nx;
    boolean_T guard1 = false;
    if (varargin_1 == floor(varargin_1)) {
        n = varargin_1;
    } else {
        n = rt_roundd_snf(varargin_1);
    }
    guard1 = false;
    if (n == 0.0) {
        nx = 0;
        guard1 = true;
    } else if (n == 1.0) {
        nx = 1;
        guard1 = true;
    } else {
        double b;
        if (rtIsInf(n)) {
            b = rtNaN;
        } else if (n == 0.0) {
            b = 0.0;
        } else {
            b = fmod(n, 2.0);
        }
        if (b == 0.0) {
            int i1;
            int k;
            int loop_ub;
            b = n / 2.0;
            if (b < 1.0) {
                r.set_size(1, 0);
            } else if (rtIsInf(b) && (1.0 == b)) {
                r.set_size(1, 1);
                r[0] = rtNaN;
            } else {
                nx = static_cast<int>(floor(b - 1.0));
                r.set_size(1, nx + 1);
                for (i = 0; i <= nx; i++) {
                    r[i] = static_cast<double>(i) + 1.0;
                }
            }
            w.set_size(r.size(1));
            nx = r.size(1);
            for (i = 0; i < nx; i++) {
                w[i] = 6.2831853071795862 * r[i] / (n + 1.0);
            }
            nx = w.size(0);
            for (k = 0; k < nx; k++) {
                w[k] = cos(w[k]);
            }
            nx = w.size(0);
            for (i = 0; i < nx; i++) {
                w[i] = 0.5 * (1.0 - w[i]);
            }
            if (1 > w.size(0)) {
                i = 0;
                k = 1;
                i1 = -1;
            } else {
                i = w.size(0) - 1;
                k = -1;
                i1 = 0;
            }
            nx = div_s32_floor(i1 - i, k);
            b_w.set_size((w.size(0) + nx) + 1);
            loop_ub = w.size(0);
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_w[i1] = w[i1];
            }
            for (i1 = 0; i1 <= nx; i1++) {
                b_w[i1 + w.size(0)] = w[i + k * i1];
            }
            w.set_size(b_w.size(0));
            nx = b_w.size(0);
            for (i = 0; i < nx; i++) {
                w[i] = b_w[i];
            }
        } else {
            int i1;
            int k;
            int loop_ub;
            b = (n + 1.0) / 2.0;
            if (b < 1.0) {
                r.set_size(1, 0);
            } else if (rtIsInf(b) && (1.0 == b)) {
                r.set_size(1, 1);
                r[0] = rtNaN;
            } else {
                nx = static_cast<int>(floor(b - 1.0));
                r.set_size(1, nx + 1);
                for (i = 0; i <= nx; i++) {
                    r[i] = static_cast<double>(i) + 1.0;
                }
            }
            w.set_size(r.size(1));
            nx = r.size(1);
            for (i = 0; i < nx; i++) {
                w[i] = 6.2831853071795862 * r[i] / (n + 1.0);
            }
            nx = w.size(0);
            for (k = 0; k < nx; k++) {
                w[k] = cos(w[k]);
            }
            nx = w.size(0);
            for (i = 0; i < nx; i++) {
                w[i] = 0.5 * (1.0 - w[i]);
            }
            if (1 > w.size(0) - 1) {
                i = 0;
                k = 1;
                i1 = -1;
            } else {
                i = w.size(0) - 2;
                k = -1;
                i1 = 0;
            }
            nx = div_s32_floor(i1 - i, k);
            b_w.set_size((w.size(0) + nx) + 1);
            loop_ub = w.size(0);
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_w[i1] = w[i1];
            }
            for (i1 = 0; i1 <= nx; i1++) {
                b_w[i1 + w.size(0)] = w[i + k * i1];
            }
            w.set_size(b_w.size(0));
            nx = b_w.size(0);
            for (i = 0; i < nx; i++) {
                w[i] = b_w[i];
            }
        }
    }
    if (guard1) {
        w.set_size(nx);
        for (i = 0; i < nx; i++) {
            w[0] = 1.0;
        }
    }
}

} // namespace coder
