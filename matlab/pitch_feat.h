#ifndef PITCH_FEAT_H
#define PITCH_FEAT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void pitch_feat(const coder::array<double, 1U> &sig, double fs,
                       double *period_mean, double *period_max,
                       double *period_min, double *period_var);

#endif
