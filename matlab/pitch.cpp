//
// File: pitch.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "pitch.h"
#include "NCF.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
namespace coder {
void b_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
  array<double, 2U> y;
  int b_x;
  int hop;
  int i;
  int i1;
  int loop_ub;
  int numHops;
  b_x = static_cast<int>(
      std::ceil((static_cast<double>(x.size(0)) - 551.0) / 275.0));
  y.set_size(551, b_x + 1);
  numHops = 551 * (b_x + 1);
  if (static_cast<int>(numHops < 1200)) {
    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i, loop_ub, i1, hop)

  for (hop = 0; hop <= b_x; hop++) {
    i1 = 275 * hop + 1;
    i = static_cast<int>(
        std::fmin(275.0 * ((static_cast<double>(hop) + 1.0) - 1.0) + 551.0,
                  static_cast<double>(x.size(0))));
    if (i1 > i) {
      i1 = 1;
      i = 0;
    }
    loop_ub = (i - i1) + 1;
    for (i = 0; i < loop_ub; i++) {
      y[i + 551 * hop] = x[(i1 + i) - 1];
    }
  }
  audio::internal::pitch::b_NCF(y, f0);
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  }
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  }
  numHops = static_cast<int>(
      std::floor((static_cast<double>(x.size(0)) - 551.0) / 275.0));
  if (1 > numHops + 1) {
    numHops = -1;
  }
  f0.set_size(numHops + 1);
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void c_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
  array<double, 2U> y;
  int b_x;
  int hop;
  int i;
  int i1;
  int loop_ub;
  int numHops;
  b_x = static_cast<int>(
      std::ceil((static_cast<double>(x.size(0)) - 600.0) / 300.0));
  y.set_size(600, b_x + 1);
  numHops = 600 * (b_x + 1);
  if (static_cast<int>(numHops < 1200)) {
    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i, loop_ub, i1, hop)

  for (hop = 0; hop <= b_x; hop++) {
    i1 = 300 * hop + 1;
    i = static_cast<int>(
        std::fmin(300.0 * ((static_cast<double>(hop) + 1.0) - 1.0) + 600.0,
                  static_cast<double>(x.size(0))));
    if (i1 > i) {
      i1 = 1;
      i = 0;
    }
    loop_ub = (i - i1) + 1;
    for (i = 0; i < loop_ub; i++) {
      y[i + 600 * hop] = x[(i1 + i) - 1];
    }
  }
  audio::internal::pitch::c_NCF(y, f0);
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  }
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  }
  numHops = static_cast<int>(
      std::floor((static_cast<double>(x.size(0)) - 600.0) / 300.0));
  if (1 > numHops + 1) {
    numHops = -1;
  }
  f0.set_size(numHops + 1);
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void d_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
  array<double, 2U> y;
  int b_x;
  int hop;
  int i;
  int i1;
  int loop_ub;
  int numHops;
  b_x = static_cast<int>(
      std::ceil((static_cast<double>(x.size(0)) - 1103.0) / 552.0));
  y.set_size(1103, b_x + 1);
  numHops = 1103 * (b_x + 1);
  if (static_cast<int>(numHops < 1200)) {
    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i, loop_ub, i1, hop)

  for (hop = 0; hop <= b_x; hop++) {
    i1 = 552 * hop + 1;
    i = static_cast<int>(
        std::fmin(552.0 * ((static_cast<double>(hop) + 1.0) - 1.0) + 1103.0,
                  static_cast<double>(x.size(0))));
    if (i1 > i) {
      i1 = 1;
      i = 0;
    }
    loop_ub = (i - i1) + 1;
    for (i = 0; i < loop_ub; i++) {
      y[i + 1103 * hop] = x[(i1 + i) - 1];
    }
  }
  audio::internal::pitch::d_NCF(y, f0);
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  }
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  }
  numHops = static_cast<int>(
      std::floor((static_cast<double>(x.size(0)) - 1103.0) / 552.0));
  if (1 > numHops + 1) {
    numHops = -1;
  }
  f0.set_size(numHops + 1);
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void e_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
  array<double, 2U> y;
  int b_x;
  int hop;
  int i;
  int i1;
  int loop_ub;
  int numHops;
  b_x = static_cast<int>(
      std::ceil((static_cast<double>(x.size(0)) - 1200.0) / 600.0));
  y.set_size(1200, b_x + 1);
  numHops = 1200 * (b_x + 1);
  if (static_cast<int>(numHops < 1200)) {
    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i, loop_ub, i1, hop)

  for (hop = 0; hop <= b_x; hop++) {
    i1 = 600 * hop + 1;
    i = static_cast<int>(
        std::fmin(600.0 * ((static_cast<double>(hop) + 1.0) - 1.0) + 1200.0,
                  static_cast<double>(x.size(0))));
    if (i1 > i) {
      i1 = 1;
      i = 0;
    }
    loop_ub = (i - i1) + 1;
    for (i = 0; i < loop_ub; i++) {
      y[i + 1200 * hop] = x[(i1 + i) - 1];
    }
  }
  audio::internal::pitch::e_NCF(y, f0);
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  }
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  }
  numHops = static_cast<int>(
      std::floor((static_cast<double>(x.size(0)) - 1200.0) / 600.0));
  if (1 > numHops + 1) {
    numHops = -1;
  }
  f0.set_size(numHops + 1);
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void f_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
  array<double, 2U> y;
  int b_x;
  int hop;
  int i;
  int i1;
  int loop_ub;
  int numHops;
  b_x = static_cast<int>(
      std::ceil((static_cast<double>(x.size(0)) - 2205.0) / 1102.0));
  y.set_size(2205, b_x + 1);
  numHops = 2205 * (b_x + 1);
  if (static_cast<int>(numHops < 1200)) {
    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i, loop_ub, i1, hop)

  for (hop = 0; hop <= b_x; hop++) {
    i1 = 1102 * hop + 1;
    i = static_cast<int>(
        std::fmin(1102.0 * ((static_cast<double>(hop) + 1.0) - 1.0) + 2205.0,
                  static_cast<double>(x.size(0))));
    if (i1 > i) {
      i1 = 1;
      i = 0;
    }
    loop_ub = (i - i1) + 1;
    for (i = 0; i < loop_ub; i++) {
      y[i + 2205 * hop] = x[(i1 + i) - 1];
    }
  }
  audio::internal::pitch::f_NCF(y, f0);
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  }
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  }
  numHops = static_cast<int>(
      std::floor((static_cast<double>(x.size(0)) - 2205.0) / 1102.0));
  if (1 > numHops + 1) {
    numHops = -1;
  }
  f0.set_size(numHops + 1);
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void g_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
  array<double, 2U> y;
  int b_x;
  int hop;
  int i;
  int i1;
  int loop_ub;
  int numHops;
  b_x = static_cast<int>(
      std::ceil((static_cast<double>(x.size(0)) - 2400.0) / 1200.0));
  y.set_size(2400, b_x + 1);
  numHops = 2400 * (b_x + 1);
  if (static_cast<int>(numHops < 1200)) {
    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i, loop_ub, i1, hop)

  for (hop = 0; hop <= b_x; hop++) {
    i1 = 1200 * hop + 1;
    i = static_cast<int>(
        std::fmin(1200.0 * ((static_cast<double>(hop) + 1.0) - 1.0) + 2400.0,
                  static_cast<double>(x.size(0))));
    if (i1 > i) {
      i1 = 1;
      i = 0;
    }
    loop_ub = (i - i1) + 1;
    for (i = 0; i < loop_ub; i++) {
      y[i + 2400 * hop] = x[(i1 + i) - 1];
    }
  }
  audio::internal::pitch::g_NCF(y, f0);
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  }
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  }
  numHops = static_cast<int>(
      std::floor((static_cast<double>(x.size(0)) - 2400.0) / 1200.0));
  if (1 > numHops + 1) {
    numHops = -1;
  }
  f0.set_size(numHops + 1);
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void pitch(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &f0)
{
  array<double, 2U> y;
  int b_x;
  int hop;
  int i;
  int i1;
  int loop_ub;
  int numHops;
  b_x = static_cast<int>(
      std::ceil((static_cast<double>(x.size(0)) - 400.0) / 200.0));
  y.set_size(400, b_x + 1);
  numHops = 400 * (b_x + 1);
  if (static_cast<int>(numHops < 1200)) {
    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < numHops; i++) {
      y[i] = 0.0;
    }
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i, loop_ub, i1, hop)

  for (hop = 0; hop <= b_x; hop++) {
    i1 = 200 * hop + 1;
    i = static_cast<int>(
        std::fmin(200.0 * ((static_cast<double>(hop) + 1.0) - 1.0) + 400.0,
                  static_cast<double>(x.size(0))));
    if (i1 > i) {
      i1 = 1;
      i = 0;
    }
    loop_ub = (i - i1) + 1;
    for (i = 0; i < loop_ub; i++) {
      y[i + 400 * hop] = x[(i1 + i) - 1];
    }
  }
  audio::internal::pitch::NCF(y, f0);
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] < 50.0) {
        f0[hop] = 50.0;
      }
    }
  }
  numHops = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(hop)

    for (hop = 0; hop < numHops; hop++) {
      if (f0[hop] > 400.0) {
        f0[hop] = 400.0;
      }
    }
  }
  numHops = static_cast<int>(
      std::floor((static_cast<double>(x.size(0)) - 400.0) / 200.0));
  if (1 > numHops + 1) {
    numHops = -1;
  }
  f0.set_size(numHops + 1);
}

} // namespace coder

//
// File trailer for pitch.cpp
//
// [EOF]
//
