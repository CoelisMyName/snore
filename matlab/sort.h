//
// File: sort.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef SORT_H
#define SORT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    namespace internal {
        void sort(::coder::array<double, 2U> &x, ::coder::array<int, 2U> &idx);

        void sort(::coder::array<double, 2U> &x);

        void sort(double x[200]);

        void sort(::coder::array<double, 1U> &x);

        void sort(double x_data[], int x_size[2]);

    } // namespace internal
} // namespace coder

#endif
//
// File trailer for sort.h
//
// [EOF]
//
