//
// File: gtcc.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef GTCC_H
#define GTCC_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct SnoringRecognitionStackData;

// Function Declarations
namespace coder {
    void b_gtcc(const ::coder::array<double, 1U> &audioIn,
                ::coder::array<double, 2U> &coeffs,
                ::coder::array<double, 2U> &delta,
                ::coder::array<double, 2U> &deltaDelta,
                ::coder::array<double, 1U> &ts);

    void b_gtcc(SnoringRecognitionStackData *SD,
                const ::coder::array<double, 1U> &audioIn,
                ::coder::array<double, 2U> &coeffs,
                ::coder::array<double, 2U> &delta,
                ::coder::array<double, 2U> &deltaDelta,
                ::coder::array<double, 1U> &ts);

    void c_gtcc(const ::coder::array<double, 1U> &audioIn,
                ::coder::array<double, 2U> &coeffs,
                ::coder::array<double, 2U> &delta,
                ::coder::array<double, 2U> &deltaDelta,
                ::coder::array<double, 1U> &ts);

    void c_gtcc(SnoringRecognitionStackData *SD,
                const ::coder::array<double, 1U> &audioIn,
                ::coder::array<double, 2U> &coeffs,
                ::coder::array<double, 2U> &delta,
                ::coder::array<double, 2U> &deltaDelta,
                ::coder::array<double, 1U> &ts);

    void d_gtcc(SnoringRecognitionStackData *SD,
                const ::coder::array<double, 1U> &audioIn,
                ::coder::array<double, 2U> &coeffs,
                ::coder::array<double, 2U> &delta,
                ::coder::array<double, 2U> &deltaDelta,
                ::coder::array<double, 1U> &ts);

    void gtcc(const ::coder::array<double, 1U> &audioIn,
              ::coder::array<double, 2U> &coeffs, ::coder::array<double, 2U> &delta,
              ::coder::array<double, 2U> &deltaDelta,
              ::coder::array<double, 1U> &ts);

    void gtcc(SnoringRecognitionStackData *SD,
              const ::coder::array<double, 1U> &audioIn,
              ::coder::array<double, 2U> &coeffs, ::coder::array<double, 2U> &delta,
              ::coder::array<double, 2U> &deltaDelta,
              ::coder::array<double, 1U> &ts);

} // namespace coder

#endif
//
// File trailer for gtcc.h
//
// [EOF]
//
