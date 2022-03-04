#ifndef HIST_H
#define HIST_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void hist(const ::coder::array<double, 1U> &Y, double no[200], double xo[200]);

}

#endif
