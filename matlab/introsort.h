//
// File: introsort.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef INTROSORT_H
#define INTROSORT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class anonymous_function;

}

// Function Declarations
namespace coder {
namespace internal {
void introsort(::coder::array<int, 1U> &x, int xend,
               const anonymous_function *cmp);

}
} // namespace coder

#endif
//
// File trailer for introsort.h
//
// [EOF]
//
