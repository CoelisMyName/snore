#include "BARKenergy.h"
#include "FFTImplementationCallback.h"
#include "SnoringRecognition_rtwutil.h"
#include "combineVectorElements.h"
#include "enframe.h"
#include "hamming.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

void BARKenergy(const coder::array<double, 1U> &x, double fs, double BPSEE1[17],
                double BPS1[17], double BPSEE2[17])
{
    static const short Fk[75] = {
        50,    150,   250,   350,  450,   570,   700,   840,   1000, 1170, 1370,
        1600,  1850,  2150,  2500, 2900,  3400,  4000,  4800,  5800, 7000, 8500,
        10500, 13500, 18775, 20,   100,   200,   300,   400,   510,  630,  770,
        920,   1080,  1270,  1480, 1720,  2000,  2320,  2700,  3150, 3700, 4400,
        5300,  6400,  7700,  9500, 12000, 15500, 100,   200,   300,  400,  510,
        630,   770,   920,   1080, 1270,  1480,  1720,  2000,  2320, 2700, 3150,
        3700,  4400,  5300,  6400, 7700,  9500,  12000, 15500, 22050};
    coder::array<creal_T, 2U> c_y;
    coder::array<creal_T, 1U> r1;
    coder::array<double, 2U> BPS;
    coder::array<double, 2U> BPSE;
    coder::array<double, 2U> Sr;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> costab;
    coder::array<double, 2U> freq;
    coder::array<double, 2U> sintab;
    coder::array<double, 2U> sintabinv;
    coder::array<double, 2U> sourfft1;
    coder::array<double, 2U> y;
    coder::array<double, 1U> r;
    double BPS1_tmp_tmp[17];
    double Srt_en[17];
    double y_tmp[17];
    double b;
    double ds;
    double inc;
    double wlen;
    int i;
    int i1;
    int k;
    int loop_ub;
    int nChan;
    int nx;
    wlen = 0.05 * fs;
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
    coder::hamming(wlen, r);
    enframe(x, r, inc, y);
    b_y.set_size(y.size(1), y.size(0));
    loop_ub = y.size(0);
    for (i = 0; i < loop_ub; i++) {
        nChan = y.size(1);
        for (i1 = 0; i1 < nChan; i1++) {
            b_y[i1 + b_y.size(0) * i] = y[i + y.size(0) * i1];
        }
    }
    if ((b_y.size(0) == 0) || (b_y.size(1) == 0)) {
        c_y.set_size(b_y.size(0), b_y.size(1));
        loop_ub = b_y.size(0) * b_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            c_y[i].re = 0.0;
            c_y[i].im = 0.0;
        }
    } else {
        boolean_T useRadix2;
        useRadix2 = ((b_y.size(0) & (b_y.size(0) - 1)) == 0);
        coder::internal::FFTImplementationCallback::get_algo_sizes(
            b_y.size(0), useRadix2, &nx, &nChan);
        coder::internal::FFTImplementationCallback::generate_twiddle_tables(
            nChan, useRadix2, costab, sintab, sintabinv);
        if (useRadix2) {
            nChan = b_y.size(1);
            c_y.set_size(b_y.size(0), b_y.size(1));
            for (nx = 0; nx < nChan; nx++) {
                coder::internal::FFTImplementationCallback::
                    r2br_r2dit_trig_impl(b_y, nx * b_y.size(0), b_y.size(0),
                                         costab, sintab, r1);
                loop_ub = r1.size(0);
                for (i = 0; i < loop_ub; i++) {
                    c_y[i + c_y.size(0) * nx] = r1[i];
                }
            }
        } else {
            coder::internal::FFTImplementationCallback::dobluesteinfft(
                b_y, nx, b_y.size(0), costab, sintab, sintabinv, c_y);
        }
    }
    nx = c_y.size(0) * c_y.size(1);
    y.set_size(c_y.size(0), c_y.size(1));
    for (k = 0; k < nx; k++) {
        y[k] = rt_hypotd_snf(c_y[k].re, c_y[k].im);
    }
    sourfft1.set_size(y.size(1), y.size(0));
    loop_ub = y.size(0);
    for (i = 0; i < loop_ub; i++) {
        nChan = y.size(1);
        for (i1 = 0; i1 < nChan; i1++) {
            sourfft1[i1 + sourfft1.size(0) * i] = y[i + y.size(0) * i1];
        }
    }
    ds = fs / wlen;
    b = wlen / 2.0;
    if (rtIsNaN(b)) {
        costab.set_size(1, 1);
        costab[0] = rtNaN;
    } else if (b < 0.0) {
        costab.set_size(1, 0);
    } else if (rtIsInf(b) && (0.0 == b)) {
        costab.set_size(1, 1);
        costab[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(b));
        costab.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            costab[i] = i;
        }
    }
    freq.set_size(1, costab.size(1));
    loop_ub = costab.size(1);
    for (i = 0; i < loop_ub; i++) {
        freq[i] = costab[i] * fs / wlen;
    }
    i = b_y.size(1);
    BPS.set_size(b_y.size(1), 17);
    BPSE.set_size(b_y.size(1), 17);
    for (int b_i = 0; b_i < i; b_i++) {
        loop_ub = sourfft1.size(1);
        Sr.set_size(1, sourfft1.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            Sr[i1] = sourfft1[b_i + sourfft1.size(0) * i1];
        }
        for (k = 0; k < 17; k++) {
            double b_Sr;
            double b_x;
            b = static_cast<double>(Fk[k + 25]) / ds;
            if (b < 0.0) {
                b = ceil(b);
            } else {
                b = floor(b);
            }
            b_x = static_cast<double>(Fk[k + 50]) / ds;
            if (b_x < 0.0) {
                b_x = ceil(b_x);
            } else {
                b_x = floor(b_x);
            }
            if (b + 1.0 > b_x + 1.0) {
                i1 = 0;
                nx = 0;
            } else {
                i1 = static_cast<int>(b + 1.0) - 1;
                nx = static_cast<int>(b_x + 1.0);
            }
            b_Sr = 0.0;
            loop_ub = nx - i1;
            for (nx = 0; nx < loop_ub; nx++) {
                double Sr_tmp;
                Sr_tmp = Sr[i1 + nx];
                b_Sr += Sr_tmp * Sr_tmp;
            }
            Srt_en[k] = b_Sr;
            if (b + 1.0 > b_x + 1.0) {
                nx = 0;
                nChan = 0;
            } else {
                nx = static_cast<int>(b + 1.0) - 1;
                nChan = static_cast<int>(b_x + 1.0);
            }
            b = 0.0;
            loop_ub = nChan - nx;
            for (nChan = 0; nChan < loop_ub; nChan++) {
                b_x = Sr[i1 + nChan];
                b += freq[nx + nChan] * (b_x * b_x);
            }
            BPS[b_i + BPS.size(0) * k] = b;
            BPSE[b_i + BPSE.size(0) * k] = Srt_en[k];
        }
    }
    coder::combineVectorElements(BPS, BPS1_tmp_tmp);
    b = BPS1_tmp_tmp[0];
    for (k = 0; k < 16; k++) {
        b += BPS1_tmp_tmp[k + 1];
    }
    for (i = 0; i < 17; i++) {
        BPS1[i] = BPS1_tmp_tmp[i] / b;
    }
    coder::combineVectorElements(BPSE, y_tmp);
    b = y_tmp[0];
    for (k = 0; k < 16; k++) {
        b += y_tmp[k + 1];
    }
    for (i = 0; i < 17; i++) {
        BPSEE1[i] = BPS1_tmp_tmp[i] / b;
    }
    b = y_tmp[0];
    for (k = 0; k < 16; k++) {
        b += y_tmp[k + 1];
    }
    for (i = 0; i < 17; i++) {
        BPSEE2[i] = y_tmp[i] / b;
    }
}
