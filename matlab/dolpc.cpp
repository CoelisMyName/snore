//
// File: dolpc.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "dolpc.h"
#include "SnoringRecognition_rtwutil.h"
#include "ifft.h"
#include "levinson.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function y = dolpc(x, modelorder)
//
// y = dolpc(x,modelorder)
//
//  compute autoregressive model from spectral magnitude samples
//
//  rows(x) = critical band
//  col(x) = frame
//
//  row(y) = lpc a_i coeffs, scaled by gain
//  col(y) = frame
//
//  modelorder is order of model, defaults to 8
//  2003-04-12 dpwe@ee.columbia.edu after shire@icsi.berkeley.edu
//
// Arguments    : const coder::array<double, 2U> &x
//                coder::array<double, 2U> &y
// Return Type  : void
//
void dolpc(const coder::array<double, 2U> &x, coder::array<double, 2U> &y) {
    coder::array<creal_T, 2U> b_r;
    coder::array<double, 2U> b_e;
    coder::array<double, 2U> b_x;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> c_r;
    coder::array<double, 2U> c_x;
    coder::array<double, 2U> r1;
    coder::array<double, 1U> e;
    int b_loop_ub;
    int i;
    int i1;
    int input_sizes_idx_0;
    int loop_ub;
    int r;
    int result;
    int sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    // 'dolpc:15' [nbands, ~] = size(x);
    // 'dolpc:17' if nargin < 2
    //  Calculate autocorrelation
    // 'dolpc:22' r = real(ifft([x; x([(nbands - 1):-1:2], :)]));
    if (2 > x.size(0) - 1) {
        i = 0;
        i1 = 1;
        r = -1;
    } else {
        i = x.size(0) - 2;
        i1 = -1;
        r = 1;
    }
    if ((x.size(0) != 0) && (x.size(1) != 0)) {
        result = x.size(1);
    } else if ((div_s32_floor(r - i, i1) + 1 != 0) && (x.size(1) != 0)) {
        result = x.size(1);
    } else {
        result = x.size(1);
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((x.size(0) != 0) && (x.size(1) != 0))) {
        input_sizes_idx_0 = x.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes ||
        ((div_s32_floor(r - i, i1) + 1 != 0) && (x.size(1) != 0))) {
        sizes_idx_0 = div_s32_floor(r - i, i1) + 1;
    } else {
        sizes_idx_0 = 0;
    }
    loop_ub = x.size(1);
    b_x.set_size(div_s32_floor(r - i, i1) + 1, x.size(1));
    for (int i2 = 0; i2 < loop_ub; i2++) {
        b_loop_ub = div_s32_floor(r - i, i1);
        for (int i3 = 0; i3 <= b_loop_ub; i3++) {
            b_x[i3 + b_x.size(0) * i2] = x[(i + i1 * i3) + x.size(0) * i2];
        }
    }
    c_x.set_size(input_sizes_idx_0 + sizes_idx_0, result);
    for (i = 0; i < result; i++) {
        for (i1 = 0; i1 < input_sizes_idx_0; i1++) {
            c_x[i1 + c_x.size(0) * i] = x[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < result; i++) {
        for (i1 = 0; i1 < sizes_idx_0; i1++) {
            c_x[(i1 + input_sizes_idx_0) + c_x.size(0) * i] =
                    b_x[i1 + sizes_idx_0 * i];
        }
    }
    coder::ifft(c_x, b_r);
    c_r.set_size(b_r.size(0), b_r.size(1));
    loop_ub = b_r.size(0) * b_r.size(1);
    for (i = 0; i < loop_ub; i++) {
        c_r[i] = b_r[i].re;
    }
    //  First half only
    // 'dolpc:24' r = r(1:nbands, :);
    r = c_r.size(1) - 1;
    loop_ub = x.size(0);
    for (i = 0; i <= r; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            c_r[i1 + loop_ub * i] = c_r[i1 + c_r.size(0) * i];
        }
    }
    c_r.set_size(x.size(0), r + 1);
    //  Find LPC coeffs by durbin
    // 'dolpc:27' [y, e] = levinson(r, modelorder);
    coder::levinson(c_r, b_y, e);
    //  Normalize each poly by gain
    // 'dolpc:30' y = y' ./ repmat(e', (modelorder + 1), 1);
    b_e.set_size(1, e.size(0));
    loop_ub = e.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_e[i] = e[i];
    }
    coder::repmat(b_e, r1);
    y.set_size(b_y.size(1), b_y.size(0));
    loop_ub = b_y.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_loop_ub = b_y.size(1);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            y[i1 + 13 * i] = b_y[i + b_y.size(0) * i1] / r1[i1 + 13 * i];
        }
    }
}

//
// File trailer for dolpc.cpp
//
// [EOF]
//
