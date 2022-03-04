#include "xdhseqr.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xzlarfg.h"
#include "rt_nonfinite.h"
#include <math.h>

namespace coder {
namespace internal {
namespace reflapack {
int eml_dlahqr(double h_data[], const int h_size[2])
{
    double v[3];
    double aa;
    double ab;
    double ba;
    double bb;
    double d;
    double rt1r;
    double rt2r;
    double s;
    double tst;
    int info;
    int ldh;
    int n;
    n = h_size[0];
    ldh = h_size[0];
    info = 0;
    if (1 != n) {
        double SMLNUM;
        int b_i;
        int i;
        int j;
        boolean_T exitg1;
        v[0] = 0.0;
        v[1] = 0.0;
        v[2] = 0.0;
        for (j = 0; j <= n - 4; j++) {
            i = j + h_size[0] * j;
            h_data[i + 2] = 0.0;
            h_data[i + 3] = 0.0;
        }
        if (1 <= n - 2) {
            h_data[(n + h_size[0] * (n - 3)) - 1] = 0.0;
        }
        SMLNUM = 2.2250738585072014E-308 *
                 (static_cast<double>(n) / 2.2204460492503131E-16);
        b_i = n - 1;
        exitg1 = false;
        while ((!exitg1) && (b_i + 1 >= 1)) {
            int L;
            int hoffset;
            int its;
            int k;
            int nr;
            int sum1_tmp;
            int sum1_tmp_tmp;
            boolean_T exitg2;
            boolean_T goto150;
            L = 1;
            goto150 = false;
            its = 0;
            exitg2 = false;
            while ((!exitg2) && (its <= 300)) {
                boolean_T exitg3;
                k = b_i;
                exitg3 = false;
                while ((!exitg3) && (k + 1 > L)) {
                    i = k + h_size[0] * (k - 1);
                    ba = fabs(h_data[i]);
                    if (ba <= SMLNUM) {
                        exitg3 = true;
                    } else {
                        hoffset = k + h_size[0] * k;
                        bb = fabs(h_data[hoffset]);
                        tst = fabs(h_data[i - 1]) + bb;
                        if (tst == 0.0) {
                            if (k - 1 >= 1) {
                                tst =
                                    fabs(h_data[(k + h_size[0] * (k - 2)) - 1]);
                            }
                            if (k + 2 <= n) {
                                tst += fabs(h_data[(k + h_size[0] * k) + 1]);
                            }
                        }
                        if (ba <= 2.2204460492503131E-16 * tst) {
                            tst = fabs(h_data[hoffset - 1]);
                            if (ba > tst) {
                                ab = ba;
                                ba = tst;
                            } else {
                                ab = tst;
                            }
                            tst = fabs(h_data[i - 1] - h_data[hoffset]);
                            if (bb > tst) {
                                aa = bb;
                                bb = tst;
                            } else {
                                aa = tst;
                            }
                            s = aa + ab;
                            tst = 2.2204460492503131E-16 * (bb * (aa / s));
                            if ((SMLNUM > tst) || rtIsNaN(tst)) {
                                tst = SMLNUM;
                            }
                            if (ba * (ab / s) <= tst) {
                                exitg3 = true;
                            } else {
                                k--;
                            }
                        } else {
                            k--;
                        }
                    }
                }
                L = k + 1;
                if (k + 1 > 1) {
                    h_data[k + h_size[0] * (k - 1)] = 0.0;
                }
                if (k + 1 >= b_i) {
                    goto150 = true;
                    exitg2 = true;
                } else {
                    int m;
                    if (its == 10) {
                        hoffset = k + h_size[0] * k;
                        s = fabs(h_data[hoffset + 1]) +
                            fabs(h_data[(k + h_size[0] * (k + 1)) + 2]);
                        tst = 0.75 * s + h_data[hoffset];
                        ab = -0.4375 * s;
                        aa = s;
                        ba = tst;
                    } else if (its == 20) {
                        s = fabs(h_data[b_i + h_size[0] * (b_i - 1)]) +
                            fabs(h_data[(b_i + h_size[0] * (b_i - 2)) - 1]);
                        tst = 0.75 * s + h_data[b_i + h_size[0] * b_i];
                        ab = -0.4375 * s;
                        aa = s;
                        ba = tst;
                    } else {
                        hoffset = b_i + h_size[0] * (b_i - 1);
                        tst = h_data[hoffset - 1];
                        aa = h_data[hoffset];
                        ab = h_data[(b_i + h_size[0] * b_i) - 1];
                        ba = h_data[b_i + h_size[0] * b_i];
                    }
                    s = ((fabs(tst) + fabs(ab)) + fabs(aa)) + fabs(ba);
                    if (s == 0.0) {
                        rt1r = 0.0;
                        aa = 0.0;
                        rt2r = 0.0;
                        ab = 0.0;
                    } else {
                        tst /= s;
                        aa /= s;
                        ab /= s;
                        ba /= s;
                        bb = (tst + ba) / 2.0;
                        tst = (tst - bb) * (ba - bb) - ab * aa;
                        aa = sqrt(fabs(tst));
                        if (tst >= 0.0) {
                            rt1r = bb * s;
                            rt2r = rt1r;
                            aa *= s;
                            ab = -aa;
                        } else {
                            rt1r = bb + aa;
                            rt2r = bb - aa;
                            if (fabs(rt1r - ba) <= fabs(rt2r - ba)) {
                                rt1r *= s;
                                rt2r = rt1r;
                            } else {
                                rt2r *= s;
                                rt1r = rt2r;
                            }
                            aa = 0.0;
                            ab = 0.0;
                        }
                    }
                    m = b_i - 1;
                    exitg3 = false;
                    while ((!exitg3) && (m >= k + 1)) {
                        hoffset = m + h_size[0] * (m - 1);
                        tst = h_data[hoffset];
                        bb = h_data[hoffset - 1];
                        ba = bb - rt2r;
                        s = (fabs(ba) + fabs(ab)) + fabs(tst);
                        tst /= s;
                        hoffset = m + h_size[0] * m;
                        v[0] = (tst * h_data[hoffset - 1] +
                                (bb - rt1r) * (ba / s)) -
                               aa * (ab / s);
                        v[1] = tst * (((bb + h_data[hoffset]) - rt1r) - rt2r);
                        v[2] = tst * h_data[hoffset + 1];
                        s = (fabs(v[0]) + fabs(v[1])) + fabs(v[2]);
                        v[0] /= s;
                        v[1] /= s;
                        v[2] /= s;
                        if (m == k + 1) {
                            exitg3 = true;
                        } else {
                            i = m + h_size[0] * (m - 2);
                            if (fabs(h_data[i - 1]) *
                                    (fabs(v[1]) + fabs(v[2])) <=
                                2.2204460492503131E-16 * fabs(v[0]) *
                                    ((fabs(h_data[i - 2]) + fabs(bb)) +
                                     fabs(h_data[hoffset]))) {
                                exitg3 = true;
                            } else {
                                m--;
                            }
                        }
                    }
                    for (int b_k = m; b_k <= b_i; b_k++) {
                        nr = (b_i - b_k) + 2;
                        if (3 < nr) {
                            nr = 3;
                        }
                        if (b_k > m) {
                            hoffset = (b_k + ldh * (b_k - 2)) - 1;
                            for (j = 0; j < nr; j++) {
                                v[j] = h_data[j + hoffset];
                            }
                        }
                        tst = v[0];
                        bb = xzlarfg(nr, &tst, v);
                        v[0] = tst;
                        if (b_k > m) {
                            i = b_k + h_size[0] * (b_k - 2);
                            h_data[i - 1] = tst;
                            h_data[i] = 0.0;
                            if (b_k < b_i) {
                                h_data[i + 1] = 0.0;
                            }
                        } else if (m > k + 1) {
                            i = (b_k + h_size[0] * (b_k - 2)) - 1;
                            h_data[i] *= 1.0 - bb;
                        }
                        d = v[1];
                        aa = bb * v[1];
                        if (nr == 3) {
                            s = v[2];
                            tst = bb * v[2];
                            for (j = b_k; j <= n; j++) {
                                sum1_tmp = b_k + h_size[0] * (j - 1);
                                ab = (h_data[sum1_tmp - 1] +
                                      d * h_data[sum1_tmp]) +
                                     s * h_data[sum1_tmp + 1];
                                h_data[sum1_tmp - 1] -= ab * bb;
                                h_data[sum1_tmp] -= ab * aa;
                                h_data[sum1_tmp + 1] -= ab * tst;
                            }
                            if (b_k + 3 < b_i + 1) {
                                i = b_k + 2;
                            } else {
                                i = b_i;
                            }
                            for (j = 0; j <= i; j++) {
                                sum1_tmp = j + h_size[0] * (b_k - 1);
                                sum1_tmp_tmp = j + h_size[0] * b_k;
                                hoffset = j + h_size[0] * (b_k + 1);
                                ab = (h_data[sum1_tmp] +
                                      d * h_data[sum1_tmp_tmp]) +
                                     s * h_data[hoffset];
                                h_data[sum1_tmp] -= ab * bb;
                                h_data[sum1_tmp_tmp] -= ab * aa;
                                h_data[hoffset] -= ab * tst;
                            }
                        } else if (nr == 2) {
                            for (j = b_k; j <= n; j++) {
                                sum1_tmp_tmp = b_k + h_size[0] * (j - 1);
                                tst = h_data[sum1_tmp_tmp - 1];
                                ab = tst + d * h_data[sum1_tmp_tmp];
                                h_data[sum1_tmp_tmp - 1] = tst - ab * bb;
                                h_data[sum1_tmp_tmp] -= ab * aa;
                            }
                            for (j = 0; j <= b_i; j++) {
                                sum1_tmp = j + h_size[0] * (b_k - 1);
                                sum1_tmp_tmp = j + h_size[0] * b_k;
                                ab =
                                    h_data[sum1_tmp] + d * h_data[sum1_tmp_tmp];
                                h_data[sum1_tmp] -= ab * bb;
                                h_data[sum1_tmp_tmp] -= ab * aa;
                            }
                        }
                    }
                    its++;
                }
            }
            if (!goto150) {
                info = b_i + 1;
                exitg1 = true;
            } else {
                if ((L != b_i + 1) && (L == b_i)) {
                    i = b_i + h_size[0] * b_i;
                    d = h_data[i - 1];
                    hoffset = b_i + h_size[0] * (b_i - 1);
                    s = h_data[hoffset];
                    tst = h_data[i];
                    xdlanv2(&h_data[(b_i + h_size[0] * (b_i - 1)) - 1], &d, &s,
                            &tst, &aa, &ab, &bb, &ba, &rt2r, &rt1r);
                    h_data[i - 1] = d;
                    h_data[hoffset] = s;
                    h_data[i] = tst;
                    if (n > b_i + 1) {
                        hoffset = (n - b_i) - 2;
                        if (hoffset + 1 >= 1) {
                            nr = b_i + (b_i + 1) * ldh;
                            for (k = 0; k <= hoffset; k++) {
                                sum1_tmp_tmp = nr + k * ldh;
                                tst = rt2r * h_data[sum1_tmp_tmp - 1] +
                                      rt1r * h_data[sum1_tmp_tmp];
                                h_data[sum1_tmp_tmp] =
                                    rt2r * h_data[sum1_tmp_tmp] -
                                    rt1r * h_data[sum1_tmp_tmp - 1];
                                h_data[sum1_tmp_tmp - 1] = tst;
                            }
                        }
                    }
                    if (b_i - 1 >= 1) {
                        hoffset = (b_i - 1) * ldh;
                        nr = b_i * ldh;
                        for (k = 0; k <= b_i - 2; k++) {
                            sum1_tmp_tmp = nr + k;
                            sum1_tmp = hoffset + k;
                            tst = rt2r * h_data[sum1_tmp] +
                                  rt1r * h_data[sum1_tmp_tmp];
                            h_data[sum1_tmp_tmp] = rt2r * h_data[sum1_tmp_tmp] -
                                                   rt1r * h_data[sum1_tmp];
                            h_data[sum1_tmp] = tst;
                        }
                    }
                }
                b_i = L - 2;
            }
        }
    }
    return info;
}

} // namespace reflapack
} // namespace internal
} // namespace coder
