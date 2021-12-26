//
// File: octbank.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "octbank.h"
#include "SnoringRecognition_data.h"
#include "combineVectorElements.h"
#include "eig.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_defines.h"
#include <cmath>
#include <cstring>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int b_u0;
    int b_u1;
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }
    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }
    y = std::atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }
  return y;
}

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
void octbank(const coder::array<double, 2U> &x, double p[8])
{
  static const double b_dv[8]{62.5,   125.0,  250.0,  500.0,
                              1000.0, 2000.0, 4000.0, 8000.0};
  static const signed char b_iv1[18]{-1, 0, 0, 0, -1, 0, 0, 0, -1,
                                     0,  0, 0, 0, 0,  0, 0, 0, 0};
  static const signed char b_iv2[9]{1, 0, 0, 0, 1, 0, 0, 0, 1};
  static const signed char b_b[7]{1, 0, -3, 0, 3, 0, -1};
  static const signed char b_iv[6]{1, 1, 1, -1, -1, -1};
  coder::array<double, 2U> b_y;
  coder::array<double, 2U> y;
  coder::array<double, 1U> b;
  coder::array<double, 1U> b_y1;
  creal_T c[7];
  creal_T b_p[6];
  creal_T c_x[6];
  creal_T b_c[3];
  creal_T b_x;
  creal_T b_zWn;
  double b_t1_tmp[36];
  double t1[36];
  double t1_tmp[36];
  double a[9];
  double x_data[8];
  double A[7];
  double B[7];
  double t[4];
  double u[2];
  double Wn1;
  double as;
  double d1;
  double im;
  double smax;
  double zWn;
  int b_i;
  int b_j;
  int b_tmp;
  int c_i;
  int d_i;
  int i;
  int ijA;
  int j;
  int jBcol;
  int jp1j;
  int k;
  int loop_ub;
  int mmj_tmp;
  int naxpy;
  int trueCount;
  signed char tmp_data[8];
  signed char ipiv[6];
  signed char b1[2];
  signed char i1;
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
  loop_ub = x.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    b, b_y1, y, k, j, as, naxpy, b_i, c_i, jBcol, ijA, jp1j, i1, smax,         \
    mmj_tmp, b_j, zWn, d1, B, A, c, b_x, c_x, b_zWn, b_p, ipiv, t1, t1_tmp,    \
    b_t1_tmp, Wn1, t, b1, b_c, a, u, i, im, b_tmp)

  for (i = 0; i < 8; i++) {
    // 'octbank:36' [B, A] = octdsgn(ff(i), Fs, N);
    //  OCTDSGN  Design of an octave filter.
    //     [B,A] = OCTDSGN(Fc,Fs,N) designs a digital octave filter with
    //     center frequency Fc for sampling frequency Fs.
    //     The filter are designed according to the Order-N specification
    //     of the ANSI S1.1-1986 standard. Default value for N is 3.
    //     Warning: for meaningful design results, center values used
    //     should preferably be in range Fs/200 < Fc < Fs/5.
    //     Usage of the filter: Y = FILTER(B,A,X).
    //
    //     Requires the Signal Processing Toolbox.
    //
    //     See also OCTSPEC, OCT3DSGN, OCT3SPEC.
    //  Author: Christophe Couvreur, Faculte Polytechnique de Mons (Belgium)
    //          couvreur@thor.fpms.ac.be
    //  Last modification: Aug. 22, 1997, 9:00pm.
    //  References:
    //     [1] ANSI S1.1-1986 (ASA 65-1986): Specifications for
    //         Octave-Band and Fractional-Octave-Band Analog and
    //         Digital Filters, 1993.
    // 'octdsgn:24' if (nargin > 3) | (nargin < 2)
    // 'octdsgn:28' if (nargin == 2)
    // 'octdsgn:32' if (Fc > 0.70 * (Fs / 2))
    //  Design Butterworth 2Nth-order octave filter
    //  Note: BUTTER is based on a bilinear transformation, as suggested in [1].
    // W1 = Fc/(Fs/2)*sqrt(1/2);
    // W2 = Fc/(Fs/2)*sqrt(2);
    // 'octdsgn:40' pi = 3.14159265358979;
    // 'octdsgn:41' beta = pi / 2 / N / sin(pi / 2 / N);
    // 'octdsgn:42' alpha = (1 + sqrt(1 + 8 * beta^2)) / 4 / beta;
    // 'octdsgn:43' W1 = Fc / (Fs / 2) * sqrt(1/2) / alpha;
    // 'octdsgn:44' W2 = Fc / (Fs / 2) * sqrt(2) * alpha;
    // 'octdsgn:45' [B, A] = butter(N, [W1, W2]);
    as = b_dv[7 - i] / 22050.0;
    u[0] = 3.1415926535897931 *
           (as * 0.70710678118654757 / 0.98505216233236492) / 2.0;
    u[1] = 3.1415926535897931 *
           (as * 1.4142135623730951 * 0.98505216233236492) / 2.0;
    u[0] = 4.0 * std::tan(u[0]);
    d1 = 4.0 * std::tan(u[1]);
    std::memset(&a[0], 0, 9U * sizeof(double));
    a[0] = -1.0;
    b_c[0].re = 1.0;
    b_c[0].im = 0.0;
    for (j = 0; j < 2; j++) {
      as = 1.7320508075688774 * static_cast<double>(j) + -0.86602540378443871;
      im = 0.49999999999999978 * b_c[j].im + -as * b_c[j].re;
      b_c[j + 1].re = 0.49999999999999978 * b_c[j].re - -as * b_c[j].im;
      b_c[j + 1].im = im;
      for (k = j + 1; k >= 2; k--) {
        b_c[1].re -= -0.49999999999999978 * b_c[0].re - as * b_c[0].im;
        b_c[1].im -= -0.49999999999999978 * b_c[0].im + as * b_c[0].re;
      }
    }
    zWn = (1.0 - -b_c[1].re * 0.0) / 1.0000000000000002;
    t[1] = zWn;
    t[0] = -b_c[1].re - zWn * 0.0;
    zWn = (0.0 - -b_c[2].re * 0.0) / 1.0000000000000002;
    t[3] = zWn;
    t[2] = -b_c[2].re - zWn * 0.0;
    b1[1] = 0;
    b1[0] = 1;
    for (b_i = 0; b_i < 2; b_i++) {
      a[b_i + 1] = b1[b_i];
      zWn = t[b_i + 2];
      as = t[b_i];
      a[b_i + 4] = as + zWn * 0.0;
      zWn = as * 0.0 + zWn * 1.0000000000000002;
      a[b_i + 7] = zWn;
    }
    Wn1 = std::sqrt(u[0] * d1);
    as = Wn1 / (d1 - u[0]);
    std::memset(&b_t1_tmp[0], 0, 36U * sizeof(double));
    for (k = 0; k < 6; k++) {
      b_t1_tmp[k + 6 * k] = 1.0;
    }
    for (b_i = 0; b_i < 3; b_i++) {
      t1_tmp[6 * b_i] = Wn1 * (a[3 * b_i] / as) * 0.5 / 2.0;
      jBcol = 6 * (b_i + 3);
      t1_tmp[jBcol] = Wn1 * static_cast<double>(b_iv2[3 * b_i]) * 0.5 / 2.0;
      naxpy = 3 * b_i + 1;
      t1_tmp[6 * b_i + 1] = Wn1 * (a[naxpy] / as) * 0.5 / 2.0;
      t1_tmp[jBcol + 1] = Wn1 * static_cast<double>(b_iv2[naxpy]) * 0.5 / 2.0;
      naxpy = 3 * b_i + 2;
      t1_tmp[6 * b_i + 2] = Wn1 * (a[naxpy] / as) * 0.5 / 2.0;
      t1_tmp[jBcol + 2] = Wn1 * static_cast<double>(b_iv2[naxpy]) * 0.5 / 2.0;
    }
    for (b_i = 0; b_i < 6; b_i++) {
      t1_tmp[6 * b_i + 3] =
          Wn1 * static_cast<double>(b_iv1[3 * b_i]) * 0.5 / 2.0;
      t1_tmp[6 * b_i + 4] =
          Wn1 * static_cast<double>(b_iv1[3 * b_i + 1]) * 0.5 / 2.0;
      t1_tmp[6 * b_i + 5] =
          Wn1 * static_cast<double>(b_iv1[3 * b_i + 2]) * 0.5 / 2.0;
    }
    for (b_i = 0; b_i < 36; b_i++) {
      zWn = b_t1_tmp[b_i];
      d1 = t1_tmp[b_i];
      t1[b_i] = zWn + d1;
      zWn -= d1;
      b_t1_tmp[b_i] = zWn;
    }
    for (b_i = 0; b_i < 6; b_i++) {
      ipiv[b_i] = static_cast<signed char>(b_i + 1);
    }
    for (b_j = 0; b_j < 5; b_j++) {
      mmj_tmp = 4 - b_j;
      b_tmp = b_j * 7;
      jp1j = b_tmp + 2;
      ijA = 6 - b_j;
      naxpy = 0;
      smax = std::abs(b_t1_tmp[b_tmp]);
      for (k = 2; k <= ijA; k++) {
        as = std::abs(b_t1_tmp[(b_tmp + k) - 1]);
        if (as > smax) {
          naxpy = k - 1;
          smax = as;
        }
      }
      if (b_t1_tmp[b_tmp + naxpy] != 0.0) {
        if (naxpy != 0) {
          naxpy += b_j;
          ipiv[b_j] = static_cast<signed char>(naxpy + 1);
          for (k = 0; k < 6; k++) {
            c_i = b_j + k * 6;
            as = b_t1_tmp[c_i];
            jBcol = naxpy + k * 6;
            b_t1_tmp[c_i] = b_t1_tmp[jBcol];
            b_t1_tmp[jBcol] = as;
          }
        }
        b_i = (b_tmp - b_j) + 6;
        for (c_i = jp1j; c_i <= b_i; c_i++) {
          b_t1_tmp[c_i - 1] /= b_t1_tmp[b_tmp];
        }
      }
      naxpy = b_tmp;
      for (j = 0; j <= mmj_tmp; j++) {
        as = b_t1_tmp[(b_tmp + j * 6) + 6];
        if (as != 0.0) {
          jp1j = naxpy + 8;
          b_i = (naxpy - b_j) + 12;
          for (ijA = jp1j; ijA <= b_i; ijA++) {
            b_t1_tmp[ijA - 1] += b_t1_tmp[((b_tmp + ijA) - naxpy) - 7] * -as;
          }
        }
        naxpy += 6;
      }
      i1 = ipiv[b_j];
      if (i1 != b_j + 1) {
        for (j = 0; j < 6; j++) {
          c_i = b_j + 6 * j;
          as = t1[c_i];
          ijA = (i1 + 6 * j) - 1;
          t1[c_i] = t1[ijA];
          t1[ijA] = as;
        }
      }
    }
    for (j = 0; j < 6; j++) {
      jBcol = 6 * j;
      for (k = 0; k < 6; k++) {
        naxpy = 6 * k;
        jp1j = k + jBcol;
        if (t1[jp1j] != 0.0) {
          b_i = k + 2;
          for (c_i = b_i; c_i < 7; c_i++) {
            ijA = (c_i + jBcol) - 1;
            t1[ijA] -= t1[jp1j] * b_t1_tmp[(c_i + naxpy) - 1];
          }
        }
      }
    }
    for (j = 0; j < 6; j++) {
      jBcol = 6 * j;
      for (k = 5; k >= 0; k--) {
        naxpy = 6 * k;
        b_i = k + jBcol;
        zWn = t1[b_i];
        if (zWn != 0.0) {
          t1[b_i] = zWn / b_t1_tmp[k + naxpy];
          for (c_i = 0; c_i < k; c_i++) {
            ijA = c_i + jBcol;
            t1[ijA] -= t1[b_i] * b_t1_tmp[c_i + naxpy];
          }
        }
      }
    }
    coder::eig(t1, b_p);
    smax = 2.0 * rt_atan2d_snf(Wn1, 4.0);
    b_zWn.re = smax * 0.0;
    if (smax == 0.0) {
      zWn = b_zWn.re;
      b_zWn.re = std::exp(zWn);
      b_zWn.im = 0.0;
    } else {
      as = std::exp(b_zWn.re / 2.0);
      b_zWn.re = as * (as * std::cos(smax));
      b_zWn.im = as * (as * std::sin(smax));
    }
    zWn = b_zWn.re;
    d1 = b_zWn.im;
    for (c_i = 0; c_i < 6; c_i++) {
      c_x[c_i].re = zWn - b_p[c_i].re;
      c_x[c_i].im = d1 - b_p[c_i].im;
    }
    b_x = c_x[0];
    for (k = 0; k < 5; k++) {
      as = c_x[k + 1].re;
      smax = c_x[k + 1].im;
      Wn1 = b_x.re * as - b_x.im * smax;
      im = b_x.re * smax + b_x.im * as;
      b_x.re = Wn1;
      b_x.im = im;
    }
    for (c_i = 0; c_i < 6; c_i++) {
      c_x[c_i].re = zWn - static_cast<double>(b_iv[c_i]);
      c_x[c_i].im = d1;
    }
    b_zWn = c_x[0];
    for (k = 0; k < 5; k++) {
      zWn = c_x[k + 1].re;
      d1 = c_x[k + 1].im;
      Wn1 = b_zWn.re * zWn - b_zWn.im * d1;
      im = b_zWn.re * d1 + b_zWn.im * zWn;
      b_zWn.re = Wn1;
      b_zWn.im = im;
    }
    if (b_zWn.im == 0.0) {
      if (b_x.im == 0.0) {
        smax = b_x.re / b_zWn.re;
      } else if (b_x.re == 0.0) {
        smax = 0.0;
      } else {
        smax = b_x.re / b_zWn.re;
      }
    } else if (b_zWn.re == 0.0) {
      if (b_x.re == 0.0) {
        smax = b_x.im / b_zWn.im;
      } else if (b_x.im == 0.0) {
        smax = 0.0;
      } else {
        smax = b_x.im / b_zWn.im;
      }
    } else {
      as = std::abs(b_zWn.re);
      smax = std::abs(b_zWn.im);
      if (as > smax) {
        as = b_zWn.im / b_zWn.re;
        smax = (b_x.re + as * b_x.im) / (b_zWn.re + as * b_zWn.im);
      } else if (smax == as) {
        if (b_zWn.re > 0.0) {
          smax = 0.5;
        } else {
          smax = -0.5;
        }
        if (b_zWn.im > 0.0) {
          zWn = 0.5;
        } else {
          zWn = -0.5;
        }
        smax = (b_x.re * smax + b_x.im * zWn) / as;
      } else {
        as = b_zWn.re / b_zWn.im;
        smax = (as * b_x.re + b_x.im) / (b_zWn.im + as * b_zWn.re);
      }
    }
    c[0].re = 1.0;
    c[0].im = 0.0;
    for (j = 0; j < 6; j++) {
      as = -b_p[j].re;
      Wn1 = -b_p[j].im;
      im = as * c[j].im + Wn1 * c[j].re;
      c[j + 1].re = as * c[j].re - Wn1 * c[j].im;
      c[j + 1].im = im;
      for (k = j + 1; k >= 2; k--) {
        zWn = b_p[j].re;
        d1 = b_p[j].im;
        Wn1 = zWn * c[k - 2].im + d1 * c[k - 2].re;
        c[k - 1].re -= zWn * c[k - 2].re - d1 * c[k - 2].im;
        c[k - 1].im -= Wn1;
      }
    }
    for (b_i = 0; b_i < 7; b_i++) {
      A[b_i] = c[b_i].re;
      B[b_i] = smax * static_cast<double>(b_b[b_i]);
    }
    // 'octbank:37' y = filter(B, A, x);
    b.set_size(x.size(1));
    for (b_i = 0; b_i < loop_ub; b_i++) {
      b[b_i] = x[b_i];
    }
    c_i = b.size(0) - 1;
    b_y1.set_size(b.size(0));
    naxpy = b.size(0);
    for (b_i = 0; b_i < naxpy; b_i++) {
      b_y1[b_i] = 0.0;
    }
    for (k = 0; k <= c_i; k++) {
      ijA = c_i - k;
      naxpy = ijA + 1;
      if (naxpy >= 7) {
        naxpy = 7;
      }
      for (j = 0; j < naxpy; j++) {
        jBcol = k + j;
        b_y1[jBcol] = b_y1[jBcol] + b[k] * B[j];
      }
      if (ijA < 6) {
        naxpy = ijA;
      } else {
        naxpy = 6;
      }
      as = -b_y1[k];
      for (j = 0; j < naxpy; j++) {
        jBcol = (k + j) + 1;
        b_y1[jBcol] = b_y1[jBcol] + as * A[j + 1];
      }
    }
    // 'octbank:38' P(i) = sum(y.^2) / m;
    b_i = b_y1.size(0);
    y.set_size(1, b_y1.size(0));
    for (k = 0; k < b_i; k++) {
      y[k] = b_y1[k] * b_y1[k];
    }
    p[7 - i] = coder::combineVectorElements(y) / static_cast<double>(x.size(1));
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
  loop_ub = 0;
  for (d_i = 0; d_i < 8; d_i++) {
    double d;
    d = p[d_i];
    idx[d_i] = (d > 0.0);
    if (d > 0.0) {
      trueCount++;
      tmp_data[loop_ub] = static_cast<signed char>(d_i + 1);
      loop_ub++;
    }
  }
  for (loop_ub = 0; loop_ub < trueCount; loop_ub++) {
    x_data[loop_ub] = p[tmp_data[loop_ub] - 1];
  }
  for (loop_ub = 0; loop_ub < trueCount; loop_ub++) {
    x_data[loop_ub] = std::log10(x_data[loop_ub]);
  }
  b_y.set_size(1, trueCount);
  for (loop_ub = 0; loop_ub < trueCount; loop_ub++) {
    b_y[loop_ub] = 10.0 * x_data[loop_ub];
  }
  loop_ub = 0;
  // 'octbank:60' P(~idx) = NaN * ones(sum(~idx), 1);
  for (d_i = 0; d_i < 8; d_i++) {
    if (p[d_i] > 0.0) {
      p[d_i] = b_y[loop_ub];
      loop_ub++;
    }
    if (!idx[d_i]) {
      p[d_i] = rtNaN;
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
