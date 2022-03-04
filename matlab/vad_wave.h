#ifndef VAD_WAVE_H
#define VAD_WAVE_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

void vad_wave(const coder::array<double, 1U> &array,
              const coder::array<long long, 1U> &starts,
              const coder::array<long long, 1U> &ends,
              coder::array<long long, 1U> &ostarts,
              coder::array<long long, 1U> &oends);

#endif
