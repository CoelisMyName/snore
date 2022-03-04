#ifndef CEP_FEAT_H
#define CEP_FEAT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void cep_feat(const coder::array<double, 1U> &sig, double fs,
                     double cep_data[], int cep_size[2]);

#endif
