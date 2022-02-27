//
// File: vad_length_filter.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "vad_length_filter.h"
#include "eml_i64relops.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [ostarts, oends] = vad_length_filter(starts, ends, min_len, max_len)
//
// Arguments    : const coder::array<long long, 1U> &starts
//                const coder::array<long long, 1U> &ends
//                double min_len
//                double max_len
//                coder::array<long long, 1U> &ostarts
//                coder::array<long long, 1U> &oends
// Return Type  : void
//
void vad_length_filter(const coder::array<long long, 1U> &starts,
                       const coder::array<long long, 1U> &ends, double min_len,
                       double max_len, coder::array<long long, 1U> &ostarts,
                       coder::array<long long, 1U> &oends) {
    coder::array<long long, 1U> b_ostarts;
    double bufferHeight;
    long long k;
    int i;
    int loop_ub;
    // vad_length_filter: stars 开始 ends 结束 min_len 最小长度 max_len 最大长度
    // 'vad_length_filter:3' k = int64(0);
    k = 0LL;
    // 'vad_length_filter:4' bufferHeight = min(length(starts), length(ends));
    bufferHeight = coder::internal::minimum2(
            static_cast<double>(starts.size(0)), static_cast<double>(ends.size(0)));
    // 'vad_length_filter:5' ostarts = zeros(bufferHeight, 1, 'int64');
    ostarts.set_size(static_cast<int>(bufferHeight));
    loop_ub = static_cast<int>(bufferHeight);
    for (i = 0; i < loop_ub; i++) {
        ostarts[i] = 0LL;
    }
    // 'vad_length_filter:6' oends = zeros(bufferHeight, 1, 'int64');
    oends.set_size(static_cast<int>(bufferHeight));
    loop_ub = static_cast<int>(bufferHeight);
    for (i = 0; i < loop_ub; i++) {
        oends[i] = 0LL;
    }
    // 'vad_length_filter:7' coder.varsize('ostarts');
    // 'vad_length_filter:8' coder.varsize('oends');
    // 'vad_length_filter:10' for i = 1:min(length(starts), length(ends))
    i = static_cast<int>(
            coder::internal::minimum2(static_cast<double>(starts.size(0)),
                                      static_cast<double>(ends.size(0))));
    for (int b_i = 0; b_i < i; b_i++) {
        long long q0;
        long long q1;
        // 'vad_length_filter:11' len = ends(i) - starts(i) + 1;
        q0 = ends[b_i];
        q1 = starts[b_i];
        if ((q0 >= 0LL) && (q1 < q0 - MAX_int64_T)) {
            q0 = MAX_int64_T;
        } else if ((q0 < 0LL) && (q1 > q0 - MIN_int64_T)) {
            q0 = MIN_int64_T;
        } else {
            q0 -= q1;
        }
        if (q0 > 9223372036854775806LL) {
            q0 = MAX_int64_T;
        } else {
            q0++;
        }
        //  小于限定长度或大于限定长度的都抛弃
        // 'vad_length_filter:13' if len > min_len && len < max_len
        if (coder::eml_i64relops(q0, min_len) &&
            coder::b_eml_i64relops(q0, max_len)) {
            // 'vad_length_filter:14' k = k + 1;
            if (k > 9223372036854775806LL) {
                q0 = MAX_int64_T;
            } else {
                q0 = k + 1LL;
            }
            k = q0;
            // 'vad_length_filter:15' ostarts(k) = starts(i);
            ostarts[static_cast<int>(q0) - 1] = starts[b_i];
            // 'vad_length_filter:16' oends(k) = ends(i);
            oends[static_cast<int>(q0) - 1] = ends[b_i];
        }
    }
    //  对结果进行裁剪
    // 'vad_length_filter:22' ostarts = ostarts(1:k);
    if (1LL > k) {
        loop_ub = 0;
    } else {
        loop_ub = static_cast<int>(k);
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
    // 'vad_length_filter:23' oends = oends(1:k);
    if (1LL > k) {
        loop_ub = 0;
    } else {
        loop_ub = static_cast<int>(k);
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
// File trailer for vad_length_filter.cpp
//
// [EOF]
//
