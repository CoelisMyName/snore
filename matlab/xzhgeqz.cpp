//
// File: xzhgeqz.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "xzhgeqz.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "xzlanhs.h"
#include "xzlartg.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const creal_T A[36]
//                int ilo
//                int ihi
//                int *info
//                creal_T alpha1[6]
//                creal_T beta1[6]
// Return Type  : void
//
namespace coder {
    namespace internal {
        namespace reflapack {
            void xzhgeqz(const creal_T A[36], int ilo, int ihi, int *info,
                         creal_T alpha1[6], creal_T beta1[6]) {
                creal_T b_A[36];
                creal_T b_ascale;
                creal_T ctemp;
                creal_T shift;
                double anorm;
                double ascale;
                double b_atol;
                double eshift_im;
                double eshift_re;
                double yi;
                int i;
                int ilast;
                int j;
                boolean_T failed;
                boolean_T guard1 = false;
                boolean_T guard2 = false;
                memcpy(&b_A[0], &A[0], 36U * sizeof(creal_T));
                *info = 0;
                for (i = 0; i < 6; i++) {
                    alpha1[i].re = 0.0;
                    alpha1[i].im = 0.0;
                    beta1[i].re = 1.0;
                    beta1[i].im = 0.0;
                }
                eshift_re = 0.0;
                eshift_im = 0.0;
                ctemp.re = 0.0;
                ctemp.im = 0.0;
                anorm = xzlanhs(A, ilo, ihi);
                yi = 2.2204460492503131E-16 * anorm;
                b_atol = 2.2250738585072014E-308;
                if (yi > 2.2250738585072014E-308) {
                    b_atol = yi;
                }
                yi = 2.2250738585072014E-308;
                if (anorm > 2.2250738585072014E-308) {
                    yi = anorm;
                }
                ascale = 1.0 / yi;
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
                                            if (fabs(b_A[i].re) + fabs(b_A[i].im) <= b_atol) {
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
                                        for (i = 0; i < 6; i++) {
                                            alpha1[i].re = rtNaN;
                                            alpha1[i].im = 0.0;
                                            beta1[i].re = rtNaN;
                                            beta1[i].im = 0.0;
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
                                        double absxr;
                                        double stemp_im;
                                        double stemp_re;
                                        int ctemp_tmp;
                                        goto70 = false;
                                        iiter++;
                                        if (iiter - iiter / 10 * 10 != 0) {
                                            double ascale_im;
                                            double ascale_re;
                                            double b_ascale_re;
                                            double t1_im;
                                            double t1_im_tmp;
                                            double t1_re;
                                            i = ilastm1 + 6 * ilastm1;
                                            anorm = ascale * b_A[i].re;
                                            yi = ascale * b_A[i].im;
                                            if (yi == 0.0) {
                                                shift.re = anorm / 0.40824829046386307;
                                                shift.im = 0.0;
                                            } else if (anorm == 0.0) {
                                                shift.re = 0.0;
                                                shift.im = yi / 0.40824829046386307;
                                            } else {
                                                shift.re = anorm / 0.40824829046386307;
                                                shift.im = yi / 0.40824829046386307;
                                            }
                                            i = ilast + 6 * ilast;
                                            anorm = ascale * b_A[i].re;
                                            yi = ascale * b_A[i].im;
                                            if (yi == 0.0) {
                                                stemp_re = anorm / 0.40824829046386307;
                                                stemp_im = 0.0;
                                            } else if (anorm == 0.0) {
                                                stemp_re = 0.0;
                                                stemp_im = yi / 0.40824829046386307;
                                            } else {
                                                stemp_re = anorm / 0.40824829046386307;
                                                stemp_im = yi / 0.40824829046386307;
                                            }
                                            t1_re = 0.5 * (shift.re + stemp_re);
                                            t1_im = 0.5 * (shift.im + stemp_im);
                                            t1_im_tmp = t1_re * t1_im;
                                            i = ilastm1 + 6 * ilast;
                                            anorm = ascale * b_A[i].re;
                                            yi = ascale * b_A[i].im;
                                            if (yi == 0.0) {
                                                ascale_re = anorm / 0.40824829046386307;
                                                ascale_im = 0.0;
                                            } else if (anorm == 0.0) {
                                                ascale_re = 0.0;
                                                ascale_im = yi / 0.40824829046386307;
                                            } else {
                                                ascale_re = anorm / 0.40824829046386307;
                                                ascale_im = yi / 0.40824829046386307;
                                            }
                                            i = ilast + 6 * ilastm1;
                                            anorm = ascale * b_A[i].re;
                                            yi = ascale * b_A[i].im;
                                            if (yi == 0.0) {
                                                b_ascale_re = anorm / 0.40824829046386307;
                                                anorm = 0.0;
                                            } else if (anorm == 0.0) {
                                                b_ascale_re = 0.0;
                                                anorm = yi / 0.40824829046386307;
                                            } else {
                                                b_ascale_re = anorm / 0.40824829046386307;
                                                anorm = yi / 0.40824829046386307;
                                            }
                                            yi = shift.re * stemp_re - shift.im * stemp_im;
                                            absxr = shift.re * stemp_im + shift.im * stemp_re;
                                            shift.re = ((t1_re * t1_re - t1_im * t1_im) +
                                                        (ascale_re * b_ascale_re - ascale_im * anorm)) -
                                                       yi;
                                            shift.im = ((t1_im_tmp + t1_im_tmp) +
                                                        (ascale_re * anorm + ascale_im * b_ascale_re)) -
                                                       absxr;
                                            if (shift.im == 0.0) {
                                                if (shift.re < 0.0) {
                                                    anorm = 0.0;
                                                    yi = sqrt(-shift.re);
                                                } else {
                                                    anorm = sqrt(shift.re);
                                                    yi = 0.0;
                                                }
                                            } else if (shift.re == 0.0) {
                                                if (shift.im < 0.0) {
                                                    anorm = sqrt(-shift.im / 2.0);
                                                    yi = -anorm;
                                                } else {
                                                    anorm = sqrt(shift.im / 2.0);
                                                    yi = anorm;
                                                }
                                            } else if (rtIsNaN(shift.re)) {
                                                anorm = shift.re;
                                                yi = shift.re;
                                            } else if (rtIsNaN(shift.im)) {
                                                anorm = shift.im;
                                                yi = shift.im;
                                            } else if (rtIsInf(shift.im)) {
                                                anorm = fabs(shift.im);
                                                yi = shift.im;
                                            } else if (rtIsInf(shift.re)) {
                                                if (shift.re < 0.0) {
                                                    anorm = 0.0;
                                                    yi = shift.im * -shift.re;
                                                } else {
                                                    anorm = shift.re;
                                                    yi = 0.0;
                                                }
                                            } else {
                                                absxr = fabs(shift.re);
                                                anorm = fabs(shift.im);
                                                if ((absxr > 4.4942328371557893E+307) ||
                                                    (anorm > 4.4942328371557893E+307)) {
                                                    absxr *= 0.5;
                                                    anorm = rt_hypotd_snf(absxr, anorm * 0.5);
                                                    if (anorm > absxr) {
                                                        anorm = sqrt(anorm) * sqrt(absxr / anorm + 1.0);
                                                    } else {
                                                        anorm = sqrt(anorm) * 1.4142135623730951;
                                                    }
                                                } else {
                                                    anorm = sqrt((rt_hypotd_snf(absxr, anorm) + absxr) * 0.5);
                                                }
                                                if (shift.re > 0.0) {
                                                    yi = 0.5 * (shift.im / anorm);
                                                } else {
                                                    if (shift.im < 0.0) {
                                                        yi = -anorm;
                                                    } else {
                                                        yi = anorm;
                                                    }
                                                    anorm = 0.5 * (shift.im / yi);
                                                }
                                            }
                                            if ((t1_re - stemp_re) * anorm + (t1_im - stemp_im) * yi <=
                                                0.0) {
                                                shift.re = t1_re + anorm;
                                                shift.im = t1_im + yi;
                                            } else {
                                                shift.re = t1_re - anorm;
                                                shift.im = t1_im - yi;
                                            }
                                        } else {
                                            double ascale_im;
                                            double ascale_re;
                                            i = ilast + 6 * ilastm1;
                                            anorm = ascale * b_A[i].re;
                                            yi = ascale * b_A[i].im;
                                            if (yi == 0.0) {
                                                ascale_re = anorm / 0.40824829046386307;
                                                ascale_im = 0.0;
                                            } else if (anorm == 0.0) {
                                                ascale_re = 0.0;
                                                ascale_im = yi / 0.40824829046386307;
                                            } else {
                                                ascale_re = anorm / 0.40824829046386307;
                                                ascale_im = yi / 0.40824829046386307;
                                            }
                                            eshift_re += ascale_re;
                                            eshift_im += ascale_im;
                                            shift.re = eshift_re;
                                            shift.im = eshift_im;
                                        }
                                        j = ilastm1;
                                        i = ilastm1 + 1;
                                        exitg2 = false;
                                        while ((!exitg2) && (j + 1 > ifirst)) {
                                            istart = j + 1;
                                            ctemp_tmp = j + 6 * j;
                                            ctemp.re =
                                                    ascale * b_A[ctemp_tmp].re - shift.re * 0.40824829046386307;
                                            ctemp.im =
                                                    ascale * b_A[ctemp_tmp].im - shift.im * 0.40824829046386307;
                                            yi = fabs(ctemp.re) + fabs(ctemp.im);
                                            i += 6 * j;
                                            anorm = ascale * (fabs(b_A[i].re) + fabs(b_A[i].im));
                                            absxr = yi;
                                            if (anorm > yi) {
                                                absxr = anorm;
                                            }
                                            if ((absxr < 1.0) && (absxr != 0.0)) {
                                                yi /= absxr;
                                                anorm /= absxr;
                                            }
                                            i = j + 6 * (j - 1);
                                            if ((fabs(b_A[i].re) + fabs(b_A[i].im)) * anorm <=
                                                yi * b_atol) {
                                                goto90 = true;
                                                exitg2 = true;
                                            } else {
                                                i = j;
                                                j--;
                                            }
                                        }
                                        if (!goto90) {
                                            istart = ifirst;
                                            ctemp_tmp = (ifirst + 6 * (ifirst - 1)) - 1;
                                            ctemp.re =
                                                    ascale * b_A[ctemp_tmp].re - shift.re * 0.40824829046386307;
                                            ctemp.im =
                                                    ascale * b_A[ctemp_tmp].im - shift.im * 0.40824829046386307;
                                        }
                                        goto90 = false;
                                        i = istart + 6 * (istart - 1);
                                        b_ascale.re = ascale * b_A[i].re;
                                        b_ascale.im = ascale * b_A[i].im;
                                        xzlartg(ctemp, b_ascale, &anorm, &shift);
                                        j = istart;
                                        i = istart - 2;
                                        while (j < ilast + 1) {
                                            int shift_re_tmp;
                                            if (j > istart) {
                                                ctemp_tmp = j + 6 * i;
                                                xzlartg(b_A[ctemp_tmp - 1], b_A[ctemp_tmp], &anorm, &shift,
                                                        &b_A[(j + 6 * i) - 1]);
                                                b_A[ctemp_tmp].re = 0.0;
                                                b_A[ctemp_tmp].im = 0.0;
                                            }
                                            for (i = j; i <= ilastm; i++) {
                                                shift_re_tmp = j + 6 * (i - 1);
                                                stemp_re = anorm * b_A[shift_re_tmp - 1].re +
                                                           (shift.re * b_A[shift_re_tmp].re -
                                                            shift.im * b_A[shift_re_tmp].im);
                                                stemp_im = anorm * b_A[shift_re_tmp - 1].im +
                                                           (shift.re * b_A[shift_re_tmp].im +
                                                            shift.im * b_A[shift_re_tmp].re);
                                                yi = b_A[shift_re_tmp - 1].re;
                                                b_A[shift_re_tmp].re = anorm * b_A[shift_re_tmp].re -
                                                                       (shift.re * b_A[shift_re_tmp - 1].re +
                                                                        shift.im * b_A[shift_re_tmp - 1].im);
                                                b_A[shift_re_tmp].im =
                                                        anorm * b_A[shift_re_tmp].im -
                                                        (shift.re * b_A[shift_re_tmp - 1].im - shift.im * yi);
                                                b_A[shift_re_tmp - 1].re = stemp_re;
                                                b_A[shift_re_tmp - 1].im = stemp_im;
                                            }
                                            shift.re = -shift.re;
                                            shift.im = -shift.im;
                                            ctemp_tmp = j;
                                            if (ilast + 1 < j + 2) {
                                                ctemp_tmp = ilast - 1;
                                            }
                                            for (i = ifirst; i <= ctemp_tmp + 2; i++) {
                                                int stemp_re_tmp;
                                                shift_re_tmp = (i + 6 * (j - 1)) - 1;
                                                stemp_re_tmp = (i + 6 * j) - 1;
                                                stemp_re = anorm * b_A[stemp_re_tmp].re +
                                                           (shift.re * b_A[shift_re_tmp].re -
                                                            shift.im * b_A[shift_re_tmp].im);
                                                stemp_im = anorm * b_A[stemp_re_tmp].im +
                                                           (shift.re * b_A[shift_re_tmp].im +
                                                            shift.im * b_A[shift_re_tmp].re);
                                                yi = b_A[stemp_re_tmp].re;
                                                b_A[shift_re_tmp].re = anorm * b_A[shift_re_tmp].re -
                                                                       (shift.re * b_A[stemp_re_tmp].re +
                                                                        shift.im * b_A[stemp_re_tmp].im);
                                                b_A[shift_re_tmp].im =
                                                        anorm * b_A[shift_re_tmp].im -
                                                        (shift.re * b_A[stemp_re_tmp].im - shift.im * yi);
                                                b_A[stemp_re_tmp].re = stemp_re;
                                                b_A[stemp_re_tmp].im = stemp_im;
                                            }
                                            i = j - 1;
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
                        for (i = 0; i <= ilast; i++) {
                            alpha1[i].re = rtNaN;
                            alpha1[i].im = 0.0;
                            beta1[i].re = rtNaN;
                            beta1[i].im = 0.0;
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
