//
// File: mfcc_m.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "mfcc_m.h"
#include "SnoringRecognition_rtwutil.h"
#include "fft.h"
#include "hamming.h"
#include "melbankm.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// function ccc = mfcc_m(x, fs, p, frameSize, inc)
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//     function ccc=mfcc_m(x,fs,p,frameSize,inc)
// ���������������x����MFCC��������ȡ������MFCC������һ��
// ���MFCC������Mel�˲����ĸ���Ϊp������Ƶ��Ϊfs
// ��xÿframeSize���Ϊһ֡��������֮֡���֡��Ϊinc
//  FFT�ĳ���Ϊ֡��
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs
//                double frameSize
//                double inc
//                coder::array<double, 2U> &ccc
// Return Type  : void
//
void mfcc_m(const coder::array<double, 1U> &x, double fs, double frameSize,
            double inc, coder::array<double, 2U> &ccc)
{
  static const double b_dv[8]{0.4708715134557912,  0.74894866958846928,
                              0.93475388500967427, 1.0,
                              0.93475388500967427, 0.7489486695884694,
                              0.47087151345579137, 0.14285714285714296};
  coder::sparse bank;
  coder::array<creal_T, 1U> b_x;
  coder::array<double, 2U> b_bank;
  coder::array<double, 2U> b_xx;
  coder::array<double, 2U> dtm;
  coder::array<double, 2U> inds;
  coder::array<double, 2U> m;
  coder::array<double, 1U> indf;
  coder::array<double, 1U> xx;
  double dctcoef[128];
  double y_data[16];
  double maxval;
  double nf;
  int b_indf[2];
  int result[2];
  int c_i;
  int cend;
  int i;
  int i1;
  int i2;
  int i3;
  int idx;
  int inner;
  int k;
  int loop_ub;
  int nx;
  int nx_m_nb;
  signed char input_sizes_idx_1;
  signed char sizes_idx_1;
  boolean_T empty_non_axis_sizes;
  //  ��֡��ΪframeSize��Mel�˲����ĸ���Ϊp������Ƶ��Ϊfs
  //  ��ȡMel�˲����������ú���������
  // 'mfcc_m:12' bank = melbankm(p, frameSize, fs, 0, 0.5, 'm');
  melbankm(frameSize, fs, &bank);
  //  ��һ��Mel�˲�����ϵ��
  // 'mfcc_m:14' bank = full(bank);
  b_bank.set_size(16, bank.n);
  nx_m_nb = bank.n << 4;
  if (static_cast<int>(nx_m_nb < 1200)) {
    for (i = 0; i < nx_m_nb; i++) {
      b_bank[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx_m_nb; i++) {
      b_bank[i] = 0.0;
    }
  }
  i1 = bank.n;
  for (nx_m_nb = 0; nx_m_nb < i1; nx_m_nb++) {
    cend = bank.colidx[nx_m_nb + 1] - 1;
    nx = bank.colidx[nx_m_nb];
    for (idx = nx; idx <= cend; idx++) {
      b_bank[(bank.rowidx[idx - 1] + 16 * nx_m_nb) - 1] = bank.d[idx - 1];
    }
  }
  coder::array<double, 1U> c_bank;
  // 'mfcc_m:15' bank = bank / max(bank(:));
  cend = b_bank.size(1) << 4;
  c_bank = b_bank.reshape(cend);
  maxval = coder::internal::maximum(c_bank);
  nx_m_nb = 16 * b_bank.size(1);
  b_bank.set_size(16, b_bank.size(1));
  if (static_cast<int>(nx_m_nb < 1200)) {
    for (i = 0; i < nx_m_nb; i++) {
      b_bank[i] = b_bank[i] / maxval;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx_m_nb; i++) {
      b_bank[i] = b_bank[i] / maxval;
    }
  }
  // 'mfcc_m:16' p2 = p / 2;
  //  DCTϵ��,p2*p
  // 'mfcc_m:18' dctcoef = zeros(p2, p);
  // 'mfcc_m:20' for k = 1:p2
  for (k = 0; k < 8; k++) {
    // 'mfcc_m:21' n = 0:p - 1;
    // 'mfcc_m:22' dctcoef(k, :) = cos((2 * n + 1) * k * pi / (2 * p));
    for (nx_m_nb = 0; nx_m_nb < 16; nx_m_nb++) {
      dctcoef[k + (nx_m_nb << 3)] =
          std::cos(static_cast<double>((2 * nx_m_nb + 1) * (k + 1)) *
                   3.1415926535897931 / 32.0);
    }
  }
  //  ��һ��������������
  // 'mfcc_m:26' w = 1 + 6 * sin(pi * [1:p2] ./ p2);
  // 'mfcc_m:27' w = w / max(w);
  //  Ԥ�����˲���
  // 'mfcc_m:30' xx = double(x);
  // 'mfcc_m:31' xx = filter([1 -0.9375], 1, xx);
  nx = x.size(0);
  xx.set_size(x.size(0));
  nx_m_nb = x.size(0);
  if (static_cast<int>(x.size(0) < 1200)) {
    for (i = 0; i < nx_m_nb; i++) {
      xx[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx_m_nb; i++) {
      xx[i] = 0.0;
    }
  }
  if (x.size(0) >= 4) {
    for (k = 0; k < 2; k++) {
      nx_m_nb = k + 1;
      for (idx = nx_m_nb; idx <= nx; idx++) {
        xx[idx - 1] = xx[idx - 1] + (-1.9375 * static_cast<double>(k) + 1.0) *
                                        x[(idx - k) - 1];
      }
    }
  } else {
    if (x.size(0) > 2) {
      nx_m_nb = 0;
    } else {
      nx_m_nb = -1;
    }
    for (k = 0; k <= nx_m_nb; k++) {
      xx[0] = xx[0] + x[0];
      xx[1] = xx[1] + x[0] * -0.9375;
    }
    cend = x.size(0) - nx_m_nb;
    i1 = nx_m_nb + 2;
    for (k = i1; k <= nx; k++) {
      for (idx = 0; idx <= cend - 2; idx++) {
        nx_m_nb = (k + idx) - 1;
        xx[nx_m_nb] =
            xx[nx_m_nb] + x[k - 1] * (-1.9375 * static_cast<double>(idx) + 1.0);
      }
      cend--;
    }
  }
  //  �����źŷ�֡
  // 'mfcc_m:34' xx = v_enframe(xx, frameSize, inc);
  maxval = inc;
  // V_ENFRAME split signal up into (overlapping) frames: one per row.
  // [F,T]=(X,WIN,HOP)
  //
  //  Usage:  (1) f=v_enframe(x,n)                          % split into frames
  //  of length n
  //          (2) f=v_enframe(x,hamming(n,'periodic'),n/4)  % use a 75%
  //          overlapped Hamming window of length n (3) calculate spectrogram in
  //          units of power per Hz
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
  //                window length W=sqrt(hamming(NW,'periodic'));     % omit
  //                sqrt if OV=4 [F,T,WS]=v_enframe(S,W,1/OV,'fa');    % do
  //                STFT: one row per time frame, +ve frequencies only
  //                ... process frames ...
  //                X=v_overlapadd(v_irfft(F,NW,2),WS,HOP); % reconstitute the
  //                time waveform with scaled window (omit "X=" to plot
  //                waveform)
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
  //                   sum(mean(v_enframe(x,win,hop,'sp'),1))=mean(x.^2) 'S'
  //                   scale window so that total energy is preserved:
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
  // 'v_enframe:87' if nargin < 4 || isempty(m)
  // 'v_enframe:88' m = '';
  // 'v_enframe:91' nwin = length(win);
  // 'v_enframe:93' if nwin == 1
  // 'v_enframe:94' lw = win(1);
  // 'v_enframe:95' w = ones(1, lw);
  // 'v_enframe:101' if (nargin < 3) || isempty(hop)
  if (inc < 1.0) {
    // 'v_enframe:103' elseif hop < 1
    // 'v_enframe:104' hop = lw * hop;
    maxval = frameSize * inc;
  }
  // 'v_enframe:107' if any(m == 'a')
  // 'v_enframe:115' if any(m == 'd')
  // 'v_enframe:125' nli = nx - lw + hop;
  // 'v_enframe:126' nf = max(fix(nli / hop), 0);
  nf = std::fmax(
      std::trunc(((static_cast<double>(xx.size(0)) - frameSize) + maxval) /
                 maxval),
      0.0);
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
    nx_m_nb = static_cast<int>(nf - 1.0);
    if (static_cast<int>(static_cast<int>(nf - 1.0) + 1 < 1200)) {
      for (i = 0; i <= nx_m_nb; i++) {
        inds[i] = i;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i <= nx_m_nb; i++) {
        inds[i] = i;
      }
    }
  }
  indf.set_size(inds.size(1));
  nx_m_nb = inds.size(1);
  if (static_cast<int>(inds.size(1) < 1200)) {
    for (i = 0; i < nx_m_nb; i++) {
      indf[i] = maxval * inds[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx_m_nb; i++) {
      indf[i] = maxval * inds[i];
    }
  }
  // 'v_enframe:131' inds = (1:lw);
  if (frameSize < 1.0) {
    inds.set_size(1, 0);
  } else if (std::isinf(frameSize) && (1.0 == frameSize)) {
    inds.set_size(1, 1);
    inds[0] = rtNaN;
  } else {
    nx_m_nb = static_cast<int>(std::floor(frameSize - 1.0));
    inds.set_size(1, nx_m_nb + 1);
    if (static_cast<int>(nx_m_nb + 1 < 1200)) {
      for (i = 0; i <= nx_m_nb; i++) {
        inds[i] = static_cast<double>(i) + 1.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i <= nx_m_nb; i++) {
        inds[i] = static_cast<double>(i) + 1.0;
      }
    }
  }
  // 'v_enframe:133' if fx
  // 'v_enframe:144' else
  // 'v_enframe:145' f(:) = x(indf(:, ones(1, lw)) + inds(ones(nf, 1), :));
  nx_m_nb = indf.size(0);
  b_xx.set_size(indf.size(0), static_cast<int>(frameSize));
  cend = static_cast<int>(frameSize);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < cend; i++) {
    for (i2 = 0; i2 < nx_m_nb; i2++) {
      b_xx[i2 + b_xx.size(0) * i] =
          xx[static_cast<int>(indf[i2] + inds[i]) - 1];
    }
  }
  // 'v_enframe:148' if (nwin > 1)
  // 'v_enframe:152' if any(lower(m) == 'p')
  // 'v_enframe:171' if nargout > 1
  // 'mfcc_m:35' n2 = fix(frameSize / 2) + 1;
  //  ����ÿ֡��MFCC����
  // 'mfcc_m:37' fn = size(xx, 1);
  // 'mfcc_m:38' m = zeros(fn, p2);
  m.set_size(indf.size(0), 8);
  nx_m_nb = indf.size(0) << 3;
  if (static_cast<int>(nx_m_nb < 1200)) {
    for (i = 0; i < nx_m_nb; i++) {
      m[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx_m_nb; i++) {
      m[i] = 0.0;
    }
  }
  // 'mfcc_m:40' for i = 1:size(xx, 1)
  i1 = indf.size(0);
  if (0 <= indf.size(0) - 1) {
    i3 = static_cast<int>(frameSize);
    loop_ub = static_cast<int>(frameSize);
    inner = b_bank.size(1);
  }
  for (int b_i{0}; b_i < i1; b_i++) {
    // 'mfcc_m:41' y = xx(i, :);
    // 'mfcc_m:42' s = y' .* hamming(frameSize);
    coder::hamming(frameSize, xx);
    // 'mfcc_m:43' t = abs(fft(s));
    indf.set_size(i3);
    for (nx = 0; nx < loop_ub; nx++) {
      indf[nx] = b_xx[b_i + b_xx.size(0) * nx] * xx[nx];
    }
    coder::fft(indf, b_x);
    nx = b_x.size(0);
    xx.set_size(b_x.size(0));
    for (k = 0; k < nx; k++) {
      xx[k] = rt_hypotd_snf(b_x[k].re, b_x[k].im);
    }
    // 'mfcc_m:44' t = t.^2;
    indf.set_size(xx.size(0));
    nx_m_nb = xx.size(0);
    for (nx = 0; nx < nx_m_nb; nx++) {
      indf[nx] = xx[nx];
    }
    cend = xx.size(0);
    for (k = 0; k < cend; k++) {
      xx[k] = indf[k] * indf[k];
    }
    // 'mfcc_m:45' c1 = dctcoef * log(bank * t(1:n2));
    std::memset(&y_data[0], 0, 16U * sizeof(double));
    for (k = 0; k < inner; k++) {
      nx_m_nb = k << 4;
      for (cend = 0; cend < 16; cend++) {
        y_data[cend] += b_bank[nx_m_nb + cend] * xx[k];
      }
    }
    for (k = 0; k < 16; k++) {
      y_data[k] = std::log(y_data[k]);
    }
    // 'mfcc_m:46' c2 = c1 .* w';
    // 'mfcc_m:47' m(i, :) = c2';
    for (nx = 0; nx < 8; nx++) {
      maxval = 0.0;
      for (idx = 0; idx < 16; idx++) {
        maxval += dctcoef[nx + (idx << 3)] * y_data[idx];
      }
      m[b_i + m.size(0) * nx] = maxval * b_dv[nx];
    }
  }
  // ���ϵ��
  // 'mfcc_m:51' dtm = zeros(size(m));
  dtm.set_size(m.size(0), 8);
  nx_m_nb = m.size(0) << 3;
  if (static_cast<int>(nx_m_nb < 1200)) {
    for (i = 0; i < nx_m_nb; i++) {
      dtm[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx_m_nb; i++) {
      dtm[i] = 0.0;
    }
  }
  // 'mfcc_m:53' for i = 3:size(m, 1) - 2
  i1 = m.size(0);
  if (static_cast<int>(((m.size(0) - 4) << 3) < 1200)) {
    for (c_i = 0; c_i <= i1 - 5; c_i++) {
      // 'mfcc_m:54' dtm(i, :) = -2 * m(i - 2, :) - m(i - 1, :) + m(i + 1, :) +
      // 2 * m(i + 2, :);
      for (i = 0; i < 8; i++) {
        dtm[(c_i + dtm.size(0) * i) + 2] =
            ((-2.0 * m[c_i + m.size(0) * i] - m[(c_i + m.size(0) * i) + 1]) +
             m[(c_i + m.size(0) * i) + 3]) +
            2.0 * m[(c_i + m.size(0) * i) + 4];
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i, c_i)

    for (c_i = 0; c_i <= i1 - 5; c_i++) {
      // 'mfcc_m:54' dtm(i, :) = -2 * m(i - 2, :) - m(i - 1, :) + m(i + 1, :) +
      // 2 * m(i + 2, :);
      for (i = 0; i < 8; i++) {
        dtm[(c_i + dtm.size(0) * i) + 2] =
            ((-2.0 * m[c_i + m.size(0) * i] - m[(c_i + m.size(0) * i) + 1]) +
             m[(c_i + m.size(0) * i) + 3]) +
            2.0 * m[(c_i + m.size(0) * i) + 4];
      }
    }
  }
  // 'mfcc_m:57' dtm = dtm / 3;
  nx_m_nb = dtm.size(0) * 8;
  dtm.set_size(dtm.size(0), 8);
  if (static_cast<int>(nx_m_nb < 1200)) {
    for (i = 0; i < nx_m_nb; i++) {
      dtm[i] = dtm[i] / 3.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx_m_nb; i++) {
      dtm[i] = dtm[i] / 3.0;
    }
  }
  // �ϲ�MFCC������һ�ײ��MFCC����
  // 'mfcc_m:59' ccc = [m dtm];
  if (m.size(0) != 0) {
    cend = m.size(0);
  } else if (dtm.size(0) != 0) {
    cend = dtm.size(0);
  } else {
    cend = 0;
  }
  empty_non_axis_sizes = (cend == 0);
  if (empty_non_axis_sizes || (m.size(0) != 0)) {
    input_sizes_idx_1 = 8;
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || (dtm.size(0) != 0)) {
    sizes_idx_1 = 8;
  } else {
    sizes_idx_1 = 0;
  }
  b_indf[0] = cend;
  b_indf[1] = input_sizes_idx_1;
  result[0] = cend;
  result[1] = sizes_idx_1;
  ccc.set_size(cend, input_sizes_idx_1 + sizes_idx_1);
  nx_m_nb = input_sizes_idx_1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, c_i, i)

  for (i = 0; i < nx_m_nb; i++) {
    c_i = b_indf[0];
    for (i2 = 0; i2 < c_i; i2++) {
      ccc[i2 + ccc.size(0) * i] = m[i2 + m.size(0) * i];
    }
  }
  nx_m_nb = result[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, c_i, i)

  for (i = 0; i < nx_m_nb; i++) {
    c_i = result[0];
    for (i2 = 0; i2 < c_i; i2++) {
      ccc[i2 + ccc.size(0) * (i + b_indf[1])] = dtm[i2 + dtm.size(0) * i];
    }
  }
  // ȥ����β��֡����Ϊ����֡��һ�ײ�ֲ���Ϊ0
  // 'mfcc_m:61' ccc = ccc(3:size(m, 1) - 2, :);
  if (3 > m.size(0) - 2) {
    i1 = -1;
    nx = -1;
  } else {
    i1 = 1;
    nx = m.size(0) - 3;
  }
  cend = ccc.size(1) - 1;
  for (i3 = 0; i3 <= cend; i3++) {
    nx_m_nb = nx - i1;
    for (idx = 0; idx < nx_m_nb; idx++) {
      ccc[idx + nx_m_nb * i3] = ccc[((i1 + idx) + ccc.size(0) * i3) + 1];
    }
  }
  ccc.set_size(nx - i1, cend + 1);
}

//
// File trailer for mfcc_m.cpp
//
// [EOF]
//
