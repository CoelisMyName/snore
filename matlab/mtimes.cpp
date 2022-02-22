//
// File: mtimes.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 1U> &C
// Return Type  : void
//
namespace coder {
    namespace internal {
        namespace blas {
            void mtimes(const ::coder::array<double, 2U> &A,
                        const ::coder::array<double, 2U> &B, ::coder::array<double, 1U> &C) {
                int i;
                int inner;
                int mc;
                mc = A.size(0) - 1;
                inner = A.size(1);
                C.set_size(A.size(0));
                for (i = 0; i <= mc; i++) {
                    C[i] = 0.0;
                }
                for (int k = 0; k < inner; k++) {
                    int aoffset;
                    aoffset = k * A.size(0);
                    for (i = 0; i <= mc; i++) {
                        C[i] = C[i] + A[aoffset + i] * B[k];
                    }
                }
            }

        } // namespace blas
    } // namespace internal
} // namespace coder

//
// File trailer for mtimes.cpp
//
// [EOF]
//
