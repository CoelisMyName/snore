#include "melbankm.h"
#include "colon.h"
#include "find.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

void melbankm(double n, double fs, coder::sparse *x)
{
    coder::array<double, 2U> af;
    coder::array<double, 2U> c;
    coder::array<double, 2U> c_x;
    coder::array<double, 2U> fp;
    coder::array<double, 2U> pf;
    coder::array<double, 2U> pm;
    coder::array<double, 2U> v;
    coder::array<double, 2U> y;
    coder::array<int, 2U> r1;
    coder::array<boolean_T, 2U> b_fp;
    coder::array<boolean_T, 2U> r;
    double b1;
    double b_x;
    double blim_idx_0;
    double d;
    double fn2;
    double k2_data;
    double melinc;
    double mflh;
    double mflh_idx_0;
    int i_size[2];
    int i;
    int i1;
    int idx;
    int k;
    int k2_size_idx_1;
    unsigned int k3_data;
    int loop_ub;
    int nx;
    int nxout;
    boolean_T exitg1;
    fn2 = floor(n / 2.0);
    d = 0.0 * fs;
    b_x = d;
    if (d == 0.0) {
        b_x = 0.0;
    }
    d = b_x * log(d / 700.0 + 1.0) * 1127.01048;
    mflh_idx_0 = d;
    mflh = -d;
    d = 0.5 * fs;
    b_x = d;
    if (d < 0.0) {
        b_x = -1.0;
    } else if (d > 0.0) {
        b_x = 1.0;
    } else if (d == 0.0) {
        b_x = 0.0;
    }
    d = b_x * log(fabs(d) / 700.0 + 1.0) * 1127.01048;
    mflh += d;
    melinc = mflh / 17.0;
    d = mflh_idx_0 + 0.0 * melinc;
    b_x = d;
    if (d == 0.0) {
        b_x = 0.0;
    }
    blim_idx_0 = 700.0 * b_x * (exp(d / 1127.01048) - 1.0) * n / fs;
    d = mflh_idx_0 + 17.0 * melinc;
    b_x = d;
    if (d < 0.0) {
        b_x = -1.0;
    } else if (d > 0.0) {
        b_x = 1.0;
    } else if (d == 0.0) {
        b_x = 0.0;
    }
    b1 = blim_idx_0 + 1.0;
    b_x = ceil(700.0 * b_x * (exp(fabs(d) / 1127.01048) - 1.0) * n / fs);
    if ((fn2 < b_x - 1.0) || rtIsNaN(b_x - 1.0)) {
        mflh = fn2;
    } else {
        mflh = b_x - 1.0;
    }
    if (rtIsNaN(blim_idx_0 + 1.0) || rtIsNaN(mflh)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (mflh < blim_idx_0 + 1.0) {
        y.set_size(y.size(0), 0);
    } else if (rtIsInf(mflh) && (blim_idx_0 + 1.0 == mflh)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
    } else if (blim_idx_0 + 1.0 == blim_idx_0 + 1.0) {
        y.set_size(1, static_cast<int>(mflh - (blim_idx_0 + 1.0)) + 1);
        loop_ub = static_cast<int>(mflh - (blim_idx_0 + 1.0));
        for (i = 0; i <= loop_ub; i++) {
            y[i] = (blim_idx_0 + 1.0) + static_cast<double>(i);
        }
    } else {
        coder::eml_float_colon(blim_idx_0 + 1.0, mflh, y);
    }
    y.set_size(1, y.size(1));
    loop_ub = y.size(1) - 1;
    for (i = 0; i <= loop_ub; i++) {
        y[i] = y[i] * fs / n;
    }
    nx = y.size(1);
    af.set_size(1, y.size(1));
    for (k = 0; k < nx; k++) {
        af[k] = fabs(y[k]);
    }
    nx = y.size(1);
    for (k = 0; k < nx; k++) {
        b_x = y[k];
        if (b_x < 0.0) {
            b_x = -1.0;
        } else if (b_x > 0.0) {
            b_x = 1.0;
        } else if (b_x == 0.0) {
            b_x = 0.0;
        }
        y[k] = b_x;
    }
    c_x.set_size(1, af.size(1));
    loop_ub = af.size(1);
    for (i = 0; i < loop_ub; i++) {
        c_x[i] = af[i] / 700.0 + 1.0;
    }
    nx = c_x.size(1);
    for (k = 0; k < nx; k++) {
        c_x[k] = log(c_x[k]);
    }
    pf.set_size(1, y.size(1));
    loop_ub = y.size(1);
    for (i = 0; i < loop_ub; i++) {
        pf[i] = (y[i] * c_x[i] * 1127.01048 - mflh_idx_0) / melinc;
    }
    if (pf[0] < 0.0) {
        nx = pf.size(1);
        nxout = pf.size(1) - 1;
        for (k = 0; k < nxout; k++) {
            pf[k] = pf[k + 1];
        }
        if (1 > nxout) {
            i = 0;
        } else {
            i = nx - 1;
        }
        pf.set_size(pf.size(0), i);
        b1 = (blim_idx_0 + 1.0) + 1.0;
    }
    if (pf[pf.size(1) - 1] >= 17.0) {
        idx = pf.size(1);
        nx = pf.size(1);
        nxout = pf.size(1) - 1;
        for (k = idx; k <= nxout; k++) {
            pf[k - 1] = pf[k];
        }
        if (1 > nxout) {
            i = 0;
        } else {
            i = nx - 1;
        }
        pf.set_size(pf.size(0), i);
    }
    fp.set_size(1, pf.size(1));
    loop_ub = pf.size(1);
    for (i = 0; i < loop_ub; i++) {
        fp[i] = pf[i];
    }
    nx = pf.size(1);
    for (k = 0; k < nx; k++) {
        fp[k] = floor(fp[k]);
    }
    pm.set_size(1, pf.size(1));
    loop_ub = pf.size(1);
    for (i = 0; i < loop_ub; i++) {
        pm[i] = pf[i] - fp[i];
    }
    b_fp.set_size(1, fp.size(1));
    loop_ub = fp.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_fp[i] = (fp[i] > 0.0);
    }
    coder::eml_find(b_fp, (int *)&nx, i_size);
    k2_size_idx_1 = i_size[1];
    loop_ub = i_size[1];
    for (i = 0; i < loop_ub; i++) {
        k2_data = nx;
    }
    b_fp.set_size(1, fp.size(1));
    loop_ub = fp.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_fp[i] = (fp[i] < 16.0);
    }
    k = (1 <= b_fp.size(1));
    nxout = b_fp.size(1);
    idx = 0;
    i_size[1] = k;
    exitg1 = false;
    while ((!exitg1) && (nxout > 0)) {
        if (b_fp[nxout - 1]) {
            idx = 1;
            nx = nxout;
            exitg1 = true;
        } else {
            nxout--;
        }
    }
    if (k == 1) {
        if (idx == 0) {
            i_size[1] = 0;
        }
    } else {
        i_size[1] = (1 <= idx);
    }
    loop_ub = i_size[1];
    for (i = 0; i < loop_ub; i++) {
        k3_data = static_cast<unsigned int>(nx);
    }
    if (k2_size_idx_1 == 0) {
        k2_data = static_cast<double>(fp.size(1)) + 1.0;
    }
    if (i_size[1] == 0) {
        k3_data = 0U;
        loop_ub = 0;
    } else {
        loop_ub = static_cast<int>(k3_data);
    }
    if (k2_data > fp.size(1)) {
        i = 0;
        i1 = 0;
    } else {
        i = static_cast<int>(k2_data) - 1;
        i1 = fp.size(1);
    }
    if (static_cast<int>(k3_data) < 1) {
        y.set_size(1, 0);
    } else {
        idx = static_cast<int>(k3_data);
        y.set_size(1, idx);
        nx = static_cast<int>(k3_data) - 1;
        for (idx = 0; idx <= nx; idx++) {
            y[idx] = static_cast<double>(idx) + 1.0;
        }
    }
    if (fp.size(1) < k2_data) {
        c_x.set_size(1, 0);
    } else if (k2_data == k2_data) {
        c_x.set_size(1, (fp.size(1) - static_cast<int>(k2_data)) + 1);
        nx = fp.size(1) - static_cast<int>(k2_data);
        for (idx = 0; idx <= nx; idx++) {
            c_x[idx] = k2_data + static_cast<double>(idx);
        }
    } else {
        coder::eml_float_colon(k2_data, static_cast<double>(fp.size(1)), c_x);
    }
    c.set_size(1, y.size(1) + c_x.size(1));
    nx = y.size(1);
    for (idx = 0; idx < nx; idx++) {
        c[idx] = y[idx];
    }
    nx = c_x.size(1);
    for (idx = 0; idx < nx; idx++) {
        c[idx + y.size(1)] = c_x[idx];
    }
    if (1 > static_cast<int>(k3_data)) {
        nx = 0;
    } else {
        nx = static_cast<int>(k3_data);
    }
    if (k2_data > fp.size(1)) {
        idx = 0;
        k2_size_idx_1 = 0;
    } else {
        idx = static_cast<int>(k2_data) - 1;
        k2_size_idx_1 = fp.size(1);
    }
    y.set_size(1, (nx + k2_size_idx_1) - idx);
    for (nxout = 0; nxout < nx; nxout++) {
        y[nxout] = pm[nxout] * 3.1415926535897931;
    }
    nxout = k2_size_idx_1 - idx;
    for (k2_size_idx_1 = 0; k2_size_idx_1 < nxout; k2_size_idx_1++) {
        y[k2_size_idx_1 + nx] =
            (1.0 - pm[idx + k2_size_idx_1]) * 3.1415926535897931;
    }
    nx = y.size(1);
    for (k = 0; k < nx; k++) {
        y[k] = cos(y[k]);
    }
    v.set_size(1, y.size(1));
    nx = y.size(1);
    for (idx = 0; idx < nx; idx++) {
        v[idx] = 0.5 - 0.42592592592592593 * y[idx];
    }
    c_x.set_size(1, c.size(1));
    nx = c.size(1);
    for (idx = 0; idx < nx; idx++) {
        c_x[idx] = c[idx] + (b1 + 1.0);
    }
    b_fp.set_size(1, c_x.size(1));
    nx = c_x.size(1);
    for (idx = 0; idx < nx; idx++) {
        b_fp[idx] = (c_x[idx] > 2.0);
    }
    r.set_size(1, c_x.size(1));
    mflh = (n - fn2) + 2.0;
    nx = c_x.size(1);
    for (idx = 0; idx < nx; idx++) {
        r[idx] = (c_x[idx] < mflh);
    }
    nx = b_fp.size(1) - 1;
    nxout = 0;
    for (idx = 0; idx <= nx; idx++) {
        if (b_fp[idx] && r[idx]) {
            nxout++;
        }
    }
    r1.set_size(1, nxout);
    nxout = 0;
    for (idx = 0; idx <= nx; idx++) {
        if (b_fp[idx] && r[idx]) {
            r1[nxout] = idx + 1;
            nxout++;
        }
    }
    c_x.set_size(1, r1.size(1));
    nx = r1.size(1);
    for (idx = 0; idx < nx; idx++) {
        c_x[idx] = 2.0 * v[r1[idx] - 1];
    }
    nx = b_fp.size(1);
    nxout = 0;
    for (idx = 0; idx < nx; idx++) {
        if (b_fp[idx] && r[idx]) {
            v[idx] = c_x[nxout];
            nxout++;
        }
    }
    c_x.set_size(1, (loop_ub + i1) - i);
    for (idx = 0; idx < loop_ub; idx++) {
        c_x[idx] = fp[idx] + 1.0;
    }
    nx = i1 - i;
    for (i1 = 0; i1 < nx; i1++) {
        c_x[i1 + loop_ub] = fp[i + i1];
    }
    y.set_size(1, c.size(1));
    loop_ub = c.size(1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = (c[i] + (b1 + 1.0)) - 1.0;
    }
    coder::b_sparse(c_x, y, v, fn2 + 1.0, x);
}
