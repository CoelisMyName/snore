//
// File: aweight.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "aweight.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_initialize.h"
#include "SnoringRecognition_rtwutil.h"
#include "octbank.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

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
             double *s)
{
  static const double weight[8]{-26.2, -16.1, -8.6, -3.2, 0.0, 1.2, 1.0, -1.1};
  double a[8];
  double y;
  int k;
  if (!isInitialized_SnoringRecognition) {
    SnoringRecognition_initialize();
  }
  for (k = 0; k < 8; k++) {
    f[k] = iv[k];
  }
  // 'aweight:2' [p, f] = octbank(x, 44100);
  octbank(x, p);
  // 'aweight:3' weight = [-26.2 -16.1 -8.6 -3.2 0 1.2 1.0 -1.1];
  // 'aweight:4' p = p + weight;
  // 'aweight:5' a = 10.^(0.1 * (p));
  for (k = 0; k < 8; k++) {
    y = p[k] + weight[k];
    p[k] = y;
    a[k] = rt_powd_snf(10.0, 0.1 * y);
  }
  // 'aweight:6' s = 10 * log10(sum(a));
  y = a[0];
  for (k = 0; k < 7; k++) {
    y += a[k + 1];
  }
  *s = 10.0 * std::log10(y);
}

//
// File trailer for aweight.cpp
//
// [EOF]
//
