#ifndef REPMAT_H
#define REPMAT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void repmat(const double a[4160], const double varargin_1[3],
            ::coder::array<double, 3U> &b);

}

#endif
