//
// File: NCF.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef NCF_H
#define NCF_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
    namespace audio {
        namespace internal {
            class pitchValidator;

        }
    } // namespace audio
} // namespace coder

// Function Declarations
namespace coder {
    namespace audio {
        namespace internal {
            namespace pitch {
                void NCF(const ::coder::array<double, 2U> &y, const pitchValidator params,
                         ::coder::array<double, 1U> &f0);

            }
        } // namespace internal
    } // namespace audio
} // namespace coder

#endif
//
// File trailer for NCF.h
//
// [EOF]
//
