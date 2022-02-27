//
// File: melbankm.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "melbankm.h"
#include "abs.h"
#include "ceil.h"
#include "colon.h"
#include "cos.h"
#include "find.h"
#include "floor.h"
#include "frq2mel.h"
#include "isinf.h"
#include "isnan.h"
#include "mel2frq.h"
#include "minOrMax.h"
#include "nullAssignment.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "coder_array.h"
#include <math.h>

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
void melbankm(double n, double fs, coder::sparse *x) {
    coder::array<double, 2U> b_c;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> c;
    coder::array<double, 2U> fp;
    coder::array<double, 2U> pf;
    coder::array<double, 2U> pm;
    coder::array<double, 2U> v;
    coder::array<double, 2U> y;
    coder::array<int, 2U> r1;
    coder::array<boolean_T, 2U> b_fp;
    coder::array<boolean_T, 2U> r;
    double b_dv1[4];
    double b_mflh[4];
    double b_dv[2];
    double mflh[2];
    double b;
    double b1;
    double b_n;
    double d;
    double fn2;
    double k2_data;
    double melinc;
    int k3_size[2];
    int b_i;
    int b_loop_ub;
    int i;
    int i1;
    int i2;
    int i3;
    int k2_size_idx_1;
    int k3_data;
    int loop_ub;
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
    b_dv[0] = 0.0 * fs;
    b_dv[1] = 0.5 * fs;
    frq2mel(b_dv, mflh);
    //  convert frequency limits into mel
    // 'melbankm:156' melrng = mflh * (-1:2:1)';
    //  mel range
    // 'melbankm:157' fn2 = floor(n / 2);
    fn2 = n / 2.0;
    coder::b_floor(&fn2);
    //  bin index of highest positive frequency (Nyquist if n is even)
    // 'melbankm:159' if isempty(p)
    // 'melbankm:163' if any(w == 'c')
    // 'melbankm:171' else
    // 'melbankm:173' if p < 1
    // 'melbankm:177' melinc = melrng / (p + 1);
    melinc = (-mflh[0] + mflh[1]) / 17.0;
    //
    //  Calculate the FFT bins corresponding to [filter#1-low filter#1-mid
    //  filter#p-mid filter#p-high]
    //
    // 'melbankm:183' switch wr
    // 'melbankm:192' otherwise
    // 'melbankm:193' blim = mel2frq(mflh(1) + [0 1 p p + 1] * melinc) * n / fs;
    b_mflh[0] = mflh[0] + 0.0 * melinc;
    b_mflh[1] = mflh[0] + melinc;
    b_mflh[2] = mflh[0] + 16.0 * melinc;
    b_mflh[3] = mflh[0] + 17.0 * melinc;
    mel2frq(b_mflh, b_dv1);
    // 'melbankm:196' mc = mflh(1) + (1:p) * melinc;
    //  mel centre frequencies
    // 'melbankm:197' b1 = floor(blim(1)) + 1;
    d = b_dv1[0] * n / fs;
    coder::b_floor(&d);
    b1 = d + 1.0;
    //  lowest FFT bin_0 required might be negative)
    // 'melbankm:198' b4 = min(fn2, ceil(blim(4)) - 1);
    b_n = b_dv1[3] * n / fs;
    coder::b_ceil(&b_n);
    b = coder::internal::minimum2(fn2, b_n - 1.0);
    //  highest FFT bin_0 required
    //
    //  now map all the useful FFT bins_0 to filter1 centres
    //
    // 'melbankm:202' switch wr
    // 'melbankm:211' otherwise
    // 'melbankm:212' pf = (frq2mel((b1:b4) * fs / n) - mflh(1)) / melinc;
    if (coder::b_isnan(d + 1.0) || coder::b_isnan(b)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (b < d + 1.0) {
        y.set_size(1, 0);
    } else if ((coder::b_isinf(d + 1.0) || coder::b_isinf(b)) &&
               (d + 1.0 == b)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else {
        b_n = d + 1.0;
        coder::b_floor(&b_n);
        if (b_n == d + 1.0) {
            loop_ub = static_cast<int>(floor(b - (d + 1.0)));
            y.set_size(1, loop_ub + 1);
            for (i = 0; i <= loop_ub; i++) {
                y[i] = (d + 1.0) + static_cast<double>(i);
            }
        } else {
            coder::eml_float_colon(d + 1.0, b, y);
        }
    }
    b_y.set_size(1, y.size(1));
    loop_ub = y.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_y[i] = y[i] * fs / n;
    }
    frq2mel(b_y, y);
    pf.set_size(1, y.size(1));
    loop_ub = y.size(1);
    for (i = 0; i < loop_ub; i++) {
        pf[i] = (y[i] - mflh[0]) / melinc;
    }
    //
    //   remove any incorrect entries in pf due to rounding errors
    //
    // 'melbankm:218' if pf(1) < 0
    if (pf[0] < 0.0) {
        // 'melbankm:219' pf(1) = [];
        coder::internal::nullAssignment(pf);
        // 'melbankm:220' b1 = b1 + 1;
        b1 = (d + 1.0) + 1.0;
    }
    // 'melbankm:223' if pf(end) >= p + 1
    if (pf[pf.size(1) - 1] >= 17.0) {
        // 'melbankm:224' pf(end) = [];
        coder::internal::nullAssignment(pf, pf.size(1));
        // 'melbankm:225' b4 = b4 - 1;
    }
    // 'melbankm:228' fp = floor(pf);
    fp.set_size(1, pf.size(1));
    loop_ub = pf.size(1);
    for (i = 0; i < loop_ub; i++) {
        fp[i] = pf[i];
    }
    coder::b_floor(fp);
    //  FFT bin_0 i contributes to filters_1 fp(1+i-b1)+[0 1]
    // 'melbankm:229' pm = pf - fp;
    pm.set_size(1, pf.size(1));
    loop_ub = pf.size(1);
    for (i = 0; i < loop_ub; i++) {
        pm[i] = pf[i] - fp[i];
    }
    //  multiplier for upper filter
    // 'melbankm:230' k2 = find(fp > 0, 1);
    b_fp.set_size(1, fp.size(1));
    loop_ub = fp.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_fp[i] = (fp[i] > 0.0);
    }
    coder::eml_find(b_fp, (int *) &k3_data, k3_size);
    k2_size_idx_1 = k3_size[1];
    loop_ub = k3_size[1];
    for (i = 0; i < loop_ub; i++) {
        k2_data = k3_data;
    }
    //  FFT bin_1 k2+b1 is the first to contribute to both upper and lower
    //  filters
    // 'melbankm:231' k3 = find(fp < p, 1, 'last');
    b_fp.set_size(1, fp.size(1));
    loop_ub = fp.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_fp[i] = (fp[i] < 16.0);
    }
    coder::b_eml_find(b_fp, (int *) &k3_data, k3_size);
    //  FFT bin_1 k3+b1 is the last to contribute to both upper and lower
    //  filters
    // 'melbankm:232' k4 = numel(fp);
    //  FFT bin_1 k4+b1 is the last to contribute to any filters
    // 'melbankm:234' if isempty(k2)
    if (k2_size_idx_1 == 0) {
        // 'melbankm:235' k2 = k4 + 1;
        k2_data = static_cast<double>(fp.size(1)) + 1.0;
    }
    // 'melbankm:238' if isempty(k3)
    if (k3_size[1] == 0) {
        // 'melbankm:239' k3 = 0;
        k3_data = 0;
    }
    // 'melbankm:242' if any(w == 'y')
    // 'melbankm:248' else
    // 'melbankm:249' r = [1 + fp(1:k3(1)) fp(k2(1):k4)];
    if (1 > k3_data) {
        loop_ub = 0;
    } else {
        loop_ub = k3_data;
    }
    if (k2_data > fp.size(1)) {
        i = 0;
        i1 = 0;
    } else {
        i = static_cast<int>(k2_data) - 1;
        i1 = fp.size(1);
    }
    //  filter number_1
    // 'melbankm:250' c = [1:k3 k2:k4];
    if (coder::b_isnan(static_cast<double>(k3_data))) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (k3_data < 1) {
        y.set_size(1, 0);
    } else if (coder::b_isinf(static_cast<double>(k3_data)) && (1 == k3_data)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else {
        y.set_size(1, k3_data);
        b_loop_ub = k3_data - 1;
        for (i2 = 0; i2 <= b_loop_ub; i2++) {
            y[i2] = static_cast<double>(i2) + 1.0;
        }
    }
    if (coder::b_isnan(k2_data) ||
        coder::b_isnan(static_cast<double>(fp.size(1)))) {
        b_y.set_size(1, 1);
        b_y[0] = rtNaN;
    } else if (fp.size(1) < k2_data) {
        b_y.set_size(1, 0);
    } else if ((coder::b_isinf(k2_data) ||
                coder::b_isinf(static_cast<double>(fp.size(1)))) &&
               (static_cast<int>(k2_data) == fp.size(1))) {
        b_y.set_size(1, 1);
        b_y[0] = rtNaN;
    } else {
        d = k2_data;
        coder::b_floor(&d);
        if (d == k2_data) {
            b_y.set_size(1, (fp.size(1) - static_cast<int>(k2_data)) + 1);
            b_loop_ub = fp.size(1) - static_cast<int>(k2_data);
            for (i2 = 0; i2 <= b_loop_ub; i2++) {
                b_y[i2] = k2_data + static_cast<double>(i2);
            }
        } else {
            coder::eml_float_colon(k2_data, static_cast<double>(fp.size(1)),
                                   b_y);
        }
    }
    c.set_size(1, y.size(1) + b_y.size(1));
    b_loop_ub = y.size(1);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
        c[i2] = y[i2];
    }
    b_loop_ub = b_y.size(1);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
        c[i2 + y.size(1)] = b_y[i2];
    }
    //  FFT bin_1 - b1
    // 'melbankm:251' v = [pm(1:k3(1)) 1 - pm(k2(1):k4)];
    if (1 > k3_data) {
        b_loop_ub = 0;
    } else {
        b_loop_ub = k3_data;
    }
    if (k2_data > fp.size(1)) {
        i2 = 0;
        b_i = 0;
    } else {
        i2 = static_cast<int>(k2_data) - 1;
        b_i = fp.size(1);
    }
    // 'melbankm:252' mn = b1 + 1;
    //  lowest fft bin_1
    // 'melbankm:253' mx = b4 + 1;
    //  highest fft bin_1
    // 'melbankm:256' if b1 < 0
    if (b1 < 0.0) {
        // 'melbankm:257' c = abs(c + b1 - 1) - b1 + 1;
        b_c.set_size(1, c.size(1));
        k2_size_idx_1 = c.size(1);
        for (i3 = 0; i3 < k2_size_idx_1; i3++) {
            b_c[i3] = (c[i3] + b1) - 1.0;
        }
        coder::b_abs(b_c, y);
        c.set_size(1, y.size(1));
        k2_size_idx_1 = y.size(1);
        for (i3 = 0; i3 < k2_size_idx_1; i3++) {
            c[i3] = (y[i3] - b1) + 1.0;
        }
        //  convert negative frequencies into positive
    }
    //  end
    // 'melbankm:261' if any(w == 'n')
    // 'melbankm:263' elseif any(w == 'm')
    // 'melbankm:264' v = 0.5 - 0.46/1.08 * cos(v * pi);
    y.set_size(1, (b_loop_ub + b_i) - i2);
    for (i3 = 0; i3 < b_loop_ub; i3++) {
        y[i3] = pm[i3] * 3.1415926535897931;
    }
    k2_size_idx_1 = b_i - i2;
    for (b_i = 0; b_i < k2_size_idx_1; b_i++) {
        y[b_i + b_loop_ub] = (1.0 - pm[i2 + b_i]) * 3.1415926535897931;
    }
    coder::b_cos(y);
    v.set_size(1, y.size(1));
    b_loop_ub = y.size(1);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
        v[i2] = 0.5 - 0.42592592592592593 * y[i2];
    }
    //  convert triangles to Hamming
    // 'melbankm:267' if sfact == 2
    //  double all except the DC and Nyquist (if any) terms
    // 'melbankm:268' msk = (c + mn > 2) & (c + mn < n - fn2 + 2);
    y.set_size(1, c.size(1));
    b_loop_ub = c.size(1);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
        y[i2] = c[i2] + (b1 + 1.0);
    }
    b_fp.set_size(1, y.size(1));
    b_loop_ub = y.size(1);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
        b_fp[i2] = (y[i2] > 2.0);
    }
    r.set_size(1, y.size(1));
    b_n = (n - fn2) + 2.0;
    b_loop_ub = y.size(1);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
        r[i2] = (y[i2] < b_n);
    }
    //  there is no Nyquist term if n is odd
    // 'melbankm:269' v(msk) = 2 * v(msk);
    b_loop_ub = b_fp.size(1) - 1;
    k2_size_idx_1 = 0;
    for (b_i = 0; b_i <= b_loop_ub; b_i++) {
        if (b_fp[b_i] && r[b_i]) {
            k2_size_idx_1++;
        }
    }
    r1.set_size(1, k2_size_idx_1);
    k2_size_idx_1 = 0;
    for (b_i = 0; b_i <= b_loop_ub; b_i++) {
        if (b_fp[b_i] && r[b_i]) {
            r1[k2_size_idx_1] = b_i + 1;
            k2_size_idx_1++;
        }
    }
    y.set_size(1, r1.size(1));
    b_loop_ub = r1.size(1);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
        y[i2] = 2.0 * v[r1[i2] - 1];
    }
    b_loop_ub = b_fp.size(1);
    k2_size_idx_1 = 0;
    for (b_i = 0; b_i < b_loop_ub; b_i++) {
        if (b_fp[b_i] && r[b_i]) {
            v[b_i] = y[k2_size_idx_1];
            k2_size_idx_1++;
        }
    }
    //
    //  sort out the output argument options
    //
    // 'melbankm:275' if nargout > 2
    // 'melbankm:283' else
    // 'melbankm:284' x = sparse(r, c + mn - 1, v, p, 1 + fn2);
    b_y.set_size(1, (loop_ub + i1) - i);
    for (i2 = 0; i2 < loop_ub; i2++) {
        b_y[i2] = fp[i2] + 1.0;
    }
    b_loop_ub = i1 - i;
    for (i1 = 0; i1 < b_loop_ub; i1++) {
        b_y[i1 + loop_ub] = fp[i + i1];
    }
    b_c.set_size(1, c.size(1));
    loop_ub = c.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_c[i] = (c[i] + (b1 + 1.0)) - 1.0;
    }
    coder::b_sparse(b_y, b_c, v, fn2 + 1.0, x);
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
