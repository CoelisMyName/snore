//
// File: hamming.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "hamming.h"
#include "SnoringRecognition_rtwutil.h"
#include "gencoswin.h"
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
    void hamming(double varargin_1, ::coder::array<double, 1U> &w) {
        array<double, 1U> b_w;
        double L;
        int i;
        int trivialwin;
        int w_size;
        signed char w_data;
        w_size = 1;
        w_data = 0;
        trivialwin = 0;
        if (varargin_1 == floor(varargin_1)) {
            L = varargin_1;
        } else {
            L = rt_roundd_snf(varargin_1);
        }
        if (L == 0.0) {
            w_size = 0;
            trivialwin = 1;
        } else if (L == 1.0) {
            w_data = 1;
            trivialwin = 1;
        }
        w.set_size(w_size);
        for (i = 0; i < w_size; i++) {
            w[0] = w_data;
        }
        if (trivialwin == 0) {
            double r;
            if (rtIsNaN(L) || rtIsInf(L)) {
                r = rtNaN;
            } else if (L == 0.0) {
                r = 0.0;
            } else {
                r = fmod(L, 2.0);
                if (r == 0.0) {
                    r = 0.0;
                } else if (L < 0.0) {
                    r += 2.0;
                }
            }
            if (r == 0.0) {
                int i1;
                int loop_ub;
                calc_window(L / 2.0, L, w);
                if (1 > w.size(0)) {
                    i = 0;
                    w_size = 1;
                    i1 = -1;
                } else {
                    i = w.size(0) - 1;
                    w_size = -1;
                    i1 = 0;
                }
                trivialwin = div_s32_floor(i1 - i, w_size);
                b_w.set_size((w.size(0) + trivialwin) + 1);
                loop_ub = w.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    b_w[i1] = w[i1];
                }
                for (i1 = 0; i1 <= trivialwin; i1++) {
                    b_w[i1 + w.size(0)] = w[i + w_size * i1];
                }
                w.set_size(b_w.size(0));
                trivialwin = b_w.size(0);
                for (i = 0; i < trivialwin; i++) {
                    w[i] = b_w[i];
                }
            } else {
                int i1;
                int loop_ub;
                calc_window((L + 1.0) / 2.0, L, w);
                if (1 > w.size(0) - 1) {
                    i = 0;
                    w_size = 1;
                    i1 = -1;
                } else {
                    i = w.size(0) - 2;
                    w_size = -1;
                    i1 = 0;
                }
                trivialwin = div_s32_floor(i1 - i, w_size);
                b_w.set_size((w.size(0) + trivialwin) + 1);
                loop_ub = w.size(0);
                for (i1 = 0; i1 < loop_ub; i1++) {
                    b_w[i1] = w[i1];
                }
                for (i1 = 0; i1 <= trivialwin; i1++) {
                    b_w[i1 + w.size(0)] = w[i + w_size * i1];
                }
                w.set_size(b_w.size(0));
                trivialwin = b_w.size(0);
                for (i = 0; i < trivialwin; i++) {
                    w[i] = b_w[i];
                }
            }
        }
    }

} // namespace coder

//
// File trailer for hamming.cpp
//
// [EOF]
//
