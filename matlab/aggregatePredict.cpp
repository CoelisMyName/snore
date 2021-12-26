//
// File: aggregatePredict.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "aggregatePredict.h"
#include "CompactClassificationTree.h"
#include "predictOneWithCache.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &X
//                ::coder::array<double, 2U> &score
//                const double learnerWeights[400]
//                const boolean_T isCached[400]
//                const double classNames[2]
//                const boolean_T learners[400]
//                const ::coder::array<boolean_T, 2U> &useObsForLearner
// Return Type  : void
//
namespace coder
{
  namespace classreg
  {
    namespace learning
    {
      namespace coder
      {
        namespace ensembleutils
        {
          void aggregatePredict(const ::coder::array<double, 2U> &X, ::coder::
                                array<double, 2U> &score, const double
                                learnerWeights[400], const boolean_T isCached
                                [400], const double classNames[2], const
                                boolean_T learners[400], const ::coder::array<
                                boolean_T, 2U> &useObsForLearner)
          {
            ::coder::classreg::learning::classif::CompactClassificationTree
              weak_learner;
            array<double, 2U> cachedScore;
            array<double, 1U> cachedWeights;
            array<boolean_T, 1U> b_useObsForLearner;
            int b_loop_ub;
            int i;
            int loop_ub;
            boolean_T b;
            boolean_T firstCache;
            boolean_T initCache;
            cachedScore.set_size(score.size(0), 2);
            loop_ub = score.size(0) * 2;
            if (static_cast<int>(loop_ub < 1200)) {
              for (i = 0; i < loop_ub; i++) {
                cachedScore[i] = score[i];
              }
            } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

              for (i = 0; i < loop_ub; i++) {
                cachedScore[i] = score[i];
              }
            }

            cachedWeights.set_size(score.size(0));
            loop_ub = score.size(0);
            if (static_cast<int>(loop_ub < 1200)) {
              for (i = 0; i < loop_ub; i++) {
                cachedWeights[i] = 0.0;
              }
            } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

              for (i = 0; i < loop_ub; i++) {
                cachedWeights[i] = 0.0;
              }
            }

            firstCache = true;
            if (learners[0]) {
              firstCache = false;
              weak_learner.init();
              b = false;
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[0], &b, classNames,
                                  b_useObsForLearner, true, score);
            }

            if (learners[1]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.b_init();
              b = isCached[1];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0)];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0)];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[1], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[2]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.c_init();
              b = isCached[2];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 2];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 2];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[2], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[3]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.d_init();
              b = isCached[3];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 3];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 3];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[3], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[4]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.e_init();
              b = isCached[4];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 4];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 4];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[4], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[5]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.f_init();
              b = isCached[5];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 5];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 5];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[5], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[6]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.g_init();
              b = isCached[6];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 6];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 6];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[6], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[7]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.h_init();
              b = isCached[7];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 7];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 7];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[7], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[8]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.i_init();
              b = isCached[8];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 8];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 8];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[8], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[9]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.j_init();
              b = isCached[9];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 9];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 9];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[9], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[10]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.k_init();
              b = isCached[10];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 10];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 10];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[10], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[11]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.l_init();
              b = isCached[11];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 11];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 11];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[11], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[12]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.m_init();
              b = isCached[12];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 12];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 12];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[12], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[13]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.n_init();
              b = isCached[13];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 13];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 13];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[13], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[14]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.o_init();
              b = isCached[14];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 14];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 14];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[14], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[15]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.p_init();
              b = isCached[15];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 15];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 15];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[15], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[16]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.q_init();
              b = isCached[16];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 16];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 16];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[16], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[17]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.r_init();
              b = isCached[17];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 17];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 17];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[17], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[18]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.s_init();
              b = isCached[18];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 18];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 18];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[18], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[19]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.t_init();
              b = isCached[19];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 19];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 19];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[19], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[20]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.u_init();
              b = isCached[20];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 20];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 20];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[20], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[21]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.v_init();
              b = isCached[21];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 21];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 21];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[21], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[22]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.w_init();
              b = isCached[22];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 22];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 22];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[22], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[23]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.x_init();
              b = isCached[23];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 23];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 23];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[23], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[24]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.y_init();
              b = isCached[24];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 24];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 24];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[24], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[25]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ab_init();
              b = isCached[25];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 25];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 25];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[25], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[26]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bb_init();
              b = isCached[26];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 26];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 26];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[26], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[27]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cb_init();
              b = isCached[27];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 27];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 27];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[27], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[28]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.db_init();
              b = isCached[28];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 28];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 28];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[28], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[29]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.eb_init();
              b = isCached[29];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 29];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 29];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[29], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[30]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fb_init();
              b = isCached[30];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 30];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 30];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[30], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[31]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gb_init();
              b = isCached[31];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 31];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 31];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[31], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[32]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hb_init();
              b = isCached[32];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 32];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 32];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[32], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[33]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ib_init();
              b = isCached[33];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 33];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 33];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[33], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[34]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jb_init();
              b = isCached[34];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 34];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 34];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[34], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[35]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kb_init();
              b = isCached[35];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 35];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 35];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[35], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[36]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lb_init();
              b = isCached[36];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 36];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 36];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[36], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[37]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mb_init();
              b = isCached[37];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 37];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 37];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[37], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[38]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nb_init();
              b = isCached[38];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 38];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 38];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[38], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[39]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ob_init();
              b = isCached[39];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 39];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 39];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[39], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[40]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pb_init();
              b = isCached[40];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 40];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 40];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[40], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[41]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qb_init();
              b = isCached[41];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 41];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 41];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[41], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[42]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rb_init();
              b = isCached[42];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 42];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 42];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[42], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[43]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sb_init();
              b = isCached[43];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 43];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 43];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[43], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[44]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tb_init();
              b = isCached[44];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 44];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 44];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[44], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[45]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ub_init();
              b = isCached[45];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 45];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 45];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[45], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[46]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vb_init();
              b = isCached[46];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 46];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 46];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[46], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[47]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wb_init();
              b = isCached[47];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 47];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 47];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[47], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[48]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xb_init();
              b = isCached[48];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 48];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 48];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[48], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[49]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yb_init();
              b = isCached[49];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 49];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 49];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[49], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[50]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ac_init();
              b = isCached[50];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 50];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 50];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[50], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[51]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bc_init();
              b = isCached[51];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 51];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 51];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[51], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[52]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cc_init();
              b = isCached[52];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 52];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 52];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[52], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[53]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dc_init();
              b = isCached[53];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 53];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 53];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[53], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[54]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ec_init();
              b = isCached[54];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 54];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 54];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[54], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[55]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fc_init();
              b = isCached[55];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 55];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 55];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[55], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[56]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gc_init();
              b = isCached[56];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 56];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 56];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[56], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[57]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hc_init();
              b = isCached[57];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 57];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 57];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[57], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[58]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ic_init();
              b = isCached[58];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 58];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 58];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[58], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[59]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jc_init();
              b = isCached[59];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 59];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 59];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[59], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[60]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kc_init();
              b = isCached[60];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 60];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 60];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[60], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[61]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lc_init();
              b = isCached[61];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 61];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 61];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[61], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[62]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mc_init();
              b = isCached[62];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 62];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 62];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[62], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[63]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nc_init();
              b = isCached[63];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 63];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 63];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[63], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[64]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.oc_init();
              b = isCached[64];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 64];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 64];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[64], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[65]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pc_init();
              b = isCached[65];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 65];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 65];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[65], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[66]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qc_init();
              b = isCached[66];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 66];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 66];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[66], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[67]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rc_init();
              b = isCached[67];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 67];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 67];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[67], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[68]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sc_init();
              b = isCached[68];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 68];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 68];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[68], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[69]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tc_init();
              b = isCached[69];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 69];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 69];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[69], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[70]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.uc_init();
              b = isCached[70];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 70];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 70];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[70], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[71]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vc_init();
              b = isCached[71];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 71];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 71];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[71], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[72]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wc_init();
              b = isCached[72];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 72];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 72];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[72], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[73]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xc_init();
              b = isCached[73];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 73];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 73];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[73], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[74]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yc_init();
              b = isCached[74];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 74];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 74];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[74], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[75]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ad_init();
              b = isCached[75];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 75];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 75];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[75], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[76]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bd_init();
              b = isCached[76];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 76];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 76];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[76], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[77]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cd_init();
              b = isCached[77];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 77];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 77];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[77], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[78]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dd_init();
              b = isCached[78];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 78];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 78];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[78], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[79]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ed_init();
              b = isCached[79];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 79];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 79];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[79], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[80]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fd_init();
              b = isCached[80];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 80];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 80];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[80], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[81]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gd_init();
              b = isCached[81];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 81];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 81];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[81], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[82]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hd_init();
              b = isCached[82];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 82];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 82];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[82], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[83]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.id_init();
              b = isCached[83];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 83];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 83];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[83], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[84]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jd_init();
              b = isCached[84];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 84];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 84];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[84], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[85]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kd_init();
              b = isCached[85];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 85];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 85];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[85], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[86]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ld_init();
              b = isCached[86];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 86];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 86];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[86], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[87]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.md_init();
              b = isCached[87];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 87];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 87];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[87], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[88]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nd_init();
              b = isCached[88];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 88];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 88];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[88], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[89]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.od_init();
              b = isCached[89];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 89];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 89];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[89], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[90]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pd_init();
              b = isCached[90];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 90];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 90];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[90], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[91]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qd_init();
              b = isCached[91];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 91];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 91];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[91], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[92]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rd_init();
              b = isCached[92];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 92];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 92];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[92], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[93]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sd_init();
              b = isCached[93];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 93];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 93];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[93], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[94]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.td_init();
              b = isCached[94];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 94];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 94];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[94], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[95]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ud_init();
              b = isCached[95];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 95];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 95];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[95], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[96]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vd_init();
              b = isCached[96];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 96];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 96];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[96], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[97]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wd_init();
              b = isCached[97];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 97];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 97];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[97], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[98]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xd_init();
              b = isCached[98];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 98];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 98];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[98], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[99]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yd_init();
              b = isCached[99];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 99];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 99];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[99], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[100]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ae_init();
              b = isCached[100];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 100];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 100];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[100], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[101]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.be_init();
              b = isCached[101];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 101];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 101];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[101], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[102]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ce_init();
              b = isCached[102];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 102];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 102];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[102], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[103]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.de_init();
              b = isCached[103];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 103];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 103];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[103], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[104]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ee_init();
              b = isCached[104];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 104];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 104];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[104], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[105]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fe_init();
              b = isCached[105];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 105];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 105];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[105], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[106]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ge_init();
              b = isCached[106];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 106];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 106];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[106], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[107]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.he_init();
              b = isCached[107];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 107];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 107];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[107], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[108]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ie_init();
              b = isCached[108];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 108];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 108];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[108], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[109]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.je_init();
              b = isCached[109];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 109];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 109];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[109], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[110]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ke_init();
              b = isCached[110];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 110];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 110];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[110], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[111]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.le_init();
              b = isCached[111];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 111];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 111];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[111], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[112]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.me_init();
              b = isCached[112];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 112];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 112];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[112], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[113]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ne_init();
              b = isCached[113];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 113];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 113];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[113], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[114]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.oe_init();
              b = isCached[114];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 114];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 114];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[114], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[115]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pe_init();
              b = isCached[115];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 115];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 115];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[115], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[116]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qe_init();
              b = isCached[116];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 116];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 116];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[116], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[117]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.re_init();
              b = isCached[117];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 117];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 117];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[117], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[118]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.se_init();
              b = isCached[118];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 118];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 118];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[118], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[119]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.te_init();
              b = isCached[119];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 119];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 119];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[119], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[120]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ue_init();
              b = isCached[120];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 120];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 120];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[120], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[121]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ve_init();
              b = isCached[121];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 121];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 121];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[121], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[122]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.we_init();
              b = isCached[122];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 122];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 122];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[122], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[123]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xe_init();
              b = isCached[123];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 123];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 123];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[123], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[124]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ye_init();
              b = isCached[124];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 124];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 124];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[124], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[125]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.af_init();
              b = isCached[125];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 125];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 125];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[125], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[126]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bf_init();
              b = isCached[126];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 126];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 126];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[126], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[127]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cf_init();
              b = isCached[127];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 127];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 127];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[127], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[128]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.df_init();
              b = isCached[128];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 128];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 128];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[128], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[129]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ef_init();
              b = isCached[129];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 129];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 129];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[129], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[130]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ff_init();
              b = isCached[130];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 130];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 130];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[130], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[131]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gf_init();
              b = isCached[131];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 131];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 131];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[131], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[132]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hf_init();
              b = isCached[132];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 132];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 132];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[132], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[133]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.if_init();
              b = isCached[133];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 133];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 133];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[133], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[134]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jf_init();
              b = isCached[134];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 134];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 134];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[134], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[135]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kf_init();
              b = isCached[135];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 135];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 135];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[135], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[136]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lf_init();
              b = isCached[136];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 136];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 136];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[136], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[137]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mf_init();
              b = isCached[137];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 137];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 137];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[137], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[138]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nf_init();
              b = isCached[138];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 138];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 138];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[138], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[139]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.of_init();
              b = isCached[139];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 139];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 139];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[139], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[140]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pf_init();
              b = isCached[140];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 140];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 140];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[140], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[141]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qf_init();
              b = isCached[141];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 141];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 141];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[141], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[142]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rf_init();
              b = isCached[142];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 142];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 142];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[142], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[143]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sf_init();
              b = isCached[143];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 143];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 143];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[143], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[144]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tf_init();
              b = isCached[144];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 144];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 144];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[144], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[145]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.uf_init();
              b = isCached[145];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 145];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 145];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[145], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[146]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vf_init();
              b = isCached[146];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 146];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 146];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[146], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[147]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wf_init();
              b = isCached[147];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 147];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 147];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[147], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[148]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xf_init();
              b = isCached[148];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 148];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 148];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[148], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[149]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yf_init();
              b = isCached[149];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 149];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 149];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[149], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[150]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ag_init();
              b = isCached[150];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 150];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 150];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[150], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[151]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bg_init();
              b = isCached[151];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 151];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 151];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[151], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[152]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cg_init();
              b = isCached[152];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 152];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 152];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[152], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[153]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dg_init();
              b = isCached[153];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 153];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 153];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[153], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[154]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.eg_init();
              b = isCached[154];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 154];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 154];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[154], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[155]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fg_init();
              b = isCached[155];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 155];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 155];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[155], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[156]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gg_init();
              b = isCached[156];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 156];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 156];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[156], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[157]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hg_init();
              b = isCached[157];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 157];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 157];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[157], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[158]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ig_init();
              b = isCached[158];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 158];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 158];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[158], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[159]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jg_init();
              b = isCached[159];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 159];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 159];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[159], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[160]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kg_init();
              b = isCached[160];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 160];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 160];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[160], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[161]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lg_init();
              b = isCached[161];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 161];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 161];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[161], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[162]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mg_init();
              b = isCached[162];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 162];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 162];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[162], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[163]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ng_init();
              b = isCached[163];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 163];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 163];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[163], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[164]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.og_init();
              b = isCached[164];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 164];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 164];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[164], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[165]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pg_init();
              b = isCached[165];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 165];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 165];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[165], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[166]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qg_init();
              b = isCached[166];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 166];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 166];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[166], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[167]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rg_init();
              b = isCached[167];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 167];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 167];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[167], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[168]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sg_init();
              b = isCached[168];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 168];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 168];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[168], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[169]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tg_init();
              b = isCached[169];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 169];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 169];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[169], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[170]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ug_init();
              b = isCached[170];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 170];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 170];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[170], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[171]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vg_init();
              b = isCached[171];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 171];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 171];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[171], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[172]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wg_init();
              b = isCached[172];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 172];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 172];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[172], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[173]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xg_init();
              b = isCached[173];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 173];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 173];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[173], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[174]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yg_init();
              b = isCached[174];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 174];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 174];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[174], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[175]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ah_init();
              b = isCached[175];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 175];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 175];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[175], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[176]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bh_init();
              b = isCached[176];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 176];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 176];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[176], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[177]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ch_init();
              b = isCached[177];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 177];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 177];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[177], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[178]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dh_init();
              b = isCached[178];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 178];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 178];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[178], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[179]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.eh_init();
              b = isCached[179];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 179];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 179];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[179], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[180]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fh_init();
              b = isCached[180];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 180];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 180];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[180], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[181]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gh_init();
              b = isCached[181];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 181];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 181];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[181], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[182]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hh_init();
              b = isCached[182];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 182];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 182];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[182], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[183]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ih_init();
              b = isCached[183];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 183];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 183];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[183], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[184]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jh_init();
              b = isCached[184];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 184];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 184];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[184], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[185]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kh_init();
              b = isCached[185];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 185];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 185];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[185], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[186]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lh_init();
              b = isCached[186];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 186];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 186];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[186], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[187]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mh_init();
              b = isCached[187];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 187];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 187];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[187], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[188]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nh_init();
              b = isCached[188];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 188];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 188];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[188], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[189]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.oh_init();
              b = isCached[189];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 189];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 189];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[189], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[190]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ph_init();
              b = isCached[190];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 190];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 190];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[190], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[191]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qh_init();
              b = isCached[191];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 191];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 191];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[191], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[192]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rh_init();
              b = isCached[192];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 192];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 192];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[192], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[193]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sh_init();
              b = isCached[193];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 193];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 193];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[193], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[194]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.th_init();
              b = isCached[194];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 194];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 194];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[194], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[195]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.uh_init();
              b = isCached[195];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 195];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 195];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[195], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[196]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vh_init();
              b = isCached[196];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 196];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 196];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[196], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[197]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wh_init();
              b = isCached[197];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 197];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 197];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[197], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[198]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xh_init();
              b = isCached[198];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 198];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 198];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[198], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[199]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yh_init();
              b = isCached[199];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 199];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 199];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[199], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[200]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ai_init();
              b = isCached[200];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 200];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 200];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[200], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[201]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bi_init();
              b = isCached[201];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 201];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 201];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[201], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[202]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ci_init();
              b = isCached[202];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 202];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 202];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[202], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[203]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.di_init();
              b = isCached[203];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 203];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 203];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[203], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[204]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ei_init();
              b = isCached[204];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 204];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 204];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[204], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[205]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fi_init();
              b = isCached[205];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 205];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 205];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[205], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[206]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gi_init();
              b = isCached[206];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 206];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 206];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[206], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[207]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hi_init();
              b = isCached[207];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 207];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 207];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[207], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[208]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ii_init();
              b = isCached[208];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 208];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 208];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[208], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[209]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ji_init();
              b = isCached[209];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 209];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 209];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[209], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[210]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ki_init();
              b = isCached[210];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 210];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 210];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[210], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[211]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.li_init();
              b = isCached[211];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 211];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 211];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[211], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[212]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mi_init();
              b = isCached[212];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 212];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 212];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[212], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[213]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ni_init();
              b = isCached[213];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 213];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 213];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[213], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[214]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.oi_init();
              b = isCached[214];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 214];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 214];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[214], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[215]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pi_init();
              b = isCached[215];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 215];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 215];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[215], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[216]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qi_init();
              b = isCached[216];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 216];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 216];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[216], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[217]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ri_init();
              b = isCached[217];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 217];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 217];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[217], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[218]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.si_init();
              b = isCached[218];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 218];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 218];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[218], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[219]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ti_init();
              b = isCached[219];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 219];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 219];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[219], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[220]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ui_init();
              b = isCached[220];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 220];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 220];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[220], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[221]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vi_init();
              b = isCached[221];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 221];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 221];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[221], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[222]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wi_init();
              b = isCached[222];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 222];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 222];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[222], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[223]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xi_init();
              b = isCached[223];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 223];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 223];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[223], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[224]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yi_init();
              b = isCached[224];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 224];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 224];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[224], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[225]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.aj_init();
              b = isCached[225];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 225];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 225];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[225], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[226]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bj_init();
              b = isCached[226];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 226];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 226];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[226], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[227]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cj_init();
              b = isCached[227];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 227];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 227];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[227], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[228]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dj_init();
              b = isCached[228];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 228];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 228];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[228], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[229]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ej_init();
              b = isCached[229];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 229];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 229];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[229], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[230]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fj_init();
              b = isCached[230];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 230];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 230];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[230], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[231]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gj_init();
              b = isCached[231];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 231];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 231];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[231], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[232]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hj_init();
              b = isCached[232];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 232];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 232];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[232], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[233]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ij_init();
              b = isCached[233];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 233];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 233];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[233], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[234]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jj_init();
              b = isCached[234];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 234];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 234];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[234], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[235]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kj_init();
              b = isCached[235];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 235];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 235];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[235], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[236]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lj_init();
              b = isCached[236];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 236];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 236];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[236], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[237]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mj_init();
              b = isCached[237];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 237];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 237];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[237], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[238]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nj_init();
              b = isCached[238];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 238];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 238];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[238], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[239]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.oj_init();
              b = isCached[239];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 239];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 239];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[239], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[240]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pj_init();
              b = isCached[240];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 240];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 240];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[240], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[241]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qj_init();
              b = isCached[241];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 241];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 241];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[241], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[242]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rj_init();
              b = isCached[242];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 242];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 242];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[242], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[243]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sj_init();
              b = isCached[243];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 243];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 243];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[243], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[244]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tj_init();
              b = isCached[244];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 244];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 244];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[244], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[245]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.uj_init();
              b = isCached[245];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 245];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 245];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[245], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[246]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vj_init();
              b = isCached[246];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 246];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 246];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[246], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[247]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wj_init();
              b = isCached[247];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 247];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 247];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[247], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[248]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xj_init();
              b = isCached[248];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 248];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 248];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[248], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[249]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yj_init();
              b = isCached[249];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 249];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 249];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[249], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[250]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ak_init();
              b = isCached[250];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 250];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 250];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[250], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[251]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bk_init();
              b = isCached[251];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 251];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 251];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[251], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[252]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ck_init();
              b = isCached[252];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 252];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 252];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[252], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[253]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dk_init();
              b = isCached[253];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 253];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 253];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[253], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[254]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ek_init();
              b = isCached[254];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 254];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 254];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[254], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[255]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fk_init();
              b = isCached[255];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 255];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 255];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[255], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[256]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gk_init();
              b = isCached[256];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 256];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 256];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[256], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[257]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hk_init();
              b = isCached[257];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 257];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 257];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[257], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[258]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ik_init();
              b = isCached[258];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 258];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 258];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[258], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[259]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jk_init();
              b = isCached[259];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 259];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 259];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[259], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[260]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kk_init();
              b = isCached[260];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 260];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 260];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[260], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[261]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lk_init();
              b = isCached[261];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 261];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 261];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[261], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[262]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mk_init();
              b = isCached[262];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 262];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 262];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[262], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[263]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nk_init();
              b = isCached[263];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 263];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 263];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[263], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[264]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ok_init();
              b = isCached[264];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 264];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 264];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[264], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[265]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pk_init();
              b = isCached[265];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 265];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 265];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[265], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[266]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qk_init();
              b = isCached[266];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 266];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 266];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[266], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[267]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rk_init();
              b = isCached[267];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 267];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 267];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[267], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[268]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sk_init();
              b = isCached[268];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 268];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 268];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[268], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[269]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tk_init();
              b = isCached[269];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 269];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 269];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[269], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[270]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.uk_init();
              b = isCached[270];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 270];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 270];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[270], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[271]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vk_init();
              b = isCached[271];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 271];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 271];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[271], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[272]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wk_init();
              b = isCached[272];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 272];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 272];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[272], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[273]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xk_init();
              b = isCached[273];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 273];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 273];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[273], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[274]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yk_init();
              b = isCached[274];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 274];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 274];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[274], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[275]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.al_init();
              b = isCached[275];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 275];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 275];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[275], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[276]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bl_init();
              b = isCached[276];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 276];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 276];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[276], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[277]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cl_init();
              b = isCached[277];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 277];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 277];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[277], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[278]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dl_init();
              b = isCached[278];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 278];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 278];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[278], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[279]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.el_init();
              b = isCached[279];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 279];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 279];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[279], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[280]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fl_init();
              b = isCached[280];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 280];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 280];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[280], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[281]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gl_init();
              b = isCached[281];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 281];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 281];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[281], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[282]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hl_init();
              b = isCached[282];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 282];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 282];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[282], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[283]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.il_init();
              b = isCached[283];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 283];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 283];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[283], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[284]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jl_init();
              b = isCached[284];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 284];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 284];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[284], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[285]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kl_init();
              b = isCached[285];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 285];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 285];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[285], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[286]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ll_init();
              b = isCached[286];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 286];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 286];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[286], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[287]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ml_init();
              b = isCached[287];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 287];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 287];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[287], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[288]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nl_init();
              b = isCached[288];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 288];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 288];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[288], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[289]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ol_init();
              b = isCached[289];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 289];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 289];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[289], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[290]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pl_init();
              b = isCached[290];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 290];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 290];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[290], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[291]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ql_init();
              b = isCached[291];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 291];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 291];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[291], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[292]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rl_init();
              b = isCached[292];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 292];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 292];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[292], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[293]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sl_init();
              b = isCached[293];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 293];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 293];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[293], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[294]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tl_init();
              b = isCached[294];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 294];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 294];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[294], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[295]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ul_init();
              b = isCached[295];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 295];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 295];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[295], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[296]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vl_init();
              b = isCached[296];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 296];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 296];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[296], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[297]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wl_init();
              b = isCached[297];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 297];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 297];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[297], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[298]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xl_init();
              b = isCached[298];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 298];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 298];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[298], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[299]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yl_init();
              b = isCached[299];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 299];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 299];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[299], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[300]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.am_init();
              b = isCached[300];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 300];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 300];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[300], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[301]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bm_init();
              b = isCached[301];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 301];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 301];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[301], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[302]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cm_init();
              b = isCached[302];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 302];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 302];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[302], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[303]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dm_init();
              b = isCached[303];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 303];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 303];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[303], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[304]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.em_init();
              b = isCached[304];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 304];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 304];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[304], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[305]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fm_init();
              b = isCached[305];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 305];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 305];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[305], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[306]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gm_init();
              b = isCached[306];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 306];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 306];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[306], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[307]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hm_init();
              b = isCached[307];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 307];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 307];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[307], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[308]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.im_init();
              b = isCached[308];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 308];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 308];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[308], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[309]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jm_init();
              b = isCached[309];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 309];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 309];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[309], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[310]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.km_init();
              b = isCached[310];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 310];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 310];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[310], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[311]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lm_init();
              b = isCached[311];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 311];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 311];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[311], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[312]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mm_init();
              b = isCached[312];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 312];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 312];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[312], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[313]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nm_init();
              b = isCached[313];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 313];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 313];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[313], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[314]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.om_init();
              b = isCached[314];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 314];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 314];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[314], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[315]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pm_init();
              b = isCached[315];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 315];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 315];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[315], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[316]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qm_init();
              b = isCached[316];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 316];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 316];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[316], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[317]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rm_init();
              b = isCached[317];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 317];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 317];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[317], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[318]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sm_init();
              b = isCached[318];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 318];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 318];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[318], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[319]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tm_init();
              b = isCached[319];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 319];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 319];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[319], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[320]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.um_init();
              b = isCached[320];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 320];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 320];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[320], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[321]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vm_init();
              b = isCached[321];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 321];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 321];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[321], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[322]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wm_init();
              b = isCached[322];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 322];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 322];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[322], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[323]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xm_init();
              b = isCached[323];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 323];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 323];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[323], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[324]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ym_init();
              b = isCached[324];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 324];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 324];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[324], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[325]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.an_init();
              b = isCached[325];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 325];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 325];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[325], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[326]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bn_init();
              b = isCached[326];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 326];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 326];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[326], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[327]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cn_init();
              b = isCached[327];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 327];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 327];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[327], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[328]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dn_init();
              b = isCached[328];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 328];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 328];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[328], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[329]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.en_init();
              b = isCached[329];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 329];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 329];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[329], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[330]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fn_init();
              b = isCached[330];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 330];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 330];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[330], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[331]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gn_init();
              b = isCached[331];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 331];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 331];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[331], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[332]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hn_init();
              b = isCached[332];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 332];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 332];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[332], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[333]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.in_init();
              b = isCached[333];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 333];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 333];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[333], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[334]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jn_init();
              b = isCached[334];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 334];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 334];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[334], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[335]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kn_init();
              b = isCached[335];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 335];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 335];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[335], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[336]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ln_init();
              b = isCached[336];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 336];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 336];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[336], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[337]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mn_init();
              b = isCached[337];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 337];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 337];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[337], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[338]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.nn_init();
              b = isCached[338];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 338];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 338];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[338], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[339]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.on_init();
              b = isCached[339];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 339];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 339];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[339], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[340]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pn_init();
              b = isCached[340];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 340];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 340];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[340], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[341]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qn_init();
              b = isCached[341];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 341];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 341];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[341], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[342]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rn_init();
              b = isCached[342];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 342];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 342];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[342], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[343]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sn_init();
              b = isCached[343];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 343];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 343];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[343], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[344]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tn_init();
              b = isCached[344];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 344];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 344];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[344], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[345]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.un_init();
              b = isCached[345];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 345];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 345];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[345], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[346]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vn_init();
              b = isCached[346];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 346];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 346];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[346], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[347]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wn_init();
              b = isCached[347];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 347];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 347];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[347], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[348]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xn_init();
              b = isCached[348];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 348];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 348];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[348], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[349]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yn_init();
              b = isCached[349];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 349];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 349];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[349], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[350]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ao_init();
              b = isCached[350];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 350];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 350];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[350], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[351]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bo_init();
              b = isCached[351];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 351];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 351];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[351], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[352]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.co_init();
              b = isCached[352];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 352];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 352];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[352], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[353]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.do_init();
              b = isCached[353];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 353];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 353];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[353], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[354]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.eo_init();
              b = isCached[354];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 354];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 354];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[354], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[355]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fo_init();
              b = isCached[355];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 355];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 355];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[355], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[356]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.go_init();
              b = isCached[356];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 356];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 356];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[356], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[357]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ho_init();
              b = isCached[357];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 357];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 357];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[357], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[358]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.io_init();
              b = isCached[358];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 358];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 358];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[358], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[359]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jo_init();
              b = isCached[359];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 359];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 359];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[359], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[360]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ko_init();
              b = isCached[360];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 360];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 360];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[360], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[361]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lo_init();
              b = isCached[361];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 361];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 361];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[361], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[362]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mo_init();
              b = isCached[362];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 362];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 362];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[362], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[363]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.no_init();
              b = isCached[363];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 363];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 363];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[363], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[364]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.oo_init();
              b = isCached[364];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 364];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 364];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[364], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[365]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.po_init();
              b = isCached[365];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 365];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 365];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[365], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[366]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qo_init();
              b = isCached[366];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 366];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 366];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[366], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[367]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ro_init();
              b = isCached[367];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 367];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 367];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[367], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[368]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.so_init();
              b = isCached[368];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 368];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 368];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[368], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[369]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.to_init();
              b = isCached[369];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 369];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 369];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[369], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[370]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.uo_init();
              b = isCached[370];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 370];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 370];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[370], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[371]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vo_init();
              b = isCached[371];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 371];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 371];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[371], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[372]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wo_init();
              b = isCached[372];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 372];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 372];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[372], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[373]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xo_init();
              b = isCached[373];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 373];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 373];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[373], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[374]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.yo_init();
              b = isCached[374];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 374];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 374];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[374], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[375]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ap_init();
              b = isCached[375];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 375];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 375];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[375], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[376]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.bp_init();
              b = isCached[376];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 376];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 376];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[376], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[377]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.cp_init();
              b = isCached[377];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 377];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 377];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[377], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[378]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.dp_init();
              b = isCached[378];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 378];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 378];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[378], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[379]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ep_init();
              b = isCached[379];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 379];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 379];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[379], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[380]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.fp_init();
              b = isCached[380];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 380];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 380];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[380], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[381]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.gp_init();
              b = isCached[381];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 381];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 381];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[381], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[382]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.hp_init();
              b = isCached[382];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 382];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 382];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[382], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[383]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.ip_init();
              b = isCached[383];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 383];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 383];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[383], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[384]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.jp_init();
              b = isCached[384];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 384];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 384];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[384], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[385]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.kp_init();
              b = isCached[385];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 385];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 385];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[385], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[386]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.lp_init();
              b = isCached[386];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 386];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 386];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[386], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[387]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.mp_init();
              b = isCached[387];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 387];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 387];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[387], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[388]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.np_init();
              b = isCached[388];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 388];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 388];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[388], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[389]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.op_init();
              b = isCached[389];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 389];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 389];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[389], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[390]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.pp_init();
              b = isCached[390];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 390];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 390];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[390], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[391]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.qp_init();
              b = isCached[391];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 391];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 391];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[391], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[392]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.rp_init();
              b = isCached[392];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 392];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 392];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[392], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[393]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.sp_init();
              b = isCached[393];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 393];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 393];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[393], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[394]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.tp_init();
              b = isCached[394];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 394];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 394];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[394], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[395]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.up_init();
              b = isCached[395];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 395];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 395];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[395], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[396]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.vp_init();
              b = isCached[396];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 396];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 396];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[396], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[397]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.wp_init();
              b = isCached[397];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 397];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 397];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[397], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[398]) {
              if (firstCache) {
                initCache = true;
                firstCache = false;
              } else {
                initCache = false;
              }

              weak_learner.xp_init();
              b = isCached[398];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 398];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 398];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[398], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }

            if (learners[399]) {
              initCache = firstCache;
              weak_learner.yp_init();
              b = isCached[399];
              loop_ub = useObsForLearner.size(0);
              b_useObsForLearner.set_size(useObsForLearner.size(0));
              b_loop_ub = useObsForLearner.size(0);
              if (static_cast<int>(useObsForLearner.size(0) < 1200)) {
                for (i = 0; i < loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 399];
                }
              } else {

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(i)

                for (i = 0; i < b_loop_ub; i++) {
                  b_useObsForLearner[i] = useObsForLearner[i +
                    useObsForLearner.size(0) * 399];
                }
              }

              predictOneWithCache(X, cachedScore, cachedWeights, &weak_learner,
                                  learnerWeights[399], &b, classNames,
                                  b_useObsForLearner, initCache, score);
            }
          }
        }
      }
    }
  }
}

//
// File trailer for aggregatePredict.cpp
//
// [EOF]
//
