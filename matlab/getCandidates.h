//
// File: getCandidates.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef GETCANDIDATES_H
#define GETCANDIDATES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    namespace audio {
        namespace internal {
            namespace pitch {
                void getCandidates(::coder::array<double, 2U> &domain, const double edge[2],
                                   double peakDistance, ::coder::array<double, 1U> &peaks,
                                   ::coder::array<double, 1U> &locs);

            }
        } // namespace internal
    } // namespace audio
} // namespace coder

#endif
//
// File trailer for getCandidates.h
//
// [EOF]
//
