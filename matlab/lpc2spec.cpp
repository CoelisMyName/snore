#include "lpc2spec.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "eigHermitianStandard.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "xzggev.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

void lpc2spec(const coder::array<double, 2U> &lpcas, double nout,
              coder::array<double, 2U> &features, coder::array<double, 2U> &F,
              coder::array<double, 2U> &M)
{
    coder::array<creal_T, 2U> b_aa;
    coder::array<creal_T, 2U> b_x;
    coder::array<creal_T, 2U> y;
    coder::array<creal_T, 1U> r;
    coder::array<double, 2U> aa;
    coder::array<double, 2U> b;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> c_y;
    coder::array<double, 2U> x;
    coder::array<double, 1U> d_y;
    coder::array<double, 1U> e_y;
    coder::array<int, 2U> iidx;
    creal_T a_data[144];
    creal_T c[13];
    creal_T ctmp[13];
    creal_T beta1_data[12];
    creal_T eiga_data[12];
    creal_T r_data[12];
    double ff_data[12];
    double x_data[12];
    double ai;
    double ar;
    double b_r;
    double br;
    double re;
    int ix_data[12];
    int a_size[2];
    int i;
    int i1;
    int ibmat;
    int j;
    int nTrailingZeros;
    int ncols;
    b.set_size(13, lpcas.size(1));
    ncols = lpcas.size(1) - 1;
    for (nTrailingZeros = 0; nTrailingZeros <= ncols; nTrailingZeros++) {
        ibmat = nTrailingZeros * 13;
        for (j = 0; j < 13; j++) {
            b[ibmat + j] = lpcas[13 * nTrailingZeros];
        }
    }
    aa.set_size(13, lpcas.size(1));
    j = 13 * lpcas.size(1);
    for (i = 0; i < j; i++) {
        aa[i] = lpcas[i] / b[i];
    }
    if (rtIsNaN(nout - 1.0)) {
        x.set_size(1, 1);
        x[0] = rtNaN;
    } else if (nout - 1.0 < 0.0) {
        x.set_size(1, 0);
    } else if (rtIsInf(nout - 1.0) && (0.0 == nout - 1.0)) {
        x.set_size(1, 1);
        x[0] = rtNaN;
    } else {
        j = static_cast<int>(floor(nout - 1.0));
        x.set_size(1, j + 1);
        for (i = 0; i <= j; i++) {
            x[i] = i;
        }
    }
    r.set_size(x.size(1));
    j = x.size(1);
    for (i = 0; i < j; i++) {
        ar = x[i] * 0.0 * 3.1415926535897931;
        ai = -x[i] * 3.1415926535897931;
        if (ai == 0.0) {
            r[i].re = ar / (nout - 1.0);
            r[i].im = 0.0;
        } else if (ar == 0.0) {
            r[i].re = 0.0;
            r[i].im = ai / (nout - 1.0);
        } else {
            r[i].re = rtNaN;
            r[i].im = ai / (nout - 1.0);
        }
    }
    b_x.set_size(r.size(0), 13);
    j = r.size(0);
    for (i = 0; i < 13; i++) {
        c[i].re = i;
        c[i].im = 0.0;
        for (i1 = 0; i1 < j; i1++) {
            nTrailingZeros = static_cast<int>(c[i].re);
            br = c[i].im;
            b_x[i1 + b_x.size(0) * i].re =
                r[i1].re * static_cast<double>(nTrailingZeros) - r[i1].im * br;
            b_x[i1 + b_x.size(0) * i].im =
                r[i1].re * br + r[i1].im * static_cast<double>(nTrailingZeros);
        }
    }
    ncols = b_x.size(0) * 13;
    for (j = 0; j < ncols; j++) {
        if (b_x[j].im == 0.0) {
            b_x[j].re = exp(b_x[j].re);
            b_x[j].im = 0.0;
        } else if (rtIsInf(b_x[j].im) && rtIsInf(b_x[j].re) &&
                   (b_x[j].re < 0.0)) {
            b_x[j].re = 0.0;
            b_x[j].im = 0.0;
        } else {
            b_r = exp(b_x[j].re / 2.0);
            br = b_x[j].im;
            b_x[j].re = b_r * (b_r * cos(b_x[j].im));
            b_x[j].im = b_r * (b_r * sin(br));
        }
    }
    b_aa.set_size(13, aa.size(1));
    j = 13 * aa.size(1);
    for (i = 0; i < j; i++) {
        b_aa[i].re = aa[i];
        b_aa[i].im = 0.0;
    }
    y.set_size(b_x.size(0), b_aa.size(1));
    j = b_x.size(0);
    for (i = 0; i < j; i++) {
        ncols = b_aa.size(1);
        for (i1 = 0; i1 < ncols; i1++) {
            re = 0.0;
            b_r = 0.0;
            for (nTrailingZeros = 0; nTrailingZeros < 13; nTrailingZeros++) {
                re += b_x[i + b_x.size(0) * nTrailingZeros].re *
                          b_aa[nTrailingZeros + 13 * i1].re -
                      b_x[i + b_x.size(0) * nTrailingZeros].im *
                          b_aa[nTrailingZeros + 13 * i1].im;
                b_r += b_x[i + b_x.size(0) * nTrailingZeros].re *
                           b_aa[nTrailingZeros + 13 * i1].im +
                       b_x[i + b_x.size(0) * nTrailingZeros].im *
                           b_aa[nTrailingZeros + 13 * i1].re;
            }
            y[i + y.size(0) * i1].re = re;
            y[i + y.size(0) * i1].im = b_r;
        }
    }
    ncols = y.size(0) * y.size(1);
    b_y.set_size(y.size(0), y.size(1));
    for (j = 0; j < ncols; j++) {
        b_y[j] = rt_hypotd_snf(y[j].re, y[j].im);
    }
    j = b_y.size(0) * b_y.size(1);
    for (i = 0; i < j; i++) {
        b_y[i] = 1.0 / b_y[i];
    }
    c_y.set_size(b_y.size(0), b_y.size(1));
    ncols = b_y.size(0) * b_y.size(1);
    for (j = 0; j < ncols; j++) {
        c_y[j] = b_y[j] * b_y[j];
    }
    i = static_cast<int>(nout);
    b_y.set_size(i, lpcas.size(1));
    ncols = lpcas.size(1) - 1;
    for (nTrailingZeros = 0; nTrailingZeros <= ncols; nTrailingZeros++) {
        ibmat = nTrailingZeros * static_cast<int>(nout);
        for (j = 0; j < i; j++) {
            b_y[ibmat + j] = lpcas[13 * nTrailingZeros];
        }
    }
    features.set_size(c_y.size(0), c_y.size(1));
    j = c_y.size(0) * c_y.size(1);
    for (i = 0; i < j; i++) {
        features[i] = c_y[i] / b_y[i];
    }
    F.set_size(lpcas.size(1), 13);
    j = lpcas.size(1) * 13;
    for (i = 0; i < j; i++) {
        F[i] = 0.0;
    }
    M.set_size(lpcas.size(1), 13);
    j = lpcas.size(1) * 13;
    for (i = 0; i < j; i++) {
        M[i] = 0.0;
    }
    i = lpcas.size(1);
    for (int b_c = 0; b_c < i; b_c++) {
        double brm;
        int b_i;
        int k2;
        for (i1 = 0; i1 < 13; i1++) {
            c[i1].re = aa[i1 + 13 * b_c];
            c[i1].im = 0.0;
        }
        memset(&r_data[0], 0, 12U * sizeof(creal_T));
        ncols = 1;
        while ((ncols <= 13) &&
               ((!(c[ncols - 1].re != 0.0)) && (!(c[ncols - 1].im != 0.0)))) {
            ncols++;
        }
        k2 = 13;
        while ((k2 >= ncols) &&
               ((!(c[k2 - 1].re != 0.0)) && (!(c[k2 - 1].im != 0.0)))) {
            k2--;
        }
        nTrailingZeros = 12 - k2;
        if (ncols < k2) {
            double bi;
            int companDim;
            boolean_T exitg1;
            companDim = k2 - ncols;
            exitg1 = false;
            while ((!exitg1) && (companDim > 0)) {
                boolean_T exitg2;
                j = 0;
                exitg2 = false;
                while ((!exitg2) && (j + 1 <= companDim)) {
                    ibmat = ncols + j;
                    ar = c[ibmat].re;
                    ai = c[ibmat].im;
                    br = c[ncols - 1].re;
                    bi = c[ncols - 1].im;
                    if (bi == 0.0) {
                        if (ai == 0.0) {
                            ctmp[j].re = ar / br;
                            ctmp[j].im = 0.0;
                        } else if (ar == 0.0) {
                            ctmp[j].re = 0.0;
                            ctmp[j].im = ai / br;
                        } else {
                            ctmp[j].re = ar / br;
                            ctmp[j].im = ai / br;
                        }
                    } else if (br == 0.0) {
                        if (ar == 0.0) {
                            ctmp[j].re = ai / bi;
                            ctmp[j].im = 0.0;
                        } else if (ai == 0.0) {
                            ctmp[j].re = 0.0;
                            ctmp[j].im = -(ar / bi);
                        } else {
                            ctmp[j].re = ai / bi;
                            ctmp[j].im = -(ar / bi);
                        }
                    } else {
                        brm = fabs(br);
                        b_r = fabs(bi);
                        if (brm > b_r) {
                            brm = bi / br;
                            b_r = br + brm * bi;
                            ctmp[j].re = (ar + brm * ai) / b_r;
                            ctmp[j].im = (ai - brm * ar) / b_r;
                        } else if (b_r == brm) {
                            if (br > 0.0) {
                                br = 0.5;
                            } else {
                                br = -0.5;
                            }
                            if (bi > 0.0) {
                                b_r = 0.5;
                            } else {
                                b_r = -0.5;
                            }
                            ctmp[j].re = (ar * br + ai * b_r) / brm;
                            ctmp[j].im = (ai * br - ar * b_r) / brm;
                        } else {
                            brm = br / bi;
                            b_r = bi + brm * br;
                            ctmp[j].re = (brm * ar + ai) / b_r;
                            ctmp[j].im = (brm * ai - ar) / b_r;
                        }
                    }
                    if (rtIsInf(rt_hypotd_snf(ctmp[j].re, ctmp[j].im))) {
                        exitg2 = true;
                    } else {
                        j++;
                    }
                }
                if (j + 1 > companDim) {
                    exitg1 = true;
                } else {
                    ncols++;
                    companDim--;
                }
            }
            if (companDim < 1) {
                if (1 > 13 - k2) {
                    ibmat = 0;
                } else {
                    ibmat = 13 - k2;
                }
            } else {
                boolean_T p;
                a_size[0] = companDim;
                a_size[1] = companDim;
                j = companDim * companDim;
                if (0 <= j - 1) {
                    memset(&a_data[0], 0, j * sizeof(creal_T));
                }
                for (j = 0; j <= companDim - 2; j++) {
                    i1 = companDim * j;
                    a_data[i1].re = -ctmp[j].re;
                    a_data[i1].im = -ctmp[j].im;
                    i1 = (j + i1) + 1;
                    a_data[i1].re = 1.0;
                    a_data[i1].im = 0.0;
                }
                i1 = companDim * (companDim - 1);
                a_data[i1].re = -ctmp[companDim - 1].re;
                a_data[i1].im = -ctmp[companDim - 1].im;
                if (0 <= nTrailingZeros) {
                    memset(&r_data[0], 0,
                           (nTrailingZeros + 1) * sizeof(creal_T));
                }
                ncols = companDim * companDim;
                p = true;
                for (j = 0; j < ncols; j++) {
                    if ((!p) ||
                        (rtIsInf(a_data[j].re) || rtIsInf(a_data[j].im) ||
                         (rtIsNaN(a_data[j].re) || rtIsNaN(a_data[j].im)))) {
                        p = false;
                    }
                }
                if (!p) {
                    for (i1 = 0; i1 < companDim; i1++) {
                        eiga_data[i1].re = rtNaN;
                        eiga_data[i1].im = 0.0;
                    }
                } else {
                    p = true;
                    j = 0;
                    exitg1 = false;
                    while ((!exitg1) && (j <= companDim - 1)) {
                        int exitg3;
                        b_i = 0;
                        do {
                            exitg3 = 0;
                            if (b_i <= j) {
                                i1 = b_i + companDim * j;
                                nTrailingZeros = j + companDim * b_i;
                                if ((!(a_data[i1].re ==
                                       a_data[nTrailingZeros].re)) ||
                                    (!(a_data[i1].im ==
                                       -a_data[nTrailingZeros].im))) {
                                    p = false;
                                    exitg3 = 1;
                                } else {
                                    b_i++;
                                }
                            } else {
                                j++;
                                exitg3 = 2;
                            }
                        } while (exitg3 == 0);
                        if (exitg3 == 1) {
                            exitg1 = true;
                        }
                    }
                    if (p) {
                        coder::eigHermitianStandard(a_data, a_size, eiga_data,
                                                    &nTrailingZeros);
                    } else {
                        coder::internal::reflapack::xzggev(
                            a_data, a_size, &ncols, eiga_data, &nTrailingZeros,
                            beta1_data, &ibmat);
                        for (i1 = 0; i1 < nTrailingZeros; i1++) {
                            ar = eiga_data[i1].re;
                            ai = eiga_data[i1].im;
                            br = beta1_data[i1].re;
                            bi = beta1_data[i1].im;
                            if (bi == 0.0) {
                                if (ai == 0.0) {
                                    re = ar / br;
                                    b_r = 0.0;
                                } else if (ar == 0.0) {
                                    re = 0.0;
                                    b_r = ai / br;
                                } else {
                                    re = ar / br;
                                    b_r = ai / br;
                                }
                            } else if (br == 0.0) {
                                if (ar == 0.0) {
                                    re = ai / bi;
                                    b_r = 0.0;
                                } else if (ai == 0.0) {
                                    re = 0.0;
                                    b_r = -(ar / bi);
                                } else {
                                    re = ai / bi;
                                    b_r = -(ar / bi);
                                }
                            } else {
                                brm = fabs(br);
                                b_r = fabs(bi);
                                if (brm > b_r) {
                                    brm = bi / br;
                                    b_r = br + brm * bi;
                                    re = (ar + brm * ai) / b_r;
                                    b_r = (ai - brm * ar) / b_r;
                                } else if (b_r == brm) {
                                    if (br > 0.0) {
                                        br = 0.5;
                                    } else {
                                        br = -0.5;
                                    }
                                    if (bi > 0.0) {
                                        b_r = 0.5;
                                    } else {
                                        b_r = -0.5;
                                    }
                                    re = (ar * br + ai * b_r) / brm;
                                    b_r = (ai * br - ar * b_r) / brm;
                                } else {
                                    brm = br / bi;
                                    b_r = bi + brm * br;
                                    re = (brm * ar + ai) / b_r;
                                    b_r = (brm * ai - ar) / b_r;
                                }
                            }
                            eiga_data[i1].re = re;
                            eiga_data[i1].im = b_r;
                        }
                    }
                }
                for (j = 0; j < companDim; j++) {
                    r_data[(j - k2) + 13] = eiga_data[j];
                }
                ibmat = (companDim - k2) + 13;
            }
        } else if (1 > 13 - k2) {
            ibmat = 0;
        } else {
            ibmat = 13 - k2;
        }
        for (i1 = 0; i1 < ibmat; i1++) {
            eiga_data[i1].re = r_data[i1].re;
            eiga_data[i1].im = -r_data[i1].im;
        }
        b_i = ibmat;
        for (j = 0; j < ibmat; j++) {
            ff_data[j] = rt_atan2d_snf(eiga_data[j].im, eiga_data[j].re);
        }
        b_x.set_size(ibmat, 13);
        for (i1 = 0; i1 < 13; i1++) {
            c[i1].re = i1;
            c[i1].im = 0.0;
            for (nTrailingZeros = 0; nTrailingZeros < ibmat; nTrailingZeros++) {
                b_r = ff_data[nTrailingZeros];
                re = b_r * 0.0;
                ncols = static_cast<int>(c[i1].re);
                br = c[i1].im;
                b_x[nTrailingZeros + b_x.size(0) * i1].re =
                    re * static_cast<double>(ncols) - b_r * br;
                b_x[nTrailingZeros + b_x.size(0) * i1].im =
                    re * br + b_r * static_cast<double>(ncols);
            }
        }
        ncols = b_x.size(0) * 13;
        for (j = 0; j < ncols; j++) {
            if (b_x[j].im == 0.0) {
                b_x[j].re = exp(b_x[j].re);
                b_x[j].im = 0.0;
            } else if (rtIsInf(b_x[j].im) && rtIsInf(b_x[j].re) &&
                       (b_x[j].re < 0.0)) {
                b_x[j].re = 0.0;
                b_x[j].im = 0.0;
            } else {
                b_r = exp(b_x[j].re / 2.0);
                br = b_x[j].im;
                b_x[j].re = b_r * (b_r * cos(b_x[j].im));
                b_x[j].im = b_r * (b_r * sin(br));
            }
        }
        for (i1 = 0; i1 < 13; i1++) {
            c[i1].re = aa[i1 + 13 * b_c];
            c[i1].im = 0.0;
        }
        ibmat = b_x.size(0);
        j = b_x.size(0);
        for (i1 = 0; i1 < j; i1++) {
            re = 0.0;
            b_r = 0.0;
            for (nTrailingZeros = 0; nTrailingZeros < 13; nTrailingZeros++) {
                br = c[nTrailingZeros].re;
                brm = c[nTrailingZeros].im;
                re += b_x[i1 + b_x.size(0) * nTrailingZeros].re * br -
                      b_x[i1 + b_x.size(0) * nTrailingZeros].im * brm;
                b_r += b_x[i1 + b_x.size(0) * nTrailingZeros].re * brm +
                       b_x[i1 + b_x.size(0) * nTrailingZeros].im * br;
            }
            r_data[i1].re = re;
            r_data[i1].im = b_r;
        }
        b_x.set_size(b_i, 13);
        for (i1 = 0; i1 < 13; i1++) {
            c[i1].re = i1;
            c[i1].im = 0.0;
            for (nTrailingZeros = 0; nTrailingZeros < b_i; nTrailingZeros++) {
                b_r = ff_data[nTrailingZeros];
                re = b_r * 0.0;
                ncols = static_cast<int>(c[i1].re);
                br = c[i1].im;
                b_x[nTrailingZeros + b_x.size(0) * i1].re =
                    re * static_cast<double>(ncols) - b_r * br;
                b_x[nTrailingZeros + b_x.size(0) * i1].im =
                    re * br + b_r * static_cast<double>(ncols);
            }
        }
        ncols = b_x.size(0) * 13;
        for (j = 0; j < ncols; j++) {
            if (b_x[j].im == 0.0) {
                b_x[j].re = exp(b_x[j].re);
                b_x[j].im = 0.0;
            } else if (rtIsInf(b_x[j].im) && rtIsInf(b_x[j].re) &&
                       (b_x[j].re < 0.0)) {
                b_x[j].re = 0.0;
                b_x[j].im = 0.0;
            } else {
                b_r = exp(b_x[j].re / 2.0);
                br = b_x[j].im;
                b_x[j].re = b_r * (b_r * cos(b_x[j].im));
                b_x[j].im = b_r * (b_r * sin(br));
            }
        }
        nTrailingZeros = b_x.size(0);
        d_y.set_size(nTrailingZeros);
        for (j = 0; j < ibmat; j++) {
            d_y[j] = rt_hypotd_snf(r_data[j].re, r_data[j].im);
        }
        j = d_y.size(0);
        for (i1 = 0; i1 < j; i1++) {
            d_y[i1] = 1.0 / d_y[i1];
        }
        e_y.set_size(d_y.size(0));
        ncols = d_y.size(0);
        for (j = 0; j < ncols; j++) {
            e_y[j] = d_y[j] * d_y[j];
        }
        b_r = lpcas[13 * b_c];
        ncols = e_y.size(0);
        j = e_y.size(0);
        for (i1 = 0; i1 < j; i1++) {
            x_data[i1] = e_y[i1] / b_r;
        }
        for (j = 0; j < ncols; j++) {
            x_data[j] = sqrt(x_data[j]);
        }
        x.set_size(1, b_i);
        for (i1 = 0; i1 < b_i; i1++) {
            x[i1] = ff_data[i1];
        }
        coder::internal::sort(x, iidx);
        x.set_size(1, iidx.size(1));
        j = iidx.size(1);
        for (i1 = 0; i1 < j; i1++) {
            nTrailingZeros = iidx[i1];
            x[i1] = nTrailingZeros;
            ix_data[i1] = nTrailingZeros;
        }
        ncols = x.size(1) - 1;
        nTrailingZeros = 0;
        for (b_i = 0; b_i <= ncols; b_i++) {
            if (ff_data[static_cast<int>(x[b_i]) - 1] > 0.0) {
                nTrailingZeros++;
            }
        }
        ibmat = 0;
        for (b_i = 0; b_i <= ncols; b_i++) {
            if (ff_data[ix_data[b_i] - 1] > 0.0) {
                ix_data[ibmat] = ix_data[b_i];
                ibmat++;
            }
        }
        for (i1 = 0; i1 < nTrailingZeros; i1++) {
            F[b_c + F.size(0) * i1] = ff_data[ix_data[i1] - 1];
        }
        for (i1 = 0; i1 < nTrailingZeros; i1++) {
            M[b_c + M.size(0) * i1] = x_data[ix_data[i1] - 1];
        }
    }
}
