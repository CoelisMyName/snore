//
// File: aweight.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "aweight.h"
#include "SnoringRecognition_data.h"
#include "log10.h"
#include "octbank.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "coder_array.h"

// Function Definitions
//
// function [p, f, s] = aweight(x)
//
// Arguments    : const coder::array<double, 2U> &x
//                double p[8]
//                double f[8]
//                double *s
// Return Type  : void
//
void aweight(const coder::array<double, 2U> &x, double p[8], double f[8],
             double *s) {
    static const double weight[8] = {-26.2, -16.1, -8.6, -3.2,
                                     0.0, 1.2, 1.0, -1.1};
    double b_dv[8];
    double b_dv1[8];
    double d;
    int i;
    for (i = 0; i < 8; i++) {
        f[i] = iv[i];
    }
    // 'aweight:2' [p, f] = octbank(x, 44100);
    octbank(x, p);
    // 'aweight:3' weight = [-26.2 -16.1 -8.6 -3.2 0 1.2 1.0 -1.1];
    // 'aweight:4' p = p + weight;
    // 'aweight:5' a = 10.^(0.1 * (p));
    // 'aweight:6' s = 10 * log10(sum(a));
    for (i = 0; i < 8; i++) {
        d = p[i] + weight[i];
        p[i] = d;
        b_dv[i] = 0.1 * d;
    }
    coder::power(10.0, b_dv, b_dv1);
    d = coder::sum(b_dv1);
    coder::b_log10(&d);
    *s = 10.0 * d;
}

//
// File trailer for aweight.cpp
//
// [EOF]
//
