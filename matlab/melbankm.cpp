//
// File: melbankm.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "melbankm.h"
#include "colon.h"
#include "find.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [x, mc, mn, mx] = melbankm(p, n, fs, fl, fh, w)
//
// MELBANKM determine matrix for a mel/erb/bark-spaced filterbank
// [X,MN,MX]=(P,N,FS,FL,FH,W)
//
//  Inputs:
//        p   number of filters in filterbank or the filter spacing in
//        k-mel/bark/erb [ceil(4.6*log10(fs))]
//   n   length of fft
//   fs  sample rate in Hz
//   fl  low end of the lowest filter as a fraction of fs [default = 0]
//   fh  high end of highest filter as a fraction of fs [default = 0.5]
//   w   any sensible combination of the following:
//              'b' = bark scale instead of mel
//              'e' = erb-rate scale
//              'l' = log10 Hz frequency scale
//              'f' = linear frequency scale
//
//              'c' = fl/fh specify centre of low and high filters
//              'h' = fl/fh are in Hz instead of fractions of fs
//              'H' = fl/fh are in mel/erb/bark/log10
//
//         't' = triangular shaped filters in mel/erb/bark domain (default)
//         'n' = hanning shaped filters in mel/erb/bark domain
//         'm' = hamming shaped filters in mel/erb/bark domain
//
//         'z' = highest and lowest filters taper down to zero [default]
//         'y' = lowest filter remains at 1 down to 0 frequency and
//            highest filter remains at 1 up to nyquist freqency
//
//              'u' = scale filters to sum to unity
//
//              's' = single-sided: do not double filters to account for
//              negative frequencies
//
//              'g' = plot idealized filters [default if no output arguments
//              present]
//
//  Note that the filter shape (triangular, hamming etc) is defined in the mel
//  (or erb etc) domain. Some people instead define an asymmetric triangular
//  filter in the frequency domain.
//
//          If 'ty' or 'ny' is specified, the total power in the fft is
//          preserved.
//
//  Outputs: x     a sparse matrix containing the filterbank amplitudes
//             If the mn and mx outputs are given then size(x)=[p,mx-mn+1]
//                  otherwise size(x)=[p,1+floor(n/2)]
//                  Note that the peak filter values equal 2 to account for the
//                  power in the negative FFT frequencies.
//            mc    the filterbank centre frequencies in mel/erb/bark
//       mn    the lowest fft bin with a non-zero coefficient
//       mx    the highest fft bin with a non-zero coefficient
//                  Note: you must specify both or neither of mn and mx.
//
//  Examples of use:
//
//  (a) Calcuate the Mel-frequency Cepstral Coefficients
//
//        f=rfft(s);           % rfft() returns only 1+floor(n/2) coefficients
//   x=melbankm(p,n,fs);         % n is the fft length, p is the number of
//   filters wanted z=log(x*abs(f).^2);         % multiply x by the power
//   spectrum c=dct(z);                   % take the DCT
//
//  (b) Calcuate the Mel-frequency Cepstral Coefficients efficiently
//
//        f=fft(s);                        % n is the fft length, p is the
//        number of filters wanted [x,mc,na,nb]=melbankm(p,n,fs);   % na:nb
//        gives the fft bins that are needed
//        z=log(x*(f(na:nb)).*conj(f(na:nb)));
//
//  (c) Plot the calculated filterbanks
//
//       plot((0:floor(n/2))*fs/n,melbankm(p,n,fs)')   % fs=sample frequency
//
//  (d) Plot the idealized filterbanks (without output sampling)
//
//       melbankm(p,n,fs);
//
//  References:
//
//  [1] S. S. Stevens, J. Volkman, and E. B. Newman. A scale for the measurement
//      of the psychological magnitude of pitch. J. Acoust Soc Amer, 8: 185�19,
//      1937.
//  [2] S. Davis and P. Mermelstein. Comparison of parametric representations
//  for
//      monosyllabic word recognition in continuously spoken sentences.
//      IEEE Trans Acoustics Speech and Signal Processing, 28 (4): 357�366, Aug.
//      1980.
//
// Arguments    : double n
//                double fs
//                coder::sparse *x
// Return Type  : void
//
void melbankm(double n, double fs, coder::sparse *x)
{
  coder::array<double, 2U> af;
  coder::array<double, 2U> c;
  coder::array<double, 2U> fp;
  coder::array<double, 2U> pf;
  coder::array<double, 2U> v;
  coder::array<int, 2U> r1;
  coder::array<boolean_T, 2U> b_fp;
  coder::array<boolean_T, 2U> r;
  double b1;
  double b_x;
  double blim_idx_0;
  double c_x;
  double d;
  double fn2;
  double k2_data;
  double melinc;
  double mflh_idx_0;
  int i_size[2];
  int b_k;
  int b_loop_ub;
  int i;
  int k;
  int k2_size_idx_1;
  unsigned int k3_data;
  int loop_ub;
  int nx;
  int nxout;
  boolean_T exitg1;
  //       Copyright (C) Mike Brookes 1997-2009
  //       Version: $Id: melbankm.m,v 1.11 2010/01/02 20:02:22 dmb Exp $
  //
  //    VOICEBOX is a MATLAB toolbox for speech processing.
  //    Home page: http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/voicebox.html
  //
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //    This program is free software; you can redistribute it and/or modify
  //    it under the terms of the GNU General Public License as published by
  //    the Free Software Foundation; either version 2 of the License, or
  //    (at your option) any later version.
  //
  //    This program is distributed in the hope that it will be useful,
  //    but WITHOUT ANY WARRANTY; without even the implied warranty of
  //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //    GNU General Public License for more details.
  //
  //    You can obtain a copy of the GNU General Public License from
  //    http://www.gnu.org/copyleft/gpl.html or by writing to
  //    Free Software Foundation, Inc.,675 Mass Ave, Cambridge, MA 02139, USA.
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //  Note "FFT bin_0" assumes DC = bin 0 whereas "FFT bin_1" means DC = bin 1
  // 'melbankm:104' if nargin < 6
  // 'melbankm:118' sfact = 2 - any(w == 's');
  //  1 if single sided else 2
  // 'melbankm:119' wr = ' ';
  //  default warping is mel
  // 'melbankm:121' for i = 1:length(w)
  // 'melbankm:123' if any(w(i) == 'lebf')
  // 'melbankm:129' if any(w == 'h') || any(w == 'H')
  // 'melbankm:131' else
  // 'melbankm:132' mflh = [fl fh] * fs;
  // 'melbankm:135' if ~any(w == 'H')
  // 'melbankm:137' switch wr
  // 'melbankm:150' otherwise
  // 'melbankm:151' mflh = frq2mel(mflh);
  // FRQ2ERB  Convert Hertz to Mel frequency scale MEL=(FRQ)
  // 	[mel,mr] = frq2mel(frq) converts a vector of frequencies (in Hz)
  // 	to the corresponding values on the Mel scale which corresponds
  // 	to the perceived pitch of a tone.
  //    mr gives the corresponding gradients in Hz/mel.
  // 	The relationship between mel and frq is given by:
  //
  // 	m = ln(1 + f/700) * 1000 / ln(1+1000/700)
  //
  //   	This means that m(1000) = 1000
  //
  // 	References:
  //
  // 	  [1] S. S. Stevens & J. Volkman "The relation of pitch to
  // 		frequency", American J of Psychology, V 53, p329 1940
  // 	  [2] C. G. M. Fant, "Acoustic description & classification
  // 		of phonetic units", Ericsson Tchnics, No 1 1959
  // 		(reprinted in "Speech Sounds & Features", MIT Press 1973)
  // 	  [3] S. B. Davis & P. Mermelstein, "Comparison of parametric
  // 		representations for monosyllabic word recognition in
  // 		continuously spoken sentences", IEEE ASSP, V 28,
  // 		pp 357-366 Aug 1980
  // 	  [4] J. R. Deller Jr, J. G. Proakis, J. H. L. Hansen,
  // 		"Discrete-Time Processing of Speech Signals", p380,
  // 		Macmillan 1993
  // 	  [5] HTK Reference Manual p73
  //
  //       Copyright (C) Mike Brookes 1998
  //       Version: $Id: frq2mel.m,v 1.7 2010/08/01 08:41:57 dmb Exp $
  //
  //    VOICEBOX is a MATLAB toolbox for speech processing.
  //    Home page: http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/voicebox.html
  //
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //    This program is free software; you can redistribute it and/or modify
  //    it under the terms of the GNU General Public License as published by
  //    the Free Software Foundation; either version 2 of the License, or
  //    (at your option) any later version.
  //
  //    This program is distributed in the hope that it will be useful,
  //    but WITHOUT ANY WARRANTY; without even the implied warranty of
  //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //    GNU General Public License for more details.
  //
  //    You can obtain a copy of the GNU General Public License from
  //    http://www.gnu.org/copyleft/gpl.html or by writing to
  //    Free Software Foundation, Inc.,675 Mass Ave, Cambridge, MA 02139, USA.
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // 'frq2mel:54' if isempty(k)
  // 'frq2mel:58' af = abs(frq);
  // 'frq2mel:59' mel = sign(frq) .* log(1 + af / 700) * k;
  // 'frq2mel:60' mr = (700 + af) / k;
  // 'frq2mel:62' if ~nargout
  //  convert frequency limits into mel
  // 'melbankm:156' melrng = mflh * (-1:2:1)';
  //  mel range
  // 'melbankm:157' fn2 = floor(n / 2);
  fn2 = std::floor(n / 2.0);
  //  bin index of highest positive frequency (Nyquist if n is even)
  // 'melbankm:159' if isempty(p)
  // 'melbankm:163' if any(w == 'c')
  // 'melbankm:171' else
  // 'melbankm:173' if p < 1
  // 'melbankm:177' melinc = melrng / (p + 1);
  d = 0.0 * fs;
  b_x = d;
  if (d == 0.0) {
    b_x = 0.0;
  }
  d = b_x * std::log(d / 700.0 + 1.0) * 1127.01048;
  mflh_idx_0 = d;
  k2_data = -d;
  d = 0.5 * fs;
  b_x = d;
  if (d < 0.0) {
    b_x = -1.0;
  } else if (d > 0.0) {
    b_x = 1.0;
  } else if (d == 0.0) {
    b_x = 0.0;
  }
  d = b_x * std::log(std::abs(d) / 700.0 + 1.0) * 1127.01048;
  k2_data += d;
  melinc = k2_data / 17.0;
  //
  //  Calculate the FFT bins corresponding to [filter#1-low filter#1-mid
  //  filter#p-mid filter#p-high]
  //
  // 'melbankm:183' switch wr
  // 'melbankm:192' otherwise
  // 'melbankm:193' blim = mel2frq(mflh(1) + [0 1 p p + 1] * melinc) * n / fs;
  // MEL2FRQ  Convert Mel frequency scale to Hertz FRQ=(MEL)
  // 	frq = mel2frq(mel) converts a vector of Mel frequencies
  // 	to the corresponding real frequencies.
  //    mr gives the corresponding gradients in Hz/mel.
  // 	The Mel scale corresponds to the perceived pitch of a tone
  // 	The relationship between mel and frq is given by:
  //
  // 	m = ln(1 + f/700) * 1000 / ln(1+1000/700)
  //
  //   	This means that m(1000) = 1000
  //
  // 	References:
  //
  // 	  [1] S. S. Stevens & J. Volkman "The relation of pitch to
  // 		frequency", American J of Psychology, V 53, p329 1940
  // 	  [2] C. G. M. Fant, "Acoustic description & classification
  // 		of phonetic units", Ericsson Tchnics, No 1 1959
  // 		(reprinted in "Speech Sounds & Features", MIT Press 1973)
  // 	  [3] S. B. Davis & P. Mermelstein, "Comparison of parametric
  // 		representations for monosyllabic word recognition in
  // 		continuously spoken sentences", IEEE ASSP, V 28,
  // 		pp 357-366 Aug 1980
  // 	  [4] J. R. Deller Jr, J. G. Proakis, J. H. L. Hansen,
  // 		"Discrete-Time Processing of Speech Signals", p380,
  // 		Macmillan 1993
  // 	  [5] HTK Reference Manual p73
  //
  //       Copyright (C) Mike Brookes 1998
  //       Version: $Id: mel2frq.m,v 1.7 2010/08/01 08:41:57 dmb Exp $
  //
  //    VOICEBOX is a MATLAB toolbox for speech processing.
  //    Home page: http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/voicebox.html
  //
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //    This program is free software; you can redistribute it and/or modify
  //    it under the terms of the GNU General Public License as published by
  //    the Free Software Foundation; either version 2 of the License, or
  //    (at your option) any later version.
  //
  //    This program is distributed in the hope that it will be useful,
  //    but WITHOUT ANY WARRANTY; without even the implied warranty of
  //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //    GNU General Public License for more details.
  //
  //    You can obtain a copy of the GNU General Public License from
  //    http://www.gnu.org/copyleft/gpl.html or by writing to
  //    Free Software Foundation, Inc.,675 Mass Ave, Cambridge, MA 02139, USA.
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // 'mel2frq:54' if isempty(k)
  // 'mel2frq:58' frq = 700 * sign(mel) .* (exp(abs(mel) / k) - 1);
  // 'mel2frq:59' mr = (700 + abs(frq)) / k;
  // 'mel2frq:61' if ~nargout
  d = mflh_idx_0 + 0.0 * melinc;
  b_x = d;
  if (d == 0.0) {
    b_x = 0.0;
  }
  blim_idx_0 = 700.0 * b_x * (std::exp(d / 1127.01048) - 1.0) * n / fs;
  d = mflh_idx_0 + 17.0 * melinc;
  b_x = d;
  if (d < 0.0) {
    b_x = -1.0;
  } else if (d > 0.0) {
    b_x = 1.0;
  } else if (d == 0.0) {
    b_x = 0.0;
  }
  // 'melbankm:196' mc = mflh(1) + (1:p) * melinc;
  //  mel centre frequencies
  // 'melbankm:197' b1 = floor(blim(1)) + 1;
  b1 = blim_idx_0 + 1.0;
  //  lowest FFT bin_0 required might be negative)
  // 'melbankm:198' b4 = min(fn2, ceil(blim(4)) - 1);
  k2_data = std::fmin(
      fn2, std::ceil(700.0 * b_x * (std::exp(std::abs(d) / 1127.01048) - 1.0) *
                     n / fs) -
               1.0);
  //  highest FFT bin_0 required
  //
  //  now map all the useful FFT bins_0 to filter1 centres
  //
  // 'melbankm:202' switch wr
  // 'melbankm:211' otherwise
  // 'melbankm:212' pf = (frq2mel((b1:b4) * fs / n) - mflh(1)) / melinc;
  if (std::isnan(blim_idx_0 + 1.0) || std::isnan(k2_data)) {
    pf.set_size(1, 1);
    pf[0] = rtNaN;
  } else if (k2_data < blim_idx_0 + 1.0) {
    pf.set_size(pf.size(0), 0);
  } else if (std::isinf(k2_data) && (blim_idx_0 + 1.0 == k2_data)) {
    pf.set_size(1, 1);
    pf[0] = rtNaN;
  } else if (blim_idx_0 + 1.0 == blim_idx_0 + 1.0) {
    d = blim_idx_0 + 1.0;
    loop_ub = static_cast<int>(k2_data - (blim_idx_0 + 1.0));
    pf.set_size(1, loop_ub + 1);
    if (static_cast<int>(loop_ub + 1 < 1200)) {
      for (k = 0; k <= loop_ub; k++) {
        pf[k] = (blim_idx_0 + 1.0) + static_cast<double>(k);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = 0; k <= loop_ub; k++) {
        pf[k] = d + static_cast<double>(k);
      }
    }
  } else {
    coder::eml_float_colon(blim_idx_0 + 1.0, k2_data, pf);
  }
  pf.set_size(1, pf.size(1));
  loop_ub = pf.size(1) - 1;
  b_loop_ub = pf.size(1) - 1;
  if (static_cast<int>(pf.size(1) < 1200)) {
    for (k = 0; k <= loop_ub; k++) {
      pf[k] = pf[k] * fs / n;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= b_loop_ub; k++) {
      pf[k] = pf[k] * fs / n;
    }
  }
  // FRQ2ERB  Convert Hertz to Mel frequency scale MEL=(FRQ)
  // 	[mel,mr] = frq2mel(frq) converts a vector of frequencies (in Hz)
  // 	to the corresponding values on the Mel scale which corresponds
  // 	to the perceived pitch of a tone.
  //    mr gives the corresponding gradients in Hz/mel.
  // 	The relationship between mel and frq is given by:
  //
  // 	m = ln(1 + f/700) * 1000 / ln(1+1000/700)
  //
  //   	This means that m(1000) = 1000
  //
  // 	References:
  //
  // 	  [1] S. S. Stevens & J. Volkman "The relation of pitch to
  // 		frequency", American J of Psychology, V 53, p329 1940
  // 	  [2] C. G. M. Fant, "Acoustic description & classification
  // 		of phonetic units", Ericsson Tchnics, No 1 1959
  // 		(reprinted in "Speech Sounds & Features", MIT Press 1973)
  // 	  [3] S. B. Davis & P. Mermelstein, "Comparison of parametric
  // 		representations for monosyllabic word recognition in
  // 		continuously spoken sentences", IEEE ASSP, V 28,
  // 		pp 357-366 Aug 1980
  // 	  [4] J. R. Deller Jr, J. G. Proakis, J. H. L. Hansen,
  // 		"Discrete-Time Processing of Speech Signals", p380,
  // 		Macmillan 1993
  // 	  [5] HTK Reference Manual p73
  //
  //       Copyright (C) Mike Brookes 1998
  //       Version: $Id: frq2mel.m,v 1.7 2010/08/01 08:41:57 dmb Exp $
  //
  //    VOICEBOX is a MATLAB toolbox for speech processing.
  //    Home page: http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/voicebox.html
  //
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //    This program is free software; you can redistribute it and/or modify
  //    it under the terms of the GNU General Public License as published by
  //    the Free Software Foundation; either version 2 of the License, or
  //    (at your option) any later version.
  //
  //    This program is distributed in the hope that it will be useful,
  //    but WITHOUT ANY WARRANTY; without even the implied warranty of
  //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //    GNU General Public License for more details.
  //
  //    You can obtain a copy of the GNU General Public License from
  //    http://www.gnu.org/copyleft/gpl.html or by writing to
  //    Free Software Foundation, Inc.,675 Mass Ave, Cambridge, MA 02139, USA.
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // 'frq2mel:54' if isempty(k)
  // 'frq2mel:58' af = abs(frq);
  nx = pf.size(1);
  af.set_size(1, pf.size(1));
  if (static_cast<int>(pf.size(1) < 1200)) {
    for (k = 0; k < nx; k++) {
      af[k] = std::abs(pf[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      af[k] = std::abs(pf[k]);
    }
  }
  // 'frq2mel:59' mel = sign(frq) .* log(1 + af / 700) * k;
  nx = pf.size(1);
  if (static_cast<int>(pf.size(1) < 1200)) {
    for (k = 0; k < nx; k++) {
      c_x = pf[k];
      if (c_x < 0.0) {
        c_x = -1.0;
      } else if (c_x > 0.0) {
        c_x = 1.0;
      } else if (c_x == 0.0) {
        c_x = 0.0;
      }
      pf[k] = c_x;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(c_x, k)

    for (k = 0; k < nx; k++) {
      c_x = pf[k];
      if (c_x < 0.0) {
        c_x = -1.0;
      } else if (c_x > 0.0) {
        c_x = 1.0;
      } else if (c_x == 0.0) {
        c_x = 0.0;
      }
      pf[k] = c_x;
    }
  }
  af.set_size(1, af.size(1));
  nxout = af.size(1) - 1;
  loop_ub = af.size(1) - 1;
  if (static_cast<int>(af.size(1) < 1200)) {
    for (k = 0; k <= nxout; k++) {
      af[k] = af[k] / 700.0 + 1.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= loop_ub; k++) {
      af[k] = af[k] / 700.0 + 1.0;
    }
  }
  nx = af.size(1);
  if (static_cast<int>(af.size(1) < 1200)) {
    for (k = 0; k < nx; k++) {
      af[k] = std::log(af[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      af[k] = std::log(af[k]);
    }
  }
  // 'frq2mel:60' mr = (700 + af) / k;
  // 'frq2mel:62' if ~nargout
  pf.set_size(1, pf.size(1));
  nxout = pf.size(1) - 1;
  loop_ub = pf.size(1) - 1;
  if (static_cast<int>(pf.size(1) < 1200)) {
    for (k = 0; k <= nxout; k++) {
      pf[k] = (pf[k] * af[k] * 1127.01048 - mflh_idx_0) / melinc;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= loop_ub; k++) {
      pf[k] = (pf[k] * af[k] * 1127.01048 - mflh_idx_0) / melinc;
    }
  }
  //
  //   remove any incorrect entries in pf due to rounding errors
  //
  // 'melbankm:218' if pf(1) < 0
  if (pf[0] < 0.0) {
    // 'melbankm:219' pf(1) = [];
    nx = pf.size(1);
    nxout = pf.size(1) - 1;
    for (b_k = 0; b_k < nxout; b_k++) {
      pf[b_k] = pf[b_k + 1];
    }
    if (1 > nxout) {
      i = 0;
    } else {
      i = nx - 1;
    }
    pf.set_size(pf.size(0), i);
    // 'melbankm:220' b1 = b1 + 1;
    b1 = (blim_idx_0 + 1.0) + 1.0;
  }
  // 'melbankm:223' if pf(end) >= p + 1
  if (pf[pf.size(1) - 1] >= 17.0) {
    // 'melbankm:224' pf(end) = [];
    b_loop_ub = pf.size(1);
    nx = pf.size(1);
    nxout = pf.size(1) - 1;
    for (b_k = b_loop_ub; b_k <= nxout; b_k++) {
      pf[b_k - 1] = pf[b_k];
    }
    if (1 > nxout) {
      i = 0;
    } else {
      i = nx - 1;
    }
    pf.set_size(pf.size(0), i);
    // 'melbankm:225' b4 = b4 - 1;
  }
  // 'melbankm:228' fp = floor(pf);
  fp.set_size(1, pf.size(1));
  loop_ub = pf.size(1);
  if (static_cast<int>(pf.size(1) < 1200)) {
    for (k = 0; k < loop_ub; k++) {
      fp[k] = pf[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < loop_ub; k++) {
      fp[k] = pf[k];
    }
  }
  nx = pf.size(1);
  if (static_cast<int>(pf.size(1) < 1200)) {
    for (k = 0; k < nx; k++) {
      fp[k] = std::floor(fp[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      fp[k] = std::floor(fp[k]);
    }
  }
  //  FFT bin_0 i contributes to filters_1 fp(1+i-b1)+[0 1]
  // 'melbankm:229' pm = pf - fp;
  pf.set_size(1, pf.size(1));
  nxout = pf.size(1) - 1;
  loop_ub = pf.size(1) - 1;
  if (static_cast<int>(pf.size(1) < 1200)) {
    for (k = 0; k <= nxout; k++) {
      pf[k] = pf[k] - fp[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= loop_ub; k++) {
      pf[k] = pf[k] - fp[k];
    }
  }
  //  multiplier for upper filter
  // 'melbankm:230' k2 = find(fp > 0, 1);
  b_fp.set_size(1, fp.size(1));
  loop_ub = fp.size(1);
  if (static_cast<int>(fp.size(1) < 1200)) {
    for (k = 0; k < loop_ub; k++) {
      b_fp[k] = (fp[k] > 0.0);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < loop_ub; k++) {
      b_fp[k] = (fp[k] > 0.0);
    }
  }
  coder::eml_find(b_fp, (int *)&nx, i_size);
  k2_size_idx_1 = i_size[1];
  loop_ub = i_size[1];
  for (i = 0; i < loop_ub; i++) {
    k2_data = nx;
  }
  //  FFT bin_1 k2+b1 is the first to contribute to both upper and lower filters
  // 'melbankm:231' k3 = find(fp < p, 1, 'last');
  b_fp.set_size(1, fp.size(1));
  loop_ub = fp.size(1);
  if (static_cast<int>(fp.size(1) < 1200)) {
    for (k = 0; k < loop_ub; k++) {
      b_fp[k] = (fp[k] < 16.0);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < loop_ub; k++) {
      b_fp[k] = (fp[k] < 16.0);
    }
  }
  b_k = (1 <= b_fp.size(1));
  nxout = b_fp.size(1);
  b_loop_ub = 0;
  i_size[1] = b_k;
  exitg1 = false;
  while ((!exitg1) && (nxout > 0)) {
    if (b_fp[nxout - 1]) {
      b_loop_ub = 1;
      nx = nxout;
      exitg1 = true;
    } else {
      nxout--;
    }
  }
  if (b_k == 1) {
    if (b_loop_ub == 0) {
      i_size[1] = 0;
    }
  } else {
    i_size[1] = (1 <= b_loop_ub);
  }
  loop_ub = i_size[1];
  for (i = 0; i < loop_ub; i++) {
    k3_data = static_cast<unsigned int>(nx);
  }
  //  FFT bin_1 k3+b1 is the last to contribute to both upper and lower filters
  // 'melbankm:232' k4 = numel(fp);
  //  FFT bin_1 k4+b1 is the last to contribute to any filters
  // 'melbankm:234' if isempty(k2)
  if (k2_size_idx_1 == 0) {
    // 'melbankm:235' k2 = k4 + 1;
    k2_data = static_cast<double>(fp.size(1)) + 1.0;
  }
  // 'melbankm:238' if isempty(k3)
  if (i_size[1] == 0) {
    // 'melbankm:239' k3 = 0;
    k3_data = 0U;
  }
  // 'melbankm:242' if any(w == 'y')
  // 'melbankm:248' else
  // 'melbankm:249' r = [1 + fp(1:k3(1)) fp(k2(1):k4)];
  if (1 > static_cast<int>(k3_data)) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(k3_data);
  }
  if (k2_data > fp.size(1)) {
    i = 0;
    b_k = 0;
  } else {
    i = static_cast<int>(k2_data) - 1;
    b_k = fp.size(1);
  }
  //  filter number_1
  // 'melbankm:250' c = [1:k3 k2:k4];
  if (static_cast<int>(k3_data) < 1) {
    af.set_size(1, 0);
  } else {
    nx = static_cast<int>(k3_data);
    af.set_size(1, nx);
    b_loop_ub = static_cast<int>(k3_data) - 1;
    if (static_cast<int>(static_cast<int>(k3_data) < 1200)) {
      for (k = 0; k <= b_loop_ub; k++) {
        af[k] = static_cast<double>(k) + 1.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = 0; k <= b_loop_ub; k++) {
        af[k] = static_cast<double>(k) + 1.0;
      }
    }
  }
  if (fp.size(1) < k2_data) {
    v.set_size(1, 0);
  } else if (k2_data == k2_data) {
    v.set_size(1, (fp.size(1) - static_cast<int>(k2_data)) + 1);
    b_loop_ub = fp.size(1) - static_cast<int>(k2_data);
    if (static_cast<int>(b_loop_ub + 1 < 1200)) {
      for (k = 0; k <= b_loop_ub; k++) {
        v[k] = k2_data + static_cast<double>(k);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = 0; k <= b_loop_ub; k++) {
        v[k] = k2_data + static_cast<double>(k);
      }
    }
  } else {
    coder::eml_float_colon(k2_data, static_cast<double>(fp.size(1)), v);
  }
  c.set_size(1, af.size(1) + v.size(1));
  b_loop_ub = af.size(1);
  if (static_cast<int>(af.size(1) < 1200)) {
    for (k = 0; k < b_loop_ub; k++) {
      c[k] = af[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < b_loop_ub; k++) {
      c[k] = af[k];
    }
  }
  b_loop_ub = v.size(1);
  if (static_cast<int>(v.size(1) < 1200)) {
    for (k = 0; k < b_loop_ub; k++) {
      c[k + af.size(1)] = v[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < b_loop_ub; k++) {
      c[k + af.size(1)] = v[k];
    }
  }
  //  FFT bin_1 - b1
  // 'melbankm:251' v = [pm(1:k3(1)) 1 - pm(k2(1):k4)];
  if (1 > static_cast<int>(k3_data)) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = static_cast<int>(k3_data);
  }
  if (k2_data > fp.size(1)) {
    nx = 0;
    nxout = 0;
  } else {
    nx = static_cast<int>(k2_data) - 1;
    nxout = fp.size(1);
  }
  // 'melbankm:252' mn = b1 + 1;
  //  lowest fft bin_1
  // 'melbankm:253' mx = b4 + 1;
  //  highest fft bin_1
  // 'melbankm:256' if b1 < 0
  //  end
  // 'melbankm:261' if any(w == 'n')
  // 'melbankm:263' elseif any(w == 'm')
  // 'melbankm:264' v = 0.5 - 0.46/1.08 * cos(v * pi);
  v.set_size(1, (b_loop_ub + nxout) - nx);
  if (static_cast<int>(b_loop_ub < 1200)) {
    for (k = 0; k < b_loop_ub; k++) {
      v[k] = pf[k] * 3.1415926535897931;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < b_loop_ub; k++) {
      v[k] = pf[k] * 3.1415926535897931;
    }
  }
  nxout -= nx;
  if (static_cast<int>(nxout < 1200)) {
    for (k = 0; k < nxout; k++) {
      v[k + b_loop_ub] = (1.0 - pf[nx + k]) * 3.1415926535897931;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nxout; k++) {
      v[k + b_loop_ub] = (1.0 - pf[nx + k]) * 3.1415926535897931;
    }
  }
  nx = v.size(1);
  if (static_cast<int>(v.size(1) < 1200)) {
    for (k = 0; k < nx; k++) {
      v[k] = std::cos(v[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      v[k] = std::cos(v[k]);
    }
  }
  v.set_size(1, v.size(1));
  nxout = v.size(1) - 1;
  b_loop_ub = v.size(1) - 1;
  if (static_cast<int>(v.size(1) < 1200)) {
    for (k = 0; k <= nxout; k++) {
      v[k] = 0.5 - 0.42592592592592593 * v[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= b_loop_ub; k++) {
      v[k] = 0.5 - 0.42592592592592593 * v[k];
    }
  }
  //  convert triangles to Hamming
  // 'melbankm:267' if sfact == 2
  //  double all except the DC and Nyquist (if any) terms
  // 'melbankm:268' msk = (c + mn > 2) & (c + mn < n - fn2 + 2);
  af.set_size(1, c.size(1));
  k2_data = b1 + 1.0;
  b_loop_ub = c.size(1);
  if (static_cast<int>(c.size(1) < 1200)) {
    for (k = 0; k < b_loop_ub; k++) {
      af[k] = c[k] + (b1 + 1.0);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < b_loop_ub; k++) {
      af[k] = c[k] + k2_data;
    }
  }
  b_fp.set_size(1, af.size(1));
  b_loop_ub = af.size(1);
  if (static_cast<int>(af.size(1) < 1200)) {
    for (k = 0; k < b_loop_ub; k++) {
      b_fp[k] = (af[k] > 2.0);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < b_loop_ub; k++) {
      b_fp[k] = (af[k] > 2.0);
    }
  }
  r.set_size(1, af.size(1));
  k2_data = (n - fn2) + 2.0;
  b_loop_ub = af.size(1);
  if (static_cast<int>(af.size(1) < 1200)) {
    for (k = 0; k < b_loop_ub; k++) {
      r[k] = (af[k] < k2_data);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < b_loop_ub; k++) {
      r[k] = (af[k] < k2_data);
    }
  }
  //  there is no Nyquist term if n is odd
  // 'melbankm:269' v(msk) = 2 * v(msk);
  nx = b_fp.size(1) - 1;
  nxout = 0;
  for (b_loop_ub = 0; b_loop_ub <= nx; b_loop_ub++) {
    if (b_fp[b_loop_ub] && r[b_loop_ub]) {
      nxout++;
    }
  }
  r1.set_size(1, nxout);
  nxout = 0;
  for (b_loop_ub = 0; b_loop_ub <= nx; b_loop_ub++) {
    if (b_fp[b_loop_ub] && r[b_loop_ub]) {
      r1[nxout] = b_loop_ub + 1;
      nxout++;
    }
  }
  af.set_size(1, r1.size(1));
  b_loop_ub = r1.size(1);
  if (static_cast<int>(r1.size(1) < 1200)) {
    for (k = 0; k < b_loop_ub; k++) {
      af[k] = 2.0 * v[r1[k] - 1];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < b_loop_ub; k++) {
      af[k] = 2.0 * v[r1[k] - 1];
    }
  }
  nx = b_fp.size(1);
  nxout = 0;
  for (b_loop_ub = 0; b_loop_ub < nx; b_loop_ub++) {
    if (b_fp[b_loop_ub] && r[b_loop_ub]) {
      v[b_loop_ub] = af[nxout];
      nxout++;
    }
  }
  //
  //  sort out the output argument options
  //
  // 'melbankm:275' if nargout > 2
  // 'melbankm:283' else
  // 'melbankm:284' x = sparse(r, c + mn - 1, v, p, 1 + fn2);
  b1++;
  af.set_size(1, (loop_ub + b_k) - i);
  if (static_cast<int>(loop_ub < 1200)) {
    for (k = 0; k < loop_ub; k++) {
      af[k] = fp[k] + 1.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < loop_ub; k++) {
      af[k] = fp[k] + 1.0;
    }
  }
  b_loop_ub = b_k - i;
  if (static_cast<int>(b_loop_ub < 1200)) {
    for (k = 0; k < b_loop_ub; k++) {
      af[k + loop_ub] = fp[i + k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < b_loop_ub; k++) {
      af[k + loop_ub] = fp[i + k];
    }
  }
  pf.set_size(1, c.size(1));
  loop_ub = c.size(1);
  if (static_cast<int>(c.size(1) < 1200)) {
    for (k = 0; k < loop_ub; k++) {
      pf[k] = (c[k] + b1) - 1.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < loop_ub; k++) {
      pf[k] = (c[k] + b1) - 1.0;
    }
  }
  coder::b_sparse(af, pf, v, fn2 + 1.0, x);
  // 'melbankm:287' if any(w == 'u')
  //
  //  plot results if no output arguments or g option given
  //
  // 'melbankm:295' if ~nargout || any(w == 'g')
}

//
// File trailer for melbankm.cpp
//
// [EOF]
//
