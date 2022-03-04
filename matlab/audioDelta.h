#ifndef AUDIODELTA_H
#define AUDIODELTA_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void audioDelta(const ::coder::array<double, 2U> &x,
                ::coder::array<double, 2U> &delta);

}

#endif
