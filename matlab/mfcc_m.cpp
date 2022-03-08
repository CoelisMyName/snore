#include "mfcc_m.h"
#include "SnoringRecognition_rtwutil.h"
#include "fft.h"
#include "hamming.h"
#include "melbankm.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

void mfcc_m(const coder::array<double, 1U> &x, double fs, double frameSize,
            double inc, coder::array<double, 2U> &ccc)
{
    static const double b_dv[8] = {0.4708715134557912,  0.74894866958846928,
                                   0.93475388500967427, 1.0,
                                   0.93475388500967427, 0.7489486695884694,
                                   0.47087151345579137, 0.14285714285714296};
    coder::sparse bank;
    coder::array<creal_T, 1U> b_x;
    coder::array<double, 2U> b_bank;
    coder::array<double, 2U> b_xx;
    coder::array<double, 2U> dtm;
    coder::array<double, 2U> inds;
    coder::array<double, 2U> m;
    coder::array<double, 2U> r;
    coder::array<double, 2U> result;
    coder::array<double, 1U> a;
    coder::array<double, 1U> c_x;
    coder::array<double, 1U> indf;
    coder::array<double, 1U> t;
    coder::array<double, 1U> xx;
    double dctcoef[128];
    double y_data[16];
    double maxval;
    double nf;
    int b_i;
    int cend;
    int i;
    int i1;
    int idx;
    int inner;
    int k;
    int loop_ub;
    int naxpy;
    int nx;
    signed char input_sizes_idx_1;
    signed char sizes_idx_1;
    boolean_T empty_non_axis_sizes;
    melbankm(frameSize, fs, &bank);
    b_bank.set_size(16, bank.n);
    naxpy = bank.n << 4;
    for (i = 0; i < naxpy; i++) {
        b_bank[i] = 0.0;
    }
    i = bank.n;
    for (naxpy = 0; naxpy < i; naxpy++) {
        cend = bank.colidx[naxpy + 1] - 1;
        nx = bank.colidx[naxpy];
        for (idx = nx; idx <= cend; idx++) {
            b_bank[(bank.rowidx[idx - 1] + 16 * naxpy) - 1] = bank.d[idx - 1];
        }
    }
    coder::array<double, 1U> c_bank;
    cend = b_bank.size(1) << 4;
    c_bank = b_bank.reshape(cend);
    maxval = coder::internal::maximum(c_bank);
    naxpy = 16 * b_bank.size(1);
    b_bank.set_size(16, b_bank.size(1));
    for (i = 0; i < naxpy; i++) {
        b_bank[i] = b_bank[i] / maxval;
    }
    for (k = 0; k < 8; k++) {
        for (cend = 0; cend < 16; cend++) {
            dctcoef[k + (cend << 3)] =
                cos(static_cast<double>((2 * cend + 1) * (k + 1)) *
                    3.1415926535897931 / 32.0);
        }
    }
    nx = x.size(0);
    xx.set_size(x.size(0));
    naxpy = x.size(0);
    for (i = 0; i < naxpy; i++) {
        xx[i] = 0.0;
    }
    if (x.size(0) >= 4) {
        for (k = 0; k < 2; k++) {
            cend = k + 1;
            for (idx = cend; idx <= nx; idx++) {
                xx[idx - 1] =
                    xx[idx - 1] +
                    (-1.9375 * static_cast<double>(k) + 1.0) * x[(idx - k) - 1];
            }
        }
    } else {
        if (x.size(0) > 2) {
            cend = 0;
        } else {
            cend = -1;
        }
        for (k = 0; k <= cend; k++) {
            xx[0] = xx[0] + x[0];
            xx[1] = xx[1] + x[0] * -0.9375;
        }
        naxpy = x.size(0) - cend;
        i = cend + 2;
        for (k = i; k <= nx; k++) {
            for (idx = 0; idx <= naxpy - 2; idx++) {
                cend = (k + idx) - 1;
                xx[cend] =
                    xx[cend] +
                    x[k - 1] * (-1.9375 * static_cast<double>(idx) + 1.0);
            }
            naxpy--;
        }
    }
    nf = ((static_cast<double>(xx.size(0)) - frameSize) + inc) / inc;
    if (nf < 0.0) {
        nf = ceil(nf);
    } else {
        nf = floor(nf);
    }
    if (nf - 1.0 < 0.0) {
        r.set_size(1, 0);
    } else if (rtIsInf(nf - 1.0) && (0.0 == nf - 1.0)) {
        r.set_size(1, 1);
        r[0] = rtNaN;
    } else {
        r.set_size(1, static_cast<int>(nf - 1.0) + 1);
        naxpy = static_cast<int>(nf - 1.0);
        for (i = 0; i <= naxpy; i++) {
            r[i] = i;
        }
    }
    indf.set_size(r.size(1));
    naxpy = r.size(1);
    for (i = 0; i < naxpy; i++) {
        indf[i] = inc * r[i];
    }
    if (frameSize < 1.0) {
        inds.set_size(1, 0);
    } else if (rtIsInf(frameSize) && (1.0 == frameSize)) {
        inds.set_size(1, 1);
        inds[0] = rtNaN;
    } else {
        naxpy = static_cast<int>(floor(frameSize - 1.0));
        inds.set_size(1, naxpy + 1);
        for (i = 0; i <= naxpy; i++) {
            inds[i] = static_cast<double>(i) + 1.0;
        }
    }
    naxpy = indf.size(0);
    cend = static_cast<int>(frameSize);
    b_xx.set_size(indf.size(0), cend);
    for (i = 0; i < cend; i++) {
        for (nx = 0; nx < naxpy; nx++) {
            b_xx[nx + b_xx.size(0) * i] =
                xx[static_cast<int>(indf[nx] + inds[i]) - 1];
        }
    }
    m.set_size(indf.size(0), 8);
    naxpy = indf.size(0) << 3;
    for (i = 0; i < naxpy; i++) {
        m[i] = 0.0;
    }
    i = indf.size(0);
    if (0 <= indf.size(0) - 1) {
        i1 = static_cast<int>(frameSize);
        loop_ub = static_cast<int>(frameSize);
        inner = b_bank.size(1);
    }
    for (b_i = 0; b_i < i; b_i++) {
        coder::hamming(frameSize, a);
        xx.set_size(i1);
        for (nx = 0; nx < loop_ub; nx++) {
            xx[nx] = b_xx[b_i + b_xx.size(0) * nx] * a[nx];
        }
        coder::fft(xx, b_x);
        nx = b_x.size(0);
        t.set_size(b_x.size(0));
        for (k = 0; k < nx; k++) {
            t[k] = rt_hypotd_snf(b_x[k].re, b_x[k].im);
        }
        a.set_size(t.size(0));
        naxpy = t.size(0);
        for (nx = 0; nx < naxpy; nx++) {
            a[nx] = t[nx];
        }
        cend = t.size(0);
        for (k = 0; k < cend; k++) {
            t[k] = a[k] * a[k];
        }
        memset(&y_data[0], 0, 16U * sizeof(double));
        for (k = 0; k < inner; k++) {
            cend = k << 4;
            for (idx = 0; idx < 16; idx++) {
                y_data[idx] += b_bank[cend + idx] * t[k];
            }
        }
        c_x.set_size(16);
        for (k = 0; k < 16; k++) {
            c_x[k] = log(y_data[k]);
        }
        for (nx = 0; nx < 8; nx++) {
            maxval = 0.0;
            for (cend = 0; cend < 16; cend++) {
                maxval += dctcoef[nx + (cend << 3)] * c_x[cend];
            }
            m[b_i + m.size(0) * nx] = maxval * b_dv[nx];
        }
    }
    dtm.set_size(m.size(0), 8);
    naxpy = m.size(0) << 3;
    for (i = 0; i < naxpy; i++) {
        dtm[i] = 0.0;
    }
    i = m.size(0);
    for (b_i = 0; b_i <= i - 5; b_i++) {
        for (nx = 0; nx < 8; nx++) {
            dtm[(b_i + dtm.size(0) * nx) + 2] =
                ((-2.0 * m[b_i + m.size(0) * nx] -
                  m[(b_i + m.size(0) * nx) + 1]) +
                 m[(b_i + m.size(0) * nx) + 3]) +
                2.0 * m[(b_i + m.size(0) * nx) + 4];
        }
    }
    naxpy = dtm.size(0) * 8;
    dtm.set_size(dtm.size(0), 8);
    for (i = 0; i < naxpy; i++) {
        dtm[i] = dtm[i] / 3.0;
    }
    if (m.size(0) != 0) {
        cend = m.size(0);
    } else if (dtm.size(0) != 0) {
        cend = dtm.size(0);
    } else {
        cend = 0;
    }
    empty_non_axis_sizes = (cend == 0);
    if (empty_non_axis_sizes || (m.size(0) != 0)) {
        input_sizes_idx_1 = 8;
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (dtm.size(0) != 0)) {
        sizes_idx_1 = 8;
    } else {
        sizes_idx_1 = 0;
    }
    result.set_size(cend, input_sizes_idx_1 + sizes_idx_1);
    naxpy = input_sizes_idx_1;
    for (i = 0; i < naxpy; i++) {
        for (nx = 0; nx < cend; nx++) {
            result[nx + result.size(0) * i] = m[nx + m.size(0) * i];
        }
    }
    naxpy = sizes_idx_1;
    for (i = 0; i < naxpy; i++) {
        for (nx = 0; nx < cend; nx++) {
            result[nx + result.size(0) * (i + input_sizes_idx_1)] =
                dtm[nx + cend * i];
        }
    }
    if (3 > m.size(0) - 2) {
        i = 0;
        nx = 0;
    } else {
        i = 2;
        nx = m.size(0) - 2;
    }
    naxpy = result.size(1);
    loop_ub = nx - i;
    ccc.set_size(loop_ub, result.size(1));
    for (nx = 0; nx < naxpy; nx++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            ccc[i1 + ccc.size(0) * nx] = result[(i + i1) + result.size(0) * nx];
        }
    }
}
