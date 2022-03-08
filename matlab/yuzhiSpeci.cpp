#include "yuzhiSpeci.h"
#include "histcounts.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <string.h>

double yuzhiSpeci(const coder::array<double, 1U> &d, double position)
{
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
    int k;
    int partialTrueCount;
    up_tmp = coder::internal::minimum(d);
    b_up_tmp = (coder::internal::maximum(d) - up_tmp) / 200.0;
    up = b_up_tmp * position + up_tmp;
    down = b_up_tmp * (position - 1.0) + up_tmp;
    x.set_size(d.size(0));
    iindx = d.size(0);
    for (partialTrueCount = 0; partialTrueCount < iindx; partialTrueCount++) {
        x[partialTrueCount] = d[partialTrueCount];
    }
    coder::internal::sort(x);
    iindx = x.size(0) - 1;
    k = 0;
    for (i = 0; i <= iindx; i++) {
        if (x[i] <= up) {
            k++;
        }
    }
    ddn.set_size(k);
    partialTrueCount = 0;
    for (i = 0; i <= iindx; i++) {
        if (x[i] <= up) {
            ddn[partialTrueCount] = x[i];
            partialTrueCount++;
        }
    }
    iindx = ddn.size(0) - 1;
    k = 0;
    for (i = 0; i <= iindx; i++) {
        if (ddn[i] > down) {
            k++;
        }
    }
    partialTrueCount = 0;
    for (i = 0; i <= iindx; i++) {
        if (ddn[i] > down) {
            ddn[partialTrueCount] = ddn[i];
            partialTrueCount++;
        }
    }
    ddn.set_size(k);
    coder::histcounts(ddn, ddnn_data, ddnn_size, a__1_data, a__1_size);
    if (!rtIsNaN(ddnn_data[0])) {
        iindx = 1;
    } else {
        boolean_T exitg1;
        iindx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= 20)) {
            if (!rtIsNaN(ddnn_data[k - 1])) {
                iindx = k;
                exitg1 = true;
            } else {
                k++;
            }
        }
    }
    if (iindx == 0) {
        iindx = 1;
    } else {
        up_tmp = ddnn_data[iindx - 1];
        partialTrueCount = iindx + 1;
        for (k = partialTrueCount; k < 21; k++) {
            b_up_tmp = ddnn_data[k - 1];
            if (up_tmp < b_up_tmp) {
                up_tmp = b_up_tmp;
                iindx = k;
            }
        }
    }
    ddnns_size[0] = 1;
    ddnns_size[1] = 20;
    memcpy(&ddnns_data[0], &ddnn_data[0], 20U * sizeof(double));
    coder::internal::sort(ddnns_data, ddnns_size);
    m = ddnns_data[ddnns_size[1] - 1] / ddnns_data[ddnns_size[1] - 2];
    if (iindx > 15) {
        b_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        pianyi = coder::internal::maximum(b_ddnns_data);
    } else if (m >= 20.0) {
        c_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        up_tmp = coder::internal::minimum(c_ddnns_data);
        g_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        pianyi = (coder::internal::maximum(g_ddnns_data) - up_tmp) / 20.0 *
                     (static_cast<double>(iindx) + 4.0) +
                 up_tmp;
    } else if (m > 10.0) {
        e_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        f_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        h_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        pianyi = (coder::internal::maximum(e_ddnns_data) -
                  coder::internal::minimum(f_ddnns_data)) /
                     20.0 * (static_cast<double>(iindx) + 5.0) +
                 coder::internal::minimum(h_ddnns_data);
    } else {
        d_ddnns_data.set(&ddnns_data[0], ddnns_size[0], ddnns_size[1]);
        pianyi = coder::internal::maximum(d_ddnns_data);
    }
    return pianyi;
}
