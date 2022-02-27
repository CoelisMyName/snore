//
// File: yuzhiSpeci.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "yuzhiSpeci.h"
#include "histcounts.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// function pianyi = yuzhiSpeci(d, position)
//
// Arguments    : const coder::array<double, 1U> &d
//                double position
// Return Type  : double
//
double yuzhiSpeci(const coder::array<double, 1U> &d, double position) {
    coder::array<double, 2U> b_ddnns_data;
    coder::array<double, 2U> c_ddnns_data;
    coder::array<double, 2U> d_ddnns_data;
    coder::array<double, 2U> e_ddnns_data;
    coder::array<double, 2U> f_ddnns_data;
    coder::array<double, 2U> g_ddnns_data;
    coder::array<double, 2U> h_ddnns_data;
    coder::array<double, 1U> ddn;
    coder::array<double, 1U> x;
    double a__1_data[21];
    double ddnn_data[20];
    double ddnns_data[20];
    double b_up_tmp;
    double down;
    double m;
    double pianyi;
    double up;
    double up_tmp;
    int a__1_size[2];
    int ddnn_size[2];
    int ddnns_size[2];
    int i;
    int iindx;
    int partialTrueCount;
    int trueCount;
    // 'yuzhiSpeci:2' up = (max(d) - min(d)) / 200 * position + min(d);
    up_tmp = coder::internal::minimum(d);
    b_up_tmp = (coder::internal::maximum(d) - up_tmp) / 200.0;
    up = b_up_tmp * position + up_tmp;
    // 'yuzhiSpeci:3' down = (max(d) - min(d)) / 200 * (position - 1) + min(d);
    down = b_up_tmp * (position - 1.0) + up_tmp;
    // 'yuzhiSpeci:4' dn = sort(d);
    x.set_size(d.size(0));
    iindx = d.size(0);
    for (trueCount = 0; trueCount < iindx; trueCount++) {
        x[trueCount] = d[trueCount];
    }
    coder::internal::sort(x);
    // 'yuzhiSpeci:5' ddn = dn(dn <= up);
    iindx = x.size(0) - 1;
    trueCount = 0;
    for (i = 0; i <= iindx; i++) {
        if (x[i] <= up) {
            trueCount++;
        }
    }
    ddn.set_size(trueCount);
    partialTrueCount = 0;
    for (i = 0; i <= iindx; i++) {
        if (x[i] <= up) {
            ddn[partialTrueCount] = x[i];
            partialTrueCount++;
        }
    }
    // 'yuzhiSpeci:6' ddn = ddn(ddn > down);
    iindx = ddn.size(0) - 1;
    trueCount = 0;
    for (i = 0; i <= iindx; i++) {
        if (ddn[i] > down) {
            trueCount++;
        }
    }
    partialTrueCount = 0;
    for (i = 0; i <= iindx; i++) {
        if (ddn[i] > down) {
            ddn[partialTrueCount] = ddn[i];
            partialTrueCount++;
        }
    }
    ddn.set_size(trueCount);
    // 'yuzhiSpeci:7' [ddnn, ~] = histcounts(ddn, 20);
    coder::histcounts(ddn, ddnn_data, ddnn_size, a__1_data, a__1_size);
    // 'yuzhiSpeci:8' [~, ddmp] = max(ddnn);
    coder::internal::b_maximum(ddnn_data, &up_tmp, &iindx);
    // 'yuzhiSpeci:9' ddnns = sort(ddnn);
    ddnns_size[0] = 1;
    ddnns_size[1] = 20;
    memcpy(&ddnns_data[0], &ddnn_data[0], 20U * sizeof(double));
    coder::internal::sort(ddnns_data, ddnns_size);
    // 'yuzhiSpeci:10' m = ddnns(end) / ddnns(end - 1);
    m = ddnns_data[ddnns_size[1] - 1] / ddnns_data[ddnns_size[1] - 2];
    // 'yuzhiSpeci:12' if ddmp > 15
    if (iindx > 15) {
        // 'yuzhiSpeci:13' pianyi = max(ddnns);
        b_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        pianyi = coder::internal::maximum(b_ddnns_data);
    } else if (m >= 20.0) {
        // 'yuzhiSpeci:14' elseif m >= 20
        // 'yuzhiSpeci:15' pianyi = (max(ddnns) - min(ddnns)) / 20 * (ddmp + 4)
        // + min(ddnns);
        c_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        up_tmp = coder::internal::minimum(c_ddnns_data);
        g_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        pianyi = (coder::internal::maximum(g_ddnns_data) - up_tmp) / 20.0 *
                 (static_cast<double>(iindx) + 4.0) +
                 up_tmp;
    } else if (m > 10.0) {
        // 'yuzhiSpeci:16' elseif m > 10
        // 'yuzhiSpeci:17' pianyi = (max(ddnns) - min(ddnns)) / 20 * (ddmp + 5)
        // + min(ddnns);
        e_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        f_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        h_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        pianyi = (coder::internal::maximum(e_ddnns_data) -
                  coder::internal::minimum(f_ddnns_data)) /
                 20.0 * (static_cast<double>(iindx) + 5.0) +
                 coder::internal::minimum(h_ddnns_data);
    } else {
        // 'yuzhiSpeci:18' else
        // 'yuzhiSpeci:19' pianyi = max(ddnns);
        d_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        pianyi = coder::internal::maximum(d_ddnns_data);
    }
    return pianyi;
}

//
// File trailer for yuzhiSpeci.cpp
//
// [EOF]
//
