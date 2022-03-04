#ifndef PR800_H
#define PR800_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void PR800(const coder::array<double, 1U> &x, double Fs, double *PR800_mean,
           double *PR800_max, double *PR800_min, double *PR800_var);

#endif
