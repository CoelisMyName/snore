//
// File: vad.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "vad.h"
#include "amax_group.h"
#include "fix.h"
#include "hist.h"
#include "mean.h"
#include "median_filter.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sum_group.h"
#include "vad_below_threshold.h"
#include "vad_length_filter.h"
#include "vad_threshold.h"
#include "vad_wave.h"
#include "coder_array.h"

// Function Declarations
static long long mul_s64_sat(long long a, long long b);

static void mul_wide_s64(long long in0, long long in1,
                         unsigned long long *ptrOutBitsHi,
                         unsigned long long *ptrOutBitsLo);

// Function Definitions
//
// Arguments    : long long a
//                long long b
// Return Type  : long long
//
static long long mul_s64_sat(long long a, long long b) {
    long long result;
    unsigned long long u64_chi;
    unsigned long long u64_clo;
    mul_wide_s64(a, b, &u64_chi, &u64_clo);
    if ((static_cast<long long>(u64_chi) > 0LL) ||
        ((u64_chi == 0ULL) && (u64_clo >= 9223372036854775808ULL))) {
        result = MAX_int64_T;
    } else if ((static_cast<long long>(u64_chi) < -1LL) ||
               ((static_cast<long long>(u64_chi) == -1LL) &&
                (u64_clo < 9223372036854775808ULL))) {
        result = MIN_int64_T;
    } else {
        result = static_cast<long long>(u64_clo);
    }
    return result;
}

//
// Arguments    : long long in0
//                long long in1
//                unsigned long long *ptrOutBitsHi
//                unsigned long long *ptrOutBitsLo
// Return Type  : void
//
static void mul_wide_s64(long long in0, long long in1,
                         unsigned long long *ptrOutBitsHi,
                         unsigned long long *ptrOutBitsLo) {
    unsigned long long absIn0;
    unsigned long long absIn1;
    unsigned long long in0Hi;
    unsigned long long in0Lo;
    unsigned long long in1Hi;
    unsigned long long productHiLo;
    unsigned long long productLoHi;
    if (in0 < 0LL) {
        absIn0 = ~static_cast<unsigned long long>(in0) + 1ULL;
    } else {
        absIn0 = static_cast<unsigned long long>(in0);
    }
    if (in1 < 0LL) {
        absIn1 = ~static_cast<unsigned long long>(in1) + 1ULL;
    } else {
        absIn1 = static_cast<unsigned long long>(in1);
    }
    in0Hi = absIn0 >> 32ULL;
    in0Lo = absIn0 & 4294967295ULL;
    in1Hi = absIn1 >> 32ULL;
    absIn0 = absIn1 & 4294967295ULL;
    productHiLo = in0Hi * absIn0;
    productLoHi = in0Lo * in1Hi;
    absIn0 *= in0Lo;
    absIn1 = 0ULL;
    in0Lo = absIn0 + (productLoHi << 32ULL);
    if (in0Lo < absIn0) {
        absIn1 = 1ULL;
    }
    absIn0 = in0Lo;
    in0Lo += productHiLo << 32ULL;
    if (in0Lo < absIn0) {
        absIn1++;
    }
    absIn0 = ((absIn1 + in0Hi * in1Hi) + (productLoHi >> 32ULL)) +
             (productHiLo >> 32ULL);
    if (static_cast<int>((in0 != 0LL) &&
                         ((in1 != 0LL) && ((in0 > 0LL) != (in1 > 0LL))))) {
        absIn0 = ~absIn0;
        in0Lo = ~in0Lo;
        in0Lo++;
        if (in0Lo == 0ULL) {
            absIn0++;
        }
    }
    *ptrOutBitsHi = absIn0;
    *ptrOutBitsLo = in0Lo;
}

//
// function [w_starts, w_ends] = vad(x, fs)
//
// %% -------------------音频最小长度60秒---------------------------
//
// Arguments    : coder::array<double, 1U> &x
//                double fs
//                coder::array<long long, 1U> &w_starts
//                coder::array<long long, 1U> &w_ends
// Return Type  : void
//
void vad(coder::array<double, 1U> &x, double fs,
         coder::array<long long, 1U> &w_starts,
         coder::array<long long, 1U> &w_ends) {
    coder::array<double, 1U> b_sums;
    coder::array<double, 1U> b_x;
    coder::array<double, 1U> c_x;
    coder::array<double, 1U> maxs;
    coder::array<double, 1U> sums;
    coder::array<long long, 1U> b_w_ends;
    coder::array<long long, 1U> b_w_starts;
    coder::array<long long, 1U> nx1;
    coder::array<long long, 1U> nx2;
    coder::array<long long, 1U> nx3;
    coder::array<long long, 1U> nx4;
    double a__1[200];
    double bins[200];
    double MIN_LEN;
    double dth;
    double ex;
    int i;
    int iindx;
    int loop_ub;
    //  只接受1分钟长度的音频，多的截去，少的补0
    //  x(inf,1) fs(1,1) w_starts(inf,1) w_ends(inf,1)
    // 'vad:6' MIN_LEN = 60 * fs;
    MIN_LEN = 60.0 * fs;
    // 'vad:8' if (length(x) > MIN_LEN)
    if (x.size(0) > MIN_LEN) {
        // 'vad:9' x = x(1:MIN_LEN);
        if (1.0 > MIN_LEN) {
            i = 0;
        } else {
            i = static_cast<int>(MIN_LEN);
        }
        x.set_size(i);
    }
    // 'vad:12' if (length(x) < MIN_LEN)
    if (x.size(0) < MIN_LEN) {
        // 'vad:13' x = [x; zeros(MIN_LEN - length(x), 1)];
        loop_ub = static_cast<int>(MIN_LEN - static_cast<double>(x.size(0)));
        i = x.size(0);
        x.set_size(x.size(0) +
                   static_cast<int>(MIN_LEN - static_cast<double>(x.size(0))));
        for (iindx = 0; iindx < loop_ub; iindx++) {
            x[iindx + i] = 0.0;
        }
    }
    // 'vad:16' maxs = amax_group(x, 50);
    amax_group(x, maxs);
    // 'vad:17' sums = sum_group(maxs, 50);
    sum_group(maxs, sums);
    // 'vad:18' sums = median_filter(sums, 10);
    b_sums.set_size(sums.size(0));
    loop_ub = sums.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
        b_sums[i] = sums[i];
    }
    median_filter(b_sums, sums);
    // 'vad:20' [bins, ~] = hist(sums, 200);
    coder::hist(sums, bins, a__1);
    // 'vad:21' [~, position] = max(bins);
    coder::internal::maximum(bins, &ex, &iindx);
    // 'vad:22' bins = sort(bins);
    coder::internal::sort(bins);
    // 'vad:23' tis = bins(end) / bins(end - 1);
    // 'vad:24' sorted_sums = sort(sums);
    b_x.set_size(sums.size(0));
    loop_ub = sums.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_x[i] = sums[i];
    }
    coder::internal::sort(b_x);
    // 前60%的平均值
    // 'vad:26' ddth = mean(sorted_sums(1:fix(length(sorted_sums) * 0.6)));
    ex = static_cast<double>(b_x.size(0)) * 0.6;
    coder::b_fix(&ex);
    if (1.0 > ex) {
        loop_ub = 0;
    } else {
        loop_ub = static_cast<int>(ex);
    }
    // 取阈值？
    // 'vad:29' dth = vad_threshold(tis, sorted_sums, position);
    dth = vad_threshold(bins[199] / bins[198], b_x, static_cast<double>(iindx));
    // 'vad:31' coder.varsize('w_starts');
    // 'vad:32' coder.varsize('w_ends');
    // 'vad:34' if max(sorted_sums) >= ddth * 5
    c_x.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
        c_x[i] = b_x[i];
    }
    if (coder::internal::maximum(b_x) >= coder::mean(c_x) * 5.0) {
        // 'vad:35' [nx1, nx2] = vad_below_threshold(sums, dth, 6);
        vad_below_threshold(sums, dth, nx1, nx2);
        // 'vad:36' [nx3, nx4] = vad_wave(sums, nx1, nx2);
        vad_wave(sums, nx1, nx2, nx3, nx4);
        //  映射至实际区间
        // 'vad:38' w_starts = (nx3 - 1) * 2500 + 1;
        w_starts.set_size(nx3.size(0));
        loop_ub = nx3.size(0);
        for (i = 0; i < loop_ub; i++) {
            long long q0;
            q0 = nx3[i];
            if (q0 < -9223372036854775807LL) {
                q0 = MIN_int64_T;
            } else {
                q0--;
            }
            q0 = mul_s64_sat(q0, 2500LL);
            if (q0 > 9223372036854775806LL) {
                q0 = MAX_int64_T;
            } else {
                q0++;
            }
            w_starts[i] = q0;
        }
        // 'vad:39' w_ends = nx4 * 2500;
        w_ends.set_size(nx4.size(0));
        loop_ub = nx4.size(0);
        for (i = 0; i < loop_ub; i++) {
            w_ends[i] = mul_s64_sat(nx4[i], 2500LL);
        }
    } else {
        // 'vad:40' else
        // 'vad:41' w_starts = zeros(0,1,'int64');
        w_starts.set_size(0);
        // 'vad:42' w_ends = zeros(0,1,'int64');
        w_ends.set_size(0);
    }
    // 截取段过滤
    // 'vad:46' [w_starts, w_ends] = vad_length_filter(w_starts, w_ends, 0.03 *
    // fs, 5 * fs);
    b_w_starts.set_size(w_starts.size(0));
    loop_ub = w_starts.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
        b_w_starts[i] = w_starts[i];
    }
    b_w_ends.set_size(w_ends.size(0));
    loop_ub = w_ends.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
        b_w_ends[i] = w_ends[i];
    }
    vad_length_filter(b_w_starts, b_w_ends, 0.03 * fs, 5.0 * fs, w_starts,
                      w_ends);
}

//
// File trailer for vad.cpp
//
// [EOF]
//
