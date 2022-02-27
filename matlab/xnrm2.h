//
// File: xnrm2.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef XNRM2_H
#define XNRM2_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    namespace internal {
        namespace blas {
            double b_xnrm2(int n, const double x_data[], int ix0);

            double xnrm2(int n, const creal_T x_data[], int ix0);

            double xnrm2(int n, const double x[36], int ix0);

            double xnrm2(int n, const double x[3]);

        } // namespace blas
    } // namespace internal
} // namespace coder

#endif
//
// File trailer for xnrm2.h
//
// [EOF]
//
