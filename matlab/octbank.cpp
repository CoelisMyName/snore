#include "octbank.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "blockedSummation.h"
#include "eig.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>
#include <string.h>

void octbank(const coder::array<double, 1U> &x, double p[8])
{
    static const double b_dv[8] = {62.5,   125.0,  250.0,  500.0,
                                   1000.0, 2000.0, 4000.0, 8000.0};
    static const signed char b_iv[18] = {-1, 0, 0, 0, -1, 0, 0, 0, -1,
                                         0,  0, 0, 0, 0,  0, 0, 0, 0};
    static const signed char b_iv1[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    static const signed char b[7] = {1, 0, -3, 0, 3, 0, -1};
    static const signed char b_iv2[6] = {1, 1, 1, -1, -1, -1};
    coder::array<double, 2U> y;
    coder::array<double, 1U> b_y;
    coder::array<double, 1U> c_x;
    creal_T b_c[7];
    creal_T b_p[6];
    creal_T b_x[6];
    creal_T c[3];
    double A[36];
    double t1[36];
    double t1_tmp[36];
    double a[9];
    double x_data[8];
    double B[7];
    double b_A[7];
    double b_a[4];
    double d;
    int b_i;
    int i;
    int jA;
    int jBcol;
    int k;
    int loop_ub;
    int nx;
    signed char tmp_data[8];
    signed char ipiv[6];
    signed char b1[2];
    boolean_T idx[8];
    nx = x.size(0) - 1;
    b1[1] = 0;
    b1[0] = 1;
    loop_ub = x.size(0);
    for (i = 0; i < 8; i++) {
        double Wn1;
        double d1;
        double im;
        double q;
        double u_idx_1;
        double zWn_im;
        double zWn_re;
        int c_i;
        int i1;
        int j;
        int kAcol;
        q = b_dv[7 - i] / 22050.0;
        zWn_im =
            4.0 * tan(3.1415926535897931 *
                      (q * 0.70710678118654757 / 0.98505216233236492) / 2.0);
        u_idx_1 =
            4.0 * tan(3.1415926535897931 *
                      (q * 1.4142135623730951 * 0.98505216233236492) / 2.0);
        memset(&a[0], 0, 9U * sizeof(double));
        a[0] = -1.0;
        c[0].re = 1.0;
        c[0].im = 0.0;
        for (j = 0; j < 2; j++) {
            q = 1.7320508075688774 * static_cast<double>(j) +
                -0.86602540378443871;
            im = 0.49999999999999978 * c[j].im + -q * c[j].re;
            c[j + 1].re = 0.49999999999999978 * c[j].re - -q * c[j].im;
            c[j + 1].im = im;
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
        for (b_i = 0; b_i < 2; b_i++) {
            a[b_i + 1] = b1[b_i];
            d = b_a[b_i + 2];
            d1 = b_a[b_i];
            a[b_i + 4] = d1 + d * 0.0;
            a[b_i + 7] = d1 * 0.0 + d * 1.0000000000000002;
        }
        Wn1 = sqrt(zWn_im * u_idx_1);
        q = Wn1 / (u_idx_1 - zWn_im);
        memset(&A[0], 0, 36U * sizeof(double));
        for (k = 0; k < 6; k++) {
            A[k + 6 * k] = 1.0;
        }
        for (b_i = 0; b_i < 3; b_i++) {
            t1_tmp[6 * b_i] = Wn1 * (a[3 * b_i] / q) * 0.5 / 2.0;
            jA = 6 * (b_i + 3);
            t1_tmp[jA] = Wn1 * static_cast<double>(b_iv1[3 * b_i]) * 0.5 / 2.0;
            jBcol = 3 * b_i + 1;
            t1_tmp[6 * b_i + 1] = Wn1 * (a[jBcol] / q) * 0.5 / 2.0;
            t1_tmp[jA + 1] =
                Wn1 * static_cast<double>(b_iv1[jBcol]) * 0.5 / 2.0;
            jBcol = 3 * b_i + 2;
            t1_tmp[6 * b_i + 2] = Wn1 * (a[jBcol] / q) * 0.5 / 2.0;
            t1_tmp[jA + 2] =
                Wn1 * static_cast<double>(b_iv1[jBcol]) * 0.5 / 2.0;
        }
        for (b_i = 0; b_i < 6; b_i++) {
            t1_tmp[6 * b_i + 3] =
                Wn1 * static_cast<double>(b_iv[3 * b_i]) * 0.5 / 2.0;
            t1_tmp[6 * b_i + 4] =
                Wn1 * static_cast<double>(b_iv[3 * b_i + 1]) * 0.5 / 2.0;
            t1_tmp[6 * b_i + 5] =
                Wn1 * static_cast<double>(b_iv[3 * b_i + 2]) * 0.5 / 2.0;
        }
        for (b_i = 0; b_i < 36; b_i++) {
            d = A[b_i];
            d1 = t1_tmp[b_i];
            t1[b_i] = d + d1;
            d -= d1;
            A[b_i] = d;
        }
        for (b_i = 0; b_i < 6; b_i++) {
            ipiv[b_i] = static_cast<signed char>(b_i + 1);
        }
        for (j = 0; j < 5; j++) {
            int b_tmp;
            int jp1j;
            int mmj_tmp;
            signed char i2;
            mmj_tmp = 4 - j;
            b_tmp = j * 7;
            jp1j = b_tmp + 2;
            jA = 6 - j;
            jBcol = 0;
            q = fabs(A[b_tmp]);
            for (k = 2; k <= jA; k++) {
                u_idx_1 = fabs(A[(b_tmp + k) - 1]);
                if (u_idx_1 > q) {
                    jBcol = k - 1;
                    q = u_idx_1;
                }
            }
            if (A[b_tmp + jBcol] != 0.0) {
                if (jBcol != 0) {
                    jA = j + jBcol;
                    ipiv[j] = static_cast<signed char>(jA + 1);
                    for (k = 0; k < 6; k++) {
                        kAcol = j + k * 6;
                        q = A[kAcol];
                        jBcol = jA + k * 6;
                        A[kAcol] = A[jBcol];
                        A[jBcol] = q;
                    }
                }
                b_i = (b_tmp - j) + 6;
                for (c_i = jp1j; c_i <= b_i; c_i++) {
                    A[c_i - 1] /= A[b_tmp];
                }
            }
            jA = b_tmp;
            for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
                q = A[(b_tmp + jp1j * 6) + 6];
                if (q != 0.0) {
                    b_i = jA + 8;
                    i1 = (jA - j) + 12;
                    for (jBcol = b_i; jBcol <= i1; jBcol++) {
                        A[jBcol - 1] += A[((b_tmp + jBcol) - jA) - 7] * -q;
                    }
                }
                jA += 6;
            }
            i2 = ipiv[j];
            if (i2 != j + 1) {
                for (jp1j = 0; jp1j < 6; jp1j++) {
                    kAcol = j + 6 * jp1j;
                    q = t1[kAcol];
                    jA = (i2 + 6 * jp1j) - 1;
                    t1[kAcol] = t1[jA];
                    t1[jA] = q;
                }
            }
        }
        for (j = 0; j < 6; j++) {
            jBcol = 6 * j;
            for (k = 0; k < 6; k++) {
                kAcol = 6 * k;
                b_i = k + jBcol;
                if (t1[b_i] != 0.0) {
                    i1 = k + 2;
                    for (c_i = i1; c_i < 7; c_i++) {
                        jA = (c_i + jBcol) - 1;
                        t1[jA] -= t1[b_i] * A[(c_i + kAcol) - 1];
                    }
                }
            }
        }
        for (j = 0; j < 6; j++) {
            jBcol = 6 * j;
            for (k = 5; k >= 0; k--) {
                kAcol = 6 * k;
                b_i = k + jBcol;
                d = t1[b_i];
                if (d != 0.0) {
                    t1[b_i] = d / A[k + kAcol];
                    for (c_i = 0; c_i < k; c_i++) {
                        jA = c_i + jBcol;
                        t1[jA] -= t1[b_i] * A[c_i + kAcol];
                    }
                }
            }
        }
        coder::eig(t1, b_p);
        q = 2.0 * rt_atan2d_snf(Wn1, 4.0);
        zWn_re = q * 0.0;
        if (q == 0.0) {
            zWn_re = exp(zWn_re);
            zWn_im = 0.0;
        } else {
            u_idx_1 = exp(zWn_re / 2.0);
            zWn_re = u_idx_1 * (u_idx_1 * cos(q));
            zWn_im = u_idx_1 * (u_idx_1 * sin(q));
        }
        for (c_i = 0; c_i < 6; c_i++) {
            b_x[c_i].re = zWn_re - b_p[c_i].re;
            b_x[c_i].im = zWn_im - b_p[c_i].im;
        }
        Wn1 = b_x[0].re;
        im = b_x[0].im;
        for (k = 0; k < 5; k++) {
            d = b_x[k + 1].re;
            d1 = b_x[k + 1].im;
            q = Wn1 * d - im * d1;
            im = Wn1 * d1 + im * d;
            Wn1 = q;
        }
        for (c_i = 0; c_i < 6; c_i++) {
            b_x[c_i].re = zWn_re - static_cast<double>(b_iv2[c_i]);
            b_x[c_i].im = zWn_im;
        }
        zWn_re = b_x[0].re;
        zWn_im = b_x[0].im;
        for (k = 0; k < 5; k++) {
            d = b_x[k + 1].re;
            d1 = b_x[k + 1].im;
            q = zWn_re * d - zWn_im * d1;
            zWn_im = zWn_re * d1 + zWn_im * d;
            zWn_re = q;
        }
        if (zWn_im == 0.0) {
            if (im == 0.0) {
                Wn1 /= zWn_re;
            } else if (Wn1 == 0.0) {
                Wn1 = 0.0;
            } else {
                Wn1 /= zWn_re;
            }
        } else if (zWn_re == 0.0) {
            if (Wn1 == 0.0) {
                Wn1 = im / zWn_im;
            } else if (im == 0.0) {
                Wn1 = 0.0;
            } else {
                Wn1 = im / zWn_im;
            }
        } else {
            q = fabs(zWn_re);
            u_idx_1 = fabs(zWn_im);
            if (q > u_idx_1) {
                u_idx_1 = zWn_im / zWn_re;
                Wn1 = (Wn1 + u_idx_1 * im) / (zWn_re + u_idx_1 * zWn_im);
            } else if (u_idx_1 == q) {
                if (zWn_re > 0.0) {
                    zWn_re = 0.5;
                } else {
                    zWn_re = -0.5;
                }
                if (zWn_im > 0.0) {
                    zWn_im = 0.5;
                } else {
                    zWn_im = -0.5;
                }
                Wn1 = (Wn1 * zWn_re + im * zWn_im) / q;
            } else {
                u_idx_1 = zWn_re / zWn_im;
                Wn1 = (u_idx_1 * Wn1 + im) / (zWn_im + u_idx_1 * zWn_re);
            }
        }
        b_c[0].re = 1.0;
        b_c[0].im = 0.0;
        for (j = 0; j < 6; j++) {
            q = -b_p[j].re;
            u_idx_1 = -b_p[j].im;
            im = q * b_c[j].im + u_idx_1 * b_c[j].re;
            b_c[j + 1].re = q * b_c[j].re - u_idx_1 * b_c[j].im;
            b_c[j + 1].im = im;
            for (k = j + 1; k >= 2; k--) {
                d = b_p[j].re;
                d1 = b_p[j].im;
                u_idx_1 = d * b_c[k - 2].im + d1 * b_c[k - 2].re;
                b_c[k - 1].re -= d * b_c[k - 2].re - d1 * b_c[k - 2].im;
                b_c[k - 1].im -= u_idx_1;
            }
        }
        for (b_i = 0; b_i < 7; b_i++) {
            b_A[b_i] = b_c[b_i].re;
            B[b_i] = Wn1 * static_cast<double>(b[b_i]);
        }
        b_y.set_size(x.size(0));
        for (b_i = 0; b_i < loop_ub; b_i++) {
            b_y[b_i] = 0.0;
        }
        for (k = 0; k <= nx; k++) {
            jA = nx - k;
            jBcol = jA + 1;
            if (jBcol >= 7) {
                jBcol = 7;
            }
            for (j = 0; j < jBcol; j++) {
                kAcol = k + j;
                b_y[kAcol] = b_y[kAcol] + x[k] * B[j];
            }
            if (jA < 6) {
                jBcol = jA;
            } else {
                jBcol = 6;
            }
            q = -b_y[k];
            for (j = 0; j < jBcol; j++) {
                kAcol = (k + j) + 1;
                b_y[kAcol] = b_y[kAcol] + q * b_A[j + 1];
            }
        }
        b_i = b_y.size(0);
        c_x.set_size(b_y.size(0));
        for (k = 0; k < b_i; k++) {
            c_x[k] = b_y[k] * b_y[k];
        }
        p[7 - i] = coder::blockedSummation(c_x, c_x.size(0)) /
                   static_cast<double>(x.size(0));
    }
    jBcol = 0;
    jA = 0;
    for (i = 0; i < 8; i++) {
        d = p[i];
        idx[i] = (d > 0.0);
        if (d > 0.0) {
            jBcol++;
            tmp_data[jA] = static_cast<signed char>(i + 1);
            jA++;
        }
    }
    for (b_i = 0; b_i < jBcol; b_i++) {
        x_data[b_i] = p[tmp_data[b_i] - 1];
    }
    for (k = 0; k < jBcol; k++) {
        x_data[k] = log10(x_data[k]);
    }
    y.set_size(1, jBcol);
    for (b_i = 0; b_i < jBcol; b_i++) {
        y[b_i] = 10.0 * x_data[b_i];
    }
    jA = 0;
    for (i = 0; i < 8; i++) {
        if (p[i] > 0.0) {
            p[i] = y[jA];
            jA++;
        }
        if (!idx[i]) {
            p[i] = rtNaN;
        }
    }
}
