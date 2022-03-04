#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <string.h>

namespace coder {
namespace internal {
void sort(::coder::array<double, 2U> &x, ::coder::array<int, 2U> &idx)
{
    sortIdx(x, idx);
}

void sort(::coder::array<double, 2U> &x)
{
    array<int, 2U> idx;
    double b_x[32];
    double xwork[32];
    double x4[4];
    int b_idx[32];
    int iwork[32];
    int i2;
    int ib;
    int nVectors;
    signed char idx4[4];
    signed char perm[4];
    nVectors = x.size(1);
    ib = x.size(1);
    idx.set_size(32, ib);
    ib <<= 5;
    for (i2 = 0; i2 < ib; i2++) {
        idx[i2] = 0;
    }
    if (x.size(1) != 0) {
        for (int k = 0; k < nVectors; k++) {
            int b_k;
            int i1;
            int i3;
            int nNaNs;
            x4[0] = 0.0;
            idx4[0] = 0;
            x4[1] = 0.0;
            idx4[1] = 0;
            x4[2] = 0.0;
            idx4[2] = 0;
            x4[3] = 0.0;
            idx4[3] = 0;
            for (ib = 0; ib < 32; ib++) {
                b_idx[ib] = idx[ib + 32 * k];
                b_x[ib] = x[ib + 32 * k];
                xwork[ib] = 0.0;
            }
            nNaNs = 0;
            ib = 0;
            for (b_k = 0; b_k < 32; b_k++) {
                if (rtIsNaN(b_x[b_k])) {
                    b_idx[31 - nNaNs] = b_k + 1;
                    xwork[31 - nNaNs] = b_x[b_k];
                    nNaNs++;
                } else {
                    ib++;
                    idx4[ib - 1] = static_cast<signed char>(b_k + 1);
                    x4[ib - 1] = b_x[b_k];
                    if (ib == 4) {
                        double d;
                        double d1;
                        int i4;
                        ib = b_k - nNaNs;
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
                        b_idx[ib - 3] = idx4[perm[0] - 1];
                        b_idx[ib - 2] = idx4[perm[1] - 1];
                        b_idx[ib - 1] = idx4[perm[2] - 1];
                        b_idx[ib] = idx4[perm[3] - 1];
                        b_x[ib - 3] = x4[perm[0] - 1];
                        b_x[ib - 2] = x4[perm[1] - 1];
                        b_x[ib - 1] = x4[perm[2] - 1];
                        b_x[ib] = x4[perm[3] - 1];
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
                for (b_k = 0; b_k < ib; b_k++) {
                    i2 = perm[b_k] - 1;
                    i1 = ((b_k - nNaNs) - ib) + 32;
                    b_idx[i1] = idx4[i2];
                    b_x[i1] = x4[i2];
                }
            }
            ib = (nNaNs >> 1) + 32;
            for (b_k = 0; b_k <= ib - 33; b_k++) {
                i2 = (b_k - nNaNs) + 32;
                i1 = b_idx[i2];
                b_idx[i2] = b_idx[31 - b_k];
                b_idx[31 - b_k] = i1;
                b_x[i2] = xwork[31 - b_k];
                b_x[31 - b_k] = xwork[i2];
            }
            if ((nNaNs & 1) != 0) {
                ib -= nNaNs;
                b_x[ib] = xwork[ib];
            }
            if (32 - nNaNs > 1) {
                memset(&iwork[0], 0, 32U * sizeof(int));
                i3 = (32 - nNaNs) >> 2;
                i1 = 4;
                while (i3 > 1) {
                    if ((i3 & 1) != 0) {
                        i3--;
                        ib = i1 * i3;
                        i2 = 32 - (nNaNs + ib);
                        if (i2 > i1) {
                            merge(b_idx, b_x, ib, i1, i2 - i1, iwork, xwork);
                        }
                    }
                    ib = i1 << 1;
                    i3 >>= 1;
                    for (b_k = 0; b_k < i3; b_k++) {
                        merge(b_idx, b_x, b_k * ib, i1, i1, iwork, xwork);
                    }
                    i1 = ib;
                }
                if (32 - nNaNs > i1) {
                    merge(b_idx, b_x, 0, i1, 32 - (nNaNs + i1), iwork, xwork);
                }
            }
            for (i2 = 0; i2 < 32; i2++) {
                idx[i2 + 32 * k] = b_idx[i2];
                x[i2 + 32 * k] = b_x[i2];
            }
        }
    }
}

void sort(double x[200])
{
    double xwork[200];
    double x4[4];
    int idx[200];
    int iwork[200];
    int i1;
    int i2;
    int i3;
    int ib;
    int k;
    int nNaNs;
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
    memset(&idx[0], 0, 200U * sizeof(int));
    memset(&xwork[0], 0, 200U * sizeof(double));
    nNaNs = 0;
    ib = 0;
    for (k = 0; k < 200; k++) {
        if (rtIsNaN(x[k])) {
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
                ib = k - nNaNs;
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
                idx[ib - 3] = idx4[perm[0] - 1];
                idx[ib - 2] = idx4[perm[1] - 1];
                idx[ib - 1] = idx4[perm[2] - 1];
                idx[ib] = idx4[perm[3] - 1];
                x[ib - 3] = x4[perm[0] - 1];
                x[ib - 2] = x4[perm[1] - 1];
                x[ib - 1] = x4[perm[2] - 1];
                x[ib] = x4[perm[3] - 1];
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
        for (k = 0; k < ib; k++) {
            i2 = perm[k] - 1;
            i1 = ((k - nNaNs) - ib) + 200;
            idx[i1] = idx4[i2];
            x[i1] = x4[i2];
        }
    }
    ib = (nNaNs >> 1) + 200;
    for (k = 0; k <= ib - 201; k++) {
        i2 = (k - nNaNs) + 200;
        i1 = idx[i2];
        idx[i2] = idx[199 - k];
        idx[199 - k] = i1;
        x[i2] = xwork[199 - k];
        x[199 - k] = xwork[i2];
    }
    if ((nNaNs & 1) != 0) {
        ib -= nNaNs;
        x[ib] = xwork[ib];
    }
    if (200 - nNaNs > 1) {
        memset(&iwork[0], 0, 200U * sizeof(int));
        i3 = (200 - nNaNs) >> 2;
        i1 = 4;
        while (i3 > 1) {
            if ((i3 & 1) != 0) {
                i3--;
                ib = i1 * i3;
                i2 = 200 - (nNaNs + ib);
                if (i2 > i1) {
                    b_merge(idx, x, ib, i1, i2 - i1, iwork, xwork);
                }
            }
            ib = i1 << 1;
            i3 >>= 1;
            for (k = 0; k < i3; k++) {
                b_merge(idx, x, k * ib, i1, i1, iwork, xwork);
            }
            i1 = ib;
        }
        if (200 - nNaNs > i1) {
            b_merge(idx, x, 0, i1, 200 - (nNaNs + i1), iwork, xwork);
        }
    }
}

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
    for (int j = 0; j < vstride; j++) {
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
                if (rtIsNaN(vwork[k])) {
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
                        for (int b = 0; b < nBlocks; b++) {
                            i4 = (b << 8) - 1;
                            for (int b_b = 0; b_b < 6; b_b++) {
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
                                                for (i1 = i3 + 1; i1 <= bLen;
                                                     i1++) {
                                                    iidx_tmp = dim + i1;
                                                    iidx[iidx_tmp] =
                                                        c_iwork[i1 - 1];
                                                    vwork[iidx_tmp] =
                                                        c_xwork[i1 - 1];
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

void sort(double x_data[], int x_size[2])
{
    array<double, 2U> x;
    array<int, 2U> b_x;
    int i;
    int loop_ub;
    x.set_size(1, x_size[1]);
    loop_ub = x_size[1];
    for (i = 0; i < loop_ub; i++) {
        x[i] = x_data[i];
    }
    sortIdx(x, b_x);
    x_size[0] = 1;
    x_size[1] = x.size(1);
    loop_ub = x.size(1);
    for (i = 0; i < loop_ub; i++) {
        x_data[i] = x[i];
    }
}

} // namespace internal
} // namespace coder
