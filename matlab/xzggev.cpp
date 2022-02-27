//
// File: xzggev.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "xzggev.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "xzhgeqz.h"
#include "xzlartg.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : creal_T A_data[]
//                const int A_size[2]
//                int *info
//                creal_T alpha1_data[]
//                int *alpha1_size
//                creal_T beta1_data[]
//                int *beta1_size
// Return Type  : void
//
namespace coder {
    namespace internal {
        namespace reflapack {
            void xzggev(creal_T A_data[], const int A_size[2], int *info,
                        creal_T alpha1_data[], int *alpha1_size, creal_T beta1_data[],
                        int *beta1_size) {
                creal_T atmp;
                double absxk;
                double anrm;
                int i;
                int jcol;
                boolean_T exitg1;
                *info = 0;
                anrm = 0.0;
                i = A_size[0] * A_size[1];
                jcol = 0;
                exitg1 = false;
                while ((!exitg1) && (jcol <= i - 1)) {
                    absxk = rt_hypotd_snf(A_data[jcol].re, A_data[jcol].im);
                    if (rtIsNaN(absxk)) {
                        anrm = rtNaN;
                        exitg1 = true;
                    } else {
                        if (absxk > anrm) {
                            anrm = absxk;
                        }
                        jcol++;
                    }
                }
                if (rtIsInf(anrm) || rtIsNaN(anrm)) {
                    int jcolp1;
                    *alpha1_size = A_size[0];
                    jcolp1 = A_size[0];
                    for (i = 0; i < jcolp1; i++) {
                        alpha1_data[i].re = rtNaN;
                        alpha1_data[i].im = 0.0;
                    }
                    *beta1_size = A_size[0];
                    jcolp1 = A_size[0];
                    for (i = 0; i < jcolp1; i++) {
                        beta1_data[i].re = rtNaN;
                        beta1_data[i].im = 0.0;
                    }
                } else {
                    double a;
                    double anrmto;
                    double cto1;
                    double ctoc;
                    double stemp_im;
                    int b_i;
                    int ihi;
                    int ii;
                    int ilo;
                    int j;
                    int jcolp1;
                    int n;
                    int nzcount;
                    boolean_T guard1 = false;
                    boolean_T ilascl;
                    boolean_T notdone;
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
                            jcolp1 = A_size[1];
                            for (i = 0; i < jcolp1; i++) {
                                ii = A_size[0];
                                for (jcol = 0; jcol < ii; jcol++) {
                                    nzcount = jcol + A_size[0] * i;
                                    A_data[nzcount].re *= a;
                                    A_data[nzcount].im *= a;
                                }
                            }
                        }
                    }
                    ilo = 1;
                    ihi = A_size[0];
                    if (A_size[0] <= 1) {
                        ihi = 1;
                    } else {
                        int exitg3;
                        boolean_T exitg4;
                        do {
                            exitg3 = 0;
                            b_i = 0;
                            j = 0;
                            notdone = false;
                            ii = ihi;
                            exitg1 = false;
                            while ((!exitg1) && (ii > 0)) {
                                nzcount = 0;
                                b_i = ii;
                                j = ihi;
                                jcol = 0;
                                exitg4 = false;
                                while ((!exitg4) && (jcol <= ihi - 1)) {
                                    i = (ii + A_size[0] * jcol) - 1;
                                    if ((A_data[i].re != 0.0) || (A_data[i].im != 0.0) ||
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
                                    exitg1 = true;
                                } else {
                                    ii--;
                                }
                            }
                            if (!notdone) {
                                exitg3 = 2;
                            } else {
                                n = A_size[0];
                                if (b_i != ihi) {
                                    for (jcol = 1; jcol <= n; jcol++) {
                                        ii = A_size[0] * (jcol - 1);
                                        nzcount = (b_i + ii) - 1;
                                        atmp = A_data[nzcount];
                                        i = (ihi + ii) - 1;
                                        A_data[nzcount] = A_data[i];
                                        A_data[i] = atmp;
                                    }
                                }
                                if (j != ihi) {
                                    for (jcol = 0; jcol < ihi; jcol++) {
                                        ii = jcol + A_size[0] * (j - 1);
                                        atmp = A_data[ii];
                                        i = jcol + A_size[0] * (ihi - 1);
                                        A_data[ii] = A_data[i];
                                        A_data[i] = atmp;
                                    }
                                }
                                ihi--;
                                if (ihi == 1) {
                                    exitg3 = 1;
                                }
                            }
                        } while (exitg3 == 0);
                        if (exitg3 != 1) {
                            int exitg2;
                            do {
                                exitg2 = 0;
                                b_i = 0;
                                j = 0;
                                notdone = false;
                                jcol = ilo;
                                exitg1 = false;
                                while ((!exitg1) && (jcol <= ihi)) {
                                    nzcount = 0;
                                    b_i = ihi;
                                    j = jcol;
                                    ii = ilo;
                                    exitg4 = false;
                                    while ((!exitg4) && (ii <= ihi)) {
                                        i = (ii + A_size[0] * (jcol - 1)) - 1;
                                        if ((A_data[i].re != 0.0) ||
                                            (A_data[i].im != 0.0) || (ii == jcol)) {
                                            if (nzcount == 0) {
                                                b_i = ii;
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
                                        exitg1 = true;
                                    } else {
                                        jcol++;
                                    }
                                }
                                if (!notdone) {
                                    exitg2 = 1;
                                } else {
                                    n = A_size[0];
                                    if (b_i != ilo) {
                                        for (jcol = ilo; jcol <= n; jcol++) {
                                            ii = A_size[0] * (jcol - 1);
                                            nzcount = (b_i + ii) - 1;
                                            atmp = A_data[nzcount];
                                            i = (ilo + ii) - 1;
                                            A_data[nzcount] = A_data[i];
                                            A_data[i] = atmp;
                                        }
                                    }
                                    if (j != ilo) {
                                        for (jcol = 0; jcol < ihi; jcol++) {
                                            ii = jcol + A_size[0] * (j - 1);
                                            atmp = A_data[ii];
                                            i = jcol + A_size[0] * (ilo - 1);
                                            A_data[ii] = A_data[i];
                                            A_data[i] = atmp;
                                        }
                                    }
                                    ilo++;
                                    if (ilo == ihi) {
                                        exitg2 = 1;
                                    }
                                }
                            } while (exitg2 == 0);
                        }
                    }
                    n = A_size[0];
                    if ((A_size[0] > 1) && (ihi >= ilo + 2)) {
                        for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
                            jcolp1 = jcol + 2;
                            for (int jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
                                xzlartg(A_data[(jrow + A_size[0] * jcol) - 1],
                                        A_data[jrow + A_size[0] * jcol], &absxk, &atmp,
                                        &A_data[(jrow + A_size[0] * jcol) - 1]);
                                i = jrow + A_size[0] * jcol;
                                A_data[i].re = 0.0;
                                A_data[i].im = 0.0;
                                for (j = jcolp1; j <= n; j++) {
                                    nzcount = jrow + A_size[0] * (j - 1);
                                    ctoc = absxk * A_data[nzcount - 1].re +
                                           (atmp.re * A_data[nzcount].re -
                                            atmp.im * A_data[nzcount].im);
                                    stemp_im = absxk * A_data[nzcount - 1].im +
                                               (atmp.re * A_data[nzcount].im +
                                                atmp.im * A_data[nzcount].re);
                                    cto1 = A_data[nzcount - 1].im;
                                    a = A_data[nzcount - 1].re;
                                    A_data[nzcount].re = absxk * A_data[nzcount].re -
                                                         (atmp.re * A_data[nzcount - 1].re +
                                                          atmp.im * A_data[nzcount - 1].im);
                                    A_data[nzcount].im = absxk * A_data[nzcount].im -
                                                         (atmp.re * cto1 - atmp.im * a);
                                    A_data[nzcount - 1].re = ctoc;
                                    A_data[nzcount - 1].im = stemp_im;
                                }
                                atmp.re = -atmp.re;
                                atmp.im = -atmp.im;
                                for (b_i = 1; b_i <= ihi; b_i++) {
                                    nzcount = (b_i + A_size[0] * (jrow - 1)) - 1;
                                    ii = (b_i + A_size[0] * jrow) - 1;
                                    ctoc = absxk * A_data[ii].re +
                                           (atmp.re * A_data[nzcount].re -
                                            atmp.im * A_data[nzcount].im);
                                    stemp_im = absxk * A_data[ii].im +
                                               (atmp.re * A_data[nzcount].im +
                                                atmp.im * A_data[nzcount].re);
                                    cto1 = A_data[ii].im;
                                    a = A_data[ii].re;
                                    A_data[nzcount].re =
                                            absxk * A_data[nzcount].re -
                                            (atmp.re * A_data[ii].re + atmp.im * A_data[ii].im);
                                    A_data[nzcount].im = absxk * A_data[nzcount].im -
                                                         (atmp.re * cto1 - atmp.im * a);
                                    A_data[ii].re = ctoc;
                                    A_data[ii].im = stemp_im;
                                }
                            }
                        }
                    }
                    xzhgeqz(A_data, A_size, ilo, ihi, info, alpha1_data, alpha1_size,
                            beta1_data, beta1_size);
                    if ((*info == 0) && ilascl) {
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
                            for (i = 0; i < *alpha1_size; i++) {
                                alpha1_data[i].re *= a;
                                alpha1_data[i].im *= a;
                            }
                        }
                    }
                }
            }

        } // namespace reflapack
    } // namespace internal
} // namespace coder

//
// File trailer for xzggev.cpp
//
// [EOF]
//
