#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
class anonymous_function;

}

namespace coder {
namespace internal {
void b_heapsort(::coder::array<int, 1U> &x, int xstart, int xend,
                const anonymous_function *cmp);

}
} // namespace coder

#endif
