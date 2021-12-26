//
// File: histcounts.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "histcounts.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                double n_data[]
//                int n_size[2]
//                double edges_data[]
//                int edges_size[2]
// Return Type  : void
//
namespace coder {
void histcounts(const ::coder::array<double, 2U> &x, double n_data[],
                int n_size[2], double edges_data[], int edges_size[2])
{
  double HighLimit;
  double LowLimit;
  double RawBinWidth_tmp;
  double epsxScale;
  double leftEdge;
  double xScale;
  int ni_data[20];
  int high_i;
  int i;
  int k;
  int low_i;
  int low_ip1;
  int mid_i;
  int nx;
  nx = x.size(1);
  k = 0;
  while ((k + 1 <= nx) && (std::isinf(x[k]) || std::isnan(x[k]))) {
    k++;
  }
  if (k + 1 > x.size(1)) {
    LowLimit = 0.0;
    low_i = 0;
  } else {
    LowLimit = x[k];
    low_i = 1;
  }
  HighLimit = LowLimit;
  i = k + 2;
  for (low_ip1 = i; low_ip1 <= nx; low_ip1++) {
    RawBinWidth_tmp = x[low_ip1 - 1];
    if ((!std::isinf(RawBinWidth_tmp)) && (!std::isnan(RawBinWidth_tmp))) {
      if (RawBinWidth_tmp < LowLimit) {
        LowLimit = RawBinWidth_tmp;
      } else if (RawBinWidth_tmp > HighLimit) {
        HighLimit = RawBinWidth_tmp;
      }
      low_i++;
    }
  }
  if (low_i > 0) {
    boolean_T b;
    boolean_T b1;
    xScale = std::fmax(std::abs(LowLimit), std::abs(HighLimit));
    b = !std::isinf(xScale);
    b1 = !std::isnan(xScale);
    if (b && b1) {
      if (xScale <= 2.2250738585072014E-308) {
        epsxScale = 4.94065645841247E-324;
      } else {
        frexp(xScale, &high_i);
        epsxScale = std::ldexp(1.0, high_i - 53);
      }
    } else {
      epsxScale = rtNaN;
    }
    RawBinWidth_tmp = HighLimit - LowLimit;
    leftEdge = std::fmax(RawBinWidth_tmp / 20.0, epsxScale);
    if (RawBinWidth_tmp >
        std::fmax(std::sqrt(epsxScale), 2.2250738585072014E-308)) {
      xScale = rt_powd_snf(10.0, std::floor(std::log10(leftEdge)));
      epsxScale = xScale * std::floor(leftEdge / xScale);
      leftEdge = std::fmax(
          std::fmin(epsxScale * std::floor(LowLimit / epsxScale), LowLimit),
          -1.7976931348623157E+308);
      xScale = (HighLimit - leftEdge) / 20.0;
      epsxScale = rt_powd_snf(
          10.0, std::floor(std::log10((HighLimit - leftEdge) / 19.0 - xScale)));
      epsxScale *= std::ceil(xScale / epsxScale);
      xScale = std::fmin(std::fmax(leftEdge + 20.0 * epsxScale, HighLimit),
                         1.7976931348623157E+308);
    } else {
      if (b && b1) {
        if (xScale <= 2.2250738585072014E-308) {
          xScale = 4.94065645841247E-324;
        } else {
          frexp(xScale, &mid_i);
          xScale = std::ldexp(1.0, mid_i - 53);
        }
      } else {
        xScale = rtNaN;
      }
      xScale = std::fmax(1.0, std::ceil(20.0 * xScale));
      leftEdge = std::floor(2.0 * (LowLimit - xScale / 4.0)) / 2.0;
      xScale = std::ceil(2.0 * (HighLimit + xScale / 4.0)) / 2.0;
      epsxScale = (xScale - leftEdge) / 20.0;
    }
    if ((!std::isinf(epsxScale)) && (!std::isnan(epsxScale))) {
      edges_size[0] = 1;
      edges_size[1] = 21;
      std::memset(&edges_data[0], 0, 21U * sizeof(double));
      edges_data[0] = leftEdge;
      for (low_i = 0; low_i < 19; low_i++) {
        edges_data[low_i + 1] =
            leftEdge + (static_cast<double>(low_i) + 1.0) * epsxScale;
      }
      edges_data[20] = xScale;
    } else {
      edges_size[0] = 1;
      edges_size[1] = 21;
      edges_data[20] = xScale;
      edges_data[0] = leftEdge;
      if (leftEdge == -xScale) {
        xScale /= 20.0;
        for (k = 0; k < 19; k++) {
          edges_data[k + 1] =
              (2.0 * (static_cast<double>(k) + 2.0) - 22.0) * xScale;
        }
        edges_data[10] = 0.0;
      } else if (((leftEdge < 0.0) != (xScale < 0.0)) &&
                 ((std::abs(leftEdge) > 8.9884656743115785E+307) ||
                  (std::abs(xScale) > 8.9884656743115785E+307))) {
        epsxScale = leftEdge / 20.0;
        xScale /= 20.0;
        for (k = 0; k < 19; k++) {
          edges_data[k + 1] =
              (leftEdge + xScale * (static_cast<double>(k) + 1.0)) -
              epsxScale * (static_cast<double>(k) + 1.0);
        }
      } else {
        epsxScale = (xScale - leftEdge) / 20.0;
        for (k = 0; k < 19; k++) {
          edges_data[k + 1] =
              leftEdge + (static_cast<double>(k) + 1.0) * epsxScale;
        }
      }
    }
  } else {
    edges_size[0] = 1;
    edges_size[1] = 21;
    for (k = 0; k < 21; k++) {
      edges_data[k] = k;
    }
  }
  std::memset(&ni_data[0], 0, 20U * sizeof(int));
  nx = x.size(1);
  leftEdge = edges_data[0];
  xScale = edges_data[1] - edges_data[0];
  for (k = 0; k < nx; k++) {
    RawBinWidth_tmp = x[k];
    if ((RawBinWidth_tmp >= leftEdge) && (RawBinWidth_tmp <= edges_data[20])) {
      boolean_T guard1{false};
      epsxScale = std::ceil((RawBinWidth_tmp - leftEdge) / xScale);
      guard1 = false;
      if ((epsxScale >= 1.0) && (epsxScale < 21.0)) {
        i = static_cast<int>(epsxScale);
        if ((RawBinWidth_tmp >= edges_data[i - 1]) &&
            (RawBinWidth_tmp < edges_data[i])) {
          ni_data[i - 1]++;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        low_i = 1;
        low_ip1 = 2;
        high_i = 21;
        while (high_i > low_ip1) {
          mid_i = (low_i >> 1) + (high_i >> 1);
          if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
            mid_i++;
          }
          if (x[k] >= edges_data[mid_i - 1]) {
            low_i = mid_i;
            low_ip1 = mid_i + 1;
          } else {
            high_i = mid_i;
          }
        }
        ni_data[low_i - 1]++;
      }
    }
  }
  n_size[0] = 1;
  n_size[1] = 20;
  for (i = 0; i < 20; i++) {
    n_data[i] = ni_data[i];
  }
}

} // namespace coder

//
// File trailer for histcounts.cpp
//
// [EOF]
//
