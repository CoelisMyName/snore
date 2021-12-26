//
// File: NCF.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "NCF.h"
#include "SnoringRecognition_rtwutil.h"
#include "fft.h"
#include "getCandidates.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &y
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
namespace coder {
namespace audio {
namespace internal {
namespace pitch {
void NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
  array<creal_T, 2U> x;
  array<double, 2U> Rt;
  array<double, 2U> b_c1;
  array<double, 2U> b_x;
  array<double, 2U> b_y;
  array<double, 2U> c1;
  array<double, 2U> c_y;
  array<double, 2U> lag;
  array<double, 1U> peak;
  double edge[2];
  int input_sizes[2];
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int ncols;
  int nx;
  short sizes_idx_0;
  unsigned char input_sizes_idx_0;
  boolean_T empty_non_axis_sizes;
  edge[0] = 20.0;
  edge[1] = 160.0;
  fft(y, x);
  nx = x.size(1) << 10;
  c1.set_size(1024, x.size(1));
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  }
  b_y.set_size(1024, c1.size(1));
  nx = c1.size(1) << 10;
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  }
  ifft(b_y, x);
  c1.set_size(1024, x.size(1));
  ncols = 1024 * x.size(1);
  if (static_cast<int>(ncols < 1200)) {
    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 32.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 32.0;
    }
  }
  c_y.set_size(1, 160);
  for (i1 = 0; i1 < 160; i1++) {
    c_y[i1] = static_cast<double>(i1) + 1.0;
  }
  lag.set_size(160, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 160; i2++) {
      lag[i2 + lag.size(0) * i] =
          c1[(static_cast<int>(c_y[i2] + 864.0) + 1024 * i) - 1];
    }
  }
  if (c1.size(1) != 0) {
    nx = c1.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    input_sizes_idx_0 = 160U;
  } else {
    input_sizes_idx_0 = 0U;
  }
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    sizes_idx_0 = 161;
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  input_sizes[1] = nx;
  b_c1.set_size(161, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 161; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = c1[i2 + 1024 * i];
    }
  }
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  Rt.set_size(input_sizes[0] + sizes_idx_0, input_sizes[1]);
  ncols = input_sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[i2 + Rt.size(0) * i] = lag[i2 + input_sizes[0] * i];
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[(i2 + input_sizes[0]) + Rt.size(0) * i] = b_c1[i2 + sizes[0] * i];
    }
  }
  if (181 > Rt.size(0)) {
    i1 = -1;
    i3 = -1;
  } else {
    i1 = 179;
    i3 = Rt.size(0) - 1;
  }
  ncols = Rt.size(1);
  b_x.set_size(1, Rt.size(1));
  nx = Rt.size(1);
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (i = 0; i < ncols; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 160];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 160];
    }
  }
  nx = Rt.size(1) - 1;
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  }
  nx = i3 - i1;
  lag.set_size(nx, b_x.size(1));
  ncols = b_x.size(1);
  for (int jcol{0}; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * nx;
    for (int itilerow{0}; itilerow < nx; itilerow++) {
      lag[ibmat + itilerow] = b_x[jcol];
    }
  }
  lag.set_size(nx, Rt.size(1));
  ncols = Rt.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i, k)

  for (i = 0; i < ncols; i++) {
    k = i3 - i1;
    for (i2 = 0; i2 < k; i2++) {
      lag[i2 + lag.size(0) * i] =
          Rt[((i1 + i2) + Rt.size(0) * i) + 1] / lag[i2 + lag.size(0) * i];
    }
  }
  if (lag.size(1) != 0) {
    nx = lag.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (lag.size(1) != 0)) {
    input_sizes_idx_0 = 19U;
  } else {
    input_sizes_idx_0 = 0U;
  }
  if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
    sizes_idx_0 = static_cast<short>(lag.size(0));
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  b_c1.set_size(input_sizes_idx_0 + sizes_idx_0, nx);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < nx; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = 0.0;
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[(i2 + input_sizes[0]) + b_c1.size(0) * i] = lag[i2 + sizes[0] * i];
    }
  }
  getCandidates(b_c1, edge, peak, f0);
  ncols = f0.size(0);
  if (static_cast<int>(f0.size(0) < 1200)) {
    for (i = 0; i < ncols; i++) {
      f0[i] = 8000.0 / f0[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      f0[i] = 8000.0 / f0[i];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &y
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void b_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
  array<creal_T, 2U> x;
  array<double, 2U> Rt;
  array<double, 2U> b_c1;
  array<double, 2U> b_x;
  array<double, 2U> b_y;
  array<double, 2U> c1;
  array<double, 2U> c_y;
  array<double, 2U> lag;
  array<double, 1U> locs;
  array<double, 1U> peak;
  double edge[2];
  int input_sizes[2];
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int ncols;
  int nx;
  short sizes_idx_0;
  unsigned char input_sizes_idx_0;
  boolean_T empty_non_axis_sizes;
  edge[0] = 28.0;
  edge[1] = 221.0;
  b_fft(y, x);
  nx = x.size(1) << 11;
  c1.set_size(2048, x.size(1));
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  }
  b_y.set_size(2048, c1.size(1));
  nx = c1.size(1) << 11;
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  }
  b_ifft(b_y, x);
  c1.set_size(2048, x.size(1));
  ncols = 2048 * x.size(1);
  if (static_cast<int>(ncols < 1200)) {
    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 45.254833995939045;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 45.254833995939045;
    }
  }
  c_y.set_size(1, 221);
  for (i1 = 0; i1 < 221; i1++) {
    c_y[i1] = static_cast<double>(i1) + 1.0;
  }
  lag.set_size(221, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 221; i2++) {
      lag[i2 + lag.size(0) * i] =
          c1[(static_cast<int>(c_y[i2] + 1827.0) + 2048 * i) - 1];
    }
  }
  if (c1.size(1) != 0) {
    nx = c1.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    input_sizes_idx_0 = 221U;
  } else {
    input_sizes_idx_0 = 0U;
  }
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    sizes_idx_0 = 222;
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  input_sizes[1] = nx;
  b_c1.set_size(222, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 222; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = c1[i2 + 2048 * i];
    }
  }
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  Rt.set_size(input_sizes[0] + sizes_idx_0, input_sizes[1]);
  ncols = input_sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[i2 + Rt.size(0) * i] = lag[i2 + input_sizes[0] * i];
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[(i2 + input_sizes[0]) + Rt.size(0) * i] = b_c1[i2 + sizes[0] * i];
    }
  }
  if (250 > Rt.size(0)) {
    i1 = -1;
    i3 = -1;
  } else {
    i1 = 248;
    i3 = Rt.size(0) - 1;
  }
  ncols = Rt.size(1);
  b_x.set_size(1, Rt.size(1));
  nx = Rt.size(1);
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (i = 0; i < ncols; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 221];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 221];
    }
  }
  nx = Rt.size(1) - 1;
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  }
  nx = i3 - i1;
  lag.set_size(nx, b_x.size(1));
  ncols = b_x.size(1);
  for (int jcol{0}; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * nx;
    for (int itilerow{0}; itilerow < nx; itilerow++) {
      lag[ibmat + itilerow] = b_x[jcol];
    }
  }
  lag.set_size(nx, Rt.size(1));
  ncols = Rt.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i, k)

  for (i = 0; i < ncols; i++) {
    k = i3 - i1;
    for (i2 = 0; i2 < k; i2++) {
      lag[i2 + lag.size(0) * i] =
          Rt[((i1 + i2) + Rt.size(0) * i) + 1] / lag[i2 + lag.size(0) * i];
    }
  }
  if (lag.size(1) != 0) {
    nx = lag.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (lag.size(1) != 0)) {
    input_sizes_idx_0 = 27U;
  } else {
    input_sizes_idx_0 = 0U;
  }
  if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
    sizes_idx_0 = static_cast<short>(lag.size(0));
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  b_c1.set_size(input_sizes_idx_0 + sizes_idx_0, nx);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < nx; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = 0.0;
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[(i2 + input_sizes[0]) + b_c1.size(0) * i] = lag[i2 + sizes[0] * i];
    }
  }
  getCandidates(b_c1, edge, peak, locs);
  f0.set_size(locs.size(0));
  ncols = locs.size(0);
  if (static_cast<int>(locs.size(0) < 1200)) {
    for (i = 0; i < ncols; i++) {
      f0[i] = 11025.0 / locs[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      f0[i] = 11025.0 / locs[i];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &y
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void c_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
  array<creal_T, 2U> x;
  array<double, 2U> Rt;
  array<double, 2U> b_c1;
  array<double, 2U> b_x;
  array<double, 2U> b_y;
  array<double, 2U> c1;
  array<double, 2U> c_y;
  array<double, 2U> lag;
  array<double, 1U> locs;
  array<double, 1U> peak;
  double edge[2];
  int input_sizes[2];
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int ncols;
  int nx;
  short sizes_idx_0;
  unsigned char input_sizes_idx_0;
  boolean_T empty_non_axis_sizes;
  edge[0] = 30.0;
  edge[1] = 240.0;
  c_fft(y, x);
  nx = x.size(1) << 11;
  c1.set_size(2048, x.size(1));
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  }
  b_y.set_size(2048, c1.size(1));
  nx = c1.size(1) << 11;
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  }
  b_ifft(b_y, x);
  c1.set_size(2048, x.size(1));
  ncols = 2048 * x.size(1);
  if (static_cast<int>(ncols < 1200)) {
    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 45.254833995939045;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 45.254833995939045;
    }
  }
  c_y.set_size(1, 240);
  for (i1 = 0; i1 < 240; i1++) {
    c_y[i1] = static_cast<double>(i1) + 1.0;
  }
  lag.set_size(240, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 240; i2++) {
      lag[i2 + lag.size(0) * i] =
          c1[(static_cast<int>(c_y[i2] + 1808.0) + 2048 * i) - 1];
    }
  }
  if (c1.size(1) != 0) {
    nx = c1.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    input_sizes_idx_0 = 240U;
  } else {
    input_sizes_idx_0 = 0U;
  }
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    sizes_idx_0 = 241;
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  input_sizes[1] = nx;
  b_c1.set_size(241, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 241; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = c1[i2 + 2048 * i];
    }
  }
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  Rt.set_size(input_sizes[0] + sizes_idx_0, input_sizes[1]);
  ncols = input_sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[i2 + Rt.size(0) * i] = lag[i2 + input_sizes[0] * i];
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[(i2 + input_sizes[0]) + Rt.size(0) * i] = b_c1[i2 + sizes[0] * i];
    }
  }
  if (271 > Rt.size(0)) {
    i1 = -1;
    i3 = -1;
  } else {
    i1 = 269;
    i3 = Rt.size(0) - 1;
  }
  ncols = Rt.size(1);
  b_x.set_size(1, Rt.size(1));
  nx = Rt.size(1);
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (i = 0; i < ncols; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 240];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 240];
    }
  }
  nx = Rt.size(1) - 1;
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  }
  nx = i3 - i1;
  lag.set_size(nx, b_x.size(1));
  ncols = b_x.size(1);
  for (int jcol{0}; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * nx;
    for (int itilerow{0}; itilerow < nx; itilerow++) {
      lag[ibmat + itilerow] = b_x[jcol];
    }
  }
  lag.set_size(nx, Rt.size(1));
  ncols = Rt.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i, k)

  for (i = 0; i < ncols; i++) {
    k = i3 - i1;
    for (i2 = 0; i2 < k; i2++) {
      lag[i2 + lag.size(0) * i] =
          Rt[((i1 + i2) + Rt.size(0) * i) + 1] / lag[i2 + lag.size(0) * i];
    }
  }
  if (lag.size(1) != 0) {
    nx = lag.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (lag.size(1) != 0)) {
    input_sizes_idx_0 = 29U;
  } else {
    input_sizes_idx_0 = 0U;
  }
  if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
    sizes_idx_0 = static_cast<short>(lag.size(0));
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  b_c1.set_size(input_sizes_idx_0 + sizes_idx_0, nx);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < nx; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = 0.0;
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[(i2 + input_sizes[0]) + b_c1.size(0) * i] = lag[i2 + sizes[0] * i];
    }
  }
  getCandidates(b_c1, edge, peak, locs);
  f0.set_size(locs.size(0));
  ncols = locs.size(0);
  if (static_cast<int>(locs.size(0) < 1200)) {
    for (i = 0; i < ncols; i++) {
      f0[i] = 12000.0 / locs[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      f0[i] = 12000.0 / locs[i];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &y
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void d_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
  array<creal_T, 2U> x;
  array<double, 2U> Rt;
  array<double, 2U> b_c1;
  array<double, 2U> b_x;
  array<double, 2U> b_y;
  array<double, 2U> c1;
  array<double, 2U> c_y;
  array<double, 2U> lag;
  array<double, 1U> locs;
  array<double, 1U> peak;
  double edge[2];
  int input_sizes[2];
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int ncols;
  int nx;
  short input_sizes_idx_0;
  short sizes_idx_0;
  boolean_T empty_non_axis_sizes;
  edge[0] = 55.0;
  edge[1] = 441.0;
  d_fft(y, x);
  nx = x.size(1) << 12;
  c1.set_size(4096, x.size(1));
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  }
  b_y.set_size(4096, c1.size(1));
  nx = c1.size(1) << 12;
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  }
  c_ifft(b_y, x);
  c1.set_size(4096, x.size(1));
  ncols = 4096 * x.size(1);
  if (static_cast<int>(ncols < 1200)) {
    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 64.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 64.0;
    }
  }
  c_y.set_size(1, 441);
  for (i1 = 0; i1 < 441; i1++) {
    c_y[i1] = static_cast<double>(i1) + 1.0;
  }
  lag.set_size(441, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 441; i2++) {
      lag[i2 + lag.size(0) * i] =
          c1[(static_cast<int>(c_y[i2] + 3655.0) + 4096 * i) - 1];
    }
  }
  if (c1.size(1) != 0) {
    nx = c1.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    input_sizes_idx_0 = 441;
  } else {
    input_sizes_idx_0 = 0;
  }
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    sizes_idx_0 = 442;
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  input_sizes[1] = nx;
  b_c1.set_size(442, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 442; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = c1[i2 + 4096 * i];
    }
  }
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  Rt.set_size(input_sizes[0] + sizes_idx_0, input_sizes[1]);
  ncols = input_sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[i2 + Rt.size(0) * i] = lag[i2 + input_sizes[0] * i];
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[(i2 + input_sizes[0]) + Rt.size(0) * i] = b_c1[i2 + sizes[0] * i];
    }
  }
  if (497 > Rt.size(0)) {
    i1 = -1;
    i3 = -1;
  } else {
    i1 = 495;
    i3 = Rt.size(0) - 1;
  }
  ncols = Rt.size(1);
  b_x.set_size(1, Rt.size(1));
  nx = Rt.size(1);
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (i = 0; i < ncols; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 441];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 441];
    }
  }
  nx = Rt.size(1) - 1;
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  }
  nx = i3 - i1;
  lag.set_size(nx, b_x.size(1));
  ncols = b_x.size(1);
  for (int jcol{0}; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * nx;
    for (int itilerow{0}; itilerow < nx; itilerow++) {
      lag[ibmat + itilerow] = b_x[jcol];
    }
  }
  lag.set_size(nx, Rt.size(1));
  ncols = Rt.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i, k)

  for (i = 0; i < ncols; i++) {
    k = i3 - i1;
    for (i2 = 0; i2 < k; i2++) {
      lag[i2 + lag.size(0) * i] =
          Rt[((i1 + i2) + Rt.size(0) * i) + 1] / lag[i2 + lag.size(0) * i];
    }
  }
  if (lag.size(1) != 0) {
    nx = lag.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (lag.size(1) != 0)) {
    input_sizes_idx_0 = 54;
  } else {
    input_sizes_idx_0 = 0;
  }
  if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
    sizes_idx_0 = static_cast<short>(lag.size(0));
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  b_c1.set_size(input_sizes_idx_0 + sizes_idx_0, nx);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < nx; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = 0.0;
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[(i2 + input_sizes[0]) + b_c1.size(0) * i] = lag[i2 + sizes[0] * i];
    }
  }
  getCandidates(b_c1, edge, peak, locs);
  f0.set_size(locs.size(0));
  ncols = locs.size(0);
  if (static_cast<int>(locs.size(0) < 1200)) {
    for (i = 0; i < ncols; i++) {
      f0[i] = 22050.0 / locs[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      f0[i] = 22050.0 / locs[i];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &y
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void e_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
  array<creal_T, 2U> x;
  array<double, 2U> Rt;
  array<double, 2U> b_c1;
  array<double, 2U> b_x;
  array<double, 2U> b_y;
  array<double, 2U> c1;
  array<double, 2U> c_y;
  array<double, 2U> lag;
  array<double, 1U> locs;
  array<double, 1U> peak;
  double edge[2];
  int input_sizes[2];
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int ncols;
  int nx;
  short input_sizes_idx_0;
  short sizes_idx_0;
  boolean_T empty_non_axis_sizes;
  edge[0] = 60.0;
  edge[1] = 480.0;
  e_fft(y, x);
  nx = x.size(1) << 12;
  c1.set_size(4096, x.size(1));
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  }
  b_y.set_size(4096, c1.size(1));
  nx = c1.size(1) << 12;
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  }
  c_ifft(b_y, x);
  c1.set_size(4096, x.size(1));
  ncols = 4096 * x.size(1);
  if (static_cast<int>(ncols < 1200)) {
    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 64.0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 64.0;
    }
  }
  c_y.set_size(1, 480);
  for (i1 = 0; i1 < 480; i1++) {
    c_y[i1] = static_cast<double>(i1) + 1.0;
  }
  lag.set_size(480, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 480; i2++) {
      lag[i2 + lag.size(0) * i] =
          c1[(static_cast<int>(c_y[i2] + 3616.0) + 4096 * i) - 1];
    }
  }
  if (c1.size(1) != 0) {
    nx = c1.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    input_sizes_idx_0 = 480;
  } else {
    input_sizes_idx_0 = 0;
  }
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    sizes_idx_0 = 481;
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  input_sizes[1] = nx;
  b_c1.set_size(481, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 481; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = c1[i2 + 4096 * i];
    }
  }
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  Rt.set_size(input_sizes[0] + sizes_idx_0, input_sizes[1]);
  ncols = input_sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[i2 + Rt.size(0) * i] = lag[i2 + input_sizes[0] * i];
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[(i2 + input_sizes[0]) + Rt.size(0) * i] = b_c1[i2 + sizes[0] * i];
    }
  }
  if (541 > Rt.size(0)) {
    i1 = -1;
    i3 = -1;
  } else {
    i1 = 539;
    i3 = Rt.size(0) - 1;
  }
  ncols = Rt.size(1);
  b_x.set_size(1, Rt.size(1));
  nx = Rt.size(1);
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (i = 0; i < ncols; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 480];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 480];
    }
  }
  nx = Rt.size(1) - 1;
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  }
  nx = i3 - i1;
  lag.set_size(nx, b_x.size(1));
  ncols = b_x.size(1);
  for (int jcol{0}; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * nx;
    for (int itilerow{0}; itilerow < nx; itilerow++) {
      lag[ibmat + itilerow] = b_x[jcol];
    }
  }
  lag.set_size(nx, Rt.size(1));
  ncols = Rt.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i, k)

  for (i = 0; i < ncols; i++) {
    k = i3 - i1;
    for (i2 = 0; i2 < k; i2++) {
      lag[i2 + lag.size(0) * i] =
          Rt[((i1 + i2) + Rt.size(0) * i) + 1] / lag[i2 + lag.size(0) * i];
    }
  }
  if (lag.size(1) != 0) {
    nx = lag.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (lag.size(1) != 0)) {
    input_sizes_idx_0 = 59;
  } else {
    input_sizes_idx_0 = 0;
  }
  if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
    sizes_idx_0 = static_cast<short>(lag.size(0));
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  b_c1.set_size(input_sizes_idx_0 + sizes_idx_0, nx);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < nx; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = 0.0;
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[(i2 + input_sizes[0]) + b_c1.size(0) * i] = lag[i2 + sizes[0] * i];
    }
  }
  getCandidates(b_c1, edge, peak, locs);
  f0.set_size(locs.size(0));
  ncols = locs.size(0);
  if (static_cast<int>(locs.size(0) < 1200)) {
    for (i = 0; i < ncols; i++) {
      f0[i] = 24000.0 / locs[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      f0[i] = 24000.0 / locs[i];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &y
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void f_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
  array<creal_T, 2U> x;
  array<double, 2U> Rt;
  array<double, 2U> b_c1;
  array<double, 2U> b_x;
  array<double, 2U> b_y;
  array<double, 2U> c1;
  array<double, 2U> c_y;
  array<double, 2U> lag;
  array<double, 1U> locs;
  array<double, 1U> peak;
  double edge[2];
  int input_sizes[2];
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int ncols;
  int nx;
  short input_sizes_idx_0;
  short sizes_idx_0;
  boolean_T empty_non_axis_sizes;
  edge[0] = 110.0;
  edge[1] = 882.0;
  f_fft(y, x);
  nx = x.size(1) << 13;
  c1.set_size(8192, x.size(1));
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  }
  b_y.set_size(8192, c1.size(1));
  nx = c1.size(1) << 13;
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  }
  d_ifft(b_y, x);
  c1.set_size(8192, x.size(1));
  ncols = 8192 * x.size(1);
  if (static_cast<int>(ncols < 1200)) {
    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 90.509667991878089;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 90.509667991878089;
    }
  }
  c_y.set_size(1, 882);
  for (i1 = 0; i1 < 882; i1++) {
    c_y[i1] = static_cast<double>(i1) + 1.0;
  }
  lag.set_size(882, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 882; i2++) {
      lag[i2 + lag.size(0) * i] =
          c1[(static_cast<int>(c_y[i2] + 7310.0) + 8192 * i) - 1];
    }
  }
  if (c1.size(1) != 0) {
    nx = c1.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    input_sizes_idx_0 = 882;
  } else {
    input_sizes_idx_0 = 0;
  }
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    sizes_idx_0 = 883;
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  input_sizes[1] = nx;
  b_c1.set_size(883, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 883; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = c1[i2 + 8192 * i];
    }
  }
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  Rt.set_size(input_sizes[0] + sizes_idx_0, input_sizes[1]);
  ncols = input_sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[i2 + Rt.size(0) * i] = lag[i2 + input_sizes[0] * i];
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[(i2 + input_sizes[0]) + Rt.size(0) * i] = b_c1[i2 + sizes[0] * i];
    }
  }
  if (993 > Rt.size(0)) {
    i1 = -1;
    i3 = -1;
  } else {
    i1 = 991;
    i3 = Rt.size(0) - 1;
  }
  ncols = Rt.size(1);
  b_x.set_size(1, Rt.size(1));
  nx = Rt.size(1);
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (i = 0; i < ncols; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 882];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 882];
    }
  }
  nx = Rt.size(1) - 1;
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  }
  nx = i3 - i1;
  lag.set_size(nx, b_x.size(1));
  ncols = b_x.size(1);
  for (int jcol{0}; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * nx;
    for (int itilerow{0}; itilerow < nx; itilerow++) {
      lag[ibmat + itilerow] = b_x[jcol];
    }
  }
  lag.set_size(nx, Rt.size(1));
  ncols = Rt.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i, k)

  for (i = 0; i < ncols; i++) {
    k = i3 - i1;
    for (i2 = 0; i2 < k; i2++) {
      lag[i2 + lag.size(0) * i] =
          Rt[((i1 + i2) + Rt.size(0) * i) + 1] / lag[i2 + lag.size(0) * i];
    }
  }
  if (lag.size(1) != 0) {
    nx = lag.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (lag.size(1) != 0)) {
    input_sizes_idx_0 = 109;
  } else {
    input_sizes_idx_0 = 0;
  }
  if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
    sizes_idx_0 = static_cast<short>(lag.size(0));
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  b_c1.set_size(input_sizes_idx_0 + sizes_idx_0, nx);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < nx; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = 0.0;
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[(i2 + input_sizes[0]) + b_c1.size(0) * i] = lag[i2 + sizes[0] * i];
    }
  }
  getCandidates(b_c1, edge, peak, locs);
  f0.set_size(locs.size(0));
  ncols = locs.size(0);
  if (static_cast<int>(locs.size(0) < 1200)) {
    for (i = 0; i < ncols; i++) {
      f0[i] = 44100.0 / locs[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      f0[i] = 44100.0 / locs[i];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &y
//                ::coder::array<double, 1U> &f0
// Return Type  : void
//
void g_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0)
{
  array<creal_T, 2U> x;
  array<double, 2U> Rt;
  array<double, 2U> b_c1;
  array<double, 2U> b_x;
  array<double, 2U> b_y;
  array<double, 2U> c1;
  array<double, 2U> c_y;
  array<double, 2U> lag;
  array<double, 1U> locs;
  array<double, 1U> peak;
  double edge[2];
  int input_sizes[2];
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int ncols;
  int nx;
  short input_sizes_idx_0;
  short sizes_idx_0;
  boolean_T empty_non_axis_sizes;
  edge[0] = 120.0;
  edge[1] = 960.0;
  g_fft(y, x);
  nx = x.size(1) << 13;
  c1.set_size(8192, x.size(1));
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      c1[k] = rt_hypotd_snf(x[k].re, x[k].im);
    }
  }
  b_y.set_size(8192, c1.size(1));
  nx = c1.size(1) << 13;
  if (static_cast<int>(nx < 1200)) {
    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k < nx; k++) {
      b_y[k] = c1[k] * c1[k];
    }
  }
  d_ifft(b_y, x);
  c1.set_size(8192, x.size(1));
  ncols = 8192 * x.size(1);
  if (static_cast<int>(ncols < 1200)) {
    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 90.509667991878089;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      c1[i] = x[i].re / 90.509667991878089;
    }
  }
  c_y.set_size(1, 960);
  for (i1 = 0; i1 < 960; i1++) {
    c_y[i1] = static_cast<double>(i1) + 1.0;
  }
  lag.set_size(960, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 960; i2++) {
      lag[i2 + lag.size(0) * i] =
          c1[(static_cast<int>(c_y[i2] + 7232.0) + 8192 * i) - 1];
    }
  }
  if (c1.size(1) != 0) {
    nx = c1.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    input_sizes_idx_0 = 960;
  } else {
    input_sizes_idx_0 = 0;
  }
  if (empty_non_axis_sizes || (c1.size(1) != 0)) {
    sizes_idx_0 = 961;
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  input_sizes[1] = nx;
  b_c1.set_size(961, c1.size(1));
  ncols = c1.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i)

  for (i = 0; i < ncols; i++) {
    for (i2 = 0; i2 < 961; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = c1[i2 + 8192 * i];
    }
  }
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  Rt.set_size(input_sizes[0] + sizes_idx_0, input_sizes[1]);
  ncols = input_sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[i2 + Rt.size(0) * i] = lag[i2 + input_sizes[0] * i];
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      Rt[(i2 + input_sizes[0]) + Rt.size(0) * i] = b_c1[i2 + sizes[0] * i];
    }
  }
  if (1081 > Rt.size(0)) {
    i1 = -1;
    i3 = -1;
  } else {
    i1 = 1079;
    i3 = Rt.size(0) - 1;
  }
  ncols = Rt.size(1);
  b_x.set_size(1, Rt.size(1));
  nx = Rt.size(1);
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (i = 0; i < ncols; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 960];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < nx; i++) {
      b_x[i] = Rt[Rt.size(0) * i + 960];
    }
  }
  nx = Rt.size(1) - 1;
  if (static_cast<int>(Rt.size(1) < 1200)) {
    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

    for (k = 0; k <= nx; k++) {
      b_x[k] = std::sqrt(b_x[k]);
    }
  }
  nx = i3 - i1;
  lag.set_size(nx, b_x.size(1));
  ncols = b_x.size(1);
  for (int jcol{0}; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * nx;
    for (int itilerow{0}; itilerow < nx; itilerow++) {
      lag[ibmat + itilerow] = b_x[jcol];
    }
  }
  lag.set_size(nx, Rt.size(1));
  ncols = Rt.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, i, k)

  for (i = 0; i < ncols; i++) {
    k = i3 - i1;
    for (i2 = 0; i2 < k; i2++) {
      lag[i2 + lag.size(0) * i] =
          Rt[((i1 + i2) + Rt.size(0) * i) + 1] / lag[i2 + lag.size(0) * i];
    }
  }
  if (lag.size(1) != 0) {
    nx = lag.size(1);
  } else {
    nx = 0;
  }
  empty_non_axis_sizes = (nx == 0);
  if (empty_non_axis_sizes || (lag.size(1) != 0)) {
    input_sizes_idx_0 = 119;
  } else {
    input_sizes_idx_0 = 0;
  }
  if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
    sizes_idx_0 = static_cast<short>(lag.size(0));
  } else {
    sizes_idx_0 = 0;
  }
  input_sizes[0] = input_sizes_idx_0;
  sizes[0] = sizes_idx_0;
  sizes[1] = nx;
  b_c1.set_size(input_sizes_idx_0 + sizes_idx_0, nx);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < nx; i++) {
    k = input_sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[i2 + b_c1.size(0) * i] = 0.0;
    }
  }
  ncols = sizes[1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i2, k, i)

  for (i = 0; i < ncols; i++) {
    k = sizes[0];
    for (i2 = 0; i2 < k; i2++) {
      b_c1[(i2 + input_sizes[0]) + b_c1.size(0) * i] = lag[i2 + sizes[0] * i];
    }
  }
  getCandidates(b_c1, edge, peak, locs);
  f0.set_size(locs.size(0));
  ncols = locs.size(0);
  if (static_cast<int>(locs.size(0) < 1200)) {
    for (i = 0; i < ncols; i++) {
      f0[i] = 48000.0 / locs[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < ncols; i++) {
      f0[i] = 48000.0 / locs[i];
    }
  }
}

} // namespace pitch
} // namespace internal
} // namespace audio
} // namespace coder

//
// File trailer for NCF.cpp
//
// [EOF]
//
