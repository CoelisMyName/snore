#ifndef XNRM2_H
#define XNRM2_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace blas {
double b_xnrm2(int n, const double x_data[], int ix0);

double xnrm2(int n, const creal_T x_data[], int ix0);

double xnrm2(int n, const double x[36], int ix0);

double xnrm2(int n, const double x[3]);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
