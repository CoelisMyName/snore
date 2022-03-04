#ifndef XDLANV2_H
#define XDLANV2_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace reflapack {
void xdlanv2(double *a, double *b, double *c, double *d, double *rt1r,
             double *rt1i, double *rt2r, double *rt2i, double *cs, double *sn);

}
} // namespace internal
} // namespace coder

#endif
