#include "fmt_feat.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "callLevinson.h"
#include "eigHermitianStandard.h"
#include "enframe.h"
#include "fft.h"
#include "hanning.h"
#include "ifft.h"
#include "nanmean.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "xzggev.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

void fmt_feat(const coder::array<double, 1U> &sig, double fs, double *Formant1,
              double *Formant2, double *Formant3)
{
    coder::array<creal_T, 1U> R;
    coder::array<creal_T, 1U> X;
    coder::array<double, 2U> b_fmt;
    coder::array<double, 2U> fmt;
    coder::array<double, 2U> r;
    coder::array<double, 2U> yf;
    coder::array<double, 1U> b_sig;
    coder::array<double, 1U> y;
    coder::array<int, 2U> b_yf;
    creal_T At_data[144];
    creal_T A_data[13];
    creal_T K_data[13];
    creal_T beta1_data[12];
    creal_T eiga_data[12];
    creal_T rts_data[10];
    double b_a_data[100];
    double a_data[11];
    double ctmp_data[11];
    double tmp_data[10];
    double F[3];
    double Nwin;
    double b_const;
    double b_fs;
    double f;
    double inc;
    double wlen;
    int A_size[2];
    int At_size[2];
    int K_size[2];
    int a_size[2];
    int tempE_size[2];
    int Nt;
    int eiga_size;
    int eint;
    int i;
    int k1;
    int loop_ub;
    int nx;
    int varargin_1_idx_1;
    int y_size_idx_1;
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
    coder::hanning(wlen, b_sig);
    enframe(sig, b_sig, inc, r);
    y_size_idx_1 = r.size(0);
    coder::hanning(wlen, b_sig);
    enframe(sig, b_sig, inc, r);
    Nt = r.size(0);
    Nwin = floor(static_cast<double>(sig.size(0)) /
                 static_cast<double>(y_size_idx_1));
    fmt.set_size(3, y_size_idx_1);
    if (0 <= y_size_idx_1 - 1) {
        varargin_1_idx_1 = sig.size(0);
        b_const = fs / 6.2831853071795862;
        b_fs = fs / 2.0;
    }
    for (int m = 0; m < Nt; m++) {
        double ai;
        double ar;
        double re;
        double s;
        int nTrailingZeros;
        f = Nwin * ((static_cast<double>(m) + 1.0) - 1.0) + 1.0;
        s = Nwin * (static_cast<double>(m) + 1.0);
        if ((s > varargin_1_idx_1) || rtIsNaN(s)) {
            s = varargin_1_idx_1;
        }
        if (f > s) {
            i = 1;
            eiga_size = 0;
        } else {
            i = static_cast<int>(f);
            eiga_size = static_cast<int>(s);
        }
        f = frexp(fabs(2.0 * (static_cast<double>(eiga_size - i) + 1.0) - 1.0),
                  &eint);
        nx = eint;
        if (f == 0.5) {
            nx = eint - 1;
        }
        eiga_size -= i;
        loop_ub = eiga_size + 1;
        b_sig.set_size(eiga_size + 1);
        for (k1 = 0; k1 < loop_ub; k1++) {
            b_sig[k1] = sig[(i + k1) - 1];
        }
        coder::fft(b_sig, rt_powd_snf(2.0, static_cast<double>(nx)), X);
        nx = X.size(0);
        b_sig.set_size(X.size(0));
        for (k1 = 0; k1 < nx; k1++) {
            b_sig[k1] = rt_hypotd_snf(X[k1].re, X[k1].im);
        }
        y.set_size(b_sig.size(0));
        nx = b_sig.size(0);
        for (k1 = 0; k1 < nx; k1++) {
            y[k1] = b_sig[k1] * b_sig[k1];
        }
        coder::ifft(y, R);
        loop_ub = R.size(0);
        for (i = 0; i < loop_ub; i++) {
            ar = R[i].re;
            ai = R[i].im;
            if (ai == 0.0) {
                re = ar / (static_cast<double>(eiga_size) + 1.0);
                f = 0.0;
            } else if (ar == 0.0) {
                re = 0.0;
                f = ai / (static_cast<double>(eiga_size) + 1.0);
            } else {
                re = ar / (static_cast<double>(eiga_size) + 1.0);
                f = ai / (static_cast<double>(eiga_size) + 1.0);
            }
            R[i].re = re;
            R[i].im = f;
        }
        nx = 10;
        if ((10 == R.size(0)) || (10 > R.size(0))) {
            nx = R.size(0) - 1;
        }
        coder::signal::internal::levinson::callLevinson(
            R, static_cast<double>(nx), A_data, A_size, (double *)&f,
            tempE_size, K_data, K_size);
        loop_ub = A_size[1];
        for (i = 0; i < loop_ub; i++) {
            a_data[i] = A_data[i].re;
        }
        if (0 <= loop_ub - 2) {
            memset(&rts_data[0], 0, (loop_ub + -1) * sizeof(creal_T));
        }
        k1 = 1;
        while ((k1 <= loop_ub) && (!(a_data[k1 - 1] != 0.0))) {
            k1++;
        }
        nx = A_size[1];
        while ((nx >= k1) && (!(a_data[nx - 1] != 0.0))) {
            nx--;
        }
        nTrailingZeros = A_size[1] - nx;
        if (k1 < nx) {
            int companDim;
            boolean_T exitg1;
            companDim = nx - k1;
            exitg1 = false;
            while ((!exitg1) && (companDim > 0)) {
                boolean_T exitg2;
                nx = 0;
                exitg2 = false;
                while ((!exitg2) && (nx + 1 <= companDim)) {
                    ctmp_data[nx] = a_data[k1 + nx] / a_data[k1 - 1];
                    if (rtIsInf(fabs(ctmp_data[nx]))) {
                        exitg2 = true;
                    } else {
                        nx++;
                    }
                }
                if (nx + 1 > companDim) {
                    exitg1 = true;
                } else {
                    k1++;
                    companDim--;
                }
            }
            if (companDim >= 1) {
                boolean_T p;
                a_size[0] = companDim;
                a_size[1] = companDim;
                nx = companDim * companDim;
                if (0 <= nx - 1) {
                    memset(&b_a_data[0], 0, nx * sizeof(double));
                }
                for (k1 = 0; k1 <= companDim - 2; k1++) {
                    nx = companDim * k1;
                    b_a_data[nx] = -ctmp_data[k1];
                    b_a_data[(k1 + nx) + 1] = 1.0;
                }
                b_a_data[companDim * (companDim - 1)] =
                    -ctmp_data[companDim - 1];
                if (0 <= nTrailingZeros - 1) {
                    memset(&rts_data[0], 0, nTrailingZeros * sizeof(creal_T));
                }
                nx = companDim * companDim;
                p = true;
                for (k1 = 0; k1 < nx; k1++) {
                    if ((!p) ||
                        (rtIsInf(b_a_data[k1]) || rtIsNaN(b_a_data[k1]))) {
                        p = false;
                    }
                }
                if (!p) {
                    for (i = 0; i < companDim; i++) {
                        eiga_data[i].re = rtNaN;
                        eiga_data[i].im = 0.0;
                    }
                } else {
                    p = true;
                    nx = 0;
                    exitg1 = false;
                    while ((!exitg1) && (nx <= companDim - 1)) {
                        int exitg3;
                        k1 = 0;
                        do {
                            exitg3 = 0;
                            if (k1 <= nx) {
                                if (!(b_a_data[k1 + companDim * nx] ==
                                      b_a_data[nx + companDim * k1])) {
                                    p = false;
                                    exitg3 = 1;
                                } else {
                                    k1++;
                                }
                            } else {
                                nx++;
                                exitg3 = 2;
                            }
                        } while (exitg3 == 0);
                        if (exitg3 == 1) {
                            exitg1 = true;
                        }
                    }
                    if (p) {
                        coder::eigHermitianStandard(b_a_data, a_size, tmp_data,
                                                    &nx);
                        for (i = 0; i < nx; i++) {
                            eiga_data[i].re = tmp_data[i];
                            eiga_data[i].im = 0.0;
                        }
                    } else {
                        At_size[0] = companDim;
                        At_size[1] = companDim;
                        nx = companDim * companDim;
                        for (i = 0; i < nx; i++) {
                            At_data[i].re = b_a_data[i];
                            At_data[i].im = 0.0;
                        }
                        coder::internal::reflapack::xzggev(
                            At_data, At_size, &nx, eiga_data, &eiga_size,
                            beta1_data, &k1);
                        for (i = 0; i < eiga_size; i++) {
                            double bi;
                            double br;
                            ar = eiga_data[i].re;
                            ai = eiga_data[i].im;
                            br = beta1_data[i].re;
                            bi = beta1_data[i].im;
                            if (bi == 0.0) {
                                if (ai == 0.0) {
                                    re = ar / br;
                                    f = 0.0;
                                } else if (ar == 0.0) {
                                    re = 0.0;
                                    f = ai / br;
                                } else {
                                    re = ar / br;
                                    f = ai / br;
                                }
                            } else if (br == 0.0) {
                                if (ar == 0.0) {
                                    re = ai / bi;
                                    f = 0.0;
                                } else if (ai == 0.0) {
                                    re = 0.0;
                                    f = -(ar / bi);
                                } else {
                                    re = ai / bi;
                                    f = -(ar / bi);
                                }
                            } else {
                                double brm;
                                brm = fabs(br);
                                f = fabs(bi);
                                if (brm > f) {
                                    s = bi / br;
                                    f = br + s * bi;
                                    re = (ar + s * ai) / f;
                                    f = (ai - s * ar) / f;
                                } else if (f == brm) {
                                    if (br > 0.0) {
                                        s = 0.5;
                                    } else {
                                        s = -0.5;
                                    }
                                    if (bi > 0.0) {
                                        f = 0.5;
                                    } else {
                                        f = -0.5;
                                    }
                                    re = (ar * s + ai * f) / brm;
                                    f = (ai * s - ar * f) / brm;
                                } else {
                                    s = br / bi;
                                    f = bi + s * br;
                                    re = (s * ar + ai) / f;
                                    f = (s * ai - ar) / f;
                                }
                            }
                            eiga_data[i].re = re;
                            eiga_data[i].im = f;
                        }
                    }
                }
                for (k1 = 0; k1 < companDim; k1++) {
                    rts_data[k1 + nTrailingZeros] = eiga_data[k1];
                }
            }
        }
        yf.set_size(1, 0);
        for (k1 = 0; k1 <= loop_ub - 2; k1++) {
            double formn;
            f = rts_data[k1].im;
            s = rts_data[k1].re;
            formn = b_const * rt_atan2d_snf(f, s);
            if ((formn > 150.0) &&
                (-2.0 * b_const * log(rt_hypotd_snf(s, f)) < 700.0) &&
                (formn < fs / 2.0)) {
                i = yf.size(1);
                yf.set_size(yf.size(0), yf.size(1) + 1);
                yf[i] = formn;
            }
        }
        coder::internal::sort(yf, b_yf);
        F[0] = rtNaN;
        F[1] = rtNaN;
        F[2] = rtNaN;
        nx = yf.size(1);
        if (3 < nx) {
            nx = 3;
        }
        if (1 > nx) {
            loop_ub = 0;
        } else {
            loop_ub = nx;
        }
        for (i = 0; i < loop_ub; i++) {
            F[i] = yf[i];
        }
        fmt[3 * m] = F[0] / b_fs;
        fmt[3 * m + 1] = F[1] / b_fs;
        fmt[3 * m + 2] = F[2] / b_fs;
    }
    f = fs / 2.0;
    loop_ub = fmt.size(1);
    b_fmt.set_size(1, fmt.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_fmt[i] = fmt[3 * i] * f;
    }
    *Formant1 = coder::nanmean(b_fmt);
    loop_ub = fmt.size(1);
    b_fmt.set_size(1, fmt.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_fmt[i] = fmt[3 * i + 1] * f;
    }
    *Formant2 = coder::nanmean(b_fmt);
    loop_ub = fmt.size(1);
    b_fmt.set_size(1, fmt.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_fmt[i] = fmt[3 * i + 2] * f;
    }
    *Formant3 = coder::nanmean(b_fmt);
    if (rtIsNaN(*Formant1)) {
        *Formant1 = 0.0;
    }
    if (rtIsNaN(*Formant2)) {
        *Formant2 = 0.0;
    }
    if (rtIsNaN(*Formant3)) {
        *Formant3 = 0.0;
    }
}
