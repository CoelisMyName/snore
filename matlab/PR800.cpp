//
// File: PR800.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "PR800.h"
#include "SnoringRecognition_rtwutil.h"
#include "blockedSummation.h"
#include "combineVectorElements.h"
#include "fft.h"
#include "hamming.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "v_enframe.h"
#include "vvarstd.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [PR800_mean, PR800_max, PR800_min, PR800_var] = PR800(x, Fs)
//
// UNTITLED4 此处显示有关此函数的摘要
//    此处显示详细说明
//
// Arguments    : const coder::array<double, 1U> &x
//                double Fs
//                double *PR800_mean
//                double *PR800_max
//                double *PR800_min
//                double *PR800_var
// Return Type  : void
//
void PR800(const coder::array<double, 1U> &x, double Fs, double *PR800_mean,
           double *PR800_max, double *PR800_min, double *PR800_var)
{
  coder::array<creal_T, 1U> Z;
  coder::array<double, 2U> b_PR800;
  coder::array<double, 2U> r;
  coder::array<double, 2U> y;
  coder::array<double, 1U> b_x;
  coder::array<double, 1U> wind;
  double f1;
  double wlen;
  int b_loop_ub;
  int c_loop_ub;
  int d_loop_ub;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int loop_ub;
  int nx;
  // 'PR800:4' wlen = fix(0.02 * Fs);
  wlen = std::trunc(0.02 * Fs);
  // 'PR800:5' inc = fix(0.5 * wlen);
  // 'PR800:6' wind = hamming(wlen);
  // 'PR800:7' y = v_enframe(x, wind, inc)';
  coder::hamming(wlen, wind);
  v_enframe(x, wind, std::trunc(0.5 * wlen), r);
  y.set_size(r.size(1), r.size(0));
  nx = r.size(0);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i1, loop_ub, i)

  for (i = 0; i < nx; i++) {
    loop_ub = r.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      y[i1 + y.size(0) * i] = r[i + r.size(0) * i1];
    }
  }
  // 'PR800:8' fn = size(y, 2);
  // 总帧数
  // 'PR800:9' PR800 = zeros(1, fn);
  b_PR800.set_size(1, y.size(1));
  // 'PR800:10' ds = Fs / wlen;
  wlen = Fs / wlen;
  // 'PR800:11' f1 = 800 / ds + 1;
  f1 = 800.0 / wlen + 1.0;
  // 'PR800:12' f2 = 8000 / ds + 1;
  wlen = 8000.0 / wlen + 1.0;
  // 'PR800:14' for i = 1:fn
  i2 = y.size(1);
  if (0 <= y.size(1) - 1) {
    i3 = y.size(0);
    b_loop_ub = y.size(0);
    if (1.0 > f1) {
      c_loop_ub = 0;
    } else {
      c_loop_ub = static_cast<int>(f1);
    }
    if (f1 > wlen) {
      i4 = 0;
      i5 = 0;
      i6 = 1;
    } else {
      i4 = static_cast<int>(f1) - 1;
      i5 = static_cast<int>(wlen);
      i6 = static_cast<int>(f1);
    }
    d_loop_ub = i5 - i4;
  }
  for (int b_i{0}; b_i < i2; b_i++) {
    // 'PR800:15' YY = y(:, i);
    // 取一帧数据
    // 'PR800:16' n = 0:length(YY) - 1;
    // 'PR800:17' Z = fft(YY);
    wind.set_size(i3);
    for (nx = 0; nx < b_loop_ub; nx++) {
      wind[nx] = y[nx + y.size(0) * b_i];
    }
    coder::fft(wind, Z);
    // 'PR800:18' f = n * Fs / length(YY);
    // 'PR800:19' mag = abs(Z);
    nx = Z.size(0);
    wind.set_size(Z.size(0));
    for (int k{0}; k < nx; k++) {
      wind[k] = rt_hypotd_snf(Z[k].re, Z[k].im);
    }
    // 'PR800:20' PR800(i) = log10(sum(mag(1:f1) .* mag(1:f1)) / sum(mag(f1:f2)
    // .* mag(f1:f2)));
    b_x.set_size(c_loop_ub);
    for (nx = 0; nx < c_loop_ub; nx++) {
      b_x[nx] = wind[nx] * wind[nx];
    }
    for (nx = 0; nx < d_loop_ub; nx++) {
      wind[nx] = wind[i4 + nx] * wind[(i6 + nx) - 1];
    }
    wind.set_size(i5 - i4);
    b_PR800[b_i] = std::log10(coder::blockedSummation(b_x, b_x.size(0)) /
                              coder::blockedSummation(wind, wind.size(0)));
  }
  //  for i = 1:fn
  //      YY = y(:,i);  %取一帧数据
  //      n = 0:length(YY)-1;
  //      Z=fft(YY);
  //      f=n*Fs/length(YY);
  //      mag=abs(Z);
  //      PR800(i)=log10(sum(mag(1:17).*mag(1:17))/sum(mag(17:161).*mag(17:161)));
  //  end
  // 'PR800:31' PR800_mean = mean(PR800);
  *PR800_mean = coder::combineVectorElements(b_PR800) /
                static_cast<double>(b_PR800.size(1));
  // 'PR800:32' PR800_max = max(PR800);
  *PR800_max = coder::internal::maximum(b_PR800);
  // 'PR800:33' PR800_min = min(PR800);
  *PR800_min = coder::internal::minimum(b_PR800);
  // 'PR800:34' PR800_var = var(PR800);
  nx = b_PR800.size(1);
  wind = b_PR800.reshape(nx);
  *PR800_var = coder::vvarstd(wind, b_PR800.size(1));
}

//
// File trailer for PR800.cpp
//
// [EOF]
//
