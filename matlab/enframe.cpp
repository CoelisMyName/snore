//
// File: enframe.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "enframe.h"
#include "fix.h"
#include "isinf.h"
#include "isnan.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// function f = enframe(x, win, inc)
//
// ENFRAME split signal up into (overlapping) frames: one per row. F=(X,WIN,INC)
//
// Arguments    : const coder::array<double, 1U> &x
//                double win
//                double inc
//                coder::array<double, 2U> &f
// Return Type  : void
//
void enframe(const coder::array<double, 1U> &x, double win, double inc,
             coder::array<double, 2U> &f) {
    coder::array<double, 2U> inds;
    coder::array<double, 2U> r;
    coder::array<double, 1U> indf;
    double nf;
    int i;
    int loop_ub;
    int loop_ub_tmp;
    // 'enframe:4' nx = length(x);
    // 'enframe:5' nwin = length(win);
    // 'enframe:7' if (nwin == 1)
    // 'enframe:8' len = win(1);
    // 'enframe:13' if (nargin < 3)
    // 'enframe:17' nf = fix((nx - len + inc) / inc);
    nf = ((static_cast<double>(x.size(0)) - win) + inc) / inc;
    coder::b_fix(&nf);
    // 'enframe:18' f = zeros(nf, len);
    // 'enframe:19' indf = inc * (0:(nf - 1)).';
    if (coder::b_isnan(nf - 1.0)) {
        r.set_size(1, 1);
        r[0] = rtNaN;
    } else if (nf - 1.0 < 0.0) {
        r.set_size(1, 0);
    } else if (coder::b_isinf(nf - 1.0) && (0.0 == nf - 1.0)) {
        r.set_size(1, 1);
        r[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(nf - 1.0));
        r.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            r[i] = i;
        }
    }
    indf.set_size(r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
        indf[i] = inc * r[i];
    }
    // 'enframe:20' inds = (1:len);
    if (coder::b_isnan(win)) {
        inds.set_size(1, 1);
        inds[0] = rtNaN;
    } else if (win < 1.0) {
        inds.set_size(1, 0);
    } else if (coder::b_isinf(win) && (1.0 == win)) {
        inds.set_size(1, 1);
        inds[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(win - 1.0));
        inds.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            inds[i] = static_cast<double>(i) + 1.0;
        }
    }
    // 'enframe:21' f(:) = x(indf(:, ones(1, len)) + inds(ones(nf, 1), :));
    loop_ub = indf.size(0);
    loop_ub_tmp = static_cast<int>(win);
    f.set_size(indf.size(0), loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        for (int i1 = 0; i1 < loop_ub; i1++) {
            f[i1 + f.size(0) * i] = x[static_cast<int>(indf[i1] + inds[i]) - 1];
        }
    }
    // 'enframe:23' if (nwin > 1)
}

//
// function f = enframe(x, win, inc)
//
// ENFRAME split signal up into (overlapping) frames: one per row. F=(X,WIN,INC)
//
// Arguments    : const coder::array<double, 1U> &x
//                const coder::array<double, 1U> &win
//                double inc
//                coder::array<double, 2U> &f
// Return Type  : void
//
void enframe(const coder::array<double, 1U> &x,
             const coder::array<double, 1U> &win, double inc,
             coder::array<double, 2U> &f) {
    coder::array<double, 2U> inds;
    coder::array<double, 2U> r;
    coder::array<double, 1U> indf;
    double len;
    double nf;
    int i;
    int i1;
    int loop_ub;
    int loop_ub_tmp;
    // 'enframe:4' nx = length(x);
    // 'enframe:5' nwin = length(win);
    // 'enframe:7' if (nwin == 1)
    if (win.size(0) == 1) {
        // 'enframe:8' len = win(1);
        len = win[0];
    } else {
        // 'enframe:9' else
        // 'enframe:10' len = nwin;
        len = win.size(0);
    }
    // 'enframe:13' if (nargin < 3)
    // 'enframe:17' nf = fix((nx - len + inc) / inc);
    nf = ((static_cast<double>(x.size(0)) - len) + inc) / inc;
    coder::b_fix(&nf);
    // 'enframe:18' f = zeros(nf, len);
    // 'enframe:19' indf = inc * (0:(nf - 1)).';
    if (coder::b_isnan(nf - 1.0)) {
        r.set_size(1, 1);
        r[0] = rtNaN;
    } else if (nf - 1.0 < 0.0) {
        r.set_size(1, 0);
    } else if (coder::b_isinf(nf - 1.0) && (0.0 == nf - 1.0)) {
        r.set_size(1, 1);
        r[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(nf - 1.0));
        r.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            r[i] = i;
        }
    }
    indf.set_size(r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
        indf[i] = inc * r[i];
    }
    // 'enframe:20' inds = (1:len);
    if (coder::b_isnan(len)) {
        inds.set_size(1, 1);
        inds[0] = rtNaN;
    } else if (len < 1.0) {
        inds.set_size(1, 0);
    } else if (coder::b_isinf(len) && (1.0 == len)) {
        inds.set_size(1, 1);
        inds[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(len - 1.0));
        inds.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            inds[i] = static_cast<double>(i) + 1.0;
        }
    }
    // 'enframe:21' f(:) = x(indf(:, ones(1, len)) + inds(ones(nf, 1), :));
    loop_ub = indf.size(0);
    loop_ub_tmp = static_cast<int>(len);
    f.set_size(indf.size(0), loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            f[i1 + f.size(0) * i] = x[static_cast<int>(indf[i1] + inds[i]) - 1];
        }
    }
    // 'enframe:23' if (nwin > 1)
    if (win.size(0) > 1) {
        // 'enframe:24' w = win(:)';
        // 'enframe:25' f = f .* w(ones(nf, 1), :);
        loop_ub = f.size(1);
        for (i = 0; i < loop_ub; i++) {
            loop_ub_tmp = f.size(0);
            for (i1 = 0; i1 < loop_ub_tmp; i1++) {
                f[i1 + f.size(0) * i] = f[i1 + f.size(0) * i] * win[i];
            }
        }
    }
}

//
// File trailer for enframe.cpp
//
// [EOF]
//
