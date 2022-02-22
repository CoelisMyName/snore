//
// File: aggregatePredict.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
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
//                const boolean_T classlogicalindices[2]
//                const boolean_T learners[400]
//                const ::coder::array<boolean_T, 2U> &useObsForLearner
// Return Type  : void
//
namespace coder {
    namespace classreg {
        namespace learning {
            namespace coder {
                namespace ensembleutils {
                    void aggregatePredict(const ::coder::array<double, 2U> &X, ::coder::
                    array<double, 2U> &score, const double
                                          learnerWeights[400], const boolean_T isCached
                    [400], const double classNames[2], const
                                          boolean_T classlogicalindices[2], const
                                          boolean_T learners[400], const ::coder::array<
                            boolean_T, 2U> &useObsForLearner) {
                        ::coder::classreg::learning::classif::CompactClassificationTree r;
                        array<double, 2U> cachedScore;
                        array<double, 1U> cachedWeights;
                        array<boolean_T, 1U> b_useObsForLearner;
                        int i;
                        int loop_ub;
                        boolean_T b;
                        boolean_T firstCache;
                        boolean_T initCache;
                        cachedScore.set_size(score.size(0), 2);
                        loop_ub = score.size(0) * 2;
                        for (i = 0; i < loop_ub; i++) {
                            cachedScore[i] = score[i];
                        }

                        cachedWeights.set_size(score.size(0));
                        loop_ub = score.size(0);
                        for (i = 0; i < loop_ub; i++) {
                            cachedWeights[i] = 0.0;
                        }

                        firstCache = true;
                        if (learners[0]) {
                            firstCache = false;
                            b = isCached[0];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i];
                            }

                            r.init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[0], &b, classNames,
                                                classlogicalindices, b_useObsForLearner, true,
                                                score);
                        }

                        if (learners[1]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[1];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0)];
                            }

                            r.b_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[1], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[2]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[2];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 2];
                            }

                            r.c_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[2], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[3]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[3];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 3];
                            }

                            r.d_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[3], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[4]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[4];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 4];
                            }

                            r.e_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[4], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[5]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[5];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 5];
                            }

                            r.f_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[5], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[6]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[6];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 6];
                            }

                            r.g_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[6], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[7]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[7];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 7];
                            }

                            r.h_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[7], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[8]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[8];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 8];
                            }

                            r.i_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[8], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[9]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[9];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 9];
                            }

                            r.j_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[9], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[10]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[10];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 10];
                            }

                            r.k_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[10], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[11]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[11];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 11];
                            }

                            r.l_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[11], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[12]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[12];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 12];
                            }

                            r.m_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[12], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[13]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[13];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 13];
                            }

                            r.n_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[13], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[14]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[14];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 14];
                            }

                            r.o_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[14], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[15]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[15];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 15];
                            }

                            r.p_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[15], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[16]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[16];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 16];
                            }

                            r.q_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[16], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[17]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[17];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 17];
                            }

                            r.r_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[17], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[18]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[18];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 18];
                            }

                            r.s_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[18], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[19]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[19];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 19];
                            }

                            r.t_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[19], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[20]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[20];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 20];
                            }

                            r.u_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[20], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[21]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[21];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 21];
                            }

                            r.v_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[21], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[22]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[22];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 22];
                            }

                            r.w_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[22], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[23]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[23];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 23];
                            }

                            r.x_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[23], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[24]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[24];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 24];
                            }

                            r.y_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[24], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[25]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[25];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 25];
                            }

                            r.ab_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[25], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[26]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[26];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 26];
                            }

                            r.bb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[26], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[27]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[27];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 27];
                            }

                            r.cb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[27], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[28]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[28];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 28];
                            }

                            r.db_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[28], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[29]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[29];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 29];
                            }

                            r.eb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[29], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[30]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[30];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 30];
                            }

                            r.fb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[30], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[31]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[31];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 31];
                            }

                            r.gb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[31], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[32]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[32];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 32];
                            }

                            r.hb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[32], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[33]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[33];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 33];
                            }

                            r.ib_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[33], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[34]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[34];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 34];
                            }

                            r.jb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[34], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[35]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[35];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 35];
                            }

                            r.kb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[35], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[36]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[36];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 36];
                            }

                            r.lb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[36], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[37]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[37];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 37];
                            }

                            r.mb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[37], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[38]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[38];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 38];
                            }

                            r.nb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[38], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[39]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[39];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 39];
                            }

                            r.ob_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[39], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[40]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[40];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 40];
                            }

                            r.pb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[40], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[41]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[41];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 41];
                            }

                            r.qb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[41], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[42]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[42];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 42];
                            }

                            r.rb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[42], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[43]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[43];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 43];
                            }

                            r.sb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[43], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[44]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[44];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 44];
                            }

                            r.tb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[44], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[45]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[45];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 45];
                            }

                            r.ub_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[45], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[46]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[46];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 46];
                            }

                            r.vb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[46], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[47]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[47];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 47];
                            }

                            r.wb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[47], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[48]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[48];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 48];
                            }

                            r.xb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[48], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[49]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[49];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 49];
                            }

                            r.yb_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[49], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[50]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[50];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 50];
                            }

                            r.ac_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[50], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[51]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[51];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 51];
                            }

                            r.bc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[51], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[52]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[52];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 52];
                            }

                            r.cc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[52], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[53]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[53];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 53];
                            }

                            r.dc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[53], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[54]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[54];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 54];
                            }

                            r.ec_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[54], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[55]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[55];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 55];
                            }

                            r.fc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[55], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[56]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[56];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 56];
                            }

                            r.gc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[56], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[57]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[57];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 57];
                            }

                            r.hc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[57], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[58]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[58];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 58];
                            }

                            r.ic_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[58], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[59]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[59];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 59];
                            }

                            r.jc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[59], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[60]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[60];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 60];
                            }

                            r.kc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[60], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[61]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[61];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 61];
                            }

                            r.lc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[61], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[62]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[62];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 62];
                            }

                            r.mc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[62], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[63]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[63];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 63];
                            }

                            r.nc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[63], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[64]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[64];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 64];
                            }

                            r.oc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[64], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[65]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[65];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 65];
                            }

                            r.pc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[65], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[66]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[66];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 66];
                            }

                            r.qc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[66], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[67]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[67];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 67];
                            }

                            r.rc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[67], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[68]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[68];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 68];
                            }

                            r.sc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[68], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[69]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[69];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 69];
                            }

                            r.tc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[69], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[70]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[70];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 70];
                            }

                            r.uc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[70], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[71]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[71];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 71];
                            }

                            r.vc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[71], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[72]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[72];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 72];
                            }

                            r.wc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[72], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[73]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[73];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 73];
                            }

                            r.xc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[73], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[74]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[74];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 74];
                            }

                            r.yc_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[74], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[75]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[75];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 75];
                            }

                            r.ad_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[75], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[76]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[76];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 76];
                            }

                            r.bd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[76], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[77]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[77];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 77];
                            }

                            r.cd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[77], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[78]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[78];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 78];
                            }

                            r.dd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[78], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[79]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[79];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 79];
                            }

                            r.ed_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[79], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[80]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[80];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 80];
                            }

                            r.fd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[80], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[81]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[81];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 81];
                            }

                            r.gd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[81], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[82]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[82];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 82];
                            }

                            r.hd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[82], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[83]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[83];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 83];
                            }

                            r.id_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[83], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[84]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[84];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 84];
                            }

                            r.jd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[84], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[85]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[85];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 85];
                            }

                            r.kd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[85], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[86]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[86];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 86];
                            }

                            r.ld_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[86], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[87]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[87];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 87];
                            }

                            r.md_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[87], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[88]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[88];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 88];
                            }

                            r.nd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[88], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[89]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[89];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 89];
                            }

                            r.od_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[89], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[90]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[90];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 90];
                            }

                            r.pd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[90], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[91]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[91];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 91];
                            }

                            r.qd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[91], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[92]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[92];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 92];
                            }

                            r.rd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[92], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[93]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[93];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 93];
                            }

                            r.sd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[93], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[94]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[94];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 94];
                            }

                            r.td_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[94], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[95]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[95];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 95];
                            }

                            r.ud_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[95], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[96]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[96];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 96];
                            }

                            r.vd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[96], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[97]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[97];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 97];
                            }

                            r.wd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[97], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[98]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[98];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 98];
                            }

                            r.xd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[98], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[99]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[99];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 99];
                            }

                            r.yd_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[99], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[100]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[100];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 100];
                            }

                            r.ae_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[100], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[101]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[101];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 101];
                            }

                            r.be_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[101], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[102]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[102];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 102];
                            }

                            r.ce_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[102], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[103]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[103];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 103];
                            }

                            r.de_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[103], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[104]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[104];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 104];
                            }

                            r.ee_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[104], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[105]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[105];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 105];
                            }

                            r.fe_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[105], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[106]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[106];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 106];
                            }

                            r.ge_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[106], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[107]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[107];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 107];
                            }

                            r.he_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[107], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[108]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[108];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 108];
                            }

                            r.ie_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[108], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[109]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[109];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 109];
                            }

                            r.je_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[109], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[110]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[110];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 110];
                            }

                            r.ke_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[110], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[111]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[111];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 111];
                            }

                            r.le_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[111], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[112]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[112];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 112];
                            }

                            r.me_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[112], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[113]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[113];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 113];
                            }

                            r.ne_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[113], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[114]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[114];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 114];
                            }

                            r.oe_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[114], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[115]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[115];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 115];
                            }

                            r.pe_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[115], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[116]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[116];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 116];
                            }

                            r.qe_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[116], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[117]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[117];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 117];
                            }

                            r.re_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[117], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[118]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[118];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 118];
                            }

                            r.se_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[118], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[119]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[119];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 119];
                            }

                            r.te_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[119], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[120]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[120];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 120];
                            }

                            r.ue_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[120], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[121]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[121];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 121];
                            }

                            r.ve_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[121], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[122]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[122];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 122];
                            }

                            r.we_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[122], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[123]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[123];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 123];
                            }

                            r.xe_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[123], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[124]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[124];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 124];
                            }

                            r.ye_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[124], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[125]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[125];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 125];
                            }

                            r.af_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[125], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[126]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[126];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 126];
                            }

                            r.bf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[126], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[127]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[127];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 127];
                            }

                            r.cf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[127], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[128]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[128];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 128];
                            }

                            r.df_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[128], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[129]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[129];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 129];
                            }

                            r.ef_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[129], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[130]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[130];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 130];
                            }

                            r.ff_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[130], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[131]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[131];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 131];
                            }

                            r.gf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[131], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[132]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[132];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 132];
                            }

                            r.hf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[132], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[133]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[133];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 133];
                            }

                            r.if_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[133], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[134]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[134];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 134];
                            }

                            r.jf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[134], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[135]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[135];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 135];
                            }

                            r.kf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[135], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[136]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[136];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 136];
                            }

                            r.lf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[136], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[137]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[137];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 137];
                            }

                            r.mf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[137], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[138]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[138];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 138];
                            }

                            r.nf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[138], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[139]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[139];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 139];
                            }

                            r.of_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[139], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[140]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[140];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 140];
                            }

                            r.pf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[140], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[141]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[141];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 141];
                            }

                            r.qf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[141], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[142]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[142];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 142];
                            }

                            r.rf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[142], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[143]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[143];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 143];
                            }

                            r.sf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[143], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[144]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[144];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 144];
                            }

                            r.tf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[144], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[145]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[145];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 145];
                            }

                            r.uf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[145], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[146]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[146];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 146];
                            }

                            r.vf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[146], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[147]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[147];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 147];
                            }

                            r.wf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[147], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[148]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[148];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 148];
                            }

                            r.xf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[148], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[149]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[149];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 149];
                            }

                            r.yf_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[149], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[150]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[150];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 150];
                            }

                            r.ag_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[150], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[151]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[151];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 151];
                            }

                            r.bg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[151], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[152]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[152];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 152];
                            }

                            r.cg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[152], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[153]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[153];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 153];
                            }

                            r.dg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[153], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[154]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[154];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 154];
                            }

                            r.eg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[154], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[155]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[155];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 155];
                            }

                            r.fg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[155], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[156]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[156];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 156];
                            }

                            r.gg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[156], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[157]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[157];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 157];
                            }

                            r.hg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[157], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[158]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[158];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 158];
                            }

                            r.ig_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[158], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[159]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[159];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 159];
                            }

                            r.jg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[159], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[160]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[160];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 160];
                            }

                            r.kg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[160], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[161]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[161];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 161];
                            }

                            r.lg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[161], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[162]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[162];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 162];
                            }

                            r.mg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[162], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[163]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[163];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 163];
                            }

                            r.ng_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[163], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[164]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[164];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 164];
                            }

                            r.og_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[164], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[165]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[165];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 165];
                            }

                            r.pg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[165], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[166]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[166];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 166];
                            }

                            r.qg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[166], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[167]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[167];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 167];
                            }

                            r.rg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[167], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[168]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[168];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 168];
                            }

                            r.sg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[168], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[169]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[169];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 169];
                            }

                            r.tg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[169], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[170]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[170];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 170];
                            }

                            r.ug_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[170], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[171]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[171];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 171];
                            }

                            r.vg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[171], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[172]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[172];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 172];
                            }

                            r.wg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[172], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[173]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[173];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 173];
                            }

                            r.xg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[173], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[174]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[174];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 174];
                            }

                            r.yg_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[174], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[175]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[175];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 175];
                            }

                            r.ah_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[175], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[176]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[176];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 176];
                            }

                            r.bh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[176], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[177]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[177];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 177];
                            }

                            r.ch_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[177], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[178]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[178];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 178];
                            }

                            r.dh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[178], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[179]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[179];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 179];
                            }

                            r.eh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[179], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[180]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[180];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 180];
                            }

                            r.fh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[180], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[181]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[181];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 181];
                            }

                            r.gh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[181], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[182]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[182];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 182];
                            }

                            r.hh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[182], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[183]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[183];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 183];
                            }

                            r.ih_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[183], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[184]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[184];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 184];
                            }

                            r.jh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[184], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[185]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[185];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 185];
                            }

                            r.kh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[185], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[186]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[186];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 186];
                            }

                            r.lh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[186], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[187]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[187];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 187];
                            }

                            r.mh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[187], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[188]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[188];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 188];
                            }

                            r.nh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[188], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[189]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[189];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 189];
                            }

                            r.oh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[189], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[190]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[190];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 190];
                            }

                            r.ph_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[190], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[191]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[191];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 191];
                            }

                            r.qh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[191], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[192]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[192];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 192];
                            }

                            r.rh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[192], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[193]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[193];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 193];
                            }

                            r.sh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[193], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[194]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[194];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 194];
                            }

                            r.th_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[194], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[195]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[195];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 195];
                            }

                            r.uh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[195], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[196]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[196];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 196];
                            }

                            r.vh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[196], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[197]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[197];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 197];
                            }

                            r.wh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[197], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[198]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[198];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 198];
                            }

                            r.xh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[198], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[199]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[199];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 199];
                            }

                            r.yh_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[199], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[200]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[200];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 200];
                            }

                            r.ai_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[200], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[201]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[201];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 201];
                            }

                            r.bi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[201], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[202]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[202];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 202];
                            }

                            r.ci_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[202], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[203]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[203];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 203];
                            }

                            r.di_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[203], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[204]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[204];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 204];
                            }

                            r.ei_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[204], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[205]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[205];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 205];
                            }

                            r.fi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[205], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[206]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[206];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 206];
                            }

                            r.gi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[206], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[207]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[207];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 207];
                            }

                            r.hi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[207], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[208]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[208];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 208];
                            }

                            r.ii_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[208], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[209]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[209];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 209];
                            }

                            r.ji_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[209], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[210]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[210];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 210];
                            }

                            r.ki_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[210], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[211]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[211];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 211];
                            }

                            r.li_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[211], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[212]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[212];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 212];
                            }

                            r.mi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[212], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[213]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[213];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 213];
                            }

                            r.ni_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[213], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[214]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[214];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 214];
                            }

                            r.oi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[214], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[215]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[215];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 215];
                            }

                            r.pi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[215], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[216]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[216];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 216];
                            }

                            r.qi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[216], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[217]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[217];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 217];
                            }

                            r.ri_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[217], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[218]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[218];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 218];
                            }

                            r.si_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[218], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[219]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[219];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 219];
                            }

                            r.ti_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[219], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[220]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[220];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 220];
                            }

                            r.ui_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[220], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[221]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[221];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 221];
                            }

                            r.vi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[221], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[222]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[222];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 222];
                            }

                            r.wi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[222], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[223]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[223];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 223];
                            }

                            r.xi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[223], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[224]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[224];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 224];
                            }

                            r.yi_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[224], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[225]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[225];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 225];
                            }

                            r.aj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[225], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[226]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[226];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 226];
                            }

                            r.bj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[226], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[227]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[227];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 227];
                            }

                            r.cj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[227], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[228]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[228];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 228];
                            }

                            r.dj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[228], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[229]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[229];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 229];
                            }

                            r.ej_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[229], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[230]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[230];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 230];
                            }

                            r.fj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[230], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[231]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[231];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 231];
                            }

                            r.gj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[231], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[232]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[232];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 232];
                            }

                            r.hj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[232], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[233]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[233];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 233];
                            }

                            r.ij_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[233], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[234]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[234];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 234];
                            }

                            r.jj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[234], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[235]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[235];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 235];
                            }

                            r.kj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[235], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[236]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[236];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 236];
                            }

                            r.lj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[236], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[237]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[237];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 237];
                            }

                            r.mj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[237], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[238]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[238];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 238];
                            }

                            r.nj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[238], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[239]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[239];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 239];
                            }

                            r.oj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[239], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[240]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[240];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 240];
                            }

                            r.pj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[240], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[241]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[241];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 241];
                            }

                            r.qj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[241], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[242]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[242];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 242];
                            }

                            r.rj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[242], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[243]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[243];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 243];
                            }

                            r.sj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[243], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[244]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[244];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 244];
                            }

                            r.tj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[244], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[245]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[245];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 245];
                            }

                            r.uj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[245], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[246]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[246];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 246];
                            }

                            r.vj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[246], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[247]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[247];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 247];
                            }

                            r.wj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[247], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[248]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[248];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 248];
                            }

                            r.xj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[248], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[249]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[249];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 249];
                            }

                            r.yj_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[249], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[250]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[250];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 250];
                            }

                            r.ak_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[250], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[251]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[251];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 251];
                            }

                            r.bk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[251], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[252]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[252];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 252];
                            }

                            r.ck_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[252], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[253]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[253];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 253];
                            }

                            r.dk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[253], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[254]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[254];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 254];
                            }

                            r.ek_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[254], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[255]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[255];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 255];
                            }

                            r.fk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[255], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[256]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[256];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 256];
                            }

                            r.gk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[256], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[257]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[257];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 257];
                            }

                            r.hk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[257], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[258]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[258];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 258];
                            }

                            r.ik_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[258], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[259]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[259];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 259];
                            }

                            r.jk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[259], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[260]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[260];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 260];
                            }

                            r.kk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[260], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[261]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[261];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 261];
                            }

                            r.lk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[261], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[262]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[262];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 262];
                            }

                            r.mk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[262], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[263]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[263];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 263];
                            }

                            r.nk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[263], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[264]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[264];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 264];
                            }

                            r.ok_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[264], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[265]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[265];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 265];
                            }

                            r.pk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[265], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[266]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[266];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 266];
                            }

                            r.qk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[266], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[267]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[267];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 267];
                            }

                            r.rk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[267], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[268]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[268];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 268];
                            }

                            r.sk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[268], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[269]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[269];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 269];
                            }

                            r.tk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[269], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[270]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[270];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 270];
                            }

                            r.uk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[270], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[271]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[271];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 271];
                            }

                            r.vk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[271], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[272]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[272];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 272];
                            }

                            r.wk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[272], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[273]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[273];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 273];
                            }

                            r.xk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[273], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[274]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[274];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 274];
                            }

                            r.yk_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[274], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[275]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[275];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 275];
                            }

                            r.al_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[275], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[276]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[276];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 276];
                            }

                            r.bl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[276], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[277]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[277];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 277];
                            }

                            r.cl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[277], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[278]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[278];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 278];
                            }

                            r.dl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[278], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[279]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[279];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 279];
                            }

                            r.el_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[279], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[280]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[280];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 280];
                            }

                            r.fl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[280], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[281]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[281];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 281];
                            }

                            r.gl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[281], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[282]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[282];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 282];
                            }

                            r.hl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[282], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[283]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[283];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 283];
                            }

                            r.il_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[283], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[284]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[284];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 284];
                            }

                            r.jl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[284], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[285]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[285];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 285];
                            }

                            r.kl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[285], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[286]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[286];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 286];
                            }

                            r.ll_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[286], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[287]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[287];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 287];
                            }

                            r.ml_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[287], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[288]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[288];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 288];
                            }

                            r.nl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[288], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[289]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[289];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 289];
                            }

                            r.ol_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[289], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[290]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[290];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 290];
                            }

                            r.pl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[290], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[291]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[291];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 291];
                            }

                            r.ql_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[291], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[292]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[292];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 292];
                            }

                            r.rl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[292], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[293]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[293];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 293];
                            }

                            r.sl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[293], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[294]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[294];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 294];
                            }

                            r.tl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[294], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[295]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[295];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 295];
                            }

                            r.ul_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[295], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[296]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[296];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 296];
                            }

                            r.vl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[296], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[297]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[297];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 297];
                            }

                            r.wl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[297], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[298]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[298];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 298];
                            }

                            r.xl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[298], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[299]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[299];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 299];
                            }

                            r.yl_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[299], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[300]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[300];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 300];
                            }

                            r.am_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[300], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[301]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[301];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 301];
                            }

                            r.bm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[301], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[302]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[302];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 302];
                            }

                            r.cm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[302], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[303]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[303];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 303];
                            }

                            r.dm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[303], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[304]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[304];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 304];
                            }

                            r.em_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[304], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[305]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[305];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 305];
                            }

                            r.fm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[305], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[306]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[306];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 306];
                            }

                            r.gm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[306], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[307]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[307];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 307];
                            }

                            r.hm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[307], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[308]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[308];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 308];
                            }

                            r.im_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[308], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[309]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[309];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 309];
                            }

                            r.jm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[309], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[310]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[310];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 310];
                            }

                            r.km_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[310], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[311]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[311];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 311];
                            }

                            r.lm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[311], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[312]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[312];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 312];
                            }

                            r.mm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[312], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[313]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[313];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 313];
                            }

                            r.nm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[313], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[314]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[314];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 314];
                            }

                            r.om_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[314], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[315]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[315];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 315];
                            }

                            r.pm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[315], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[316]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[316];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 316];
                            }

                            r.qm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[316], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[317]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[317];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 317];
                            }

                            r.rm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[317], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[318]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[318];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 318];
                            }

                            r.sm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[318], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[319]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[319];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 319];
                            }

                            r.tm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[319], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[320]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[320];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 320];
                            }

                            r.um_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[320], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[321]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[321];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 321];
                            }

                            r.vm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[321], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[322]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[322];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 322];
                            }

                            r.wm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[322], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[323]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[323];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 323];
                            }

                            r.xm_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[323], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[324]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[324];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 324];
                            }

                            r.ym_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[324], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[325]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[325];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 325];
                            }

                            r.an_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[325], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[326]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[326];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 326];
                            }

                            r.bn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[326], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[327]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[327];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 327];
                            }

                            r.cn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[327], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[328]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[328];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 328];
                            }

                            r.dn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[328], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[329]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[329];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 329];
                            }

                            r.en_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[329], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[330]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[330];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 330];
                            }

                            r.fn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[330], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[331]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[331];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 331];
                            }

                            r.gn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[331], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[332]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[332];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 332];
                            }

                            r.hn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[332], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[333]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[333];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 333];
                            }

                            r.in_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[333], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[334]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[334];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 334];
                            }

                            r.jn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[334], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[335]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[335];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 335];
                            }

                            r.kn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[335], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[336]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[336];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 336];
                            }

                            r.ln_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[336], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[337]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[337];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 337];
                            }

                            r.mn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[337], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[338]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[338];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 338];
                            }

                            r.nn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[338], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[339]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[339];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 339];
                            }

                            r.on_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[339], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[340]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[340];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 340];
                            }

                            r.pn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[340], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[341]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[341];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 341];
                            }

                            r.qn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[341], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[342]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[342];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 342];
                            }

                            r.rn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[342], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[343]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[343];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 343];
                            }

                            r.sn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[343], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[344]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[344];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 344];
                            }

                            r.tn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[344], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[345]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[345];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 345];
                            }

                            r.un_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[345], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[346]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[346];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 346];
                            }

                            r.vn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[346], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[347]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[347];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 347];
                            }

                            r.wn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[347], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[348]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[348];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 348];
                            }

                            r.xn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[348], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[349]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[349];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 349];
                            }

                            r.yn_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[349], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[350]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[350];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 350];
                            }

                            r.ao_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[350], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[351]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[351];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 351];
                            }

                            r.bo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[351], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[352]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[352];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 352];
                            }

                            r.co_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[352], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[353]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[353];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 353];
                            }

                            r.do_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[353], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[354]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[354];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 354];
                            }

                            r.eo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[354], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[355]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[355];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 355];
                            }

                            r.fo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[355], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[356]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[356];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 356];
                            }

                            r.go_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[356], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[357]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[357];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 357];
                            }

                            r.ho_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[357], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[358]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[358];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 358];
                            }

                            r.io_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[358], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[359]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[359];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 359];
                            }

                            r.jo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[359], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[360]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[360];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 360];
                            }

                            r.ko_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[360], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[361]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[361];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 361];
                            }

                            r.lo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[361], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[362]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[362];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 362];
                            }

                            r.mo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[362], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[363]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[363];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 363];
                            }

                            r.no_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[363], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[364]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[364];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 364];
                            }

                            r.oo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[364], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[365]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[365];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 365];
                            }

                            r.po_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[365], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[366]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[366];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 366];
                            }

                            r.qo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[366], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[367]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[367];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 367];
                            }

                            r.ro_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[367], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[368]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[368];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 368];
                            }

                            r.so_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[368], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[369]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[369];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 369];
                            }

                            r.to_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[369], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[370]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[370];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 370];
                            }

                            r.uo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[370], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[371]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[371];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 371];
                            }

                            r.vo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[371], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[372]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[372];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 372];
                            }

                            r.wo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[372], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[373]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[373];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 373];
                            }

                            r.xo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[373], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[374]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[374];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 374];
                            }

                            r.yo_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[374], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[375]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[375];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 375];
                            }

                            r.ap_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[375], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[376]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[376];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 376];
                            }

                            r.bp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[376], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[377]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[377];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 377];
                            }

                            r.cp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[377], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[378]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[378];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 378];
                            }

                            r.dp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[378], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[379]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[379];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 379];
                            }

                            r.ep_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[379], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[380]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[380];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 380];
                            }

                            r.fp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[380], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[381]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[381];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 381];
                            }

                            r.gp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[381], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[382]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[382];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 382];
                            }

                            r.hp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[382], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[383]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[383];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 383];
                            }

                            r.ip_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[383], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[384]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[384];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 384];
                            }

                            r.jp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[384], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[385]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[385];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 385];
                            }

                            r.kp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[385], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[386]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[386];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 386];
                            }

                            r.lp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[386], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[387]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[387];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 387];
                            }

                            r.mp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[387], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[388]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[388];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 388];
                            }

                            r.np_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[388], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[389]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[389];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 389];
                            }

                            r.op_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[389], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[390]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[390];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 390];
                            }

                            r.pp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[390], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[391]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[391];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 391];
                            }

                            r.qp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[391], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[392]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[392];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 392];
                            }

                            r.rp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[392], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[393]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[393];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 393];
                            }

                            r.sp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[393], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[394]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[394];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 394];
                            }

                            r.tp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[394], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[395]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[395];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 395];
                            }

                            r.up_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[395], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[396]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[396];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 396];
                            }

                            r.vp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[396], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[397]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[397];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 397];
                            }

                            r.wp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[397], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[398]) {
                            if (firstCache) {
                                initCache = true;
                                firstCache = false;
                            } else {
                                initCache = false;
                            }

                            b = isCached[398];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 398];
                            }

                            r.xp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[398], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                initCache, score);
                        }

                        if (learners[399]) {
                            b = isCached[399];
                            loop_ub = useObsForLearner.size(0);
                            b_useObsForLearner.set_size(useObsForLearner.size(0));
                            for (i = 0; i < loop_ub; i++) {
                                b_useObsForLearner[i] = useObsForLearner[i +
                                                                         useObsForLearner.size(0) * 399];
                            }

                            r.yp_init();
                            predictOneWithCache(X, cachedScore, cachedWeights, &r,
                                                learnerWeights[399], &b, classNames,
                                                classlogicalindices, b_useObsForLearner,
                                                firstCache, score);
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
