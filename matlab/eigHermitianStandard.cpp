//
// File: eigHermitianStandard.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "eigHermitianStandard.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "xdhseqr.h"
#include "xdlapy3.h"
#include "xnrm2.h"
#include "xzhseqr.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const creal_T A_data[]
//                const int A_size[2]
//                creal_T V_data[]
//                int *V_size
// Return Type  : void
//
namespace coder {
    void eigHermitianStandard(const creal_T A_data[], const int A_size[2],
                              creal_T V_data[], int *V_size) {
        creal_T T_data[144];
        creal_T work_data[12];
        creal_T tau_data[11];
        creal_T c;
        int T_size[2];
        int k;
        int n;
        int rowleft;
        boolean_T p;
        T_size[0] = A_size[0];
        T_size[1] = A_size[1];
        rowleft = A_size[0] * A_size[1];
        if (0 <= rowleft - 1) {
            memcpy(&T_data[0], &A_data[0], rowleft * sizeof(creal_T));
        }
        p = true;
        for (k = 0; k < rowleft; k++) {
            if ((!p) || (rtIsInf(A_data[k].re) || rtIsInf(A_data[k].im) ||
                         (rtIsNaN(A_data[k].re) || rtIsNaN(A_data[k].im)))) {
                p = false;
            }
        }
        if (!p) {
            int i;
            T_size[0] = static_cast<signed char>(A_size[0]);
            rowleft = static_cast<signed char>(A_size[0]) *
                      static_cast<signed char>(A_size[1]);
            for (i = 0; i < rowleft; i++) {
                T_data[i].re = rtNaN;
                T_data[i].im = 0.0;
            }
            rowleft = static_cast<signed char>(A_size[0]);
            if (1 < static_cast<signed char>(A_size[0])) {
                int c_i;
                int knt;
                knt = 2;
                if (static_cast<signed char>(A_size[0]) - 2 <
                    static_cast<signed char>(A_size[1]) - 1) {
                    c_i = static_cast<signed char>(A_size[0]) - 1;
                } else {
                    c_i = static_cast<signed char>(A_size[1]);
                }
                for (k = 0; k < c_i; k++) {
                    for (int b_i = knt; b_i <= rowleft; b_i++) {
                        i = (b_i + T_size[0] * k) - 1;
                        T_data[i].re = 0.0;
                        T_data[i].im = 0.0;
                    }
                    knt++;
                }
            }
        } else {
            int b_i;
            int c_i;
            int i;
            int knt;
            n = A_size[0];
            rowleft = static_cast<signed char>(A_size[0]);
            if (0 <= rowleft - 1) {
                memset(&work_data[0], 0, rowleft * sizeof(creal_T));
            }
            i = A_size[0];
            for (b_i = 0; b_i <= i - 2; b_i++) {
                double alpha1_im;
                double alpha1_re;
                double ar;
                double beta1;
                double d;
                double temp_im;
                int exitg1;
                int i1;
                int i2;
                int ia;
                int in;
                int iv0_tmp;
                int jA;
                int lastc;
                int lastv;
                int n_tmp_tmp;
                boolean_T exitg2;
                c_i = b_i * n;
                in = (b_i + 1) * n;
                knt = (b_i + T_size[0] * b_i) + 1;
                alpha1_re = T_data[knt].re;
                alpha1_im = T_data[knt].im;
                rowleft = b_i + 3;
                if (rowleft >= n) {
                    rowleft = n;
                }
                rowleft += c_i;
                n_tmp_tmp = n - b_i;
                tau_data[b_i].re = 0.0;
                tau_data[b_i].im = 0.0;
                if (n_tmp_tmp - 1 > 0) {
                    temp_im = internal::blas::xnrm2(n_tmp_tmp - 2, T_data, rowleft);
                    if ((temp_im != 0.0) || (T_data[knt].im != 0.0)) {
                        beta1 = internal::xdlapy3(T_data[knt].re, T_data[knt].im,
                                                  temp_im);
                        if (T_data[knt].re >= 0.0) {
                            beta1 = -beta1;
                        }
                        if (fabs(beta1) < 1.0020841800044864E-292) {
                            knt = -1;
                            i1 = (rowleft + n_tmp_tmp) - 3;
                            do {
                                knt++;
                                for (k = rowleft; k <= i1; k++) {
                                    temp_im = T_data[k - 1].im;
                                    d = T_data[k - 1].re;
                                    ar = 9.9792015476736E+291 * temp_im + 0.0 * d;
                                    d = 9.9792015476736E+291 * d - 0.0 * temp_im;
                                    T_data[k - 1].re = d;
                                    T_data[k - 1].im = ar;
                                }
                                beta1 *= 9.9792015476736E+291;
                                alpha1_re *= 9.9792015476736E+291;
                                alpha1_im *= 9.9792015476736E+291;
                            } while (!(fabs(beta1) >= 1.0020841800044864E-292));
                            beta1 = internal::xdlapy3(
                                    alpha1_re, alpha1_im,
                                    internal::blas::xnrm2(n_tmp_tmp - 2, T_data,
                                                          rowleft));
                            if (alpha1_re >= 0.0) {
                                beta1 = -beta1;
                            }
                            ar = beta1 - alpha1_re;
                            if (0.0 - alpha1_im == 0.0) {
                                tau_data[b_i].re = ar / beta1;
                                tau_data[b_i].im = 0.0;
                            } else if (ar == 0.0) {
                                tau_data[b_i].re = 0.0;
                                tau_data[b_i].im = (0.0 - alpha1_im) / beta1;
                            } else {
                                tau_data[b_i].re = ar / beta1;
                                tau_data[b_i].im = (0.0 - alpha1_im) / beta1;
                            }
                            c.re = alpha1_re - beta1;
                            c.im = alpha1_im;
                            c = internal::recip(c);
                            for (k = rowleft; k <= i1; k++) {
                                temp_im = T_data[k - 1].im;
                                d = T_data[k - 1].re;
                                ar = c.re * temp_im + c.im * d;
                                d = c.re * d - c.im * temp_im;
                                T_data[k - 1].re = d;
                                T_data[k - 1].im = ar;
                            }
                            for (k = 0; k <= knt; k++) {
                                beta1 *= 1.0020841800044864E-292;
                            }
                            alpha1_re = beta1;
                            alpha1_im = 0.0;
                        } else {
                            ar = beta1 - T_data[knt].re;
                            temp_im = 0.0 - T_data[knt].im;
                            if (temp_im == 0.0) {
                                tau_data[b_i].re = ar / beta1;
                                tau_data[b_i].im = 0.0;
                            } else if (ar == 0.0) {
                                tau_data[b_i].re = 0.0;
                                tau_data[b_i].im = temp_im / beta1;
                            } else {
                                tau_data[b_i].re = ar / beta1;
                                tau_data[b_i].im = temp_im / beta1;
                            }
                            c.re = T_data[knt].re - beta1;
                            c.im = T_data[knt].im;
                            c = internal::recip(c);
                            i1 = (rowleft + n_tmp_tmp) - 3;
                            for (k = rowleft; k <= i1; k++) {
                                temp_im = T_data[k - 1].im;
                                d = T_data[k - 1].re;
                                ar = c.re * temp_im + c.im * d;
                                d = c.re * d - c.im * temp_im;
                                T_data[k - 1].re = d;
                                T_data[k - 1].im = ar;
                            }
                            alpha1_re = beta1;
                            alpha1_im = 0.0;
                        }
                    }
                }
                i1 = (b_i + T_size[0] * b_i) + 1;
                T_data[i1].re = 1.0;
                T_data[i1].im = 0.0;
                iv0_tmp = (b_i + c_i) + 1;
                k = in + 1;
                if ((tau_data[b_i].re != 0.0) || (tau_data[b_i].im != 0.0)) {
                    lastv = n_tmp_tmp - 2;
                    c_i = (iv0_tmp + n_tmp_tmp) - 3;
                    while ((lastv + 1 > 0) && ((T_data[c_i + 1].re == 0.0) &&
                                               (T_data[c_i + 1].im == 0.0))) {
                        lastv--;
                        c_i--;
                    }
                    lastc = n;
                    exitg2 = false;
                    while ((!exitg2) && (lastc > 0)) {
                        rowleft = in + lastc;
                        ia = rowleft;
                        do {
                            exitg1 = 0;
                            if ((n > 0) && (ia <= rowleft + lastv * n)) {
                                if ((T_data[ia - 1].re != 0.0) ||
                                    (T_data[ia - 1].im != 0.0)) {
                                    exitg1 = 1;
                                } else {
                                    ia += n;
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
                            memset(&work_data[0], 0, lastc * sizeof(creal_T));
                        }
                        knt = iv0_tmp;
                        i1 = (in + n * lastv) + 1;
                        for (rowleft = k; n < 0 ? rowleft >= i1 : rowleft <= i1;
                             rowleft += n) {
                            c.re = T_data[knt].re - 0.0 * T_data[knt].im;
                            c.im = T_data[knt].im + 0.0 * T_data[knt].re;
                            i2 = (rowleft + lastc) - 1;
                            for (ia = rowleft; ia <= i2; ia++) {
                                c_i = ia - rowleft;
                                temp_im = T_data[ia - 1].re;
                                d = T_data[ia - 1].im;
                                work_data[c_i].re += temp_im * c.re - d * c.im;
                                work_data[c_i].im += temp_im * c.im + d * c.re;
                            }
                            knt++;
                        }
                    }
                    c.re = -tau_data[b_i].re;
                    c.im = -tau_data[b_i].im;
                    if ((!(c.re == 0.0)) || (!(c.im == 0.0))) {
                        jA = in;
                        for (k = 0; k <= lastv; k++) {
                            knt = iv0_tmp + k;
                            if ((T_data[knt].re != 0.0) ||
                                (T_data[knt].im != 0.0)) {
                                beta1 =
                                        T_data[knt].re * c.re + T_data[knt].im * c.im;
                                temp_im =
                                        T_data[knt].re * c.im - T_data[knt].im * c.re;
                                i1 = jA + 1;
                                i2 = lastc + jA;
                                for (c_i = i1; c_i <= i2; c_i++) {
                                    knt = (c_i - jA) - 1;
                                    T_data[c_i - 1].re +=
                                            work_data[knt].re * beta1 -
                                            work_data[knt].im * temp_im;
                                    T_data[c_i - 1].im +=
                                            work_data[knt].re * temp_im +
                                            work_data[knt].im * beta1;
                                }
                            }
                            jA += n;
                        }
                    }
                }
                jA = (b_i + in) + 2;
                beta1 = tau_data[b_i].re;
                temp_im = -tau_data[b_i].im;
                if ((beta1 != 0.0) || (temp_im != 0.0)) {
                    lastv = n_tmp_tmp - 1;
                    c_i = (iv0_tmp + n_tmp_tmp) - 3;
                    while ((lastv > 0) && ((T_data[c_i + 1].re == 0.0) &&
                                           (T_data[c_i + 1].im == 0.0))) {
                        lastv--;
                        c_i--;
                    }
                    lastc = n_tmp_tmp - 2;
                    exitg2 = false;
                    while ((!exitg2) && (lastc + 1 > 0)) {
                        rowleft = jA + lastc * n;
                        ia = rowleft;
                        do {
                            exitg1 = 0;
                            if (ia <= (rowleft + lastv) - 1) {
                                if ((T_data[ia - 1].re != 0.0) ||
                                    (T_data[ia - 1].im != 0.0)) {
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
                            memset(&work_data[0], 0, (lastc + 1) * sizeof(creal_T));
                        }
                        knt = 0;
                        i1 = jA + n * lastc;
                        for (rowleft = jA; n < 0 ? rowleft >= i1 : rowleft <= i1;
                             rowleft += n) {
                            c.re = 0.0;
                            c.im = 0.0;
                            i2 = (rowleft + lastv) - 1;
                            for (ia = rowleft; ia <= i2; ia++) {
                                c_i = (iv0_tmp + ia) - rowleft;
                                c.re += T_data[ia - 1].re * T_data[c_i].re +
                                        T_data[ia - 1].im * T_data[c_i].im;
                                c.im += T_data[ia - 1].re * T_data[c_i].im -
                                        T_data[ia - 1].im * T_data[c_i].re;
                            }
                            work_data[knt].re += c.re - 0.0 * c.im;
                            work_data[knt].im += c.im + 0.0 * c.re;
                            knt++;
                        }
                    }
                    c.re = -beta1;
                    c.im = -temp_im;
                    if ((!(-beta1 == 0.0)) || (!(-temp_im == 0.0))) {
                        for (k = 0; k <= lastc; k++) {
                            temp_im = work_data[k].re;
                            d = work_data[k].im;
                            if ((temp_im != 0.0) || (d != 0.0)) {
                                beta1 = temp_im * c.re + d * c.im;
                                temp_im = temp_im * c.im - d * c.re;
                                i1 = lastv + jA;
                                for (c_i = jA; c_i < i1; c_i++) {
                                    knt = (iv0_tmp + c_i) - jA;
                                    ar = T_data[knt].re * temp_im +
                                         T_data[knt].im * beta1;
                                    T_data[c_i - 1].re += T_data[knt].re * beta1 -
                                                          T_data[knt].im * temp_im;
                                    T_data[c_i - 1].im += ar;
                                }
                            }
                            jA += n;
                        }
                    }
                }
                i1 = (b_i + T_size[0] * b_i) + 1;
                T_data[i1].re = alpha1_re;
                T_data[i1].im = alpha1_im;
            }
            internal::reflapack::eml_zlahqr(T_data, T_size);
            rowleft = T_size[0];
            if (3 < T_size[0]) {
                knt = 4;
                if (T_size[0] - 4 < T_size[1] - 1) {
                    c_i = T_size[0] - 3;
                } else {
                    c_i = T_size[1];
                }
                for (k = 0; k < c_i; k++) {
                    for (b_i = knt; b_i <= rowleft; b_i++) {
                        i = (b_i + T_size[0] * k) - 1;
                        T_data[i].re = 0.0;
                        T_data[i].im = 0.0;
                    }
                    knt++;
                }
            }
        }
        n = T_size[0];
        *V_size = T_size[0];
        for (k = 0; k < n; k++) {
            V_data[k].re = T_data[k + T_size[0] * k].re;
            V_data[k].im = 0.0;
        }
    }

//
// Arguments    : const double A_data[]
//                const int A_size[2]
//                double V_data[]
//                int *V_size
// Return Type  : void
//
    void eigHermitianStandard(const double A_data[], const int A_size[2],
                              double V_data[], int *V_size) {
        double T_data[100];
        double work_data[10];
        double tau_data[9];
        int T_size[2];
        int jA;
        int n;
        int rowleft;
        boolean_T p;
        T_size[0] = A_size[0];
        T_size[1] = A_size[1];
        rowleft = A_size[0] * A_size[1];
        if (0 <= rowleft - 1) {
            memcpy(&T_data[0], &A_data[0], rowleft * sizeof(double));
        }
        p = true;
        for (jA = 0; jA < rowleft; jA++) {
            if ((!p) || (rtIsInf(A_data[jA]) || rtIsNaN(A_data[jA]))) {
                p = false;
            }
        }
        if (!p) {
            T_size[0] = static_cast<signed char>(A_size[0]);
            rowleft = static_cast<signed char>(A_size[0]) *
                      static_cast<signed char>(A_size[1]);
            for (int i = 0; i < rowleft; i++) {
                T_data[i] = rtNaN;
            }
            rowleft = static_cast<signed char>(A_size[0]);
            if (1 < static_cast<signed char>(A_size[0])) {
                int c_i;
                int knt;
                c_i = 2;
                if (static_cast<signed char>(A_size[0]) - 2 <
                    static_cast<signed char>(A_size[1]) - 1) {
                    knt = static_cast<signed char>(A_size[0]) - 1;
                } else {
                    knt = static_cast<signed char>(A_size[1]);
                }
                for (int j = 0; j < knt; j++) {
                    for (int b_i = c_i; b_i <= rowleft; b_i++) {
                        T_data[(b_i + T_size[0] * j) - 1] = 0.0;
                    }
                    c_i++;
                }
            }
        } else {
            int b_i;
            int c_i;
            int i;
            int j;
            int knt;
            n = A_size[0];
            rowleft = static_cast<signed char>(A_size[0]);
            if (0 <= rowleft - 1) {
                memset(&work_data[0], 0, rowleft * sizeof(double));
            }
            i = A_size[0];
            for (b_i = 0; b_i <= i - 2; b_i++) {
                double alpha1;
                double temp;
                int alpha1_tmp;
                int exitg1;
                int i1;
                int i2;
                int ia;
                int in;
                int iv0_tmp;
                int lastc;
                int lastv;
                int n_tmp_tmp;
                boolean_T exitg2;
                j = b_i * n;
                in = (b_i + 1) * n;
                alpha1_tmp = (b_i + T_size[0] * b_i) + 1;
                alpha1 = T_data[alpha1_tmp];
                rowleft = b_i + 3;
                if (rowleft >= n) {
                    rowleft = n;
                }
                c_i = rowleft + j;
                n_tmp_tmp = n - b_i;
                tau_data[b_i] = 0.0;
                if (n_tmp_tmp - 1 > 0) {
                    temp = internal::blas::b_xnrm2(n_tmp_tmp - 2, T_data, c_i);
                    if (temp != 0.0) {
                        double beta1;
                        beta1 = rt_hypotd_snf(alpha1, temp);
                        if (alpha1 >= 0.0) {
                            beta1 = -beta1;
                        }
                        if (fabs(beta1) < 1.0020841800044864E-292) {
                            knt = -1;
                            i1 = (c_i + n_tmp_tmp) - 3;
                            do {
                                knt++;
                                for (jA = c_i; jA <= i1; jA++) {
                                    T_data[jA - 1] *= 9.9792015476736E+291;
                                }
                                beta1 *= 9.9792015476736E+291;
                                alpha1 *= 9.9792015476736E+291;
                            } while (!(fabs(beta1) >= 1.0020841800044864E-292));
                            beta1 = rt_hypotd_snf(
                                    alpha1, internal::blas::b_xnrm2(n_tmp_tmp - 2,
                                                                    T_data, c_i));
                            if (alpha1 >= 0.0) {
                                beta1 = -beta1;
                            }
                            tau_data[b_i] = (beta1 - alpha1) / beta1;
                            temp = 1.0 / (alpha1 - beta1);
                            for (jA = c_i; jA <= i1; jA++) {
                                T_data[jA - 1] *= temp;
                            }
                            for (jA = 0; jA <= knt; jA++) {
                                beta1 *= 1.0020841800044864E-292;
                            }
                            alpha1 = beta1;
                        } else {
                            tau_data[b_i] = (beta1 - alpha1) / beta1;
                            temp = 1.0 / (alpha1 - beta1);
                            i1 = (c_i + n_tmp_tmp) - 3;
                            for (jA = c_i; jA <= i1; jA++) {
                                T_data[jA - 1] *= temp;
                            }
                            alpha1 = beta1;
                        }
                    }
                }
                T_data[alpha1_tmp] = 1.0;
                iv0_tmp = (b_i + j) + 1;
                j = in + 1;
                if (tau_data[b_i] != 0.0) {
                    lastv = n_tmp_tmp - 2;
                    c_i = (iv0_tmp + n_tmp_tmp) - 3;
                    while ((lastv + 1 > 0) && (T_data[c_i + 1] == 0.0)) {
                        lastv--;
                        c_i--;
                    }
                    lastc = n;
                    exitg2 = false;
                    while ((!exitg2) && (lastc > 0)) {
                        rowleft = in + lastc;
                        ia = rowleft;
                        do {
                            exitg1 = 0;
                            if ((n > 0) && (ia <= rowleft + lastv * n)) {
                                if (T_data[ia - 1] != 0.0) {
                                    exitg1 = 1;
                                } else {
                                    ia += n;
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
                            memset(&work_data[0], 0, lastc * sizeof(double));
                        }
                        knt = iv0_tmp;
                        i1 = (in + n * lastv) + 1;
                        for (rowleft = j; n < 0 ? rowleft >= i1 : rowleft <= i1;
                             rowleft += n) {
                            i2 = (rowleft + lastc) - 1;
                            for (ia = rowleft; ia <= i2; ia++) {
                                c_i = ia - rowleft;
                                work_data[c_i] += T_data[ia - 1] * T_data[knt];
                            }
                            knt++;
                        }
                    }
                    if (!(-tau_data[b_i] == 0.0)) {
                        jA = in;
                        for (j = 0; j <= lastv; j++) {
                            i1 = iv0_tmp + j;
                            if (T_data[i1] != 0.0) {
                                temp = T_data[i1] * -tau_data[b_i];
                                i1 = jA + 1;
                                i2 = lastc + jA;
                                for (knt = i1; knt <= i2; knt++) {
                                    T_data[knt - 1] +=
                                            work_data[(knt - jA) - 1] * temp;
                                }
                            }
                            jA += n;
                        }
                    }
                }
                jA = (b_i + in) + 2;
                if (tau_data[b_i] != 0.0) {
                    lastv = n_tmp_tmp - 1;
                    c_i = (iv0_tmp + n_tmp_tmp) - 3;
                    while ((lastv > 0) && (T_data[c_i + 1] == 0.0)) {
                        lastv--;
                        c_i--;
                    }
                    lastc = n_tmp_tmp - 2;
                    exitg2 = false;
                    while ((!exitg2) && (lastc + 1 > 0)) {
                        rowleft = jA + lastc * n;
                        ia = rowleft;
                        do {
                            exitg1 = 0;
                            if (ia <= (rowleft + lastv) - 1) {
                                if (T_data[ia - 1] != 0.0) {
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
                            memset(&work_data[0], 0, (lastc + 1) * sizeof(double));
                        }
                        knt = 0;
                        i1 = jA + n * lastc;
                        for (rowleft = jA; n < 0 ? rowleft >= i1 : rowleft <= i1;
                             rowleft += n) {
                            temp = 0.0;
                            i2 = (rowleft + lastv) - 1;
                            for (ia = rowleft; ia <= i2; ia++) {
                                temp += T_data[ia - 1] *
                                        T_data[(iv0_tmp + ia) - rowleft];
                            }
                            work_data[knt] += temp;
                            knt++;
                        }
                    }
                    if (!(-tau_data[b_i] == 0.0)) {
                        for (j = 0; j <= lastc; j++) {
                            temp = work_data[j];
                            if (temp != 0.0) {
                                temp *= -tau_data[b_i];
                                i1 = lastv + jA;
                                for (knt = jA; knt < i1; knt++) {
                                    T_data[knt - 1] +=
                                            T_data[(iv0_tmp + knt) - jA] * temp;
                                }
                            }
                            jA += n;
                        }
                    }
                }
                T_data[alpha1_tmp] = alpha1;
            }
            internal::reflapack::eml_dlahqr(T_data, T_size);
            rowleft = T_size[0];
            if (3 < T_size[0]) {
                c_i = 4;
                if (T_size[0] - 4 < T_size[1] - 1) {
                    knt = T_size[0] - 3;
                } else {
                    knt = T_size[1];
                }
                for (j = 0; j < knt; j++) {
                    for (b_i = c_i; b_i <= rowleft; b_i++) {
                        T_data[(b_i + T_size[0] * j) - 1] = 0.0;
                    }
                    c_i++;
                }
            }
        }
        n = T_size[0];
        *V_size = T_size[0];
        for (jA = 0; jA < n; jA++) {
            V_data[jA] = T_data[jA + T_size[0] * jA];
        }
    }

} // namespace coder

//
// File trailer for eigHermitianStandard.cpp
//
// [EOF]
//
