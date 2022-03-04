#include "quickselect.h"
#include "rt_nonfinite.h"

namespace coder {
namespace internal {
static int thirdOfFive(const double v[10], int ia, int ib);

}
} // namespace coder

namespace coder {
namespace internal {
static int thirdOfFive(const double v[10], int ia, int ib)
{
    int im;
    if ((ia == ib) || (ia + 1 == ib)) {
        im = ia;
    } else if ((ia + 2 == ib) || (ia + 3 == ib)) {
        double v4;
        v4 = v[ia - 1];
        if (v4 < v[ia]) {
            double v5;
            v5 = v[ia + 1];
            if (v[ia] < v5) {
                im = ia + 1;
            } else if (v4 < v5) {
                im = ia + 2;
            } else {
                im = ia;
            }
        } else {
            double v5;
            v5 = v[ia + 1];
            if (v4 < v5) {
                im = ia;
            } else if (v[ia] < v5) {
                im = ia + 2;
            } else {
                im = ia + 1;
            }
        }
    } else {
        double v4;
        double v5;
        int b_j1;
        int j2;
        int j4;
        int j5;
        v4 = v[ia - 1];
        if (v4 < v[ia]) {
            v5 = v[ia + 1];
            if (v[ia] < v5) {
                b_j1 = ia;
                j2 = ia;
                im = ia + 2;
            } else if (v4 < v5) {
                b_j1 = ia;
                j2 = ia + 1;
                im = ia + 1;
            } else {
                b_j1 = ia + 2;
                j2 = ia - 1;
                im = ia + 1;
            }
        } else {
            v5 = v[ia + 1];
            if (v4 < v5) {
                b_j1 = ia + 1;
                j2 = ia - 1;
                im = ia + 2;
            } else if (v[ia] < v5) {
                b_j1 = ia + 1;
                j2 = ia + 1;
                im = ia;
            } else {
                b_j1 = ia + 2;
                j2 = ia;
                im = ia;
            }
        }
        j4 = ia;
        j5 = ia + 1;
        v4 = v[ia + 2];
        v5 = v[ia + 3];
        if (v5 < v4) {
            j4 = ia + 1;
            j5 = ia;
            v5 = v4;
            v4 = v[ia + 3];
        }
        if (v5 < v[b_j1 - 1]) {
            im = b_j1;
        } else if (v5 < v[j2]) {
            im = j5 + 3;
        } else if (v4 < v[j2]) {
            im = j2 + 1;
        } else if (v4 < v[im - 1]) {
            im = j4 + 3;
        }
    }
    return im;
}

void quickselect(double v[10], int n, int vlen, double *vn, int *nfirst,
                 int *nlast)
{
    if (n > vlen) {
        *vn = rtNaN;
        *nfirst = 0;
        *nlast = 0;
    } else {
        int ia;
        int ib;
        int ilast;
        int ipiv;
        int oldnv;
        boolean_T checkspeed;
        boolean_T exitg1;
        boolean_T isslow;
        ipiv = n;
        ia = 0;
        ib = vlen - 1;
        *nfirst = 1;
        ilast = vlen - 1;
        oldnv = vlen;
        checkspeed = false;
        isslow = false;
        exitg1 = false;
        while ((!exitg1) && (ia + 1 < ib + 1)) {
            double vref;
            int k;
            boolean_T guard1 = false;
            vref = v[ipiv - 1];
            v[ipiv - 1] = v[ib];
            v[ib] = vref;
            ilast = ia;
            ipiv = -1;
            for (k = ia + 1; k <= ib; k++) {
                double d;
                double vk;
                vk = v[k - 1];
                d = v[k - 1];
                if (d == vref) {
                    v[k - 1] = v[ilast];
                    v[ilast] = vk;
                    ipiv++;
                    ilast++;
                } else if (d < vref) {
                    v[k - 1] = v[ilast];
                    v[ilast] = vk;
                    ilast++;
                }
            }
            v[ib] = v[ilast];
            v[ilast] = vref;
            guard1 = false;
            if (n <= ilast + 1) {
                *nfirst = ilast - ipiv;
                if (n >= *nfirst) {
                    exitg1 = true;
                } else {
                    ib = ilast - 1;
                    guard1 = true;
                }
            } else {
                ia = ilast + 1;
                guard1 = true;
            }
            if (guard1) {
                int c;
                c = (ib - ia) + 1;
                if (checkspeed) {
                    isslow = (c > oldnv / 2);
                    oldnv = c;
                }
                checkspeed = !checkspeed;
                if (isslow) {
                    while (c > 1) {
                        int ngroupsof5;
                        ngroupsof5 = c / 5;
                        *nlast = c - ngroupsof5 * 5;
                        c = ngroupsof5;
                        for (k = 0; k < ngroupsof5; k++) {
                            ipiv = (ia + k * 5) + 1;
                            ipiv = thirdOfFive(v, ipiv, ipiv + 4) - 1;
                            ilast = ia + k;
                            vref = v[ilast];
                            v[ilast] = v[ipiv];
                            v[ipiv] = vref;
                        }
                        if (*nlast > 0) {
                            ipiv = (ia + ngroupsof5 * 5) + 1;
                            ipiv =
                                thirdOfFive(v, ipiv, (ipiv + *nlast) - 1) - 1;
                            ilast = ia + ngroupsof5;
                            vref = v[ilast];
                            v[ilast] = v[ipiv];
                            v[ipiv] = vref;
                            c = ngroupsof5 + 1;
                        }
                    }
                } else if (c >= 3) {
                    ipiv = ia + (c - 1) / 2;
                    if (v[ia] < v[ipiv]) {
                        if (!(v[ipiv] < v[ib])) {
                            if (v[ia] < v[ib]) {
                                ipiv = ib;
                            } else {
                                ipiv = ia;
                            }
                        }
                    } else if (v[ia] < v[ib]) {
                        ipiv = ia;
                    } else if (v[ipiv] < v[ib]) {
                        ipiv = ib;
                    }
                    if (ipiv + 1 > ia + 1) {
                        vref = v[ia];
                        v[ia] = v[ipiv];
                        v[ipiv] = vref;
                    }
                }
                ipiv = ia + 1;
                *nfirst = ia + 1;
                ilast = ib;
            }
        }
        *vn = v[ilast];
        *nlast = ilast + 1;
    }
}

} // namespace internal
} // namespace coder
