#include "eig.h"
#include "SnoringRecognition_rtwutil.h"
#include "eigStandard.h"
#include "rt_nonfinite.h"
#include "xhseqr.h"
#include "xnrm2.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

static int div_nde_s32_floor(int numerator, int denominator);

static int div_nde_s32_floor(int numerator, int denominator)
{
    int b_numerator;
    if (((numerator < 0) != (denominator < 0)) &&
        (numerator % denominator != 0)) {
        b_numerator = -1;
    } else {
        b_numerator = 0;
    }
    return numerator / denominator + b_numerator;
}

namespace coder {
void eig(const double A[36], creal_T V[6])
{
    double T[36];
    double work[6];
    double tau[5];
    int i;
    boolean_T p;
    p = true;
    for (i = 0; i < 36; i++) {
        if ((!p) || (rtIsInf(A[i]) || rtIsNaN(A[i]))) {
            p = false;
        }
    }
    if (!p) {
        for (int b_i = 0; b_i < 6; b_i++) {
            V[b_i].re = rtNaN;
            V[b_i].im = 0.0;
        }
    } else {
        int b_i;
        int coltop;
        int exitg1;
        boolean_T exitg2;
        p = true;
        coltop = 0;
        exitg2 = false;
        while ((!exitg2) && (coltop < 6)) {
            b_i = 0;
            do {
                exitg1 = 0;
                if (b_i <= coltop) {
                    if (!(A[b_i + 6 * coltop] == A[coltop + 6 * b_i])) {
                        p = false;
                        exitg1 = 1;
                    } else {
                        b_i++;
                    }
                } else {
                    coltop++;
                    exitg1 = 2;
                }
            } while (exitg1 == 0);
            if (exitg1 == 1) {
                exitg2 = true;
            }
        }
        if (p) {
            double temp;
            p = true;
            for (i = 0; i < 36; i++) {
                temp = A[i];
                T[i] = temp;
                if ((!p) || (rtIsInf(temp) || rtIsNaN(temp))) {
                    p = false;
                }
            }
            if (!p) {
                for (int c_i = 0; c_i < 36; c_i++) {
                    T[c_i] = rtNaN;
                }
                i = 2;
                for (coltop = 0; coltop < 5; coltop++) {
                    if (i <= 6) {
                        memset(&T[(coltop * 6 + i) + -1], 0,
                               (7 - i) * sizeof(double));
                    }
                    i++;
                }
            } else {
                for (b_i = 0; b_i < 6; b_i++) {
                    work[b_i] = 0.0;
                }
                for (b_i = 0; b_i < 5; b_i++) {
                    double alpha1;
                    int alpha1_tmp;
                    int c_i;
                    int ia;
                    int in;
                    int iv0_tmp;
                    int jA;
                    int knt;
                    int lastc;
                    int lastv;
                    int rowleft;
                    coltop = b_i * 6 + 2;
                    in = (b_i + 1) * 6;
                    alpha1_tmp = (b_i + 6 * b_i) + 1;
                    alpha1 = T[alpha1_tmp];
                    if (b_i + 3 < 6) {
                        i = b_i + 1;
                    } else {
                        i = 4;
                    }
                    rowleft = i + coltop;
                    tau[b_i] = 0.0;
                    temp = internal::blas::xnrm2(4 - b_i, T, rowleft);
                    if (temp != 0.0) {
                        double beta1;
                        beta1 = rt_hypotd_snf(alpha1, temp);
                        if (alpha1 >= 0.0) {
                            beta1 = -beta1;
                        }
                        if (fabs(beta1) < 1.0020841800044864E-292) {
                            knt = -1;
                            c_i = (rowleft - b_i) + 3;
                            do {
                                knt++;
                                for (i = rowleft; i <= c_i; i++) {
                                    T[i - 1] *= 9.9792015476736E+291;
                                }
                                beta1 *= 9.9792015476736E+291;
                                alpha1 *= 9.9792015476736E+291;
                            } while (!(fabs(beta1) >= 1.0020841800044864E-292));
                            beta1 = rt_hypotd_snf(
                                alpha1,
                                internal::blas::xnrm2(4 - b_i, T, rowleft));
                            if (alpha1 >= 0.0) {
                                beta1 = -beta1;
                            }
                            tau[b_i] = (beta1 - alpha1) / beta1;
                            temp = 1.0 / (alpha1 - beta1);
                            c_i = (rowleft - b_i) + 3;
                            for (i = rowleft; i <= c_i; i++) {
                                T[i - 1] *= temp;
                            }
                            for (i = 0; i <= knt; i++) {
                                beta1 *= 1.0020841800044864E-292;
                            }
                            alpha1 = beta1;
                        } else {
                            tau[b_i] = (beta1 - alpha1) / beta1;
                            temp = 1.0 / (alpha1 - beta1);
                            c_i = (rowleft - b_i) + 3;
                            for (i = rowleft; i <= c_i; i++) {
                                T[i - 1] *= temp;
                            }
                            alpha1 = beta1;
                        }
                    }
                    T[alpha1_tmp] = 1.0;
                    iv0_tmp = (b_i + coltop) - 1;
                    jA = in + 1;
                    if (tau[b_i] != 0.0) {
                        lastv = 4 - b_i;
                        i = (iv0_tmp - b_i) + 4;
                        while ((lastv + 1 > 0) && (T[i] == 0.0)) {
                            lastv--;
                            i--;
                        }
                        lastc = 6;
                        exitg2 = false;
                        while ((!exitg2) && (lastc > 0)) {
                            rowleft = in + lastc;
                            ia = rowleft;
                            do {
                                exitg1 = 0;
                                if (ia <= rowleft + lastv * 6) {
                                    if (T[ia - 1] != 0.0) {
                                        exitg1 = 1;
                                    } else {
                                        ia += 6;
                                    }
                                } else {
                                    lastc--;
                                    exitg1 = 2;
                                }
                            } while (exitg1 == 0);
                            if (exitg1 == 1) {
                                exitg2 = true;
                            }
                        }
                    } else {
                        lastv = -1;
                        lastc = 0;
                    }
                    if (lastv + 1 > 0) {
                        if (lastc != 0) {
                            if (0 <= lastc - 1) {
                                memset(&work[0], 0, lastc * sizeof(double));
                            }
                            knt = iv0_tmp;
                            c_i = (in + 6 * lastv) + 1;
                            for (i = jA; i <= c_i; i += 6) {
                                rowleft = (i + lastc) - 1;
                                for (ia = i; ia <= rowleft; ia++) {
                                    coltop = ia - i;
                                    work[coltop] += T[ia - 1] * T[knt];
                                }
                                knt++;
                            }
                        }
                        if (!(-tau[b_i] == 0.0)) {
                            jA = in;
                            for (coltop = 0; coltop <= lastv; coltop++) {
                                temp = T[iv0_tmp + coltop];
                                if (temp != 0.0) {
                                    temp *= -tau[b_i];
                                    c_i = jA + 1;
                                    rowleft = lastc + jA;
                                    for (knt = c_i; knt <= rowleft; knt++) {
                                        T[knt - 1] +=
                                            work[(knt - jA) - 1] * temp;
                                    }
                                }
                                jA += 6;
                            }
                        }
                    }
                    jA = (b_i + in) + 2;
                    if (tau[b_i] != 0.0) {
                        lastv = 5 - b_i;
                        i = (iv0_tmp - b_i) + 4;
                        while ((lastv > 0) && (T[i] == 0.0)) {
                            lastv--;
                            i--;
                        }
                        lastc = 4 - b_i;
                        exitg2 = false;
                        while ((!exitg2) && (lastc + 1 > 0)) {
                            coltop = jA + lastc * 6;
                            ia = coltop;
                            do {
                                exitg1 = 0;
                                if (ia <= (coltop + lastv) - 1) {
                                    if (T[ia - 1] != 0.0) {
                                        exitg1 = 1;
                                    } else {
                                        ia++;
                                    }
                                } else {
                                    lastc--;
                                    exitg1 = 2;
                                }
                            } while (exitg1 == 0);
                            if (exitg1 == 1) {
                                exitg2 = true;
                            }
                        }
                    } else {
                        lastv = 0;
                        lastc = -1;
                    }
                    if (lastv > 0) {
                        if (lastc + 1 != 0) {
                            if (0 <= lastc) {
                                memset(&work[0], 0,
                                       (lastc + 1) * sizeof(double));
                            }
                            c_i = jA + 6 * lastc;
                            for (i = jA; i <= c_i; i += 6) {
                                temp = 0.0;
                                rowleft = (i + lastv) - 1;
                                for (ia = i; ia <= rowleft; ia++) {
                                    temp += T[ia - 1] * T[(iv0_tmp + ia) - i];
                                }
                                coltop = div_nde_s32_floor(i - jA, 6);
                                work[coltop] += temp;
                            }
                        }
                        if (!(-tau[b_i] == 0.0)) {
                            for (coltop = 0; coltop <= lastc; coltop++) {
                                temp = work[coltop];
                                if (temp != 0.0) {
                                    temp *= -tau[b_i];
                                    c_i = lastv + jA;
                                    for (knt = jA; knt < c_i; knt++) {
                                        T[knt - 1] +=
                                            T[(iv0_tmp + knt) - jA] * temp;
                                    }
                                }
                                jA += 6;
                            }
                        }
                    }
                    T[alpha1_tmp] = alpha1;
                }
                internal::lapack::xhseqr(T);
            }
            for (i = 0; i < 6; i++) {
                V[i].re = T[i + 6 * i];
                V[i].im = 0.0;
            }
        } else {
            eigStandard(A, V);
        }
    }
}

} // namespace coder
