//
// File: fft2barkmx.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "fft2barkmx.h"
#include "ceil.h"
#include "hz2bark.h"
#include "isinf.h"
#include "isnan.h"
#include "minOrMax.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// function wts = fft2barkmx(nfft, sr, nfilts, width, minfreq, maxfreq)
//
// wts = fft2barkmx(nfft, sr, nfilts, width, minfreq, maxfreq)
//       Generate a matrix of weights to combine FFT bins into Bark
//       bins.  nfft defines the source FFT size at sampling rate sr.
//       Optional nfilts specifies the number of output bands required
//       (else one per bark), and width is the constant width of each
//       band in Bark (default 1).
//       While wts has nfft columns, the second half are all zero.
//       Hence, Bark spectrum is fft2barkmx(nfft,sr)*abs(fft(xincols,nfft));
//  2004-09-05  dpwe@ee.columbia.edu  based on rastamat/audspec.m
//
// Arguments    : double nfft
//                double sr
//                double nfilts
//                double maxfreq
//                coder::array<double, 2U> &wts
// Return Type  : void
//
void fft2barkmx(double nfft, double sr, double nfilts, double maxfreq,
                coder::array<double, 2U> &wts) {
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> binbarks;
    coder::array<double, 2U> c_y;
    coder::array<double, 2U> r;
    coder::array<double, 2U> y;
    double b;
    double min_bark;
    double nyqbark;
    double step_barks;
    int i;
    int i1;
    int loop_ub;
    // 'fft2barkmx:12' if nargin < 3
    // 'fft2barkmx:13' if nargin < 4
    // 'fft2barkmx:14' if nargin < 5
    // 'fft2barkmx:15' if nargin < 6
    // 'fft2barkmx:17' min_bark = hz2bark(minfreq);
    min_bark = hz2bark(0.0);
    // 'fft2barkmx:18' nyqbark = hz2bark(maxfreq) - min_bark;
    nyqbark = hz2bark(maxfreq) - min_bark;
    // 'fft2barkmx:20' if nfilts == 0
    if (nfilts == 0.0) {
        // 'fft2barkmx:21' nfilts = ceil(nyqbark) + 1;
        b = nyqbark;
        coder::b_ceil(&b);
        nfilts = b + 1.0;
    }
    // 'fft2barkmx:24' wts = zeros(nfilts, nfft);
    i = static_cast<int>(nfilts);
    wts.set_size(i, static_cast<int>(nfft));
    loop_ub = static_cast<int>(nfilts) * static_cast<int>(nfft);
    for (i1 = 0; i1 < loop_ub; i1++) {
        wts[i1] = 0.0;
    }
    //  bark per filt
    // 'fft2barkmx:27' step_barks = nyqbark / (nfilts - 1);
    step_barks = nyqbark / (nfilts - 1.0);
    //  Frequency of each FFT bin in Bark
    // 'fft2barkmx:30' binbarks = hz2bark([0:nfft / 2] * sr / nfft);
    b = nfft / 2.0;
    if (coder::b_isnan(b)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (coder::b_isinf(b) && (0.0 == b)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(b));
        y.set_size(1, loop_ub + 1);
        for (i1 = 0; i1 <= loop_ub; i1++) {
            y[i1] = i1;
        }
    }
    b_y.set_size(1, y.size(1));
    loop_ub = y.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
        b_y[i1] = y[i1] * sr / nfft;
    }
    hz2bark(b_y, binbarks);
    // 'fft2barkmx:32' for i = 1:nfilts
    for (int b_i = 0; b_i < i; b_i++) {
        double f_bark_mid;
        // 'fft2barkmx:33' f_bark_mid = min_bark + (i - 1) * step_barks;
        f_bark_mid =
                min_bark + ((static_cast<double>(b_i) + 1.0) - 1.0) * step_barks;
        //  Linear slopes in log-space (i.e. dB) intersect to trapezoidal window
        // 'fft2barkmx:35' lof = (binbarks - f_bark_mid - 0.5);
        y.set_size(1, binbarks.size(1));
        loop_ub = binbarks.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1] = binbarks[i1] - f_bark_mid;
        }
        // 'fft2barkmx:36' hif = (binbarks - f_bark_mid + 0.5);
        // 'fft2barkmx:37' wts(i, 1:(nfft / 2 + 1)) = 10.^(min(0, min([hif; -2.5
        // * lof]) / width));
        c_y.set_size(2, y.size(1));
        loop_ub = y.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            c_y[2 * i1] = y[i1] + 0.5;
        }
        loop_ub = y.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            c_y[2 * i1 + 1] = -2.5 * (y[i1] - 0.5);
        }
        coder::internal::minimum(c_y, y);
        coder::internal::minimum2(y, r);
        coder::b_power(r, b_y);
        loop_ub = b_y.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            wts[b_i + wts.size(0) * i1] = b_y[i1];
        }
    }
}

//
// File trailer for fft2barkmx.cpp
//
// [EOF]
//
