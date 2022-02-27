//
// File: designMelFilterBank.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef DESIGNMELFILTERBANK_H
#define DESIGNMELFILTERBANK_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
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
//
// File trailer for designMelFilterBank.h
//
// [EOF]
//
