//
// File: mean.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "mean.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cstring>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                double y_data[]
//                int y_size[2]
// Return Type  : void
//
namespace coder {
void mean(const ::coder::array<double, 2U> &x, double y_data[], int y_size[2])
{
  double bsum;
  int firstBlockLength;
  int hi;
  int ib;
  int k;
  int nblocks;
  int npages;
  int xblockoffset;
  int xi;
  int xpageoffset;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    y_size[1] = x.size(1);
    npages = x.size(1);
    if (static_cast<int>(x.size(1) < 1200)) {
      if (0 <= npages - 1) {
        std::memset(&y_data[0], 0, npages * sizeof(double));
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(xi)

      for (xi = 0; xi < npages; xi++) {
        y_data[xi] = 0.0;
      }
    }
  } else {
    int lastBlockLength;
    npages = x.size(1);
    y_size[1] = x.size(1);
    if (x.size(0) <= 1024) {
      firstBlockLength = x.size(0);
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = x.size(0) / 1024;
      lastBlockLength = x.size(0) - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    k, hi, bsum, xblockoffset, ib, xpageoffset, xi)

    for (xi = 0; xi < npages; xi++) {
      xpageoffset = xi * x.size(0);
      y_data[xi] = x[xpageoffset];
      for (k = 2; k <= firstBlockLength; k++) {
        y_data[xi] += x[(xpageoffset + k) - 1];
      }
      for (ib = 2; ib <= nblocks; ib++) {
        xblockoffset = xpageoffset + ((ib - 1) << 10);
        bsum = x[xblockoffset];
        if (ib == nblocks) {
          hi = lastBlockLength;
        } else {
          hi = 1024;
        }
        for (k = 2; k <= hi; k++) {
          bsum += x[(xblockoffset + k) - 1];
        }
        y_data[xi] += bsum;
      }
    }
  }
  y_size[0] = 1;
  firstBlockLength = x.size(0);
  nblocks = y_size[1] - 1;
  npages = y_size[1] - 1;
  if (static_cast<int>(y_size[1] < 1200)) {
    for (xi = 0; xi <= nblocks; xi++) {
      y_data[xi] /= static_cast<double>(firstBlockLength);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(xi)

    for (xi = 0; xi <= npages; xi++) {
      y_data[xi] /= static_cast<double>(firstBlockLength);
    }
  }
}

} // namespace coder

//
// File trailer for mean.cpp
//
// [EOF]
//
