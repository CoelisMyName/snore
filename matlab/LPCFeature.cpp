//
// File: LPCFeature.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "LPCFeature.h"
#include "FFTImplementationCallback.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "hamming.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "v_enframe.h"
#include "vvarstd.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
//
// function [LPC, LPC_mean, LPC_max, LPC_min, LPC_var] = LPCFeature(x, Fs)
//
// UNTITLED2 此处显示有关此函数的摘要
//    此处显示详细说明
//
// Arguments    : const coder::array<double, 1U> &x
//                double Fs
//                coder::array<double, 2U> &LPC
//                double LPC_mean[12]
//                double LPC_max[12]
//                double LPC_min[12]
//                double LPC_var[12]
// Return Type  : void
//
void LPCFeature(const coder::array<double, 1U> &x, double Fs,
                coder::array<double, 2U> &LPC, double LPC_mean[12],
                double LPC_max[12], double LPC_min[12], double LPC_var[12])
{
  coder::array<creal_T, 1U> X;
  coder::array<double, 2U> b_LPC;
  coder::array<double, 2U> c_LPC;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> r;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  coder::array<double, 2U> y;
  coder::array<double, 1U> b_wind;
  coder::array<double, 1U> b_y;
  coder::array<double, 1U> c_y;
  coder::array<double, 1U> wind;
  creal_T A_data[13];
  creal_T temp_A_data[12];
  creal_T temp_a_data[12];
  creal_T temp_auf_data[12];
  double LPC_max_tmp;
  double bsum;
  double wlen;
  int outsize[2];
  int eint;
  int hi;
  int i;
  int i1;
  int i2;
  int i3;
  int ib;
  int k;
  int loop_ub;
  int naxpy;
  int nx;
  int nx_m_nb;
  int xblockoffset;
  int xi;
  int xpageoffset;
  boolean_T p;
  // 'LPCFeature:4' wlen = fix(0.02 * Fs);
  wlen = std::trunc(0.02 * Fs);
  // 'LPCFeature:5' inc = fix(0.5 * wlen);
  // 'LPCFeature:6' wind = hamming(wlen);
  coder::hamming(wlen, wind);
  // 'LPCFeature:7' y = v_enframe(x, wind, inc)';
  v_enframe(x, wind, std::trunc(0.5 * wlen), r);
  y.set_size(r.size(1), r.size(0));
  loop_ub = r.size(0);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hi, xi, i)

  for (i = 0; i < loop_ub; i++) {
    xi = r.size(1);
    for (hi = 0; hi < xi; hi++) {
      y[hi + y.size(0) * i] = r[i + r.size(0) * hi];
    }
  }
  // 分帧
  // 'LPCFeature:8' fn = size(y, 2);
  // 总帧数
  // 'LPCFeature:9' LPC = zeros(13, fn);
  b_LPC.set_size(13, y.size(1));
  loop_ub = 13 * y.size(1);
  if (static_cast<int>(loop_ub < 1200)) {
    for (i = 0; i < loop_ub; i++) {
      b_LPC[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < loop_ub; i++) {
      b_LPC[i] = 0.0;
    }
  }
  // 'LPCFeature:11' for i = 1:fn
  i1 = y.size(1);
  for (int b_i{0}; b_i < i1; b_i++) {
    double ar;
    double im;
    double re;
    double temp_J_re;
    // 'LPCFeature:12' YY = y(:, i);
    // 取一帧数据
    // 'LPCFeature:13' z_new = filter([1 -0.99], 1, YY);
    i2 = y.size(0);
    wind.set_size(y.size(0));
    loop_ub = y.size(0);
    for (i3 = 0; i3 < loop_ub; i3++) {
      wind[i3] = 0.0;
    }
    if (y.size(0) >= 4) {
      for (loop_ub = 0; loop_ub < 2; loop_ub++) {
        naxpy = loop_ub + 1;
        for (nx = naxpy; nx <= i2; nx++) {
          wind[nx - 1] =
              wind[nx - 1] + (-1.99 * static_cast<double>(loop_ub) + 1.0) *
                                 y[((nx - loop_ub) + y.size(0) * b_i) - 1];
        }
      }
    } else {
      if (y.size(0) > 2) {
        nx_m_nb = 0;
      } else {
        nx_m_nb = -1;
      }
      for (loop_ub = 0; loop_ub <= nx_m_nb; loop_ub++) {
        wind[0] = wind[0] + y[y.size(0) * b_i];
        wind[1] = wind[1] + y[y.size(0) * b_i] * -0.99;
      }
      naxpy = (y.size(0) - nx_m_nb) - 2;
      i3 = nx_m_nb + 2;
      for (loop_ub = i3; loop_ub <= i2; loop_ub++) {
        for (nx = 0; nx <= naxpy; nx++) {
          nx_m_nb = (loop_ub + nx) - 1;
          wind[nx_m_nb] =
              wind[nx_m_nb] + y[(loop_ub + y.size(0) * b_i) - 1] *
                                  (-1.99 * static_cast<double>(nx) + 1.0);
        }
        naxpy--;
      }
    }
    // 预加重
    // 'LPCFeature:14' LPC(:, i) = m_lpc(z_new, 12);
    // 'm_lpc:2' [m, n] = size(x);
    // 'm_lpc:4' if (n > 1) && (m == 1)
    // 'm_lpc:9' X = fft(x, 2^nextpow2(2 * size(x, 1) - 1));
    wlen = frexp(static_cast<double>(static_cast<unsigned int>(
                     std::abs(2.0 * static_cast<double>(wind.size(0)) - 1.0))),
                 &eint);
    nx_m_nb = eint;
    if (wlen == 0.5) {
      nx_m_nb = eint - 1;
    }
    wlen = rt_powd_snf(2.0, static_cast<double>(nx_m_nb));
    if ((wind.size(0) == 0) || (0 == static_cast<int>(wlen))) {
      nx_m_nb = static_cast<int>(wlen);
      X.set_size(nx_m_nb);
      for (i2 = 0; i2 < nx_m_nb; i2++) {
        X[i2].re = 0.0;
        X[i2].im = 0.0;
      }
    } else {
      boolean_T useRadix2;
      useRadix2 =
          ((static_cast<int>(wlen) > 0) &&
           ((static_cast<int>(wlen) & (static_cast<int>(wlen) - 1)) == 0));
      coder::internal::FFTImplementationCallback::get_algo_sizes(
          static_cast<int>(wlen), useRadix2, &nx_m_nb, &naxpy);
      coder::internal::FFTImplementationCallback::generate_twiddle_tables(
          naxpy, useRadix2, costab, sintab, sintabinv);
      if (useRadix2) {
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
            wind, static_cast<int>(wlen), costab, sintab, X);
      } else {
        coder::internal::FFTImplementationCallback::dobluesteinfft(
            wind, nx_m_nb, static_cast<int>(wlen), costab, sintab, sintabinv,
            X);
      }
    }
    // 'm_lpc:10' R = ifft(abs(X).^2);
    nx = X.size(0);
    b_y.set_size(X.size(0));
    for (loop_ub = 0; loop_ub < nx; loop_ub++) {
      b_y[loop_ub] = rt_hypotd_snf(X[loop_ub].re, X[loop_ub].im);
    }
    c_y.set_size(b_y.size(0));
    nx = b_y.size(0);
    for (loop_ub = 0; loop_ub < nx; loop_ub++) {
      c_y[loop_ub] = b_y[loop_ub] * b_y[loop_ub];
    }
    coder::ifft(c_y, X);
    // 'm_lpc:11' R = R ./ m;
    temp_J_re = wind.size(0);
    loop_ub = X.size(0);
    for (i2 = 0; i2 < loop_ub; i2++) {
      ar = X[i2].re;
      im = X[i2].im;
      if (im == 0.0) {
        re = ar / temp_J_re;
        im = 0.0;
      } else if (ar == 0.0) {
        re = 0.0;
        im /= temp_J_re;
      } else {
        re = ar / temp_J_re;
        im /= temp_J_re;
      }
      X[i2].re = re;
      X[i2].im = im;
    }
    //  Biased autocorrelation estimate
    // 'm_lpc:13' [a, e] = levinson(R, N);
    naxpy = 12;
    if ((12 == X.size(0)) || (12 > X.size(0))) {
      naxpy = X.size(0) - 1;
    }
    if (naxpy == 0) {
      A_data[0].re = 1.0;
      A_data[0].im = 0.0;
    } else if (X.size(0) == 1) {
      A_data[0].re = 1.0;
      A_data[0].im = 0.0;
    } else {
      double temp_J_im;
      if (0 <= naxpy - 1) {
        std::memset(&temp_a_data[0], 0, naxpy * sizeof(creal_T));
      }
      if (0 <= naxpy - 1) {
        std::memset(&temp_A_data[0], 0, naxpy * sizeof(creal_T));
      }
      if (0 <= naxpy - 1) {
        std::memset(&temp_auf_data[0], 0, naxpy * sizeof(creal_T));
      }
      i2 = (2 <= naxpy + 1);
      temp_a_data[0].re = -X[0].re;
      temp_a_data[0].im = -X[0].im;
      temp_J_re = X[0].re;
      temp_J_im = 0.0;
      for (loop_ub = 0; loop_ub < naxpy; loop_ub++) {
        double d;
        double temp_kprod_im;
        wlen = 0.0;
        temp_kprod_im = 0.0;
        for (nx = 0; nx < loop_ub; nx++) {
          temp_auf_data[nx] = temp_a_data[nx];
          nx_m_nb = ((i2 + loop_ub) - nx) - 1;
          wlen += temp_a_data[nx].re * X[nx_m_nb].re -
                  temp_a_data[nx].im * X[nx_m_nb].im;
          temp_kprod_im += temp_a_data[nx].re * X[nx_m_nb].im +
                           temp_a_data[nx].im * X[nx_m_nb].re;
        }
        nx_m_nb = i2 + loop_ub;
        ar = -(X[nx_m_nb].re + wlen);
        im = -(X[nx_m_nb].im + temp_kprod_im);
        if (temp_J_im == 0.0) {
          if (im == 0.0) {
            re = ar / temp_J_re;
            im = 0.0;
          } else if (ar == 0.0) {
            re = 0.0;
            im /= temp_J_re;
          } else {
            re = ar / temp_J_re;
            im /= temp_J_re;
          }
        } else if (temp_J_re == 0.0) {
          if (ar == 0.0) {
            re = im / temp_J_im;
            im = 0.0;
          } else if (im == 0.0) {
            re = 0.0;
            im = -(ar / temp_J_im);
          } else {
            re = im / temp_J_im;
            im = -(ar / temp_J_im);
          }
        } else {
          temp_kprod_im = std::abs(temp_J_re);
          wlen = std::abs(temp_J_im);
          if (temp_kprod_im > wlen) {
            wlen = temp_J_im / temp_J_re;
            d = temp_J_re + wlen * temp_J_im;
            re = (ar + wlen * im) / d;
            im = (im - wlen * ar) / d;
          } else if (wlen == temp_kprod_im) {
            if (temp_J_re > 0.0) {
              wlen = 0.5;
            } else {
              wlen = -0.5;
            }
            if (temp_J_im > 0.0) {
              d = 0.5;
            } else {
              d = -0.5;
            }
            re = (ar * wlen + im * d) / temp_kprod_im;
            im = (im * wlen - ar * d) / temp_kprod_im;
          } else {
            wlen = temp_J_re / temp_J_im;
            d = temp_J_im + wlen * temp_J_re;
            re = (wlen * ar + im) / d;
            im = (wlen * im - ar) / d;
          }
        }
        wlen = re * re - im * -im;
        temp_kprod_im = re * -im + im * re;
        d = (1.0 - wlen) * temp_J_re - (0.0 - temp_kprod_im) * temp_J_im;
        temp_J_im =
            (1.0 - wlen) * temp_J_im + (0.0 - temp_kprod_im) * temp_J_re;
        temp_J_re = d;
        for (nx = 0; nx < loop_ub; nx++) {
          nx_m_nb = (loop_ub - nx) - 1;
          wlen = temp_auf_data[nx_m_nb].re;
          d = -temp_auf_data[nx_m_nb].im;
          temp_a_data[nx].re = temp_auf_data[nx].re + (re * wlen - im * d);
          temp_a_data[nx].im = temp_auf_data[nx].im + (re * d + im * wlen);
        }
        temp_a_data[loop_ub].re = re;
        temp_a_data[loop_ub].im = im;
      }
      if (0 <= naxpy - 1) {
        std::copy(&temp_a_data[0], &temp_a_data[naxpy], &temp_A_data[0]);
      }
      if (1 > naxpy) {
        loop_ub = 0;
      } else {
        loop_ub = naxpy;
      }
      A_data[0].re = 1.0;
      A_data[0].im = 0.0;
      if (0 <= loop_ub - 1) {
        std::copy(&temp_A_data[0], &temp_A_data[loop_ub], &A_data[1]);
      }
    }
    // 'm_lpc:15' a = real(a);
    for (i2 = 0; i2 < 13; i2++) {
      b_LPC[i2 + 13 * b_i] = A_data[i2].re;
    }
  }
  // 'LPCFeature:17' LPC = LPC';
  c_LPC.set_size(b_LPC.size(1), 13);
  loop_ub = b_LPC.size(1);
  if (static_cast<int>(13 * b_LPC.size(1) < 1200)) {
    for (i = 0; i < 13; i++) {
      for (hi = 0; hi < loop_ub; hi++) {
        c_LPC[hi + c_LPC.size(0) * i] = b_LPC[i + 13 * hi];
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hi, i)

    for (i = 0; i < 13; i++) {
      for (hi = 0; hi < loop_ub; hi++) {
        c_LPC[hi + c_LPC.size(0) * i] = b_LPC[i + 13 * hi];
      }
    }
  }
  // 每一行有13个系数
  // 'LPCFeature:18' LPC = LPC(:, 2:13);
  loop_ub = c_LPC.size(0);
  LPC.set_size(c_LPC.size(0), 12);
  nx_m_nb = c_LPC.size(0);
  if (static_cast<int>(12 * c_LPC.size(0) < 1200)) {
    for (i = 0; i < 12; i++) {
      for (hi = 0; hi < loop_ub; hi++) {
        LPC[hi + LPC.size(0) * i] = c_LPC[hi + c_LPC.size(0) * (i + 1)];
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hi, i)

    for (i = 0; i < 12; i++) {
      for (hi = 0; hi < nx_m_nb; hi++) {
        LPC[hi + LPC.size(0) * i] = c_LPC[hi + c_LPC.size(0) * (i + 1)];
      }
    }
  }
  // 'LPCFeature:19' LPC_mean = mean(LPC);
  if (c_LPC.size(0) == 0) {
    std::memset(&LPC_mean[0], 0, 12U * sizeof(double));
  } else {
    if (c_LPC.size(0) <= 1024) {
      nx_m_nb = c_LPC.size(0) - 1;
      nx = 0;
      naxpy = 1;
    } else {
      nx_m_nb = 1023;
      naxpy = c_LPC.size(0) / 1024;
      nx = c_LPC.size(0) - (naxpy << 10);
      if (nx > 0) {
        naxpy++;
      } else {
        nx = 1024;
      }
    }
    i1 = c_LPC.size(0);
    i2 = c_LPC.size(0);
    i3 = c_LPC.size(0);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i, k, hi, bsum, xblockoffset, ib, xpageoffset, xi)

    for (xi = 0; xi < 12; xi++) {
      xpageoffset = xi * i1;
      LPC_mean[xi] =
          c_LPC[xpageoffset % i2 + c_LPC.size(0) * (xpageoffset / i3 + 1)];
      for (k = 2; k <= nx_m_nb + 1; k++) {
        i = (xpageoffset + k) - 1;
        LPC_mean[xi] +=
            c_LPC[i % c_LPC.size(0) + c_LPC.size(0) * (i / c_LPC.size(0) + 1)];
      }
      for (ib = 2; ib <= naxpy; ib++) {
        xblockoffset = xpageoffset + ((ib - 1) << 10);
        bsum = c_LPC[xblockoffset % c_LPC.size(0) +
                     c_LPC.size(0) * (xblockoffset / c_LPC.size(0) + 1)];
        if (ib == naxpy) {
          hi = nx;
        } else {
          hi = 1024;
        }
        for (k = 2; k <= hi; k++) {
          i = (xblockoffset + k) - 1;
          bsum += c_LPC[i % c_LPC.size(0) +
                        c_LPC.size(0) * (i / c_LPC.size(0) + 1)];
        }
        LPC_mean[xi] += bsum;
      }
    }
  }
  i1 = c_LPC.size(0);
  // 'LPCFeature:20' LPC_max = max(LPC);
  nx_m_nb = c_LPC.size(0);
  // 'LPCFeature:21' LPC_min = min(LPC);
  naxpy = c_LPC.size(0);
  // 'LPCFeature:22' LPC_var = var(LPC);
  nx = c_LPC.size(0);
  outsize[0] = c_LPC.size(0);
  loop_ub = c_LPC.size(0);
  i2 = c_LPC.size(0);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    b_wind, i, k, p, bsum, xi, hi, LPC_max_tmp)

  for (hi = 0; hi < 12; hi++) {
    LPC_mean[hi] /= static_cast<double>(i1);
    LPC_max_tmp = c_LPC[c_LPC.size(0) * (hi + 1)];
    LPC_max[hi] = LPC_max_tmp;
    for (xi = 2; xi <= nx_m_nb; xi++) {
      bsum = c_LPC[(xi + c_LPC.size(0) * (hi + 1)) - 1];
      if (std::isnan(bsum)) {
        p = false;
      } else if (std::isnan(LPC_max[hi])) {
        p = true;
      } else {
        p = (LPC_max[hi] < bsum);
      }
      if (p) {
        LPC_max[hi] = bsum;
      }
    }
    LPC_min[hi] = LPC_max_tmp;
    for (xi = 2; xi <= naxpy; xi++) {
      bsum = c_LPC[(xi + c_LPC.size(0) * (hi + 1)) - 1];
      if (std::isnan(bsum)) {
        p = false;
      } else if (std::isnan(LPC_min[hi])) {
        p = true;
      } else {
        p = (LPC_min[hi] > bsum);
      }
      if (p) {
        LPC_min[hi] = bsum;
      }
    }
    xi = hi * nx;
    b_wind.set_size(outsize[0]);
    for (i = 0; i < loop_ub; i++) {
      b_wind[i] = 0.0;
    }
    for (k = 0; k < nx; k++) {
      i = xi + k;
      b_wind[k] =
          c_LPC[i % c_LPC.size(0) + c_LPC.size(0) * (i / c_LPC.size(0) + 1)];
    }
    LPC_var[hi] = coder::vvarstd(b_wind, i2);
  }
}

//
// File trailer for LPCFeature.cpp
//
// [EOF]
//
