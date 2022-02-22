//
// File: insertionsort.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
    class anonymous_function;

}

// Function Declarations
namespace coder {
    namespace internal {
        void insertionsort(::coder::array<int, 1U> &x, int xstart, int xend,
                           const anonymous_function *cmp);

    }
} // namespace coder

#endif
//
// File trailer for insertionsort.h
//
// [EOF]
//
