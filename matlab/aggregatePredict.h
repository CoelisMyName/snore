#ifndef AGGREGATEPREDICT_H
#define AGGREGATEPREDICT_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace classreg {
namespace learning {
namespace coder {
namespace ensembleutils {
void aggregatePredict(const ::coder::array<double, 2U> &X,
                      ::coder::array<double, 2U> &score,
                      const double learnerWeights[400],
                      const boolean_T isCached[400], const double classNames[2],
                      const boolean_T learners[400],
                      const ::coder::array<boolean_T, 2U> &useObsForLearner);

}
} // namespace coder
} // namespace learning
} // namespace classreg
} // namespace coder

#endif
