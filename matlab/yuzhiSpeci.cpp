//
// File: yuzhiSpeci.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "yuzhiSpeci.h"
#include "histcounts.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "coder_array.h"

// Function Definitions
//
// function pianyi = yuzhiSpeci(d, position)
//
// Arguments    : const coder::array<double, 2U> &d
//                double position
// Return Type  : double
//
double yuzhiSpeci(const coder::array<double, 2U> &d, double position) {
    coder::array<double, 2U> a__1;
    coder::array<double, 2U> ddn;
    coder::array<double, 2U> dn;
    double down;
    double pianyi;
    double up;
    double up_tmp;
    int i;
    int loop_ub;
    int partialTrueCount;
    int trueCount;
    // 'yuzhiSpeci:2' up = (max(d) - min(d)) / 200 * position + min(d);
    down = coder::internal::minimum(d);
    up_tmp = (coder::internal::maximum(d) - down) / 200.0;
    up = up_tmp * position + down;
    // 'yuzhiSpeci:3' down = (max(d) - min(d)) / 200 * (position - 1) + min(d);
    down += up_tmp * (position - 1.0);
    // 'yuzhiSpeci:4' dn = sort(d);
    dn.set_size(1, d.size(1));
    loop_ub = d.size(1);
    for (trueCount = 0; trueCount < loop_ub; trueCount++) {
        dn[trueCount] = d[trueCount];
    }
    coder::internal::sort(dn);
    // 'yuzhiSpeci:5' ddn = dn(dn <= up);
    loop_ub = dn.size(1) - 1;
    trueCount = 0;
    for (i = 0; i <= loop_ub; i++) {
        if (dn[i] <= up) {
            trueCount++;
        }
    }
    ddn.set_size(1, trueCount);
    partialTrueCount = 0;
    for (i = 0; i <= loop_ub; i++) {
        up_tmp = dn[i];
        if (up_tmp <= up) {
            ddn[partialTrueCount] = up_tmp;
            partialTrueCount++;
        }
    }
    // 'yuzhiSpeci:6' ddn = ddn(ddn > down);
    loop_ub = ddn.size(1) - 1;
    trueCount = 0;
    for (i = 0; i <= loop_ub; i++) {
        if (ddn[i] > down) {
            trueCount++;
        }
    }
    partialTrueCount = 0;
    for (i = 0; i <= loop_ub; i++) {
        if (ddn[i] > down) {
            ddn[partialTrueCount] = ddn[i];
            partialTrueCount++;
        }
    }
    ddn.set_size(1, trueCount);
    // 'yuzhiSpeci:7' [ddnn, ~] = histcounts(ddn, 20);
    coder::histcounts(ddn, dn, a__1);
    // 'yuzhiSpeci:8' [~, ddmp] = max(ddnn);
    coder::internal::maximum(dn, &down, &loop_ub);
    // 'yuzhiSpeci:9' ddnns = sort(ddnn);
    coder::internal::sort(dn);
    // 'yuzhiSpeci:10' m = ddnns(end) / ddnns(end - 1);
    down = dn[dn.size(1) - 1] / dn[dn.size(1) - 2];
    // 'yuzhiSpeci:12' if ddmp > 15
    if (loop_ub > 15) {
        // 'yuzhiSpeci:13' pianyi = max(ddnns);
        pianyi = coder::internal::maximum(dn);
    } else if (down >= 20.0) {
        // 'yuzhiSpeci:14' elseif m >= 20
        // 'yuzhiSpeci:15' pianyi = (max(ddnns) - min(ddnns)) / 20 * (ddmp + 4) +
        // min(ddnns);
        down = coder::internal::minimum(dn);
        pianyi = (coder::internal::maximum(dn) - down) / 20.0 *
                 (static_cast<double>(loop_ub) + 4.0) +
                 down;
    } else if (down > 10.0) {
        // 'yuzhiSpeci:16' elseif m > 10
        // 'yuzhiSpeci:17' pianyi = (max(ddnns) - min(ddnns)) / 20 * (ddmp + 5) +
        // min(ddnns);
        down = coder::internal::minimum(dn);
        pianyi = (coder::internal::maximum(dn) - down) / 20.0 *
                 (static_cast<double>(loop_ub) + 5.0) +
                 down;
    } else {
        // 'yuzhiSpeci:18' else
        // 'yuzhiSpeci:19' pianyi = max(ddnns);
        pianyi = coder::internal::maximum(dn);
    }
    return pianyi;
}

//
// File trailer for yuzhiSpeci.cpp
//
// [EOF]
//
