//
// File: hanning.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "hanning.h"
#include "SnoringRecognition_rtwutil.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double varargin_1
//                ::coder::array<double, 1U> &w
// Return Type  : void
//
namespace coder {
    void hanning(double varargin_1, ::coder::array<double, 1U> &w) {
        array<double, 2U> r;
        array<double, 1U> b_w;
        double n;
        if (varargin_1 == floor(varargin_1)) {
            n = varargin_1;
        } else {
            n = rt_roundd_snf(varargin_1);
        }
        if (n == 0.0) {
            w.set_size(0);
        } else if (n == 1.0) {
            w.set_size(1);
            w[0] = 1.0;
        } else if (iseven(n)) {
            double b;
            int i;
            int i1;
            int k;
            int loop_ub;
            int nx;
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
            double b;
            int i;
            int i1;
            int k;
            int loop_ub;
            int nx;
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

} // namespace coder

//
// File trailer for hanning.cpp
//
// [EOF]
//
