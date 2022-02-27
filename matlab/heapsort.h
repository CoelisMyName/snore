//
// File: heapsort.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef HEAPSORT_H
#define HEAPSORT_H

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
        void b_heapsort(::coder::array<int, 1U> &x, int xstart, int xend,
                        const anonymous_function *cmp);

    }
} // namespace coder

#endif
//
// File trailer for heapsort.h
//
// [EOF]
//
