#include "vad.h"
#include "SnoringRecognition_rtwutil.h"
#include "blockedSummation.h"
#include "eml_i64relops.h"
#include "hist.h"
#include "median_filter.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "vad_wave.h"
#include "yuzhiSpeci.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <math.h>

static long long mul_s64_sat(long long a, long long b);

static void mul_wide_s64(long long in0, long long in1,
                         unsigned long long *ptrOutBitsHi,
                         unsigned long long *ptrOutBitsLo);

static long long mul_s64_sat(long long a, long long b)
{
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

static void mul_wide_s64(long long in0, long long in1,
                         unsigned long long *ptrOutBitsHi,
                         unsigned long long *ptrOutBitsLo)
{
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

void vad(const coder::array<double, 1U> &x, double fs,
         coder::array<long long, 1U> &w_starts,
         coder::array<long long, 1U> &w_ends)
{
    coder::array<double, 1U> b_maxs;
    coder::array<double, 1U> b_sums;
    coder::array<double, 1U> b_y;
    coder::array<double, 1U> maxs;
    coder::array<double, 1U> sums;
    coder::array<double, 1U> y;
    coder::array<long long, 1U> b_nx1;
    coder::array<long long, 1U> b_w_ends;
    coder::array<long long, 1U> nx1;
    coder::array<long long, 1U> nx2;
    coder::array<long long, 1U> nx3;
    coder::array<long long, 1U> nx4;
    double a__1[200];
    double bins[200];
    double dth;
    double ex;
    double u;
    long long b_k;
    long long q1;
    long long qY;
    int b_i;
    int b_x;
    int bufferHeight;
    int i;
    int k;
    int nx;
    b_x = static_cast<int>(floor(static_cast<double>(x.size(0)) / 50.0)) - 1;
    maxs.set_size(b_x + 1);
    for (i = 0; i <= b_x; i++) {
        maxs[i] = 0.0;
    }
    for (b_i = 0; b_i <= b_x; b_i++) {
        i = b_i * 50;
        nx = (b_i + 1) * 50;
        if (i + 1 > nx) {
            i = -1;
            nx = -1;
        } else {
            i--;
            nx--;
        }
        k = nx - i;
        nx = k - 1;
        y.set_size(k);
        for (k = 0; k <= nx; k++) {
            y[k] = fabs(x[(i + k) + 1]);
        }
        maxs[b_i] = coder::internal::maximum(y);
    }
    b_x = static_cast<int>(floor(static_cast<double>(maxs.size(0)) / 50.0)) - 1;
    sums.set_size(b_x + 1);
    for (i = 0; i <= b_x; i++) {
        sums[i] = 0.0;
    }
    for (b_i = 0; b_i <= b_x; b_i++) {
        i = b_i * 50;
        nx = (b_i + 1) * 50;
        if (i + 1 > nx) {
            i = 0;
            nx = 0;
        }
        k = nx - i;
        b_maxs.set_size(k);
        for (nx = 0; nx < k; nx++) {
            b_maxs[nx] = maxs[i + nx];
        }
        sums[b_i] = coder::blockedSummation(b_maxs, k);
    }
    b_sums.set_size(sums.size(0));
    k = sums.size(0) - 1;
    for (i = 0; i <= k; i++) {
        b_sums[i] = sums[i];
    }
    median_filter(b_sums, sums);
    coder::hist(sums, bins, a__1);
    if (!rtIsNaN(bins[0])) {
        nx = 1;
    } else {
        boolean_T exitg1;
        nx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 201)) {
            if (!rtIsNaN(bins[k - 1])) {
                nx = k;
                exitg1 = true;
            } else {
                k++;
            }
        }
    }
    if (nx == 0) {
        nx = 1;
    } else {
        ex = bins[nx - 1];
        i = nx + 1;
        for (k = i; k < 201; k++) {
            u = bins[k - 1];
            if (ex < u) {
                ex = u;
                nx = k;
            }
        }
    }
    coder::internal::sort(bins);
    ex = bins[199] / bins[198];
    y.set_size(sums.size(0));
    k = sums.size(0);
    for (i = 0; i < k; i++) {
        y[i] = sums[i];
    }
    coder::internal::sort(y);
    u = static_cast<double>(y.size(0)) * 0.6;
    if (u < 0.0) {
        u = ceil(u);
    } else {
        u = floor(u);
    }
    if (1.0 > u) {
        k = 0;
    } else {
        k = static_cast<int>(u);
    }
    if (ex > 50.0) {
        dth = yuzhiSpeci(y, static_cast<double>(nx));
    } else if (ex > 20.0) {
        ex = coder::internal::minimum(y);
        dth = (coder::internal::maximum(y) - ex) / 200.0 *
                  (static_cast<double>(nx) + 1.5) +
              ex;
    } else if (ex > 7.0) {
        dth = (coder::internal::maximum(y) - coder::internal::minimum(y)) /
                  200.0 *
                  (((-0.076923076923076927 * ex + 1.5384615384615385) +
                    static_cast<double>(nx)) +
                   2.5) +
              coder::internal::minimum(y);
    } else if (ex > 2.0) {
        dth = (coder::internal::maximum(y) - coder::internal::minimum(y)) /
                  200.0 *
                  ((static_cast<double>(nx) + (-0.6 * ex + 5.2)) + 2.5) +
              coder::internal::minimum(y);
    } else {
        dth = (coder::internal::maximum(y) - coder::internal::minimum(y)) /
                  200.0 * (static_cast<double>(nx) + 6.5) +
              coder::internal::minimum(y);
    }
    b_y.set_size(k);
    for (i = 0; i < k; i++) {
        b_y[i] = y[i];
    }
    if (coder::internal::maximum(y) >=
        coder::blockedSummation(b_y, k) / static_cast<double>(k) * 5.0) {
        double count;
        long long len;
        b_x = static_cast<int>(ceil(static_cast<double>(sums.size(0)) / 6.0));
        nx1.set_size(b_x + 1);
        nx2.set_size(b_x + 1);
        for (i = 0; i <= b_x; i++) {
            nx1[i] = 0LL;
            nx2[i] = 0LL;
        }
        len = 0LL;
        count = 0.0;
        i = sums.size(0);
        for (b_i = 0; b_i < i; b_i++) {
            if (sums[b_i] > dth) {
                count++;
            }
            if ((sums[b_i] <= dth) && (count >= 6.0)) {
                if (len > 9223372036854775806LL) {
                    qY = MAX_int64_T;
                } else {
                    qY = len + 1LL;
                }
                len = qY;
                u = (static_cast<double>(b_i) + 1.0) - count;
                if (u >= -9.2233720368547758E+18) {
                    q1 = static_cast<long long>(u);
                } else {
                    q1 = MIN_int64_T;
                }
                nx1[static_cast<int>(qY) - 1] = q1;
                nx2[static_cast<int>(qY) - 1] = b_i;
            }
            if (sums[b_i] <= dth) {
                count = 0.0;
            }
        }
        if (count >= 6.0) {
            if (len > 9223372036854775806LL) {
                qY = MAX_int64_T;
            } else {
                qY = len + 1LL;
            }
            len = qY;
            u = (static_cast<double>(sums.size(0)) - count) + 1.0;
            if (u >= -9.2233720368547758E+18) {
                q1 = static_cast<long long>(u);
            } else {
                q1 = MIN_int64_T;
            }
            nx1[static_cast<int>(qY) - 1] = q1;
            nx2[static_cast<int>(qY) - 1] = sums.size(0);
        }
        if (1LL > len) {
            k = 0;
        } else {
            k = static_cast<int>(len);
        }
        b_nx1.set_size(k);
        for (i = 0; i < k; i++) {
            b_nx1[i] = nx1[i];
        }
        nx1.set_size(b_nx1.size(0));
        k = b_nx1.size(0);
        for (i = 0; i < k; i++) {
            nx1[i] = b_nx1[i];
        }
        if (1LL > len) {
            k = 0;
        } else {
            k = static_cast<int>(len);
        }
        b_nx1.set_size(k);
        for (i = 0; i < k; i++) {
            b_nx1[i] = nx2[i];
        }
        nx2.set_size(b_nx1.size(0));
        k = b_nx1.size(0);
        for (i = 0; i < k; i++) {
            nx2[i] = b_nx1[i];
        }
        vad_wave(sums, nx1, nx2, nx3, nx4);
        w_starts.set_size(nx3.size(0));
        k = nx3.size(0);
        for (i = 0; i < k; i++) {
            qY = nx3[i];
            if (qY < -9223372036854775807LL) {
                qY = MIN_int64_T;
            } else {
                qY--;
            }
            qY = mul_s64_sat(qY, 2500LL);
            if (qY > 9223372036854775806LL) {
                qY = MAX_int64_T;
            } else {
                qY++;
            }
            w_starts[i] = qY;
        }
        w_ends.set_size(nx4.size(0));
        k = nx4.size(0);
        for (i = 0; i < k; i++) {
            w_ends[i] = mul_s64_sat(nx4[i], 2500LL);
        }
    } else {
        w_starts.set_size(0);
        w_ends.set_size(0);
    }
    ex = 0.03 * fs;
    u = 5.0 * fs;
    b_k = 0LL;
    nx = w_starts.size(0);
    k = w_ends.size(0);
    if (nx < k) {
        bufferHeight = nx;
    } else {
        bufferHeight = k;
    }
    b_nx1.set_size(bufferHeight);
    b_w_ends.set_size(bufferHeight);
    for (i = 0; i < bufferHeight; i++) {
        b_nx1[i] = 0LL;
        b_w_ends[i] = 0LL;
    }
    nx = w_starts.size(0);
    k = w_ends.size(0);
    if (nx < k) {
        k = nx;
    }
    for (b_i = 0; b_i < k; b_i++) {
        qY = w_ends[b_i];
        q1 = w_starts[b_i];
        if ((qY >= 0LL) && (q1 < qY - MAX_int64_T)) {
            qY = MAX_int64_T;
        } else if ((qY < 0LL) && (q1 > qY - MIN_int64_T)) {
            qY = MIN_int64_T;
        } else {
            qY -= q1;
        }
        if (qY > 9223372036854775806LL) {
            qY = MAX_int64_T;
        } else {
            qY++;
        }
        if (coder::eml_i64relops(qY, ex)) {
            boolean_T p;
            p = false;
            if ((-9.2233720368547758E+18 <= u) &&
                (u < 9.2233720368547758E+18)) {
                boolean_T alarge;
                boolean_T asmall;
                boolean_T blarge;
                boolean_T bsmall;
                blarge = (u >= 4.503599627370496E+15);
                alarge = (qY >= 4503599627370496LL);
                bsmall = (u <= -4.503599627370496E+15);
                asmall = (qY <= -4503599627370496LL);
                if (((!alarge) && blarge) || (asmall && (!bsmall))) {
                    p = true;
                } else if (blarge || asmall) {
                    p = (qY < static_cast<long long>(rt_roundd_snf(u)));
                } else if ((!alarge) && (!bsmall)) {
                    p = (qY < u);
                }
            } else {
                p = (u >= 0.0);
            }
            if (p) {
                if (b_k > 9223372036854775806LL) {
                    qY = MAX_int64_T;
                } else {
                    qY = b_k + 1LL;
                }
                b_k = qY;
                b_nx1[static_cast<int>(qY) - 1] = w_starts[b_i];
                b_w_ends[static_cast<int>(qY) - 1] = w_ends[b_i];
            }
        }
    }
    if (1LL > b_k) {
        k = 0;
    } else {
        k = static_cast<int>(b_k);
    }
    w_starts.set_size(k);
    for (i = 0; i < k; i++) {
        w_starts[i] = b_nx1[i];
    }
    if (1LL > b_k) {
        k = 0;
    } else {
        k = static_cast<int>(b_k);
    }
    w_ends.set_size(k);
    for (i = 0; i < k; i++) {
        w_ends[i] = b_w_ends[i];
    }
}
