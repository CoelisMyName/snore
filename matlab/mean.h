#ifndef MEAN_H
#define MEAN_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void mean(const ::coder::array<double, 2U> &x, double y_data[], int *y_size);

double mean(const ::coder::array<double, 2U> &x);

} // namespace coder

#endif
