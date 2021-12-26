//
// File: HENR.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "HENR.h"
#include "SnoringRecognition_rtwutil.h"
#include "combineVectorElements.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "v_enframe.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [Eh, En_mean] = HENR(x, fs)
//
// 高能量帧比率，计算一段声音信号中短时能量大于平均短时能量*0.5的比率
//  输入x为信号，fs为采样率
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs
//                double *Eh
//                double *En_mean
// Return Type  : void
//
void HENR(const coder::array<double, 1U> &x, double fs, double *Eh,
          double *En_mean)
{
  coder::array<double, 2U> En;
  coder::array<double, 2U> r;
  coder::array<double, 2U> r1;
  coder::array<double, 2U> y;
  coder::array<double, 1U> b_wnd;
  coder::array<double, 1U> wnd;
  coder::array<boolean_T, 2U> b_x;
  double b;
  double b_y;
  double d;
  double wlen;
  int b_loop_ub;
  int i;
  int i1;
  int k;
  int loop_ub;
  int nx;
  int nz;
  boolean_T guard1{false};
  // 'HENR:4' wlen = fix(0.02 * fs);
  wlen = std::trunc(0.02 * fs);
  // 'HENR:5' inc = fix(0.5 * wlen);
  // 'HENR:6' wnd = hanning(wlen);
  guard1 = false;
  if (wlen == 0.0) {
    nx = 0;
    guard1 = true;
  } else if (wlen == 1.0) {
    nx = 1;
    guard1 = true;
  } else if (coder::iseven(wlen)) {
    b = wlen / 2.0;
    if (b < 1.0) {
      r.set_size(1, 0);
    } else if (std::isinf(b) && (1.0 == b)) {
      r.set_size(1, 1);
      r[0] = rtNaN;
    } else {
      loop_ub = static_cast<int>(std::floor(b - 1.0));
      r.set_size(1, loop_ub + 1);
      if (static_cast<int>(loop_ub + 1 < 1200)) {
        for (i1 = 0; i1 <= loop_ub; i1++) {
          r[i1] = static_cast<double>(i1) + 1.0;
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

        for (i1 = 0; i1 <= loop_ub; i1++) {
          r[i1] = static_cast<double>(i1) + 1.0;
        }
      }
    }
    b = wlen + 1.0;
    wnd.set_size(r.size(1));
    loop_ub = r.size(1);
    if (static_cast<int>(r.size(1) < 1200)) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = 6.2831853071795862 * r[i1] / (wlen + 1.0);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = 6.2831853071795862 * r[i1] / b;
      }
    }
    nx = wnd.size(0);
    if (static_cast<int>(wnd.size(0) < 1200)) {
      for (k = 0; k < nx; k++) {
        wnd[k] = std::cos(wnd[k]);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = 0; k < nx; k++) {
        wnd[k] = std::cos(wnd[k]);
      }
    }
    loop_ub = wnd.size(0);
    if (static_cast<int>(wnd.size(0) < 1200)) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = 0.5 * (1.0 - wnd[i1]);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = 0.5 * (1.0 - wnd[i1]);
      }
    }
    if (1 > wnd.size(0)) {
      i = 0;
      nx = 1;
      nz = -1;
    } else {
      i = wnd.size(0) - 1;
      nx = -1;
      nz = 0;
    }
    b_wnd.set_size((wnd.size(0) + div_s32_floor(nz - i, nx)) + 1);
    loop_ub = wnd.size(0);
    if (static_cast<int>(wnd.size(0) < 1200)) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_wnd[i1] = wnd[i1];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < loop_ub; i1++) {
        b_wnd[i1] = wnd[i1];
      }
    }
    loop_ub = div_s32_floor(nz - i, nx);
    if (static_cast<int>(loop_ub + 1 < 1200)) {
      for (i1 = 0; i1 <= loop_ub; i1++) {
        b_wnd[i1 + wnd.size(0)] = wnd[i + nx * i1];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 <= loop_ub; i1++) {
        b_wnd[i1 + wnd.size(0)] = wnd[i + nx * i1];
      }
    }
    wnd.set_size(b_wnd.size(0));
    loop_ub = b_wnd.size(0);
    if (static_cast<int>(b_wnd.size(0) < 1200)) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = b_wnd[i1];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = b_wnd[i1];
      }
    }
  } else {
    b = (wlen + 1.0) / 2.0;
    if (b < 1.0) {
      r.set_size(1, 0);
    } else if (std::isinf(b) && (1.0 == b)) {
      r.set_size(1, 1);
      r[0] = rtNaN;
    } else {
      loop_ub = static_cast<int>(std::floor(b - 1.0));
      r.set_size(1, loop_ub + 1);
      if (static_cast<int>(loop_ub + 1 < 1200)) {
        for (i1 = 0; i1 <= loop_ub; i1++) {
          r[i1] = static_cast<double>(i1) + 1.0;
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

        for (i1 = 0; i1 <= loop_ub; i1++) {
          r[i1] = static_cast<double>(i1) + 1.0;
        }
      }
    }
    b = wlen + 1.0;
    wnd.set_size(r.size(1));
    loop_ub = r.size(1);
    if (static_cast<int>(r.size(1) < 1200)) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = 6.2831853071795862 * r[i1] / (wlen + 1.0);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = 6.2831853071795862 * r[i1] / b;
      }
    }
    nx = wnd.size(0);
    if (static_cast<int>(wnd.size(0) < 1200)) {
      for (k = 0; k < nx; k++) {
        wnd[k] = std::cos(wnd[k]);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = 0; k < nx; k++) {
        wnd[k] = std::cos(wnd[k]);
      }
    }
    loop_ub = wnd.size(0);
    if (static_cast<int>(wnd.size(0) < 1200)) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = 0.5 * (1.0 - wnd[i1]);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = 0.5 * (1.0 - wnd[i1]);
      }
    }
    if (1 > wnd.size(0) - 1) {
      i = 0;
      nx = 1;
      nz = -1;
    } else {
      i = wnd.size(0) - 2;
      nx = -1;
      nz = 0;
    }
    b_wnd.set_size((wnd.size(0) + div_s32_floor(nz - i, nx)) + 1);
    loop_ub = wnd.size(0);
    if (static_cast<int>(wnd.size(0) < 1200)) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_wnd[i1] = wnd[i1];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < loop_ub; i1++) {
        b_wnd[i1] = wnd[i1];
      }
    }
    loop_ub = div_s32_floor(nz - i, nx);
    if (static_cast<int>(loop_ub + 1 < 1200)) {
      for (i1 = 0; i1 <= loop_ub; i1++) {
        b_wnd[i1 + wnd.size(0)] = wnd[i + nx * i1];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 <= loop_ub; i1++) {
        b_wnd[i1 + wnd.size(0)] = wnd[i + nx * i1];
      }
    }
    wnd.set_size(b_wnd.size(0));
    loop_ub = b_wnd.size(0);
    if (static_cast<int>(b_wnd.size(0) < 1200)) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = b_wnd[i1];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

      for (i1 = 0; i1 < loop_ub; i1++) {
        wnd[i1] = b_wnd[i1];
      }
    }
  }
  if (guard1) {
    wnd.set_size(nx);
    for (i = 0; i < nx; i++) {
      wnd[0] = 1.0;
    }
  }
  // 'HENR:7' y = v_enframe(x, wnd, inc)';
  v_enframe(x, wnd, std::trunc(0.5 * wlen), r1);
  y.set_size(r1.size(1), r1.size(0));
  loop_ub = r1.size(0);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    k, b_loop_ub, i1)

  for (i1 = 0; i1 < loop_ub; i1++) {
    b_loop_ub = r1.size(1);
    for (k = 0; k < b_loop_ub; k++) {
      y[k + y.size(0) * i1] = r1[i1 + r1.size(0) * k];
    }
  }
  // 'HENR:8' fn = size(y, 2);
  // 'HENR:9' En = zeros(1, fn);
  En.set_size(1, y.size(1));
  // 'HENR:11' for i = 1:fn
  i = y.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    d, i1, b_y, b_loop_ub, k)

  for (k = 0; k < i; k++) {
    // 'HENR:12' Y = y(:, i);
    // 'HENR:13' En(i) = Y' * Y;
    b_loop_ub = y.size(0);
    b_y = 0.0;
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      d = y[i1 + y.size(0) * k];
      b_y += d * d;
    }
    En[k] = b_y;
  }
  // 'HENR:16' En_mean = mean(En);
  *En_mean = coder::combineVectorElements(En) / static_cast<double>(En.size(1));
  // 求取频率能量
  // 'HENR:17' Eh = sum(En > (0.5 * En_mean)) / fn;
  b_x.set_size(1, En.size(1));
  b = 0.5 * *En_mean;
  loop_ub = En.size(1);
  if (static_cast<int>(En.size(1) < 1200)) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_x[i1] = (En[i1] > b);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

    for (i1 = 0; i1 < loop_ub; i1++) {
      b_x[i1] = (En[i1] > b);
    }
  }
  nx = b_x.size(1);
  if (b_x.size(1) == 0) {
    nz = 0;
  } else {
    nz = b_x[0];
    for (loop_ub = 2; loop_ub <= nx; loop_ub++) {
      nz += b_x[loop_ub - 1];
    }
  }
  *Eh = static_cast<double>(nz) / static_cast<double>(y.size(1));
}

//
// File trailer for HENR.cpp
//
// [EOF]
//
