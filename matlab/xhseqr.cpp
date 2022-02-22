//
// File: xhseqr.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "xhseqr.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xzlarfg.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : double h[36]
// Return Type  : int
//
namespace coder {
    namespace internal {
        namespace lapack {
            int xhseqr(double h[36]) {
                double v[3];
                double aa;
                double ab;
                double ba;
                double bb;
                double rt1r;
                double rt2r;
                double s;
                double s_tmp;
                double tst;
                int i;
                int info;
                int iy;
                int j;
                boolean_T exitg1;
                info = 0;
                v[0] = 0.0;
                h[2] = 0.0;
                h[3] = 0.0;
                v[1] = 0.0;
                h[9] = 0.0;
                h[10] = 0.0;
                v[2] = 0.0;
                h[16] = 0.0;
                h[17] = 0.0;
                h[23] = 0.0;
                i = 5;
                exitg1 = false;
                while ((!exitg1) && (i + 1 >= 1)) {
                    int L;
                    int b_i;
                    int b_k;
                    int hoffset;
                    int its;
                    int k;
                    int nr;
                    boolean_T exitg2;
                    boolean_T goto150;
                    L = 1;
                    goto150 = false;
                    its = 0;
                    exitg2 = false;
                    while ((!exitg2) && (its < 301)) {
                        boolean_T exitg3;
                        k = i;
                        exitg3 = false;
                        while ((!exitg3) && (k + 1 > L)) {
                            b_i = k + 6 * (k - 1);
                            ba = fabs(h[b_i]);
                            if (ba <= 6.0125050800269183E-292) {
                                exitg3 = true;
                            } else {
                                iy = k + 6 * k;
                                bb = fabs(h[iy]);
                                tst = fabs(h[b_i - 1]) + bb;
                                if (tst == 0.0) {
                                    if (k - 1 >= 1) {
                                        tst = fabs(h[(k + 6 * (k - 2)) - 1]);
                                    }
                                    if (k + 2 <= 6) {
                                        tst += fabs(h[iy + 1]);
                                    }
                                }
                                if (ba <= 2.2204460492503131E-16 * tst) {
                                    tst = fabs(h[iy - 1]);
                                    if (ba > tst) {
                                        ab = ba;
                                        ba = tst;
                                    } else {
                                        ab = tst;
                                    }
                                    tst = fabs(h[b_i - 1] - h[iy]);
                                    if (bb > tst) {
                                        aa = bb;
                                        bb = tst;
                                    } else {
                                        aa = tst;
                                    }
                                    s = aa + ab;
                                    tst = 2.2204460492503131E-16 * (bb * (aa / s));
                                    if ((6.0125050800269183E-292 > tst) || rtIsNaN(tst)) {
                                        tst = 6.0125050800269183E-292;
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
                            h[k + 6 * (k - 1)] = 0.0;
                        }
                        if (k + 1 >= i) {
                            goto150 = true;
                            exitg2 = true;
                        } else {
                            int m;
                            if (its == 10) {
                                iy = k + 6 * k;
                                s = fabs(h[iy + 1]) + fabs(h[(k + 6 * (k + 1)) + 2]);
                                tst = 0.75 * s + h[iy];
                                ab = -0.4375 * s;
                                aa = s;
                                ba = tst;
                            } else if (its == 20) {
                                s = fabs(h[i + 6 * (i - 1)]) + fabs(h[(i + 6 * (i - 2)) - 1]);
                                tst = 0.75 * s + h[i + 6 * i];
                                ab = -0.4375 * s;
                                aa = s;
                                ba = tst;
                            } else {
                                iy = i + 6 * (i - 1);
                                tst = h[iy - 1];
                                aa = h[iy];
                                ab = h[(i + 6 * i) - 1];
                                ba = h[i + 6 * i];
                            }
                            s = ((fabs(tst) + fabs(ab)) + fabs(aa)) + fabs(ba);
                            if (s == 0.0) {
                                rt1r = 0.0;
                                bb = 0.0;
                                rt2r = 0.0;
                                ba = 0.0;
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
                                    bb = aa * s;
                                    ba = -bb;
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
                                    bb = 0.0;
                                    ba = 0.0;
                                }
                            }
                            m = i - 1;
                            exitg3 = false;
                            while ((!exitg3) && (m >= k + 1)) {
                                iy = m + 6 * (m - 1);
                                tst = h[iy];
                                s_tmp = h[iy - 1];
                                aa = s_tmp - rt2r;
                                s = (fabs(aa) + fabs(ba)) + fabs(tst);
                                ab = tst / s;
                                iy = m + 6 * m;
                                v[0] = (ab * h[iy - 1] + (s_tmp - rt1r) * (aa / s)) - bb * (ba / s);
                                tst = h[iy];
                                v[1] = ab * (((s_tmp + tst) - rt1r) - rt2r);
                                v[2] = ab * h[iy + 1];
                                s = (fabs(v[0]) + fabs(v[1])) + fabs(v[2]);
                                v[0] /= s;
                                v[1] /= s;
                                v[2] /= s;
                                if (m == k + 1) {
                                    exitg3 = true;
                                } else {
                                    b_i = m + 6 * (m - 2);
                                    if (fabs(h[b_i - 1]) * (fabs(v[1]) + fabs(v[2])) <=
                                        2.2204460492503131E-16 * fabs(v[0]) *
                                        ((fabs(h[b_i - 2]) + fabs(s_tmp)) + fabs(tst))) {
                                        exitg3 = true;
                                    } else {
                                        m--;
                                    }
                                }
                            }
                            for (b_k = m; b_k <= i; b_k++) {
                                nr = (i - b_k) + 2;
                                if (3 < nr) {
                                    nr = 3;
                                }
                                if (b_k > m) {
                                    hoffset = (b_k + 6 * (b_k - 2)) - 1;
                                    for (j = 0; j < nr; j++) {
                                        v[j] = h[j + hoffset];
                                    }
                                }
                                tst = v[0];
                                bb = reflapack::xzlarfg(nr, &tst, v);
                                v[0] = tst;
                                if (b_k > m) {
                                    h[(b_k + 6 * (b_k - 2)) - 1] = tst;
                                    b_i = b_k + 6 * (b_k - 2);
                                    h[b_i] = 0.0;
                                    if (b_k < i) {
                                        h[b_i + 1] = 0.0;
                                    }
                                } else if (m > k + 1) {
                                    h[(b_k + 6 * (b_k - 2)) - 1] *= 1.0 - bb;
                                }
                                s = v[1];
                                aa = bb * v[1];
                                if (nr == 3) {
                                    rt1r = v[2];
                                    tst = bb * v[2];
                                    for (j = b_k; j < 7; j++) {
                                        iy = b_k + 6 * (j - 1);
                                        ab = (h[iy - 1] + s * h[iy]) + rt1r * h[iy + 1];
                                        h[iy - 1] -= ab * bb;
                                        h[iy] -= ab * aa;
                                        h[iy + 1] -= ab * tst;
                                    }
                                    if (b_k + 3 < i + 1) {
                                        b_i = b_k + 2;
                                    } else {
                                        b_i = i;
                                    }
                                    for (j = 0; j <= b_i; j++) {
                                        iy = j + 6 * (b_k - 1);
                                        hoffset = j + 6 * b_k;
                                        nr = j + 6 * (b_k + 1);
                                        ab = (h[iy] + s * h[hoffset]) + rt1r * h[nr];
                                        h[iy] -= ab * bb;
                                        h[hoffset] -= ab * aa;
                                        h[nr] -= ab * tst;
                                    }
                                } else if (nr == 2) {
                                    for (j = b_k; j < 7; j++) {
                                        iy = b_k + 6 * (j - 1);
                                        tst = h[iy - 1];
                                        ab = tst + s * h[iy];
                                        h[iy - 1] = tst - ab * bb;
                                        h[iy] -= ab * aa;
                                    }
                                    for (j = 0; j <= i; j++) {
                                        iy = j + 6 * (b_k - 1);
                                        hoffset = j + 6 * b_k;
                                        ab = h[iy] + s * h[hoffset];
                                        h[iy] -= ab * bb;
                                        h[hoffset] -= ab * aa;
                                    }
                                }
                            }
                            its++;
                        }
                    }
                    if (!goto150) {
                        info = i + 1;
                        exitg1 = true;
                    } else {
                        if ((L != i + 1) && (L == i)) {
                            b_i = i + 6 * i;
                            s = h[b_i - 1];
                            b_k = 6 * (i - 1);
                            iy = i + b_k;
                            rt1r = h[iy];
                            tst = h[b_i];
                            reflapack::xdlanv2(&h[(i + 6 * (i - 1)) - 1], &s, &rt1r, &tst, &aa, &ab,
                                               &bb, &ba, &s_tmp, &rt2r);
                            h[b_i - 1] = s;
                            h[iy] = rt1r;
                            h[b_i] = tst;
                            if (6 > i + 1) {
                                iy = 4 - i;
                                hoffset = i + (i + 1) * 6;
                                for (k = 0; k <= iy; k++) {
                                    nr = hoffset + k * 6;
                                    tst = h[nr];
                                    aa = h[nr - 1];
                                    h[nr] = s_tmp * tst - rt2r * aa;
                                    h[nr - 1] = s_tmp * aa + rt2r * tst;
                                }
                            }
                            if (i - 1 >= 1) {
                                iy = i * 6;
                                for (k = 0; k <= i - 2; k++) {
                                    hoffset = iy + k;
                                    nr = b_k + k;
                                    tst = s_tmp * h[nr] + rt2r * h[hoffset];
                                    h[hoffset] = s_tmp * h[hoffset] - rt2r * h[nr];
                                    h[nr] = tst;
                                }
                            }
                        }
                        i = L - 2;
                    }
                }
                iy = 4;
                for (j = 0; j < 3; j++) {
                    if (iy <= 6) {
                        memset(&h[(j * 6 + iy) + -1], 0, (7 - iy) * sizeof(double));
                    }
                    iy++;
                }
                return info;
            }

        } // namespace lapack
    } // namespace internal
} // namespace coder

//
// File trailer for xhseqr.cpp
//
// [EOF]
//
