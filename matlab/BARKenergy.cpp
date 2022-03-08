#include "BARKenergy.h"
#include "SnoringRecognition_rtwutil.h"
#include "combineVectorElements.h"
#include "enframe.h"
#include "hamming.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "fftw3.h"
#include "mylock.h"
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
    coder::array<creal_T, 2U> b_x;
    coder::array<creal_T, 2U> d_y;
    coder::array<double, 2U> BPS;
    coder::array<double, 2U> BPSE;
    coder::array<double, 2U> Sr;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> c_y;
    coder::array<double, 2U> freq;
    coder::array<double, 2U> sourfft1;
    coder::array<double, 2U> y;
    coder::array<double, 1U> r;
    coder::array<int, 2U> index_f2;
    coder::array<int, 1U> r1;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
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
    int n;
    int nfft;
    int nx;
    int yk;
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
    yk = y.size(0);
    for (i = 0; i < yk; i++) {
        nx = y.size(1);
        for (i1 = 0; i1 < nx; i1++) {
            b_y[i1 + b_y.size(0) * i] = y[i + y.size(0) * i1];
        }
    }
    nfft = b_y.size(0) + 1;
    if ((b_y.size(0) == 0) || (b_y.size(1) == 0)) {
        b_x.set_size(b_y.size(0), b_y.size(1));
        yk = b_y.size(0) * b_y.size(1);
        for (i = 0; i < yk; i++) {
            b_x[i].re = 0.0;
            b_x[i].im = 0.0;
        }
    } else {
        fftw_plan plan;
        iodims.n = b_y.size(0);
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = b_y.size(1);
        howmany_iodims.is = b_y.size(0);
        howmany_iodims.os = b_y.size(0);
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        b_x.set_size(b_y.size(0), b_y.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&b_y[0],
            (fftw_complex *)&b_x[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        nx = b_y.size(0) / 2;
        if (nx + 2 <= b_y.size(0)) {
            n = b_y.size(1);
            index_f2.set_size(1, b_y.size(1));
            index_f2[0] = 1;
            yk = 1;
            for (k = 2; k <= n; k++) {
                yk++;
                index_f2[k - 1] = yk;
            }
            n = nx + 1;
            yk = index_f2.size(1);
            do {
                nx = nfft - n;
                if (nx == nfft) {
                    nx = 1;
                }
                r1.set_size(index_f2.size(1));
                d_y.set_size(1, index_f2.size(1));
                for (i = 0; i < yk; i++) {
                    i1 = index_f2[i];
                    r1[i] = i1 - 1;
                    d_y[i].re = b_x[(nx + b_x.size(0) * (i1 - 1)) - 1].re;
                    d_y[i].im = -b_x[(nx + b_x.size(0) * (i1 - 1)) - 1].im;
                }
                nx = d_y.size(1);
                for (i = 0; i < nx; i++) {
                    b_x[n + b_x.size(0) * r1[i]] = d_y[i];
                }
                n++;
            } while (!(n + 1 == nfft));
        }
    }
    nx = b_x.size(0) * b_x.size(1);
    y.set_size(b_x.size(0), b_x.size(1));
    for (k = 0; k < nx; k++) {
        y[k] = rt_hypotd_snf(b_x[k].re, b_x[k].im);
    }
    sourfft1.set_size(y.size(1), y.size(0));
    yk = y.size(0);
    for (i = 0; i < yk; i++) {
        nx = y.size(1);
        for (i1 = 0; i1 < nx; i1++) {
            sourfft1[i1 + sourfft1.size(0) * i] = y[i + y.size(0) * i1];
        }
    }
    ds = fs / wlen;
    b = wlen / 2.0;
    if (rtIsNaN(b)) {
        c_y.set_size(1, 1);
        c_y[0] = rtNaN;
    } else if (b < 0.0) {
        c_y.set_size(1, 0);
    } else if (rtIsInf(b) && (0.0 == b)) {
        c_y.set_size(1, 1);
        c_y[0] = rtNaN;
    } else {
        yk = static_cast<int>(floor(b));
        c_y.set_size(1, yk + 1);
        for (i = 0; i <= yk; i++) {
            c_y[i] = i;
        }
    }
    freq.set_size(1, c_y.size(1));
    yk = c_y.size(1);
    for (i = 0; i < yk; i++) {
        freq[i] = c_y[i] * fs / wlen;
    }
    i = b_y.size(1);
    BPS.set_size(b_y.size(1), 17);
    BPSE.set_size(b_y.size(1), 17);
    for (int b_i = 0; b_i < i; b_i++) {
        yk = sourfft1.size(1);
        Sr.set_size(1, sourfft1.size(1));
        for (i1 = 0; i1 < yk; i1++) {
            Sr[i1] = sourfft1[b_i + sourfft1.size(0) * i1];
        }
        for (k = 0; k < 17; k++) {
            double b_Sr;
            double c_x;
            b = static_cast<double>(Fk[k + 25]) / ds;
            if (b < 0.0) {
                b = ceil(b);
            } else {
                b = floor(b);
            }
            c_x = static_cast<double>(Fk[k + 50]) / ds;
            if (c_x < 0.0) {
                c_x = ceil(c_x);
            } else {
                c_x = floor(c_x);
            }
            if (b + 1.0 > c_x + 1.0) {
                i1 = 0;
                nx = 0;
            } else {
                i1 = static_cast<int>(b + 1.0) - 1;
                nx = static_cast<int>(c_x + 1.0);
            }
            b_Sr = 0.0;
            yk = nx - i1;
            for (nx = 0; nx < yk; nx++) {
                double Sr_tmp;
                Sr_tmp = Sr[i1 + nx];
                b_Sr += Sr_tmp * Sr_tmp;
            }
            Srt_en[k] = b_Sr;
            if (b + 1.0 > c_x + 1.0) {
                nx = 0;
                n = 0;
            } else {
                nx = static_cast<int>(b + 1.0) - 1;
                n = static_cast<int>(c_x + 1.0);
            }
            b = 0.0;
            yk = n - nx;
            for (n = 0; n < yk; n++) {
                c_x = Sr[i1 + n];
                b += freq[nx + n] * (c_x * c_x);
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
