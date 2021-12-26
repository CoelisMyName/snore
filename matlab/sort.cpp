//
// File: sort.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &x
// Return Type  : void
//
namespace coder {
namespace internal {
void sort(::coder::array<double, 1U> &x)
{
  array<double, 1U> b_xwork;
  array<double, 1U> vwork;
  array<double, 1U> xwork;
  array<int, 1U> b_iwork;
  array<int, 1U> iidx;
  array<int, 1U> iwork;
  double c_xwork[256];
  double x4[4];
  int c_iwork[256];
  int idx4[4];
  int dim;
  int i2;
  int k;
  int vlen;
  int vstride;
  signed char perm[4];
  dim = 0;
  if (x.size(0) != 1) {
    dim = -1;
  }
  if (dim + 2 <= 1) {
    i2 = x.size(0);
  } else {
    i2 = 1;
  }
  vlen = i2 - 1;
  vwork.set_size(i2);
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x.size(0);
  }
  for (int j{0}; j < vstride; j++) {
    for (k = 0; k <= vlen; k++) {
      vwork[k] = x[j + k * vstride];
    }
    iidx.set_size(vwork.size(0));
    dim = vwork.size(0);
    for (i2 = 0; i2 < dim; i2++) {
      iidx[i2] = 0;
    }
    if (vwork.size(0) != 0) {
      int bLen;
      int b_n;
      int i1;
      int i3;
      int i4;
      int iidx_tmp;
      int n;
      int nNonNaN;
      n = vwork.size(0);
      b_n = vwork.size(0);
      x4[0] = 0.0;
      idx4[0] = 0;
      x4[1] = 0.0;
      idx4[1] = 0;
      x4[2] = 0.0;
      idx4[2] = 0;
      x4[3] = 0.0;
      idx4[3] = 0;
      iwork.set_size(vwork.size(0));
      dim = vwork.size(0);
      for (i2 = 0; i2 < dim; i2++) {
        iwork[i2] = 0;
      }
      xwork.set_size(vwork.size(0));
      dim = vwork.size(0);
      for (i2 = 0; i2 < dim; i2++) {
        xwork[i2] = 0.0;
      }
      bLen = 0;
      dim = -1;
      for (k = 0; k < b_n; k++) {
        if (std::isnan(vwork[k])) {
          iidx_tmp = (b_n - bLen) - 1;
          iidx[iidx_tmp] = k + 1;
          xwork[iidx_tmp] = vwork[k];
          bLen++;
        } else {
          dim++;
          idx4[dim] = k + 1;
          x4[dim] = vwork[k];
          if (dim + 1 == 4) {
            double d;
            double d1;
            dim = k - bLen;
            if (x4[0] <= x4[1]) {
              i1 = 1;
              i2 = 2;
            } else {
              i1 = 2;
              i2 = 1;
            }
            if (x4[2] <= x4[3]) {
              i3 = 3;
              i4 = 4;
            } else {
              i3 = 4;
              i4 = 3;
            }
            d = x4[i1 - 1];
            d1 = x4[i3 - 1];
            if (d <= d1) {
              d = x4[i2 - 1];
              if (d <= d1) {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i2);
                perm[2] = static_cast<signed char>(i3);
                perm[3] = static_cast<signed char>(i4);
              } else if (d <= x4[i4 - 1]) {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i3);
                perm[2] = static_cast<signed char>(i2);
                perm[3] = static_cast<signed char>(i4);
              } else {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i3);
                perm[2] = static_cast<signed char>(i4);
                perm[3] = static_cast<signed char>(i2);
              }
            } else {
              d1 = x4[i4 - 1];
              if (d <= d1) {
                if (x4[i2 - 1] <= d1) {
                  perm[0] = static_cast<signed char>(i3);
                  perm[1] = static_cast<signed char>(i1);
                  perm[2] = static_cast<signed char>(i2);
                  perm[3] = static_cast<signed char>(i4);
                } else {
                  perm[0] = static_cast<signed char>(i3);
                  perm[1] = static_cast<signed char>(i1);
                  perm[2] = static_cast<signed char>(i4);
                  perm[3] = static_cast<signed char>(i2);
                }
              } else {
                perm[0] = static_cast<signed char>(i3);
                perm[1] = static_cast<signed char>(i4);
                perm[2] = static_cast<signed char>(i1);
                perm[3] = static_cast<signed char>(i2);
              }
            }
            iidx[dim - 3] = idx4[perm[0] - 1];
            iidx[dim - 2] = idx4[perm[1] - 1];
            iidx[dim - 1] = idx4[perm[2] - 1];
            iidx[dim] = idx4[perm[3] - 1];
            vwork[dim - 3] = x4[perm[0] - 1];
            vwork[dim - 2] = x4[perm[1] - 1];
            vwork[dim - 1] = x4[perm[2] - 1];
            vwork[dim] = x4[perm[3] - 1];
            dim = -1;
          }
        }
      }
      i3 = (b_n - bLen) - 1;
      if (dim + 1 > 0) {
        perm[1] = 0;
        perm[2] = 0;
        perm[3] = 0;
        if (dim + 1 == 1) {
          perm[0] = 1;
        } else if (dim + 1 == 2) {
          if (x4[0] <= x4[1]) {
            perm[0] = 1;
            perm[1] = 2;
          } else {
            perm[0] = 2;
            perm[1] = 1;
          }
        } else if (x4[0] <= x4[1]) {
          if (x4[1] <= x4[2]) {
            perm[0] = 1;
            perm[1] = 2;
            perm[2] = 3;
          } else if (x4[0] <= x4[2]) {
            perm[0] = 1;
            perm[1] = 3;
            perm[2] = 2;
          } else {
            perm[0] = 3;
            perm[1] = 1;
            perm[2] = 2;
          }
        } else if (x4[0] <= x4[2]) {
          perm[0] = 2;
          perm[1] = 1;
          perm[2] = 3;
        } else if (x4[1] <= x4[2]) {
          perm[0] = 2;
          perm[1] = 3;
          perm[2] = 1;
        } else {
          perm[0] = 3;
          perm[1] = 2;
          perm[2] = 1;
        }
        for (k = 0; k <= dim; k++) {
          iidx_tmp = perm[k] - 1;
          i1 = (i3 - dim) + k;
          iidx[i1] = idx4[iidx_tmp];
          vwork[i1] = x4[iidx_tmp];
        }
      }
      dim = (bLen >> 1) + 1;
      for (k = 0; k <= dim - 2; k++) {
        i1 = (i3 + k) + 1;
        i2 = iidx[i1];
        iidx_tmp = (b_n - k) - 1;
        iidx[i1] = iidx[iidx_tmp];
        iidx[iidx_tmp] = i2;
        vwork[i1] = xwork[iidx_tmp];
        vwork[iidx_tmp] = xwork[i1];
      }
      if ((bLen & 1) != 0) {
        dim += i3;
        vwork[dim] = xwork[dim];
      }
      nNonNaN = n - bLen;
      i1 = 2;
      if (nNonNaN > 1) {
        if (n >= 256) {
          int nBlocks;
          nBlocks = nNonNaN >> 8;
          if (nBlocks > 0) {
            for (int b{0}; b < nBlocks; b++) {
              i4 = (b << 8) - 1;
              for (int b_b{0}; b_b < 6; b_b++) {
                bLen = 1 << (b_b + 2);
                b_n = bLen << 1;
                n = 256 >> (b_b + 3);
                for (k = 0; k < n; k++) {
                  i2 = (i4 + k * b_n) + 1;
                  for (i1 = 0; i1 < b_n; i1++) {
                    dim = i2 + i1;
                    c_iwork[i1] = iidx[dim];
                    c_xwork[i1] = vwork[dim];
                  }
                  i3 = 0;
                  i1 = bLen;
                  dim = i2 - 1;
                  int exitg1;
                  do {
                    exitg1 = 0;
                    dim++;
                    if (c_xwork[i3] <= c_xwork[i1]) {
                      iidx[dim] = c_iwork[i3];
                      vwork[dim] = c_xwork[i3];
                      if (i3 + 1 < bLen) {
                        i3++;
                      } else {
                        exitg1 = 1;
                      }
                    } else {
                      iidx[dim] = c_iwork[i1];
                      vwork[dim] = c_xwork[i1];
                      if (i1 + 1 < b_n) {
                        i1++;
                      } else {
                        dim -= i3;
                        for (i1 = i3 + 1; i1 <= bLen; i1++) {
                          iidx_tmp = dim + i1;
                          iidx[iidx_tmp] = c_iwork[i1 - 1];
                          vwork[iidx_tmp] = c_xwork[i1 - 1];
                        }
                        exitg1 = 1;
                      }
                    }
                  } while (exitg1 == 0);
                }
              }
            }
            dim = nBlocks << 8;
            i1 = nNonNaN - dim;
            if (i1 > 0) {
              merge_block(iidx, vwork, dim, i1, 2, iwork, xwork);
            }
            i1 = 8;
          }
        }
        dim = iwork.size(0);
        b_iwork.set_size(iwork.size(0));
        for (i2 = 0; i2 < dim; i2++) {
          b_iwork[i2] = iwork[i2];
        }
        b_xwork.set_size(xwork.size(0));
        dim = xwork.size(0);
        for (i2 = 0; i2 < dim; i2++) {
          b_xwork[i2] = xwork[i2];
        }
        merge_block(iidx, vwork, 0, nNonNaN, i1, b_iwork, b_xwork);
      }
    }
    for (k = 0; k <= vlen; k++) {
      x[j + k * vstride] = vwork[k];
    }
  }
}

//
// Arguments    : double x[200]
// Return Type  : void
//
void sort(double x[200])
{
  double xwork[200];
  double x4[4];
  int idx[200];
  int iwork[200];
  int b_idx_tmp;
  int b_k;
  int i2;
  int i3;
  int ib;
  int idx_tmp;
  int k;
  int nNaNs;
  int quartetOffset;
  unsigned char idx4[4];
  signed char perm[4];
  x4[0] = 0.0;
  idx4[0] = 0U;
  x4[1] = 0.0;
  idx4[1] = 0U;
  x4[2] = 0.0;
  idx4[2] = 0U;
  x4[3] = 0.0;
  idx4[3] = 0U;
  std::memset(&idx[0], 0, 200U * sizeof(int));
  std::memset(&xwork[0], 0, 200U * sizeof(double));
  nNaNs = 0;
  ib = 0;
  for (k = 0; k < 200; k++) {
    if (std::isnan(x[k])) {
      idx[199 - nNaNs] = k + 1;
      xwork[199 - nNaNs] = x[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = static_cast<unsigned char>(k + 1);
      x4[ib - 1] = x[k];
      if (ib == 4) {
        double d;
        double d1;
        int i4;
        quartetOffset = k - nNaNs;
        if (x4[0] <= x4[1]) {
          ib = 1;
          i2 = 2;
        } else {
          ib = 2;
          i2 = 1;
        }
        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }
        d = x4[ib - 1];
        d1 = x4[i3 - 1];
        if (d <= d1) {
          d = x4[i2 - 1];
          if (d <= d1) {
            perm[0] = static_cast<signed char>(ib);
            perm[1] = static_cast<signed char>(i2);
            perm[2] = static_cast<signed char>(i3);
            perm[3] = static_cast<signed char>(i4);
          } else if (d <= x4[i4 - 1]) {
            perm[0] = static_cast<signed char>(ib);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i2);
            perm[3] = static_cast<signed char>(i4);
          } else {
            perm[0] = static_cast<signed char>(ib);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i4);
            perm[3] = static_cast<signed char>(i2);
          }
        } else {
          d1 = x4[i4 - 1];
          if (d <= d1) {
            if (x4[i2 - 1] <= d1) {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(ib);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(ib);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            perm[0] = static_cast<signed char>(i3);
            perm[1] = static_cast<signed char>(i4);
            perm[2] = static_cast<signed char>(ib);
            perm[3] = static_cast<signed char>(i2);
          }
        }
        idx[quartetOffset - 3] = idx4[perm[0] - 1];
        idx[quartetOffset - 2] = idx4[perm[1] - 1];
        idx[quartetOffset - 1] = idx4[perm[2] - 1];
        idx[quartetOffset] = idx4[perm[3] - 1];
        x[quartetOffset - 3] = x4[perm[0] - 1];
        x[quartetOffset - 2] = x4[perm[1] - 1];
        x[quartetOffset - 1] = x4[perm[2] - 1];
        x[quartetOffset] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }
  if (ib > 0) {
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }
    if (static_cast<int>(ib < 1200)) {
      for (b_k = 0; b_k < ib; b_k++) {
        quartetOffset = perm[b_k] - 1;
        i2 = ((b_k - nNaNs) - ib) + 200;
        idx[i2] = idx4[quartetOffset];
        x[i2] = x4[quartetOffset];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    b_k, idx_tmp, b_idx_tmp)

      for (b_k = 0; b_k < ib; b_k++) {
        idx_tmp = perm[b_k] - 1;
        b_idx_tmp = ((b_k - nNaNs) - ib) + 200;
        idx[b_idx_tmp] = idx4[idx_tmp];
        x[b_idx_tmp] = x4[idx_tmp];
      }
    }
  }
  quartetOffset = (nNaNs >> 1) + 200;
  for (k = 0; k <= quartetOffset - 201; k++) {
    i2 = (k - nNaNs) + 200;
    ib = idx[i2];
    idx[i2] = idx[199 - k];
    idx[199 - k] = ib;
    x[i2] = xwork[199 - k];
    x[199 - k] = xwork[i2];
  }
  if ((nNaNs & 1) != 0) {
    quartetOffset -= nNaNs;
    x[quartetOffset] = xwork[quartetOffset];
  }
  if (200 - nNaNs > 1) {
    std::memset(&iwork[0], 0, 200U * sizeof(int));
    i3 = (200 - nNaNs) >> 2;
    ib = 4;
    while (i3 > 1) {
      if ((i3 & 1) != 0) {
        i3--;
        i2 = ib * i3;
        quartetOffset = 200 - (nNaNs + i2);
        if (quartetOffset > ib) {
          merge(idx, x, i2, ib, quartetOffset - ib, iwork, xwork);
        }
      }
      quartetOffset = ib << 1;
      i3 >>= 1;
      for (k = 0; k < i3; k++) {
        merge(idx, x, k * quartetOffset, ib, ib, iwork, xwork);
      }
      ib = quartetOffset;
    }
    if (200 - nNaNs > ib) {
      merge(idx, x, 0, ib, 200 - (nNaNs + ib), iwork, xwork);
    }
  }
}

//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
void sort(::coder::array<double, 2U> &x)
{
  array<double, 1U> xwork;
  array<int, 2U> idx;
  array<int, 1U> iwork;
  double x4[4];
  int idx4[4];
  int b_idx_tmp;
  int b_k;
  int idx_tmp;
  int quartetOffset;
  signed char perm[4];
  idx.set_size(1, x.size(1));
  quartetOffset = x.size(1);
  if (static_cast<int>(quartetOffset < 1200)) {
    for (idx_tmp = 0; idx_tmp < quartetOffset; idx_tmp++) {
      idx[idx_tmp] = 0;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(idx_tmp)

    for (idx_tmp = 0; idx_tmp < quartetOffset; idx_tmp++) {
      idx[idx_tmp] = 0;
    }
  }
  if (x.size(1) != 0) {
    int b_n;
    int i2;
    int i3;
    int i4;
    int ib;
    int k;
    int n;
    int nNaNs;
    n = x.size(1);
    b_n = x.size(1);
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    quartetOffset = x.size(1);
    iwork.set_size(quartetOffset);
    if (static_cast<int>(quartetOffset < 1200)) {
      for (idx_tmp = 0; idx_tmp < quartetOffset; idx_tmp++) {
        iwork[idx_tmp] = 0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(idx_tmp)

      for (idx_tmp = 0; idx_tmp < quartetOffset; idx_tmp++) {
        iwork[idx_tmp] = 0;
      }
    }
    quartetOffset = x.size(1);
    xwork.set_size(quartetOffset);
    if (static_cast<int>(quartetOffset < 1200)) {
      for (idx_tmp = 0; idx_tmp < quartetOffset; idx_tmp++) {
        xwork[idx_tmp] = 0.0;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(idx_tmp)

      for (idx_tmp = 0; idx_tmp < quartetOffset; idx_tmp++) {
        xwork[idx_tmp] = 0.0;
      }
    }
    nNaNs = 0;
    ib = -1;
    for (k = 0; k < b_n; k++) {
      if (std::isnan(x[k])) {
        i3 = (b_n - nNaNs) - 1;
        idx[i3] = k + 1;
        xwork[i3] = x[k];
        nNaNs++;
      } else {
        ib++;
        idx4[ib] = k + 1;
        x4[ib] = x[k];
        if (ib + 1 == 4) {
          double d;
          double d1;
          quartetOffset = k - nNaNs;
          if (x4[0] <= x4[1]) {
            ib = 1;
            i2 = 2;
          } else {
            ib = 2;
            i2 = 1;
          }
          if (x4[2] <= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }
          d = x4[ib - 1];
          d1 = x4[i3 - 1];
          if (d <= d1) {
            d = x4[i2 - 1];
            if (d <= d1) {
              perm[0] = static_cast<signed char>(ib);
              perm[1] = static_cast<signed char>(i2);
              perm[2] = static_cast<signed char>(i3);
              perm[3] = static_cast<signed char>(i4);
            } else if (d <= x4[i4 - 1]) {
              perm[0] = static_cast<signed char>(ib);
              perm[1] = static_cast<signed char>(i3);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(ib);
              perm[1] = static_cast<signed char>(i3);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            d1 = x4[i4 - 1];
            if (d <= d1) {
              if (x4[i2 - 1] <= d1) {
                perm[0] = static_cast<signed char>(i3);
                perm[1] = static_cast<signed char>(ib);
                perm[2] = static_cast<signed char>(i2);
                perm[3] = static_cast<signed char>(i4);
              } else {
                perm[0] = static_cast<signed char>(i3);
                perm[1] = static_cast<signed char>(ib);
                perm[2] = static_cast<signed char>(i4);
                perm[3] = static_cast<signed char>(i2);
              }
            } else {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i4);
              perm[2] = static_cast<signed char>(ib);
              perm[3] = static_cast<signed char>(i2);
            }
          }
          idx[quartetOffset - 3] = idx4[perm[0] - 1];
          idx[quartetOffset - 2] = idx4[perm[1] - 1];
          idx[quartetOffset - 1] = idx4[perm[2] - 1];
          idx[quartetOffset] = idx4[perm[3] - 1];
          x[quartetOffset - 3] = x4[perm[0] - 1];
          x[quartetOffset - 2] = x4[perm[1] - 1];
          x[quartetOffset - 1] = x4[perm[2] - 1];
          x[quartetOffset] = x4[perm[3] - 1];
          ib = -1;
        }
      }
    }
    i4 = (b_n - nNaNs) - 1;
    if (ib + 1 > 0) {
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib + 1 == 1) {
        perm[0] = 1;
      } else if (ib + 1 == 2) {
        if (x4[0] <= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] <= x4[1]) {
        if (x4[1] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }
      if (static_cast<int>(ib + 1 < 1200)) {
        for (b_k = 0; b_k <= ib; b_k++) {
          i3 = perm[b_k] - 1;
          quartetOffset = (i4 - ib) + b_k;
          idx[quartetOffset] = idx4[i3];
          x[quartetOffset] = x4[i3];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    b_k, idx_tmp, b_idx_tmp)

        for (b_k = 0; b_k <= ib; b_k++) {
          idx_tmp = perm[b_k] - 1;
          b_idx_tmp = (i4 - ib) + b_k;
          idx[b_idx_tmp] = idx4[idx_tmp];
          x[b_idx_tmp] = x4[idx_tmp];
        }
      }
    }
    quartetOffset = (nNaNs >> 1) + 1;
    for (k = 0; k <= quartetOffset - 2; k++) {
      ib = (i4 + k) + 1;
      i2 = idx[ib];
      i3 = (b_n - k) - 1;
      idx[ib] = idx[i3];
      idx[i3] = i2;
      x[ib] = xwork[i3];
      x[i3] = xwork[ib];
    }
    if ((nNaNs & 1) != 0) {
      quartetOffset += i4;
      x[quartetOffset] = xwork[quartetOffset];
    }
    i2 = n - nNaNs;
    quartetOffset = 2;
    if (i2 > 1) {
      if (n >= 256) {
        ib = i2 >> 8;
        if (ib > 0) {
          for (quartetOffset = 0; quartetOffset < ib; quartetOffset++) {
            merge_pow2_block(idx, x, quartetOffset << 8);
          }
          quartetOffset = ib << 8;
          ib = i2 - quartetOffset;
          if (ib > 0) {
            merge_block(idx, x, quartetOffset, ib, 2, iwork, xwork);
          }
          quartetOffset = 8;
        }
      }
      merge_block(idx, x, 0, i2, quartetOffset, iwork, xwork);
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for sort.cpp
//
// [EOF]
//
