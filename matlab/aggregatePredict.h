//
// File: aggregatePredict.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef AGGREGATEPREDICT_H
#define AGGREGATEPREDICT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
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
//
// File trailer for aggregatePredict.h
//
// [EOF]
//
