//
// File: xzhgeqz.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "xzhgeqz.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xzlartg.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const creal_T A_data[]
//                const int A_size[2]
//                int ilo
//                int ihi
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
            void xzhgeqz(const creal_T A_data[], const int A_size[2], int ilo, int ihi,
                         int *info, creal_T alpha1_data[], int *alpha1_size,
                         creal_T beta1_data[], int *beta1_size) {
                creal_T b_A_data[144];
                creal_T b_ascale;
                creal_T ctemp;
                creal_T shift;
                double absxk;
                double anorm;
                double ascale;
                double b_atol;
                double bscale;
                double colscale;
                double colssq;
                double eshift_im;
                double eshift_re;
                double scale;
                double t;
                int A_size_idx_0;
                int col;
                int i;
                int ilast;
                int j;
                int jm1;
                int n;
                int nm1;
                int row;
                boolean_T failed;
                boolean_T guard1 = false;
                boolean_T guard2 = false;
                A_size_idx_0 = A_size[0];
                jm1 = A_size[0] * A_size[1];
                if (0 <= jm1 - 1) {
                    memcpy(&b_A_data[0], &A_data[0], jm1 * sizeof(creal_T));
                }
                *info = 0;
                if ((A_size[0] == 1) && (A_size[1] == 1)) {
                    ihi = 1;
                }
                n = A_size[0];
                *alpha1_size = A_size[0];
                jm1 = A_size[0];
                if (0 <= jm1 - 1) {
                    memset(&alpha1_data[0], 0, jm1 * sizeof(creal_T));
                }
                *beta1_size = A_size[0];
                jm1 = A_size[0];
                for (i = 0; i < jm1; i++) {
                    beta1_data[i].re = 1.0;
                    beta1_data[i].im = 0.0;
                }
                eshift_re = 0.0;
                eshift_im = 0.0;
                ctemp.re = 0.0;
                ctemp.im = 0.0;
                anorm = 0.0;
                if (ilo <= ihi) {
                    scale = 3.3121686421112381E-170;
                    anorm = 0.0;
                    nm1 = ihi - ilo;
                    for (j = 0; j <= nm1; j++) {
                        colscale = 3.3121686421112381E-170;
                        colssq = 0.0;
                        col = (ilo + j) - 1;
                        jm1 = j + 1;
                        if (jm1 >= nm1) {
                            jm1 = nm1;
                        }
                        i = ilo + jm1;
                        for (row = ilo; row <= i; row++) {
                            jm1 = (row + A_size[0] * col) - 1;
                            absxk = fabs(A_data[jm1].re);
                            if (absxk > colscale) {
                                t = colscale / absxk;
                                colssq = colssq * t * t + 1.0;
                                colscale = absxk;
                            } else {
                                t = absxk / colscale;
                                colssq += t * t;
                            }
                            absxk = fabs(A_data[jm1].im);
                            if (absxk > colscale) {
                                t = colscale / absxk;
                                colssq = colssq * t * t + 1.0;
                                colscale = absxk;
                            } else {
                                t = absxk / colscale;
                                colssq += t * t;
                            }
                        }
                        if (scale >= colscale) {
                            anorm += rt_powd_snf(colscale / scale, 2.0) * colssq;
                        } else {
                            anorm = colssq + rt_powd_snf(scale / colscale, 2.0) * anorm;
                            scale = colscale;
                        }
                    }
                    anorm = scale * sqrt(anorm);
                }
                scale = 2.2204460492503131E-16 * anorm;
                b_atol = 2.2250738585072014E-308;
                if (scale > 2.2250738585072014E-308) {
                    b_atol = scale;
                }
                scale = 2.2250738585072014E-308;
                if (anorm > 2.2250738585072014E-308) {
                    scale = anorm;
                }
                ascale = 1.0 / scale;
                bscale = 1.0 / sqrt(static_cast<double>(A_size[0]));
                failed = true;
                i = ihi + 1;
                for (j = i; j <= n; j++) {
                    alpha1_data[j - 1] = A_data[(j + A_size[0] * (j - 1)) - 1];
                }
                guard1 = false;
                guard2 = false;
                if (ihi >= ilo) {
                    int ifirst;
                    int iiter;
                    int ilastm;
                    int ilastm1;
                    int istart;
                    int jiter;
                    boolean_T goto60;
                    boolean_T goto70;
                    boolean_T goto90;
                    ifirst = ilo;
                    istart = ilo;
                    ilast = ihi - 1;
                    ilastm1 = ihi - 2;
                    ilastm = ihi;
                    iiter = 0;
                    goto60 = false;
                    goto70 = false;
                    goto90 = false;
                    jiter = 0;
                    int exitg1;
                    do {
                        exitg1 = 0;
                        if (jiter <= 30 * ((ihi - ilo) + 1) - 1) {
                            boolean_T b_guard1 = false;
                            boolean_T exitg2;
                            b_guard1 = false;
                            if (ilast + 1 == ilo) {
                                goto60 = true;
                                b_guard1 = true;
                            } else {
                                i = ilast + A_size_idx_0 * ilastm1;
                                if (fabs(b_A_data[i].re) + fabs(b_A_data[i].im) <= b_atol) {
                                    b_A_data[i].re = 0.0;
                                    b_A_data[i].im = 0.0;
                                    goto60 = true;
                                    b_guard1 = true;
                                } else {
                                    boolean_T guard3 = false;
                                    j = ilastm1;
                                    guard3 = false;
                                    exitg2 = false;
                                    while ((!exitg2) && (j + 1 >= ilo)) {
                                        if (j + 1 == ilo) {
                                            guard3 = true;
                                            exitg2 = true;
                                        } else {
                                            i = j + A_size_idx_0 * (j - 1);
                                            if (fabs(b_A_data[i].re) +
                                                fabs(b_A_data[i].im) <=
                                                b_atol) {
                                                b_A_data[i].re = 0.0;
                                                b_A_data[i].im = 0.0;
                                                guard3 = true;
                                                exitg2 = true;
                                            } else {
                                                j--;
                                                guard3 = false;
                                            }
                                        }
                                    }
                                    if (guard3) {
                                        ifirst = j + 1;
                                        goto70 = true;
                                    }
                                    if (goto70) {
                                        b_guard1 = true;
                                    } else {
                                        for (i = 0; i < *alpha1_size; i++) {
                                            alpha1_data[i].re = rtNaN;
                                            alpha1_data[i].im = 0.0;
                                        }
                                        for (i = 0; i < *beta1_size; i++) {
                                            beta1_data[i].re = rtNaN;
                                            beta1_data[i].im = 0.0;
                                        }
                                        *info = 1;
                                        exitg1 = 1;
                                    }
                                }
                            }
                            if (b_guard1) {
                                if (goto60) {
                                    goto60 = false;
                                    alpha1_data[ilast] =
                                            b_A_data[ilast + A_size_idx_0 * ilast];
                                    ilast = ilastm1;
                                    ilastm1--;
                                    if (ilast + 1 < ilo) {
                                        failed = false;
                                        guard2 = true;
                                        exitg1 = 1;
                                    } else {
                                        iiter = 0;
                                        eshift_re = 0.0;
                                        eshift_im = 0.0;
                                        ilastm = ilast + 1;
                                        jiter++;
                                    }
                                } else {
                                    if (goto70) {
                                        double ad22_im;
                                        double ad22_re;
                                        goto70 = false;
                                        iiter++;
                                        if (iiter - iiter / 10 * 10 != 0) {
                                            double t1_im;
                                            double t1_im_tmp;
                                            double t1_re;
                                            jm1 = ilastm1 + A_size_idx_0 * ilastm1;
                                            anorm = ascale * b_A_data[jm1].re;
                                            scale = ascale * b_A_data[jm1].im;
                                            if (scale == 0.0) {
                                                shift.re = anorm / bscale;
                                                shift.im = 0.0;
                                            } else if (anorm == 0.0) {
                                                shift.re = 0.0;
                                                shift.im = scale / bscale;
                                            } else {
                                                shift.re = anorm / bscale;
                                                shift.im = scale / bscale;
                                            }
                                            jm1 = ilast + A_size_idx_0 * ilast;
                                            anorm = ascale * b_A_data[jm1].re;
                                            scale = ascale * b_A_data[jm1].im;
                                            if (scale == 0.0) {
                                                ad22_re = anorm / bscale;
                                                ad22_im = 0.0;
                                            } else if (anorm == 0.0) {
                                                ad22_re = 0.0;
                                                ad22_im = scale / bscale;
                                            } else {
                                                ad22_re = anorm / bscale;
                                                ad22_im = scale / bscale;
                                            }
                                            t1_re = 0.5 * (shift.re + ad22_re);
                                            t1_im = 0.5 * (shift.im + ad22_im);
                                            t1_im_tmp = t1_re * t1_im;
                                            jm1 = ilastm1 + A_size_idx_0 * ilast;
                                            anorm = ascale * b_A_data[jm1].re;
                                            scale = ascale * b_A_data[jm1].im;
                                            if (scale == 0.0) {
                                                absxk = anorm / bscale;
                                                t = 0.0;
                                            } else if (anorm == 0.0) {
                                                absxk = 0.0;
                                                t = scale / bscale;
                                            } else {
                                                absxk = anorm / bscale;
                                                t = scale / bscale;
                                            }
                                            jm1 = ilast + A_size_idx_0 * ilastm1;
                                            anorm = ascale * b_A_data[jm1].re;
                                            scale = ascale * b_A_data[jm1].im;
                                            if (scale == 0.0) {
                                                colssq = anorm / bscale;
                                                anorm = 0.0;
                                            } else if (anorm == 0.0) {
                                                colssq = 0.0;
                                                anorm = scale / bscale;
                                            } else {
                                                colssq = anorm / bscale;
                                                anorm = scale / bscale;
                                            }
                                            scale = shift.re * ad22_re - shift.im * ad22_im;
                                            colscale =
                                                    shift.re * ad22_im + shift.im * ad22_re;
                                            shift.re = ((t1_re * t1_re - t1_im * t1_im) +
                                                        (absxk * colssq - t * anorm)) -
                                                       scale;
                                            shift.im = ((t1_im_tmp + t1_im_tmp) +
                                                        (absxk * anorm + t * colssq)) -
                                                       colscale;
                                            b_sqrt(&shift);
                                            if ((t1_re - ad22_re) * shift.re +
                                                (t1_im - ad22_im) * shift.im <=
                                                0.0) {
                                                shift.re += t1_re;
                                                shift.im += t1_im;
                                            } else {
                                                shift.re = t1_re - shift.re;
                                                shift.im = t1_im - shift.im;
                                            }
                                        } else {
                                            jm1 = ilast + A_size_idx_0 * ilastm1;
                                            anorm = ascale * b_A_data[jm1].re;
                                            scale = ascale * b_A_data[jm1].im;
                                            if (scale == 0.0) {
                                                absxk = anorm / bscale;
                                                t = 0.0;
                                            } else if (anorm == 0.0) {
                                                absxk = 0.0;
                                                t = scale / bscale;
                                            } else {
                                                absxk = anorm / bscale;
                                                t = scale / bscale;
                                            }
                                            eshift_re += absxk;
                                            eshift_im += t;
                                            shift.re = eshift_re;
                                            shift.im = eshift_im;
                                        }
                                        j = ilastm1;
                                        nm1 = ilastm1 + 1;
                                        exitg2 = false;
                                        while ((!exitg2) && (j + 1 > ifirst)) {
                                            istart = j + 1;
                                            col = A_size_idx_0 * j;
                                            row = j + col;
                                            ctemp.re = ascale * b_A_data[row].re -
                                                       shift.re * bscale;
                                            ctemp.im = ascale * b_A_data[row].im -
                                                       shift.im * bscale;
                                            anorm = fabs(ctemp.re) + fabs(ctemp.im);
                                            jm1 = nm1 + col;
                                            scale = ascale * (fabs(b_A_data[jm1].re) +
                                                              fabs(b_A_data[jm1].im));
                                            colscale = anorm;
                                            if (scale > anorm) {
                                                colscale = scale;
                                            }
                                            if ((colscale < 1.0) && (colscale != 0.0)) {
                                                anorm /= colscale;
                                                scale /= colscale;
                                            }
                                            i = j + A_size_idx_0 * (j - 1);
                                            if ((fabs(b_A_data[i].re) +
                                                 fabs(b_A_data[i].im)) *
                                                scale <=
                                                anorm * b_atol) {
                                                goto90 = true;
                                                exitg2 = true;
                                            } else {
                                                nm1 = j;
                                                j--;
                                            }
                                        }
                                        if (!goto90) {
                                            istart = ifirst;
                                            row =
                                                    (ifirst + A_size_idx_0 * (ifirst - 1)) - 1;
                                            ctemp.re = ascale * b_A_data[row].re -
                                                       shift.re * bscale;
                                            ctemp.im = ascale * b_A_data[row].im -
                                                       shift.im * bscale;
                                        }
                                        goto90 = false;
                                        jm1 = istart + A_size_idx_0 * (istart - 1);
                                        b_ascale.re = ascale * b_A_data[jm1].re;
                                        b_ascale.im = ascale * b_A_data[jm1].im;
                                        xzlartg(ctemp, b_ascale, &anorm, &shift);
                                        j = istart;
                                        jm1 = istart - 2;
                                        while (j < ilast + 1) {
                                            if (j > istart) {
                                                xzlartg(
                                                        b_A_data[(j + A_size_idx_0 * jm1) - 1],
                                                        b_A_data[j + A_size_idx_0 * jm1],
                                                        &anorm, &shift,
                                                        &b_A_data[(j + A_size_idx_0 * jm1) -
                                                                  1]);
                                                i = j + A_size_idx_0 * jm1;
                                                b_A_data[i].re = 0.0;
                                                b_A_data[i].im = 0.0;
                                            }
                                            for (nm1 = j; nm1 <= ilastm; nm1++) {
                                                row = j + A_size_idx_0 * (nm1 - 1);
                                                ad22_re = anorm * b_A_data[row - 1].re +
                                                          (shift.re * b_A_data[row].re -
                                                           shift.im * b_A_data[row].im);
                                                ad22_im = anorm * b_A_data[row - 1].im +
                                                          (shift.re * b_A_data[row].im +
                                                           shift.im * b_A_data[row].re);
                                                scale = b_A_data[row - 1].re;
                                                b_A_data[row].re =
                                                        anorm * b_A_data[row].re -
                                                        (shift.re * b_A_data[row - 1].re +
                                                         shift.im * b_A_data[row - 1].im);
                                                b_A_data[row].im =
                                                        anorm * b_A_data[row].im -
                                                        (shift.re * b_A_data[row - 1].im -
                                                         shift.im * scale);
                                                b_A_data[row - 1].re = ad22_re;
                                                b_A_data[row - 1].im = ad22_im;
                                            }
                                            shift.re = -shift.re;
                                            shift.im = -shift.im;
                                            nm1 = j;
                                            if (ilast + 1 < j + 2) {
                                                nm1 = ilast - 1;
                                            }
                                            for (n = ifirst; n <= nm1 + 2; n++) {
                                                row = (n + A_size_idx_0 * (j - 1)) - 1;
                                                col = (n + A_size_idx_0 * j) - 1;
                                                ad22_re = anorm * b_A_data[col].re +
                                                          (shift.re * b_A_data[row].re -
                                                           shift.im * b_A_data[row].im);
                                                ad22_im = anorm * b_A_data[col].im +
                                                          (shift.re * b_A_data[row].im +
                                                           shift.im * b_A_data[row].re);
                                                scale = b_A_data[col].re;
                                                b_A_data[row].re =
                                                        anorm * b_A_data[row].re -
                                                        (shift.re * b_A_data[col].re +
                                                         shift.im * b_A_data[col].im);
                                                b_A_data[row].im =
                                                        anorm * b_A_data[row].im -
                                                        (shift.re * b_A_data[col].im -
                                                         shift.im * scale);
                                                b_A_data[col].re = ad22_re;
                                                b_A_data[col].im = ad22_im;
                                            }
                                            jm1 = j - 1;
                                            j++;
                                        }
                                    }
                                    jiter++;
                                }
                            }
                        } else {
                            guard2 = true;
                            exitg1 = 1;
                        }
                    } while (exitg1 == 0);
                } else {
                    guard1 = true;
                }
                if (guard2) {
                    if (failed) {
                        *info = ilast + 1;
                        for (jm1 = 0; jm1 <= ilast; jm1++) {
                            alpha1_data[jm1].re = rtNaN;
                            alpha1_data[jm1].im = 0.0;
                            beta1_data[jm1].re = rtNaN;
                            beta1_data[jm1].im = 0.0;
                        }
                    } else {
                        guard1 = true;
                    }
                }
                if (guard1) {
                    for (j = 0; j <= ilo - 2; j++) {
                        alpha1_data[j] = b_A_data[j + A_size_idx_0 * j];
                    }
                }
            }

//
// Arguments    : const creal_T A[36]
//                int ilo
//                int ihi
//                int *info
//                creal_T alpha1[6]
//                creal_T beta1[6]
// Return Type  : void
//
            void xzhgeqz(const creal_T A[36], int ilo, int ihi, int *info,
                         creal_T alpha1[6], creal_T beta1[6]) {
                creal_T b_A[36];
                creal_T b_ascale;
                creal_T ctemp;
                creal_T shift;
                double absxk;
                double anorm;
                double ascale;
                double b_atol;
                double colscale;
                double colssq;
                double eshift_im;
                double eshift_re;
                double ssq;
                double t;
                int col;
                int i;
                int ilast;
                int j;
                int jm1;
                int jp1;
                int nm1;
                boolean_T failed;
                boolean_T guard1 = false;
                boolean_T guard2 = false;
                memcpy(&b_A[0], &A[0], 36U * sizeof(creal_T));
                *info = 0;
                for (nm1 = 0; nm1 < 6; nm1++) {
                    alpha1[nm1].re = 0.0;
                    alpha1[nm1].im = 0.0;
                    beta1[nm1].re = 1.0;
                    beta1[nm1].im = 0.0;
                }
                eshift_re = 0.0;
                eshift_im = 0.0;
                ctemp.re = 0.0;
                ctemp.im = 0.0;
                anorm = 0.0;
                if (ilo <= ihi) {
                    anorm = 3.3121686421112381E-170;
                    ssq = 0.0;
                    nm1 = ihi - ilo;
                    for (j = 0; j <= nm1; j++) {
                        colscale = 3.3121686421112381E-170;
                        colssq = 0.0;
                        col = (ilo + j) - 1;
                        jp1 = j + 1;
                        if (jp1 >= nm1) {
                            jp1 = nm1;
                        }
                        i = ilo + jp1;
                        for (jp1 = ilo; jp1 <= i; jp1++) {
                            jm1 = (jp1 + 6 * col) - 1;
                            absxk = fabs(A[jm1].re);
                            if (absxk > colscale) {
                                t = colscale / absxk;
                                colssq = colssq * t * t + 1.0;
                                colscale = absxk;
                            } else {
                                t = absxk / colscale;
                                colssq += t * t;
                            }
                            absxk = fabs(A[jm1].im);
                            if (absxk > colscale) {
                                t = colscale / absxk;
                                colssq = colssq * t * t + 1.0;
                                colscale = absxk;
                            } else {
                                t = absxk / colscale;
                                colssq += t * t;
                            }
                        }
                        if (anorm >= colscale) {
                            ssq += rt_powd_snf(colscale / anorm, 2.0) * colssq;
                        } else {
                            ssq = colssq + rt_powd_snf(anorm / colscale, 2.0) * ssq;
                            anorm = colscale;
                        }
                    }
                    anorm *= sqrt(ssq);
                }
                ssq = 2.2204460492503131E-16 * anorm;
                b_atol = 2.2250738585072014E-308;
                if (ssq > 2.2250738585072014E-308) {
                    b_atol = ssq;
                }
                ssq = 2.2250738585072014E-308;
                if (anorm > 2.2250738585072014E-308) {
                    ssq = anorm;
                }
                ascale = 1.0 / ssq;
                failed = true;
                i = ihi + 1;
                for (j = i; j < 7; j++) {
                    alpha1[j - 1] = A[(j + 6 * (j - 1)) - 1];
                }
                guard1 = false;
                guard2 = false;
                if (ihi >= ilo) {
                    int ifirst;
                    int iiter;
                    int ilastm;
                    int ilastm1;
                    int istart;
                    int jiter;
                    boolean_T goto60;
                    boolean_T goto70;
                    boolean_T goto90;
                    ifirst = ilo;
                    istart = ilo;
                    ilast = ihi - 1;
                    ilastm1 = ihi - 2;
                    ilastm = ihi;
                    iiter = 0;
                    goto60 = false;
                    goto70 = false;
                    goto90 = false;
                    jiter = 0;
                    int exitg1;
                    do {
                        exitg1 = 0;
                        if (jiter <= 30 * ((ihi - ilo) + 1) - 1) {
                            boolean_T b_guard1 = false;
                            boolean_T exitg2;
                            b_guard1 = false;
                            if (ilast + 1 == ilo) {
                                goto60 = true;
                                b_guard1 = true;
                            } else {
                                i = ilast + 6 * ilastm1;
                                if (fabs(b_A[i].re) + fabs(b_A[i].im) <= b_atol) {
                                    b_A[i].re = 0.0;
                                    b_A[i].im = 0.0;
                                    goto60 = true;
                                    b_guard1 = true;
                                } else {
                                    boolean_T guard3 = false;
                                    j = ilastm1;
                                    guard3 = false;
                                    exitg2 = false;
                                    while ((!exitg2) && (j + 1 >= ilo)) {
                                        if (j + 1 == ilo) {
                                            guard3 = true;
                                            exitg2 = true;
                                        } else {
                                            i = j + 6 * (j - 1);
                                            if (fabs(b_A[i].re) + fabs(b_A[i].im) <=
                                                b_atol) {
                                                b_A[i].re = 0.0;
                                                b_A[i].im = 0.0;
                                                guard3 = true;
                                                exitg2 = true;
                                            } else {
                                                j--;
                                                guard3 = false;
                                            }
                                        }
                                    }
                                    if (guard3) {
                                        ifirst = j + 1;
                                        goto70 = true;
                                    }
                                    if (goto70) {
                                        b_guard1 = true;
                                    } else {
                                        for (nm1 = 0; nm1 < 6; nm1++) {
                                            alpha1[nm1].re = rtNaN;
                                            alpha1[nm1].im = 0.0;
                                            beta1[nm1].re = rtNaN;
                                            beta1[nm1].im = 0.0;
                                        }
                                        *info = 1;
                                        exitg1 = 1;
                                    }
                                }
                            }
                            if (b_guard1) {
                                if (goto60) {
                                    goto60 = false;
                                    alpha1[ilast] = b_A[ilast + 6 * ilast];
                                    ilast = ilastm1;
                                    ilastm1--;
                                    if (ilast + 1 < ilo) {
                                        failed = false;
                                        guard2 = true;
                                        exitg1 = 1;
                                    } else {
                                        iiter = 0;
                                        eshift_re = 0.0;
                                        eshift_im = 0.0;
                                        ilastm = ilast + 1;
                                        jiter++;
                                    }
                                } else {
                                    if (goto70) {
                                        double ad22_im;
                                        double ad22_re;
                                        goto70 = false;
                                        iiter++;
                                        if (iiter - iiter / 10 * 10 != 0) {
                                            double t1_im;
                                            double t1_im_tmp;
                                            double t1_re;
                                            jp1 = ilastm1 + 6 * ilastm1;
                                            anorm = ascale * b_A[jp1].re;
                                            ssq = ascale * b_A[jp1].im;
                                            if (ssq == 0.0) {
                                                shift.re = anorm / 0.40824829046386307;
                                                shift.im = 0.0;
                                            } else if (anorm == 0.0) {
                                                shift.re = 0.0;
                                                shift.im = ssq / 0.40824829046386307;
                                            } else {
                                                shift.re = anorm / 0.40824829046386307;
                                                shift.im = ssq / 0.40824829046386307;
                                            }
                                            jp1 = ilast + 6 * ilast;
                                            anorm = ascale * b_A[jp1].re;
                                            ssq = ascale * b_A[jp1].im;
                                            if (ssq == 0.0) {
                                                ad22_re = anorm / 0.40824829046386307;
                                                ad22_im = 0.0;
                                            } else if (anorm == 0.0) {
                                                ad22_re = 0.0;
                                                ad22_im = ssq / 0.40824829046386307;
                                            } else {
                                                ad22_re = anorm / 0.40824829046386307;
                                                ad22_im = ssq / 0.40824829046386307;
                                            }
                                            t1_re = 0.5 * (shift.re + ad22_re);
                                            t1_im = 0.5 * (shift.im + ad22_im);
                                            t1_im_tmp = t1_re * t1_im;
                                            jp1 = ilastm1 + 6 * ilast;
                                            anorm = ascale * b_A[jp1].re;
                                            ssq = ascale * b_A[jp1].im;
                                            if (ssq == 0.0) {
                                                absxk = anorm / 0.40824829046386307;
                                                t = 0.0;
                                            } else if (anorm == 0.0) {
                                                absxk = 0.0;
                                                t = ssq / 0.40824829046386307;
                                            } else {
                                                absxk = anorm / 0.40824829046386307;
                                                t = ssq / 0.40824829046386307;
                                            }
                                            jp1 = ilast + 6 * ilastm1;
                                            anorm = ascale * b_A[jp1].re;
                                            ssq = ascale * b_A[jp1].im;
                                            if (ssq == 0.0) {
                                                colssq = anorm / 0.40824829046386307;
                                                anorm = 0.0;
                                            } else if (anorm == 0.0) {
                                                colssq = 0.0;
                                                anorm = ssq / 0.40824829046386307;
                                            } else {
                                                colssq = anorm / 0.40824829046386307;
                                                anorm = ssq / 0.40824829046386307;
                                            }
                                            ssq = shift.re * ad22_re - shift.im * ad22_im;
                                            colscale =
                                                    shift.re * ad22_im + shift.im * ad22_re;
                                            shift.re = ((t1_re * t1_re - t1_im * t1_im) +
                                                        (absxk * colssq - t * anorm)) -
                                                       ssq;
                                            shift.im = ((t1_im_tmp + t1_im_tmp) +
                                                        (absxk * anorm + t * colssq)) -
                                                       colscale;
                                            b_sqrt(&shift);
                                            if ((t1_re - ad22_re) * shift.re +
                                                (t1_im - ad22_im) * shift.im <=
                                                0.0) {
                                                shift.re += t1_re;
                                                shift.im += t1_im;
                                            } else {
                                                shift.re = t1_re - shift.re;
                                                shift.im = t1_im - shift.im;
                                            }
                                        } else {
                                            jp1 = ilast + 6 * ilastm1;
                                            anorm = ascale * b_A[jp1].re;
                                            ssq = ascale * b_A[jp1].im;
                                            if (ssq == 0.0) {
                                                absxk = anorm / 0.40824829046386307;
                                                t = 0.0;
                                            } else if (anorm == 0.0) {
                                                absxk = 0.0;
                                                t = ssq / 0.40824829046386307;
                                            } else {
                                                absxk = anorm / 0.40824829046386307;
                                                t = ssq / 0.40824829046386307;
                                            }
                                            eshift_re += absxk;
                                            eshift_im += t;
                                            shift.re = eshift_re;
                                            shift.im = eshift_im;
                                        }
                                        j = ilastm1;
                                        jp1 = ilastm1 + 1;
                                        exitg2 = false;
                                        while ((!exitg2) && (j + 1 > ifirst)) {
                                            istart = j + 1;
                                            jm1 = j + 6 * j;
                                            ctemp.re = ascale * b_A[jm1].re -
                                                       shift.re * 0.40824829046386307;
                                            ctemp.im = ascale * b_A[jm1].im -
                                                       shift.im * 0.40824829046386307;
                                            ssq = fabs(ctemp.re) + fabs(ctemp.im);
                                            jp1 += 6 * j;
                                            anorm = ascale *
                                                    (fabs(b_A[jp1].re) + fabs(b_A[jp1].im));
                                            colscale = ssq;
                                            if (anorm > ssq) {
                                                colscale = anorm;
                                            }
                                            if ((colscale < 1.0) && (colscale != 0.0)) {
                                                ssq /= colscale;
                                                anorm /= colscale;
                                            }
                                            i = j + 6 * (j - 1);
                                            if ((fabs(b_A[i].re) + fabs(b_A[i].im)) *
                                                anorm <=
                                                ssq * b_atol) {
                                                goto90 = true;
                                                exitg2 = true;
                                            } else {
                                                jp1 = j;
                                                j--;
                                            }
                                        }
                                        if (!goto90) {
                                            istart = ifirst;
                                            jm1 = (ifirst + 6 * (ifirst - 1)) - 1;
                                            ctemp.re = ascale * b_A[jm1].re -
                                                       shift.re * 0.40824829046386307;
                                            ctemp.im = ascale * b_A[jm1].im -
                                                       shift.im * 0.40824829046386307;
                                        }
                                        goto90 = false;
                                        jp1 = istart + 6 * (istart - 1);
                                        b_ascale.re = ascale * b_A[jp1].re;
                                        b_ascale.im = ascale * b_A[jp1].im;
                                        xzlartg(ctemp, b_ascale, &anorm, &shift);
                                        j = istart;
                                        jm1 = istart - 2;
                                        while (j < ilast + 1) {
                                            if (j > istart) {
                                                nm1 = j + 6 * jm1;
                                                xzlartg(b_A[nm1 - 1], b_A[nm1], &anorm,
                                                        &shift, &b_A[(j + 6 * jm1) - 1]);
                                                b_A[nm1].re = 0.0;
                                                b_A[nm1].im = 0.0;
                                            }
                                            for (nm1 = j; nm1 <= ilastm; nm1++) {
                                                jm1 = j + 6 * (nm1 - 1);
                                                ad22_re = anorm * b_A[jm1 - 1].re +
                                                          (shift.re * b_A[jm1].re -
                                                           shift.im * b_A[jm1].im);
                                                ad22_im = anorm * b_A[jm1 - 1].im +
                                                          (shift.re * b_A[jm1].im +
                                                           shift.im * b_A[jm1].re);
                                                ssq = b_A[jm1 - 1].re;
                                                b_A[jm1].re = anorm * b_A[jm1].re -
                                                              (shift.re * b_A[jm1 - 1].re +
                                                               shift.im * b_A[jm1 - 1].im);
                                                b_A[jm1].im = anorm * b_A[jm1].im -
                                                              (shift.re * b_A[jm1 - 1].im -
                                                               shift.im * ssq);
                                                b_A[jm1 - 1].re = ad22_re;
                                                b_A[jm1 - 1].im = ad22_im;
                                            }
                                            shift.re = -shift.re;
                                            shift.im = -shift.im;
                                            col = j;
                                            if (ilast + 1 < j + 2) {
                                                col = ilast - 1;
                                            }
                                            for (nm1 = ifirst; nm1 <= col + 2; nm1++) {
                                                jm1 = (nm1 + 6 * (j - 1)) - 1;
                                                jp1 = (nm1 + 6 * j) - 1;
                                                ad22_re = anorm * b_A[jp1].re +
                                                          (shift.re * b_A[jm1].re -
                                                           shift.im * b_A[jm1].im);
                                                ad22_im = anorm * b_A[jp1].im +
                                                          (shift.re * b_A[jm1].im +
                                                           shift.im * b_A[jm1].re);
                                                ssq = b_A[jp1].re;
                                                b_A[jm1].re = anorm * b_A[jm1].re -
                                                              (shift.re * b_A[jp1].re +
                                                               shift.im * b_A[jp1].im);
                                                b_A[jm1].im = anorm * b_A[jm1].im -
                                                              (shift.re * b_A[jp1].im -
                                                               shift.im * ssq);
                                                b_A[jp1].re = ad22_re;
                                                b_A[jp1].im = ad22_im;
                                            }
                                            jm1 = j - 1;
                                            j++;
                                        }
                                    }
                                    jiter++;
                                }
                            }
                        } else {
                            guard2 = true;
                            exitg1 = 1;
                        }
                    } while (exitg1 == 0);
                } else {
                    guard1 = true;
                }
                if (guard2) {
                    if (failed) {
                        *info = ilast + 1;
                        for (jp1 = 0; jp1 <= ilast; jp1++) {
                            alpha1[jp1].re = rtNaN;
                            alpha1[jp1].im = 0.0;
                            beta1[jp1].re = rtNaN;
                            beta1[jp1].im = 0.0;
                        }
                    } else {
                        guard1 = true;
                    }
                }
                if (guard1) {
                    for (j = 0; j <= ilo - 2; j++) {
                        alpha1[j] = b_A[j + 6 * j];
                    }
                }
            }

        } // namespace reflapack
    } // namespace internal
} // namespace coder

//
// File trailer for xzhgeqz.cpp
//
// [EOF]
//
