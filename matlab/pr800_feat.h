#ifndef PR800_FEAT_H
#define PR800_FEAT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void pr800_feat(const coder::array<double, 1U> &sig, double fs,
                       double *PR800_mean, double *PR800_max, double *PR800_min,
                       double *PR800_var);

#endif
