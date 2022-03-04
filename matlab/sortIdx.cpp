#include "sortIdx.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

namespace coder {
namespace internal {
static void merge(::coder::array<int, 1U> &idx, ::coder::array<double, 1U> &x,
                  int offset, int np, int nq, ::coder::array<int, 1U> &iwork,
                  ::coder::array<double, 1U> &xwork);

static void merge(::coder::array<int, 2U> &idx, ::coder::array<double, 2U> &x,
                  int offset, int np, int nq, ::coder::array<int, 1U> &iwork,
                  ::coder::array<double, 1U> &xwork);

static void merge_block(::coder::array<int, 2U> &idx,
                        ::coder::array<double, 2U> &x, int offset, int n,
                        int preSortLevel, ::coder::array<int, 1U> &iwork,
                        ::coder::array<double, 1U> &xwork);

} // namespace internal
} // namespace coder

namespace coder {
namespace internal {
static void merge(::coder::array<int, 1U> &idx, ::coder::array<double, 1U> &x,
                  int offset, int np, int nq, ::coder::array<int, 1U> &iwork,
                  ::coder::array<double, 1U> &xwork)
{
    if (nq != 0) {
        int iout;
        int j;
        int n_tmp;
        int p;
        int q;
        n_tmp = np + nq;
        for (j = 0; j < n_tmp; j++) {
            iout = offset + j;
            iwork[j] = idx[iout];
            xwork[j] = x[iout];
        }
        p = 0;
        q = np;
        iout = offset - 1;
        int exitg1;
        do {
            exitg1 = 0;
            iout++;
            if (xwork[p] <= xwork[q]) {
                idx[iout] = iwork[p];
                x[iout] = xwork[p];
                if (p + 1 < np) {
                    p++;
                } else {
                    exitg1 = 1;
                }
            } else {
                idx[iout] = iwork[q];
                x[iout] = xwork[q];
                if (q + 1 < n_tmp) {
                    q++;
                } else {
                    q = iout - p;
                    for (j = p + 1; j <= np; j++) {
                        iout = q + j;
                        idx[iout] = iwork[j - 1];
                        x[iout] = xwork[j - 1];
                    }
                    exitg1 = 1;
                }
            }
        } while (exitg1 == 0);
    }
}

static void merge(::coder::array<int, 2U> &idx, ::coder::array<double, 2U> &x,
                  int offset, int np, int nq, ::coder::array<int, 1U> &iwork,
                  ::coder::array<double, 1U> &xwork)
{
    if (nq != 0) {
        int iout;
        int j;
        int n_tmp;
        int p;
        int q;
        n_tmp = np + nq;
        for (j = 0; j < n_tmp; j++) {
            iout = offset + j;
            iwork[j] = idx[iout];
            xwork[j] = x[iout];
        }
        p = 0;
        q = np;
        iout = offset - 1;
        int exitg1;
        do {
            exitg1 = 0;
            iout++;
            if (xwork[p] <= xwork[q]) {
                idx[iout] = iwork[p];
                x[iout] = xwork[p];
                if (p + 1 < np) {
                    p++;
                } else {
                    exitg1 = 1;
                }
            } else {
                idx[iout] = iwork[q];
                x[iout] = xwork[q];
                if (q + 1 < n_tmp) {
                    q++;
                } else {
                    q = iout - p;
                    for (j = p + 1; j <= np; j++) {
                        iout = q + j;
                        idx[iout] = iwork[j - 1];
                        x[iout] = xwork[j - 1];
                    }
                    exitg1 = 1;
                }
            }
        } while (exitg1 == 0);
    }
}

static void merge_block(::coder::array<int, 2U> &idx,
                        ::coder::array<double, 2U> &x, int offset, int n,
                        int preSortLevel, ::coder::array<int, 1U> &iwork,
                        ::coder::array<double, 1U> &xwork)
{
    int bLen;
    int nPairs;
    nPairs = n >> preSortLevel;
    bLen = 1 << preSortLevel;
    while (nPairs > 1) {
        int nTail;
        int tailOffset;
        if ((nPairs & 1) != 0) {
            nPairs--;
            tailOffset = bLen * nPairs;
            nTail = n - tailOffset;
            if (nTail > bLen) {
                merge(idx, x, offset + tailOffset, bLen, nTail - bLen, iwork,
                      xwork);
            }
        }
        tailOffset = bLen << 1;
        nPairs >>= 1;
        for (nTail = 0; nTail < nPairs; nTail++) {
            merge(idx, x, offset + nTail * tailOffset, bLen, bLen, iwork,
                  xwork);
        }
        bLen = tailOffset;
    }
    if (n > bLen) {
        merge(idx, x, offset, bLen, n - bLen, iwork, xwork);
    }
}

void b_merge(int idx[200], double x[200], int offset, int np, int nq,
             int iwork[200], double xwork[200])
{
    if (nq != 0) {
        int iout;
        int j;
        int n_tmp;
        int p;
        int q;
        n_tmp = np + nq;
        for (j = 0; j < n_tmp; j++) {
            iout = offset + j;
            iwork[j] = idx[iout];
            xwork[j] = x[iout];
        }
        p = 0;
        q = np;
        iout = offset - 1;
        int exitg1;
        do {
            exitg1 = 0;
            iout++;
            if (xwork[p] <= xwork[q]) {
                idx[iout] = iwork[p];
                x[iout] = xwork[p];
                if (p + 1 < np) {
                    p++;
                } else {
                    exitg1 = 1;
                }
            } else {
                idx[iout] = iwork[q];
                x[iout] = xwork[q];
                if (q + 1 < n_tmp) {
                    q++;
                } else {
                    q = iout - p;
                    for (j = p + 1; j <= np; j++) {
                        iout = q + j;
                        idx[iout] = iwork[j - 1];
                        x[iout] = xwork[j - 1];
                    }
                    exitg1 = 1;
                }
            }
        } while (exitg1 == 0);
    }
}

void merge(int idx[32], double x[32], int offset, int np, int nq, int iwork[32],
           double xwork[32])
{
    if (nq != 0) {
        int iout;
        int j;
        int n_tmp;
        int p;
        int q;
        n_tmp = np + nq;
        for (j = 0; j < n_tmp; j++) {
            iout = offset + j;
            iwork[j] = idx[iout];
            xwork[j] = x[iout];
        }
        p = 0;
        q = np;
        iout = offset - 1;
        int exitg1;
        do {
            exitg1 = 0;
            iout++;
            if (xwork[p] <= xwork[q]) {
                idx[iout] = iwork[p];
                x[iout] = xwork[p];
                if (p + 1 < np) {
                    p++;
                } else {
                    exitg1 = 1;
                }
            } else {
                idx[iout] = iwork[q];
                x[iout] = xwork[q];
                if (q + 1 < n_tmp) {
                    q++;
                } else {
                    q = iout - p;
                    for (j = p + 1; j <= np; j++) {
                        iout = q + j;
                        idx[iout] = iwork[j - 1];
                        x[iout] = xwork[j - 1];
                    }
                    exitg1 = 1;
                }
            }
        } while (exitg1 == 0);
    }
}

void merge_block(::coder::array<int, 1U> &idx, ::coder::array<double, 1U> &x,
                 int offset, int n, int preSortLevel,
                 ::coder::array<int, 1U> &iwork,
                 ::coder::array<double, 1U> &xwork)
{
    int bLen;
    int nPairs;
    nPairs = n >> preSortLevel;
    bLen = 1 << preSortLevel;
    while (nPairs > 1) {
        int nTail;
        int tailOffset;
        if ((nPairs & 1) != 0) {
            nPairs--;
            tailOffset = bLen * nPairs;
            nTail = n - tailOffset;
            if (nTail > bLen) {
                merge(idx, x, offset + tailOffset, bLen, nTail - bLen, iwork,
                      xwork);
            }
        }
        tailOffset = bLen << 1;
        nPairs >>= 1;
        for (nTail = 0; nTail < nPairs; nTail++) {
            merge(idx, x, offset + nTail * tailOffset, bLen, bLen, iwork,
                  xwork);
        }
        bLen = tailOffset;
    }
    if (n > bLen) {
        merge(idx, x, offset, bLen, n - bLen, iwork, xwork);
    }
}

void sortIdx(::coder::array<double, 2U> &x, ::coder::array<int, 2U> &idx)
{
    array<double, 1U> xwork;
    array<int, 1U> iwork;
    double b_xwork[256];
    double x4[4];
    int b_iwork[256];
    int idx4[4];
    int ib;
    int quartetOffset;
    signed char perm[4];
    idx.set_size(1, x.size(1));
    quartetOffset = x.size(1);
    for (ib = 0; ib < quartetOffset; ib++) {
        idx[ib] = 0;
    }
    if (x.size(1) != 0) {
        int bLen;
        int b_n;
        int i2;
        int i3;
        int i4;
        int idx_tmp;
        int k;
        int n;
        int nNonNaN;
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
        for (ib = 0; ib < quartetOffset; ib++) {
            iwork[ib] = 0;
        }
        quartetOffset = x.size(1);
        xwork.set_size(quartetOffset);
        for (ib = 0; ib < quartetOffset; ib++) {
            xwork[ib] = 0.0;
        }
        bLen = 0;
        ib = -1;
        for (k = 0; k < b_n; k++) {
            if (rtIsNaN(x[k])) {
                idx_tmp = (b_n - bLen) - 1;
                idx[idx_tmp] = k + 1;
                xwork[idx_tmp] = x[k];
                bLen++;
            } else {
                ib++;
                idx4[ib] = k + 1;
                x4[ib] = x[k];
                if (ib + 1 == 4) {
                    double d;
                    double d1;
                    quartetOffset = k - bLen;
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
        i3 = (b_n - bLen) - 1;
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
            for (k = 0; k <= ib; k++) {
                idx_tmp = perm[k] - 1;
                quartetOffset = (i3 - ib) + k;
                idx[quartetOffset] = idx4[idx_tmp];
                x[quartetOffset] = x4[idx_tmp];
            }
        }
        ib = (bLen >> 1) + 1;
        for (k = 0; k <= ib - 2; k++) {
            quartetOffset = (i3 + k) + 1;
            i2 = idx[quartetOffset];
            idx_tmp = (b_n - k) - 1;
            idx[quartetOffset] = idx[idx_tmp];
            idx[idx_tmp] = i2;
            x[quartetOffset] = xwork[idx_tmp];
            x[idx_tmp] = xwork[quartetOffset];
        }
        if ((bLen & 1) != 0) {
            ib += i3;
            x[ib] = xwork[ib];
        }
        nNonNaN = n - bLen;
        quartetOffset = 2;
        if (nNonNaN > 1) {
            if (n >= 256) {
                int nBlocks;
                nBlocks = nNonNaN >> 8;
                if (nBlocks > 0) {
                    for (int b = 0; b < nBlocks; b++) {
                        i4 = (b << 8) - 1;
                        for (int b_b = 0; b_b < 6; b_b++) {
                            bLen = 1 << (b_b + 2);
                            b_n = bLen << 1;
                            n = 256 >> (b_b + 3);
                            for (k = 0; k < n; k++) {
                                i2 = (i4 + k * b_n) + 1;
                                for (quartetOffset = 0; quartetOffset < b_n;
                                     quartetOffset++) {
                                    ib = i2 + quartetOffset;
                                    b_iwork[quartetOffset] = idx[ib];
                                    b_xwork[quartetOffset] = x[ib];
                                }
                                i3 = 0;
                                quartetOffset = bLen;
                                ib = i2 - 1;
                                int exitg1;
                                do {
                                    exitg1 = 0;
                                    ib++;
                                    if (b_xwork[i3] <= b_xwork[quartetOffset]) {
                                        idx[ib] = b_iwork[i3];
                                        x[ib] = b_xwork[i3];
                                        if (i3 + 1 < bLen) {
                                            i3++;
                                        } else {
                                            exitg1 = 1;
                                        }
                                    } else {
                                        idx[ib] = b_iwork[quartetOffset];
                                        x[ib] = b_xwork[quartetOffset];
                                        if (quartetOffset + 1 < b_n) {
                                            quartetOffset++;
                                        } else {
                                            ib -= i3;
                                            for (quartetOffset = i3 + 1;
                                                 quartetOffset <= bLen;
                                                 quartetOffset++) {
                                                idx_tmp = ib + quartetOffset;
                                                idx[idx_tmp] =
                                                    b_iwork[quartetOffset - 1];
                                                x[idx_tmp] =
                                                    b_xwork[quartetOffset - 1];
                                            }
                                            exitg1 = 1;
                                        }
                                    }
                                } while (exitg1 == 0);
                            }
                        }
                    }
                    quartetOffset = nBlocks << 8;
                    ib = nNonNaN - quartetOffset;
                    if (ib > 0) {
                        merge_block(idx, x, quartetOffset, ib, 2, iwork, xwork);
                    }
                    quartetOffset = 8;
                }
            }
            merge_block(idx, x, 0, nNonNaN, quartetOffset, iwork, xwork);
        }
    }
}

} // namespace internal
} // namespace coder
