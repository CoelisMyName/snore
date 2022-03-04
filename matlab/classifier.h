#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void classifier(const coder::array<double, 1U> &x, double fs,
                       const coder::array<long long, 1U> &w_starts,
                       const coder::array<long long, 1U> &w_ends,
                       coder::array<double, 1U> &predict_label);

#endif
