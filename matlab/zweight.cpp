//
// File: zweight.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "zweight.h"
#include "SnoringRecognition_data.h"
#include "log10.h"
#include "octbank.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "coder_array.h"

// Function Definitions
//
// function [p, f, s] = zweight(x)
//
// Arguments    : const coder::array<double, 1U> &x
//                double p[8]
//                double f[8]
//                double *s
// Return Type  : void
//
void zweight(const coder::array<double, 1U> &x, double p[8], double f[8],
             double *s) {
    double b_dv[8];
    double b_dv1[8];
    double d;
    int i;
    for (i = 0; i < 8; i++) {
        f[i] = iv[i];
    }
    // 'zweight:2' [p, f] = octbank(x, 44100);
    octbank(x, p);
    // 'zweight:3' a = 10.^(0.1 * (p));
    // 'zweight:4' s = 10 * log10(sum(a));
    for (i = 0; i < 8; i++) {
        b_dv[i] = 0.1 * p[i];
    }
    coder::power(b_dv, b_dv1);
    d = coder::sum(b_dv1);
    coder::b_log10(&d);
    *s = 10.0 * d;
}

//
// File trailer for zweight.cpp
//
// [EOF]
//
