//
// File: powspec.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "powspec.h"
#include "abs.h"
#include "ceil.h"
#include "hanning.h"
#include "log.h"
#include "m_specgram.h"
#include "mpower.h"
#include "power.h"
#include "round.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [y, e] = powspec(x, sr, wintime, steptime, dither)
//
// [y,e] = powspec(x, sr, wintime, steptime, sumlin, dither)
//
//  compute the powerspectrum and frame energy of the input signal.
//  basically outputs a power spectrogram
//
//  each column represents a power spectrum for a given frame
//  each row represents a frequency
//
//  default values:
//  sr = 8000Hz
//  wintime = 25ms (200 samps)
//  steptime = 10ms (80 samps)
//  which means use 256 point fft
//  hamming window
//
//  $Header: /Users/dpwe/matlab/rastamat/RCS/powspec.m,v 1.3 2012/09/03 14:02:01
//  dpwe Exp dpwe $
//
// Arguments    : const coder::array<double, 1U> &x
//                double sr
//                coder::array<double, 2U> &y
// Return Type  : void
//
void powspec(const coder::array<double, 1U> &x, double sr,
             coder::array<double, 2U> &y) {
    coder::array<creal_T, 2U> r;
    coder::array<double, 2U> WINDOW;
    coder::array<double, 2U> r1;
    coder::array<double, 1U> b_x;
    double d;
    double d1;
    double winpts;
    int i;
    int loop_ub;
    //  for sr = 8000
    // NFFT = 256;
    // NOVERLAP = 120;
    // SAMPRATE = 8000;
    // WINDOW = hamming(200);
    // 'powspec:25' if nargin < 2
    // 'powspec:29' if nargin < 3
    // 'powspec:30' wintime = 0.025;
    // 'powspec:33' if nargin < 4
    // 'powspec:34' steptime = 0.010;
    // 'powspec:37' if nargin < 5
    // 'powspec:38' dither = 1;
    // 'powspec:41' winpts = round(wintime * sr);
    winpts = 0.025 * sr;
    coder::b_round(&winpts);
    // 'powspec:42' steppts = round(steptime * sr);
    // 'powspec:44' NFFT = 2^(ceil(log(winpts) / log(2)));
    // WINDOW = hamming(winpts);
    // WINDOW = [0,hanning(winpts)'];
    // 'powspec:47' WINDOW = [hanning(winpts)'];
    coder::hanning(winpts, b_x);
    WINDOW.set_size(1, b_x.size(0));
    loop_ub = b_x.size(0);
    for (i = 0; i < loop_ub; i++) {
        WINDOW[i] = b_x[i];
    }
    //  hanning gives much less noisy sidelobes
    // 'powspec:49' NOVERLAP = winpts - steppts;
    // 'powspec:50' SAMPRATE = sr;
    //  Values coming out of rasta treat samples as integers,
    //  not range -1..1, hence scale up here to match (approx)
    // bugbug = specgram(x * 32768, NFFT, SAMPRATE, WINDOW, NOVERLAP)
    // 'powspec:55' y = abs(m_specgram(x * 32768, NFFT, SAMPRATE, WINDOW,
    // NOVERLAP)).^2;
    d = winpts;
    coder::b_log(&d);
    d /= 0.69314718055994529;
    coder::b_ceil(&d);
    d1 = 0.01 * sr;
    coder::b_round(&d1);
    b_x.set_size(x.size(0));
    loop_ub = x.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_x[i] = x[i] * 32768.0;
    }
    m_specgram(b_x, coder::mpower(2.0, d), WINDOW, winpts - d1, r);
    coder::b_abs(r, r1);
    coder::power(r1, y);
    //  imagine we had random dither that had a variance of 1 sample
    //  step and a white spectrum.  That's like (in expectation, anyway)
    //  adding a constant value to every bin (to avoid digital zero)
    // 'powspec:59' if (dither)
    // 'powspec:60' y = y + winpts;
    loop_ub = y.size(0) * y.size(1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = y[i] + winpts;
    }
    //  ignoring the hamming window, total power would be = #pts
    //  I think this doesn't quite make sense, but it's what rasta/powspec.c
    //  does that's all she wrote 2012-09-03 Calculate log energy - after
    //  windowing, by parseval
    // 'powspec:69' e = log(sum(y));
}

//
// File trailer for powspec.cpp
//
// [EOF]
//
