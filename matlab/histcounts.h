#ifndef HISTCOUNTS_H
#define HISTCOUNTS_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void histcounts(const ::coder::array<double, 1U> &x, double n_data[],
                int n_size[2], double edges_data[], int edges_size[2]);

}

#endif
