//
// File: getCandidates.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "getCandidates.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &domain
//                const double edge[2]
//                ::coder::array<double, 1U> &peaks
//                ::coder::array<double, 1U> &locs
// Return Type  : void
//
namespace coder {
namespace audio {
namespace internal {
namespace pitch {
void getCandidates(::coder::array<double, 2U> &domain, const double edge[2],
                   ::coder::array<double, 1U> &peaks,
                   ::coder::array<double, 1U> &locs)
{
  array<double, 2U> b_y;
  array<double, 2U> y;
  double varargin_1_data[941];
  double lower;
  int tmp_data[941];
  int i;
  int i1;
  int loop_ub;
  locs.set_size(domain.size(1));
  loop_ub = domain.size(1);
  if (static_cast<int>(domain.size(1) < 1200)) {
    for (i = 0; i < loop_ub; i++) {
      locs[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < loop_ub; i++) {
      locs[i] = 0.0;
    }
  }
  peaks.set_size(domain.size(1));
  loop_ub = domain.size(1);
  if (static_cast<int>(domain.size(1) < 1200)) {
    for (i = 0; i < loop_ub; i++) {
      peaks[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < loop_ub; i++) {
      peaks[i] = 0.0;
    }
  }
  if (std::isnan(edge[0]) || std::isnan(edge[1])) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else if (edge[1] < edge[0]) {
    y.set_size(1, 0);
  } else if ((std::isinf(edge[0]) || std::isinf(edge[1])) &&
             (edge[0] == edge[1])) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else if (std::floor(edge[0]) == edge[0]) {
    loop_ub = static_cast<int>(std::floor(edge[1] - edge[0]));
    y.set_size(1, loop_ub + 1);
    if (static_cast<int>(loop_ub + 1 < 1200)) {
      for (i = 0; i <= loop_ub; i++) {
        y[i] = edge[0] + static_cast<double>(i);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i <= loop_ub; i++) {
        y[i] = edge[0] + static_cast<double>(i);
      }
    }
  } else {
    eml_float_colon(edge[0], edge[1], y);
  }
  lower = edge[0];
  i1 = domain.size(1);
  for (int c{0}; c < i1; c++) {
    double b;
    double ex;
    int i2;
    int idx;
    int last;
    loop_ub = y.size(1);
    for (i2 = 0; i2 < loop_ub; i2++) {
      varargin_1_data[i2] =
          domain[(static_cast<int>(y[i2]) + domain.size(0) * c) - 1];
    }
    last = y.size(1);
    if (y.size(1) <= 2) {
      if (y.size(1) == 1) {
        peaks[c] = domain[(static_cast<int>(y[0]) + domain.size(0) * c) - 1];
        idx = 1;
      } else {
        b = domain[(static_cast<int>(y[0]) + domain.size(0) * c) - 1];
        if ((b <
             domain[(static_cast<int>(y[y.size(1) - 1]) + domain.size(0) * c) -
                    1]) ||
            (std::isnan(b) &&
             (!std::isnan(domain[(static_cast<int>(y[y.size(1) - 1]) +
                                  domain.size(0) * c) -
                                 1])))) {
          peaks[c] =
              domain[(static_cast<int>(y[y.size(1) - 1]) + domain.size(0) * c) -
                     1];
          idx = y.size(1);
        } else {
          peaks[c] = b;
          idx = 1;
        }
      }
    } else {
      if (!std::isnan(varargin_1_data[0])) {
        idx = 1;
      } else {
        boolean_T exitg1;
        idx = 0;
        loop_ub = 2;
        exitg1 = false;
        while ((!exitg1) && (loop_ub <= last)) {
          if (!std::isnan(varargin_1_data[loop_ub - 1])) {
            idx = loop_ub;
            exitg1 = true;
          } else {
            loop_ub++;
          }
        }
      }
      if (idx == 0) {
        peaks[c] = domain[(static_cast<int>(y[0]) + domain.size(0) * c) - 1];
        idx = 1;
      } else {
        ex = varargin_1_data[idx - 1];
        i2 = idx + 1;
        for (loop_ub = i2; loop_ub <= last; loop_ub++) {
          b = varargin_1_data[loop_ub - 1];
          if (ex < b) {
            ex = b;
            idx = loop_ub;
          }
        }
        peaks[c] = ex;
      }
    }
    ex = std::fmax((static_cast<double>(idx) - 1.0) + lower, lower);
    b = std::fmin((static_cast<double>(idx) + 1.0) + lower, edge[1]);
    if (std::isnan(ex) || std::isnan(b)) {
      b_y.set_size(1, 1);
      b_y[0] = rtNaN;
    } else if (b < ex) {
      b_y.set_size(1, 0);
    } else if ((std::isinf(ex) || std::isinf(b)) && (ex == b)) {
      b_y.set_size(1, 1);
      b_y[0] = rtNaN;
    } else if (std::floor(ex) == ex) {
      loop_ub = static_cast<int>(std::floor(b - ex));
      b_y.set_size(1, loop_ub + 1);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        b_y[i2] = ex + static_cast<double>(i2);
      }
    } else {
      eml_float_colon(ex, b, b_y);
    }
    last = b_y.size(1);
    loop_ub = b_y.size(1);
    for (i2 = 0; i2 < loop_ub; i2++) {
      tmp_data[i2] = static_cast<int>(b_y[i2]);
    }
    for (i2 = 0; i2 < last; i2++) {
      domain[(tmp_data[i2] + domain.size(0) * c) - 1] = rtNaN;
    }
    locs[c] = (lower + static_cast<double>(idx)) - 1.0;
  }
}

} // namespace pitch
} // namespace internal
} // namespace audio
} // namespace coder

//
// File trailer for getCandidates.cpp
//
// [EOF]
//
