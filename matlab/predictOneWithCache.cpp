//
// File: predictOneWithCache.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "predictOneWithCache.h"
#include "CompactClassificationTree.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &X
//                ::coder::array<double, 2U> &cachedScore
//                ::coder::array<double, 1U> &cachedWeights
//                const
//                ::coder::classreg::learning::classif::CompactClassificationTree
//                *weak_learner double learnerWeights boolean_T *cached const
//                double classnames[2] const boolean_T classlogicalindices[2]
//                const ::coder::array<boolean_T, 1U> &useObsForLearner
//                boolean_T initCache
//                ::coder::array<double, 2U> &score
// Return Type  : void
//
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
                            const boolean_T classlogicalindices[2],
                            const ::coder::array<boolean_T, 1U> &useObsForLearner, boolean_T initCache,
                            ::coder::array<double, 2U> &score) {
                        array<double, 2U> b_X;
                        array<double, 2U> b_cachedScore;
                        array<double, 2U> learnerscore;
                        array<double, 1U> a__2;
                        array<int, 1U> r;
                        array<int, 1U> r1;
                        array<int, 1U> r3;
                        array<int, 1U> r4;
                        array<int, 1U> r5;
                        array<int, 1U> r6;
                        array<boolean_T, 2U> r2;
                        array<boolean_T, 2U> tf;
                        double absx;
                        int i;
                        int ibcol;
                        int jtilecol;
                        int nrows;
                        signed char iloc[2];
                        boolean_T exitg1;
                        boolean_T y;
                        learnerscore.set_size(cachedScore.size(0), 2);
                        ibcol = cachedScore.size(0) << 1;
                        for (jtilecol = 0; jtilecol < ibcol; jtilecol++) {
                            learnerscore[jtilecol] = rtNaN;
                        }
                        iloc[0] = 0;
                        i = 0;
                        exitg1 = false;
                        while ((!exitg1) && (i < 2)) {
                            absx = fabs(classnames[i] / 2.0);
                            if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
                                if (absx <= 2.2250738585072014E-308) {
                                    absx = 4.94065645841247E-324;
                                } else {
                                    frexp(absx, &nrows);
                                    absx = ldexp(1.0, nrows - 53);
                                }
                            } else {
                                absx = rtNaN;
                            }
                            if ((fabs(classnames[i] - weak_learner->ClassNames[0]) < absx) ||
                                (rtIsInf(weak_learner->ClassNames[0]) && rtIsInf(classnames[i]) &&
                                 ((weak_learner->ClassNames[0] > 0.0) == (classnames[i] > 0.0)))) {
                                iloc[0] = static_cast<signed char>(i + 1);
                                exitg1 = true;
                            } else {
                                i++;
                            }
                        }
                        iloc[1] = 0;
                        i = 0;
                        exitg1 = false;
                        while ((!exitg1) && (i < 2)) {
                            absx = fabs(classnames[i] / 2.0);
                            if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
                                if (absx <= 2.2250738585072014E-308) {
                                    absx = 4.94065645841247E-324;
                                } else {
                                    frexp(absx, &nrows);
                                    absx = ldexp(1.0, nrows - 53);
                                }
                            } else {
                                absx = rtNaN;
                            }
                            if ((fabs(classnames[i] - weak_learner->ClassNames[1]) < absx) ||
                                (rtIsInf(weak_learner->ClassNames[1]) && rtIsInf(classnames[i]) &&
                                 ((weak_learner->ClassNames[1] > 0.0) == (classnames[i] > 0.0)))) {
                                iloc[1] = static_cast<signed char>(i + 1);
                                exitg1 = true;
                            } else {
                                i++;
                            }
                        }
                        y = false;
                        nrows = 1;
                        exitg1 = false;
                        while ((!exitg1) && (nrows <= useObsForLearner.size(0))) {
                            if (!useObsForLearner[nrows - 1]) {
                                nrows++;
                            } else {
                                y = true;
                                exitg1 = true;
                            }
                        }
                        if (y) {
                            ibcol = useObsForLearner.size(0) - 1;
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    nrows++;
                                }
                            }
                            r.set_size(nrows);
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    r[nrows] = i + 1;
                                    nrows++;
                                }
                            }
                            b_X.set_size(r.size(0), 23);
                            ibcol = r.size(0);
                            for (jtilecol = 0; jtilecol < 23; jtilecol++) {
                                for (nrows = 0; nrows < ibcol; nrows++) {
                                    b_X[nrows + b_X.size(0) * jtilecol] =
                                            X[(r[nrows] + X.size(0) * jtilecol) - 1];
                                }
                            }
                            weak_learner->predict(b_X, a__2, b_cachedScore);
                            ibcol = useObsForLearner.size(0) - 1;
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    nrows++;
                                }
                            }
                            r3.set_size(nrows);
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    r3[nrows] = i + 1;
                                    nrows++;
                                }
                            }
                            ibcol = b_cachedScore.size(0);
                            for (jtilecol = 0; jtilecol < 2; jtilecol++) {
                                for (nrows = 0; nrows < ibcol; nrows++) {
                                    learnerscore[(r3[nrows] + learnerscore.size(0) * (iloc[jtilecol] - 1)) -
                                                 1] =
                                            b_cachedScore[nrows + b_cachedScore.size(0) * jtilecol];
                                }
                            }
                        }
                        if (initCache) {
                            ibcol = useObsForLearner.size(0) - 1;
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    nrows++;
                                }
                            }
                            r1.set_size(nrows);
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    r1[nrows] = i + 1;
                                    nrows++;
                                }
                            }
                            ibcol = r1.size(0);
                            for (jtilecol = 0; jtilecol < 2; jtilecol++) {
                                for (nrows = 0; nrows < ibcol; nrows++) {
                                    cachedScore[(r1[nrows] + cachedScore.size(0) * jtilecol) - 1] = 0.0;
                                }
                            }
                        } else {
                            tf.set_size(cachedScore.size(0), 2);
                            ibcol = cachedScore.size(0) * 2;
                            for (jtilecol = 0; jtilecol < ibcol; jtilecol++) {
                                tf[jtilecol] = rtIsNaN(cachedScore[jtilecol]);
                            }
                            y = false;
                            nrows = 1;
                            exitg1 = false;
                            while ((!exitg1) && (nrows <= (tf.size(0) << 1))) {
                                if (!tf[nrows - 1]) {
                                    nrows++;
                                } else {
                                    y = true;
                                    exitg1 = true;
                                }
                            }
                            if (y) {
                                r2.set_size(useObsForLearner.size(0), 2);
                                nrows = useObsForLearner.size(0);
                                for (jtilecol = 0; jtilecol < 2; jtilecol++) {
                                    ibcol = jtilecol * nrows;
                                    for (i = 0; i < nrows; i++) {
                                        r2[ibcol + i] = useObsForLearner[i];
                                    }
                                }
                                ibcol = (tf.size(0) << 1) - 1;
                                nrows = 0;
                                for (i = 0; i <= ibcol; i++) {
                                    if (tf[i] && r2[i]) {
                                        nrows++;
                                    }
                                }
                                r1.set_size(nrows);
                                nrows = 0;
                                for (i = 0; i <= ibcol; i++) {
                                    if (tf[i] && r2[i]) {
                                        r1[nrows] = i + 1;
                                        nrows++;
                                    }
                                }
                                ibcol = r1.size(0);
                                for (jtilecol = 0; jtilecol < ibcol; jtilecol++) {
                                    cachedScore[r1[jtilecol] - 1] = 0.0;
                                }
                            }
                        }
                        score.set_size(cachedScore.size(0), 2);
                        ibcol = cachedScore.size(0) * 2;
                        for (jtilecol = 0; jtilecol < ibcol; jtilecol++) {
                            score[jtilecol] = cachedScore[jtilecol];
                        }
                        if ((!*cached) && (!(learnerWeights <= 0.0))) {
                            *cached = true;
                            ibcol = useObsForLearner.size(0) - 1;
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    nrows++;
                                }
                            }
                            r4.set_size(nrows);
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    r4[nrows] = i + 1;
                                    nrows++;
                                }
                            }
                            ibcol = useObsForLearner.size(0) - 1;
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    nrows++;
                                }
                            }
                            r5.set_size(nrows);
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    r5[nrows] = i + 1;
                                    nrows++;
                                }
                            }
                            b_cachedScore.set_size(r5.size(0), 2);
                            ibcol = r5.size(0);
                            for (jtilecol = 0; jtilecol < 2; jtilecol++) {
                                for (nrows = 0; nrows < ibcol; nrows++) {
                                    b_cachedScore[nrows + b_cachedScore.size(0) * jtilecol] =
                                            cachedScore[(r5[nrows] + cachedScore.size(0) * jtilecol) - 1] +
                                            learnerscore[(r4[nrows] + learnerscore.size(0) * jtilecol) - 1] *
                                            learnerWeights;
                                }
                            }
                            ibcol = b_cachedScore.size(0);
                            for (jtilecol = 0; jtilecol < 2; jtilecol++) {
                                for (nrows = 0; nrows < ibcol; nrows++) {
                                    cachedScore[(r5[nrows] + cachedScore.size(0) * jtilecol) - 1] =
                                            b_cachedScore[nrows + b_cachedScore.size(0) * jtilecol];
                                }
                            }
                            ibcol = useObsForLearner.size(0) - 1;
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    nrows++;
                                }
                            }
                            r6.set_size(nrows);
                            nrows = 0;
                            for (i = 0; i <= ibcol; i++) {
                                if (useObsForLearner[i]) {
                                    r6[nrows] = i + 1;
                                    nrows++;
                                }
                            }
                            a__2.set_size(r6.size(0));
                            ibcol = r6.size(0);
                            for (jtilecol = 0; jtilecol < ibcol; jtilecol++) {
                                a__2[jtilecol] = cachedWeights[r6[jtilecol] - 1] + learnerWeights;
                            }
                            ibcol = a__2.size(0);
                            for (jtilecol = 0; jtilecol < ibcol; jtilecol++) {
                                cachedWeights[r6[jtilecol] - 1] = a__2[jtilecol];
                            }
                            jtilecol = cachedScore.size(0);
                            for (i = 0; i < jtilecol; i++) {
                                score[i] = cachedScore[i];
                                score[i + score.size(0)] = cachedScore[i + cachedScore.size(0)];
                            }
                        }
                        for (nrows = 0; nrows < 2; nrows++) {
                            if (!classlogicalindices[nrows]) {
                                ibcol = score.size(0);
                                for (jtilecol = 0; jtilecol < ibcol; jtilecol++) {
                                    score[jtilecol + score.size(0) * nrows] = rtNaN;
                                }
                            }
                        }
                    }

                } // namespace ensembleutils
            } // namespace coder
        } // namespace learning
    } // namespace classreg
} // namespace coder

//
// File trailer for predictOneWithCache.cpp
//
// [EOF]
//
