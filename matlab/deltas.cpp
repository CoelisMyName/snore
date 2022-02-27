//
// File: deltas.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "deltas.h"
#include "filter.h"
#include "isinf.h"
#include "isnan.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function d = deltas(x, w)
//
// D = deltas(X,W)  Calculate the deltas (derivatives) of a sequence
//     Use a W-point window (W odd, default 9) to calculate deltas using a
//     simple linear slope.  This mirrors the delta calculation performed
//     in feacalc etc.  Each row of X is filtered separately.
//  2003-06-30 dpwe@ee.columbia.edu
//
// Arguments    : const coder::array<double, 2U> &x
//                coder::array<double, 2U> &d
// Return Type  : void
//
void b_deltas(const coder::array<double, 2U> &x, coder::array<double, 2U> &d) {
    coder::array<double, 2U> b_d;
    coder::array<double, 2U> y;
    double b_dv[26];
    double b_dv1[26];
    // 'deltas:8' if nargin < 2
    // 'deltas:12' [nr, nc] = size(x);
    // 'deltas:14' if nc == 0
    if (x.size(1) == 0) {
        //  empty vector passed in; return empty vector
        // 'deltas:16' d = x;
        d.set_size(13, 0);
    } else {
        int b_x;
        int i;
        int i1;
        // 'deltas:18' else
        //  actually calculate deltas
        //  Define window shape
        // 'deltas:22' hlen = floor(w / 2);
        // 'deltas:23' w = 2 * hlen + 1;
        // 'deltas:24' win = hlen:-1:-hlen;
        //  pad data by repeating first and last columns
        // 'deltas:27' xx = [repmat(x(:, 1), 1, hlen), x, repmat(x(:, end), 1,
        // hlen)];
        //  Apply the delta filter
        // 'deltas:30' d = filter(win, 1, xx, [], 2);
        coder::b_repmat(*(double (*)[13]) &x[0], b_dv);
        b_x = x.size(1);
        coder::b_repmat(*(double (*)[13]) &x[13 * (b_x - 1)], b_dv1);
        b_d.set_size(13, x.size(1) + 4);
        for (i = 0; i < 2; i++) {
            for (i1 = 0; i1 < 13; i1++) {
                b_d[i1 + 13 * i] = b_dv[i1 + 13 * i];
            }
        }
        b_x = x.size(1);
        for (i = 0; i < b_x; i++) {
            for (i1 = 0; i1 < 13; i1++) {
                b_d[i1 + 13 * (i + 2)] = x[i1 + 13 * i];
            }
        }
        for (i = 0; i < 2; i++) {
            for (i1 = 0; i1 < 13; i1++) {
                b_d[i1 + 13 * ((i + x.size(1)) + 2)] = b_dv1[i1 + 13 * i];
            }
        }
        coder::b_filter(b_d, d);
        //  filter along dim 2 (rows)
        //  Trim edges
        // 'deltas:33' d = d(:, 2 * hlen + [1:nc]);
        if (coder::b_isnan(static_cast<double>(x.size(1)))) {
            y.set_size(1, 1);
            y[0] = rtNaN;
        } else if (coder::b_isinf(static_cast<double>(x.size(1))) &&
                   (1 == x.size(1))) {
            y.set_size(1, 1);
            y[0] = rtNaN;
        } else {
            y.set_size(1, x.size(1));
            b_x = x.size(1) - 1;
            for (i = 0; i <= b_x; i++) {
                y[i] = static_cast<double>(i) + 1.0;
            }
        }
        b_d.set_size(13, y.size(1));
        b_x = y.size(1);
        for (i = 0; i < b_x; i++) {
            for (i1 = 0; i1 < 13; i1++) {
                b_d[i1 + 13 * i] =
                        d[i1 + 13 * (static_cast<int>(y[i] + 4.0) - 1)];
            }
        }
        d.set_size(13, b_d.size(1));
        b_x = 13 * b_d.size(1);
        for (i = 0; i < b_x; i++) {
            d[i] = b_d[i];
        }
    }
}

//
// function d = deltas(x, w)
//
// D = deltas(X,W)  Calculate the deltas (derivatives) of a sequence
//     Use a W-point window (W odd, default 9) to calculate deltas using a
//     simple linear slope.  This mirrors the delta calculation performed
//     in feacalc etc.  Each row of X is filtered separately.
//  2003-06-30 dpwe@ee.columbia.edu
//
// Arguments    : const coder::array<double, 2U> &x
//                coder::array<double, 2U> &d
// Return Type  : void
//
void deltas(const coder::array<double, 2U> &x, coder::array<double, 2U> &d) {
    coder::array<double, 2U> b_d;
    coder::array<double, 2U> y;
    double b_dv[52];
    double b_dv1[52];
    int b_x;
    int i;
    int i1;
    // 'deltas:8' if nargin < 2
    // 'deltas:9' w = 9;
    // 'deltas:12' [nr, nc] = size(x);
    // 'deltas:14' if nc == 0
    // 'deltas:18' else
    //  actually calculate deltas
    //  Define window shape
    // 'deltas:22' hlen = floor(w / 2);
    // 'deltas:23' w = 2 * hlen + 1;
    // 'deltas:24' win = hlen:-1:-hlen;
    //  pad data by repeating first and last columns
    // 'deltas:27' xx = [repmat(x(:, 1), 1, hlen), x, repmat(x(:, end), 1,
    // hlen)];
    //  Apply the delta filter
    // 'deltas:30' d = filter(win, 1, xx, [], 2);
    coder::repmat(*(double (*)[13]) &x[0], b_dv);
    b_x = x.size(1);
    coder::repmat(*(double (*)[13]) &x[13 * (b_x - 1)], b_dv1);
    b_d.set_size(13, x.size(1) + 8);
    for (i = 0; i < 4; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            b_d[i1 + 13 * i] = b_dv[i1 + 13 * i];
        }
    }
    b_x = x.size(1);
    for (i = 0; i < b_x; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            b_d[i1 + 13 * (i + 4)] = x[i1 + 13 * i];
        }
    }
    for (i = 0; i < 4; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            b_d[i1 + 13 * ((i + x.size(1)) + 4)] = b_dv1[i1 + 13 * i];
        }
    }
    coder::filter(b_d, d);
    //  filter along dim 2 (rows)
    //  Trim edges
    // 'deltas:33' d = d(:, 2 * hlen + [1:nc]);
    if (coder::b_isnan(static_cast<double>(x.size(1)))) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (x.size(1) < 1) {
        y.set_size(1, 0);
    } else if (coder::b_isinf(static_cast<double>(x.size(1))) &&
               (1 == x.size(1))) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else {
        y.set_size(1, x.size(1));
        b_x = x.size(1) - 1;
        for (i = 0; i <= b_x; i++) {
            y[i] = static_cast<double>(i) + 1.0;
        }
    }
    b_d.set_size(13, y.size(1));
    b_x = y.size(1);
    for (i = 0; i < b_x; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            b_d[i1 + 13 * i] = d[i1 + 13 * (static_cast<int>(y[i] + 8.0) - 1)];
        }
    }
    d.set_size(13, b_d.size(1));
    b_x = 13 * b_d.size(1);
    for (i = 0; i < b_x; i++) {
        d[i] = b_d[i];
    }
}

//
// File trailer for deltas.cpp
//
// [EOF]
//
