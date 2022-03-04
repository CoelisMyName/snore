#ifndef GETCANDIDATES_H
#define GETCANDIDATES_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace audio {
namespace internal {
namespace pitch {
void getCandidates(::coder::array<double, 2U> &domain, const double edge[2],
                   ::coder::array<double, 1U> &peaks,
                   ::coder::array<double, 1U> &locs);

}
} // namespace internal
} // namespace audio
} // namespace coder

#endif
