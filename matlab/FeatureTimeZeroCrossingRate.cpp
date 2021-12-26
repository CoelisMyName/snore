//
// File: FeatureTimeZeroCrossingRate.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "FeatureTimeZeroCrossingRate.h"
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [vzc, t] = FeatureTimeZeroCrossingRate(x, iBlockLength, iHopLength,
// f_s)
//
// number of results
//
// Arguments    : const coder::array<double, 1U> &x
//                double iBlockLength
//                double iHopLength
//                double f_s
//                coder::array<double, 2U> &vzc
//                coder::array<double, 2U> &t
// Return Type  : void
//
void FeatureTimeZeroCrossingRate(const coder::array<double, 1U> &x,
                                 double iBlockLength, double iHopLength,
                                 double f_s, coder::array<double, 2U> &vzc,
                                 coder::array<double, 2U> &t)
{
  coder::array<double, 1U> b_x;
  coder::array<double, 1U> b_y1;
  double b_iBlockLength;
  double iNumOfBlocks;
  double i_stop;
  double tmp1;
  double work_data;
  int dimSize;
  int k;
  int loop_ub;
  int loop_ub_tmp;
  int n;
  int nx;
  //  ======================================================================
  // > @brief computes the zero crossing rate from a time domain signal
  // > called by ::ComputeFeature
  // >
  // > @param x: audio signal
  // > @param iBlockLength: block length in samples
  // > @param iHopLength: hop length in samples
  // > @param f_s: sample rate of audio data (unused)
  // >
  // > @retval vzc zero crossing rate
  // > @retval t time stamp
  //  ======================================================================
  // 'FeatureTimeZeroCrossingRate:16' iNumOfBlocks = ceil (length(x) /
  // iHopLength);
  iNumOfBlocks = std::ceil(static_cast<double>(x.size(0)) / iHopLength);
  //  compute time stamps
  // 'FeatureTimeZeroCrossingRate:19' t = ((0:iNumOfBlocks - 1) * iHopLength +
  // (iBlockLength / 2)) / f_s;
  if (std::isnan(iNumOfBlocks - 1.0)) {
    t.set_size(1, 1);
    t[0] = rtNaN;
  } else if (iNumOfBlocks - 1.0 < 0.0) {
    t.set_size(t.size(0), 0);
  } else if (std::isinf(iNumOfBlocks - 1.0) && (0.0 == iNumOfBlocks - 1.0)) {
    t.set_size(1, 1);
    t[0] = rtNaN;
  } else {
    t.set_size(1, static_cast<int>(iNumOfBlocks - 1.0) + 1);
    loop_ub = static_cast<int>(iNumOfBlocks - 1.0);
    if (static_cast<int>(static_cast<int>(iNumOfBlocks - 1.0) + 1 < 1200)) {
      for (k = 0; k <= loop_ub; k++) {
        t[k] = k;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = 0; k <= loop_ub; k++) {
        t[k] = k;
      }
    }
  }
  t.set_size(1, t.size(1));
  b_iBlockLength = iBlockLength / 2.0;
  loop_ub_tmp = t.size(1) - 1;
  loop_ub = t.size(1) - 1;
  if (static_cast<int>(t.size(1) < 1200)) {
    for (k = 0; k <= loop_ub_tmp; k++) {
      t[k] = (t[k] * iHopLength + b_iBlockLength) / f_s;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= loop_ub; k++) {
      t[k] = (t[k] * iHopLength + b_iBlockLength) / f_s;
    }
  }
  //  allocate memory
  // 'FeatureTimeZeroCrossingRate:22' vzc = zeros(1, iNumOfBlocks);
  vzc.set_size(1, static_cast<int>(iNumOfBlocks));
  // 'FeatureTimeZeroCrossingRate:24' for (n = 1:iNumOfBlocks
  loop_ub = static_cast<int>(iNumOfBlocks);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    b_x, b_y1, k, i_stop, nx, tmp1, work_data, dimSize, n)

  for (n = 0; n < loop_ub; n++) {
    // 'FeatureTimeZeroCrossingRate:25' i_start = (n - 1) * iHopLength + 1;
    tmp1 = ((static_cast<double>(n) + 1.0) - 1.0) * iHopLength + 1.0;
    // 'FeatureTimeZeroCrossingRate:26' i_stop = min(length(x), i_start +
    // iBlockLength - 1);
    i_stop =
        std::fmin(static_cast<double>(x.size(0)), (tmp1 + iBlockLength) - 1.0);
    //  compute the zero crossing rate
    // 'FeatureTimeZeroCrossingRate:29' vzc(n) = 0.5 *
    // mean(abs(diff(sign(x(i_start:i_stop)))));
    if (tmp1 > i_stop) {
      nx = 1;
      k = 0;
    } else {
      nx = static_cast<int>(tmp1);
      k = static_cast<int>(i_stop);
    }
    dimSize = k - nx;
    b_x.set_size(dimSize + 1);
    for (k = 0; k <= dimSize; k++) {
      b_x[k] = x[(nx + k) - 1];
    }
    for (k = 0; k <= dimSize; k++) {
      i_stop = b_x[k];
      if (b_x[k] < 0.0) {
        i_stop = -1.0;
      } else if (b_x[k] > 0.0) {
        i_stop = 1.0;
      } else if (b_x[k] == 0.0) {
        i_stop = 0.0;
      }
      b_x[k] = i_stop;
    }
    dimSize = b_x.size(0);
    if (b_x.size(0) == 0) {
      b_y1.set_size(0);
    } else {
      nx = b_x.size(0) - 1;
      if (nx >= 1) {
        nx = 1;
      }
      if (nx < 1) {
        b_y1.set_size(0);
      } else {
        b_y1.set_size(b_x.size(0) - 1);
        if (b_x.size(0) - 1 != 0) {
          work_data = b_x[0];
          for (nx = 2; nx <= dimSize; nx++) {
            tmp1 = b_x[nx - 1];
            i_stop = tmp1;
            tmp1 -= work_data;
            work_data = i_stop;
            b_y1[nx - 2] = tmp1;
          }
        }
      }
    }
    nx = b_y1.size(0);
    b_x.set_size(b_y1.size(0));
    for (k = 0; k < nx; k++) {
      b_x[k] = std::abs(b_y1[k]);
    }
    vzc[n] = 0.5 * (coder::blockedSummation(b_x, b_x.size(0)) /
                    static_cast<double>(b_x.size(0)));
  }
}

//
// File trailer for FeatureTimeZeroCrossingRate.cpp
//
// [EOF]
//
