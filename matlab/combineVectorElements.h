#ifndef COMBINEVECTORELEMENTS_H
#define COMBINEVECTORELEMENTS_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void combineVectorElements(const ::coder::array<double, 2U> &x, double y[17]);

void combineVectorElements(const ::coder::array<double, 2U> &x,
                           ::coder::array<double, 2U> &y);

} // namespace coder

#endif
