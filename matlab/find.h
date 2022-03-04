#ifndef FIND_H
#define FIND_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void eml_find(const ::coder::array<boolean_T, 2U> &x, int i_data[],
              int i_size[2]);

}

#endif
