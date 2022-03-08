#include "noise_segment.h"
#include "eml_i64relops.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"

void noise_segment(const coder::array<long long, 1U> &starts,
                   const coder::array<long long, 1U> &ends, double fs,
                   double min_gap, double margin, double *ostart,
                   double *olength)
{
    int i;
    int len;
    int u0;
    int u1;
    boolean_T exitg1;
    u0 = starts.size(0);
    u1 = ends.size(0);
    if (u0 < u1) {
        len = u0;
    } else {
        len = u1;
    }
    *ostart = -1.0;
    *olength = -1.0;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i <= len - 2)) {
        long long q0_tmp;
        long long q1;
        q0_tmp = starts[i + 1];
        q1 = ends[i];
        if ((q0_tmp >= 0LL) && (q1 < q0_tmp - MAX_int64_T)) {
            q1 = MAX_int64_T;
        } else if ((q0_tmp < 0LL) && (q1 > q0_tmp - MIN_int64_T)) {
            q1 = MIN_int64_T;
        } else {
            q1 = q0_tmp - q1;
        }
        if (coder::eml_i64relops(q1, margin)) {
            *ostart = (static_cast<double>(ends[i]) + min_gap) / fs;
            *olength = (static_cast<double>(q0_tmp) - min_gap) / fs - *ostart;
            exitg1 = true;
        } else {
            i++;
        }
    }
}
