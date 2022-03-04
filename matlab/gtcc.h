#ifndef GTCC_H
#define GTCC_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

struct SnoringRecognitionStackData;

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
