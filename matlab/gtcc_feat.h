#ifndef GTCC_FEAT_H
#define GTCC_FEAT_H

#include "SnoringRecognition_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

extern void gtcc_feat(SnoringRecognitionStackData *SD,
                      const coder::array<double, 1U> &sig, double fs,
                      coder::array<double, 2U> &GTCCmean);

#endif
