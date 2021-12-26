//
// File: CrestFactor.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "CrestFactor.h"
#include "blockedSummation.h"
#include "combineVectorElements.h"
#include "hamming.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "v_enframe.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [CF_mean] = CrestFactor(x, fs)
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs
// Return Type  : double
//
double CrestFactor(const coder::array<double, 1U> &x, double fs)
{
  coder::array<double, 2U> Crest_Factor;
  coder::array<double, 2U> r;
  coder::array<double, 2U> y;
  coder::array<double, 1U> b_x;
  coder::array<double, 1U> wnd;
  double CF_mean;
  double wlen;
  int b_loop_ub;
  int i;
  int i1;
  int i2;
  int loop_ub;
  // 'CrestFactor:3' wlen = fix(0.02 * fs);
  wlen = std::trunc(0.02 * fs);
  // 'CrestFactor:4' wnd = hamming(wlen);
  // 'CrestFactor:5' inc = fix(0.5 * wlen);
  // 'CrestFactor:6' y = v_enframe(x, wnd, inc)';
  coder::hamming(wlen, wnd);
  v_enframe(x, wnd, std::trunc(0.5 * wlen), r);
  y.set_size(r.size(1), r.size(0));
  loop_ub = r.size(0);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i1, b_loop_ub, i)

  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = r.size(1);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      y[i1 + y.size(0) * i] = r[i + r.size(0) * i1];
    }
  }
  // 'CrestFactor:7' fn = size(y, 2);
  // 'CrestFactor:8' Crest_Factor = zeros(1, fn);
  Crest_Factor.set_size(1, y.size(1));
  // 'CrestFactor:10' for i = 1:fn
  i2 = y.size(1);
  for (int b_i{0}; b_i < i2; b_i++) {
    double d;
    int i3;
    int k;
    // 'CrestFactor:11' YY = y(:, i);
    // 取一帧数据
    // 'CrestFactor:12' V90th = sort(abs(YY));
    i3 = y.size(0) - 1;
    wnd.set_size(y.size(0));
    for (k = 0; k <= i3; k++) {
      wnd[k] = std::abs(y[k + y.size(0) * b_i]);
    }
    coder::internal::sort(wnd);
    // 从小到大排列
    // 'CrestFactor:13' V90 = max(V90th(1:end - floor(length(V90th) * 0.1)));
    d = static_cast<double>(wnd.size(0)) -
        std::floor(static_cast<double>(wnd.size(0)) * 0.1);
    // 前90 %d的最大值
    // 'CrestFactor:14' V10th = V90th(floor(length(V90th) * 0.1):end -
    // floor(length(V90th) * 0.1));
    i3 = static_cast<int>(std::floor(static_cast<double>(wnd.size(0)) * 0.1));
    wlen = static_cast<double>(wnd.size(0)) -
           std::floor(static_cast<double>(wnd.size(0)) * 0.1);
    if (i3 > wlen) {
      i3 = 0;
      k = 0;
    } else {
      i3--;
      k = static_cast<int>(wlen);
    }
    //  10 %到90 %之间的值
    // 'CrestFactor:15' Vrms = rms(V10th);
    loop_ub = k - i3;
    b_x.set_size(loop_ub);
    for (k = 0; k < loop_ub; k++) {
      wlen = wnd[i3 + k];
      b_x[k] = wlen * wlen;
    }
    // 'CrestFactor:16' Crest_Factor(i) = V90 / Vrms;
    if (1.0 > d) {
      i3 = 0;
    } else {
      i3 = static_cast<int>(d);
    }
    wnd.set_size(i3);
    Crest_Factor[b_i] = coder::internal::maximum(wnd) /
                        std::sqrt(coder::blockedSummation(b_x, b_x.size(0)) /
                                  static_cast<double>(b_x.size(0)));
  }
  // 'CrestFactor:19' CF_mean = mean(Crest_Factor);
  CF_mean = coder::combineVectorElements(Crest_Factor) /
            static_cast<double>(Crest_Factor.size(1));
  return CF_mean;
}

//
// File trailer for CrestFactor.cpp
//
// [EOF]
//
