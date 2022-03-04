#include "PR800.h"
#include "FFTImplementationCallback.h"
#include "SnoringRecognition_rtwutil.h"
#include "blockedSummation.h"
#include "enframe.h"
#include "hamming.h"
#include "mean.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "vvarstd.h"
#include "coder_array.h"
#include <math.h>

void PR800(const coder::array<double, 1U> &x, double Fs, double *PR800_mean,
           double *PR800_max, double *PR800_min, double *PR800_var)
{
    coder::array<creal_T, 1U> Z;
    coder::array<double, 2U> b_PR800;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> costab;
    coder::array<double, 2U> r;
    coder::array<double, 2U> sintab;
    coder::array<double, 2U> sintabinv;
    coder::array<double, 1U> b_x;
    coder::array<double, 1U> mag;
    coder::array<double, 1U> y;
    double f1;
    double f2;
    double inc;
    double wlen;
    int b_loop_ub;
    int c_loop_ub;
    int i;
    int i1;
    int i2;
    int i3;
    int i4;
    int i5;
    int loop_ub;
    int nRows;
    int nx;
    wlen = 0.02 * Fs;
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
    coder::hamming(wlen, y);
    enframe(x, y, inc, r);
    b_y.set_size(r.size(1), r.size(0));
    nx = r.size(0);
    for (i = 0; i < nx; i++) {
        nRows = r.size(1);
        for (i1 = 0; i1 < nRows; i1++) {
            b_y[i1 + b_y.size(0) * i] = r[i + r.size(0) * i1];
        }
    }
    double ds;
    b_PR800.set_size(1, b_y.size(1));
    ds = Fs / wlen;
    f1 = 800.0 / ds + 1.0;
    f2 = 8000.0 / ds + 1.0;
    i = b_y.size(1);
    if (0 <= b_y.size(1) - 1) {
        i2 = b_y.size(0);
        loop_ub = b_y.size(0);
        if (1.0 > f1) {
            b_loop_ub = 0;
        } else {
            b_loop_ub = static_cast<int>(f1);
        }
        if (f1 > f2) {
            i3 = 0;
            i4 = 0;
            i5 = 1;
        } else {
            i3 = static_cast<int>(f1) - 1;
            i4 = static_cast<int>(f2);
            i5 = static_cast<int>(f1);
        }
        c_loop_ub = i4 - i3;
    }
    for (int b_i = 0; b_i < i; b_i++) {
        y.set_size(i2);
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1] = b_y[i1 + b_y.size(0) * b_i];
        }
        if (y.size(0) == 0) {
            Z.set_size(0);
        } else {
            boolean_T useRadix2;
            useRadix2 = ((y.size(0) & (y.size(0) - 1)) == 0);
            coder::internal::FFTImplementationCallback::get_algo_sizes(
                y.size(0), useRadix2, &nx, &nRows);
            coder::internal::FFTImplementationCallback::generate_twiddle_tables(
                nRows, useRadix2, costab, sintab, sintabinv);
            if (useRadix2) {
                coder::internal::FFTImplementationCallback::
                    r2br_r2dit_trig_impl(y, y.size(0), costab, sintab, Z);
            } else {
                coder::internal::FFTImplementationCallback::dobluesteinfft(
                    y, nx, y.size(0), costab, sintab, sintabinv, Z);
            }
        }
        nx = Z.size(0);
        mag.set_size(Z.size(0));
        for (nRows = 0; nRows < nx; nRows++) {
            mag[nRows] = rt_hypotd_snf(Z[nRows].re, Z[nRows].im);
        }
        b_x.set_size(b_loop_ub);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            b_x[i1] = mag[i1] * mag[i1];
        }
        y.set_size(i4 - i3);
        for (i1 = 0; i1 < c_loop_ub; i1++) {
            y[i1] = mag[i3 + i1] * mag[(i5 + i1) - 1];
        }
        b_PR800[b_i] = log10(coder::blockedSummation(b_x, b_x.size(0)) /
                             coder::blockedSummation(y, y.size(0)));
    }
    *PR800_mean = coder::mean(b_PR800);
    *PR800_max = coder::internal::maximum(b_PR800);
    *PR800_min = coder::internal::minimum(b_PR800);
    nx = b_PR800.size(1);
    y = b_PR800.reshape(nx);
    *PR800_var = coder::vvarstd(y, b_PR800.size(1));
}
