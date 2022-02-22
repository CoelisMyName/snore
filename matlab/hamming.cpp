//
// File: hamming.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "hamming.h"
#include "SnoringRecognition_rtwutil.h"
#include "gencoswin.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double varargin_1
//                ::coder::array<double, 1U> &w
// Return Type  : void
//
namespace coder {
    void hamming(double varargin_1, ::coder::array<double, 1U> &w) {
        array<double, 1U> b_w;
        double L;
        if (varargin_1 == floor(varargin_1)) {
            L = varargin_1;
        } else {
            L = rt_roundd_snf(varargin_1);
        }
        if (L == 0.0) {
            w.set_size(0);
        } else if (L == 1.0) {
            w.set_size(1);
            w[0] = 1.0;
        } else if (iseven(L)) {
            int b_loop_ub;
            int i;
            int i1;
            int i2;
            int loop_ub;
            calc_window(L / 2.0, L, w);
            if (1 > w.size(0)) {
                i = 0;
                i1 = 1;
                i2 = -1;
            } else {
                i = w.size(0) - 1;
                i1 = -1;
                i2 = 0;
            }
            loop_ub = div_s32_floor(i2 - i, i1);
            b_w.set_size((w.size(0) + loop_ub) + 1);
            b_loop_ub = w.size(0);
            for (i2 = 0; i2 < b_loop_ub; i2++) {
                b_w[i2] = w[i2];
            }
            for (i2 = 0; i2 <= loop_ub; i2++) {
                b_w[i2 + w.size(0)] = w[i + i1 * i2];
            }
            w.set_size(b_w.size(0));
            loop_ub = b_w.size(0);
            for (i = 0; i < loop_ub; i++) {
                w[i] = b_w[i];
            }
        } else {
            int b_loop_ub;
            int i;
            int i1;
            int i2;
            int loop_ub;
            calc_window((L + 1.0) / 2.0, L, w);
            if (1 > w.size(0) - 1) {
                i = 0;
                i1 = 1;
                i2 = -1;
            } else {
                i = w.size(0) - 2;
                i1 = -1;
                i2 = 0;
            }
            loop_ub = div_s32_floor(i2 - i, i1);
            b_w.set_size((w.size(0) + loop_ub) + 1);
            b_loop_ub = w.size(0);
            for (i2 = 0; i2 < b_loop_ub; i2++) {
                b_w[i2] = w[i2];
            }
            for (i2 = 0; i2 <= loop_ub; i2++) {
                b_w[i2 + w.size(0)] = w[i + i1 * i2];
            }
            w.set_size(b_w.size(0));
            loop_ub = b_w.size(0);
            for (i = 0; i < loop_ub; i++) {
                w[i] = b_w[i];
            }
        }
    }

} // namespace coder

//
// File trailer for hamming.cpp
//
// [EOF]
//
