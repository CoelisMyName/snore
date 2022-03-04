#ifndef XHSEQR_H
#define XHSEQR_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace lapack {
int xhseqr(double h[36]);

}
} // namespace internal
} // namespace coder

#endif
