//
// File: xzhgeqz.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef XZHGEQZ_H
#define XZHGEQZ_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    namespace internal {
        namespace reflapack {
            void xzhgeqz(const creal_T A_data[], const int A_size[2], int ilo, int ihi,
                         int *info, creal_T alpha1_data[], int *alpha1_size,
                         creal_T beta1_data[], int *beta1_size);

            void xzhgeqz(const creal_T A[36], int ilo, int ihi, int *info,
                         creal_T alpha1[6], creal_T beta1[6]);

        } // namespace reflapack
    } // namespace internal
} // namespace coder

#endif
//
// File trailer for xzhgeqz.h
//
// [EOF]
//
