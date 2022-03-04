#ifndef GENCOSWIN_H
#define GENCOSWIN_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void calc_window(double m, double n, ::coder::array<double, 1U> &w);

}

#endif
