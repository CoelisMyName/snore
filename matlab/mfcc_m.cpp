//
// File: mfcc_m.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "mfcc_m.h"
#include "abs.h"
#include "cos.h"
#include "enframe.h"
#include "fft.h"
#include "filter.h"
#include "fix.h"
#include "hamming.h"
#include "log.h"
#include "melbankm.h"
#include "minOrMax.h"
#include "mtimes.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "coder_array.h"

// Function Definitions
//
// function ccc = mfcc_m(x, fs, p, frameSize, inc)
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs
//                double frameSize
//                double inc
//                coder::array<double, 2U> &ccc
// Return Type  : void
//
void mfcc_m(const coder::array<double, 1U> &x, double fs, double frameSize,
            double inc, coder::array<double, 2U> &ccc) {
    static const double b_dv[8] = {0.4708715134557912, 0.74894866958846928,
                                   0.93475388500967427, 1.0,
                                   0.93475388500967427, 0.7489486695884694,
                                   0.47087151345579137, 0.14285714285714296};
    coder::sparse bank;
    coder::array<creal_T, 1U> r1;
    coder::array<double, 2U> b_bank;
    coder::array<double, 2U> b_t;
    coder::array<double, 2U> dtm;
    coder::array<double, 2U> m;
    coder::array<double, 2U> result;
    coder::array<double, 2U> xx;
    coder::array<double, 1U> b_xx;
    coder::array<double, 1U> c_bank;
    coder::array<double, 1U> r;
    coder::array<double, 1U> r2;
    coder::array<double, 1U> t;
    double dctcoef[128];
    double tmp_data[16];
    double maxval;
    int b_i;
    int b_loop_ub;
    int c_loop_ub;
    int i;
    int i1;
    int i2;
    int loop_ub;
    int tmp_size;
    signed char input_sizes_idx_1;
    signed char sizes_idx_1;
    boolean_T empty_non_axis_sizes;
    // 'mfcc_m:2' bank = melbankm(p, frameSize, fs, 0, 0.5, 'm');
    melbankm(frameSize, fs, &bank);
    // 'mfcc_m:3' bank = full(bank);
    bank.full(b_bank);
    // 'mfcc_m:4' bank = bank / max(bank(:));
    i = b_bank.size(1) << 4;
    c_bank = b_bank.reshape(i);
    maxval = coder::internal::maximum(c_bank);
    loop_ub = 16 * b_bank.size(1);
    b_bank.set_size(16, b_bank.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_bank[i] = b_bank[i] / maxval;
    }
    // 'mfcc_m:5' p2 = p / 2;
    // 'mfcc_m:6' dctcoef = zeros(p2, p);
    // 'mfcc_m:8' for k = 1:p2
    for (int k = 0; k < 8; k++) {
        // 'mfcc_m:9' n = 0:p - 1;
        // 'mfcc_m:10' dctcoef(k, :) = cos((2 * n + 1) * k * pi / (2 * p));
        for (i = 0; i < 16; i++) {
            tmp_data[i] = static_cast<double>((2 * i + 1) * (k + 1)) *
                          3.1415926535897931 / 32.0;
        }
        coder::b_cos(tmp_data);
        for (i = 0; i < 16; i++) {
            dctcoef[k + (i << 3)] = tmp_data[i];
        }
    }
    // 'mfcc_m:13' w = 1 + 6 * sin(pi * [1:p2] ./ p2);
    // 'mfcc_m:14' w = w / max(w);
    // 'mfcc_m:16' xx = double(x);
    // 'mfcc_m:17' xx = filter([1 -0.9375], 1, xx);
    // 'mfcc_m:19' xx = enframe(xx, frameSize, inc);
    coder::filter(x, r);
    enframe(r, frameSize, inc, xx);
    // 'mfcc_m:20' n2 = fix(frameSize / 2) + 1;
    maxval = frameSize / 2.0;
    coder::b_fix(&maxval);
    // 'mfcc_m:21' fn = size(xx, 1);
    // 'mfcc_m:22' m = zeros(fn, p2);
    m.set_size(xx.size(0), 8);
    loop_ub = xx.size(0) << 3;
    for (i = 0; i < loop_ub; i++) {
        m[i] = 0.0;
    }
    // 'mfcc_m:24' for i = 1:size(xx, 1)
    i = xx.size(0);
    if (0 <= xx.size(0) - 1) {
        coder::hamming(frameSize, r);
        i1 = xx.size(1);
        b_loop_ub = xx.size(1);
        if (1.0 > maxval + 1.0) {
            c_loop_ub = 0;
        } else {
            c_loop_ub = static_cast<int>(maxval + 1.0);
        }
    }
    for (b_i = 0; b_i < i; b_i++) {
        // 'mfcc_m:25' y = xx(i, :);
        // 'mfcc_m:26' s = y' .* hamming(frameSize);
        // 'mfcc_m:27' t = abs(fft(s));
        b_xx.set_size(i1);
        for (i2 = 0; i2 < b_loop_ub; i2++) {
            b_xx[i2] = xx[b_i + xx.size(0) * i2] * r[i2];
        }
        coder::fft(b_xx, r1);
        // 'mfcc_m:28' t = t.^2;
        coder::b_abs(r1, b_xx);
        coder::power(b_xx, t);
        // 'mfcc_m:29' c1 = dctcoef * log(bank * t(1:n2));
        // 'mfcc_m:30' c2 = c1 .* w';
        // 'mfcc_m:31' m(i, :) = c2';
        b_t.set_size(1, c_loop_ub);
        for (i2 = 0; i2 < c_loop_ub; i2++) {
            b_t[i2] = t[i2];
        }
        coder::internal::blas::mtimes(b_bank, b_t, tmp_data, &tmp_size);
        r2.set_size(16);
        for (i2 = 0; i2 < 16; i2++) {
            r2[i2] = tmp_data[i2];
        }
        coder::b_log(r2);
        for (i2 = 0; i2 < 8; i2++) {
            maxval = 0.0;
            for (tmp_size = 0; tmp_size < 16; tmp_size++) {
                maxval += dctcoef[i2 + (tmp_size << 3)] * r2[tmp_size];
            }
            m[b_i + m.size(0) * i2] = maxval * b_dv[i2];
        }
    }
    // 'mfcc_m:34' dtm = zeros(size(m));
    dtm.set_size(m.size(0), 8);
    loop_ub = m.size(0) << 3;
    for (i = 0; i < loop_ub; i++) {
        dtm[i] = 0.0;
    }
    // 'mfcc_m:36' for i = 3:size(m, 1) - 2
    i = m.size(0);
    for (b_i = 0; b_i <= i - 5; b_i++) {
        // 'mfcc_m:37' dtm(i, :) = -2 * m(i - 2, :) - m(i - 1, :) + m(i + 1, :)
        // + 2 * m(i + 2, :);
        for (i1 = 0; i1 < 8; i1++) {
            dtm[(b_i + dtm.size(0) * i1) + 2] =
                    ((-2.0 * m[b_i + m.size(0) * i1] -
                      m[(b_i + m.size(0) * i1) + 1]) +
                     m[(b_i + m.size(0) * i1) + 3]) +
                    2.0 * m[(b_i + m.size(0) * i1) + 4];
        }
    }
    // 'mfcc_m:40' dtm = dtm / 3;
    loop_ub = dtm.size(0) * 8;
    dtm.set_size(dtm.size(0), 8);
    for (i = 0; i < loop_ub; i++) {
        dtm[i] = dtm[i] / 3.0;
    }
    // 'mfcc_m:41' ccc = [m dtm];
    if (m.size(0) != 0) {
        tmp_size = m.size(0);
    } else if (dtm.size(0) != 0) {
        tmp_size = dtm.size(0);
    } else {
        tmp_size = 0;
    }
    empty_non_axis_sizes = (tmp_size == 0);
    if (empty_non_axis_sizes || (m.size(0) != 0)) {
        input_sizes_idx_1 = 8;
    } else {
        input_sizes_idx_1 = 0;
    }
    if (empty_non_axis_sizes || (dtm.size(0) != 0)) {
        sizes_idx_1 = 8;
    } else {
        sizes_idx_1 = 0;
    }
    result.set_size(tmp_size, input_sizes_idx_1 + sizes_idx_1);
    loop_ub = input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < tmp_size; i1++) {
            result[i1 + result.size(0) * i] = m[i1 + m.size(0) * i];
        }
    }
    loop_ub = sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < tmp_size; i1++) {
            result[i1 + result.size(0) * (i + input_sizes_idx_1)] =
                    dtm[i1 + tmp_size * i];
        }
    }
    // 'mfcc_m:42' ccc = ccc(3:size(m, 1) - 2, :);
    if (3 > m.size(0) - 2) {
        i = 0;
        i1 = 0;
    } else {
        i = 2;
        i1 = m.size(0) - 2;
    }
    loop_ub = result.size(1);
    b_loop_ub = i1 - i;
    ccc.set_size(b_loop_ub, result.size(1));
    for (i1 = 0; i1 < loop_ub; i1++) {
        for (i2 = 0; i2 < b_loop_ub; i2++) {
            ccc[i2 + ccc.size(0) * i1] = result[(i + i2) + result.size(0) * i1];
        }
    }
}

//
// File trailer for mfcc_m.cpp
//
// [EOF]
//
