//
// File: mtimes.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef MTIMES_H
#define MTIMES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    namespace internal {
        namespace blas {
            void mtimes(const ::coder::array<double, 2U> &A,
                        const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C);

            void mtimes(const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C);

            void mtimes(const ::coder::array<double, 2U> &A,
                        const ::coder::array<double, 2U> &B, double C_data[], int *C_size);

        } // namespace blas
    } // namespace internal
} // namespace coder

#endif
//
// File trailer for mtimes.h
//
// [EOF]
//
