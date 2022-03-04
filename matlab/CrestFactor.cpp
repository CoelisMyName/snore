#include "CrestFactor.h"
#include "blockedSummation.h"
#include "enframe.h"
#include "hamming.h"
#include "mean.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "coder_array.h"
#include <math.h>

double CrestFactor(const coder::array<double, 1U> &x, double fs)
{
    coder::array<double, 2U> Crest_Factor;
    coder::array<double, 2U> r;
    coder::array<double, 2U> y;
    coder::array<double, 1U> V90th;
    coder::array<double, 1U> b_x;
    double inc;
    double wlen;
    int i;
    int i1;
    int k;
    int loop_ub;
    wlen = 0.02 * fs;
    if (wlen < 0.0) {
        wlen = ceil(wlen);
    } else {
        wlen = floor(wlen);
    }
    inc = 0.5 * wlen;
    if (inc < 0.0) {
        inc = ceil(inc);
    } else {
        inc = floor(inc);
    }
    coder::hamming(wlen, b_x);
    enframe(x, b_x, inc, r);
    y.set_size(r.size(1), r.size(0));
    loop_ub = r.size(0);
    for (i = 0; i < loop_ub; i++) {
        k = r.size(1);
        for (i1 = 0; i1 < k; i1++) {
            y[i1 + y.size(0) * i] = r[i + r.size(0) * i1];
        }
    }
    Crest_Factor.set_size(1, y.size(1));
    i = y.size(1);
    for (int b_i = 0; b_i < i; b_i++) {
        double d;
        double x_tmp;
        i1 = y.size(0) - 1;
        V90th.set_size(y.size(0));
        for (k = 0; k <= i1; k++) {
            V90th[k] = fabs(y[k + y.size(0) * b_i]);
        }
        coder::internal::sort(V90th);
        d = static_cast<double>(V90th.size(0)) -
            floor(static_cast<double>(V90th.size(0)) * 0.1);
        i1 = static_cast<int>(floor(static_cast<double>(V90th.size(0)) * 0.1));
        x_tmp = static_cast<double>(V90th.size(0)) -
                floor(static_cast<double>(V90th.size(0)) * 0.1);
        if (i1 > x_tmp) {
            i1 = 0;
            k = 0;
        } else {
            i1--;
            k = static_cast<int>(x_tmp);
        }
        loop_ub = k - i1;
        b_x.set_size(loop_ub);
        for (k = 0; k < loop_ub; k++) {
            x_tmp = V90th[i1 + k];
            b_x[k] = x_tmp * x_tmp;
        }
        if (1.0 > d) {
            i1 = 0;
        } else {
            i1 = static_cast<int>(d);
        }
        V90th.set_size(i1);
        Crest_Factor[b_i] = coder::internal::maximum(V90th) /
                            sqrt(coder::blockedSummation(b_x, b_x.size(0)) /
                                 static_cast<double>(b_x.size(0)));
    }
    return coder::mean(Crest_Factor);
}
