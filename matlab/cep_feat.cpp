#include "cep_feat.h"
#include "SnoringRecognition_rtwutil.h"
#include "any1.h"
#include "asinh.h"
#include "deltas.h"
#include "dolpc.h"
#include "fft.h"
#include "filter.h"
#include "hanning.h"
#include "lpc2spec.h"
#include "mean.h"
#include "mod.h"
#include "mtimes.h"
#include "postaud.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

void cep_feat(const coder::array<double, 1U> &sig, double fs, double cep_data[],
              int cep_size[2])
{
    static const double b_dv[169] = {1.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     1.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     1.515716566510398,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     1.9331820449317627,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     2.2973967099940698,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     2.626527804403767,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     2.9301560515835217,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     3.2140958497160383,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     3.4822022531844965,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     3.7371928188465517,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     3.9810717055349722,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     4.2153691330919,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     0.0,
                                     4.44128606984584};
    coder::array<creal_T, 2U> d_y;
    coder::array<creal_T, 2U> e_y;
    coder::array<double, 2U> F;
    coder::array<double, 2U> M;
    coder::array<double, 2U> WINDOW;
    coder::array<double, 2U> aspectrum;
    coder::array<double, 2U> b_WINDOW;
    coder::array<double, 2U> b_cep2;
    coder::array<double, 2U> b_select;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> binbarks;
    coder::array<double, 2U> c;
    coder::array<double, 2U> c_y;
    coder::array<double, 2U> cep2;
    coder::array<double, 2U> colindex;
    coder::array<double, 2U> ddel;
    coder::array<double, 2U> del;
    coder::array<double, 2U> ex;
    coder::array<double, 2U> f_y;
    coder::array<double, 2U> lpcas;
    coder::array<double, 2U> postspectrum;
    coder::array<double, 2U> pspectrum;
    coder::array<double, 2U> sum;
    coder::array<double, 2U> wts;
    coder::array<double, 2U> x;
    coder::array<double, 1U> rowindex;
    coder::array<double, 1U> y;
    double b_b[52];
    double c_b[52];
    double tmp_data[39];
    double b;
    double d;
    double min_bark;
    double ncol;
    double nfft;
    double nfilts;
    double nyqbark;
    double s;
    double step_barks;
    double winpts;
    int b_i;
    int i;
    int ibmat;
    int j;
    int k;
    int n;
    int nx;
    int outsize_idx_0;
    signed char b_input_sizes_idx_0;
    signed char input_sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    winpts = rt_roundd_snf(0.025 * fs);
    coder::hanning(winpts, y);
    WINDOW.set_size(1, y.size(0));
    j = y.size(0);
    for (i = 0; i < j; i++) {
        WINDOW[i] = y[i];
    }
    s = winpts - rt_roundd_snf(0.01 * fs);
    y.set_size(sig.size(0));
    j = sig.size(0);
    for (i = 0; i < j; i++) {
        y[i] = sig[i] * 32768.0;
    }
    nfft = rt_roundd_snf(
        rt_powd_snf(2.0, ceil(log(winpts) / 0.69314718055994529)));
    nx = y.size(0);
    if (y.size(0) < WINDOW.size(1)) {
        y[WINDOW.size(1) - 1] = 0.0;
        nx = WINDOW.size(1);
    }
    ncol = (static_cast<double>(nx) - s) /
           (static_cast<double>(WINDOW.size(1)) - s);
    if (ncol < 0.0) {
        ncol = ceil(ncol);
    } else {
        ncol = floor(ncol);
    }
    if (rtIsNaN(ncol - 1.0)) {
        b_y.set_size(1, 1);
        b_y[0] = rtNaN;
    } else if (ncol - 1.0 < 0.0) {
        b_y.set_size(1, 0);
    } else if (rtIsInf(ncol - 1.0) && (0.0 == ncol - 1.0)) {
        b_y.set_size(1, 1);
        b_y[0] = rtNaN;
    } else {
        b_y.set_size(1, static_cast<int>(ncol - 1.0) + 1);
        j = static_cast<int>(ncol - 1.0);
        for (i = 0; i <= j; i++) {
            b_y[i] = i;
        }
    }
    b = static_cast<double>(WINDOW.size(1)) - s;
    colindex.set_size(1, b_y.size(1));
    j = b_y.size(1);
    for (i = 0; i < j; i++) {
        colindex[i] = b_y[i] * b + 1.0;
    }
    if (WINDOW.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        b_y.set_size(1, WINDOW.size(1));
        j = WINDOW.size(1) - 1;
        for (i = 0; i <= j; i++) {
            b_y[i] = static_cast<double>(i) + 1.0;
        }
    }
    rowindex.set_size(b_y.size(1));
    j = b_y.size(1);
    for (i = 0; i < j; i++) {
        rowindex[i] = b_y[i];
    }
    d = colindex[static_cast<int>(ncol) - 1];
    if (y.size(0) < (static_cast<double>(WINDOW.size(1)) + d) - 1.0) {
        y[static_cast<int>((static_cast<double>(WINDOW.size(1)) + d) - 1.0) -
          1] = 0.0;
    }
    j = rowindex.size(0);
    c_y.set_size(rowindex.size(0), static_cast<int>(ncol));
    k = static_cast<int>(ncol);
    for (i = 0; i < k; i++) {
        for (n = 0; n < j; n++) {
            c_y[n + c_y.size(0) * i] =
                y[static_cast<int>((rowindex[n] + colindex[i]) - 1.0) - 1];
        }
    }
    j = WINDOW.size(1);
    b_WINDOW.set_size(WINDOW.size(1), static_cast<int>(ncol));
    k = static_cast<int>(ncol);
    for (i = 0; i < k; i++) {
        for (n = 0; n < j; n++) {
            b_WINDOW[n + b_WINDOW.size(0) * i] =
                WINDOW[n] * c_y[n + c_y.size(0) * i];
        }
    }
    coder::fft(b_WINDOW, nfft, d_y);
    j = y.size(0);
    for (i = 0; i < j; i++) {
        y[i] = 0.0;
    }
    if (!coder::any(y)) {
        if (coder::b_mod(nfft) != 0.0) {
            b = (nfft + 1.0) / 2.0;
            if (rtIsNaN(b)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else if (b < 1.0) {
                b_select.set_size(1, 0);
            } else if (rtIsInf(b) && (1.0 == b)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else {
                j = static_cast<int>(floor(b - 1.0));
                b_select.set_size(1, j + 1);
                for (i = 0; i <= j; i++) {
                    b_select[i] = static_cast<double>(i) + 1.0;
                }
            }
        } else {
            b = nfft / 2.0 + 1.0;
            if (rtIsNaN(b)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else if (rtIsInf(b) && (1.0 == b)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else {
                j = static_cast<int>(floor(b - 1.0));
                b_select.set_size(1, j + 1);
                for (i = 0; i <= j; i++) {
                    b_select[i] = static_cast<double>(i) + 1.0;
                }
            }
        }
        ibmat = d_y.size(1) - 1;
        e_y.set_size(b_select.size(1), d_y.size(1));
        for (i = 0; i <= ibmat; i++) {
            j = b_select.size(1);
            for (n = 0; n < j; n++) {
                e_y[n + e_y.size(0) * i] =
                    d_y[(static_cast<int>(b_select[n]) + d_y.size(0) * i) - 1];
            }
        }
        d_y.set_size(e_y.size(0), e_y.size(1));
        j = e_y.size(0) * e_y.size(1);
        for (i = 0; i < j; i++) {
            d_y[i] = e_y[i];
        }
    }
    nx = d_y.size(0) * d_y.size(1);
    c_y.set_size(d_y.size(0), d_y.size(1));
    for (k = 0; k < nx; k++) {
        c_y[k] = rt_hypotd_snf(d_y[k].re, d_y[k].im);
    }
    b_WINDOW.set_size(c_y.size(0), c_y.size(1));
    nx = c_y.size(0) * c_y.size(1);
    for (k = 0; k < nx; k++) {
        b_WINDOW[k] = c_y[k] * c_y[k];
    }
    pspectrum.set_size(b_WINDOW.size(0), b_WINDOW.size(1));
    j = b_WINDOW.size(0) * b_WINDOW.size(1);
    for (i = 0; i < j; i++) {
        pspectrum[i] = b_WINDOW[i] + winpts;
    }
    d = fs / 2.0 / 600.0;
    s = d;
    coder::internal::scalar::b_asinh(&s);
    b = ceil(6.0 * s);
    nfilts = b + 1.0;
    nfft = (static_cast<double>(pspectrum.size(0)) - 1.0) * 2.0;
    s = 0.0;
    coder::internal::scalar::b_asinh(&s);
    min_bark = 6.0 * s;
    coder::internal::scalar::b_asinh(&d);
    nyqbark = 6.0 * d - min_bark;
    if (b + 1.0 == 0.0) {
        nfilts = ceil(nyqbark) + 1.0;
    }
    i = static_cast<int>(nfilts);
    wts.set_size(i, static_cast<int>(nfft));
    j = static_cast<int>(nfilts) * static_cast<int>(nfft);
    for (n = 0; n < j; n++) {
        wts[n] = 0.0;
    }
    step_barks = nyqbark / (nfilts - 1.0);
    j = static_cast<int>(floor(nfft / 2.0));
    b_y.set_size(1, j + 1);
    for (n = 0; n <= j; n++) {
        b_y[n] = n;
    }
    b_y.set_size(1, b_y.size(1));
    j = b_y.size(1) - 1;
    for (n = 0; n <= j; n++) {
        b_y[n] = b_y[n] * fs / nfft / 600.0;
    }
    nx = b_y.size(1);
    for (k = 0; k < nx; k++) {
        coder::internal::scalar::b_asinh(&b_y[k]);
    }
    binbarks.set_size(1, b_y.size(1));
    j = b_y.size(1);
    for (n = 0; n < j; n++) {
        binbarks[n] = 6.0 * b_y[n];
    }
    for (b_i = 0; b_i < i; b_i++) {
        double f_bark_mid;
        f_bark_mid =
            min_bark + ((static_cast<double>(b_i) + 1.0) - 1.0) * step_barks;
        b_y.set_size(1, binbarks.size(1));
        j = binbarks.size(1);
        for (n = 0; n < j; n++) {
            b_y[n] = binbarks[n] - f_bark_mid;
        }
        x.set_size(2, b_y.size(1));
        j = b_y.size(1);
        for (n = 0; n < j; n++) {
            x[2 * n] = b_y[n] + 0.5;
        }
        j = b_y.size(1);
        for (n = 0; n < j; n++) {
            x[2 * n + 1] = -2.5 * (b_y[n] - 0.5);
        }
        n = x.size(1);
        b_y.set_size(1, x.size(1));
        for (j = 0; j < n; j++) {
            s = x[2 * j];
            b_y[j] = s;
            b = x[2 * j + 1];
            if (rtIsNaN(b)) {
                empty_non_axis_sizes = false;
            } else if (rtIsNaN(s)) {
                empty_non_axis_sizes = true;
            } else {
                empty_non_axis_sizes = (s > b);
            }
            if (empty_non_axis_sizes) {
                b_y[j] = b;
            }
        }
        ex.set_size(1, b_y.size(1));
        nx = b_y.size(1);
        for (k = 0; k < nx; k++) {
            d = b_y[k];
            if ((0.0 < d) || rtIsNaN(d)) {
                ex[k] = 0.0;
            } else {
                ex[k] = d;
            }
        }
        b_y.set_size(1, ex.size(1));
        nx = ex.size(1);
        for (k = 0; k < nx; k++) {
            b_y[k] = rt_powd_snf(10.0, ex[k]);
        }
        j = b_y.size(1);
        for (n = 0; n < j; n++) {
            wts[b_i + wts.size(0) * n] = b_y[n];
        }
    }
    if (1 > pspectrum.size(0)) {
        j = 0;
    } else {
        j = pspectrum.size(0);
    }
    ibmat = wts.size(0) - 1;
    k = wts.size(0);
    for (i = 0; i < j; i++) {
        for (n = 0; n < k; n++) {
            wts[n + (ibmat + 1) * i] = wts[n + wts.size(0) * i];
        }
    }
    wts.set_size(ibmat + 1, j);
    coder::internal::blas::mtimes(wts, pspectrum, aspectrum);
    postaud(aspectrum, fs / 2.0, postspectrum);
    dolpc(postspectrum, lpcas);
    c.set_size(13, lpcas.size(1));
    j = 13 * lpcas.size(1);
    for (i = 0; i < j; i++) {
        c[i] = 0.0;
    }
    j = lpcas.size(1);
    b_y.set_size(1, lpcas.size(1));
    for (i = 0; i < j; i++) {
        b_y[i] = lpcas[13 * i];
    }
    nx = lpcas.size(1) - 1;
    for (k = 0; k <= nx; k++) {
        b_y[k] = log(b_y[k]);
    }
    j = b_y.size(1);
    for (i = 0; i < j; i++) {
        c[13 * i] = -b_y[i];
    }
    f_y.set_size(13, lpcas.size(1));
    i = lpcas.size(1) - 1;
    for (outsize_idx_0 = 0; outsize_idx_0 <= i; outsize_idx_0++) {
        ibmat = outsize_idx_0 * 13;
        for (j = 0; j < 13; j++) {
            f_y[ibmat + j] = lpcas[13 * outsize_idx_0];
        }
    }
    j = 13 * lpcas.size(1);
    f_y.set_size(13, lpcas.size(1));
    for (i = 0; i < j; i++) {
        f_y[i] = lpcas[i] / f_y[i];
    }
    j = lpcas.size(1);
    k = f_y.size(1);
    for (n = 0; n < 12; n++) {
        sum.set_size(1, lpcas.size(1));
        for (i = 0; i < j; i++) {
            sum[i] = 0.0;
        }
        for (int m = 0; m <= n; m++) {
            ibmat = n - m;
            outsize_idx_0 = c.size(1);
            b_y.set_size(1, c.size(1));
            for (i = 0; i < outsize_idx_0; i++) {
                b_y[i] = c[ibmat + 13 * i];
            }
            sum.set_size(1, sum.size(1));
            outsize_idx_0 = sum.size(1);
            for (i = 0; i < outsize_idx_0; i++) {
                sum[i] = sum[i] + static_cast<double>(ibmat) *
                                      f_y[(m + 13 * i) + 1] * b_y[i];
            }
        }
        for (i = 0; i < k; i++) {
            c[(n + 13 * i) + 1] =
                -(f_y[(n + 13 * i) + 1] +
                  sum[i] / ((static_cast<double>(n) + 2.0) - 1.0));
        }
    }
    lpc2spec(lpcas, static_cast<double>(aspectrum.size(0)), b_WINDOW, F, M);
    n = c.size(1);
    cep2.set_size(13, c.size(1));
    for (j = 0; j < n; j++) {
        ibmat = j * 13;
        for (b_i = 0; b_i < 13; b_i++) {
            s = 0.0;
            for (k = 0; k < 13; k++) {
                s += b_dv[k * 13 + b_i] * c[ibmat + k];
            }
            cep2[ibmat + b_i] = s;
        }
    }
    if (cep2.size(1) == 0) {
        del.set_size(13, 0);
    } else {
        for (j = 0; j < 4; j++) {
            ibmat = j * 13;
            for (k = 0; k < 13; k++) {
                outsize_idx_0 = ibmat + k;
                b_b[outsize_idx_0] = cep2[k];
                c_b[outsize_idx_0] = cep2[k + 13 * (cep2.size(1) - 1)];
            }
        }
        f_y.set_size(13, cep2.size(1) + 8);
        for (i = 0; i < 4; i++) {
            for (n = 0; n < 13; n++) {
                f_y[n + 13 * i] = b_b[n + 13 * i];
            }
        }
        j = cep2.size(1);
        for (i = 0; i < j; i++) {
            for (n = 0; n < 13; n++) {
                f_y[n + 13 * (i + 4)] = cep2[n + 13 * i];
            }
        }
        for (i = 0; i < 4; i++) {
            for (n = 0; n < 13; n++) {
                f_y[n + 13 * ((i + cep2.size(1)) + 4)] = c_b[n + 13 * i];
            }
        }
        coder::filter(f_y, del);
        b_y.set_size(1, cep2.size(1));
        j = cep2.size(1) - 1;
        for (i = 0; i <= j; i++) {
            b_y[i] = static_cast<double>(i) + 1.0;
        }
        f_y.set_size(13, b_y.size(1));
        j = b_y.size(1);
        for (i = 0; i < j; i++) {
            for (n = 0; n < 13; n++) {
                f_y[n + 13 * i] = del[n + 13 * (static_cast<int>(b_y[i]) + 7)];
            }
        }
        del.set_size(13, f_y.size(1));
        j = 13 * f_y.size(1);
        for (i = 0; i < j; i++) {
            del[i] = f_y[i];
        }
    }
    deltas(cep2, f_y);
    deltas(f_y, ddel);
    if (cep2.size(1) != 0) {
        ibmat = cep2.size(1);
    } else if (del.size(1) != 0) {
        ibmat = del.size(1);
    } else if (ddel.size(1) != 0) {
        ibmat = ddel.size(1);
    } else {
        ibmat = 0;
    }
    empty_non_axis_sizes = (ibmat == 0);
    if (empty_non_axis_sizes || (cep2.size(1) != 0)) {
        input_sizes_idx_0 = 13;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (del.size(1) != 0)) {
        b_input_sizes_idx_0 = 13;
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (ddel.size(1) != 0)) {
        outsize_idx_0 = 13;
    } else {
        outsize_idx_0 = 0;
    }
    j = input_sizes_idx_0;
    k = b_input_sizes_idx_0;
    b_cep2.set_size((input_sizes_idx_0 + b_input_sizes_idx_0) + outsize_idx_0,
                    ibmat);
    for (i = 0; i < ibmat; i++) {
        for (n = 0; n < j; n++) {
            b_cep2[n + b_cep2.size(0) * i] = cep2[n + 13 * i];
        }
    }
    for (i = 0; i < ibmat; i++) {
        for (n = 0; n < k; n++) {
            b_cep2[(n + input_sizes_idx_0) + b_cep2.size(0) * i] =
                del[n + 13 * i];
        }
    }
    for (i = 0; i < ibmat; i++) {
        for (n = 0; n < outsize_idx_0; n++) {
            b_cep2[((n + input_sizes_idx_0) + b_input_sizes_idx_0) +
                   b_cep2.size(0) * i] = ddel[n + 13 * i];
        }
    }
    coder::mean(b_cep2, tmp_data, &ibmat);
    cep_size[0] = 1;
    cep_size[1] = ibmat;
    if (0 <= ibmat - 1) {
        memcpy(&cep_data[0], &tmp_data[0], ibmat * sizeof(double));
    }
}
