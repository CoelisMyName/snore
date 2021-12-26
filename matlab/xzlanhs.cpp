//
// File: xzlanhs.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "xzlanhs.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const creal_T A[36]
//                int ilo
//                int ihi
// Return Type  : double
//
namespace coder {
namespace internal {
namespace reflapack {
double xzlanhs(const creal_T A[36], int ilo, int ihi)
{
  double f;
  f = 0.0;
  if (ilo <= ihi) {
    double scale;
    double ssq;
    int nm1;
    scale = 3.3121686421112381E-170;
    ssq = 0.0;
    nm1 = ihi - ilo;
    for (int j{0}; j <= nm1; j++) {
      double colscale;
      double colssq;
      int col;
      int u0;
      colscale = 3.3121686421112381E-170;
      colssq = 0.0;
      col = (ilo + j) - 1;
      u0 = j + 1;
      if (u0 >= nm1) {
        u0 = nm1;
      }
      u0 += ilo;
      for (int row{ilo}; row <= u0; row++) {
        double absxk;
        double t;
        int re_tmp;
        re_tmp = (row + 6 * col) - 1;
        absxk = std::abs(A[re_tmp].re);
        if (absxk > colscale) {
          t = colscale / absxk;
          colssq = colssq * t * t + 1.0;
          colscale = absxk;
        } else {
          t = absxk / colscale;
          colssq += t * t;
        }
        absxk = std::abs(A[re_tmp].im);
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
        ssq += rt_powd_snf(colscale / scale, 2.0) * colssq;
      } else {
        ssq = colssq + rt_powd_snf(scale / colscale, 2.0) * ssq;
        scale = colscale;
      }
    }
    f = scale * std::sqrt(ssq);
  }
  return f;
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzlanhs.cpp
//
// [EOF]
//
