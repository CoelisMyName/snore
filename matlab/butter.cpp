//
// File: butter.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "butter.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "eig.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const double Wn[2]
//                double varargout_1[7]
//                double varargout_2[7]
// Return Type  : void
//
namespace coder {
    void butter(const double Wn[2], double varargout_1[7], double varargout_2[7]) {
        static const signed char b_iv[18] = {-1, 0, 0, 0, -1, 0, 0, 0, -1,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0};
        static const signed char b_iv1[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        static const signed char b[7] = {1, 0, -3, 0, 3, 0, -1};
        static const signed char b_iv2[6] = {1, 1, 1, -1, -1, -1};
        creal_T b_c[7];
        creal_T p[6];
        creal_T x[6];
        creal_T c[3];
        double A[36];
        double t1[36];
        double t1_tmp[36];
        double a[9];
        double b_a[4];
        double Wn1;
        double d;
        double d1;
        double q;
        double u_idx_0;
        double u_idx_1;
        double x_re;
        double zWn_re;
        int b_i;
        int i;
        int i1;
        int j;
        int jA;
        int k;
        int kAcol;
        int mmj_tmp;
        signed char ipiv[6];
        signed char b1[2];
        u_idx_0 = 4.0 * tan(3.1415926535897931 * Wn[0] / 2.0);
        u_idx_1 = 4.0 * tan(3.1415926535897931 * Wn[1] / 2.0);
        memset(&a[0], 0, 9U * sizeof(double));
        a[0] = -1.0;
        c[0].re = 1.0;
        c[0].im = 0.0;
        for (j = 0; j < 2; j++) {
            q = 1.7320508075688774 * static_cast<double>(j) + -0.86602540378443871;
            d = c[j].im;
            d1 = c[j].re;
            c[j + 1].re = 0.49999999999999978 * d1 - -q * d;
            c[j + 1].im = 0.49999999999999978 * d + -q * d1;
            for (k = j + 1; k >= 2; k--) {
                c[1].re -= -0.49999999999999978 * c[0].re - q * c[0].im;
                c[1].im -= -0.49999999999999978 * c[0].im + q * c[0].re;
            }
        }
        d = (1.0 - -c[1].re * 0.0) / 1.0000000000000002;
        b_a[1] = d;
        b_a[0] = -c[1].re - d * 0.0;
        d = (0.0 - -c[2].re * 0.0) / 1.0000000000000002;
        b_a[3] = d;
        b_a[2] = -c[2].re - d * 0.0;
        b1[1] = 0;
        b1[0] = 1;
        for (i = 0; i < 2; i++) {
            a[i + 1] = b1[i];
            d = b_a[i + 2];
            d1 = b_a[i];
            a[i + 4] = d1 + d * 0.0;
            a[i + 7] = d1 * 0.0 + d * 1.0000000000000002;
        }
        Wn1 = sqrt(u_idx_0 * u_idx_1);
        q = Wn1 / (u_idx_1 - u_idx_0);
        memset(&A[0], 0, 36U * sizeof(double));
        for (k = 0; k < 6; k++) {
            A[k + 6 * k] = 1.0;
        }
        for (i = 0; i < 3; i++) {
            t1_tmp[6 * i] = Wn1 * (a[3 * i] / q) * 0.5 / 2.0;
            jA = 6 * (i + 3);
            t1_tmp[jA] = Wn1 * static_cast<double>(b_iv1[3 * i]) * 0.5 / 2.0;
            kAcol = 3 * i + 1;
            t1_tmp[6 * i + 1] = Wn1 * (a[kAcol] / q) * 0.5 / 2.0;
            t1_tmp[jA + 1] = Wn1 * static_cast<double>(b_iv1[kAcol]) * 0.5 / 2.0;
            kAcol = 3 * i + 2;
            t1_tmp[6 * i + 2] = Wn1 * (a[kAcol] / q) * 0.5 / 2.0;
            t1_tmp[jA + 2] = Wn1 * static_cast<double>(b_iv1[kAcol]) * 0.5 / 2.0;
        }
        for (i = 0; i < 6; i++) {
            t1_tmp[6 * i + 3] = Wn1 * static_cast<double>(b_iv[3 * i]) * 0.5 / 2.0;
            t1_tmp[6 * i + 4] =
                    Wn1 * static_cast<double>(b_iv[3 * i + 1]) * 0.5 / 2.0;
            t1_tmp[6 * i + 5] =
                    Wn1 * static_cast<double>(b_iv[3 * i + 2]) * 0.5 / 2.0;
        }
        for (i = 0; i < 36; i++) {
            d = A[i];
            d1 = t1_tmp[i];
            t1[i] = d + d1;
            d -= d1;
            A[i] = d;
        }
        for (i = 0; i < 6; i++) {
            ipiv[i] = static_cast<signed char>(i + 1);
        }
        for (j = 0; j < 5; j++) {
            int b_tmp;
            int jp1j;
            signed char i2;
            mmj_tmp = 4 - j;
            b_tmp = j * 7;
            jp1j = b_tmp + 2;
            jA = 6 - j;
            kAcol = 0;
            q = fabs(A[b_tmp]);
            for (k = 2; k <= jA; k++) {
                u_idx_0 = fabs(A[(b_tmp + k) - 1]);
                if (u_idx_0 > q) {
                    kAcol = k - 1;
                    q = u_idx_0;
                }
            }
            if (A[b_tmp + kAcol] != 0.0) {
                if (kAcol != 0) {
                    jA = j + kAcol;
                    ipiv[j] = static_cast<signed char>(jA + 1);
                    for (k = 0; k < 6; k++) {
                        b_i = j + k * 6;
                        q = A[b_i];
                        kAcol = jA + k * 6;
                        A[b_i] = A[kAcol];
                        A[kAcol] = q;
                    }
                }
                i = (b_tmp - j) + 6;
                for (b_i = jp1j; b_i <= i; b_i++) {
                    A[b_i - 1] /= A[b_tmp];
                }
            }
            jA = b_tmp;
            for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
                q = A[(b_tmp + jp1j * 6) + 6];
                if (q != 0.0) {
                    i = jA + 8;
                    i1 = (jA - j) + 12;
                    for (kAcol = i; kAcol <= i1; kAcol++) {
                        A[kAcol - 1] += A[((b_tmp + kAcol) - jA) - 7] * -q;
                    }
                }
                jA += 6;
            }
            i2 = ipiv[j];
            if (i2 != j + 1) {
                for (jp1j = 0; jp1j < 6; jp1j++) {
                    b_i = j + 6 * jp1j;
                    q = t1[b_i];
                    mmj_tmp = (i2 + 6 * jp1j) - 1;
                    t1[b_i] = t1[mmj_tmp];
                    t1[mmj_tmp] = q;
                }
            }
        }
        for (j = 0; j < 6; j++) {
            jA = 6 * j;
            for (k = 0; k < 6; k++) {
                kAcol = 6 * k;
                i = k + jA;
                if (t1[i] != 0.0) {
                    i1 = k + 2;
                    for (b_i = i1; b_i < 7; b_i++) {
                        mmj_tmp = (b_i + jA) - 1;
                        t1[mmj_tmp] -= t1[i] * A[(b_i + kAcol) - 1];
                    }
                }
            }
        }
        for (j = 0; j < 6; j++) {
            jA = 6 * j;
            for (k = 5; k >= 0; k--) {
                kAcol = 6 * k;
                i = k + jA;
                d = t1[i];
                if (d != 0.0) {
                    t1[i] = d / A[k + kAcol];
                    for (b_i = 0; b_i < k; b_i++) {
                        mmj_tmp = b_i + jA;
                        t1[mmj_tmp] -= t1[i] * A[b_i + kAcol];
                    }
                }
            }
        }
        eig(t1, p);
        q = 2.0 * rt_atan2d_snf(Wn1, 4.0);
        zWn_re = q * 0.0;
        if (q == 0.0) {
            zWn_re = exp(zWn_re);
            u_idx_1 = 0.0;
        } else {
            u_idx_0 = exp(zWn_re / 2.0);
            zWn_re = u_idx_0 * (u_idx_0 * cos(q));
            u_idx_1 = u_idx_0 * (u_idx_0 * sin(q));
        }
        for (b_i = 0; b_i < 6; b_i++) {
            x[b_i].re = zWn_re - p[b_i].re;
            x[b_i].im = u_idx_1 - p[b_i].im;
        }
        x_re = x[0].re;
        Wn1 = x[0].im;
        for (k = 0; k < 5; k++) {
            d = x[k + 1].re;
            d1 = x[k + 1].im;
            q = x_re * d - Wn1 * d1;
            Wn1 = x_re * d1 + Wn1 * d;
            x_re = q;
        }
        for (b_i = 0; b_i < 6; b_i++) {
            x[b_i].re = zWn_re - static_cast<double>(b_iv2[b_i]);
            x[b_i].im = u_idx_1;
        }
        zWn_re = x[0].re;
        u_idx_1 = x[0].im;
        for (k = 0; k < 5; k++) {
            d = x[k + 1].re;
            d1 = x[k + 1].im;
            q = zWn_re * d - u_idx_1 * d1;
            u_idx_1 = zWn_re * d1 + u_idx_1 * d;
            zWn_re = q;
        }
        if (u_idx_1 == 0.0) {
            if (Wn1 == 0.0) {
                x_re /= zWn_re;
            } else if (x_re == 0.0) {
                x_re = 0.0;
            } else {
                x_re /= zWn_re;
            }
        } else if (zWn_re == 0.0) {
            if (x_re == 0.0) {
                x_re = Wn1 / u_idx_1;
            } else if (Wn1 == 0.0) {
                x_re = 0.0;
            } else {
                x_re = Wn1 / u_idx_1;
            }
        } else {
            q = fabs(zWn_re);
            u_idx_0 = fabs(u_idx_1);
            if (q > u_idx_0) {
                u_idx_0 = u_idx_1 / zWn_re;
                x_re = (x_re + u_idx_0 * Wn1) / (zWn_re + u_idx_0 * u_idx_1);
            } else if (u_idx_0 == q) {
                if (zWn_re > 0.0) {
                    zWn_re = 0.5;
                } else {
                    zWn_re = -0.5;
                }
                if (u_idx_1 > 0.0) {
                    u_idx_1 = 0.5;
                } else {
                    u_idx_1 = -0.5;
                }
                x_re = (x_re * zWn_re + Wn1 * u_idx_1) / q;
            } else {
                u_idx_0 = zWn_re / u_idx_1;
                x_re = (u_idx_0 * x_re + Wn1) / (u_idx_1 + u_idx_0 * zWn_re);
            }
        }
        b_c[0].re = 1.0;
        b_c[0].im = 0.0;
        for (j = 0; j < 6; j++) {
            q = -p[j].re;
            u_idx_0 = -p[j].im;
            d = b_c[j].im;
            d1 = b_c[j].re;
            b_c[j + 1].re = q * d1 - u_idx_0 * d;
            b_c[j + 1].im = q * d + u_idx_0 * d1;
            for (k = j + 1; k >= 2; k--) {
                d = p[j].re;
                d1 = p[j].im;
                u_idx_0 = d * b_c[k - 2].im + d1 * b_c[k - 2].re;
                b_c[k - 1].re -= d * b_c[k - 2].re - d1 * b_c[k - 2].im;
                b_c[k - 1].im -= u_idx_0;
            }
        }
        for (i = 0; i < 7; i++) {
            varargout_2[i] = b_c[i].re;
            varargout_1[i] = x_re * static_cast<double>(b[i]);
        }
    }

} // namespace coder

//
// File trailer for butter.cpp
//
// [EOF]
//
