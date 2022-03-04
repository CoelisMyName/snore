#ifndef GMM_SCORE_H
#define GMM_SCORE_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

struct SnoringRecognitionStackData;

double GMM_score(SnoringRecognitionStackData *SD,
                 const coder::array<double, 2U> &data_test);

#endif
