//
// File: predictOneWithCache.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "predictOneWithCache.h"
#include "CompactClassificationTree.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &X
//                ::coder::array<double, 2U> &cachedScore
//                ::coder::array<double, 1U> &cachedWeights
//                const
//                ::coder::classreg::learning::classif::CompactClassificationTree
//                *weak_learner double learnerWeights boolean_T *cached const
//                double classnames[2] const ::coder::array<boolean_T, 1U>
//                &useObsForLearner boolean_T initCache
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
  int c_i;
  int exponent;
  int i;
  int loop_ub;
  signed char iloc[2];
  boolean_T exitg1;
  boolean_T y;
  learnerscore.set_size(cachedScore.size(0), 2);
  loop_ub = cachedScore.size(0) << 1;
  if (static_cast<int>(loop_ub < 1200)) {
    for (i = 0; i < loop_ub; i++) {
      learnerscore[i] = rtNaN;
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < loop_ub; i++) {
      learnerscore[i] = rtNaN;
    }
  }
  iloc[0] = 0;
  b_i = 0;
  exitg1 = false;
  while ((!exitg1) && (b_i < 2)) {
    absx = std::abs(classnames[b_i] / 2.0);
    if ((!std::isinf(absx)) && (!std::isnan(absx))) {
      if (absx <= 2.2250738585072014E-308) {
        absx = 4.94065645841247E-324;
      } else {
        frexp(absx, &exponent);
        absx = std::ldexp(1.0, exponent - 53);
      }
    } else {
      absx = rtNaN;
    }
    if ((std::abs(classnames[b_i] - weak_learner->ClassNames[0]) < absx) ||
        (std::isinf(weak_learner->ClassNames[0]) &&
         std::isinf(classnames[b_i]) &&
         ((weak_learner->ClassNames[0] > 0.0) == (classnames[b_i] > 0.0)))) {
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
    absx = std::abs(classnames[b_i] / 2.0);
    if ((!std::isinf(absx)) && (!std::isnan(absx))) {
      if (absx <= 2.2250738585072014E-308) {
        absx = 4.94065645841247E-324;
      } else {
        frexp(absx, &exponent);
        absx = std::ldexp(1.0, exponent - 53);
      }
    } else {
      absx = rtNaN;
    }
    if ((std::abs(classnames[b_i] - weak_learner->ClassNames[1]) < absx) ||
        (std::isinf(weak_learner->ClassNames[1]) &&
         std::isinf(classnames[b_i]) &&
         ((weak_learner->ClassNames[1] > 0.0) == (classnames[b_i] > 0.0)))) {
      iloc[1] = static_cast<signed char>(b_i + 1);
      exitg1 = true;
    } else {
      b_i++;
    }
  }
  y = false;
  exponent = 1;
  exitg1 = false;
  while ((!exitg1) && (exponent <= useObsForLearner.size(0))) {
    if (!useObsForLearner[exponent - 1]) {
      exponent++;
    } else {
      y = true;
      exitg1 = true;
    }
  }
  if (y) {
    loop_ub = useObsForLearner.size(0) - 1;
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        exponent++;
      }
    }
    r.set_size(exponent);
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        r[exponent] = b_i + 1;
        exponent++;
      }
    }
    b_X.set_size(r.size(0), 23);
    loop_ub = r.size(0);
    if (static_cast<int>(23 * r.size(0) < 1200)) {
      for (i = 0; i < 23; i++) {
        for (c_i = 0; c_i < loop_ub; c_i++) {
          b_X[c_i + b_X.size(0) * i] = X[(r[c_i] + X.size(0) * i) - 1];
        }
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(c_i, i)

      for (i = 0; i < 23; i++) {
        for (c_i = 0; c_i < loop_ub; c_i++) {
          b_X[c_i + b_X.size(0) * i] = X[(r[c_i] + X.size(0) * i) - 1];
        }
      }
    }
    weak_learner->predict(b_X, a__2, b_cachedScore);
    loop_ub = useObsForLearner.size(0) - 1;
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        exponent++;
      }
    }
    r2.set_size(exponent);
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        r2[exponent] = b_i + 1;
        exponent++;
      }
    }
    loop_ub = b_cachedScore.size(0);
    for (b_i = 0; b_i < 2; b_i++) {
      for (exponent = 0; exponent < loop_ub; exponent++) {
        learnerscore[(r2[exponent] + learnerscore.size(0) * (iloc[b_i] - 1)) -
                     1] = b_cachedScore[exponent + b_cachedScore.size(0) * b_i];
      }
    }
  }
  if (initCache) {
    loop_ub = useObsForLearner.size(0) - 1;
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        exponent++;
      }
    }
    r1.set_size(exponent);
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        r1[exponent] = b_i + 1;
        exponent++;
      }
    }
    loop_ub = r1.size(0);
    for (b_i = 0; b_i < 2; b_i++) {
      for (exponent = 0; exponent < loop_ub; exponent++) {
        cachedScore[(r1[exponent] + cachedScore.size(0) * b_i) - 1] = 0.0;
      }
    }
  } else {
    tf.set_size(cachedScore.size(0), 2);
    loop_ub = cachedScore.size(0) * 2;
    if (static_cast<int>(loop_ub < 1200)) {
      for (i = 0; i < loop_ub; i++) {
        tf[i] = std::isnan(cachedScore[i]);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i < loop_ub; i++) {
        tf[i] = std::isnan(cachedScore[i]);
      }
    }
    y = false;
    exponent = 1;
    exitg1 = false;
    while ((!exitg1) && (exponent <= (tf.size(0) << 1))) {
      if (!tf[exponent - 1]) {
        exponent++;
      } else {
        y = true;
        exitg1 = true;
      }
    }
    if (y) {
      loop_ub = (tf.size(0) << 1) - 1;
      exponent = 0;
      for (b_i = 0; b_i <= loop_ub; b_i++) {
        if (tf[b_i]) {
          exponent++;
        }
      }
      r1.set_size(exponent);
      exponent = 0;
      for (b_i = 0; b_i <= loop_ub; b_i++) {
        if (tf[b_i]) {
          r1[exponent] = b_i + 1;
          exponent++;
        }
      }
      loop_ub = r1.size(0);
      for (b_i = 0; b_i < loop_ub; b_i++) {
        cachedScore[r1[b_i] - 1] = 0.0;
      }
    }
  }
  score.set_size(cachedScore.size(0), 2);
  loop_ub = cachedScore.size(0) * 2;
  if (static_cast<int>(loop_ub < 1200)) {
    for (i = 0; i < loop_ub; i++) {
      score[i] = cachedScore[i];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

    for (i = 0; i < loop_ub; i++) {
      score[i] = cachedScore[i];
    }
  }
  if (!*cached) {
    *cached = true;
    loop_ub = useObsForLearner.size(0) - 1;
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        exponent++;
      }
    }
    r3.set_size(exponent);
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        r3[exponent] = b_i + 1;
        exponent++;
      }
    }
    loop_ub = useObsForLearner.size(0) - 1;
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        exponent++;
      }
    }
    r4.set_size(exponent);
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        r4[exponent] = b_i + 1;
        exponent++;
      }
    }
    b_cachedScore.set_size(r4.size(0), 2);
    loop_ub = r4.size(0);
    if (static_cast<int>((r4.size(0) << 1) < 1200)) {
      for (i = 0; i < 2; i++) {
        for (c_i = 0; c_i < loop_ub; c_i++) {
          b_cachedScore[c_i + b_cachedScore.size(0) * i] =
              cachedScore[(r4[c_i] + cachedScore.size(0) * i) - 1] +
              learnerscore[(r3[c_i] + learnerscore.size(0) * i) - 1] *
                  learnerWeights;
        }
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(c_i, i)

      for (i = 0; i < 2; i++) {
        for (c_i = 0; c_i < loop_ub; c_i++) {
          b_cachedScore[c_i + b_cachedScore.size(0) * i] =
              cachedScore[(r4[c_i] + cachedScore.size(0) * i) - 1] +
              learnerscore[(r3[c_i] + learnerscore.size(0) * i) - 1] *
                  learnerWeights;
        }
      }
    }
    loop_ub = b_cachedScore.size(0);
    for (b_i = 0; b_i < 2; b_i++) {
      for (exponent = 0; exponent < loop_ub; exponent++) {
        cachedScore[(r4[exponent] + cachedScore.size(0) * b_i) - 1] =
            b_cachedScore[exponent + b_cachedScore.size(0) * b_i];
      }
    }
    loop_ub = useObsForLearner.size(0) - 1;
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        exponent++;
      }
    }
    r5.set_size(exponent);
    exponent = 0;
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      if (useObsForLearner[b_i]) {
        r5[exponent] = b_i + 1;
        exponent++;
      }
    }
    a__2.set_size(r5.size(0));
    loop_ub = r5.size(0);
    if (static_cast<int>(r5.size(0) < 1200)) {
      for (i = 0; i < loop_ub; i++) {
        a__2[i] = cachedWeights[r5[i] - 1] + learnerWeights;
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i)

      for (i = 0; i < loop_ub; i++) {
        a__2[i] = cachedWeights[r5[i] - 1] + learnerWeights;
      }
    }
    loop_ub = a__2.size(0);
    for (b_i = 0; b_i < loop_ub; b_i++) {
      cachedWeights[r5[b_i] - 1] = a__2[b_i];
    }
    b_i = cachedScore.size(0);
    if (static_cast<int>((b_i << 1) < 1200)) {
      for (c_i = 0; c_i < b_i; c_i++) {
        score[c_i] = cachedScore[c_i];
        score[c_i + score.size(0)] = cachedScore[c_i + cachedScore.size(0)];
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(c_i)

      for (c_i = 0; c_i < b_i; c_i++) {
        score[c_i] = cachedScore[c_i];
        score[c_i + score.size(0)] = cachedScore[c_i + cachedScore.size(0)];
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
