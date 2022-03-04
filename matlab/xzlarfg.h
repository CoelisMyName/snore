#ifndef XZLARFG_H
#define XZLARFG_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace reflapack {
double xzlarfg(int n, double *alpha1, double x[3]);

}
} // namespace internal
} // namespace coder

#endif
