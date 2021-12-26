//
// File: gencoswin.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "gencoswin.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double m
//                double n
//                ::coder::array<double, 1U> &w
// Return Type  : void
//
namespace coder {
void calc_window(double m, double n, ::coder::array<double, 1U> &w)
{
  array<double, 2U> y;
  double b_n;
  int k;
  int nx;
  if (std::isnan(m - 1.0)) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y.set_size(1, 0);
  } else if (std::isinf(m - 1.0) && (0.0 == m - 1.0)) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else {
    nx = static_cast<int>(std::floor(m - 1.0));
    y.set_size(1, nx + 1);
    if (static_cast<int>(nx + 1 < 1200)) {
      for (k = 0; k <= nx; k++) {
        y[k] = k;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = 0; k <= nx; k++) {
        y[k] = k;
      }
    }
  }
  b_n = n - 1.0;
  w.set_size(y.size(1));
  nx = y.size(1);
  if (static_cast<int>(y.size(1) < 1200)) {
    for (k = 0; k < nx; k++) {
      w[k] = 6.2831853071795862 * (y[k] / (n - 1.0));
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      w[k] = 6.2831853071795862 * (y[k] / b_n);
    }
  }
  nx = w.size(0);
  if (static_cast<int>(w.size(0) < 1200)) {
    for (k = 0; k < nx; k++) {
      w[k] = std::cos(w[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      w[k] = std::cos(w[k]);
    }
  }
  nx = w.size(0);
  if (static_cast<int>(w.size(0) < 1200)) {
    for (k = 0; k < nx; k++) {
      w[k] = 0.54 - 0.46 * w[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      w[k] = 0.54 - 0.46 * w[k];
    }
  }
}

} // namespace coder

//
// File trailer for gencoswin.cpp
//
// [EOF]
//
