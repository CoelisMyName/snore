#include "HENR.h"
#include "enframe.h"
#include "hanning.h"
#include "mean.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

void HENR(const coder::array<double, 1U> &x, double fs, double *Eh,
          double *En_mean)
{
    coder::array<double, 2U> En;
    coder::array<double, 2U> r1;
    coder::array<double, 2U> y;
    coder::array<double, 1U> r;
    coder::array<boolean_T, 2U> b_x;
    double d;
    double inc;
    double wlen;
    int i;
    int k;
    int nz;
    int vlen;
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
    coder::hanning(wlen, r);
    enframe(x, r, inc, r1);
    y.set_size(r1.size(1), r1.size(0));
    nz = r1.size(0);
    for (k = 0; k < nz; k++) {
        vlen = r1.size(1);
        for (i = 0; i < vlen; i++) {
            y[i + y.size(0) * k] = r1[k + r1.size(0) * i];
        }
    }
    En.set_size(1, y.size(1));
    k = y.size(1);
    for (int b_i = 0; b_i < k; b_i++) {
        double b_y;
        nz = y.size(0);
        b_y = 0.0;
        for (i = 0; i < nz; i++) {
            d = y[i + y.size(0) * b_i];
            b_y += d * d;
        }
        En[b_i] = b_y;
    }
    *En_mean = coder::mean(En);
    b_x.set_size(1, En.size(1));
    d = 0.5 * *En_mean;
    nz = En.size(1);
    for (k = 0; k < nz; k++) {
        b_x[k] = (En[k] > d);
    }
    vlen = b_x.size(1);
    if (b_x.size(1) == 0) {
        nz = 0;
    } else {
        nz = b_x[0];
        for (k = 2; k <= vlen; k++) {
            nz += b_x[k - 1];
        }
    }
    *Eh = static_cast<double>(nz) / static_cast<double>(y.size(1));
}
