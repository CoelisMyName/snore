//
// File: xzhgeqz.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef XZHGEQZ_H
#define XZHGEQZ_H

// Include Files
#include "rtwtypes.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
void xzhgeqz(const creal_T A[36], int ilo, int ihi, int *info,
             creal_T alpha1[6], creal_T beta1[6]);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xzhgeqz.h
//
// [EOF]
//