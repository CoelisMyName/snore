#ifndef PREDICTONEWITHCACHE_H
#define PREDICTONEWITHCACHE_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace classreg {
namespace learning {
namespace classif {
class CompactClassificationTree;

}
} // namespace learning
} // namespace classreg
} // namespace coder

namespace coder {
namespace classreg {
namespace learning {
namespace coder {
namespace ensembleutils {
void predictOneWithCache(
    const ::coder::array<double, 2U> &X,
    ::coder::array<double, 2U> &cachedScore,
    ::coder::array<double, 1U> &cachedWeights,
    const ::coder::classreg::learning::classif::CompactClassificationTree
        *weak_learner,
    double learnerWeights, boolean_T *cached, const double classnames[2],
    const ::coder::array<boolean_T, 1U> &useObsForLearner, boolean_T initCache,
    ::coder::array<double, 2U> &score);

}
} // namespace coder
} // namespace learning
} // namespace classreg
} // namespace coder

#endif
