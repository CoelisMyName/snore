#ifndef BARKENERGY_H
#define BARKENERGY_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void BARKenergy(const coder::array<double, 1U> &x, double fs, double BPSEE1[17],
                double BPS1[17], double BPSEE2[17]);

#endif
