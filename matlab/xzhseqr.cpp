#include "xzhseqr.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xdlapy3.h"
#include "rt_nonfinite.h"
#include <math.h>

namespace coder {
namespace internal {
namespace reflapack {
int eml_zlahqr(creal_T h_data[], const int h_size[2])
{
    creal_T b_v[2];
    creal_T sc;
    creal_T v;
    int info;
    int itmax;
    int knt;
    int ldh;
    int n;
    n = h_size[0];
    knt = h_size[0];
    if (10 > knt) {
        knt = 10;
    }
    itmax = 30 * knt;
    ldh = h_size[0];
    info = 0;
    if (1 != n) {
        double SMLNUM;
        double aa;
        double br;
        double im;
        double re;
        double tst;
        int b_i;
        int b_k;
        int i;
        int ix0;
        int k;
        boolean_T exitg1;
        for (knt = 0; knt <= n - 4; knt++) {
            i = knt + h_size[0] * knt;
            h_data[i + 2].re = 0.0;
            h_data[i + 2].im = 0.0;
            h_data[i + 3].re = 0.0;
            h_data[i + 3].im = 0.0;
        }
        if (1 <= n - 2) {
            i = (n + h_size[0] * (n - 3)) - 1;
            h_data[i].re = 0.0;
            h_data[i].im = 0.0;
        }
        for (b_i = 2; b_i <= n; b_i++) {
            i = (b_i + h_size[0] * (b_i - 2)) - 1;
            if (h_data[i].im != 0.0) {
                tst = h_data[i].re;
                aa = h_data[i].im;
                br = fabs(h_data[i].re) + fabs(h_data[i].im);
                if (aa == 0.0) {
                    sc.re = tst / br;
                    sc.im = 0.0;
                } else if (tst == 0.0) {
                    sc.re = 0.0;
                    sc.im = aa / br;
                } else {
                    sc.re = tst / br;
                    sc.im = aa / br;
                }
                br = rt_hypotd_snf(sc.re, sc.im);
                if (-sc.im == 0.0) {
                    re = sc.re / br;
                    im = 0.0;
                } else if (sc.re == 0.0) {
                    re = 0.0;
                    im = -sc.im / br;
                } else {
                    re = sc.re / br;
                    im = -sc.im / br;
                }
                h_data[i].re = rt_hypotd_snf(tst, h_data[i].im);
                h_data[i].im = 0.0;
                b_k = (b_i - 1) * ldh;
                ix0 = b_i + b_k;
                i = ix0 + ldh * (n - b_i);
                for (k = ix0; ldh < 0 ? k >= i : k <= i; k += ldh) {
                    aa = re * h_data[k - 1].im + im * h_data[k - 1].re;
                    h_data[k - 1].re =
                        re * h_data[k - 1].re - im * h_data[k - 1].im;
                    h_data[k - 1].im = aa;
                }
                ix0 = b_k + 1;
                knt = b_i + 1;
                if (n < knt) {
                    knt = n;
                }
                i = b_k + knt;
                for (k = ix0; k <= i; k++) {
                    aa = re * h_data[k - 1].im + -im * h_data[k - 1].re;
                    h_data[k - 1].re =
                        re * h_data[k - 1].re - -im * h_data[k - 1].im;
                    h_data[k - 1].im = aa;
                }
            }
        }
        SMLNUM = 2.2250738585072014E-308 *
                 (static_cast<double>(n) / 2.2204460492503131E-16);
        b_i = n - 1;
        exitg1 = false;
        while ((!exitg1) && (b_i + 1 >= 1)) {
            int L;
            int its;
            boolean_T exitg2;
            boolean_T goto140;
            L = -1;
            goto140 = false;
            its = 0;
            exitg2 = false;
            while ((!exitg2) && (its <= itmax)) {
                double ab;
                double ba;
                double bb;
                double s;
                boolean_T exitg3;
                k = b_i;
                exitg3 = false;
                while ((!exitg3) && (k + 1 > L + 2)) {
                    i = k + h_size[0] * (k - 1);
                    aa = fabs(h_data[i].re);
                    ba = aa + fabs(h_data[i].im);
                    if (ba <= SMLNUM) {
                        exitg3 = true;
                    } else {
                        knt = k + h_size[0] * k;
                        bb = fabs(h_data[knt].re) + fabs(h_data[knt].im);
                        tst =
                            (fabs(h_data[i - 1].re) + fabs(h_data[i - 1].im)) +
                            bb;
                        if (tst == 0.0) {
                            if (k - 1 >= 1) {
                                tst = fabs(
                                    h_data[(k + h_size[0] * (k - 2)) - 1].re);
                            }
                            if (k + 2 <= n) {
                                tst += fabs(h_data[knt + 1].re);
                            }
                        }
                        if (aa <= 2.2204460492503131E-16 * tst) {
                            tst = fabs(h_data[knt - 1].re) +
                                  fabs(h_data[knt - 1].im);
                            if (ba > tst) {
                                ab = ba;
                                ba = tst;
                            } else {
                                ab = tst;
                            }
                            tst = fabs(h_data[i - 1].re - h_data[knt].re) +
                                  fabs(h_data[i - 1].im - h_data[knt].im);
                            if (bb > tst) {
                                aa = bb;
                                bb = tst;
                            } else {
                                aa = tst;
                            }
                            s = aa + ab;
                            aa = 2.2204460492503131E-16 * (bb * (aa / s));
                            if ((SMLNUM > aa) || rtIsNaN(aa)) {
                                aa = SMLNUM;
                            }
                            if (ba * (ab / s) <= aa) {
                                exitg3 = true;
                            } else {
                                k--;
                            }
                        } else {
                            k--;
                        }
                    }
                }
                L = k - 1;
                if (k + 1 > 1) {
                    i = k + h_size[0] * (k - 1);
                    h_data[i].re = 0.0;
                    h_data[i].im = 0.0;
                }
                if (k + 1 >= b_i + 1) {
                    goto140 = true;
                    exitg2 = true;
                } else {
                    double t_re;
                    int m;
                    boolean_T goto70;
                    if (its == 10) {
                        knt = k + h_size[0] * k;
                        t_re = 0.75 * fabs(h_data[(k + h_size[0] * k) + 1].re) +
                               h_data[knt].re;
                        ab = h_data[knt].im;
                    } else if (its == 20) {
                        knt = b_i + h_size[0] * b_i;
                        t_re =
                            0.75 *
                                fabs(h_data[b_i + h_size[0] * (b_i - 1)].re) +
                            h_data[knt].re;
                        ab = h_data[knt].im;
                    } else {
                        double u_im;
                        double u_re;
                        knt = b_i + h_size[0] * b_i;
                        t_re = h_data[knt].re;
                        ab = h_data[knt].im;
                        v = h_data[knt - 1];
                        b_sqrt(&v);
                        ix0 = b_i + h_size[0] * (b_i - 1);
                        sc = h_data[ix0];
                        b_sqrt(&sc);
                        u_re = v.re * sc.re - v.im * sc.im;
                        u_im = v.re * sc.im + v.im * sc.re;
                        s = fabs(u_re) + fabs(u_im);
                        if (s != 0.0) {
                            ba = 0.5 * (h_data[ix0 - 1].re - h_data[knt].re);
                            im = 0.5 * (h_data[ix0 - 1].im - h_data[knt].im);
                            bb = fabs(ba) + fabs(im);
                            if ((!(s > bb)) && (!rtIsNaN(bb))) {
                                s = bb;
                            }
                            if (im == 0.0) {
                                t_re = ba / s;
                                ab = 0.0;
                            } else if (ba == 0.0) {
                                t_re = 0.0;
                                ab = im / s;
                            } else {
                                t_re = ba / s;
                                ab = im / s;
                            }
                            re = t_re * t_re - ab * ab;
                            tst = t_re * ab;
                            if (u_im == 0.0) {
                                sc.re = u_re / s;
                                sc.im = 0.0;
                            } else if (u_re == 0.0) {
                                sc.re = 0.0;
                                sc.im = u_im / s;
                            } else {
                                sc.re = u_re / s;
                                sc.im = u_im / s;
                            }
                            aa = sc.re * sc.re - sc.im * sc.im;
                            ab = sc.re * sc.im;
                            v.re = re + aa;
                            v.im = (tst + tst) + (ab + ab);
                            b_sqrt(&v);
                            sc.re = s * v.re;
                            sc.im = s * v.im;
                            if (bb > 0.0) {
                                if (im == 0.0) {
                                    t_re = ba / bb;
                                    ab = 0.0;
                                } else if (ba == 0.0) {
                                    t_re = 0.0;
                                    ab = im / bb;
                                } else {
                                    t_re = ba / bb;
                                    ab = im / bb;
                                }
                                if (t_re * sc.re + ab * sc.im < 0.0) {
                                    sc.re = -sc.re;
                                    sc.im = -sc.im;
                                }
                            }
                            br = ba + sc.re;
                            ab = im + sc.im;
                            if (ab == 0.0) {
                                if (u_im == 0.0) {
                                    ba = u_re / br;
                                    tst = 0.0;
                                } else if (u_re == 0.0) {
                                    ba = 0.0;
                                    tst = u_im / br;
                                } else {
                                    ba = u_re / br;
                                    tst = u_im / br;
                                }
                            } else if (br == 0.0) {
                                if (u_re == 0.0) {
                                    ba = u_im / ab;
                                    tst = 0.0;
                                } else if (u_im == 0.0) {
                                    ba = 0.0;
                                    tst = -(u_re / ab);
                                } else {
                                    ba = u_im / ab;
                                    tst = -(u_re / ab);
                                }
                            } else {
                                bb = fabs(br);
                                tst = fabs(ab);
                                if (bb > tst) {
                                    s = ab / br;
                                    tst = br + s * ab;
                                    ba = (u_re + s * u_im) / tst;
                                    tst = (u_im - s * u_re) / tst;
                                } else if (tst == bb) {
                                    if (br > 0.0) {
                                        aa = 0.5;
                                    } else {
                                        aa = -0.5;
                                    }
                                    if (ab > 0.0) {
                                        tst = 0.5;
                                    } else {
                                        tst = -0.5;
                                    }
                                    ba = (u_re * aa + u_im * tst) / bb;
                                    tst = (u_im * aa - u_re * tst) / bb;
                                } else {
                                    s = br / ab;
                                    tst = ab + s * br;
                                    ba = (s * u_re + u_im) / tst;
                                    tst = (s * u_im - u_re) / tst;
                                }
                            }
                            t_re = h_data[knt].re - (u_re * ba - u_im * tst);
                            ab = h_data[knt].im - (u_re * tst + u_im * ba);
                        }
                    }
                    goto70 = false;
                    m = b_i;
                    exitg3 = false;
                    while ((!exitg3) && (m > k + 1)) {
                        b_k = m + h_size[0] * (m - 1);
                        sc.re = h_data[b_k - 1].re - t_re;
                        sc.im = h_data[b_k - 1].im - ab;
                        tst = h_data[b_k].re;
                        s = (fabs(sc.re) + fabs(sc.im)) + fabs(tst);
                        if (sc.im == 0.0) {
                            re = sc.re / s;
                            im = 0.0;
                        } else if (sc.re == 0.0) {
                            re = 0.0;
                            im = sc.im / s;
                        } else {
                            re = sc.re / s;
                            im = sc.im / s;
                        }
                        sc.re = re;
                        sc.im = im;
                        tst /= s;
                        b_v[0] = sc;
                        b_v[1].re = tst;
                        b_v[1].im = 0.0;
                        i = m + h_size[0] * m;
                        if (fabs(h_data[(m + h_size[0] * (m - 2)) - 1].re) *
                                fabs(tst) <=
                            2.2204460492503131E-16 *
                                ((fabs(re) + fabs(im)) *
                                 ((fabs(h_data[b_k - 1].re) +
                                   fabs(h_data[b_k - 1].im)) +
                                  (fabs(h_data[i].re) + fabs(h_data[i].im))))) {
                            goto70 = true;
                            exitg3 = true;
                        } else {
                            m--;
                        }
                    }
                    if (!goto70) {
                        ix0 = k + h_size[0] * k;
                        sc.re = h_data[ix0].re - t_re;
                        sc.im = h_data[ix0].im - ab;
                        tst = h_data[(k + h_size[0] * k) + 1].re;
                        s = (fabs(sc.re) + fabs(sc.im)) + fabs(tst);
                        if (sc.im == 0.0) {
                            b_v[0].re = sc.re / s;
                            b_v[0].im = 0.0;
                        } else if (sc.re == 0.0) {
                            b_v[0].re = 0.0;
                            b_v[0].im = sc.im / s;
                        } else {
                            b_v[0].re = sc.re / s;
                            b_v[0].im = sc.im / s;
                        }
                        tst /= s;
                        b_v[1].re = tst;
                        b_v[1].im = 0.0;
                    }
                    for (int c_k = m; c_k <= b_i; c_k++) {
                        if (c_k > m) {
                            knt = c_k + h_size[0] * (c_k - 2);
                            b_v[0] = h_data[knt - 1];
                            b_v[1] = h_data[knt];
                        }
                        sc = b_v[0];
                        ba = b_v[1].re;
                        im = b_v[1].im;
                        t_re = 0.0;
                        ab = 0.0;
                        tst = rt_hypotd_snf(b_v[1].re, b_v[1].im);
                        if ((tst != 0.0) || (b_v[0].im != 0.0)) {
                            tst = xdlapy3(b_v[0].re, b_v[0].im, tst);
                            if (b_v[0].re >= 0.0) {
                                tst = -tst;
                            }
                            if (fabs(tst) < 1.0020841800044864E-292) {
                                knt = -1;
                                do {
                                    knt++;
                                    ba *= 9.9792015476736E+291;
                                    im *= 9.9792015476736E+291;
                                    tst *= 9.9792015476736E+291;
                                    sc.re *= 9.9792015476736E+291;
                                    sc.im *= 9.9792015476736E+291;
                                } while (
                                    !(fabs(tst) >= 1.0020841800044864E-292));
                                tst = xdlapy3(sc.re, sc.im,
                                              rt_hypotd_snf(ba, im));
                                if (sc.re >= 0.0) {
                                    tst = -tst;
                                }
                                aa = tst - sc.re;
                                if (0.0 - sc.im == 0.0) {
                                    t_re = aa / tst;
                                    ab = 0.0;
                                } else if (aa == 0.0) {
                                    t_re = 0.0;
                                    ab = (0.0 - sc.im) / tst;
                                } else {
                                    t_re = aa / tst;
                                    ab = (0.0 - sc.im) / tst;
                                }
                                v.re = sc.re - tst;
                                v.im = sc.im;
                                sc = recip(v);
                                re = sc.re * ba - sc.im * im;
                                im = sc.re * im + sc.im * ba;
                                ba = re;
                                for (b_k = 0; b_k <= knt; b_k++) {
                                    tst *= 1.0020841800044864E-292;
                                }
                                sc.re = tst;
                                sc.im = 0.0;
                            } else {
                                aa = tst - b_v[0].re;
                                if (0.0 - b_v[0].im == 0.0) {
                                    t_re = aa / tst;
                                    ab = 0.0;
                                } else if (aa == 0.0) {
                                    t_re = 0.0;
                                    ab = (0.0 - b_v[0].im) / tst;
                                } else {
                                    t_re = aa / tst;
                                    ab = (0.0 - b_v[0].im) / tst;
                                }
                                v.re = b_v[0].re - tst;
                                v.im = b_v[0].im;
                                v = recip(v);
                                ba = v.re * b_v[1].re - v.im * b_v[1].im;
                                im = v.re * b_v[1].im + v.im * b_v[1].re;
                                sc.re = tst;
                                sc.im = 0.0;
                            }
                        }
                        b_v[0] = sc;
                        b_v[1].re = ba;
                        b_v[1].im = im;
                        if (c_k > m) {
                            h_data[(c_k + h_size[0] * (c_k - 2)) - 1] = sc;
                            i = c_k + h_size[0] * (c_k - 2);
                            h_data[i].re = 0.0;
                            h_data[i].im = 0.0;
                        }
                        tst = t_re * ba - ab * im;
                        for (knt = c_k; knt <= n; knt++) {
                            b_k = c_k + h_size[0] * (knt - 1);
                            sc.re = (t_re * h_data[b_k - 1].re -
                                     -ab * h_data[b_k - 1].im) +
                                    tst * h_data[b_k].re;
                            sc.im = (t_re * h_data[b_k - 1].im +
                                     -ab * h_data[b_k - 1].re) +
                                    tst * h_data[b_k].im;
                            h_data[b_k - 1].re -= sc.re;
                            h_data[b_k - 1].im -= sc.im;
                            h_data[b_k].re -= sc.re * ba - sc.im * im;
                            h_data[b_k].im -= sc.re * im + sc.im * ba;
                        }
                        if (c_k + 2 < b_i + 1) {
                            i = c_k + 1;
                        } else {
                            i = b_i;
                        }
                        for (knt = 0; knt <= i; knt++) {
                            ix0 = knt + h_size[0] * (c_k - 1);
                            b_k = knt + h_size[0] * c_k;
                            sc.re =
                                (t_re * h_data[ix0].re - ab * h_data[ix0].im) +
                                tst * h_data[b_k].re;
                            sc.im =
                                (t_re * h_data[ix0].im + ab * h_data[ix0].re) +
                                tst * h_data[b_k].im;
                            h_data[ix0].re -= sc.re;
                            h_data[ix0].im -= sc.im;
                            h_data[b_k].re -= sc.re * ba - sc.im * -im;
                            h_data[b_k].im -= sc.re * -im + sc.im * ba;
                        }
                        if ((c_k == m) && (m > k + 1)) {
                            t_re = 1.0 - t_re;
                            ab = 0.0 - ab;
                            br = rt_hypotd_snf(t_re, ab);
                            if (ab == 0.0) {
                                re = t_re / br;
                                im = 0.0;
                            } else if (t_re == 0.0) {
                                re = 0.0;
                                im = ab / br;
                            } else {
                                re = t_re / br;
                                im = ab / br;
                            }
                            knt = m + h_size[0] * (m - 1);
                            aa = h_data[knt].re * -im + h_data[knt].im * re;
                            h_data[knt].re =
                                h_data[knt].re * re - h_data[knt].im * -im;
                            h_data[knt].im = aa;
                            if (m + 2 <= b_i + 1) {
                                knt = (m + h_size[0] * m) + 1;
                                aa = h_data[knt].re * im + h_data[knt].im * re;
                                h_data[knt].re =
                                    h_data[knt].re * re - h_data[knt].im * im;
                                h_data[knt].im = aa;
                            }
                            for (knt = m; knt <= b_i + 1; knt++) {
                                if (knt != m + 1) {
                                    if (n > knt) {
                                        ix0 = knt + knt * ldh;
                                        i = ix0 + ldh * ((n - knt) - 1);
                                        for (b_k = ix0;
                                             ldh < 0 ? b_k >= i : b_k <= i;
                                             b_k += ldh) {
                                            aa = re * h_data[b_k - 1].im +
                                                 im * h_data[b_k - 1].re;
                                            h_data[b_k - 1].re =
                                                re * h_data[b_k - 1].re -
                                                im * h_data[b_k - 1].im;
                                            h_data[b_k - 1].im = aa;
                                        }
                                    }
                                    b_k = (knt - 1) * ldh;
                                    ix0 = b_k + 1;
                                    i = (b_k + knt) - 1;
                                    for (b_k = ix0; b_k <= i; b_k++) {
                                        aa = re * h_data[b_k - 1].im +
                                             -im * h_data[b_k - 1].re;
                                        h_data[b_k - 1].re =
                                            re * h_data[b_k - 1].re -
                                            -im * h_data[b_k - 1].im;
                                        h_data[b_k - 1].im = aa;
                                    }
                                }
                            }
                        }
                    }
                    knt = b_i + h_size[0] * (b_i - 1);
                    t_re = h_data[knt].re;
                    ab = h_data[knt].im;
                    if (h_data[knt].im != 0.0) {
                        aa = rt_hypotd_snf(h_data[knt].re, h_data[knt].im);
                        h_data[knt].re = aa;
                        h_data[knt].im = 0.0;
                        if (ab == 0.0) {
                            re = t_re / aa;
                            im = 0.0;
                        } else if (t_re == 0.0) {
                            re = 0.0;
                            im = ab / aa;
                        } else {
                            re = t_re / aa;
                            im = ab / aa;
                        }
                        if (n > b_i + 1) {
                            ix0 = (b_i + (b_i + 1) * ldh) + 1;
                            i = ix0 + ldh * ((n - b_i) - 2);
                            for (k = ix0; ldh < 0 ? k >= i : k <= i; k += ldh) {
                                aa = re * h_data[k - 1].im +
                                     -im * h_data[k - 1].re;
                                h_data[k - 1].re = re * h_data[k - 1].re -
                                                   -im * h_data[k - 1].im;
                                h_data[k - 1].im = aa;
                            }
                        }
                        b_k = b_i * ldh;
                        ix0 = b_k + 1;
                        i = b_k + b_i;
                        for (k = ix0; k <= i; k++) {
                            aa = re * h_data[k - 1].im + im * h_data[k - 1].re;
                            h_data[k - 1].re =
                                re * h_data[k - 1].re - im * h_data[k - 1].im;
                            h_data[k - 1].im = aa;
                        }
                    }
                    its++;
                }
            }
            if (!goto140) {
                info = b_i + 1;
                exitg1 = true;
            } else {
                b_i = L;
            }
        }
    }
    return info;
}

} // namespace reflapack
} // namespace internal
} // namespace coder
