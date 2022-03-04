#ifndef DESIGNMELFILTERBANK_H
#define DESIGNMELFILTERBANK_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace audio {
namespace internal {
void designMelFilterBank(double fs, const double bandEdges_data[],
                         const int bandEdges_size[2], double NFFT,
                         ::coder::array<double, 2U> &filterBank);

}
} // namespace audio
} // namespace coder

#endif
