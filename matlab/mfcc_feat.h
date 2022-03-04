#ifndef MFCC_FEAT_H
#define MFCC_FEAT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void mfcc_feat(const coder::array<double, 1U> &sig, double fs,
                      coder::array<double, 2U> &MFCC_feature);

#endif
