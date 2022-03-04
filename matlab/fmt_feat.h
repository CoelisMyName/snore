#ifndef FMT_FEAT_H
#define FMT_FEAT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void fmt_feat(const coder::array<double, 1U> &sig, double fs,
                     double *Formant1, double *Formant2, double *Formant3);

#endif
