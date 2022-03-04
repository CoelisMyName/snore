#include "cep_feat.h"
#include "SnoringRecognition_rtwutil.h"
#include "any1.h"
#include "asinh.h"
#include "deltas.h"
#include "fft.h"
#include "filter.h"
#include "hanning.h"
#include "ifft.h"
#include "levinson.h"
#include "lpc2spec.h"
#include "mean.h"
#include "minOrMax.h"
#include "mod.h"
#include "mtimes.h"
#include "postaud.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

void cep_feat(const coder::array<double, 1U> &sig, double fs, double cep_data[],
              int cep_size[2])
{
    static const double b_dv2[169] = {1.0,
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
    coder::array<double, 2U> b_postspectrum;
    coder::array<double, 2U> b_r;
    coder::array<double, 2U> b_select;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> binbarks;
    coder::array<double, 2U> c;
    coder::array<double, 2U> c_y;
    coder::array<double, 2U> cep2;
    coder::array<double, 2U> colindex;
    coder::array<double, 2U> ddel;
    coder::array<double, 2U> del;
    coder::array<double, 2U> f_y;
    coder::array<double, 2U> g_y;
    coder::array<double, 2U> h_y;
    coder::array<double, 2U> lpcas;
    coder::array<double, 2U> minval;
    coder::array<double, 2U> postspectrum;
    coder::array<double, 2U> pspectrum;
    coder::array<double, 2U> r;
    coder::array<double, 2U> sum;
    coder::array<double, 2U> wts;
    coder::array<double, 1U> e;
    coder::array<double, 1U> rowindex;
    coder::array<double, 1U> y;
    double b_dv[52];
    double b_dv1[52];
    double tmp_data[39];
    double d;
    double min_bark;
    double ncol;
    double nfft;
    double nfilts;
    double nyqbark;
    double s;
    double step_barks;
    double winpts;
    double x;
    int b_i;
    int b_loop_ub;
    int i;
    int i1;
    int ibmat;
    int input_sizes_idx_0;
    int loop_ub;
    int n;
    int ncols;
    int nx;
    int sizes_idx_0;
    signed char b_input_sizes_idx_0;
    signed char c_input_sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    winpts = rt_roundd_snf(0.025 * fs);
    coder::hanning(winpts, y);
    WINDOW.set_size(1, y.size(0));
    loop_ub = y.size(0);
    for (i = 0; i < loop_ub; i++) {
        WINDOW[i] = y[i];
    }
    s = winpts - rt_roundd_snf(0.01 * fs);
    y.set_size(sig.size(0));
    loop_ub = sig.size(0);
    for (i = 0; i < loop_ub; i++) {
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
        loop_ub = static_cast<int>(ncol - 1.0);
        for (i = 0; i <= loop_ub; i++) {
            b_y[i] = i;
        }
    }
    s = static_cast<double>(WINDOW.size(1)) - s;
    colindex.set_size(1, b_y.size(1));
    loop_ub = b_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        colindex[i] = b_y[i] * s + 1.0;
    }
    if (WINDOW.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        b_y.set_size(1, WINDOW.size(1));
        loop_ub = WINDOW.size(1) - 1;
        for (i = 0; i <= loop_ub; i++) {
            b_y[i] = static_cast<double>(i) + 1.0;
        }
    }
    rowindex.set_size(b_y.size(1));
    loop_ub = b_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        rowindex[i] = b_y[i];
    }
    d = colindex[static_cast<int>(ncol) - 1];
    if (y.size(0) < (static_cast<double>(WINDOW.size(1)) + d) - 1.0) {
        y[static_cast<int>((static_cast<double>(WINDOW.size(1)) + d) - 1.0) -
          1] = 0.0;
    }
    loop_ub = rowindex.size(0);
    c_y.set_size(rowindex.size(0), static_cast<int>(ncol));
    b_loop_ub = static_cast<int>(ncol);
    for (i = 0; i < b_loop_ub; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            c_y[i1 + c_y.size(0) * i] =
                y[static_cast<int>((rowindex[i1] + colindex[i]) - 1.0) - 1];
        }
    }
    loop_ub = WINDOW.size(1);
    b_WINDOW.set_size(WINDOW.size(1), static_cast<int>(ncol));
    b_loop_ub = static_cast<int>(ncol);
    for (i = 0; i < b_loop_ub; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_WINDOW[i1 + b_WINDOW.size(0) * i] =
                WINDOW[i1] * c_y[i1 + c_y.size(0) * i];
        }
    }
    coder::fft(b_WINDOW, nfft, d_y);
    loop_ub = y.size(0);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    if (!coder::any(y)) {
        if (coder::b_mod(nfft) != 0.0) {
            s = (nfft + 1.0) / 2.0;
            if (rtIsNaN(s)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else if (s < 1.0) {
                b_select.set_size(1, 0);
            } else if (rtIsInf(s) && (1.0 == s)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else {
                loop_ub = static_cast<int>(floor(s - 1.0));
                b_select.set_size(1, loop_ub + 1);
                for (i = 0; i <= loop_ub; i++) {
                    b_select[i] = static_cast<double>(i) + 1.0;
                }
            }
        } else {
            s = nfft / 2.0 + 1.0;
            if (rtIsNaN(s)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else if (rtIsInf(s) && (1.0 == s)) {
                b_select.set_size(1, 1);
                b_select[0] = rtNaN;
            } else {
                loop_ub = static_cast<int>(floor(s - 1.0));
                b_select.set_size(1, loop_ub + 1);
                for (i = 0; i <= loop_ub; i++) {
                    b_select[i] = static_cast<double>(i) + 1.0;
                }
            }
        }
        ncols = d_y.size(1) - 1;
        e_y.set_size(b_select.size(1), d_y.size(1));
        for (i = 0; i <= ncols; i++) {
            loop_ub = b_select.size(1);
            for (i1 = 0; i1 < loop_ub; i1++) {
                e_y[i1 + e_y.size(0) * i] =
                    d_y[(static_cast<int>(b_select[i1]) + d_y.size(0) * i) - 1];
            }
        }
        d_y.set_size(e_y.size(0), e_y.size(1));
        loop_ub = e_y.size(0) * e_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            d_y[i] = e_y[i];
        }
    }
    nx = d_y.size(0) * d_y.size(1);
    b_WINDOW.set_size(d_y.size(0), d_y.size(1));
    for (sizes_idx_0 = 0; sizes_idx_0 < nx; sizes_idx_0++) {
        b_WINDOW[sizes_idx_0] =
            rt_hypotd_snf(d_y[sizes_idx_0].re, d_y[sizes_idx_0].im);
    }
    postspectrum.set_size(b_WINDOW.size(0), b_WINDOW.size(1));
    nx = b_WINDOW.size(0) * b_WINDOW.size(1);
    for (sizes_idx_0 = 0; sizes_idx_0 < nx; sizes_idx_0++) {
        postspectrum[sizes_idx_0] =
            b_WINDOW[sizes_idx_0] * b_WINDOW[sizes_idx_0];
    }
    pspectrum.set_size(postspectrum.size(0), postspectrum.size(1));
    loop_ub = postspectrum.size(0) * postspectrum.size(1);
    for (i = 0; i < loop_ub; i++) {
        pspectrum[i] = postspectrum[i] + winpts;
    }
    d = fs / 2.0 / 600.0;
    s = d;
    coder::internal::scalar::b_asinh(&s);
    x = ceil(6.0 * s);
    nfilts = x + 1.0;
    nfft = (static_cast<double>(pspectrum.size(0)) - 1.0) * 2.0;
    s = 0.0;
    coder::internal::scalar::b_asinh(&s);
    min_bark = 6.0 * s;
    coder::internal::scalar::b_asinh(&d);
    nyqbark = 6.0 * d - min_bark;
    if (x + 1.0 == 0.0) {
        nfilts = ceil(nyqbark) + 1.0;
    }
    i = static_cast<int>(nfilts);
    wts.set_size(i, static_cast<int>(nfft));
    loop_ub = static_cast<int>(nfilts) * static_cast<int>(nfft);
    for (i1 = 0; i1 < loop_ub; i1++) {
        wts[i1] = 0.0;
    }
    step_barks = nyqbark / (nfilts - 1.0);
    loop_ub = static_cast<int>(floor(nfft / 2.0));
    b_y.set_size(1, loop_ub + 1);
    for (i1 = 0; i1 <= loop_ub; i1++) {
        b_y[i1] = i1;
    }
    b_y.set_size(1, b_y.size(1));
    loop_ub = b_y.size(1) - 1;
    for (i1 = 0; i1 <= loop_ub; i1++) {
        b_y[i1] = b_y[i1] * fs / nfft / 600.0;
    }
    nx = b_y.size(1);
    for (sizes_idx_0 = 0; sizes_idx_0 < nx; sizes_idx_0++) {
        coder::internal::scalar::b_asinh(&b_y[sizes_idx_0]);
    }
    binbarks.set_size(1, b_y.size(1));
    loop_ub = b_y.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
        binbarks[i1] = 6.0 * b_y[i1];
    }
    for (b_i = 0; b_i < i; b_i++) {
        double f_bark_mid;
        f_bark_mid =
            min_bark + ((static_cast<double>(b_i) + 1.0) - 1.0) * step_barks;
        b_y.set_size(1, binbarks.size(1));
        loop_ub = binbarks.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_y[i1] = binbarks[i1] - f_bark_mid;
        }
        f_y.set_size(2, b_y.size(1));
        loop_ub = b_y.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            f_y[2 * i1] = b_y[i1] + 0.5;
        }
        loop_ub = b_y.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            f_y[2 * i1 + 1] = -2.5 * (b_y[i1] - 0.5);
        }
        coder::internal::minimum(f_y, b_y);
        i1 = b_y.size(1);
        minval.set_size(1, b_y.size(1));
        for (sizes_idx_0 = 0; sizes_idx_0 < i1; sizes_idx_0++) {
            d = b_y[sizes_idx_0];
            if ((0.0 < d) || rtIsNaN(d)) {
                minval[sizes_idx_0] = 0.0;
            } else {
                minval[sizes_idx_0] = d;
            }
        }
        i1 = minval.size(1);
        r.set_size(1, minval.size(1));
        for (sizes_idx_0 = 0; sizes_idx_0 < i1; sizes_idx_0++) {
            r[sizes_idx_0] = rt_powd_snf(10.0, minval[sizes_idx_0]);
        }
        loop_ub = r.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
            wts[b_i + wts.size(0) * i1] = r[i1];
        }
    }
    if (1 > pspectrum.size(0)) {
        loop_ub = 0;
    } else {
        loop_ub = pspectrum.size(0);
    }
    ncols = wts.size(0) - 1;
    b_loop_ub = wts.size(0);
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            wts[i1 + (ncols + 1) * i] = wts[i1 + wts.size(0) * i];
        }
    }
    wts.set_size(ncols + 1, loop_ub);
    coder::internal::blas::mtimes(wts, pspectrum, aspectrum);
    postaud(aspectrum, fs / 2.0, b_postspectrum);
    if (2 > b_postspectrum.size(0) - 1) {
        i = 0;
        i1 = 1;
        ncols = -1;
    } else {
        i = b_postspectrum.size(0) - 2;
        i1 = -1;
        ncols = 1;
    }
    if ((b_postspectrum.size(0) != 0) && (b_postspectrum.size(1) != 0)) {
        ibmat = b_postspectrum.size(1);
    } else if ((div_s32_floor(ncols - i, i1) + 1 != 0) &&
               (b_postspectrum.size(1) != 0)) {
        ibmat = b_postspectrum.size(1);
    } else {
        ibmat = b_postspectrum.size(1);
    }
    empty_non_axis_sizes = (ibmat == 0);
    if (empty_non_axis_sizes ||
        ((b_postspectrum.size(0) != 0) && (b_postspectrum.size(1) != 0))) {
        input_sizes_idx_0 = b_postspectrum.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((div_s32_floor(ncols - i, i1) + 1 != 0) &&
                                 (b_postspectrum.size(1) != 0))) {
        sizes_idx_0 = div_s32_floor(ncols - i, i1) + 1;
    } else {
        sizes_idx_0 = 0;
    }
    loop_ub = b_postspectrum.size(1);
    b_WINDOW.set_size(div_s32_floor(ncols - i, i1) + 1, b_postspectrum.size(1));
    for (int i2 = 0; i2 < loop_ub; i2++) {
        b_loop_ub = div_s32_floor(ncols - i, i1);
        for (int i3 = 0; i3 <= b_loop_ub; i3++) {
            b_WINDOW[i3 + b_WINDOW.size(0) * i2] =
                b_postspectrum[(i + i1 * i3) + b_postspectrum.size(0) * i2];
        }
    }
    postspectrum.set_size(input_sizes_idx_0 + sizes_idx_0, ibmat);
    for (i = 0; i < ibmat; i++) {
        for (i1 = 0; i1 < input_sizes_idx_0; i1++) {
            postspectrum[i1 + postspectrum.size(0) * i] =
                b_postspectrum[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < ibmat; i++) {
        for (i1 = 0; i1 < sizes_idx_0; i1++) {
            postspectrum[(i1 + input_sizes_idx_0) + postspectrum.size(0) * i] =
                b_WINDOW[i1 + sizes_idx_0 * i];
        }
    }
    coder::ifft(postspectrum, e_y);
    b_r.set_size(e_y.size(0), e_y.size(1));
    loop_ub = e_y.size(0) * e_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_r[i] = e_y[i].re;
    }
    ncols = b_r.size(1) - 1;
    loop_ub = b_postspectrum.size(0);
    for (i = 0; i <= ncols; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_r[i1 + loop_ub * i] = b_r[i1 + b_r.size(0) * i];
        }
    }
    b_r.set_size(b_postspectrum.size(0), ncols + 1);
    coder::levinson(b_r, g_y, e);
    h_y.set_size(13, e.size(0));
    ncols = e.size(0);
    for (sizes_idx_0 = 0; sizes_idx_0 < ncols; sizes_idx_0++) {
        ibmat = sizes_idx_0 * 13;
        for (input_sizes_idx_0 = 0; input_sizes_idx_0 < 13;
             input_sizes_idx_0++) {
            h_y[ibmat + input_sizes_idx_0] = e[sizes_idx_0];
        }
    }
    lpcas.set_size(g_y.size(1), g_y.size(0));
    loop_ub = g_y.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_loop_ub = g_y.size(1);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            lpcas[i1 + 13 * i] = g_y[i + g_y.size(0) * i1] / h_y[i1 + 13 * i];
        }
    }
    c.set_size(13, lpcas.size(1));
    loop_ub = 13 * lpcas.size(1);
    for (i = 0; i < loop_ub; i++) {
        c[i] = 0.0;
    }
    loop_ub = lpcas.size(1);
    b_y.set_size(1, lpcas.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_y[i] = lpcas[13 * i];
    }
    nx = lpcas.size(1) - 1;
    for (sizes_idx_0 = 0; sizes_idx_0 <= nx; sizes_idx_0++) {
        b_y[sizes_idx_0] = log(b_y[sizes_idx_0]);
    }
    loop_ub = b_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        c[13 * i] = -b_y[i];
    }
    h_y.set_size(13, lpcas.size(1));
    i = lpcas.size(1) - 1;
    for (sizes_idx_0 = 0; sizes_idx_0 <= i; sizes_idx_0++) {
        ibmat = sizes_idx_0 * 13;
        for (input_sizes_idx_0 = 0; input_sizes_idx_0 < 13;
             input_sizes_idx_0++) {
            h_y[ibmat + input_sizes_idx_0] = lpcas[13 * sizes_idx_0];
        }
    }
    loop_ub = 13 * lpcas.size(1);
    h_y.set_size(13, lpcas.size(1));
    for (i = 0; i < loop_ub; i++) {
        h_y[i] = lpcas[i] / h_y[i];
    }
    loop_ub = lpcas.size(1);
    b_loop_ub = h_y.size(1);
    for (n = 0; n < 12; n++) {
        sum.set_size(1, lpcas.size(1));
        for (i = 0; i < loop_ub; i++) {
            sum[i] = 0.0;
        }
        for (int m = 0; m <= n; m++) {
            ncols = n - m;
            ibmat = c.size(1);
            r.set_size(1, c.size(1));
            for (i = 0; i < ibmat; i++) {
                r[i] = c[ncols + 13 * i];
            }
            sum.set_size(1, sum.size(1));
            ibmat = sum.size(1);
            for (i = 0; i < ibmat; i++) {
                sum[i] = sum[i] + static_cast<double>(ncols) *
                                      h_y[(m + 13 * i) + 1] * r[i];
            }
        }
        for (i = 0; i < b_loop_ub; i++) {
            c[(n + 13 * i) + 1] =
                -(h_y[(n + 13 * i) + 1] +
                  sum[i] / ((static_cast<double>(n) + 2.0) - 1.0));
        }
    }
    lpc2spec(lpcas, static_cast<double>(aspectrum.size(0)), b_WINDOW, F, M);
    n = c.size(1);
    cep2.set_size(13, c.size(1));
    for (ibmat = 0; ibmat < n; ibmat++) {
        ncols = ibmat * 13;
        for (b_i = 0; b_i < 13; b_i++) {
            s = 0.0;
            for (sizes_idx_0 = 0; sizes_idx_0 < 13; sizes_idx_0++) {
                s += b_dv2[sizes_idx_0 * 13 + b_i] * c[ncols + sizes_idx_0];
            }
            cep2[ncols + b_i] = s;
        }
    }
    coder::repmat(*(double(*)[13]) & cep2[0], b_dv);
    ncols = cep2.size(1);
    coder::repmat(*(double(*)[13]) & cep2[13 * (ncols - 1)], b_dv1);
    h_y.set_size(13, cep2.size(1) + 8);
    for (i = 0; i < 4; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            h_y[i1 + 13 * i] = b_dv[i1 + 13 * i];
        }
    }
    loop_ub = cep2.size(1);
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            h_y[i1 + 13 * (i + 4)] = cep2[i1 + 13 * i];
        }
    }
    for (i = 0; i < 4; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            h_y[i1 + 13 * ((i + cep2.size(1)) + 4)] = b_dv1[i1 + 13 * i];
        }
    }
    coder::filter(h_y, del);
    if (cep2.size(1) < 1) {
        b_y.set_size(1, 0);
    } else {
        b_y.set_size(1, cep2.size(1));
        loop_ub = cep2.size(1) - 1;
        for (i = 0; i <= loop_ub; i++) {
            b_y[i] = static_cast<double>(i) + 1.0;
        }
    }
    h_y.set_size(13, b_y.size(1));
    loop_ub = b_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            h_y[i1 + 13 * i] = del[i1 + 13 * (static_cast<int>(b_y[i]) + 7)];
        }
    }
    del.set_size(13, h_y.size(1));
    loop_ub = 13 * h_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        del[i] = h_y[i];
    }
    deltas(cep2, h_y);
    deltas(h_y, ddel);
    empty_non_axis_sizes = (cep2.size(1) == 0);
    if (empty_non_axis_sizes || (cep2.size(1) != 0)) {
        b_input_sizes_idx_0 = 13;
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (del.size(1) != 0)) {
        c_input_sizes_idx_0 = 13;
    } else {
        c_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (ddel.size(1) != 0)) {
        sizes_idx_0 = 13;
    } else {
        sizes_idx_0 = 0;
    }
    input_sizes_idx_0 = b_input_sizes_idx_0;
    b_cep2.set_size((b_input_sizes_idx_0 + c_input_sizes_idx_0) + sizes_idx_0,
                    cep2.size(1));
    loop_ub = cep2.size(1);
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < input_sizes_idx_0; i1++) {
            b_cep2[i1 + b_cep2.size(0) * i] = cep2[i1 + 13 * i];
        }
    }
    loop_ub = cep2.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_loop_ub = c_input_sizes_idx_0;
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            b_cep2[(i1 + b_input_sizes_idx_0) + b_cep2.size(0) * i] =
                del[i1 + 13 * i];
        }
    }
    loop_ub = cep2.size(1);
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < sizes_idx_0; i1++) {
            b_cep2[((i1 + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                   b_cep2.size(0) * i] = ddel[i1 + 13 * i];
        }
    }
    coder::mean(b_cep2, tmp_data, &ncols);
    cep_size[0] = 1;
    cep_size[1] = ncols;
    if (0 <= ncols - 1) {
        memcpy(&cep_data[0], &tmp_data[0], ncols * sizeof(double));
    }
}
