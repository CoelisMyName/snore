#ifndef PERMUTE_H
#define PERMUTE_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void permute(const ::coder::array<double, 2U> &a,
             ::coder::array<double, 2U> &b);

void permute(const ::coder::array<double, 3U> &a,
             ::coder::array<double, 3U> &b);

} // namespace coder

#endif
