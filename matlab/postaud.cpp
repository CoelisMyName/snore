//
// File: postaud.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "postaud.h"
#include "bark2hz.h"
#include "hz2bark.h"
#include "isinf.h"
#include "isnan.h"
#include "linspace.h"
#include "power.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [y, eql] = postaud(x, fmax, fbtype, broaden)
//
// y = postaud(x, fmax, fbtype)
//
//  do loudness equalization and cube root compression
//  x = critical band filters
//  rows = critical bands
//  cols = frames
//
// Arguments    : const coder::array<double, 2U> &x
//                double b_fmax
//                coder::array<double, 2U> &y
// Return Type  : void
//
void postaud(const coder::array<double, 2U> &x, double b_fmax,
             coder::array<double, 2U> &y) {
    coder::array<double, 2U> b_fsq;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> bandcfhz;
    coder::array<double, 2U> fsq;
    coder::array<double, 2U> r;
    coder::array<double, 2U> r1;
    coder::array<double, 2U> z;
    coder::array<double, 1U> c_y;
    coder::array<int, 1U> r2;
    double d;
    int i;
    int loop_ub;
    // 'postaud:9' if nargin < 3
    // 'postaud:10' fbtype = 'bark';
    // 'postaud:13' if nargin < 4
    //  By default, don't add extra flanking bands
    // 'postaud:15' broaden = 0;
    // 'postaud:18' [nbands, nframes] = size(x);
    //  equal loundness weights stolen from rasta code
    // eql = [0.000479 0.005949 0.021117 0.044806 0.073345 0.104417 0.137717 ...
    //       0.174255 0.215590 0.263260 0.318302 0.380844 0.449798 0.522813
    //       0.596597];
    //  Include frequency points at extremes, discard later
    // 'postaud:26' nfpts = nbands + 2 * broaden;
    // 'postaud:28' if strcmp(fbtype, 'bark')
    // 'postaud:29' bandcfhz = bark2hz(linspace(0, hz2bark(fmax), nfpts));
    coder::linspace(hz2bark(b_fmax), static_cast<double>(x.size(0)), fsq);
    bark2hz(fsq, bandcfhz);
    //  Remove extremal bands (the ones that will be duplicated)
    // 'postaud:40' bandcfhz = bandcfhz((1 + broaden):(nfpts - broaden));
    if (1 > x.size(0)) {
        i = 0;
    } else {
        i = x.size(0);
    }
    bandcfhz.set_size(bandcfhz.size(0), i);
    //  Hynek's magic equal-loudness-curve formula
    // 'postaud:43' fsq = bandcfhz.^2;
    coder::c_power(bandcfhz, b_fsq);
    // 'postaud:44' ftmp = fsq + 1.6e5;
    // 'postaud:45' eql = ((fsq ./ ftmp).^2) .* ((fsq + 1.44e6) ./ (fsq
    // + 9.61e6));
    //  weight the critical bands
    // 'postaud:48' z = repmat(eql', 1, nframes) .* x;
    //  cube root compress
    // 'postaud:51' z = z.^(.33);
    fsq.set_size(1, b_fsq.size(1));
    loop_ub = b_fsq.size(1);
    for (i = 0; i < loop_ub; i++) {
        d = b_fsq[i];
        fsq[i] = d / (d + 160000.0);
    }
    coder::c_power(fsq, b_y);
    c_y.set_size(b_y.size(1));
    loop_ub = b_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        d = b_fsq[i];
        c_y[i] = b_y[i] * ((d + 1.44E+6) / (d + 9.61E+6));
    }
    coder::repmat(c_y, static_cast<double>(x.size(1)), r);
    r1.set_size(r.size(0), r.size(1));
    loop_ub = r.size(0) * r.size(1);
    for (i = 0; i < loop_ub; i++) {
        r1[i] = r[i] * x[i];
    }
    coder::d_power(r1, z);
    //  replicate first and last band (because they are unreliable as
    //  calculated)
    // 'postaud:54' if (broaden)
    // 'postaud:56' else
    // 'postaud:57' y = z([2, 2:(nbands - 1), nbands - 1], :);
    if (coder::b_isnan(static_cast<double>(x.size(0)) - 1.0)) {
        b_y.set_size(1, 1);
        b_y[0] = rtNaN;
    } else if (x.size(0) - 1 < 2) {
        b_y.set_size(1, 0);
    } else if (coder::b_isinf(static_cast<double>(x.size(0)) - 1.0) &&
               (2 == x.size(0) - 1)) {
        b_y.set_size(1, 1);
        b_y[0] = rtNaN;
    } else {
        b_y.set_size(
                1,
                static_cast<int>((static_cast<double>(x.size(0)) - 1.0) - 2.0) + 1);
        loop_ub =
                static_cast<int>((static_cast<double>(x.size(0)) - 1.0) - 2.0);
        for (i = 0; i <= loop_ub; i++) {
            b_y[i] = static_cast<double>(i) + 2.0;
        }
    }
    r2.set_size(b_y.size(1) + 2);
    r2[0] = 1;
    loop_ub = b_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        r2[i + 1] = static_cast<int>(b_y[i]) - 1;
    }
    r2[b_y.size(1) + 1] = x.size(0) - 2;
    loop_ub = z.size(1);
    y.set_size(r2.size(0), z.size(1));
    for (i = 0; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = r2.size(0);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            y[i1 + y.size(0) * i] = z[r2[i1] + z.size(0) * i];
        }
    }
    // y = z([1,1:nbands-2,nbands-2],:);
}

//
// File trailer for postaud.cpp
//
// [EOF]
//
