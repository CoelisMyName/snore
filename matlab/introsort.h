#ifndef INTROSORT_H
#define INTROSORT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
class anonymous_function;

}

namespace coder {
namespace internal {
void introsort(::coder::array<int, 1U> &x, int xend,
               const anonymous_function *cmp);

}
} // namespace coder

#endif
