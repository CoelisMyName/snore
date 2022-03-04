#ifndef LPCFEATURE_H
#define LPCFEATURE_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void LPCFeature(const coder::array<double, 1U> &x, double Fs,
                coder::array<double, 2U> &LPC, double LPC_mean[12],
                double LPC_max[12], double LPC_min[12], double LPC_var[12]);

#endif
