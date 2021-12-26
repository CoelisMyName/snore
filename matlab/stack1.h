//
// File: stack1.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef STACK1_H
#define STACK1_H

// Include Files
#include "rtwtypes.h"
#include "coder_bounded_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct struct_T {
  int xstart;
  int xend;
  int depth;
};

namespace coder {
namespace internal {
class stack {
public:
  bounded_array<struct_T, 120U, 1U> d;
  int n;
};

} // namespace internal
} // namespace coder

#endif
//
// File trailer for stack1.h
//
// [EOF]
//
