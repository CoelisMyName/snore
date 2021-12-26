//
// File: v_enframe.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "v_enframe.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [f, t, w] = v_enframe(x, win, hop, m, fs)
//
// V_ENFRAME split signal up into (overlapping) frames: one per row.
// [F,T]=(X,WIN,HOP)
//
//  Usage:  (1) f=v_enframe(x,n)                          % split into frames of
//  length n
//          (2) f=v_enframe(x,hamming(n,'periodic'),n/4)  % use a 75% overlapped
//          Hamming window of length n (3) calculate spectrogram in units of
//          power per Hz
//
//                W=hamming(NW);                      % analysis window (NW =
//                fft length) P=v_enframe(S,W,HOP,'sdp',FS);        % computer
//                first half of PSD (HOP = frame increment in samples)
//
//          (3) frequency domain frame-based processing:
//
//                S=...;                              % input signal
//                OV=2;                               % overlap factor of 2 (4
//                is also often used) NW=16                          % DFT
//                window length W=sqrt(hamming(NW,'periodic'));     % omit sqrt
//                if OV=4 [F,T,WS]=v_enframe(S,W,1/OV,'fa');    % do STFT: one
//                row per time frame, +ve frequencies only
//                ... process frames ...
//                X=v_overlapadd(v_irfft(F,NW,2),WS,HOP); % reconstitute the
//                time waveform with scaled window (omit "X=" to plot waveform)
//
//   Inputs:   x    input signal
//           win    window or window length in samples
//           hop    frame increment or hop in samples or fraction of window
//           [window length]
//             m    mode input:
//                   'z'  zero pad to fill up final frame
//                   'r'  reflect last few samples for final frame
//                   'A'  calculate the t output as the centre of mass
//                   'E'  calculate the t output as the centre of energy
//                   'f'  perform a 1-sided dft on each frame (like v_rfft)
//                   'F'  perform a 2-sided dft on each frame using fft
//                   'p'  calculate the 1-sided power/energy spectrum of each
//                   frame 'P'  calculate the 2-sided power/energy spectrum of
//                   each frame 'a'  scale window to give unity gain with
//                   overlap-add 's'  scale window so that power is preserved:
//                   sum(mean(v_enframe(x,win,hop,'sp'),1))=mean(x.^2) 'S' scale
//                   window so that total energy is preserved:
//                   sum(sum(v_enframe(x,win,hop,'Sp')))=sum(x.^2) 'd'  make
//                   options 's' and 'S' give power/energy per Hz:
//                   sum(mean(v_enframe(x,win,hop,'sp'),1))*fs/length(win)=mean(x.^2)
//            fs    sample frequency (only needed for 'd' option) [1]
//
//  Outputs:   f    enframed data - one frame per row
//             t    fractional time in samples at the centre of each frame
//                  with the first sample being 1.
//             w    window function used
//
//  By default, the number of frames will be rounded down to the nearest
//  integer and the last few samples of x() will be ignored unless its length
//  is lw more than a multiple of hop. If the 'z' or 'r' options are given,
//  the number of frame will instead be rounded up and no samples will be
//  ignored.
//
//
// Arguments    : const coder::array<double, 1U> &x
//                coder::array<double, 1U> &win
//                double hop
//                coder::array<double, 2U> &f
// Return Type  : void
//
void v_enframe(const coder::array<double, 1U> &x, coder::array<double, 1U> &win,
               double hop, coder::array<double, 2U> &f)
{
  coder::array<double, 2U> inds;
  coder::array<double, 2U> w;
  coder::array<double, 1U> indf;
  double lw;
  double nf;
  int b_loop_ub;
  int c_loop_ub;
  int i;
  int i1;
  int loop_ub;
  //  Bugs/Suggestions:
  //   (1) Possible additional mode options:
  //         'u'  modify window for first and last few frames to ensure WOLA
  //         'a'  normalize window to give a mean of unity after overlaps
  //         'e'  normalize window to give an energy of unity after overlaps
  //         'wm' use Hamming window
  //         'wn' use Hanning window
  //         'x'  hoplude all frames that hoplude any of the x samples
  //        Copyright (C) Mike Brookes 1997-2014
  //       Version: $Id: v_enframe.m 12018-09-21 17:22:45Z dmb $
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
  // 'v_enframe:81' nx = length(x(:));
  // 'v_enframe:83' if nargin < 2 || isempty(win)
  if (win.size(0) == 0) {
    // 'v_enframe:84' win = nx;
    win.set_size(1);
    win[0] = x.size(0);
  }
  // 'v_enframe:87' if nargin < 4 || isempty(m)
  // 'v_enframe:88' m = '';
  // 'v_enframe:91' nwin = length(win);
  // 'v_enframe:93' if nwin == 1
  if (win.size(0) == 1) {
    // 'v_enframe:94' lw = win(1);
    lw = win[0];
    // 'v_enframe:95' w = ones(1, lw);
    loop_ub = static_cast<int>(win[0]);
    w.set_size(1, static_cast<int>(win[0]));
    b_loop_ub = static_cast<int>(win[0]);
    if (static_cast<int>(static_cast<int>(win[0]) < 1200)) {
      for (i = 0; i < loop_ub; i++) {
        w[i] = 1.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i < b_loop_ub; i++) {
        w[i] = 1.0;
      }
    }
  } else {
    // 'v_enframe:96' else
    // 'v_enframe:97' lw = nwin;
    lw = win.size(0);
    // 'v_enframe:98' w = win(:).';
    w.set_size(1, win.size(0));
    loop_ub = win.size(0);
    if (static_cast<int>(win.size(0) < 1200)) {
      for (i = 0; i < loop_ub; i++) {
        w[i] = win[i];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i < loop_ub; i++) {
        w[i] = win[i];
      }
    }
  }
  // 'v_enframe:101' if (nargin < 3) || isempty(hop)
  if (hop < 1.0) {
    // 'v_enframe:103' elseif hop < 1
    // 'v_enframe:104' hop = lw * hop;
    hop *= lw;
  }
  // 'v_enframe:107' if any(m == 'a')
  // 'v_enframe:115' if any(m == 'd')
  // 'v_enframe:125' nli = nx - lw + hop;
  // 'v_enframe:126' nf = max(fix(nli / hop), 0);
  nf = std::fmax(
      std::trunc(((static_cast<double>(x.size(0)) - lw) + hop) / hop), 0.0);
  //  number of full frames
  // 'v_enframe:127' na = nli - hop * nf + (nf == 0) * (lw - hop);
  //  number of samples left over
  // 'v_enframe:128' fx = nargin > 3 && (any(m == 'z') || any(m == 'r')) && na >
  // 0;
  //  need an extra row
  // 'v_enframe:129' f = zeros(nf + fx, lw);
  // 'v_enframe:130' indf = hop * (0:(nf - 1)).';
  if (nf - 1.0 < 0.0) {
    inds.set_size(1, 0);
  } else if (std::isinf(nf - 1.0) && (0.0 == nf - 1.0)) {
    inds.set_size(1, 1);
    inds[0] = rtNaN;
  } else {
    inds.set_size(1, static_cast<int>(nf - 1.0) + 1);
    loop_ub = static_cast<int>(nf - 1.0);
    if (static_cast<int>(static_cast<int>(nf - 1.0) + 1 < 1200)) {
      for (i = 0; i <= loop_ub; i++) {
        inds[i] = i;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i <= loop_ub; i++) {
        inds[i] = i;
      }
    }
  }
  indf.set_size(inds.size(1));
  loop_ub = inds.size(1);
  if (static_cast<int>(inds.size(1) < 1200)) {
    for (i = 0; i < loop_ub; i++) {
      indf[i] = hop * inds[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < loop_ub; i++) {
      indf[i] = hop * inds[i];
    }
  }
  // 'v_enframe:131' inds = (1:lw);
  if (lw < 1.0) {
    inds.set_size(1, 0);
  } else if (std::isinf(lw) && (1.0 == lw)) {
    inds.set_size(1, 1);
    inds[0] = rtNaN;
  } else {
    loop_ub = static_cast<int>(std::floor(lw - 1.0));
    inds.set_size(1, loop_ub + 1);
    if (static_cast<int>(loop_ub + 1 < 1200)) {
      for (i = 0; i <= loop_ub; i++) {
        inds[i] = static_cast<double>(i) + 1.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i <= loop_ub; i++) {
        inds[i] = static_cast<double>(i) + 1.0;
      }
    }
  }
  // 'v_enframe:133' if fx
  // 'v_enframe:144' else
  // 'v_enframe:145' f(:) = x(indf(:, ones(1, lw)) + inds(ones(nf, 1), :));
  loop_ub = indf.size(0);
  f.set_size(indf.size(0), static_cast<int>(lw));
  b_loop_ub = static_cast<int>(lw);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1, i)

  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      f[i1 + f.size(0) * i] = x[static_cast<int>(indf[i1] + inds[i]) - 1];
    }
  }
  // 'v_enframe:148' if (nwin > 1)
  if (win.size(0) > 1) {
    //  if we have a non-unity window
    // 'v_enframe:149' f = f .* w(ones(nf, 1), :);
    loop_ub = f.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i1, c_loop_ub, i)

    for (i = 0; i < loop_ub; i++) {
      c_loop_ub = f.size(0);
      for (i1 = 0; i1 < c_loop_ub; i1++) {
        f[i1 + f.size(0) * i] = f[i1 + f.size(0) * i] * w[i];
      }
    }
  }
  // 'v_enframe:152' if any(lower(m) == 'p')
  // 'v_enframe:171' if nargout > 1
}

//
// File trailer for v_enframe.cpp
//
// [EOF]
//
