#ifndef HENR_H
#define HENR_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void HENR(const coder::array<double, 1U> &x, double fs, double *Eh,
          double *En_mean);

#endif
