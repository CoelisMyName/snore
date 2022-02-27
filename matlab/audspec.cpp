//
// File: audspec.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "audspec.h"
#include "ceil.h"
#include "fft2barkmx.h"
#include "hz2bark.h"
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [aspectrum, wts] = audspec(pspectrum, sr, nfilts, fbtype, minfreq,
// maxfreq, sumpower, bwidth)
//
// [aspectrum,wts] = audspec(pspectrum, sr, nfilts, fbtype, minfreq, maxfreq,
// sumpower, bwidth)
//
//  perform critical band analysis (see PLP)
//  takes power spectrogram as input
//
// Arguments    : const coder::array<double, 2U> &pspectrum
//                double sr
//                coder::array<double, 2U> &aspectrum
// Return Type  : void
//
void audspec(const coder::array<double, 2U> &pspectrum, double sr,
             coder::array<double, 2U> &aspectrum) {
    coder::array<double, 2U> wts;
    double d;
    int b_loop_ub;
    int b_wts;
    int loop_ub;
    // 'audspec:7' if nargin < 2
    // 'audspec:8' if nargin < 3
    // 'audspec:8' nfilts = ceil(hz2bark(sr / 2)) + 1;
    // 'audspec:9' if nargin < 4
    // 'audspec:9' fbtype = 'bark';
    // 'audspec:10' if nargin < 5
    // 'audspec:10' minfreq = 0;
    // 'audspec:11' if nargin < 6
    // 'audspec:11' maxfreq = sr / 2;
    // 'audspec:12' if nargin < 7
    // 'audspec:12' sumpower = 1;
    // 'audspec:13' if nargin < 8
    // 'audspec:13' bwidth = 1.0;
    // 'audspec:15' [nfreqs, ~] = size(pspectrum);
    // 'audspec:17' nfft = (nfreqs - 1) * 2;
    // 'audspec:19' if strcmp(fbtype, 'bark')
    // 'audspec:20' wts = fft2barkmx(nfft, sr, nfilts, bwidth, minfreq,
    // maxfreq);
    d = hz2bark(sr / 2.0);
    coder::b_ceil(&d);
    fft2barkmx((static_cast<double>(pspectrum.size(0)) - 1.0) * 2.0, sr,
               d + 1.0, sr / 2.0, wts);
    // 'audspec:32' wts = wts(:, 1:nfreqs);
    if (1 > pspectrum.size(0)) {
        loop_ub = 0;
    } else {
        loop_ub = pspectrum.size(0);
    }
    b_wts = wts.size(0) - 1;
    b_loop_ub = wts.size(0);
    for (int i = 0; i < loop_ub; i++) {
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            wts[i1 + (b_wts + 1) * i] = wts[i1 + wts.size(0) * i];
        }
    }
    wts.set_size(b_wts + 1, loop_ub);
    //  Integrate FFT bins into Mel bins, in abs or abs^2 domains:
    // 'audspec:35' if (sumpower)
    // 'audspec:36' aspectrum = wts * pspectrum;
    coder::internal::blas::mtimes(wts, pspectrum, aspectrum);
}

//
// File trailer for audspec.cpp
//
// [EOF]
//
