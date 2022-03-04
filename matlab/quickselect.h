#ifndef QUICKSELECT_H
#define QUICKSELECT_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
void quickselect(double v[10], int n, int vlen, double *vn, int *nfirst,
                 int *nlast);

}
} // namespace coder

#endif
