//
// File: CompactClassificationEnsemble.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef COMPACTCLASSIFICATIONENSEMBLE_H
#define COMPACTCLASSIFICATIONENSEMBLE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
    namespace classreg {
        namespace learning {
            namespace coderutils {
                enum Transform {
                    Logit = 0, // Default value
                    Doublelogit,
                    Invlogit,
                    Ismax,
                    Sign,
                    Symmetric,
                    Symmetricismax,
                    Symmetriclogit,
                    Identity
                };

            }
            namespace classif {
                class CompactClassificationEnsemble {
                public:
                    void init();

                    void predict(const ::coder::array<double, 2U> &Xin,
                                 ::coder::array<double, 1U> &labels) const;

                    boolean_T IsCached[400];
                    double LearnerWeights[400];
                    double ClassNames[2];
                    int ClassNamesLength[2];
                    coderutils::Transform ScoreTransform;
                    double Prior[2];
                    boolean_T ClassLogicalIndices[2];
                    double Cost[4];
                };

            } // namespace classif
        } // namespace learning
    } // namespace classreg
} // namespace coder

#endif
//
// File trailer for CompactClassificationEnsemble.h
//
// [EOF]
//
