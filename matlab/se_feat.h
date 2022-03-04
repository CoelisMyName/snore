#ifndef SE_FEAT_H
#define SE_FEAT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void se_feat(const coder::array<double, 1U> &sig, double fs,
                    double *SE_mean, double *SE_max, double *SE_min,
                    double *SE_var);

#endif
