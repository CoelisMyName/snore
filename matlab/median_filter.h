#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void median_filter(const coder::array<double, 1U> &array,
                   coder::array<double, 1U> &output);

#endif
