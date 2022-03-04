#ifndef SPARSE_H
#define SPARSE_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
class sparse;

}

namespace coder {
void b_sparse(const ::coder::array<double, 2U> &varargin_1,
              const ::coder::array<double, 2U> &varargin_2,
              const ::coder::array<double, 2U> &varargin_3, double varargin_5,
              sparse *y);

}

#endif
