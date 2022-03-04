#ifndef LPC2SPEC_H
#define LPC2SPEC_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void lpc2spec(const coder::array<double, 2U> &lpcas, double nout,
              coder::array<double, 2U> &features, coder::array<double, 2U> &F,
              coder::array<double, 2U> &M);

#endif
