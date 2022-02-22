//
// File: vad_length_filter.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "vad_length_filter.h"
#include "length.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function [fstarts, fends] = vad_length_filter(starts, ends, min_len, max_len)
//
// Arguments    : const coder::array<double, 2U> &starts
//                const coder::array<double, 2U> &ends
//                double min_len
//                double max_len
//                coder::array<double, 2U> &fstarts
//                coder::array<double, 2U> &fends
// Return Type  : void
//
void vad_length_filter(const coder::array<double, 2U> &starts,
                       const coder::array<double, 2U> &ends, double min_len,
                       double max_len, coder::array<double, 2U> &fstarts,
                       coder::array<double, 2U> &fends) {
    int i;
    unsigned int k;
    int n;
    // vad_length_filter: stars 开始 ends 结束 min_len 最小长度 max_len 最大长度
    // 'vad_length_filter:3' k = 0;
    k = 0U;
    // 'vad_length_filter:4' fstarts = zeros(1, length(starts));
    n = coder::internal::intlength(starts.size(0), starts.size(1));
    fstarts.set_size(1, n);
    for (i = 0; i < n; i++) {
        fstarts[i] = 0.0;
    }
    // 'vad_length_filter:5' fends = zeros(1, length(ends));
    n = coder::internal::intlength(ends.size(0), ends.size(1));
    fends.set_size(1, n);
    for (i = 0; i < n; i++) {
        fends[i] = 0.0;
    }
    // 'vad_length_filter:6' coder.varsize('fstarts');
    // 'vad_length_filter:7' coder.varsize('fends');
    // 'vad_length_filter:9' for i = 1:min(length(starts), length(ends))
    i = static_cast<int>(coder::internal::minimum2(
            static_cast<double>(
                    coder::internal::intlength(starts.size(0), starts.size(1))),
            static_cast<double>(
                    coder::internal::intlength(ends.size(0), ends.size(1)))));
    for (n = 0; n < i; n++) {
        double len;
        // 'vad_length_filter:10' len = ends(i) - starts(i) + 1;
        len = (ends[n] - starts[n]) + 1.0;
        //  小于限定长度或大于限定长度的都抛弃
        // 'vad_length_filter:12' if len > min_len && len < max_len
        if ((len > min_len) && (len < max_len)) {
            // 'vad_length_filter:13' k = k + 1;
            k++;
            // 'vad_length_filter:14' fstarts(k) = starts(i);
            fstarts[static_cast<int>(k) - 1] = starts[n];
            // 'vad_length_filter:15' fends(k) = ends(i);
            fends[static_cast<int>(k) - 1] = ends[n];
        }
    }
    //  对结果进行裁剪
    // 'vad_length_filter:20' fstarts = fstarts(1:k);
    if (1 > static_cast<int>(k)) {
        i = 0;
    } else {
        i = static_cast<int>(k);
    }
    fstarts.set_size(fstarts.size(0), i);
    // 'vad_length_filter:21' fends = fends(1:k);
    if (1 > static_cast<int>(k)) {
        i = 0;
    } else {
        i = static_cast<int>(k);
    }
    fends.set_size(fends.size(0), i);
}

//
// File trailer for vad_length_filter.cpp
//
// [EOF]
//
