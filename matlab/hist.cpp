//
// File: hist.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "hist.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &Y
//                double no[200]
//                double xo[200]
// Return Type  : void
//
namespace coder {
void hist(const ::coder::array<double, 2U> &Y, double no[200], double xo[200])
{
  double edges[201];
  double nn[201];
  int low_ip1;
  if (Y.size(1) == 0) {
    for (int i{0}; i < 200; i++) {
      xo[i] = static_cast<double>(i) + 1.0;
      no[i] = 0.0;
    }
  } else {
    double delta2;
    double miny;
    int i;
    int k;
    int ny;
    ny = Y.size(1);
    k = 0;
    while ((k + 1 <= ny) && (std::isinf(Y[k]) || std::isnan(Y[k]))) {
      k++;
    }
    if (k + 1 > Y.size(1)) {
      miny = 0.0;
      delta2 = 0.0;
    } else {
      miny = Y[k];
      delta2 = Y[k];
      while (k + 1 <= ny) {
        if ((!std::isinf(Y[k])) && (!std::isnan(Y[k]))) {
          if (Y[k] < miny) {
            miny = Y[k];
          }
          if (Y[k] > delta2) {
            delta2 = Y[k];
          }
        }
        k++;
      }
    }
    if (miny == delta2) {
      miny = (miny - 100.0) - 0.5;
      delta2 = (delta2 + 100.0) - 0.5;
    }
    edges[200] = delta2;
    edges[0] = miny;
    if (miny == -delta2) {
      delta2 /= 200.0;
      for (k = 0; k < 199; k++) {
        edges[k + 1] = (2.0 * (static_cast<double>(k) + 2.0) - 202.0) * delta2;
      }
      edges[100] = 0.0;
    } else if (((miny < 0.0) != (delta2 < 0.0)) &&
               ((std::abs(miny) > 8.9884656743115785E+307) ||
                (std::abs(delta2) > 8.9884656743115785E+307))) {
      double delta1;
      delta1 = miny / 200.0;
      delta2 /= 200.0;
      for (k = 0; k < 199; k++) {
        edges[k + 1] = (miny + delta2 * (static_cast<double>(k) + 1.0)) -
                       delta1 * (static_cast<double>(k) + 1.0);
      }
    } else {
      double delta1;
      delta1 = (delta2 - miny) / 200.0;
      for (k = 0; k < 199; k++) {
        edges[k + 1] = miny + (static_cast<double>(k) + 1.0) * delta1;
      }
    }
    delta2 = (edges[1] - edges[0]) / 2.0;
    for (i = 0; i < 200; i++) {
      xo[i] = edges[i] + delta2;
    }
    edges[0] = rtMinusInf;
    edges[200] = rtInf;
    for (k = 0; k < 199; k++) {
      miny = edges[k + 1];
      delta2 = std::abs(miny);
      if ((!std::isinf(delta2)) && (!std::isnan(delta2))) {
        if (delta2 <= 2.2250738585072014E-308) {
          delta2 = 4.94065645841247E-324;
        } else {
          frexp(delta2, &low_ip1);
          delta2 = std::ldexp(1.0, low_ip1 - 53);
        }
      } else {
        delta2 = rtNaN;
      }
      edges[k + 1] = miny + delta2;
    }
    std::memset(&nn[0], 0, 201U * sizeof(double));
    i = Y.size(1);
    for (k = 0; k < i; k++) {
      ny = 0;
      delta2 = Y[k];
      if (!std::isnan(delta2)) {
        if ((delta2 >= edges[0]) && (delta2 < edges[200])) {
          int high_i;
          ny = 1;
          low_ip1 = 2;
          high_i = 201;
          while (high_i > low_ip1) {
            int mid_i;
            mid_i = (ny + high_i) >> 1;
            if (Y[k] >= edges[mid_i - 1]) {
              ny = mid_i;
              low_ip1 = mid_i + 1;
            } else {
              high_i = mid_i;
            }
          }
        }
        if (Y[k] == edges[200]) {
          ny = 201;
        }
      }
      if (ny > 0) {
        nn[ny - 1]++;
      }
    }
    std::copy(&nn[0], &nn[200], &no[0]);
    no[199] += nn[200];
  }
}

} // namespace coder

//
// File trailer for hist.cpp
//
// [EOF]
//
