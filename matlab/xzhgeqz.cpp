//
// File: xzhgeqz.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "xzhgeqz.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "xzlanhs.h"
#include "xzlartg.h"
#include "rtGetNaN.h"
#include <algorithm>
#include <cmath>

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
             creal_T alpha1[6], creal_T beta1[6])
{
  static creal_T dc{
      0.0, // re
      0.0  // im
  };
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
  boolean_T guard1{false};
  boolean_T guard2{false};
  dc.re = rtGetNaN();
  std::copy(&A[0], &A[36], &b_A[0]);
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
  if (static_cast<int>(6 - ihi < 1200)) {
    for (j = i; j < 7; j++) {
      alpha1[j - 1] = A[(j + 6 * (j - 1)) - 1];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(j)

    for (j = i; j < 7; j++) {
      alpha1[j - 1] = A[(j + 6 * (j - 1)) - 1];
    }
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
        int b_j;
        boolean_T b_guard1{false};
        boolean_T exitg2;
        b_guard1 = false;
        if (ilast + 1 == ilo) {
          goto60 = true;
          b_guard1 = true;
        } else {
          i = ilast + 6 * ilastm1;
          if (std::abs(b_A[i].re) + std::abs(b_A[i].im) <= b_atol) {
            b_A[i].re = 0.0;
            b_A[i].im = 0.0;
            goto60 = true;
            b_guard1 = true;
          } else {
            boolean_T guard3{false};
            b_j = ilastm1;
            guard3 = false;
            exitg2 = false;
            while ((!exitg2) && (b_j + 1 >= ilo)) {
              if (b_j + 1 == ilo) {
                guard3 = true;
                exitg2 = true;
              } else {
                i = b_j + 6 * (b_j - 1);
                if (std::abs(b_A[i].re) + std::abs(b_A[i].im) <= b_atol) {
                  b_A[i].re = 0.0;
                  b_A[i].im = 0.0;
                  guard3 = true;
                  exitg2 = true;
                } else {
                  b_j--;
                  guard3 = false;
                }
              }
            }
            if (guard3) {
              ifirst = b_j + 1;
              goto70 = true;
            }
            if (goto70) {
              b_guard1 = true;
            } else {
              for (i = 0; i < 6; i++) {
                alpha1[i] = dc;
                beta1[i] = dc;
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
              double ad22_im;
              double ad22_re;
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
                  ad22_re = anorm / 0.40824829046386307;
                  ad22_im = 0.0;
                } else if (anorm == 0.0) {
                  ad22_re = 0.0;
                  ad22_im = yi / 0.40824829046386307;
                } else {
                  ad22_re = anorm / 0.40824829046386307;
                  ad22_im = yi / 0.40824829046386307;
                }
                t1_re = 0.5 * (shift.re + ad22_re);
                t1_im = 0.5 * (shift.im + ad22_im);
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
                yi = shift.re * ad22_re - shift.im * ad22_im;
                absxr = shift.re * ad22_im + shift.im * ad22_re;
                shift.re = ((t1_re * t1_re - t1_im * t1_im) +
                            (ascale_re * b_ascale_re - ascale_im * anorm)) -
                           yi;
                shift.im = ((t1_im_tmp + t1_im_tmp) +
                            (ascale_re * anorm + ascale_im * b_ascale_re)) -
                           absxr;
                if (shift.im == 0.0) {
                  if (shift.re < 0.0) {
                    anorm = 0.0;
                    yi = std::sqrt(-shift.re);
                  } else {
                    anorm = std::sqrt(shift.re);
                    yi = 0.0;
                  }
                } else if (shift.re == 0.0) {
                  if (shift.im < 0.0) {
                    anorm = std::sqrt(-shift.im / 2.0);
                    yi = -anorm;
                  } else {
                    anorm = std::sqrt(shift.im / 2.0);
                    yi = anorm;
                  }
                } else if (std::isnan(shift.re)) {
                  anorm = shift.re;
                  yi = shift.re;
                } else if (std::isnan(shift.im)) {
                  anorm = shift.im;
                  yi = shift.im;
                } else if (std::isinf(shift.im)) {
                  anorm = std::abs(shift.im);
                  yi = shift.im;
                } else if (std::isinf(shift.re)) {
                  if (shift.re < 0.0) {
                    anorm = 0.0;
                    yi = shift.im * -shift.re;
                  } else {
                    anorm = shift.re;
                    yi = 0.0;
                  }
                } else {
                  absxr = std::abs(shift.re);
                  anorm = std::abs(shift.im);
                  if ((absxr > 4.4942328371557893E+307) ||
                      (anorm > 4.4942328371557893E+307)) {
                    absxr *= 0.5;
                    anorm = rt_hypotd_snf(absxr, anorm * 0.5);
                    if (anorm > absxr) {
                      anorm = std::sqrt(anorm) * std::sqrt(absxr / anorm + 1.0);
                    } else {
                      anorm = std::sqrt(anorm) * 1.4142135623730951;
                    }
                  } else {
                    anorm =
                        std::sqrt((rt_hypotd_snf(absxr, anorm) + absxr) * 0.5);
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
                if ((t1_re - ad22_re) * anorm + (t1_im - ad22_im) * yi <= 0.0) {
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
              b_j = ilastm1;
              i = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (b_j + 1 > ifirst)) {
                istart = b_j + 1;
                ctemp_tmp = b_j + 6 * b_j;
                ctemp.re =
                    ascale * b_A[ctemp_tmp].re - shift.re * 0.40824829046386307;
                ctemp.im =
                    ascale * b_A[ctemp_tmp].im - shift.im * 0.40824829046386307;
                yi = std::abs(ctemp.re) + std::abs(ctemp.im);
                i += 6 * b_j;
                anorm = ascale * (std::abs(b_A[i].re) + std::abs(b_A[i].im));
                absxr = yi;
                if (anorm > yi) {
                  absxr = anorm;
                }
                if ((absxr < 1.0) && (absxr != 0.0)) {
                  yi /= absxr;
                  anorm /= absxr;
                }
                i = b_j + 6 * (b_j - 1);
                if ((std::abs(b_A[i].re) + std::abs(b_A[i].im)) * anorm <=
                    yi * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  i = b_j;
                  b_j--;
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
              b_j = istart;
              i = istart - 2;
              while (b_j < ilast + 1) {
                int shift_re_tmp;
                if (b_j > istart) {
                  ctemp_tmp = b_j + 6 * i;
                  xzlartg(b_A[ctemp_tmp - 1], b_A[ctemp_tmp], &anorm, &shift,
                          &b_A[(b_j + 6 * i) - 1]);
                  b_A[ctemp_tmp].re = 0.0;
                  b_A[ctemp_tmp].im = 0.0;
                }
                for (i = b_j; i <= ilastm; i++) {
                  shift_re_tmp = b_j + 6 * (i - 1);
                  ad22_re = anorm * b_A[shift_re_tmp - 1].re +
                            (shift.re * b_A[shift_re_tmp].re -
                             shift.im * b_A[shift_re_tmp].im);
                  ad22_im = anorm * b_A[shift_re_tmp - 1].im +
                            (shift.re * b_A[shift_re_tmp].im +
                             shift.im * b_A[shift_re_tmp].re);
                  yi = b_A[shift_re_tmp - 1].re;
                  b_A[shift_re_tmp].re = anorm * b_A[shift_re_tmp].re -
                                         (shift.re * b_A[shift_re_tmp - 1].re +
                                          shift.im * b_A[shift_re_tmp - 1].im);
                  b_A[shift_re_tmp].im =
                      anorm * b_A[shift_re_tmp].im -
                      (shift.re * b_A[shift_re_tmp - 1].im - shift.im * yi);
                  b_A[shift_re_tmp - 1].re = ad22_re;
                  b_A[shift_re_tmp - 1].im = ad22_im;
                }
                shift.re = -shift.re;
                shift.im = -shift.im;
                ctemp_tmp = b_j;
                if (ilast + 1 < b_j + 2) {
                  ctemp_tmp = ilast - 1;
                }
                for (i = ifirst; i <= ctemp_tmp + 2; i++) {
                  int ad22_re_tmp;
                  shift_re_tmp = (i + 6 * (b_j - 1)) - 1;
                  ad22_re_tmp = (i + 6 * b_j) - 1;
                  ad22_re = anorm * b_A[ad22_re_tmp].re +
                            (shift.re * b_A[shift_re_tmp].re -
                             shift.im * b_A[shift_re_tmp].im);
                  ad22_im = anorm * b_A[ad22_re_tmp].im +
                            (shift.re * b_A[shift_re_tmp].im +
                             shift.im * b_A[shift_re_tmp].re);
                  yi = b_A[ad22_re_tmp].re;
                  b_A[shift_re_tmp].re = anorm * b_A[shift_re_tmp].re -
                                         (shift.re * b_A[ad22_re_tmp].re +
                                          shift.im * b_A[ad22_re_tmp].im);
                  b_A[shift_re_tmp].im =
                      anorm * b_A[shift_re_tmp].im -
                      (shift.re * b_A[ad22_re_tmp].im - shift.im * yi);
                  b_A[ad22_re_tmp].re = ad22_re;
                  b_A[ad22_re_tmp].im = ad22_im;
                }
                i = b_j - 1;
                b_j++;
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
      if (static_cast<int>(ilast + 1 < 1200)) {
        for (j = 0; j <= ilast; j++) {
          alpha1[j] = dc;
          beta1[j] = dc;
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(j)

        for (j = 0; j <= ilast; j++) {
          alpha1[j] = dc;
          beta1[j] = dc;
        }
      }
    } else {
      guard1 = true;
    }
  }
  if (guard1) {
    if (static_cast<int>(ilo - 1 < 1200)) {
      for (j = 0; j <= ilo - 2; j++) {
        alpha1[j] = b_A[j + 6 * j];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(j)

      for (j = 0; j <= ilo - 2; j++) {
        alpha1[j] = b_A[j + 6 * j];
      }
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
