//
// File: octbank.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "octbank.h"
#include "filter.h"
#include "log10.h"
#include "octdsgn.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "coder_array.h"

// Function Definitions
//
// function [p, f] = octbank(x, Fs)
//
// OCT3BANK Simple one-third-octave filter bank.
//     OCT3BANK(X) plots one-third-octave power spectra of signal vector X.
//     Implementation based on ANSI S1.11-1986 Order-3 filters.
//     Sampling frequency Fs = 44100 Hz. Restricted one-third-octave-band
//     range (from 100 Hz to 5000 Hz). RMS power is computed in each band
//     and expressed in dB with 1 as reference level.
//
//     [P,F] = OCT3BANK(X) returns two length-18 row-vectors with
//     the RMS power (in dB) in P and the corresponding preferred labeling
//     frequencies (ANSI S1.6-1984) in F.
//
//     See also OCT3DSGN, OCT3SPEC, OCTDSGN, OCTSPEC.
//
// Arguments    : const coder::array<double, 2U> &x
//                double p[8]
// Return Type  : void
//
void octbank(const coder::array<double, 2U> &x, double p[8]) {
    static const double b_dv[8] = {62.5, 125.0, 250.0, 500.0,
                                   1000.0, 2000.0, 4000.0, 8000.0};
    coder::array<double, 2U> r;
    coder::array<double, 2U> r1;
    coder::array<signed char, 2U> r2;
    double A[7];
    double B[7];
    int i;
    int trueCount;
    boolean_T idx[8];
    //  Author: Christophe Couvreur, Faculte Polytechnique de Mons (Belgium)
    //          couvreur@thor.fpms.ac.be
    //  Last modification: Aug. 23, 1997, 10:30pm.
    //  References:
    //     [1] ANSI S1.1-1986 (ASA 65-1986): Specifications for
    //         Octave-Band and Fractional-Octave-Band Analog and
    //         Digital Filters, 1993.
    //     [2] S. J. Orfanidis, Introduction to Signal Processing,
    //         Prentice Hall, Englewood Cliffs, 1996.
    // Fs = 44100; 				% Sampling Frequency
    // 'octbank:27' N = 3;
    //  Order of analysis filters.
    // 'octbank:28' F = [63 125 250 500 1000 2000 4000 8000];
    //  Preferred labeling freq.
    // 'octbank:29' ff = (1000) .* ((2^(1/1)).^[-4:3]);
    //  Exact center freq.
    // 'octbank:30' P = zeros(1, 8);
    // 'octbank:31' m = length(x);
    //  Design filters and compute RMS powers in 1/1-oct. bands
    //  5000 Hz band to 1600 Hz band, direct implementation of filters.
    // 'octbank:35' for i = 8:-1:1
    for (i = 0; i < 8; i++) {
        // 'octbank:36' [B, A] = octdsgn(ff(i), Fs, N);
        octdsgn(b_dv[7 - i], B, A);
        // 'octbank:37' y = filter(B, A, x);
        // 'octbank:38' P(i) = sum(y.^2) / m;
        coder::filter(B, A, x, r);
        coder::power(r, r1);
        p[7 - i] = coder::sum(r1) / static_cast<double>(x.size(1));
    }
    //  1250 Hz to 100 Hz, multirate filter implementation (see [2]).
    // [Bu,Au] = oct3dsgn(ff(18),Fs,N); 	% Upper 1/3-oct. band in last octave.
    // [Bc,Ac] = oct3dsgn(ff(17),Fs,N); 	% Center 1/3-oct. band in last octave.
    // [Bl,Al] = oct3dsgn(ff(16),Fs,N); 	% Lower 1/3-oct. band in last octave.
    // for j = 4:-1:0
    //    x = decimate(x,2);
    //    m = length(x);
    //    y = filter(Bu,Au,x);
    //    P(j*3+3) = sum(y.^2)/m;
    //    y = filter(Bc,Ac,x);
    //    P(j*3+2) = sum(y.^2)/m;
    //    y = filter(Bl,Al,x);
    //    P(j*3+1) = sum(y.^2)/m;
    // end
    //  Convert to decibels.
    // 'octbank:57' Pref = 1;
    //  Reference level for dB scale.
    // 'octbank:58' idx = (P > 0);
    // 'octbank:59' P(idx) = 10 * log10(P(idx) / Pref);
    trueCount = 0;
    for (i = 0; i < 8; i++) {
        double d;
        d = p[i];
        idx[i] = (d > 0.0);
        if (d > 0.0) {
            trueCount++;
        }
    }
    r2.set_size(1, trueCount);
    trueCount = 0;
    for (i = 0; i < 8; i++) {
        if (p[i] > 0.0) {
            r2[trueCount] = static_cast<signed char>(i + 1);
            trueCount++;
        }
    }
    r.set_size(1, r2.size(1));
    trueCount = r2.size(1);
    for (i = 0; i < trueCount; i++) {
        r[i] = p[r2[i] - 1];
    }
    coder::b_log10(r);
    r.set_size(1, r.size(1));
    trueCount = r.size(1) - 1;
    for (i = 0; i <= trueCount; i++) {
        r[i] = 10.0 * r[i];
    }
    trueCount = 0;
    // 'octbank:60' P(~idx) = NaN * ones(sum(~idx), 1);
    for (i = 0; i < 8; i++) {
        if (p[i] > 0.0) {
            p[i] = r[trueCount];
            trueCount++;
        }
        if (!idx[i]) {
            p[i] = rtNaN;
        }
    }
    //  Generate the plot
    // 'octbank:63' if (nargout == 1)
    // 'octbank:65' elseif (nargout == 2)
    // 'octbank:66' p = P;
    // 'octbank:67' f = F;
}

//
// File trailer for octbank.cpp
//
// [EOF]
//
