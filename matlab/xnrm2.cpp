//
// File: xnrm2.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "xnrm2.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : int n
//                const double x[36]
//                int ix0
// Return Type  : double
//
namespace coder {
    namespace internal {
        namespace blas {
            double xnrm2(int n, const double x[36], int ix0) {
                double y;
                y = 0.0;
                if (n >= 1) {
                    if (n == 1) {
                        y = fabs(x[ix0 - 1]);
                    } else {
                        double scale;
                        int kend;
                        scale = 3.3121686421112381E-170;
                        kend = (ix0 + n) - 1;
                        for (int k = ix0; k <= kend; k++) {
                            double absxk;
                            absxk = fabs(x[k - 1]);
                            if (absxk > scale) {
                                double t;
                                t = scale / absxk;
                                y = y * t * t + 1.0;
                                scale = absxk;
                            } else {
                                double t;
                                t = absxk / scale;
                                y += t * t;
                            }
                        }
                        y = scale * sqrt(y);
                    }
                }
                return y;
            }

//
// Arguments    : int n
//                const double x[3]
// Return Type  : double
//
            double xnrm2(int n, const double x[3]) {
                double y;
                y = 0.0;
                if (n >= 1) {
                    if (n == 1) {
                        y = fabs(x[1]);
                    } else {
                        double scale;
                        int kend;
                        scale = 3.3121686421112381E-170;
                        kend = n + 1;
                        for (int k = 2; k <= kend; k++) {
                            double absxk;
                            absxk = fabs(x[k - 1]);
                            if (absxk > scale) {
                                double t;
                                t = scale / absxk;
                                y = y * t * t + 1.0;
                                scale = absxk;
                            } else {
                                double t;
                                t = absxk / scale;
                                y += t * t;
                            }
                        }
                        y = scale * sqrt(y);
                    }
                }
                return y;
            }

        } // namespace blas
    } // namespace internal
} // namespace coder

//
// File trailer for xnrm2.cpp
//
// [EOF]
//
