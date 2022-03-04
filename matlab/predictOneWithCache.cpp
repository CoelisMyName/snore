#include "predictOneWithCache.h"
#include "CompactClassificationTree.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

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
    ::coder::array<double, 2U> &score)
{
    array<double, 2U> b_X;
    array<double, 2U> b_cachedScore;
    array<double, 2U> learnerscore;
    array<double, 1U> a__2;
    array<int, 1U> r;
    array<int, 1U> r1;
    array<int, 1U> r2;
    array<int, 1U> r3;
    array<int, 1U> r4;
    array<int, 1U> r5;
    array<boolean_T, 2U> tf;
    double absx;
    int b_i;
    int exponent;
    int i;
    int ix;
    signed char iloc[2];
    boolean_T exitg1;
    boolean_T y;
    learnerscore.set_size(cachedScore.size(0), 2);
    ix = cachedScore.size(0) << 1;
    for (i = 0; i < ix; i++) {
        learnerscore[i] = rtNaN;
    }
    iloc[0] = 0;
    b_i = 0;
    exitg1 = false;
    while ((!exitg1) && (b_i < 2)) {
        absx = fabs(classnames[b_i] / 2.0);
        if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
            if (absx <= 2.2250738585072014E-308) {
                absx = 4.94065645841247E-324;
            } else {
                frexp(absx, &exponent);
                absx = ldexp(1.0, exponent - 53);
            }
        } else {
            absx = rtNaN;
        }
        if ((fabs(classnames[b_i] - weak_learner->ClassNames[0]) < absx) ||
            (rtIsInf(weak_learner->ClassNames[0]) && rtIsInf(classnames[b_i]) &&
             ((weak_learner->ClassNames[0] > 0.0) ==
              (classnames[b_i] > 0.0)))) {
            iloc[0] = static_cast<signed char>(b_i + 1);
            exitg1 = true;
        } else {
            b_i++;
        }
    }
    iloc[1] = 0;
    b_i = 0;
    exitg1 = false;
    while ((!exitg1) && (b_i < 2)) {
        absx = fabs(classnames[b_i] / 2.0);
        if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
            if (absx <= 2.2250738585072014E-308) {
                absx = 4.94065645841247E-324;
            } else {
                frexp(absx, &exponent);
                absx = ldexp(1.0, exponent - 53);
            }
        } else {
            absx = rtNaN;
        }
        if ((fabs(classnames[b_i] - weak_learner->ClassNames[1]) < absx) ||
            (rtIsInf(weak_learner->ClassNames[1]) && rtIsInf(classnames[b_i]) &&
             ((weak_learner->ClassNames[1] > 0.0) ==
              (classnames[b_i] > 0.0)))) {
            iloc[1] = static_cast<signed char>(b_i + 1);
            exitg1 = true;
        } else {
            b_i++;
        }
    }
    y = false;
    ix = 1;
    exitg1 = false;
    while ((!exitg1) && (ix <= useObsForLearner.size(0))) {
        if (!useObsForLearner[ix - 1]) {
            ix++;
        } else {
            y = true;
            exitg1 = true;
        }
    }
    if (y) {
        exponent = useObsForLearner.size(0) - 1;
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                ix++;
            }
        }
        r.set_size(ix);
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                r[ix] = b_i + 1;
                ix++;
            }
        }
        b_X.set_size(r.size(0), 23);
        ix = r.size(0);
        for (i = 0; i < 23; i++) {
            for (exponent = 0; exponent < ix; exponent++) {
                b_X[exponent + b_X.size(0) * i] =
                    X[(r[exponent] + X.size(0) * i) - 1];
            }
        }
        weak_learner->predict(b_X, a__2, b_cachedScore);
        exponent = useObsForLearner.size(0) - 1;
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                ix++;
            }
        }
        r2.set_size(ix);
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                r2[ix] = b_i + 1;
                ix++;
            }
        }
        ix = b_cachedScore.size(0);
        for (i = 0; i < 2; i++) {
            for (exponent = 0; exponent < ix; exponent++) {
                learnerscore[(r2[exponent] +
                              learnerscore.size(0) * (iloc[i] - 1)) -
                             1] =
                    b_cachedScore[exponent + b_cachedScore.size(0) * i];
            }
        }
    }
    if (initCache) {
        exponent = useObsForLearner.size(0) - 1;
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                ix++;
            }
        }
        r1.set_size(ix);
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                r1[ix] = b_i + 1;
                ix++;
            }
        }
        ix = r1.size(0);
        for (i = 0; i < 2; i++) {
            for (exponent = 0; exponent < ix; exponent++) {
                cachedScore[(r1[exponent] + cachedScore.size(0) * i) - 1] = 0.0;
            }
        }
    } else {
        tf.set_size(cachedScore.size(0), 2);
        ix = cachedScore.size(0) * 2;
        for (i = 0; i < ix; i++) {
            tf[i] = rtIsNaN(cachedScore[i]);
        }
        y = false;
        ix = 1;
        exitg1 = false;
        while ((!exitg1) && (ix <= (tf.size(0) << 1))) {
            if (!tf[ix - 1]) {
                ix++;
            } else {
                y = true;
                exitg1 = true;
            }
        }
        if (y) {
            exponent = (tf.size(0) << 1) - 1;
            ix = 0;
            for (b_i = 0; b_i <= exponent; b_i++) {
                if (tf[b_i]) {
                    ix++;
                }
            }
            r1.set_size(ix);
            ix = 0;
            for (b_i = 0; b_i <= exponent; b_i++) {
                if (tf[b_i]) {
                    r1[ix] = b_i + 1;
                    ix++;
                }
            }
            ix = r1.size(0);
            for (i = 0; i < ix; i++) {
                cachedScore[r1[i] - 1] = 0.0;
            }
        }
    }
    score.set_size(cachedScore.size(0), 2);
    ix = cachedScore.size(0) * 2;
    for (i = 0; i < ix; i++) {
        score[i] = cachedScore[i];
    }
    if (!*cached) {
        *cached = true;
        exponent = useObsForLearner.size(0) - 1;
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                ix++;
            }
        }
        r3.set_size(ix);
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                r3[ix] = b_i + 1;
                ix++;
            }
        }
        exponent = useObsForLearner.size(0) - 1;
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                ix++;
            }
        }
        r4.set_size(ix);
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                r4[ix] = b_i + 1;
                ix++;
            }
        }
        b_cachedScore.set_size(r4.size(0), 2);
        ix = r4.size(0);
        for (i = 0; i < 2; i++) {
            for (exponent = 0; exponent < ix; exponent++) {
                b_cachedScore[exponent + b_cachedScore.size(0) * i] =
                    cachedScore[(r4[exponent] + cachedScore.size(0) * i) - 1] +
                    learnerscore[(r3[exponent] + learnerscore.size(0) * i) -
                                 1] *
                        learnerWeights;
            }
        }
        ix = b_cachedScore.size(0);
        for (i = 0; i < 2; i++) {
            for (exponent = 0; exponent < ix; exponent++) {
                cachedScore[(r4[exponent] + cachedScore.size(0) * i) - 1] =
                    b_cachedScore[exponent + b_cachedScore.size(0) * i];
            }
        }
        exponent = useObsForLearner.size(0) - 1;
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                ix++;
            }
        }
        r5.set_size(ix);
        ix = 0;
        for (b_i = 0; b_i <= exponent; b_i++) {
            if (useObsForLearner[b_i]) {
                r5[ix] = b_i + 1;
                ix++;
            }
        }
        a__2.set_size(r5.size(0));
        ix = r5.size(0);
        for (i = 0; i < ix; i++) {
            a__2[i] = cachedWeights[r5[i] - 1] + learnerWeights;
        }
        ix = a__2.size(0);
        for (i = 0; i < ix; i++) {
            cachedWeights[r5[i] - 1] = a__2[i];
        }
        i = cachedScore.size(0);
        for (b_i = 0; b_i < i; b_i++) {
            score[b_i] = cachedScore[b_i];
            score[b_i + score.size(0)] = cachedScore[b_i + cachedScore.size(0)];
        }
    }
}

} // namespace ensembleutils
} // namespace coder
} // namespace learning
} // namespace classreg
} // namespace coder
