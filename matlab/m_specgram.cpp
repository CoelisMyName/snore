//
// File: m_specgram.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "m_specgram.h"
#include "any1.h"
#include "fft.h"
#include "fix.h"
#include "isinf.h"
#include "isnan.h"
#include "mod.h"
#include "round.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// function [yo, fo, to] = m_specgram(x, nfft, Fs, window, noverlap)
//
// Arguments    : coder::array<double, 1U> &x
//                double nfft
//                const coder::array<double, 2U> &window
//                double noverlap
//                coder::array<creal_T, 2U> &yo
// Return Type  : void
//
void m_specgram(coder::array<double, 1U> &x, double nfft,
                const coder::array<double, 2U> &window, double noverlap,
                coder::array<creal_T, 2U> &yo) {
    coder::array<creal_T, 2U> b_yo;
    coder::array<double, 2U> b_select;
    coder::array<double, 2U> b_window;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> colindex;
    coder::array<double, 2U> y;
    coder::array<double, 1U> b_x;
    coder::array<double, 1U> rowindex;
    double b;
    double ncol;
    int b_loop_ub;
    int i;
    int i1;
    int loop_ub;
    int nx;
    // 'm_specgram:2' nfft = round(nfft);
    coder::b_round(&nfft);
    // 'm_specgram:3' nx = length(x);
    nx = x.size(0);
    // 'm_specgram:4' nwind = length(window);
    // 'm_specgram:6' if nx < nwind
    if (x.size(0) < window.size(1)) {
        //  zero-pad x if it has length less than the window length
        // 'm_specgram:7' x(nwind) = 0;
        x[window.size(1) - 1] = 0.0;
        // 'm_specgram:7' nx = nwind;
        nx = window.size(1);
    }
    // 'm_specgram:10' x = x(:);
    //  make a column vector for ease later
    // 'm_specgram:11' window = window(:);
    //  be consistent with data set
    // 'm_specgram:13' ncol = fix((nx - noverlap) / (nwind - noverlap));
    ncol = (static_cast<double>(nx) - noverlap) /
           (static_cast<double>(window.size(1)) - noverlap);
    coder::b_fix(&ncol);
    // 'm_specgram:14' colindex = 1 + (0:(ncol - 1)) * (nwind - noverlap);
    if (coder::b_isnan(ncol - 1.0)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (ncol - 1.0 < 0.0) {
        y.set_size(1, 0);
    } else if (coder::b_isinf(ncol - 1.0) && (0.0 == ncol - 1.0)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(ncol - 1.0));
        y.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            y[i] = i;
        }
    }
    b = static_cast<double>(window.size(1)) - noverlap;
    colindex.set_size(1, y.size(1));
    loop_ub = y.size(1);
    for (i = 0; i < loop_ub; i++) {
        colindex[i] = y[i] * b + 1.0;
    }
    // 'm_specgram:15' rowindex = (1:nwind)';
    if (coder::b_isnan(static_cast<double>(window.size(1)))) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (window.size(1) < 1) {
        y.set_size(1, 0);
    } else if (coder::b_isinf(static_cast<double>(window.size(1))) &&
               (1 == window.size(1))) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else {
        y.set_size(1, window.size(1));
        loop_ub = window.size(1) - 1;
        for (i = 0; i <= loop_ub; i++) {
            y[i] = static_cast<double>(i) + 1.0;
        }
    }
    rowindex.set_size(y.size(1));
    loop_ub = y.size(1);
    for (i = 0; i < loop_ub; i++) {
        rowindex[i] = y[i];
    }
    // 'm_specgram:17' if length(x) < (nwind + colindex(ncol) - 1)
    b = colindex[static_cast<int>(ncol) - 1];
    if (x.size(0) < (static_cast<double>(window.size(1)) + b) - 1.0) {
        // 'm_specgram:18' x(nwind + colindex(ncol) - 1) = 0;
        x[static_cast<int>((static_cast<double>(window.size(1)) + b) - 1.0) -
          1] = 0.0;
        //  zero-pad x
    }
    // 'm_specgram:21' if length(nfft) > 1
    // 'm_specgram:25' else
    // 'm_specgram:26' use_chirp = 0;
    // 'm_specgram:29' if (length(nfft) == 1) || use_chirp
    // 'm_specgram:30' y = zeros(nwind, ncol);
    //  put x into columns of y with the proper offset
    //  should be able to do this with fancy indexing!
    // 'm_specgram:34' y(:) = x(rowindex(:, ones(1, ncol)) +
    // colindex(ones(nwind, 1), :) - 1);
    loop_ub = rowindex.size(0);
    b_y.set_size(rowindex.size(0), static_cast<int>(ncol));
    b_loop_ub = static_cast<int>(ncol);
    for (i = 0; i < b_loop_ub; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_y[i1 + b_y.size(0) * i] =
                    x[static_cast<int>((rowindex[i1] + colindex[i]) - 1.0) - 1];
        }
    }
    //  Apply the window to the array of offset signal segments.
    // 'm_specgram:37' y = window(:, ones(1, ncol)) .* y;
    // 'm_specgram:39' if ~use_chirp
    //  USE FFT
    //  now fft y which does the columns
    // 'm_specgram:41' y = fft(y, nfft);
    loop_ub = window.size(1);
    b_window.set_size(window.size(1), static_cast<int>(ncol));
    b_loop_ub = static_cast<int>(ncol);
    for (i = 0; i < b_loop_ub; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_window[i1 + b_window.size(0) * i] =
                    window[i1] * b_y[i1 + b_y.size(0) * i];
        }
    }
    coder::fft(b_window, nfft, yo);
    // 'm_specgram:43' if ~any(any(imag(x)))
    b_x.set_size(x.size(0));
    loop_ub = x.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_x[i] = 0.0;
    }
    if (!coder::any(coder::b_any(b_x))) {
        //  x purely real
        // 'm_specgram:45' if mod(nfft, 2) ~= 0
        if (coder::b_mod(nfft) != 0.0) {
            //  nfft odd
            // 'm_specgram:46' select = 1:(nfft + 1) / 2;
            b = (nfft + 1.0) / 2.0;
            if (coder::b_isnan(b)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else if (b < 1.0) {
                b_select.set_size(1, 0);
            } else if (coder::b_isinf(b) && (1.0 == b)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else {
                loop_ub = static_cast<int>(floor(b - 1.0));
                b_select.set_size(1, loop_ub + 1);
                for (i = 0; i <= loop_ub; i++) {
                    b_select[i] = static_cast<double>(i) + 1.0;
                }
            }
        } else {
            // 'm_specgram:47' else
            // 'm_specgram:48' select = 1:nfft / 2 + 1;
            b = nfft / 2.0 + 1.0;
            if (coder::b_isnan(b)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else if (b < 1.0) {
                b_select.set_size(1, 0);
            } else if (coder::b_isinf(b) && (1.0 == b)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else {
                loop_ub = static_cast<int>(floor(b - 1.0));
                b_select.set_size(1, loop_ub + 1);
                for (i = 0; i <= loop_ub; i++) {
                    b_select[i] = static_cast<double>(i) + 1.0;
                }
            }
        }
        // 'm_specgram:51' y = y(select, :);
        b_loop_ub = yo.size(1) - 1;
        b_yo.set_size(b_select.size(1), yo.size(1));
        for (i = 0; i <= b_loop_ub; i++) {
            loop_ub = b_select.size(1);
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_yo[i1 + b_yo.size(0) * i] =
                        yo[(static_cast<int>(b_select[i1]) + yo.size(0) * i) - 1];
            }
        }
        yo.set_size(b_yo.size(0), b_yo.size(1));
        loop_ub = b_yo.size(0) * b_yo.size(1);
        for (i = 0; i < loop_ub; i++) {
            yo[i] = b_yo[i];
        }
    } else {
        // 'm_specgram:52' else
        // 'm_specgram:53' select = 1:nfft;
    }
    // 'm_specgram:56' f = (select - 1)' * Fs / nfft;
    // 'm_specgram:78' t = (colindex - 1)' / Fs;
    //  take abs, and use image to display results
    // 'm_specgram:81' if nargout == 1
    // 'm_specgram:82' yo = y;
}

//
// File trailer for m_specgram.cpp
//
// [EOF]
//
