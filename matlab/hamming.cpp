//
// File: hamming.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "hamming.h"
#include "SnoringRecognition_rtwutil.h"
#include "gencoswin.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double varargin_1
//                ::coder::array<double, 1U> &w
// Return Type  : void
//
namespace coder {
void hamming(double varargin_1, ::coder::array<double, 1U> &w)
{
  array<double, 1U> b_w;
  double L;
  int i;
  int i1;
  int trivialwin;
  int w_size;
  signed char w_data;
  w_size = 1;
  w_data = 0;
  trivialwin = 0;
  if (varargin_1 == std::floor(varargin_1)) {
    L = varargin_1;
  } else {
    L = std::round(varargin_1);
  }
  if (L == 0.0) {
    w_size = 0;
    trivialwin = 1;
  } else if (L == 1.0) {
    w_data = 1;
    trivialwin = 1;
  }
  w.set_size(w_size);
  for (i = 0; i < w_size; i++) {
    w[0] = w_data;
  }
  if (trivialwin == 0) {
    if (iseven(L)) {
      int loop_ub;
      calc_window(L / 2.0, L, w);
      if (1 > w.size(0)) {
        i = 0;
        w_size = 1;
        trivialwin = -1;
      } else {
        i = w.size(0) - 1;
        w_size = -1;
        trivialwin = 0;
      }
      b_w.set_size((w.size(0) + div_s32_floor(trivialwin - i, w_size)) + 1);
      loop_ub = w.size(0);
      if (static_cast<int>(w.size(0) < 1200)) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_w[i1] = w[i1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

        for (i1 = 0; i1 < loop_ub; i1++) {
          b_w[i1] = w[i1];
        }
      }
      loop_ub = div_s32_floor(trivialwin - i, w_size);
      if (static_cast<int>(loop_ub + 1 < 1200)) {
        for (i1 = 0; i1 <= loop_ub; i1++) {
          b_w[i1 + w.size(0)] = w[i + w_size * i1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

        for (i1 = 0; i1 <= loop_ub; i1++) {
          b_w[i1 + w.size(0)] = w[i + w_size * i1];
        }
      }
      w.set_size(b_w.size(0));
      loop_ub = b_w.size(0);
      if (static_cast<int>(b_w.size(0) < 1200)) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          w[i1] = b_w[i1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

        for (i1 = 0; i1 < loop_ub; i1++) {
          w[i1] = b_w[i1];
        }
      }
    } else {
      int loop_ub;
      calc_window((L + 1.0) / 2.0, L, w);
      if (1 > w.size(0) - 1) {
        i = 0;
        w_size = 1;
        trivialwin = -1;
      } else {
        i = w.size(0) - 2;
        w_size = -1;
        trivialwin = 0;
      }
      b_w.set_size((w.size(0) + div_s32_floor(trivialwin - i, w_size)) + 1);
      loop_ub = w.size(0);
      if (static_cast<int>(w.size(0) < 1200)) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_w[i1] = w[i1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

        for (i1 = 0; i1 < loop_ub; i1++) {
          b_w[i1] = w[i1];
        }
      }
      loop_ub = div_s32_floor(trivialwin - i, w_size);
      if (static_cast<int>(loop_ub + 1 < 1200)) {
        for (i1 = 0; i1 <= loop_ub; i1++) {
          b_w[i1 + w.size(0)] = w[i + w_size * i1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

        for (i1 = 0; i1 <= loop_ub; i1++) {
          b_w[i1 + w.size(0)] = w[i + w_size * i1];
        }
      }
      w.set_size(b_w.size(0));
      loop_ub = b_w.size(0);
      if (static_cast<int>(b_w.size(0) < 1200)) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          w[i1] = b_w[i1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1)

        for (i1 = 0; i1 < loop_ub; i1++) {
          w[i1] = b_w[i1];
        }
      }
    }
  }
}

} // namespace coder

//
// File trailer for hamming.cpp
//
// [EOF]
//
