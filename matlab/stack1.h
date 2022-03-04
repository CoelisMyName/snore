#ifndef STACK1_H
#define STACK1_H

#include "rtwtypes.h"
#include "coder_bounded_array.h"
#include <cstddef>
#include <cstdlib>

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
