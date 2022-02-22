//
// File: vad_wave.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "vad_wave.h"
#include "abs.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [w_starts, w_ends] = vad_wave(array, s_starts, s_ends)
//
// Arguments    : const coder::array<double, 2U> &array
//                const coder::array<double, 2U> &s_starts
//                const coder::array<double, 2U> &s_ends
//                coder::array<double, 2U> &w_starts
//                coder::array<double, 2U> &w_ends
// Return Type  : void
//
void vad_wave(const coder::array<double, 2U> &array,
              const coder::array<double, 2U> &s_starts,
              const coder::array<double, 2U> &s_ends,
              coder::array<double, 2U> &w_starts,
              coder::array<double, 2U> &w_ends) {
    int i;
    int islow;
    unsigned int k;
    //  按波形重新分段
    // 'vad_wave:3' w_starts = zeros(1, length(s_starts));
    w_starts.set_size(1, s_starts.size(1));
    islow = s_starts.size(1);
    for (i = 0; i < islow; i++) {
        w_starts[i] = 0.0;
    }
    // 'vad_wave:4' w_ends = zeros(1, length(s_ends));
    w_ends.set_size(1, s_ends.size(1));
    islow = s_ends.size(1);
    for (i = 0; i < islow; i++) {
        w_ends[i] = 0.0;
    }
    // 'vad_wave:5' coder.varsize('w_starts');
    // 'vad_wave:6' coder.varsize('w_ends');
    // 'vad_wave:7' k = 1;
    k = 1U;
    // 'vad_wave:9' for i = 1:min(length(s_starts), length(s_ends))
    i = static_cast<int>(
            coder::internal::minimum2(static_cast<double>(s_starts.size(1)),
                                      static_cast<double>(s_ends.size(1))));
    for (int b_i = 0; b_i < i; b_i++) {
        double count;
        double d;
        int i1;
        int i2;
        int lowb;
        // 'vad_wave:10' if(k > length(w_ends))
        if (k > static_cast<unsigned int>(w_ends.size(1))) {
            // 'vad_wave:11' w_ends = [w_ends zeros(1, k)];
            islow = static_cast<int>(k);
            i1 = w_ends.size(1);
            w_ends.set_size(w_ends.size(0), w_ends.size(1) + static_cast<int>(k));
            for (i2 = 0; i2 < islow; i2++) {
                w_ends[i1 + i2] = 0.0;
            }
            // 'vad_wave:12' w_starts = [w_starts zeros(1, k)];
            i1 = w_starts.size(1);
            w_starts.set_size(w_starts.size(0),
                              w_starts.size(1) + static_cast<int>(k));
            for (i2 = 0; i2 < islow; i2++) {
                w_starts[i1 + i2] = 0.0;
            }
        }
        // 'vad_wave:14' w_starts(k) = s_starts(i);
        d = s_starts[b_i];
        w_starts[static_cast<int>(k) - 1] = d;
        // 'vad_wave:15' islow = 0;
        islow = 0;
        // 'vad_wave:16' count = 0;
        count = 0.0;
        // 'vad_wave:17' lowb = -1;
        lowb = -1;
        // 'vad_wave:19' for j = s_starts(i) + 1:s_ends(i)
        i1 = static_cast<int>(s_ends[b_i] + (1.0 - (d + 1.0)));
        for (int j = 0; j < i1; j++) {
            double b_j;
            b_j = (s_starts[b_i] + 1.0) + static_cast<double>(j);
            // 'vad_wave:21' if array(j) - array(j - 1) < -0.01
            d = array[static_cast<int>(b_j) - 1];
            if (d - array[static_cast<int>(b_j - 1.0) - 1] < -0.01) {
                // 'vad_wave:22' islow = 1;
                islow = 1;
            }
            // 'vad_wave:25' if islow == 1 && abs(array(j) - array(j - 1)) <= 0.01
            if ((islow == 1) &&
                (coder::b_abs(d - array[static_cast<int>(b_j) - 2]) <= 0.01)) {
                // 'vad_wave:26' count = count + 1;
                count++;
                // 'vad_wave:28' if (lowb == -1)
                if (lowb == -1) {
                    // 'vad_wave:29' lowb = j;
                    lowb = static_cast<int>(b_j);
                }
            } else if (islow == 1) {
                // 'vad_wave:32' elseif islow == 1
                // 连续下降的特殊情况
                // 'vad_wave:34' if array(j) < array(j - 1)
                if (d < array[static_cast<int>(b_j) - 2]) {
                    // 后一个点抬升
                    // 'vad_wave:36' if (j + 1 < s_ends(i) && array(j + 1) - array(j) <=
                    // 0.01)
                    if ((b_j + 1.0 < s_ends[b_i]) &&
                        (array[static_cast<int>(static_cast<unsigned int>(b_j))] - d <=
                         0.01)) {
                        // 'vad_wave:37' lowb = j;
                        lowb = static_cast<int>(b_j);
                        // j+1;
                        // %lowb针对连续下降不断往后推，直到碰到抬升点，lowb记录的是最后一个非上升点，波谷的前一个点
                    }
                } else {
                    // 'vad_wave:40' else
                    // 'vad_wave:42' if (count >= 3)
                    if (count >= 3.0) {
                        int i3;
                        // 'vad_wave:43' if(k > length(w_ends))
                        if (static_cast<int>(k) > w_ends.size(1)) {
                            // 'vad_wave:44' w_ends = [w_ends zeros(1, k)];
                            islow = static_cast<int>(k);
                            i2 = w_ends.size(1);
                            w_ends.set_size(w_ends.size(0),
                                            w_ends.size(1) + static_cast<int>(k));
                            for (i3 = 0; i3 < islow; i3++) {
                                w_ends[i2 + i3] = 0.0;
                            }
                            // 'vad_wave:45' w_starts = [w_starts zeros(1, k)];
                            islow = static_cast<int>(k);
                            i2 = w_starts.size(1);
                            w_starts.set_size(w_starts.size(0),
                                              w_starts.size(1) + static_cast<int>(k));
                            for (i3 = 0; i3 < islow; i3++) {
                                w_starts[i2 + i3] = 0.0;
                            }
                        }
                        // 'vad_wave:47' w_ends(k) = lowb;
                        w_ends[static_cast<int>(k) - 1] = lowb;
                        // 'vad_wave:48' k = k + 1;
                        k++;
                        // 'vad_wave:49' if(k > length(w_ends))
                        if (k > static_cast<unsigned int>(w_ends.size(1))) {
                            // 'vad_wave:50' w_ends = [w_ends zeros(1, k)];
                            islow = static_cast<int>(k);
                            i2 = w_ends.size(1);
                            w_ends.set_size(w_ends.size(0),
                                            w_ends.size(1) + static_cast<int>(k));
                            for (i3 = 0; i3 < islow; i3++) {
                                w_ends[i2 + i3] = 0.0;
                            }
                            // 'vad_wave:51' w_starts = [w_starts zeros(1, k)];
                            islow = static_cast<int>(k);
                            i2 = w_starts.size(1);
                            w_starts.set_size(w_starts.size(0),
                                              w_starts.size(1) + static_cast<int>(k));
                            for (i3 = 0; i3 < islow; i3++) {
                                w_starts[i2 + i3] = 0.0;
                            }
                        }
                        // 'vad_wave:53' w_starts(k) = j - 1;
                        w_starts[static_cast<int>(k) - 1] = b_j - 1.0;
                        // 'vad_wave:54' islow = 0;
                        islow = 0;
                        // 'vad_wave:55' lowb = -1;
                        lowb = -1;
                    }
                    // 'vad_wave:58' count = 0;
                    count = 0.0;
                }
            }
        }
        // 'vad_wave:64' if(k > length(w_ends))
        if (static_cast<int>(k) > w_ends.size(1)) {
            // 'vad_wave:65' w_ends = [w_ends zeros(1, k)];
            islow = static_cast<int>(k);
            i1 = w_ends.size(1);
            w_ends.set_size(w_ends.size(0), w_ends.size(1) + static_cast<int>(k));
            for (i2 = 0; i2 < islow; i2++) {
                w_ends[i1 + i2] = 0.0;
            }
            // 'vad_wave:66' w_starts = [w_starts zeros(1, k)];
            islow = static_cast<int>(k);
            i1 = w_starts.size(1);
            w_starts.set_size(w_starts.size(0),
                              w_starts.size(1) + static_cast<int>(k));
            for (i2 = 0; i2 < islow; i2++) {
                w_starts[i1 + i2] = 0.0;
            }
        }
        // 'vad_wave:68' w_ends(k) = s_ends(i);
        w_ends[static_cast<int>(k) - 1] = s_ends[b_i];
        // 'vad_wave:69' k = k + 1;
        k++;
    }
    // 'vad_wave:73' w_starts = w_starts(1:k - 1);
    if (1 > static_cast<int>(k - 1U)) {
        i = 0;
    } else {
        i = static_cast<int>(k - 1U);
    }
    w_starts.set_size(w_starts.size(0), i);
    // 'vad_wave:74' w_ends = w_ends(1:k - 1);
    if (1 > static_cast<int>(k - 1U)) {
        i = 0;
    } else {
        i = static_cast<int>(k - 1U);
    }
    w_ends.set_size(w_ends.size(0), i);
}

//
// File trailer for vad_wave.cpp
//
// [EOF]
//
