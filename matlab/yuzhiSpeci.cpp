//
// File: yuzhiSpeci.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "yuzhiSpeci.h"
#include "histcounts.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function pianyi = yuzhiSpeci(d, position)
//
// Arguments    : const coder::array<double, 2U> &d
//                double position
// Return Type  : double
//
double yuzhiSpeci(const coder::array<double, 2U> &d, double position)
{
  coder::array<double, 2U> ddn;
  coder::array<double, 2U> dn;
  double a__1_data[21];
  double ddnn_data[20];
  double down;
  double pianyi;
  double up;
  double up_tmp;
  int a__1_size[2];
  int ddnn_size[2];
  int b_i;
  int i;
  int loop_ub;
  int partialTrueCount;
  int trueCount;
  // 'yuzhiSpeci:2' up = (max(d) - min(d)) / 200 * position + min(d);
  down = coder::internal::minimum(d);
  up_tmp = (coder::internal::maximum(d) - down) / 200.0;
  up = up_tmp * position + down;
  // 'yuzhiSpeci:3' down = (max(d) - min(d)) / 200 * (position - 1) + min(d);
  down += up_tmp * (position - 1.0);
  // 'yuzhiSpeci:4' dn = sort(d);
  dn.set_size(1, d.size(1));
  loop_ub = d.size(1);
  if (static_cast<int>(d.size(1) < 1200)) {
    for (i = 0; i < loop_ub; i++) {
      dn[i] = d[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < loop_ub; i++) {
      dn[i] = d[i];
    }
  }
  coder::internal::sort(dn);
  // 'yuzhiSpeci:5' ddn = dn(dn <= up);
  loop_ub = dn.size(1) - 1;
  trueCount = 0;
  for (b_i = 0; b_i <= loop_ub; b_i++) {
    if (dn[b_i] <= up) {
      trueCount++;
    }
  }
  ddn.set_size(1, trueCount);
  partialTrueCount = 0;
  for (b_i = 0; b_i <= loop_ub; b_i++) {
    up_tmp = dn[b_i];
    if (up_tmp <= up) {
      ddn[partialTrueCount] = up_tmp;
      partialTrueCount++;
    }
  }
  // 'yuzhiSpeci:6' ddn = ddn(ddn > down);
  loop_ub = ddn.size(1) - 1;
  trueCount = 0;
  for (b_i = 0; b_i <= loop_ub; b_i++) {
    if (ddn[b_i] > down) {
      trueCount++;
    }
  }
  partialTrueCount = 0;
  for (b_i = 0; b_i <= loop_ub; b_i++) {
    if (ddn[b_i] > down) {
      ddn[partialTrueCount] = ddn[b_i];
      partialTrueCount++;
    }
  }
  ddn.set_size(1, trueCount);
  // 'yuzhiSpeci:7' [ddnn, ~] = histcounts(ddn, 20);
  coder::histcounts(ddn, ddnn_data, ddnn_size, a__1_data, a__1_size);
  // 'yuzhiSpeci:8' [~, ddmp] = max(ddnn);
  if (!std::isnan(ddnn_data[0])) {
    loop_ub = 1;
  } else {
    boolean_T exitg1;
    loop_ub = 0;
    trueCount = 2;
    exitg1 = false;
    while ((!exitg1) && (trueCount <= 20)) {
      if (!std::isnan(ddnn_data[trueCount - 1])) {
        loop_ub = trueCount;
        exitg1 = true;
      } else {
        trueCount++;
      }
    }
  }
  if (loop_ub == 0) {
    loop_ub = 1;
  } else {
    down = ddnn_data[loop_ub - 1];
    partialTrueCount = loop_ub + 1;
    for (trueCount = partialTrueCount; trueCount < 21; trueCount++) {
      up_tmp = ddnn_data[trueCount - 1];
      if (down < up_tmp) {
        down = up_tmp;
        loop_ub = trueCount;
      }
    }
  }
  // 'yuzhiSpeci:9' ddnns = sort(ddnn);
  dn.set_size(1, 20);
  for (partialTrueCount = 0; partialTrueCount < 20; partialTrueCount++) {
    dn[partialTrueCount] = ddnn_data[partialTrueCount];
  }
  coder::internal::sort(dn);
  // 'yuzhiSpeci:10' m = ddnns(end) / ddnns(end - 1);
  down = dn[dn.size(1) - 1] / dn[dn.size(1) - 2];
  // 'yuzhiSpeci:12' if ddmp > 15
  if (loop_ub > 15) {
    // 'yuzhiSpeci:13' pianyi = max(ddnns);
    pianyi = coder::internal::maximum(dn);
  } else if (down >= 20.0) {
    // 'yuzhiSpeci:14' elseif m >= 20
    // 'yuzhiSpeci:15' pianyi = (max(ddnns) - min(ddnns)) / 20 * (ddmp + 4) +
    // min(ddnns);
    down = coder::internal::minimum(dn);
    pianyi = (coder::internal::maximum(dn) - down) / 20.0 *
                 (static_cast<double>(loop_ub) + 4.0) +
             down;
  } else if (down > 10.0) {
    // 'yuzhiSpeci:16' elseif m > 10
    // 'yuzhiSpeci:17' pianyi = (max(ddnns) - min(ddnns)) / 20 * (ddmp + 5) +
    // min(ddnns);
    pianyi = (coder::internal::maximum(dn) - coder::internal::minimum(dn)) /
                 20.0 * (static_cast<double>(loop_ub) + 5.0) +
             coder::internal::minimum(dn);
  } else {
    // 'yuzhiSpeci:18' else
    // 'yuzhiSpeci:19' pianyi = max(ddnns);
    pianyi = coder::internal::maximum(dn);
  }
  return pianyi;
}

//
// File trailer for yuzhiSpeci.cpp
//
// [EOF]
//
