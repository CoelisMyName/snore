#ifndef VAR_H
#define VAR_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void var(const ::coder::array<double, 2U> &x, double y_data[], int y_size[2]);

}

#endif
