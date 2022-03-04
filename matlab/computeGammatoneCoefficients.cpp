#include "computeGammatoneCoefficients.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

namespace coder {
namespace audio {
namespace internal {
void b_computeGammatoneCoefficients(double fs, const double cf[29],
                                    double coeffs[696])
{
    double T;
    double a;
    double a_tmp;
    double b_a_tmp;
    T = 1.0 / fs;
    a = 2.0 * T;
    a_tmp = 4.82842712474619 * T;
    b_a_tmp = 0.82842712474619074 * T;
    for (int k = 0; k < 29; k++) {
        double b_im;
        double b_re;
        double b_re_tmp;
        double br;
        double c_im;
        double c_re;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d_im;
        double d_re;
        double e_im;
        double e_re;
        double f_im;
        double f_re;
        double g_im;
        double g_re;
        double im;
        double r;
        double re;
        double re_tmp;
        double y_re;
        d = cf[k];
        re = 6.4025658280159981 * (d / 9.26449 + 24.7);
        im = 2.0 * d * 3.1415926535897931 * T;
        d1 = cos(im);
        y_re = re * T;
        br = exp(y_re);
        d2 = exp(-2.0 * re * T);
        d3 = sin(im);
        d4 = a * d1 / br;
        d5 = 0.41421356237309537 * d3;
        re_tmp = T * (3.1415926535897931 * (d * 0.0));
        b_im = T * (3.1415926535897931 * (d * 4.0));
        if (b_im == 0.0) {
            b_re = exp(re_tmp);
            b_im = 0.0;
        } else {
            r = exp(re_tmp / 2.0);
            b_re = r * (r * cos(b_im));
            b_im = r * (r * sin(b_im));
        }
        c_re = T * (-2.0 * b_re);
        c_im = T * (-2.0 * b_im);
        d = 2.4142135623730949 * d3;
        re_tmp += -y_re;
        if (im == 0.0) {
            b_re_tmp = exp(re_tmp);
            d_im = 0.0;
            d_re = b_re_tmp;
            e_im = 0.0;
            e_re = b_re_tmp;
            f_im = 0.0;
            f_re = b_re_tmp;
            im = 0.0;
        } else {
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                b_re_tmp = 0.0;
                d_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                b_re_tmp = r * (r * cos(im));
                d_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                d_re = 0.0;
                e_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                d_re = r * (r * cos(im));
                e_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                e_re = 0.0;
                f_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                e_re = r * (r * cos(im));
                f_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                f_re = 0.0;
                im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                f_re = r * (r * cos(im));
                im = r * (r * sin(im));
            }
        }
        re = 2.0 * re * T;
        re = exp(re);
        r = 2.0 * (b_re + 1.0);
        y_re = 2.0 * b_im;
        if (y_re == 0.0) {
            g_re = r / br;
            g_im = 0.0;
        } else if (r == 0.0) {
            g_re = 0.0;
            g_im = y_re / br;
        } else {
            g_re = r / br;
            g_im = y_re / br;
        }
        b_re = (-2.0 / re - 2.0 * b_re) + g_re;
        b_im = (0.0 - 2.0 * b_im) + g_im;
        if ((b_im == 0.0) && (b_re >= 0.0)) {
            re = rt_powd_snf(b_re, 4.0);
            g_im = 0.0;
        } else if (b_re == 0.0) {
            re = rt_powd_snf(b_im, 4.0);
            g_im = 0.0;
        } else {
            if (b_im == 0.0) {
                if (b_re < 0.0) {
                    y_re = log(fabs(b_re));
                    g_re = 3.1415926535897931;
                } else {
                    y_re = log(b_re);
                    g_re = 0.0;
                }
            } else if ((fabs(b_re) > 8.9884656743115785E+307) ||
                       (fabs(b_im) > 8.9884656743115785E+307)) {
                y_re = log(rt_hypotd_snf(b_re / 2.0, b_im / 2.0)) +
                       0.69314718055994529;
                g_re = rt_atan2d_snf(b_im, b_re);
            } else {
                y_re = log(rt_hypotd_snf(b_re, b_im));
                g_re = rt_atan2d_snf(b_im, b_re);
            }
            y_re *= 4.0;
            g_re *= 4.0;
            if (g_re == 0.0) {
                re = exp(y_re);
                g_im = 0.0;
            } else if (rtIsInf(g_re) && rtIsInf(y_re) && (y_re < 0.0)) {
                re = 0.0;
                g_im = 0.0;
            } else {
                r = exp(y_re / 2.0);
                re = r * (r * cos(g_re));
                g_im = r * (r * sin(g_re));
            }
        }
        re_tmp = d1 - d5;
        b_re = c_re + T * (2.0 * b_re_tmp) * re_tmp;
        b_im = c_im + T * (2.0 * d_im) * re_tmp;
        re_tmp = d1 + d5;
        g_re = c_re + T * (2.0 * d_re) * re_tmp;
        d_im = c_im + T * (2.0 * e_im) * re_tmp;
        d_re = b_re * g_re - b_im * d_im;
        b_im = b_re * d_im + b_im * g_re;
        re_tmp = d1 - d;
        b_re = c_re + T * (2.0 * e_re) * re_tmp;
        d_im = c_im + T * (2.0 * f_im) * re_tmp;
        g_re = d_re * b_re - b_im * d_im;
        b_im = d_re * d_im + b_im * b_re;
        re_tmp = d1 + d;
        f_re = c_re + T * (2.0 * f_re) * re_tmp;
        im = c_im + T * (2.0 * im) * re_tmp;
        b_re = g_re * f_re - b_im * im;
        im = g_re * im + b_im * f_re;
        if (g_im == 0.0) {
            if (im == 0.0) {
                c_re = b_re / re;
                c_im = 0.0;
            } else if (b_re == 0.0) {
                c_re = 0.0;
                c_im = im / re;
            } else {
                c_re = b_re / re;
                c_im = im / re;
            }
        } else if (re == 0.0) {
            if (b_re == 0.0) {
                c_re = im / g_im;
                c_im = 0.0;
            } else if (im == 0.0) {
                c_re = 0.0;
                c_im = -(b_re / g_im);
            } else {
                c_re = im / g_im;
                c_im = -(b_re / g_im);
            }
        } else {
            r = fabs(re);
            y_re = fabs(g_im);
            if (r > y_re) {
                g_re = g_im / re;
                y_re = re + g_re * g_im;
                c_re = (b_re + g_re * im) / y_re;
                c_im = (im - g_re * b_re) / y_re;
            } else if (y_re == r) {
                if (re > 0.0) {
                    g_re = 0.5;
                } else {
                    g_re = -0.5;
                }
                if (g_im > 0.0) {
                    y_re = 0.5;
                } else {
                    y_re = -0.5;
                }
                c_re = (b_re * g_re + im * y_re) / r;
                c_im = (im * g_re - b_re * y_re) / r;
            } else {
                g_re = re / g_im;
                y_re = g_im + g_re * re;
                c_re = (g_re * b_re + im) / y_re;
                c_im = (g_re * im - b_re) / y_re;
            }
        }
        re = rt_hypotd_snf(c_re, c_im);
        d = -2.0 * d1 / br;
        coeffs[24 * k] = T / re;
        y_re = a_tmp * d3 / br;
        coeffs[24 * k + 4] = -(d4 + y_re) / 2.0 / re;
        coeffs[24 * k + 8] = 0.0 / re;
        coeffs[24 * k + 12] = 1.0;
        coeffs[24 * k + 16] = d;
        coeffs[24 * k + 20] = d2;
        coeffs[24 * k + 1] = T;
        coeffs[24 * k + 5] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 9] = 0.0;
        coeffs[24 * k + 13] = 1.0;
        coeffs[24 * k + 17] = d;
        coeffs[24 * k + 21] = d2;
        coeffs[24 * k + 2] = T;
        y_re = b_a_tmp * d3 / br;
        coeffs[24 * k + 6] = -(d4 + y_re) / 2.0;
        coeffs[24 * k + 10] = 0.0;
        coeffs[24 * k + 14] = 1.0;
        coeffs[24 * k + 18] = d;
        coeffs[24 * k + 22] = d2;
        coeffs[24 * k + 3] = T;
        coeffs[24 * k + 7] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 11] = 0.0;
        coeffs[24 * k + 15] = 1.0;
        coeffs[24 * k + 19] = d;
        coeffs[24 * k + 23] = d2;
    }
}

void c_computeGammatoneCoefficients(double fs, const double cf[35],
                                    double coeffs[840])
{
    double T;
    double a;
    double a_tmp;
    double b_a_tmp;
    T = 1.0 / fs;
    a = 2.0 * T;
    a_tmp = 4.82842712474619 * T;
    b_a_tmp = 0.82842712474619074 * T;
    for (int k = 0; k < 35; k++) {
        double b_im;
        double b_re;
        double b_re_tmp;
        double br;
        double c_im;
        double c_re;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d_im;
        double d_re;
        double e_im;
        double e_re;
        double f_im;
        double f_re;
        double g_im;
        double g_re;
        double im;
        double r;
        double re;
        double re_tmp;
        double y_re;
        d = cf[k];
        re = 6.4025658280159981 * (d / 9.26449 + 24.7);
        im = 2.0 * d * 3.1415926535897931 * T;
        d1 = cos(im);
        y_re = re * T;
        br = exp(y_re);
        d2 = exp(-2.0 * re * T);
        d3 = sin(im);
        d4 = a * d1 / br;
        d5 = 0.41421356237309537 * d3;
        re_tmp = T * (3.1415926535897931 * (d * 0.0));
        b_im = T * (3.1415926535897931 * (d * 4.0));
        if (b_im == 0.0) {
            b_re = exp(re_tmp);
            b_im = 0.0;
        } else {
            r = exp(re_tmp / 2.0);
            b_re = r * (r * cos(b_im));
            b_im = r * (r * sin(b_im));
        }
        c_re = T * (-2.0 * b_re);
        c_im = T * (-2.0 * b_im);
        d = 2.4142135623730949 * d3;
        re_tmp += -y_re;
        if (im == 0.0) {
            b_re_tmp = exp(re_tmp);
            d_im = 0.0;
            d_re = b_re_tmp;
            e_im = 0.0;
            e_re = b_re_tmp;
            f_im = 0.0;
            f_re = b_re_tmp;
            im = 0.0;
        } else {
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                b_re_tmp = 0.0;
                d_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                b_re_tmp = r * (r * cos(im));
                d_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                d_re = 0.0;
                e_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                d_re = r * (r * cos(im));
                e_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                e_re = 0.0;
                f_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                e_re = r * (r * cos(im));
                f_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                f_re = 0.0;
                im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                f_re = r * (r * cos(im));
                im = r * (r * sin(im));
            }
        }
        re = 2.0 * re * T;
        re = exp(re);
        r = 2.0 * (b_re + 1.0);
        y_re = 2.0 * b_im;
        if (y_re == 0.0) {
            g_re = r / br;
            g_im = 0.0;
        } else if (r == 0.0) {
            g_re = 0.0;
            g_im = y_re / br;
        } else {
            g_re = r / br;
            g_im = y_re / br;
        }
        b_re = (-2.0 / re - 2.0 * b_re) + g_re;
        b_im = (0.0 - 2.0 * b_im) + g_im;
        if ((b_im == 0.0) && (b_re >= 0.0)) {
            re = rt_powd_snf(b_re, 4.0);
            g_im = 0.0;
        } else if (b_re == 0.0) {
            re = rt_powd_snf(b_im, 4.0);
            g_im = 0.0;
        } else {
            if (b_im == 0.0) {
                if (b_re < 0.0) {
                    y_re = log(fabs(b_re));
                    g_re = 3.1415926535897931;
                } else {
                    y_re = log(b_re);
                    g_re = 0.0;
                }
            } else if ((fabs(b_re) > 8.9884656743115785E+307) ||
                       (fabs(b_im) > 8.9884656743115785E+307)) {
                y_re = log(rt_hypotd_snf(b_re / 2.0, b_im / 2.0)) +
                       0.69314718055994529;
                g_re = rt_atan2d_snf(b_im, b_re);
            } else {
                y_re = log(rt_hypotd_snf(b_re, b_im));
                g_re = rt_atan2d_snf(b_im, b_re);
            }
            y_re *= 4.0;
            g_re *= 4.0;
            if (g_re == 0.0) {
                re = exp(y_re);
                g_im = 0.0;
            } else if (rtIsInf(g_re) && rtIsInf(y_re) && (y_re < 0.0)) {
                re = 0.0;
                g_im = 0.0;
            } else {
                r = exp(y_re / 2.0);
                re = r * (r * cos(g_re));
                g_im = r * (r * sin(g_re));
            }
        }
        re_tmp = d1 - d5;
        b_re = c_re + T * (2.0 * b_re_tmp) * re_tmp;
        b_im = c_im + T * (2.0 * d_im) * re_tmp;
        re_tmp = d1 + d5;
        g_re = c_re + T * (2.0 * d_re) * re_tmp;
        d_im = c_im + T * (2.0 * e_im) * re_tmp;
        d_re = b_re * g_re - b_im * d_im;
        b_im = b_re * d_im + b_im * g_re;
        re_tmp = d1 - d;
        b_re = c_re + T * (2.0 * e_re) * re_tmp;
        d_im = c_im + T * (2.0 * f_im) * re_tmp;
        g_re = d_re * b_re - b_im * d_im;
        b_im = d_re * d_im + b_im * b_re;
        re_tmp = d1 + d;
        f_re = c_re + T * (2.0 * f_re) * re_tmp;
        im = c_im + T * (2.0 * im) * re_tmp;
        b_re = g_re * f_re - b_im * im;
        im = g_re * im + b_im * f_re;
        if (g_im == 0.0) {
            if (im == 0.0) {
                c_re = b_re / re;
                c_im = 0.0;
            } else if (b_re == 0.0) {
                c_re = 0.0;
                c_im = im / re;
            } else {
                c_re = b_re / re;
                c_im = im / re;
            }
        } else if (re == 0.0) {
            if (b_re == 0.0) {
                c_re = im / g_im;
                c_im = 0.0;
            } else if (im == 0.0) {
                c_re = 0.0;
                c_im = -(b_re / g_im);
            } else {
                c_re = im / g_im;
                c_im = -(b_re / g_im);
            }
        } else {
            r = fabs(re);
            y_re = fabs(g_im);
            if (r > y_re) {
                g_re = g_im / re;
                y_re = re + g_re * g_im;
                c_re = (b_re + g_re * im) / y_re;
                c_im = (im - g_re * b_re) / y_re;
            } else if (y_re == r) {
                if (re > 0.0) {
                    g_re = 0.5;
                } else {
                    g_re = -0.5;
                }
                if (g_im > 0.0) {
                    y_re = 0.5;
                } else {
                    y_re = -0.5;
                }
                c_re = (b_re * g_re + im * y_re) / r;
                c_im = (im * g_re - b_re * y_re) / r;
            } else {
                g_re = re / g_im;
                y_re = g_im + g_re * re;
                c_re = (g_re * b_re + im) / y_re;
                c_im = (g_re * im - b_re) / y_re;
            }
        }
        re = rt_hypotd_snf(c_re, c_im);
        d = -2.0 * d1 / br;
        coeffs[24 * k] = T / re;
        y_re = a_tmp * d3 / br;
        coeffs[24 * k + 4] = -(d4 + y_re) / 2.0 / re;
        coeffs[24 * k + 8] = 0.0 / re;
        coeffs[24 * k + 12] = 1.0;
        coeffs[24 * k + 16] = d;
        coeffs[24 * k + 20] = d2;
        coeffs[24 * k + 1] = T;
        coeffs[24 * k + 5] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 9] = 0.0;
        coeffs[24 * k + 13] = 1.0;
        coeffs[24 * k + 17] = d;
        coeffs[24 * k + 21] = d2;
        coeffs[24 * k + 2] = T;
        y_re = b_a_tmp * d3 / br;
        coeffs[24 * k + 6] = -(d4 + y_re) / 2.0;
        coeffs[24 * k + 10] = 0.0;
        coeffs[24 * k + 14] = 1.0;
        coeffs[24 * k + 18] = d;
        coeffs[24 * k + 22] = d2;
        coeffs[24 * k + 3] = T;
        coeffs[24 * k + 7] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 11] = 0.0;
        coeffs[24 * k + 15] = 1.0;
        coeffs[24 * k + 19] = d;
        coeffs[24 * k + 23] = d2;
    }
}

void computeGammatoneCoefficients(double fs, const double cf[26],
                                  double coeffs[624])
{
    double T;
    double a;
    double a_tmp;
    double b_a_tmp;
    T = 1.0 / fs;
    a = 2.0 * T;
    a_tmp = 4.82842712474619 * T;
    b_a_tmp = 0.82842712474619074 * T;
    for (int k = 0; k < 26; k++) {
        double b_im;
        double b_re;
        double b_re_tmp;
        double br;
        double c_im;
        double c_re;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d_im;
        double d_re;
        double e_im;
        double e_re;
        double f_im;
        double f_re;
        double g_im;
        double g_re;
        double im;
        double r;
        double re;
        double re_tmp;
        double y_re;
        d = cf[k];
        re = 6.4025658280159981 * (d / 9.26449 + 24.7);
        im = 2.0 * d * 3.1415926535897931 * T;
        d1 = cos(im);
        y_re = re * T;
        br = exp(y_re);
        d2 = exp(-2.0 * re * T);
        d3 = sin(im);
        d4 = a * d1 / br;
        d5 = 0.41421356237309537 * d3;
        re_tmp = T * (3.1415926535897931 * (d * 0.0));
        b_im = T * (3.1415926535897931 * (d * 4.0));
        if (b_im == 0.0) {
            b_re = exp(re_tmp);
            b_im = 0.0;
        } else {
            r = exp(re_tmp / 2.0);
            b_re = r * (r * cos(b_im));
            b_im = r * (r * sin(b_im));
        }
        c_re = T * (-2.0 * b_re);
        c_im = T * (-2.0 * b_im);
        d = 2.4142135623730949 * d3;
        re_tmp += -y_re;
        if (im == 0.0) {
            b_re_tmp = exp(re_tmp);
            d_im = 0.0;
            d_re = b_re_tmp;
            e_im = 0.0;
            e_re = b_re_tmp;
            f_im = 0.0;
            f_re = b_re_tmp;
            im = 0.0;
        } else {
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                b_re_tmp = 0.0;
                d_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                b_re_tmp = r * (r * cos(im));
                d_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                d_re = 0.0;
                e_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                d_re = r * (r * cos(im));
                e_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                e_re = 0.0;
                f_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                e_re = r * (r * cos(im));
                f_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                f_re = 0.0;
                im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                f_re = r * (r * cos(im));
                im = r * (r * sin(im));
            }
        }
        re = 2.0 * re * T;
        re = exp(re);
        r = 2.0 * (b_re + 1.0);
        y_re = 2.0 * b_im;
        if (y_re == 0.0) {
            g_re = r / br;
            g_im = 0.0;
        } else if (r == 0.0) {
            g_re = 0.0;
            g_im = y_re / br;
        } else {
            g_re = r / br;
            g_im = y_re / br;
        }
        b_re = (-2.0 / re - 2.0 * b_re) + g_re;
        b_im = (0.0 - 2.0 * b_im) + g_im;
        if ((b_im == 0.0) && (b_re >= 0.0)) {
            re = rt_powd_snf(b_re, 4.0);
            g_im = 0.0;
        } else if (b_re == 0.0) {
            re = rt_powd_snf(b_im, 4.0);
            g_im = 0.0;
        } else {
            if (b_im == 0.0) {
                if (b_re < 0.0) {
                    y_re = log(fabs(b_re));
                    g_re = 3.1415926535897931;
                } else {
                    y_re = log(b_re);
                    g_re = 0.0;
                }
            } else if ((fabs(b_re) > 8.9884656743115785E+307) ||
                       (fabs(b_im) > 8.9884656743115785E+307)) {
                y_re = log(rt_hypotd_snf(b_re / 2.0, b_im / 2.0)) +
                       0.69314718055994529;
                g_re = rt_atan2d_snf(b_im, b_re);
            } else {
                y_re = log(rt_hypotd_snf(b_re, b_im));
                g_re = rt_atan2d_snf(b_im, b_re);
            }
            y_re *= 4.0;
            g_re *= 4.0;
            if (g_re == 0.0) {
                re = exp(y_re);
                g_im = 0.0;
            } else if (rtIsInf(g_re) && rtIsInf(y_re) && (y_re < 0.0)) {
                re = 0.0;
                g_im = 0.0;
            } else {
                r = exp(y_re / 2.0);
                re = r * (r * cos(g_re));
                g_im = r * (r * sin(g_re));
            }
        }
        re_tmp = d1 - d5;
        b_re = c_re + T * (2.0 * b_re_tmp) * re_tmp;
        b_im = c_im + T * (2.0 * d_im) * re_tmp;
        re_tmp = d1 + d5;
        g_re = c_re + T * (2.0 * d_re) * re_tmp;
        d_im = c_im + T * (2.0 * e_im) * re_tmp;
        d_re = b_re * g_re - b_im * d_im;
        b_im = b_re * d_im + b_im * g_re;
        re_tmp = d1 - d;
        b_re = c_re + T * (2.0 * e_re) * re_tmp;
        d_im = c_im + T * (2.0 * f_im) * re_tmp;
        g_re = d_re * b_re - b_im * d_im;
        b_im = d_re * d_im + b_im * b_re;
        re_tmp = d1 + d;
        f_re = c_re + T * (2.0 * f_re) * re_tmp;
        im = c_im + T * (2.0 * im) * re_tmp;
        b_re = g_re * f_re - b_im * im;
        im = g_re * im + b_im * f_re;
        if (g_im == 0.0) {
            if (im == 0.0) {
                c_re = b_re / re;
                c_im = 0.0;
            } else if (b_re == 0.0) {
                c_re = 0.0;
                c_im = im / re;
            } else {
                c_re = b_re / re;
                c_im = im / re;
            }
        } else if (re == 0.0) {
            if (b_re == 0.0) {
                c_re = im / g_im;
                c_im = 0.0;
            } else if (im == 0.0) {
                c_re = 0.0;
                c_im = -(b_re / g_im);
            } else {
                c_re = im / g_im;
                c_im = -(b_re / g_im);
            }
        } else {
            r = fabs(re);
            y_re = fabs(g_im);
            if (r > y_re) {
                g_re = g_im / re;
                y_re = re + g_re * g_im;
                c_re = (b_re + g_re * im) / y_re;
                c_im = (im - g_re * b_re) / y_re;
            } else if (y_re == r) {
                if (re > 0.0) {
                    g_re = 0.5;
                } else {
                    g_re = -0.5;
                }
                if (g_im > 0.0) {
                    y_re = 0.5;
                } else {
                    y_re = -0.5;
                }
                c_re = (b_re * g_re + im * y_re) / r;
                c_im = (im * g_re - b_re * y_re) / r;
            } else {
                g_re = re / g_im;
                y_re = g_im + g_re * re;
                c_re = (g_re * b_re + im) / y_re;
                c_im = (g_re * im - b_re) / y_re;
            }
        }
        re = rt_hypotd_snf(c_re, c_im);
        d = -2.0 * d1 / br;
        coeffs[24 * k] = T / re;
        y_re = a_tmp * d3 / br;
        coeffs[24 * k + 4] = -(d4 + y_re) / 2.0 / re;
        coeffs[24 * k + 8] = 0.0 / re;
        coeffs[24 * k + 12] = 1.0;
        coeffs[24 * k + 16] = d;
        coeffs[24 * k + 20] = d2;
        coeffs[24 * k + 1] = T;
        coeffs[24 * k + 5] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 9] = 0.0;
        coeffs[24 * k + 13] = 1.0;
        coeffs[24 * k + 17] = d;
        coeffs[24 * k + 21] = d2;
        coeffs[24 * k + 2] = T;
        y_re = b_a_tmp * d3 / br;
        coeffs[24 * k + 6] = -(d4 + y_re) / 2.0;
        coeffs[24 * k + 10] = 0.0;
        coeffs[24 * k + 14] = 1.0;
        coeffs[24 * k + 18] = d;
        coeffs[24 * k + 22] = d2;
        coeffs[24 * k + 3] = T;
        coeffs[24 * k + 7] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 11] = 0.0;
        coeffs[24 * k + 15] = 1.0;
        coeffs[24 * k + 19] = d;
        coeffs[24 * k + 23] = d2;
    }
}

void d_computeGammatoneCoefficients(double fs, const double cf[36],
                                    double coeffs[864])
{
    double T;
    double a;
    double a_tmp;
    double b_a_tmp;
    T = 1.0 / fs;
    a = 2.0 * T;
    a_tmp = 4.82842712474619 * T;
    b_a_tmp = 0.82842712474619074 * T;
    for (int k = 0; k < 36; k++) {
        double b_im;
        double b_re;
        double b_re_tmp;
        double br;
        double c_im;
        double c_re;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d_im;
        double d_re;
        double e_im;
        double e_re;
        double f_im;
        double f_re;
        double g_im;
        double g_re;
        double im;
        double r;
        double re;
        double re_tmp;
        double y_re;
        d = cf[k];
        re = 6.4025658280159981 * (d / 9.26449 + 24.7);
        im = 2.0 * d * 3.1415926535897931 * T;
        d1 = cos(im);
        y_re = re * T;
        br = exp(y_re);
        d2 = exp(-2.0 * re * T);
        d3 = sin(im);
        d4 = a * d1 / br;
        d5 = 0.41421356237309537 * d3;
        re_tmp = T * (3.1415926535897931 * (d * 0.0));
        b_im = T * (3.1415926535897931 * (d * 4.0));
        if (b_im == 0.0) {
            b_re = exp(re_tmp);
            b_im = 0.0;
        } else {
            r = exp(re_tmp / 2.0);
            b_re = r * (r * cos(b_im));
            b_im = r * (r * sin(b_im));
        }
        c_re = T * (-2.0 * b_re);
        c_im = T * (-2.0 * b_im);
        d = 2.4142135623730949 * d3;
        re_tmp += -y_re;
        if (im == 0.0) {
            b_re_tmp = exp(re_tmp);
            d_im = 0.0;
            d_re = b_re_tmp;
            e_im = 0.0;
            e_re = b_re_tmp;
            f_im = 0.0;
            f_re = b_re_tmp;
            im = 0.0;
        } else {
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                b_re_tmp = 0.0;
                d_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                b_re_tmp = r * (r * cos(im));
                d_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                d_re = 0.0;
                e_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                d_re = r * (r * cos(im));
                e_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                e_re = 0.0;
                f_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                e_re = r * (r * cos(im));
                f_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                f_re = 0.0;
                im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                f_re = r * (r * cos(im));
                im = r * (r * sin(im));
            }
        }
        re = 2.0 * re * T;
        re = exp(re);
        r = 2.0 * (b_re + 1.0);
        y_re = 2.0 * b_im;
        if (y_re == 0.0) {
            g_re = r / br;
            g_im = 0.0;
        } else if (r == 0.0) {
            g_re = 0.0;
            g_im = y_re / br;
        } else {
            g_re = r / br;
            g_im = y_re / br;
        }
        b_re = (-2.0 / re - 2.0 * b_re) + g_re;
        b_im = (0.0 - 2.0 * b_im) + g_im;
        if ((b_im == 0.0) && (b_re >= 0.0)) {
            re = rt_powd_snf(b_re, 4.0);
            g_im = 0.0;
        } else if (b_re == 0.0) {
            re = rt_powd_snf(b_im, 4.0);
            g_im = 0.0;
        } else {
            if (b_im == 0.0) {
                if (b_re < 0.0) {
                    y_re = log(fabs(b_re));
                    g_re = 3.1415926535897931;
                } else {
                    y_re = log(b_re);
                    g_re = 0.0;
                }
            } else if ((fabs(b_re) > 8.9884656743115785E+307) ||
                       (fabs(b_im) > 8.9884656743115785E+307)) {
                y_re = log(rt_hypotd_snf(b_re / 2.0, b_im / 2.0)) +
                       0.69314718055994529;
                g_re = rt_atan2d_snf(b_im, b_re);
            } else {
                y_re = log(rt_hypotd_snf(b_re, b_im));
                g_re = rt_atan2d_snf(b_im, b_re);
            }
            y_re *= 4.0;
            g_re *= 4.0;
            if (g_re == 0.0) {
                re = exp(y_re);
                g_im = 0.0;
            } else if (rtIsInf(g_re) && rtIsInf(y_re) && (y_re < 0.0)) {
                re = 0.0;
                g_im = 0.0;
            } else {
                r = exp(y_re / 2.0);
                re = r * (r * cos(g_re));
                g_im = r * (r * sin(g_re));
            }
        }
        re_tmp = d1 - d5;
        b_re = c_re + T * (2.0 * b_re_tmp) * re_tmp;
        b_im = c_im + T * (2.0 * d_im) * re_tmp;
        re_tmp = d1 + d5;
        g_re = c_re + T * (2.0 * d_re) * re_tmp;
        d_im = c_im + T * (2.0 * e_im) * re_tmp;
        d_re = b_re * g_re - b_im * d_im;
        b_im = b_re * d_im + b_im * g_re;
        re_tmp = d1 - d;
        b_re = c_re + T * (2.0 * e_re) * re_tmp;
        d_im = c_im + T * (2.0 * f_im) * re_tmp;
        g_re = d_re * b_re - b_im * d_im;
        b_im = d_re * d_im + b_im * b_re;
        re_tmp = d1 + d;
        f_re = c_re + T * (2.0 * f_re) * re_tmp;
        im = c_im + T * (2.0 * im) * re_tmp;
        b_re = g_re * f_re - b_im * im;
        im = g_re * im + b_im * f_re;
        if (g_im == 0.0) {
            if (im == 0.0) {
                c_re = b_re / re;
                c_im = 0.0;
            } else if (b_re == 0.0) {
                c_re = 0.0;
                c_im = im / re;
            } else {
                c_re = b_re / re;
                c_im = im / re;
            }
        } else if (re == 0.0) {
            if (b_re == 0.0) {
                c_re = im / g_im;
                c_im = 0.0;
            } else if (im == 0.0) {
                c_re = 0.0;
                c_im = -(b_re / g_im);
            } else {
                c_re = im / g_im;
                c_im = -(b_re / g_im);
            }
        } else {
            r = fabs(re);
            y_re = fabs(g_im);
            if (r > y_re) {
                g_re = g_im / re;
                y_re = re + g_re * g_im;
                c_re = (b_re + g_re * im) / y_re;
                c_im = (im - g_re * b_re) / y_re;
            } else if (y_re == r) {
                if (re > 0.0) {
                    g_re = 0.5;
                } else {
                    g_re = -0.5;
                }
                if (g_im > 0.0) {
                    y_re = 0.5;
                } else {
                    y_re = -0.5;
                }
                c_re = (b_re * g_re + im * y_re) / r;
                c_im = (im * g_re - b_re * y_re) / r;
            } else {
                g_re = re / g_im;
                y_re = g_im + g_re * re;
                c_re = (g_re * b_re + im) / y_re;
                c_im = (g_re * im - b_re) / y_re;
            }
        }
        re = rt_hypotd_snf(c_re, c_im);
        d = -2.0 * d1 / br;
        coeffs[24 * k] = T / re;
        y_re = a_tmp * d3 / br;
        coeffs[24 * k + 4] = -(d4 + y_re) / 2.0 / re;
        coeffs[24 * k + 8] = 0.0 / re;
        coeffs[24 * k + 12] = 1.0;
        coeffs[24 * k + 16] = d;
        coeffs[24 * k + 20] = d2;
        coeffs[24 * k + 1] = T;
        coeffs[24 * k + 5] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 9] = 0.0;
        coeffs[24 * k + 13] = 1.0;
        coeffs[24 * k + 17] = d;
        coeffs[24 * k + 21] = d2;
        coeffs[24 * k + 2] = T;
        y_re = b_a_tmp * d3 / br;
        coeffs[24 * k + 6] = -(d4 + y_re) / 2.0;
        coeffs[24 * k + 10] = 0.0;
        coeffs[24 * k + 14] = 1.0;
        coeffs[24 * k + 18] = d;
        coeffs[24 * k + 22] = d2;
        coeffs[24 * k + 3] = T;
        coeffs[24 * k + 7] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 11] = 0.0;
        coeffs[24 * k + 15] = 1.0;
        coeffs[24 * k + 19] = d;
        coeffs[24 * k + 23] = d2;
    }
}

void e_computeGammatoneCoefficients(double fs, const double cf[41],
                                    double coeffs[984])
{
    double T;
    double a;
    double a_tmp;
    double b_a_tmp;
    T = 1.0 / fs;
    a = 2.0 * T;
    a_tmp = 4.82842712474619 * T;
    b_a_tmp = 0.82842712474619074 * T;
    for (int k = 0; k < 41; k++) {
        double b_im;
        double b_re;
        double b_re_tmp;
        double br;
        double c_im;
        double c_re;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d_im;
        double d_re;
        double e_im;
        double e_re;
        double f_im;
        double f_re;
        double g_im;
        double g_re;
        double im;
        double r;
        double re;
        double re_tmp;
        double y_re;
        d = cf[k];
        re = 6.4025658280159981 * (d / 9.26449 + 24.7);
        im = 2.0 * d * 3.1415926535897931 * T;
        d1 = cos(im);
        y_re = re * T;
        br = exp(y_re);
        d2 = exp(-2.0 * re * T);
        d3 = sin(im);
        d4 = a * d1 / br;
        d5 = 0.41421356237309537 * d3;
        re_tmp = T * (3.1415926535897931 * (d * 0.0));
        b_im = T * (3.1415926535897931 * (d * 4.0));
        if (b_im == 0.0) {
            b_re = exp(re_tmp);
            b_im = 0.0;
        } else {
            r = exp(re_tmp / 2.0);
            b_re = r * (r * cos(b_im));
            b_im = r * (r * sin(b_im));
        }
        c_re = T * (-2.0 * b_re);
        c_im = T * (-2.0 * b_im);
        d = 2.4142135623730949 * d3;
        re_tmp += -y_re;
        if (im == 0.0) {
            b_re_tmp = exp(re_tmp);
            d_im = 0.0;
            d_re = b_re_tmp;
            e_im = 0.0;
            e_re = b_re_tmp;
            f_im = 0.0;
            f_re = b_re_tmp;
            im = 0.0;
        } else {
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                b_re_tmp = 0.0;
                d_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                b_re_tmp = r * (r * cos(im));
                d_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                d_re = 0.0;
                e_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                d_re = r * (r * cos(im));
                e_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                e_re = 0.0;
                f_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                e_re = r * (r * cos(im));
                f_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                f_re = 0.0;
                im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                f_re = r * (r * cos(im));
                im = r * (r * sin(im));
            }
        }
        re = 2.0 * re * T;
        re = exp(re);
        r = 2.0 * (b_re + 1.0);
        y_re = 2.0 * b_im;
        if (y_re == 0.0) {
            g_re = r / br;
            g_im = 0.0;
        } else if (r == 0.0) {
            g_re = 0.0;
            g_im = y_re / br;
        } else {
            g_re = r / br;
            g_im = y_re / br;
        }
        b_re = (-2.0 / re - 2.0 * b_re) + g_re;
        b_im = (0.0 - 2.0 * b_im) + g_im;
        if ((b_im == 0.0) && (b_re >= 0.0)) {
            re = rt_powd_snf(b_re, 4.0);
            g_im = 0.0;
        } else if (b_re == 0.0) {
            re = rt_powd_snf(b_im, 4.0);
            g_im = 0.0;
        } else {
            if (b_im == 0.0) {
                if (b_re < 0.0) {
                    y_re = log(fabs(b_re));
                    g_re = 3.1415926535897931;
                } else {
                    y_re = log(b_re);
                    g_re = 0.0;
                }
            } else if ((fabs(b_re) > 8.9884656743115785E+307) ||
                       (fabs(b_im) > 8.9884656743115785E+307)) {
                y_re = log(rt_hypotd_snf(b_re / 2.0, b_im / 2.0)) +
                       0.69314718055994529;
                g_re = rt_atan2d_snf(b_im, b_re);
            } else {
                y_re = log(rt_hypotd_snf(b_re, b_im));
                g_re = rt_atan2d_snf(b_im, b_re);
            }
            y_re *= 4.0;
            g_re *= 4.0;
            if (g_re == 0.0) {
                re = exp(y_re);
                g_im = 0.0;
            } else if (rtIsInf(g_re) && rtIsInf(y_re) && (y_re < 0.0)) {
                re = 0.0;
                g_im = 0.0;
            } else {
                r = exp(y_re / 2.0);
                re = r * (r * cos(g_re));
                g_im = r * (r * sin(g_re));
            }
        }
        re_tmp = d1 - d5;
        b_re = c_re + T * (2.0 * b_re_tmp) * re_tmp;
        b_im = c_im + T * (2.0 * d_im) * re_tmp;
        re_tmp = d1 + d5;
        g_re = c_re + T * (2.0 * d_re) * re_tmp;
        d_im = c_im + T * (2.0 * e_im) * re_tmp;
        d_re = b_re * g_re - b_im * d_im;
        b_im = b_re * d_im + b_im * g_re;
        re_tmp = d1 - d;
        b_re = c_re + T * (2.0 * e_re) * re_tmp;
        d_im = c_im + T * (2.0 * f_im) * re_tmp;
        g_re = d_re * b_re - b_im * d_im;
        b_im = d_re * d_im + b_im * b_re;
        re_tmp = d1 + d;
        f_re = c_re + T * (2.0 * f_re) * re_tmp;
        im = c_im + T * (2.0 * im) * re_tmp;
        b_re = g_re * f_re - b_im * im;
        im = g_re * im + b_im * f_re;
        if (g_im == 0.0) {
            if (im == 0.0) {
                c_re = b_re / re;
                c_im = 0.0;
            } else if (b_re == 0.0) {
                c_re = 0.0;
                c_im = im / re;
            } else {
                c_re = b_re / re;
                c_im = im / re;
            }
        } else if (re == 0.0) {
            if (b_re == 0.0) {
                c_re = im / g_im;
                c_im = 0.0;
            } else if (im == 0.0) {
                c_re = 0.0;
                c_im = -(b_re / g_im);
            } else {
                c_re = im / g_im;
                c_im = -(b_re / g_im);
            }
        } else {
            r = fabs(re);
            y_re = fabs(g_im);
            if (r > y_re) {
                g_re = g_im / re;
                y_re = re + g_re * g_im;
                c_re = (b_re + g_re * im) / y_re;
                c_im = (im - g_re * b_re) / y_re;
            } else if (y_re == r) {
                if (re > 0.0) {
                    g_re = 0.5;
                } else {
                    g_re = -0.5;
                }
                if (g_im > 0.0) {
                    y_re = 0.5;
                } else {
                    y_re = -0.5;
                }
                c_re = (b_re * g_re + im * y_re) / r;
                c_im = (im * g_re - b_re * y_re) / r;
            } else {
                g_re = re / g_im;
                y_re = g_im + g_re * re;
                c_re = (g_re * b_re + im) / y_re;
                c_im = (g_re * im - b_re) / y_re;
            }
        }
        re = rt_hypotd_snf(c_re, c_im);
        d = -2.0 * d1 / br;
        coeffs[24 * k] = T / re;
        y_re = a_tmp * d3 / br;
        coeffs[24 * k + 4] = -(d4 + y_re) / 2.0 / re;
        coeffs[24 * k + 8] = 0.0 / re;
        coeffs[24 * k + 12] = 1.0;
        coeffs[24 * k + 16] = d;
        coeffs[24 * k + 20] = d2;
        coeffs[24 * k + 1] = T;
        coeffs[24 * k + 5] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 9] = 0.0;
        coeffs[24 * k + 13] = 1.0;
        coeffs[24 * k + 17] = d;
        coeffs[24 * k + 21] = d2;
        coeffs[24 * k + 2] = T;
        y_re = b_a_tmp * d3 / br;
        coeffs[24 * k + 6] = -(d4 + y_re) / 2.0;
        coeffs[24 * k + 10] = 0.0;
        coeffs[24 * k + 14] = 1.0;
        coeffs[24 * k + 18] = d;
        coeffs[24 * k + 22] = d2;
        coeffs[24 * k + 3] = T;
        coeffs[24 * k + 7] = -(d4 - y_re) / 2.0;
        coeffs[24 * k + 11] = 0.0;
        coeffs[24 * k + 15] = 1.0;
        coeffs[24 * k + 19] = d;
        coeffs[24 * k + 23] = d2;
    }
}

void f_computeGammatoneCoefficients(double fs, const double cf[42],
                                    double coeffs[1008])
{
    double T;
    double a;
    double a_tmp;
    double b_a;
    T = 1.0 / fs;
    a = 2.0 * T;
    b_a = 4.82842712474619 * T;
    a_tmp = 0.82842712474619074 * T;
    for (int k = 0; k < 42; k++) {
        double b_im;
        double b_re;
        double b_re_tmp;
        double br;
        double c_im;
        double c_re;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d_im;
        double d_re;
        double e_im;
        double e_re;
        double f_im;
        double f_re;
        double g_im;
        double g_re;
        double im;
        double r;
        double re;
        double re_tmp;
        double y_re;
        d = cf[k];
        re = 6.4025658280159981 * (d / 9.26449 + 24.7);
        im = 2.0 * d * 3.1415926535897931 * T;
        d1 = cos(im);
        y_re = re * T;
        br = exp(y_re);
        d2 = exp(-2.0 * re * T);
        d3 = a * d1 / br;
        d4 = sin(im);
        d5 = b_a * d4 / br;
        d6 = 0.41421356237309537 * d4;
        re_tmp = T * (3.1415926535897931 * (d * 0.0));
        b_im = T * (3.1415926535897931 * (d * 4.0));
        if (b_im == 0.0) {
            b_re = exp(re_tmp);
            b_im = 0.0;
        } else {
            r = exp(re_tmp / 2.0);
            b_re = r * (r * cos(b_im));
            b_im = r * (r * sin(b_im));
        }
        c_re = T * (-2.0 * b_re);
        c_im = T * (-2.0 * b_im);
        d = 2.4142135623730949 * d4;
        re_tmp += -y_re;
        if (im == 0.0) {
            b_re_tmp = exp(re_tmp);
            d_im = 0.0;
            d_re = b_re_tmp;
            e_im = 0.0;
            e_re = b_re_tmp;
            f_im = 0.0;
            f_re = b_re_tmp;
            im = 0.0;
        } else {
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                b_re_tmp = 0.0;
                d_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                b_re_tmp = r * (r * cos(im));
                d_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                d_re = 0.0;
                e_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                d_re = r * (r * cos(im));
                e_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                e_re = 0.0;
                f_im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                e_re = r * (r * cos(im));
                f_im = r * (r * sin(im));
            }
            if (rtIsInf(im) && rtIsInf(re_tmp) && (re_tmp < 0.0)) {
                f_re = 0.0;
                im = 0.0;
            } else {
                r = exp(re_tmp / 2.0);
                f_re = r * (r * cos(im));
                im = r * (r * sin(im));
            }
        }
        re = 2.0 * re * T;
        re = exp(re);
        r = 2.0 * (b_re + 1.0);
        y_re = 2.0 * b_im;
        if (y_re == 0.0) {
            g_re = r / br;
            g_im = 0.0;
        } else if (r == 0.0) {
            g_re = 0.0;
            g_im = y_re / br;
        } else {
            g_re = r / br;
            g_im = y_re / br;
        }
        b_re = (-2.0 / re - 2.0 * b_re) + g_re;
        b_im = (0.0 - 2.0 * b_im) + g_im;
        if ((b_im == 0.0) && (b_re >= 0.0)) {
            re = rt_powd_snf(b_re, 4.0);
            g_im = 0.0;
        } else if (b_re == 0.0) {
            re = rt_powd_snf(b_im, 4.0);
            g_im = 0.0;
        } else {
            if (b_im == 0.0) {
                if (b_re < 0.0) {
                    y_re = log(fabs(b_re));
                    g_re = 3.1415926535897931;
                } else {
                    y_re = log(b_re);
                    g_re = 0.0;
                }
            } else if ((fabs(b_re) > 8.9884656743115785E+307) ||
                       (fabs(b_im) > 8.9884656743115785E+307)) {
                y_re = log(rt_hypotd_snf(b_re / 2.0, b_im / 2.0)) +
                       0.69314718055994529;
                g_re = rt_atan2d_snf(b_im, b_re);
            } else {
                y_re = log(rt_hypotd_snf(b_re, b_im));
                g_re = rt_atan2d_snf(b_im, b_re);
            }
            y_re *= 4.0;
            g_re *= 4.0;
            if (g_re == 0.0) {
                re = exp(y_re);
                g_im = 0.0;
            } else if (rtIsInf(g_re) && rtIsInf(y_re) && (y_re < 0.0)) {
                re = 0.0;
                g_im = 0.0;
            } else {
                r = exp(y_re / 2.0);
                re = r * (r * cos(g_re));
                g_im = r * (r * sin(g_re));
            }
        }
        re_tmp = d1 - d6;
        b_re = c_re + T * (2.0 * b_re_tmp) * re_tmp;
        b_im = c_im + T * (2.0 * d_im) * re_tmp;
        re_tmp = d1 + d6;
        g_re = c_re + T * (2.0 * d_re) * re_tmp;
        d_im = c_im + T * (2.0 * e_im) * re_tmp;
        d_re = b_re * g_re - b_im * d_im;
        b_im = b_re * d_im + b_im * g_re;
        re_tmp = d1 - d;
        b_re = c_re + T * (2.0 * e_re) * re_tmp;
        d_im = c_im + T * (2.0 * f_im) * re_tmp;
        g_re = d_re * b_re - b_im * d_im;
        b_im = d_re * d_im + b_im * b_re;
        re_tmp = d1 + d;
        f_re = c_re + T * (2.0 * f_re) * re_tmp;
        im = c_im + T * (2.0 * im) * re_tmp;
        b_re = g_re * f_re - b_im * im;
        im = g_re * im + b_im * f_re;
        if (g_im == 0.0) {
            if (im == 0.0) {
                c_re = b_re / re;
                c_im = 0.0;
            } else if (b_re == 0.0) {
                c_re = 0.0;
                c_im = im / re;
            } else {
                c_re = b_re / re;
                c_im = im / re;
            }
        } else if (re == 0.0) {
            if (b_re == 0.0) {
                c_re = im / g_im;
                c_im = 0.0;
            } else if (im == 0.0) {
                c_re = 0.0;
                c_im = -(b_re / g_im);
            } else {
                c_re = im / g_im;
                c_im = -(b_re / g_im);
            }
        } else {
            r = fabs(re);
            y_re = fabs(g_im);
            if (r > y_re) {
                g_re = g_im / re;
                y_re = re + g_re * g_im;
                c_re = (b_re + g_re * im) / y_re;
                c_im = (im - g_re * b_re) / y_re;
            } else if (y_re == r) {
                if (re > 0.0) {
                    g_re = 0.5;
                } else {
                    g_re = -0.5;
                }
                if (g_im > 0.0) {
                    y_re = 0.5;
                } else {
                    y_re = -0.5;
                }
                c_re = (b_re * g_re + im * y_re) / r;
                c_im = (im * g_re - b_re * y_re) / r;
            } else {
                g_re = re / g_im;
                y_re = g_im + g_re * re;
                c_re = (g_re * b_re + im) / y_re;
                c_im = (g_re * im - b_re) / y_re;
            }
        }
        re = rt_hypotd_snf(c_re, c_im);
        d = -2.0 * d1 / br;
        coeffs[24 * k] = T / re;
        coeffs[24 * k + 4] = -(d3 + d5) / 2.0 / re;
        coeffs[24 * k + 8] = 0.0 / re;
        coeffs[24 * k + 12] = 1.0;
        coeffs[24 * k + 16] = d;
        coeffs[24 * k + 20] = d2;
        coeffs[24 * k + 1] = T;
        coeffs[24 * k + 5] = -(d3 - d5) / 2.0;
        coeffs[24 * k + 9] = 0.0;
        coeffs[24 * k + 13] = 1.0;
        coeffs[24 * k + 17] = d;
        coeffs[24 * k + 21] = d2;
        coeffs[24 * k + 2] = T;
        y_re = a_tmp * d4 / br;
        coeffs[24 * k + 6] = -(d3 + y_re) / 2.0;
        coeffs[24 * k + 10] = 0.0;
        coeffs[24 * k + 14] = 1.0;
        coeffs[24 * k + 18] = d;
        coeffs[24 * k + 22] = d2;
        coeffs[24 * k + 3] = T;
        coeffs[24 * k + 7] = -(d3 - y_re) / 2.0;
        coeffs[24 * k + 11] = 0.0;
        coeffs[24 * k + 15] = 1.0;
        coeffs[24 * k + 19] = d;
        coeffs[24 * k + 23] = d2;
    }
}

} // namespace internal
} // namespace audio
} // namespace coder
