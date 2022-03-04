#ifndef MTIMES_H
#define MTIMES_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace blas {
void mtimes(const ::coder::array<double, 2U> &A,
            const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C);

}
} // namespace internal
} // namespace coder

#endif
