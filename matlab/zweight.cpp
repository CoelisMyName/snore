//
// File: zweight.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "zweight.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_initialize.h"
#include "SnoringRecognition_rtwutil.h"
#include "octbank.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [p, f, s] = zweight(x)
//
// Arguments    : const coder::array<double, 2U> &x
//                double p[8]
//                double f[8]
//                double *s
// Return Type  : void
//
void zweight(const coder::array<double, 2U> &x, double p[8], double f[8],
             double *s)
{
  double a[8];
  double y;
  int k;
  if (!isInitialized_SnoringRecognition) {
    SnoringRecognition_initialize();
  }
  for (k = 0; k < 8; k++) {
    f[k] = iv[k];
  }
  // 'zweight:2' [p, f] = octbank(x, 44100);
  octbank(x, p);
  // 'zweight:3' a = 10.^(0.1 * (p));
  for (k = 0; k < 8; k++) {
    a[k] = rt_powd_snf(10.0, 0.1 * p[k]);
  }
  // 'zweight:4' s = 10 * log10(sum(a));
  y = a[0];
  for (k = 0; k < 7; k++) {
    y += a[k + 1];
  }
  *s = 10.0 * std::log10(y);
}

//
// File trailer for zweight.cpp
//
// [EOF]
//
