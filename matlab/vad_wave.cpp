//
// File: vad_wave.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "vad_wave.h"
#include "abs.h"
#include "eml_i64relops.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [ostarts, oends] = vad_wave(array, starts, ends)
//
// Arguments    : const coder::array<double, 1U> &array
//                const coder::array<long long, 1U> &starts
//                const coder::array<long long, 1U> &ends
//                coder::array<long long, 1U> &ostarts
//                coder::array<long long, 1U> &oends
// Return Type  : void
//
void vad_wave(const coder::array<double, 1U> &array,
              const coder::array<long long, 1U> &starts,
              const coder::array<long long, 1U> &ends,
              coder::array<long long, 1U> &ostarts,
              coder::array<long long, 1U> &oends) {
    coder::array<long long, 1U> b_ostarts;
    double bufferHeight;
    long long k;
    long long qY;
    int i;
    int loop_ub;
    //  按波形重新分段
    // 'vad_wave:3' bufferHeight = min(length(starts), length(ends));
    bufferHeight = coder::internal::minimum2(
            static_cast<double>(starts.size(0)), static_cast<double>(ends.size(0)));
    // 'vad_wave:4' ostarts = zeros(bufferHeight, 1, 'int64');
    ostarts.set_size(static_cast<int>(bufferHeight));
    loop_ub = static_cast<int>(bufferHeight);
    for (i = 0; i < loop_ub; i++) {
        ostarts[i] = 0LL;
    }
    // 'vad_wave:5' oends = zeros(bufferHeight, 1, 'int64');
    oends.set_size(static_cast<int>(bufferHeight));
    loop_ub = static_cast<int>(bufferHeight);
    for (i = 0; i < loop_ub; i++) {
        oends[i] = 0LL;
    }
    // 'vad_wave:6' coder.varsize('ostarts');
    // 'vad_wave:7' coder.varsize('oends');
    // 'vad_wave:8' k = int64(1);
    k = 1LL;
    // 'vad_wave:10' for i = 1:bufferHeight
    i = static_cast<int>(bufferHeight);
    for (int b_i = 0; b_i < i; b_i++) {
        double count;
        long long lowb;
        long long q0;
        int i1;
        int i2;
        int islow;
        // 'vad_wave:12' if (k > length(oends))
        if (coder::eml_i64relops(k, static_cast<double>(oends.size(0)))) {
            // 'vad_wave:13' ostarts = [ostarts; zeros(k, 1, 'int64')];
            i1 = ostarts.size(0);
            ostarts.set_size(ostarts.size(0) + static_cast<int>(k));
            loop_ub = static_cast<int>(k);
            for (i2 = 0; i2 < loop_ub; i2++) {
                ostarts[i1 + i2] = 0LL;
            }
            // 'vad_wave:14' oends = [oends; zeros(k, 1, 'int64')];
            i1 = oends.size(0);
            oends.set_size(oends.size(0) + static_cast<int>(k));
            loop_ub = static_cast<int>(k);
            for (i2 = 0; i2 < loop_ub; i2++) {
                oends[i1 + i2] = 0LL;
            }
        }
        // 'vad_wave:17' ostarts(k) = starts(i);
        ostarts[static_cast<int>(k) - 1] = starts[b_i];
        // 'vad_wave:18' islow = 0;
        islow = 0;
        // 'vad_wave:19' count = 0;
        count = 0.0;
        // 'vad_wave:20' lowb = int64(-1);
        lowb = -1LL;
        // 'vad_wave:22' for j = starts(i) + 1:ends(i)
        q0 = starts[b_i];
        if (q0 > 9223372036854775806LL) {
            qY = MAX_int64_T;
        } else {
            qY = q0 + 1LL;
        }
        for (long long j = qY; j <= ends[b_i]; j++) {
            double d;
            boolean_T guard1 = false;
            // 'vad_wave:24' if array(j) - array(j - 1) < -0.01
            if (j < -9223372036854775807LL) {
                qY = MIN_int64_T;
            } else {
                qY = j - 1LL;
            }
            d = array[static_cast<int>(j) - 1];
            if (d - array[static_cast<int>(qY) - 1] < -0.01) {
                // 'vad_wave:25' islow = 1;
                islow = 1;
            }
            // 'vad_wave:28' if islow == 1 && abs(array(j) - array(j - 1)) <=
            // 0.01
            guard1 = false;
            if (islow == 1) {
                if (j < -9223372036854775807LL) {
                    qY = MIN_int64_T;
                } else {
                    qY = j - 1LL;
                }
                if (coder::b_abs(d - array[static_cast<int>(qY) - 1]) <= 0.01) {
                    // 'vad_wave:29' count = count + 1;
                    count++;
                    // 'vad_wave:31' if (lowb == int64(-1))
                    if (lowb == -1LL) {
                        // 'vad_wave:32' lowb = j;
                        lowb = j;
                    }
                } else {
                    guard1 = true;
                }
            } else {
                guard1 = true;
            }
            if (guard1 && (islow == 1)) {
                // 'vad_wave:35' elseif islow == 1
                // 连续下降的特殊情况
                // 'vad_wave:37' if array(j) < array(j - 1)
                if (j < -9223372036854775807LL) {
                    qY = MIN_int64_T;
                } else {
                    qY = j - 1LL;
                }
                if (d < array[static_cast<int>(qY) - 1]) {
                    // 后一个点抬升
                    // 'vad_wave:39' if (j + 1 < ends(i) && array(j + 1) -
                    // array(j) <= 0.01)
                    if (j > 9223372036854775806LL) {
                        qY = MAX_int64_T;
                    } else {
                        qY = j + 1LL;
                    }
                    if (qY < ends[b_i]) {
                        if (j > 9223372036854775806LL) {
                            qY = MAX_int64_T;
                        } else {
                            qY = j + 1LL;
                        }
                        if (array[static_cast<int>(qY) - 1] - d <= 0.01) {
                            // 'vad_wave:40' lowb = j;
                            lowb = j;
                            // j+1;
                            // %lowb针对连续下降不断往后推，直到碰到抬升点，lowb记录的是最后一个非上升点，波谷的前一个点
                        }
                    }
                } else {
                    // 'vad_wave:43' else
                    // 'vad_wave:45' if (count >= 3)
                    if (count >= 3.0) {
                        // 'vad_wave:47' if (k > length(oends))
                        if (coder::eml_i64relops(
                                k, static_cast<double>(oends.size(0)))) {
                            // 'vad_wave:48' ostarts = [ostarts; zeros(k, 1,
                            // 'int64')];
                            i1 = ostarts.size(0);
                            ostarts.set_size(ostarts.size(0) +
                                             static_cast<int>(k));
                            loop_ub = static_cast<int>(k);
                            for (i2 = 0; i2 < loop_ub; i2++) {
                                ostarts[i1 + i2] = 0LL;
                            }
                            // 'vad_wave:49' oends = [oends; zeros(k, 1,
                            // 'int64')];
                            i1 = oends.size(0);
                            oends.set_size(oends.size(0) + static_cast<int>(k));
                            loop_ub = static_cast<int>(k);
                            for (i2 = 0; i2 < loop_ub; i2++) {
                                oends[i1 + i2] = 0LL;
                            }
                        }
                        // 'vad_wave:52' oends(k) = lowb;
                        oends[static_cast<int>(k) - 1] = lowb;
                        // 'vad_wave:53' k = k + 1;
                        if (k > 9223372036854775806LL) {
                            qY = MAX_int64_T;
                        } else {
                            qY = k + 1LL;
                        }
                        k = qY;
                        // 'vad_wave:55' if (k > length(oends))
                        if (coder::eml_i64relops(
                                qY, static_cast<double>(oends.size(0)))) {
                            // 'vad_wave:56' ostarts = [ostarts; zeros(k, 1,
                            // 'int64')];
                            i1 = ostarts.size(0);
                            ostarts.set_size(ostarts.size(0) +
                                             static_cast<int>(qY));
                            loop_ub = static_cast<int>(qY);
                            for (i2 = 0; i2 < loop_ub; i2++) {
                                ostarts[i1 + i2] = 0LL;
                            }
                            // 'vad_wave:57' oends = [oends; zeros(k, 1,
                            // 'int64')];
                            i1 = oends.size(0);
                            oends.set_size(oends.size(0) +
                                           static_cast<int>(qY));
                            loop_ub = static_cast<int>(qY);
                            for (i2 = 0; i2 < loop_ub; i2++) {
                                oends[i1 + i2] = 0LL;
                            }
                        }
                        // 'vad_wave:60' ostarts(k) = j - 1;
                        if (j < -9223372036854775807LL) {
                            q0 = MIN_int64_T;
                        } else {
                            q0 = j - 1LL;
                        }
                        ostarts[static_cast<int>(qY) - 1] = q0;
                        // 'vad_wave:61' islow = 0;
                        islow = 0;
                        // 'vad_wave:62' lowb = int64(-1);
                        lowb = -1LL;
                    }
                    // 'vad_wave:65' count = 0;
                    count = 0.0;
                }
            }
        }
        // 'vad_wave:72' if (k > length(oends))
        if (coder::eml_i64relops(k, static_cast<double>(oends.size(0)))) {
            // 'vad_wave:73' ostarts = [ostarts; zeros(k, 1, 'int64')];
            i1 = ostarts.size(0);
            ostarts.set_size(ostarts.size(0) + static_cast<int>(k));
            loop_ub = static_cast<int>(k);
            for (i2 = 0; i2 < loop_ub; i2++) {
                ostarts[i1 + i2] = 0LL;
            }
            // 'vad_wave:74' oends = [oends; zeros(k, 1, 'int64')];
            i1 = oends.size(0);
            oends.set_size(oends.size(0) + static_cast<int>(k));
            loop_ub = static_cast<int>(k);
            for (i2 = 0; i2 < loop_ub; i2++) {
                oends[i1 + i2] = 0LL;
            }
        }
        // 'vad_wave:77' oends(k) = ends(i);
        oends[static_cast<int>(k) - 1] = ends[b_i];
        // 'vad_wave:78' k = k + 1;
        if (k > 9223372036854775806LL) {
            qY = MAX_int64_T;
        } else {
            qY = k + 1LL;
        }
        k = qY;
    }
    // 'vad_wave:82' ostarts = ostarts(1:k - 1);
    if (k < -9223372036854775807LL) {
        qY = MIN_int64_T;
    } else {
        qY = k - 1LL;
    }
    if (1LL > qY) {
        loop_ub = 0;
    } else {
        loop_ub = static_cast<int>(qY);
    }
    b_ostarts.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
        b_ostarts[i] = ostarts[i];
    }
    ostarts.set_size(b_ostarts.size(0));
    loop_ub = b_ostarts.size(0);
    for (i = 0; i < loop_ub; i++) {
        ostarts[i] = b_ostarts[i];
    }
    // 'vad_wave:83' oends = oends(1:k - 1);
    if (k < -9223372036854775807LL) {
        qY = MIN_int64_T;
    } else {
        qY = k - 1LL;
    }
    if (1LL > qY) {
        loop_ub = 0;
    } else {
        loop_ub = static_cast<int>(qY);
    }
    b_ostarts.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
        b_ostarts[i] = oends[i];
    }
    oends.set_size(b_ostarts.size(0));
    loop_ub = b_ostarts.size(0);
    for (i = 0; i < loop_ub; i++) {
        oends[i] = b_ostarts[i];
    }
}

//
// File trailer for vad_wave.cpp
//
// [EOF]
//
