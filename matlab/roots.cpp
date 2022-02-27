//
// File: roots.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "roots.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "eigHermitianStandard.h"
#include "rt_nonfinite.h"
#include "xzggev.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const creal_T c[13]
//                creal_T r_data[]
//                int *r_size
// Return Type  : void
//
namespace coder {
    void roots(const creal_T c[13], creal_T r_data[], int *r_size) {
        creal_T a_data[144];
        creal_T ctmp[13];
        creal_T beta1_data[12];
        creal_T eiga_data[12];
        int a_size[2];
        int k;
        int k1;
        int k2;
        int nTrailingZeros;
        memset(&r_data[0], 0, 12U * sizeof(creal_T));
        k1 = 1;
        while ((k1 <= 13) &&
               ((!(c[k1 - 1].re != 0.0)) && (!(c[k1 - 1].im != 0.0)))) {
            k1++;
        }
        k2 = 13;
        while ((k2 >= k1) &&
               ((!(c[k2 - 1].re != 0.0)) && (!(c[k2 - 1].im != 0.0)))) {
            k2--;
        }
        nTrailingZeros = 12 - k2;
        if (k1 < k2) {
            double ai;
            double ar;
            double bi;
            double bim;
            double br;
            double brm;
            double s;
            int companDim;
            int j;
            boolean_T exitg1;
            companDim = k2 - k1;
            exitg1 = false;
            while ((!exitg1) && (companDim > 0)) {
                boolean_T exitg2;
                j = 0;
                exitg2 = false;
                while ((!exitg2) && (j + 1 <= companDim)) {
                    k = k1 + j;
                    ar = c[k].re;
                    ai = c[k].im;
                    br = c[k1 - 1].re;
                    bi = c[k1 - 1].im;
                    if (bi == 0.0) {
                        if (ai == 0.0) {
                            ctmp[j].re = ar / br;
                            ctmp[j].im = 0.0;
                        } else if (ar == 0.0) {
                            ctmp[j].re = 0.0;
                            ctmp[j].im = ai / br;
                        } else {
                            ctmp[j].re = ar / br;
                            ctmp[j].im = ai / br;
                        }
                    } else if (br == 0.0) {
                        if (ar == 0.0) {
                            ctmp[j].re = ai / bi;
                            ctmp[j].im = 0.0;
                        } else if (ai == 0.0) {
                            ctmp[j].re = 0.0;
                            ctmp[j].im = -(ar / bi);
                        } else {
                            ctmp[j].re = ai / bi;
                            ctmp[j].im = -(ar / bi);
                        }
                    } else {
                        brm = fabs(br);
                        bim = fabs(bi);
                        if (brm > bim) {
                            s = bi / br;
                            bim = br + s * bi;
                            ctmp[j].re = (ar + s * ai) / bim;
                            ctmp[j].im = (ai - s * ar) / bim;
                        } else if (bim == brm) {
                            if (br > 0.0) {
                                s = 0.5;
                            } else {
                                s = -0.5;
                            }
                            if (bi > 0.0) {
                                bim = 0.5;
                            } else {
                                bim = -0.5;
                            }
                            ctmp[j].re = (ar * s + ai * bim) / brm;
                            ctmp[j].im = (ai * s - ar * bim) / brm;
                        } else {
                            s = br / bi;
                            bim = bi + s * br;
                            ctmp[j].re = (s * ar + ai) / bim;
                            ctmp[j].im = (s * ai - ar) / bim;
                        }
                    }
                    if (rtIsInf(rt_hypotd_snf(ctmp[j].re, ctmp[j].im))) {
                        exitg2 = true;
                    } else {
                        j++;
                    }
                }
                if (j + 1 > companDim) {
                    exitg1 = true;
                } else {
                    k1++;
                    companDim--;
                }
            }
            if (companDim < 1) {
                if (1 > 13 - k2) {
                    *r_size = 0;
                } else {
                    *r_size = 13 - k2;
                }
            } else {
                int i;
                boolean_T p;
                a_size[0] = companDim;
                a_size[1] = companDim;
                k1 = companDim * companDim;
                if (0 <= k1 - 1) {
                    memset(&a_data[0], 0, k1 * sizeof(creal_T));
                }
                for (k = 0; k <= companDim - 2; k++) {
                    i = companDim * k;
                    a_data[i].re = -ctmp[k].re;
                    a_data[i].im = -ctmp[k].im;
                    i = (k + i) + 1;
                    a_data[i].re = 1.0;
                    a_data[i].im = 0.0;
                }
                i = companDim * (companDim - 1);
                a_data[i].re = -ctmp[companDim - 1].re;
                a_data[i].im = -ctmp[companDim - 1].im;
                if (0 <= nTrailingZeros) {
                    memset(&r_data[0], 0, (nTrailingZeros + 1) * sizeof(creal_T));
                }
                k1 = companDim * companDim;
                p = true;
                for (k = 0; k < k1; k++) {
                    if ((!p) ||
                        (rtIsInf(a_data[k].re) || rtIsInf(a_data[k].im) ||
                         (rtIsNaN(a_data[k].re) || rtIsNaN(a_data[k].im)))) {
                        p = false;
                    }
                }
                if (!p) {
                    for (i = 0; i < companDim; i++) {
                        eiga_data[i].re = rtNaN;
                        eiga_data[i].im = 0.0;
                    }
                } else {
                    p = true;
                    j = 0;
                    exitg1 = false;
                    while ((!exitg1) && (j <= companDim - 1)) {
                        int exitg3;
                        k1 = 0;
                        do {
                            exitg3 = 0;
                            if (k1 <= j) {
                                i = k1 + companDim * j;
                                k = j + companDim * k1;
                                if ((!(a_data[i].re == a_data[k].re)) ||
                                    (!(a_data[i].im == -a_data[k].im))) {
                                    p = false;
                                    exitg3 = 1;
                                } else {
                                    k1++;
                                }
                            } else {
                                j++;
                                exitg3 = 2;
                            }
                        } while (exitg3 == 0);
                        if (exitg3 == 1) {
                            exitg1 = true;
                        }
                    }
                    if (p) {
                        eigHermitianStandard(a_data, a_size, eiga_data,
                                             &nTrailingZeros);
                    } else {
                        internal::reflapack::xzggev(a_data, a_size, &k1, eiga_data,
                                                    &nTrailingZeros, beta1_data,
                                                    &k);
                        for (i = 0; i < nTrailingZeros; i++) {
                            double re;
                            ar = eiga_data[i].re;
                            ai = eiga_data[i].im;
                            br = beta1_data[i].re;
                            bi = beta1_data[i].im;
                            if (bi == 0.0) {
                                if (ai == 0.0) {
                                    re = ar / br;
                                    bim = 0.0;
                                } else if (ar == 0.0) {
                                    re = 0.0;
                                    bim = ai / br;
                                } else {
                                    re = ar / br;
                                    bim = ai / br;
                                }
                            } else if (br == 0.0) {
                                if (ar == 0.0) {
                                    re = ai / bi;
                                    bim = 0.0;
                                } else if (ai == 0.0) {
                                    re = 0.0;
                                    bim = -(ar / bi);
                                } else {
                                    re = ai / bi;
                                    bim = -(ar / bi);
                                }
                            } else {
                                brm = fabs(br);
                                bim = fabs(bi);
                                if (brm > bim) {
                                    s = bi / br;
                                    bim = br + s * bi;
                                    re = (ar + s * ai) / bim;
                                    bim = (ai - s * ar) / bim;
                                } else if (bim == brm) {
                                    if (br > 0.0) {
                                        s = 0.5;
                                    } else {
                                        s = -0.5;
                                    }
                                    if (bi > 0.0) {
                                        bim = 0.5;
                                    } else {
                                        bim = -0.5;
                                    }
                                    re = (ar * s + ai * bim) / brm;
                                    bim = (ai * s - ar * bim) / brm;
                                } else {
                                    s = br / bi;
                                    bim = bi + s * br;
                                    re = (s * ar + ai) / bim;
                                    bim = (s * ai - ar) / bim;
                                }
                            }
                            eiga_data[i].re = re;
                            eiga_data[i].im = bim;
                        }
                    }
                }
                for (k = 0; k < companDim; k++) {
                    r_data[(k - k2) + 13] = eiga_data[k];
                }
                *r_size = (companDim - k2) + 13;
            }
        } else if (1 > 13 - k2) {
            *r_size = 0;
        } else {
            *r_size = 13 - k2;
        }
    }

//
// Arguments    : const double c_data[]
//                int c_size
//                creal_T r_data[]
//                int *r_size
// Return Type  : void
//
    void roots(const double c_data[], int c_size, creal_T r_data[], int *r_size) {
        creal_T At_data[144];
        creal_T beta1_data[12];
        creal_T eiga_data[12];
        double a_data[100];
        double ctmp_data[11];
        double tmp_data[10];
        int At_size[2];
        int a_size[2];
        int j;
        int k1;
        int k2;
        int nTrailingZeros;
        if (0 <= c_size - 2) {
            memset(&r_data[0], 0, (c_size + -1) * sizeof(creal_T));
        }
        k1 = 1;
        while ((k1 <= c_size) && (!(c_data[k1 - 1] != 0.0))) {
            k1++;
        }
        k2 = c_size;
        while ((k2 >= k1) && (!(c_data[k2 - 1] != 0.0))) {
            k2--;
        }
        nTrailingZeros = c_size - k2;
        if (k1 < k2) {
            int companDim;
            boolean_T exitg1;
            companDim = k2 - k1;
            exitg1 = false;
            while ((!exitg1) && (companDim > 0)) {
                boolean_T exitg2;
                j = 0;
                exitg2 = false;
                while ((!exitg2) && (j + 1 <= companDim)) {
                    ctmp_data[j] = c_data[k1 + j] / c_data[k1 - 1];
                    if (rtIsInf(fabs(ctmp_data[j]))) {
                        exitg2 = true;
                    } else {
                        j++;
                    }
                }
                if (j + 1 > companDim) {
                    exitg1 = true;
                } else {
                    k1++;
                    companDim--;
                }
            }
            if (companDim < 1) {
                if (1 > nTrailingZeros) {
                    *r_size = 0;
                } else {
                    *r_size = nTrailingZeros;
                }
            } else {
                int nx_tmp;
                boolean_T p;
                a_size[0] = companDim;
                a_size[1] = companDim;
                k2 = companDim * companDim;
                if (0 <= k2 - 1) {
                    memset(&a_data[0], 0, k2 * sizeof(double));
                }
                for (k1 = 0; k1 <= companDim - 2; k1++) {
                    k2 = companDim * k1;
                    a_data[k2] = -ctmp_data[k1];
                    a_data[(k1 + k2) + 1] = 1.0;
                }
                a_data[companDim * (companDim - 1)] = -ctmp_data[companDim - 1];
                if (0 <= nTrailingZeros - 1) {
                    memset(&r_data[0], 0, nTrailingZeros * sizeof(creal_T));
                }
                nx_tmp = companDim * companDim;
                p = true;
                for (k1 = 0; k1 < nx_tmp; k1++) {
                    if ((!p) || (rtIsInf(a_data[k1]) || rtIsNaN(a_data[k1]))) {
                        p = false;
                    }
                }
                if (!p) {
                    for (k1 = 0; k1 < companDim; k1++) {
                        eiga_data[k1].re = rtNaN;
                        eiga_data[k1].im = 0.0;
                    }
                } else {
                    p = true;
                    j = 0;
                    exitg1 = false;
                    while ((!exitg1) && (j <= companDim - 1)) {
                        int exitg3;
                        k2 = 0;
                        do {
                            exitg3 = 0;
                            if (k2 <= j) {
                                if (!(a_data[k2 + companDim * j] ==
                                      a_data[j + companDim * k2])) {
                                    p = false;
                                    exitg3 = 1;
                                } else {
                                    k2++;
                                }
                            } else {
                                j++;
                                exitg3 = 2;
                            }
                        } while (exitg3 == 0);
                        if (exitg3 == 1) {
                            exitg1 = true;
                        }
                    }
                    if (p) {
                        eigHermitianStandard(a_data, a_size, tmp_data, &k2);
                        for (k1 = 0; k1 < k2; k1++) {
                            eiga_data[k1].re = tmp_data[k1];
                            eiga_data[k1].im = 0.0;
                        }
                    } else {
                        At_size[0] = companDim;
                        At_size[1] = companDim;
                        for (k1 = 0; k1 < nx_tmp; k1++) {
                            At_data[k1].re = a_data[k1];
                            At_data[k1].im = 0.0;
                        }
                        internal::reflapack::xzggev(At_data, At_size, &k2,
                                                    eiga_data, &j, beta1_data, &k1);
                        for (k1 = 0; k1 < j; k1++) {
                            double ai;
                            double ar;
                            double bi;
                            double br;
                            double im;
                            double re;
                            ar = eiga_data[k1].re;
                            ai = eiga_data[k1].im;
                            br = beta1_data[k1].re;
                            bi = beta1_data[k1].im;
                            if (bi == 0.0) {
                                if (ai == 0.0) {
                                    re = ar / br;
                                    im = 0.0;
                                } else if (ar == 0.0) {
                                    re = 0.0;
                                    im = ai / br;
                                } else {
                                    re = ar / br;
                                    im = ai / br;
                                }
                            } else if (br == 0.0) {
                                if (ar == 0.0) {
                                    re = ai / bi;
                                    im = 0.0;
                                } else if (ai == 0.0) {
                                    re = 0.0;
                                    im = -(ar / bi);
                                } else {
                                    re = ai / bi;
                                    im = -(ar / bi);
                                }
                            } else {
                                double brm;
                                brm = fabs(br);
                                im = fabs(bi);
                                if (brm > im) {
                                    double s;
                                    s = bi / br;
                                    im = br + s * bi;
                                    re = (ar + s * ai) / im;
                                    im = (ai - s * ar) / im;
                                } else if (im == brm) {
                                    double s;
                                    if (br > 0.0) {
                                        s = 0.5;
                                    } else {
                                        s = -0.5;
                                    }
                                    if (bi > 0.0) {
                                        im = 0.5;
                                    } else {
                                        im = -0.5;
                                    }
                                    re = (ar * s + ai * im) / brm;
                                    im = (ai * s - ar * im) / brm;
                                } else {
                                    double s;
                                    s = br / bi;
                                    im = bi + s * br;
                                    re = (s * ar + ai) / im;
                                    im = (s * ai - ar) / im;
                                }
                            }
                            eiga_data[k1].re = re;
                            eiga_data[k1].im = im;
                        }
                    }
                }
                for (k1 = 0; k1 < companDim; k1++) {
                    r_data[k1 + nTrailingZeros] = eiga_data[k1];
                }
                k2 = nTrailingZeros + companDim;
                if (1 > k2) {
                    *r_size = 0;
                } else {
                    *r_size = k2;
                }
            }
        } else if (1 > nTrailingZeros) {
            *r_size = 0;
        } else {
            *r_size = nTrailingZeros;
        }
    }

} // namespace coder

//
// File trailer for roots.cpp
//
// [EOF]
//
