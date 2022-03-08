#include "enframe.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <math.h>

void enframe(const coder::array<double, 1U> &x,
             const coder::array<double, 1U> &win, double inc,
             coder::array<double, 2U> &f)
{
    coder::array<double, 2U> inds;
    coder::array<double, 2U> r;
    coder::array<double, 1U> indf;
    double len;
    double nf;
    int i;
    int i1;
    int loop_ub;
    int loop_ub_tmp;
    if (win.size(0) == 1) {
        len = win[0];
    } else {
        len = win.size(0);
    }
    nf = ((static_cast<double>(x.size(0)) - len) + inc) / inc;
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
        loop_ub = static_cast<int>(nf - 1.0);
        for (i = 0; i <= loop_ub; i++) {
            r[i] = i;
        }
    }
    indf.set_size(r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
        indf[i] = inc * r[i];
    }
    if (len < 1.0) {
        inds.set_size(1, 0);
    } else if (rtIsInf(len) && (1.0 == len)) {
        inds.set_size(1, 1);
        inds[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(len - 1.0));
        inds.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            inds[i] = static_cast<double>(i) + 1.0;
        }
    }
    loop_ub = indf.size(0);
    loop_ub_tmp = static_cast<int>(len);
    f.set_size(indf.size(0), loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            f[i1 + f.size(0) * i] = x[static_cast<int>(indf[i1] + inds[i]) - 1];
        }
    }
    if (win.size(0) > 1) {
        loop_ub = f.size(1);
        for (i = 0; i < loop_ub; i++) {
            loop_ub_tmp = f.size(0);
            for (i1 = 0; i1 < loop_ub_tmp; i1++) {
                f[i1 + f.size(0) * i] = f[i1 + f.size(0) * i] * win[i];
            }
        }
    }
}
