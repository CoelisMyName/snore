//
// File: butter.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "butter.h"
#include "SnoringRecognition_data.h"
#include "eig.h"
#include "rt_nonfinite.h"
#include "zp2ss.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1) {
    double y;
    if (rtIsNaN(u0) || rtIsNaN(u1)) {
        y = rtNaN;
    } else if (rtIsInf(u0) && rtIsInf(u1)) {
        int b_u0;
        int b_u1;
        if (u0 > 0.0) {
            b_u0 = 1;
        } else {
            b_u0 = -1;
        }
        if (u1 > 0.0) {
            b_u1 = 1;
        } else {
            b_u1 = -1;
        }
        y = atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
    } else if (u1 == 0.0) {
        if (u0 > 0.0) {
            y = RT_PI / 2.0;
        } else if (u0 < 0.0) {
            y = -(RT_PI / 2.0);
        } else {
            y = 0.0;
        }
    } else {
        y = atan2(u0, u1);
    }
    return y;
}

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
        static const signed char b_b[7] = {1, 0, -3, 0, 3, 0, -1};
        static const signed char b_iv2[6] = {1, 1, 1, -1, -1, -1};
        creal_T b_c[7];
        creal_T p[6];
        creal_T x[6];
        double b_t1_tmp[36];
        double t1[36];
        double t1_tmp[36];
        double a[9];
        double b[3];
        double c[3];
        double Wn1;
        double d;
        double im;
        double q;
        double u_idx_0;
        double u_idx_1;
        double x_re;
        double zWn_re;
        int i;
        int i1;
        int j;
        int jA;
        int jBcol;
        int k;
        int mmj_tmp;
        int temp_tmp;
        signed char ipiv[6];
        u_idx_0 = 4.0 * tan(3.1415926535897931 * Wn[0] / 2.0);
        u_idx_1 = 4.0 * tan(3.1415926535897931 * Wn[1] / 2.0);
        zp2ss(a, b, c, &q);
        Wn1 = sqrt(u_idx_0 * u_idx_1);
        q = Wn1 / (u_idx_1 - u_idx_0);
        memset(&t1_tmp[0], 0, 36U * sizeof(double));
        for (k = 0; k < 6; k++) {
            t1_tmp[k + 6 * k] = 1.0;
        }
        for (i = 0; i < 3; i++) {
            b_t1_tmp[6 * i] = Wn1 * (a[3 * i] / q) * 0.5 / 2.0;
            jBcol = 6 * (i + 3);
            b_t1_tmp[jBcol] = Wn1 * static_cast<double>(b_iv1[3 * i]) * 0.5 / 2.0;
            jA = 3 * i + 1;
            b_t1_tmp[6 * i + 1] = Wn1 * (a[jA] / q) * 0.5 / 2.0;
            b_t1_tmp[jBcol + 1] = Wn1 * static_cast<double>(b_iv1[jA]) * 0.5 / 2.0;
            jA = 3 * i + 2;
            b_t1_tmp[6 * i + 2] = Wn1 * (a[jA] / q) * 0.5 / 2.0;
            b_t1_tmp[jBcol + 2] = Wn1 * static_cast<double>(b_iv1[jA]) * 0.5 / 2.0;
        }
        for (i = 0; i < 6; i++) {
            b_t1_tmp[6 * i + 3] = Wn1 * static_cast<double>(b_iv[3 * i]) * 0.5 / 2.0;
            b_t1_tmp[6 * i + 4] =
                    Wn1 * static_cast<double>(b_iv[3 * i + 1]) * 0.5 / 2.0;
            b_t1_tmp[6 * i + 5] =
                    Wn1 * static_cast<double>(b_iv[3 * i + 2]) * 0.5 / 2.0;
        }
        for (i = 0; i < 36; i++) {
            u_idx_1 = t1_tmp[i];
            d = b_t1_tmp[i];
            t1[i] = u_idx_1 + d;
            u_idx_1 -= d;
            t1_tmp[i] = u_idx_1;
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
            jBcol = 0;
            q = fabs(t1_tmp[b_tmp]);
            for (k = 2; k <= jA; k++) {
                u_idx_0 = fabs(t1_tmp[(b_tmp + k) - 1]);
                if (u_idx_0 > q) {
                    jBcol = k - 1;
                    q = u_idx_0;
                }
            }
            if (t1_tmp[b_tmp + jBcol] != 0.0) {
                if (jBcol != 0) {
                    jA = j + jBcol;
                    ipiv[j] = static_cast<signed char>(jA + 1);
                    for (k = 0; k < 6; k++) {
                        temp_tmp = j + k * 6;
                        q = t1_tmp[temp_tmp];
                        jBcol = jA + k * 6;
                        t1_tmp[temp_tmp] = t1_tmp[jBcol];
                        t1_tmp[jBcol] = q;
                    }
                }
                i = (b_tmp - j) + 6;
                for (temp_tmp = jp1j; temp_tmp <= i; temp_tmp++) {
                    t1_tmp[temp_tmp - 1] /= t1_tmp[b_tmp];
                }
            }
            jA = b_tmp;
            for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
                q = t1_tmp[(b_tmp + jp1j * 6) + 6];
                if (q != 0.0) {
                    i = jA + 8;
                    i1 = (jA - j) + 12;
                    for (jBcol = i; jBcol <= i1; jBcol++) {
                        t1_tmp[jBcol - 1] += t1_tmp[((b_tmp + jBcol) - jA) - 7] * -q;
                    }
                }
                jA += 6;
            }
            i2 = ipiv[j];
            if (i2 != j + 1) {
                for (jp1j = 0; jp1j < 6; jp1j++) {
                    temp_tmp = j + 6 * jp1j;
                    q = t1[temp_tmp];
                    mmj_tmp = (i2 + 6 * jp1j) - 1;
                    t1[temp_tmp] = t1[mmj_tmp];
                    t1[mmj_tmp] = q;
                }
            }
        }
        for (j = 0; j < 6; j++) {
            jBcol = 6 * j;
            for (k = 0; k < 6; k++) {
                jA = 6 * k;
                i = k + jBcol;
                if (t1[i] != 0.0) {
                    i1 = k + 2;
                    for (temp_tmp = i1; temp_tmp < 7; temp_tmp++) {
                        mmj_tmp = (temp_tmp + jBcol) - 1;
                        t1[mmj_tmp] -= t1[i] * t1_tmp[(temp_tmp + jA) - 1];
                    }
                }
            }
        }
        for (j = 0; j < 6; j++) {
            jBcol = 6 * j;
            for (k = 5; k >= 0; k--) {
                jA = 6 * k;
                i = k + jBcol;
                u_idx_1 = t1[i];
                if (u_idx_1 != 0.0) {
                    t1[i] = u_idx_1 / t1_tmp[k + jA];
                    for (temp_tmp = 0; temp_tmp < k; temp_tmp++) {
                        mmj_tmp = temp_tmp + jBcol;
                        t1[mmj_tmp] -= t1[i] * t1_tmp[temp_tmp + jA];
                    }
                }
            }
        }
        eig(t1, p);
        q = 2.0 * rt_atan2d_snf(Wn1, 4.0);
        zWn_re = q * 0.0;
        if (q == 0.0) {
            zWn_re = exp(zWn_re);
            Wn1 = 0.0;
        } else {
            u_idx_0 = exp(zWn_re / 2.0);
            zWn_re = u_idx_0 * (u_idx_0 * cos(q));
            Wn1 = u_idx_0 * (u_idx_0 * sin(q));
        }
        for (temp_tmp = 0; temp_tmp < 6; temp_tmp++) {
            x[temp_tmp].re = zWn_re - p[temp_tmp].re;
            x[temp_tmp].im = Wn1 - p[temp_tmp].im;
        }
        x_re = x[0].re;
        im = x[0].im;
        for (k = 0; k < 5; k++) {
            u_idx_1 = x[k + 1].re;
            d = x[k + 1].im;
            q = x_re * u_idx_1 - im * d;
            im = x_re * d + im * u_idx_1;
            x_re = q;
        }
        for (temp_tmp = 0; temp_tmp < 6; temp_tmp++) {
            x[temp_tmp].re = zWn_re - static_cast<double>(b_iv2[temp_tmp]);
            x[temp_tmp].im = Wn1;
        }
        zWn_re = x[0].re;
        Wn1 = x[0].im;
        for (k = 0; k < 5; k++) {
            u_idx_1 = x[k + 1].re;
            d = x[k + 1].im;
            q = zWn_re * u_idx_1 - Wn1 * d;
            Wn1 = zWn_re * d + Wn1 * u_idx_1;
            zWn_re = q;
        }
        if (Wn1 == 0.0) {
            if (im == 0.0) {
                x_re /= zWn_re;
            } else if (x_re == 0.0) {
                x_re = 0.0;
            } else {
                x_re /= zWn_re;
            }
        } else if (zWn_re == 0.0) {
            if (x_re == 0.0) {
                x_re = im / Wn1;
            } else if (im == 0.0) {
                x_re = 0.0;
            } else {
                x_re = im / Wn1;
            }
        } else {
            q = fabs(zWn_re);
            u_idx_0 = fabs(Wn1);
            if (q > u_idx_0) {
                u_idx_0 = Wn1 / zWn_re;
                x_re = (x_re + u_idx_0 * im) / (zWn_re + u_idx_0 * Wn1);
            } else if (u_idx_0 == q) {
                if (zWn_re > 0.0) {
                    zWn_re = 0.5;
                } else {
                    zWn_re = -0.5;
                }
                if (Wn1 > 0.0) {
                    Wn1 = 0.5;
                } else {
                    Wn1 = -0.5;
                }
                x_re = (x_re * zWn_re + im * Wn1) / q;
            } else {
                u_idx_0 = zWn_re / Wn1;
                x_re = (u_idx_0 * x_re + im) / (Wn1 + u_idx_0 * zWn_re);
            }
        }
        b_c[0].re = 1.0;
        b_c[0].im = 0.0;
        for (j = 0; j < 6; j++) {
            q = -p[j].re;
            u_idx_0 = -p[j].im;
            u_idx_1 = b_c[j].im;
            d = b_c[j].re;
            b_c[j + 1].re = q * d - u_idx_0 * u_idx_1;
            b_c[j + 1].im = q * u_idx_1 + u_idx_0 * d;
            for (k = j + 1; k >= 2; k--) {
                u_idx_1 = p[j].re;
                d = p[j].im;
                u_idx_0 = u_idx_1 * b_c[k - 2].im + d * b_c[k - 2].re;
                b_c[k - 1].re -= u_idx_1 * b_c[k - 2].re - d * b_c[k - 2].im;
                b_c[k - 1].im -= u_idx_0;
            }
        }
        for (i = 0; i < 7; i++) {
            varargout_2[i] = b_c[i].re;
            varargout_1[i] = x_re * static_cast<double>(b_b[i]);
        }
    }

} // namespace coder

//
// File trailer for butter.cpp
//
// [EOF]
//
