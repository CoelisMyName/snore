#ifndef ANONYMOUS_FUNCTION_H
#define ANONYMOUS_FUNCTION_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

struct c_struct_T {
    coder::array<int, 1U> a;
    coder::array<int, 1U> b;
};

namespace coder {
class anonymous_function {
  public:
    c_struct_T workspace;
};

} // namespace coder

#endif
