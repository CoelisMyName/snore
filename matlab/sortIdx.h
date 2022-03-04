#ifndef SORTIDX_H
#define SORTIDX_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
void b_merge(int idx[200], double x[200], int offset, int np, int nq,
             int iwork[200], double xwork[200]);

void merge(int idx[32], double x[32], int offset, int np, int nq, int iwork[32],
           double xwork[32]);

void merge_block(::coder::array<int, 1U> &idx, ::coder::array<double, 1U> &x,
                 int offset, int n, int preSortLevel,
                 ::coder::array<int, 1U> &iwork,
                 ::coder::array<double, 1U> &xwork);

void sortIdx(::coder::array<double, 2U> &x, ::coder::array<int, 2U> &idx);

} // namespace internal
} // namespace coder

#endif
