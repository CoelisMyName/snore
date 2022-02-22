//
// File: quickselect.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "quickselect.h"
#include "rt_nonfinite.h"

// Function Declarations
namespace coder {
    namespace internal {
        static int thirdOfFive(const double v[10], int ia, int ib);

    }
} // namespace coder

// Function Definitions
//
// Arguments    : const double v[10]
//                int ia
//                int ib
// Return Type  : int
//
namespace coder {
    namespace internal {
        static int thirdOfFive(const double v[10], int ia, int ib) {
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

//
// Arguments    : double v[10]
//                int n
//                int idx0
//                int vlen
//                double *vn
//                int *nfirst
//                int *nlast
// Return Type  : void
//
        void quickselect(double v[10], int n, int idx0, int vlen, double *vn,
                         int *nfirst, int *nlast) {
            if ((n < 1) || (n > vlen)) {
                *vn = rtNaN;
                *nfirst = 0;
                *nlast = 0;
            } else {
                int ia;
                int ib;
                int ifirst;
                int ilast;
                int ipiv;
                int itarget;
                int oldnv;
                boolean_T checkspeed;
                boolean_T exitg1;
                boolean_T isslow;
                itarget = (idx0 + n) - 1;
                ipiv = itarget;
                ia = idx0;
                ib = (idx0 + vlen) - 2;
                ifirst = idx0;
                ilast = ib;
                oldnv = vlen;
                checkspeed = false;
                isslow = false;
                exitg1 = false;
                while ((!exitg1) && (ia < ib + 1)) {
                    double d;
                    double vref;
                    int k;
                    boolean_T guard1 = false;
                    vref = v[ipiv - 1];
                    v[ipiv - 1] = v[ib];
                    v[ib] = vref;
                    ilast = ia - 1;
                    ipiv = -1;
                    for (k = ia; k <= ib; k++) {
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
                    if (itarget <= ilast + 1) {
                        ifirst = ilast - ipiv;
                        if (itarget >= ifirst) {
                            exitg1 = true;
                        } else {
                            ib = ilast - 1;
                            guard1 = true;
                        }
                    } else {
                        ia = ilast + 2;
                        guard1 = true;
                    }
                    if (guard1) {
                        ilast = (ib - ia) + 2;
                        if (checkspeed) {
                            isslow = (ilast > oldnv / 2);
                            oldnv = ilast;
                        }
                        checkspeed = !checkspeed;
                        if (isslow) {
                            while (ilast > 1) {
                                int ngroupsof5;
                                ngroupsof5 = ilast / 5;
                                *nlast = ilast - ngroupsof5 * 5;
                                ilast = ngroupsof5;
                                for (k = 0; k < ngroupsof5; k++) {
                                    ipiv = ia + k * 5;
                                    ipiv = thirdOfFive(v, ipiv, ipiv + 4) - 1;
                                    ifirst = (ia + k) - 1;
                                    vref = v[ifirst];
                                    v[ifirst] = v[ipiv];
                                    v[ipiv] = vref;
                                }
                                if (*nlast > 0) {
                                    ipiv = ia + ngroupsof5 * 5;
                                    ipiv = thirdOfFive(v, ipiv, (ipiv + *nlast) - 1) - 1;
                                    ifirst = (ia + ngroupsof5) - 1;
                                    vref = v[ifirst];
                                    v[ifirst] = v[ipiv];
                                    v[ipiv] = vref;
                                    ilast = ngroupsof5 + 1;
                                }
                            }
                        } else if (ilast >= 3) {
                            ipiv = ia + (ilast - 1) / 2;
                            d = v[ia - 1];
                            vref = v[ipiv - 1];
                            if (d < vref) {
                                if (!(vref < v[ib])) {
                                    if (d < v[ib]) {
                                        ipiv = ib + 1;
                                    } else {
                                        ipiv = ia;
                                    }
                                }
                            } else if (d < v[ib]) {
                                ipiv = ia;
                            } else if (vref < v[ib]) {
                                ipiv = ib + 1;
                            }
                            if (ipiv > ia) {
                                v[ia - 1] = v[ipiv - 1];
                                v[ipiv - 1] = d;
                            }
                        }
                        ipiv = ia;
                        ifirst = ia;
                        ilast = ib;
                    }
                }
                *vn = v[ilast];
                *nfirst = (ifirst - idx0) + 1;
                *nlast = (ilast - idx0) + 2;
            }
        }

    } // namespace internal
} // namespace coder

//
// File trailer for quickselect.cpp
//
// [EOF]
//
