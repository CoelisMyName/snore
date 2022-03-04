#ifndef AWEIGHT_H
#define AWEIGHT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void aweight(const coder::array<double, 1U> &x, double p[8], double f[8],
                    double *s);

#endif
