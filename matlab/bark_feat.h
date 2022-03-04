#ifndef BARK_FEAT_H
#define BARK_FEAT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void bark_feat(const coder::array<double, 1U> &sig, double fs,
                      double barkee[17]);

#endif
