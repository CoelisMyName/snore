//
// File: eig.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "eig.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "eigHermitianStandard.h"
#include "rt_nonfinite.h"
#include "xzhgeqz.h"
#include "xzlartg.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const double A[36]
//                creal_T V[6]
// Return Type  : void
//
namespace coder {
    void eig(const double A[36], creal_T V[6]) {
        creal_T At[36];
        creal_T beta1[6];
        creal_T atmp;
        double b_dv[6];
        double absxk;
        int ii;
        boolean_T notdone;
        notdone = true;
        for (ii = 0; ii < 36; ii++) {
            if ((!notdone) || (rtIsInf(A[ii]) || rtIsNaN(A[ii]))) {
                notdone = false;
            }
        }
        if (!notdone) {
            for (int i = 0; i < 6; i++) {
                V[i].re = rtNaN;
                V[i].im = 0.0;
            }
        } else {
            int exitg1;
            int i;
            int j;
            boolean_T exitg2;
            notdone = true;
            j = 0;
            exitg2 = false;
            while ((!exitg2) && (j < 6)) {
                i = 0;
                do {
                    exitg1 = 0;
                    if (i <= j) {
                        if (!(A[i + 6 * j] == A[j + 6 * i])) {
                            notdone = false;
                            exitg1 = 1;
                        } else {
                            i++;
                        }
                    } else {
                        j++;
                        exitg1 = 2;
                    }
                } while (exitg1 == 0);
                if (exitg1 == 1) {
                    exitg2 = true;
                }
            }
            if (notdone) {
                eigHermitianStandard(A, b_dv);
                for (i = 0; i < 6; i++) {
                    V[i].re = b_dv[i];
                    V[i].im = 0.0;
                }
            } else {
                double a;
                double anrm;
                double anrmto;
                double cto1;
                double ctoc;
                double stemp_im;
                for (ii = 0; ii < 36; ii++) {
                    At[ii].re = A[ii];
                    At[ii].im = 0.0;
                }
                anrm = 0.0;
                ii = 0;
                exitg2 = false;
                while ((!exitg2) && (ii < 36)) {
                    absxk = rt_hypotd_snf(At[ii].re, At[ii].im);
                    if (rtIsNaN(absxk)) {
                        anrm = rtNaN;
                        exitg2 = true;
                    } else {
                        if (absxk > anrm) {
                            anrm = absxk;
                        }
                        ii++;
                    }
                }
                if (rtIsInf(anrm) || rtIsNaN(anrm)) {
                    for (i = 0; i < 6; i++) {
                        V[i].re = rtNaN;
                        V[i].im = 0.0;
                        beta1[i].re = rtNaN;
                        beta1[i].im = 0.0;
                    }
                } else {
                    int At_tmp;
                    int exitg3;
                    int ihi;
                    int ilo;
                    int jcol;
                    int nzcount;
                    boolean_T exitg4;
                    boolean_T guard1 = false;
                    boolean_T ilascl;
                    ilascl = false;
                    anrmto = anrm;
                    guard1 = false;
                    if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
                        anrmto = 6.7178761075670888E-139;
                        ilascl = true;
                        guard1 = true;
                    } else if (anrm > 1.4885657073574029E+138) {
                        anrmto = 1.4885657073574029E+138;
                        ilascl = true;
                        guard1 = true;
                    }
                    if (guard1) {
                        absxk = anrm;
                        ctoc = anrmto;
                        notdone = true;
                        while (notdone) {
                            stemp_im = absxk * 2.0041683600089728E-292;
                            cto1 = ctoc / 4.9896007738368E+291;
                            if ((stemp_im > ctoc) && (ctoc != 0.0)) {
                                a = 2.0041683600089728E-292;
                                absxk = stemp_im;
                            } else if (cto1 > absxk) {
                                a = 4.9896007738368E+291;
                                ctoc = cto1;
                            } else {
                                a = ctoc / absxk;
                                notdone = false;
                            }
                            for (ii = 0; ii < 36; ii++) {
                                At[ii].re *= a;
                                At[ii].im *= a;
                            }
                        }
                    }
                    ilo = 1;
                    ihi = 6;
                    do {
                        exitg3 = 0;
                        i = 0;
                        j = 0;
                        notdone = false;
                        ii = ihi;
                        exitg2 = false;
                        while ((!exitg2) && (ii > 0)) {
                            nzcount = 0;
                            i = ii;
                            j = ihi;
                            jcol = 0;
                            exitg4 = false;
                            while ((!exitg4) && (jcol <= ihi - 1)) {
                                At_tmp = (ii + 6 * jcol) - 1;
                                if ((At[At_tmp].re != 0.0) || (At[At_tmp].im != 0.0) ||
                                    (ii == jcol + 1)) {
                                    if (nzcount == 0) {
                                        j = jcol + 1;
                                        nzcount = 1;
                                        jcol++;
                                    } else {
                                        nzcount = 2;
                                        exitg4 = true;
                                    }
                                } else {
                                    jcol++;
                                }
                            }
                            if (nzcount < 2) {
                                notdone = true;
                                exitg2 = true;
                            } else {
                                ii--;
                            }
                        }
                        if (!notdone) {
                            exitg3 = 2;
                        } else {
                            if (i != ihi) {
                                for (ii = 0; ii < 6; ii++) {
                                    nzcount = (i + 6 * ii) - 1;
                                    atmp = At[nzcount];
                                    At_tmp = (ihi + 6 * ii) - 1;
                                    At[nzcount] = At[At_tmp];
                                    At[At_tmp] = atmp;
                                }
                            }
                            if (j != ihi) {
                                for (ii = 0; ii < ihi; ii++) {
                                    nzcount = ii + 6 * (j - 1);
                                    atmp = At[nzcount];
                                    At_tmp = ii + 6 * (ihi - 1);
                                    At[nzcount] = At[At_tmp];
                                    At[At_tmp] = atmp;
                                }
                            }
                            ihi--;
                            if (ihi == 1) {
                                exitg3 = 1;
                            }
                        }
                    } while (exitg3 == 0);
                    if (exitg3 != 1) {
                        do {
                            exitg1 = 0;
                            i = 0;
                            j = 0;
                            notdone = false;
                            jcol = ilo;
                            exitg2 = false;
                            while ((!exitg2) && (jcol <= ihi)) {
                                nzcount = 0;
                                i = ihi;
                                j = jcol;
                                ii = ilo;
                                exitg4 = false;
                                while ((!exitg4) && (ii <= ihi)) {
                                    At_tmp = (ii + 6 * (jcol - 1)) - 1;
                                    if ((At[At_tmp].re != 0.0) || (At[At_tmp].im != 0.0) ||
                                        (ii == jcol)) {
                                        if (nzcount == 0) {
                                            i = ii;
                                            nzcount = 1;
                                            ii++;
                                        } else {
                                            nzcount = 2;
                                            exitg4 = true;
                                        }
                                    } else {
                                        ii++;
                                    }
                                }
                                if (nzcount < 2) {
                                    notdone = true;
                                    exitg2 = true;
                                } else {
                                    jcol++;
                                }
                            }
                            if (!notdone) {
                                exitg1 = 1;
                            } else {
                                if (i != ilo) {
                                    for (ii = ilo; ii < 7; ii++) {
                                        nzcount = 6 * (ii - 1);
                                        jcol = (i + nzcount) - 1;
                                        atmp = At[jcol];
                                        At_tmp = (ilo + nzcount) - 1;
                                        At[jcol] = At[At_tmp];
                                        At[At_tmp] = atmp;
                                    }
                                }
                                if (j != ilo) {
                                    for (ii = 0; ii < ihi; ii++) {
                                        nzcount = ii + 6 * (j - 1);
                                        atmp = At[nzcount];
                                        At_tmp = ii + 6 * (ilo - 1);
                                        At[nzcount] = At[At_tmp];
                                        At[At_tmp] = atmp;
                                    }
                                }
                                ilo++;
                                if (ilo == ihi) {
                                    exitg1 = 1;
                                }
                            }
                        } while (exitg1 == 0);
                    }
                    if (ihi >= ilo + 2) {
                        for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
                            int jcolp1;
                            jcolp1 = jcol + 2;
                            for (int jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
                                At_tmp = jrow + 6 * jcol;
                                internal::reflapack::xzlartg(At[At_tmp - 1], At[At_tmp], &absxk,
                                                             &atmp, &At[(jrow + 6 * jcol) - 1]);
                                At[At_tmp].re = 0.0;
                                At[At_tmp].im = 0.0;
                                for (j = jcolp1; j < 7; j++) {
                                    nzcount = jrow + 6 * (j - 1);
                                    ctoc = absxk * At[nzcount - 1].re +
                                           (atmp.re * At[nzcount].re - atmp.im * At[nzcount].im);
                                    stemp_im =
                                            absxk * At[nzcount - 1].im +
                                            (atmp.re * At[nzcount].im + atmp.im * At[nzcount].re);
                                    cto1 = At[nzcount - 1].re;
                                    At[nzcount].re =
                                            absxk * At[nzcount].re - (atmp.re * At[nzcount - 1].re +
                                                                      atmp.im * At[nzcount - 1].im);
                                    At[nzcount].im =
                                            absxk * At[nzcount].im -
                                            (atmp.re * At[nzcount - 1].im - atmp.im * cto1);
                                    At[nzcount - 1].re = ctoc;
                                    At[nzcount - 1].im = stemp_im;
                                }
                                atmp.re = -atmp.re;
                                atmp.im = -atmp.im;
                                for (i = 1; i <= ihi; i++) {
                                    nzcount = (i + 6 * (jrow - 1)) - 1;
                                    ii = (i + 6 * jrow) - 1;
                                    ctoc = absxk * At[ii].re +
                                           (atmp.re * At[nzcount].re - atmp.im * At[nzcount].im);
                                    stemp_im = absxk * At[ii].im + (atmp.re * At[nzcount].im +
                                                                    atmp.im * At[nzcount].re);
                                    cto1 = At[ii].re;
                                    At[nzcount].re = absxk * At[nzcount].re -
                                                     (atmp.re * At[ii].re + atmp.im * At[ii].im);
                                    At[nzcount].im = absxk * At[nzcount].im -
                                                     (atmp.re * At[ii].im - atmp.im * cto1);
                                    At[ii].re = ctoc;
                                    At[ii].im = stemp_im;
                                }
                            }
                        }
                    }
                    internal::reflapack::xzhgeqz(At, ilo, ihi, &ii, V, beta1);
                    if ((ii == 0) && ilascl) {
                        notdone = true;
                        while (notdone) {
                            stemp_im = anrmto * 2.0041683600089728E-292;
                            cto1 = anrm / 4.9896007738368E+291;
                            if ((stemp_im > anrm) && (anrm != 0.0)) {
                                a = 2.0041683600089728E-292;
                                anrmto = stemp_im;
                            } else if (cto1 > anrmto) {
                                a = 4.9896007738368E+291;
                                anrm = cto1;
                            } else {
                                a = anrm / anrmto;
                                notdone = false;
                            }
                            for (ii = 0; ii < 6; ii++) {
                                V[ii].re *= a;
                                V[ii].im *= a;
                            }
                        }
                    }
                }
                for (ii = 0; ii < 6; ii++) {
                    double ai;
                    anrm = V[ii].re;
                    ai = V[ii].im;
                    ctoc = beta1[ii].re;
                    cto1 = beta1[ii].im;
                    if (cto1 == 0.0) {
                        if (ai == 0.0) {
                            anrmto = anrm / ctoc;
                            absxk = 0.0;
                        } else if (anrm == 0.0) {
                            anrmto = 0.0;
                            absxk = ai / ctoc;
                        } else {
                            anrmto = anrm / ctoc;
                            absxk = ai / ctoc;
                        }
                    } else if (ctoc == 0.0) {
                        if (anrm == 0.0) {
                            anrmto = ai / cto1;
                            absxk = 0.0;
                        } else if (ai == 0.0) {
                            anrmto = 0.0;
                            absxk = -(anrm / cto1);
                        } else {
                            anrmto = ai / cto1;
                            absxk = -(anrm / cto1);
                        }
                    } else {
                        a = fabs(ctoc);
                        absxk = fabs(cto1);
                        if (a > absxk) {
                            stemp_im = cto1 / ctoc;
                            absxk = ctoc + stemp_im * cto1;
                            anrmto = (anrm + stemp_im * ai) / absxk;
                            absxk = (ai - stemp_im * anrm) / absxk;
                        } else if (absxk == a) {
                            if (ctoc > 0.0) {
                                stemp_im = 0.5;
                            } else {
                                stemp_im = -0.5;
                            }
                            if (cto1 > 0.0) {
                                absxk = 0.5;
                            } else {
                                absxk = -0.5;
                            }
                            anrmto = (anrm * stemp_im + ai * absxk) / a;
                            absxk = (ai * stemp_im - anrm * absxk) / a;
                        } else {
                            stemp_im = ctoc / cto1;
                            absxk = cto1 + stemp_im * ctoc;
                            anrmto = (stemp_im * anrm + ai) / absxk;
                            absxk = (stemp_im * ai - anrm) / absxk;
                        }
                    }
                    V[ii].re = anrmto;
                    V[ii].im = absxk;
                }
            }
        }
    }

} // namespace coder

//
// File trailer for eig.cpp
//
// [EOF]
//
