#ifndef SPARSE1_H
#define SPARSE1_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
class sparse {
  public:
    array<double, 1U> d;
    array<int, 1U> colidx;
    array<int, 1U> rowidx;
    int n;
};

} // namespace coder

#endif
