//
// File: levinson.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "levinson.h"
#include "SnoringRecognition_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 1U> &R
//                ::coder::array<creal_T, 2U> &A
//                ::coder::array<double, 2U> &E
// Return Type  : void
//
namespace coder {
    void levinson(const ::coder::array<creal_T, 1U> &R,
                  ::coder::array<creal_T, 2U> &A, ::coder::array<double, 2U> &E) {
        array<creal_T, 2U> temp_a;
        array<creal_T, 2U> temp_auf;
        array<creal_T, 1U> temp_A;
        array<creal_T, 1U> temp_r;
        array<signed char, 1U> r;
        int N;
        N = 12;
        if ((12 == R.size(0)) || (12 > R.size(0))) {
            N = R.size(0) - 1;
        }
        if (N == 0) {
            E.set_size(1, 1);
            E[0] = R[0].re;
            A.set_size(1, 1);
            A[0].re = 1.0;
            A[0].im = 0.0;
        } else if (R.size(0) == 1) {
            A.set_size(1, 1);
            A[0].re = 1.0;
            A[0].im = 0.0;
            E.set_size(1, 1);
            E[0] = R[0].re;
        } else {
            double temp_J_im;
            double temp_J_re;
            int idx;
            int j;
            int loop_ub;
            temp_a.set_size(1, N);
            temp_A.set_size(N);
            temp_auf.set_size(1, N);
            for (j = 0; j < N; j++) {
                temp_a[j].re = 0.0;
                temp_a[j].im = 0.0;
                temp_A[j].re = 0.0;
                temp_A[j].im = 0.0;
                temp_auf[j].re = 0.0;
                temp_auf[j].im = 0.0;
            }
            if (2 > N + 1) {
                j = 0;
                idx = -1;
            } else {
                j = 1;
                idx = N;
            }
            loop_ub = idx - j;
            temp_r.set_size(loop_ub + 1);
            for (idx = 0; idx <= loop_ub; idx++) {
                temp_r[idx] = R[j + idx];
            }
            temp_a[0].re = -R[0].re;
            temp_a[0].im = -R[0].im;
            temp_J_re = R[0].re;
            temp_J_im = 0.0;
            for (int l = 0; l < N; l++) {
                double ar;
                double im;
                double re;
                double s;
                double temp_kprod_im;
                double temp_kprod_re;
                temp_kprod_re = 0.0;
                temp_kprod_im = 0.0;
                for (j = 0; j < l; j++) {
                    temp_auf[j] = temp_a[j];
                    loop_ub = (l - j) - 1;
                    temp_kprod_re += temp_a[j].re * temp_r[loop_ub].re -
                                     temp_a[j].im * temp_r[loop_ub].im;
                    temp_kprod_im += temp_a[j].re * temp_r[loop_ub].im +
                                     temp_a[j].im * temp_r[loop_ub].re;
                }
                ar = -(temp_r[l].re + temp_kprod_re);
                im = -(temp_r[l].im + temp_kprod_im);
                if (temp_J_im == 0.0) {
                    if (im == 0.0) {
                        re = ar / temp_J_re;
                        im = 0.0;
                    } else if (ar == 0.0) {
                        re = 0.0;
                        im /= temp_J_re;
                    } else {
                        re = ar / temp_J_re;
                        im /= temp_J_re;
                    }
                } else if (temp_J_re == 0.0) {
                    if (ar == 0.0) {
                        re = im / temp_J_im;
                        im = 0.0;
                    } else if (im == 0.0) {
                        re = 0.0;
                        im = -(ar / temp_J_im);
                    } else {
                        re = im / temp_J_im;
                        im = -(ar / temp_J_im);
                    }
                } else {
                    temp_kprod_im = fabs(temp_J_re);
                    temp_kprod_re = fabs(temp_J_im);
                    if (temp_kprod_im > temp_kprod_re) {
                        s = temp_J_im / temp_J_re;
                        temp_kprod_re = temp_J_re + s * temp_J_im;
                        re = (ar + s * im) / temp_kprod_re;
                        im = (im - s * ar) / temp_kprod_re;
                    } else if (temp_kprod_re == temp_kprod_im) {
                        if (temp_J_re > 0.0) {
                            temp_kprod_re = 0.5;
                        } else {
                            temp_kprod_re = -0.5;
                        }
                        if (temp_J_im > 0.0) {
                            s = 0.5;
                        } else {
                            s = -0.5;
                        }
                        re = (ar * temp_kprod_re + im * s) / temp_kprod_im;
                        im = (im * temp_kprod_re - ar * s) / temp_kprod_im;
                    } else {
                        s = temp_J_re / temp_J_im;
                        temp_kprod_re = temp_J_im + s * temp_J_re;
                        re = (s * ar + im) / temp_kprod_re;
                        im = (s * im - ar) / temp_kprod_re;
                    }
                }
                temp_kprod_re = re * re - im * -im;
                temp_kprod_im = re * -im + im * re;
                s = (1.0 - temp_kprod_re) * temp_J_re - (0.0 - temp_kprod_im) * temp_J_im;
                temp_J_im =
                        (1.0 - temp_kprod_re) * temp_J_im + (0.0 - temp_kprod_im) * temp_J_re;
                temp_J_re = s;
                for (idx = 0; idx < l; idx++) {
                    loop_ub = (l - idx) - 1;
                    temp_kprod_re = temp_auf[loop_ub].re;
                    s = -temp_auf[loop_ub].im;
                    temp_a[idx].re = temp_auf[idx].re + (re * temp_kprod_re - im * s);
                    temp_a[idx].im = temp_auf[idx].im + (re * s + im * temp_kprod_re);
                }
                temp_a[l].re = re;
                temp_a[l].im = im;
            }
            r.set_size(static_cast<signed char>(N - 1) + 1);
            loop_ub = static_cast<signed char>(N - 1);
            for (j = 0; j <= loop_ub; j++) {
                r[j] = static_cast<signed char>(j);
            }
            loop_ub = r.size(0);
            for (j = 0; j < loop_ub; j++) {
                temp_A[static_cast<int>(r[j])] = temp_a[j];
            }
            if (1 > temp_A.size(0)) {
                loop_ub = 0;
            } else {
                loop_ub = temp_A.size(0);
            }
            A.set_size(1, loop_ub + 1);
            A[0].re = 1.0;
            A[0].im = 0.0;
            for (j = 0; j < loop_ub; j++) {
                A[A.size(0) * (j + 1)] = temp_A[j];
            }
            E.set_size(1, 1);
            E[0] = temp_J_re;
        }
    }

} // namespace coder

//
// File trailer for levinson.cpp
//
// [EOF]
//
