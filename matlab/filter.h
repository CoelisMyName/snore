#ifndef FILTER_H
#define FILTER_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void filter(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);

void filter(double b[3], double a[3], const ::coder::array<double, 1U> &x,
            const double zi[2], ::coder::array<double, 1U> &y, double zf[2]);

} // namespace coder

#endif
