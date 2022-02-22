//
// File: zp2ss.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "zp2ss.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : double a[9]
//                double b[3]
//                double c[3]
//                double *d
// Return Type  : void
//
namespace coder {
    void zp2ss(double a[9], double b[3], double c[3], double *d) {
        static const creal_T b_dcv[3] = {{
                                                 -0.49999999999999978, // re
                                                 -0.86602540378443871  // im
                                         },
                                         {
                                                 -0.49999999999999978, // re
                                                 0.86602540378443871   // im
                                         },
                                         {
                                                 -1.0, // re
                                                 0.0   // im
                                         }};
        creal_T b_c[3];
        creal_T x[2];
        double Y[4];
        double a1[4];
        double b_d;
        double d1;
        double re;
        int j;
        memset(&a[0], 0, 9U * sizeof(double));
        a[0] = -1.0;
        b[0] = 1.0;
        *d = 0.0;
        b_c[0].re = 1.0;
        b_c[0].im = 0.0;
        for (j = 0; j < 2; j++) {
            double im;
            x[j] = b_dcv[j];
            re = -b_dcv[j].re;
            im = -b_dcv[j].im;
            b_d = b_c[j].im;
            d1 = b_c[j].re;
            b_c[j + 1].re = re * d1 - im * b_d;
            b_c[j + 1].im = re * b_d + im * d1;
            for (int k = j + 1; k >= 2; k--) {
                b_d = x[j].re;
                d1 = x[j].im;
                b_c[1].re -= b_d * b_c[0].re - d1 * b_c[0].im;
                b_c[1].im -= b_d * b_c[0].im + d1 * b_c[0].re;
            }
        }
        re = 1.0 / sqrt(rt_hypotd_snf(b_dcv[0].re, b_dcv[0].im) *
                        rt_hypotd_snf(b_dcv[1].re, b_dcv[1].im));
        b_d = (1.0 - -b_c[1].re * 0.0) / re;
        Y[1] = b_d;
        Y[0] = -b_c[1].re - b_d * 0.0;
        b_d = (0.0 - -b_c[2].re * 0.0) / re;
        Y[3] = b_d;
        Y[2] = -b_c[2].re - b_d * 0.0;
        for (j = 0; j < 2; j++) {
            b_d = Y[j + 2];
            d1 = Y[j];
            a1[j] = d1 + b_d * 0.0;
            a1[j + 2] = d1 * 0.0 + b_d * re;
        }
        a[4] = a1[0];
        a[5] = a1[1];
        a[7] = a1[2];
        a[8] = a1[3];
        c[0] = 0.0;
        a[2] = 0.0;
        a[1] = 1.0;
        b[1] = 0.0;
        b[2] = 0.0;
        c[0] *= 0.99999999999999989;
        c[1] = 0.0;
        c[2] = re * 0.99999999999999989;
    }

} // namespace coder

//
// File trailer for zp2ss.cpp
//
// [EOF]
//
