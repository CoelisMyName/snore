//
// File: lpc2spec.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "lpc2spec.h"
#include "SnoringRecognition_data.h"
#include "abs.h"
#include "angle.h"
#include "exp.h"
#include "isinf.h"
#include "isnan.h"
#include "power.h"
#include "repmat.h"
#include "roots.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sqrt.h"
#include "coder_array.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// function [features, F, M] = lpc2spec(lpcas, nout)
//
// [features,F,M] = lpc2spec(lpcas,nout)
//     Convert LPC coeffs back into spectra
//     nout is number of freq channels, default 17 (i.e. for 8 kHz)
//  2003-04-11 dpwe@ee.columbia.edu  part of rastamat
//
// Arguments    : const coder::array<double, 2U> &lpcas
//                double nout
//                coder::array<double, 2U> &features
//                coder::array<double, 2U> &F
//                coder::array<double, 2U> &M
// Return Type  : void
//
void lpc2spec(const coder::array<double, 2U> &lpcas, double nout,
              coder::array<double, 2U> &features, coder::array<double, 2U> &F,
              coder::array<double, 2U> &M) {
    coder::array<creal_T, 2U> c_aa;
    coder::array<creal_T, 2U> r2;
    coder::array<creal_T, 2U> r3;
    coder::array<creal_T, 1U> c_tmp_data;
    coder::array<creal_T, 1U> r1;
    coder::array<double, 2U> aa;
    coder::array<double, 2U> b_lpcas;
    coder::array<double, 2U> r;
    coder::array<double, 2U> r4;
    coder::array<double, 2U> r5;
    coder::array<double, 1U> d_tmp_data;
    coder::array<double, 1U> r6;
    coder::array<int, 2U> iidx;
    creal_T b_aa[13];
    creal_T b_tmp_data[12];
    creal_T tmp_data[12];
    double e_tmp_data[12];
    double ff_data[12];
    double mags_data[12];
    double ai;
    double ar;
    double im;
    int ix_data[12];
    int ff_size[2];
    int tmp_size[2];
    int b_i;
    int b_loop_ub;
    int i;
    int loop_ub;
    int trueCount;
    // 'lpc2spec:7' if nargin < 2
    // 'lpc2spec:11' [rows, cols] = size(lpcas);
    // 'lpc2spec:12' order = rows - 1;
    // 'lpc2spec:14' gg = lpcas(1, :);
    // 'lpc2spec:15' aa = lpcas ./ repmat(gg, rows, 1);
    loop_ub = lpcas.size(1);
    b_lpcas.set_size(1, lpcas.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_lpcas[i] = lpcas[13 * i];
    }
    coder::repmat(b_lpcas, r);
    aa.set_size(13, lpcas.size(1));
    loop_ub = 13 * lpcas.size(1);
    for (i = 0; i < loop_ub; i++) {
        aa[i] = lpcas[i] / r[i];
    }
    //  Calculate the actual z-plane polyvals: nout points around unit circle
    // 'lpc2spec:18' zz = exp((-1i * [0:(nout - 1)]' * pi / (nout - 1)) *
    // [0:order]);
    if (coder::b_isnan(nout - 1.0)) {
        b_lpcas.set_size(1, 1);
        b_lpcas[0] = rtNaN;
    } else if (nout - 1.0 < 0.0) {
        b_lpcas.set_size(1, 0);
    } else if (coder::b_isinf(nout - 1.0) && (0.0 == nout - 1.0)) {
        b_lpcas.set_size(1, 1);
        b_lpcas[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(nout - 1.0));
        b_lpcas.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            b_lpcas[i] = i;
        }
    }
    //  Actual polyvals, in power (mag^2)
    // 'lpc2spec:21' features = ((1 ./ abs(zz * aa)).^2) ./ repmat(gg, nout, 1);
    r1.set_size(b_lpcas.size(1));
    loop_ub = b_lpcas.size(1);
    for (i = 0; i < loop_ub; i++) {
        ar = b_lpcas[i] * 0.0 * 3.1415926535897931;
        ai = -b_lpcas[i] * 3.1415926535897931;
        if (ai == 0.0) {
            r1[i].re = ar / (nout - 1.0);
            r1[i].im = 0.0;
        } else if (ar == 0.0) {
            r1[i].re = 0.0;
            r1[i].im = ai / (nout - 1.0);
        } else {
            r1[i].re = rtNaN;
            r1[i].im = ai / (nout - 1.0);
        }
    }
    r2.set_size(r1.size(0), 13);
    loop_ub = r1.size(0);
    for (i = 0; i < 13; i++) {
        b_aa[i].re = i;
        b_aa[i].im = 0.0;
        for (b_i = 0; b_i < loop_ub; b_i++) {
            trueCount = static_cast<int>(b_aa[i].re);
            ar = b_aa[i].im;
            r2[b_i + r2.size(0) * i].re =
                    r1[b_i].re * static_cast<double>(trueCount) - r1[b_i].im * ar;
            r2[b_i + r2.size(0) * i].im =
                    r1[b_i].re * ar + r1[b_i].im * static_cast<double>(trueCount);
        }
    }
    coder::b_exp(r2);
    c_aa.set_size(13, aa.size(1));
    loop_ub = 13 * aa.size(1);
    for (i = 0; i < loop_ub; i++) {
        c_aa[i].re = aa[i];
        c_aa[i].im = 0.0;
    }
    r3.set_size(r2.size(0), c_aa.size(1));
    loop_ub = r2.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_loop_ub = c_aa.size(1);
        for (b_i = 0; b_i < b_loop_ub; b_i++) {
            ai = 0.0;
            im = 0.0;
            for (trueCount = 0; trueCount < 13; trueCount++) {
                ai += r2[i + r2.size(0) * trueCount].re *
                      c_aa[trueCount + 13 * b_i].re -
                      r2[i + r2.size(0) * trueCount].im *
                      c_aa[trueCount + 13 * b_i].im;
                im += r2[i + r2.size(0) * trueCount].re *
                      c_aa[trueCount + 13 * b_i].im +
                      r2[i + r2.size(0) * trueCount].im *
                      c_aa[trueCount + 13 * b_i].re;
            }
            r3[i + r3.size(0) * b_i].re = ai;
            r3[i + r3.size(0) * b_i].im = im;
        }
    }
    coder::b_abs(r3, r4);
    r5.set_size(r4.size(0), r4.size(1));
    loop_ub = r4.size(0) * r4.size(1);
    for (i = 0; i < loop_ub; i++) {
        r5[i] = 1.0 / r4[i];
    }
    coder::power(r5, r4);
    loop_ub = lpcas.size(1);
    b_lpcas.set_size(1, lpcas.size(1));
    for (i = 0; i < loop_ub; i++) {
        b_lpcas[i] = lpcas[13 * i];
    }
    coder::repmat(b_lpcas, nout, r5);
    features.set_size(r4.size(0), r4.size(1));
    loop_ub = r4.size(0) * r4.size(1);
    for (i = 0; i < loop_ub; i++) {
        features[i] = r4[i] / r5[i];
    }
    // 'lpc2spec:23' F = zeros(cols, size(aa, 1));
    F.set_size(lpcas.size(1), 13);
    loop_ub = lpcas.size(1) * 13;
    for (i = 0; i < loop_ub; i++) {
        F[i] = 0.0;
    }
    // 'lpc2spec:24' M = zeros(cols, size(aa, 1));
    M.set_size(lpcas.size(1), 13);
    loop_ub = lpcas.size(1) * 13;
    for (i = 0; i < loop_ub; i++) {
        M[i] = 0.0;
    }
    // 'lpc2spec:26' for c = 1:cols
    i = lpcas.size(1);
    if (0 <= i - 1) {
        tmp_size[0] = 1;
    }
    for (int c = 0; c < i; c++) {
        // 'lpc2spec:27' aaa = aa(:, c);
        // 'lpc2spec:28' rr = roots(complex(aaa'));
        // 'lpc2spec:29' ff = angle(rr');
        for (b_i = 0; b_i < 13; b_i++) {
            b_aa[b_i].re = aa[b_i + 13 * c];
            b_aa[b_i].im = 0.0;
        }
        coder::roots(b_aa, tmp_data, &b_loop_ub);
        tmp_size[1] = b_loop_ub;
        for (b_i = 0; b_i < b_loop_ub; b_i++) {
            b_tmp_data[b_i].re = tmp_data[b_i].re;
            b_tmp_data[b_i].im = -tmp_data[b_i].im;
        }
        coder::angle(b_tmp_data, tmp_size, ff_data, ff_size);
        //   size(ff)
        //   size(aaa)
        // 'lpc2spec:32' zz = exp(1i * ff' * [0:(length(aaa) - 1)]);
        // 'lpc2spec:33' mags = sqrt(((1 ./ abs(zz * aaa)).^2) / gg(c))';
        loop_ub = ff_size[1];
        r2.set_size(ff_size[1], 13);
        for (b_i = 0; b_i < 13; b_i++) {
            b_aa[b_i].re = b_i;
            b_aa[b_i].im = 0.0;
            for (trueCount = 0; trueCount < loop_ub; trueCount++) {
                im = ff_data[trueCount];
                ai = im * 0.0;
                b_loop_ub = static_cast<int>(b_aa[b_i].re);
                ar = b_aa[b_i].im;
                r2[trueCount + r2.size(0) * b_i].re =
                        ai * static_cast<double>(b_loop_ub) - im * ar;
                r2[trueCount + r2.size(0) * b_i].im =
                        ai * ar + im * static_cast<double>(b_loop_ub);
            }
        }
        coder::b_exp(r2);
        for (b_i = 0; b_i < 13; b_i++) {
            b_aa[b_i].re = aa[b_i + 13 * c];
            b_aa[b_i].im = 0.0;
        }
        b_loop_ub = r2.size(0);
        loop_ub = r2.size(0);
        for (b_i = 0; b_i < loop_ub; b_i++) {
            ai = 0.0;
            im = 0.0;
            for (trueCount = 0; trueCount < 13; trueCount++) {
                double d;
                ar = b_aa[trueCount].re;
                d = b_aa[trueCount].im;
                ai += r2[b_i + r2.size(0) * trueCount].re * ar -
                      r2[b_i + r2.size(0) * trueCount].im * d;
                im += r2[b_i + r2.size(0) * trueCount].re * d +
                      r2[b_i + r2.size(0) * trueCount].im * ar;
            }
            tmp_data[b_i].re = ai;
            tmp_data[b_i].im = im;
        }
        c_tmp_data.set(&tmp_data[0], b_loop_ub);
        coder::b_abs(c_tmp_data, r6);
        b_loop_ub = r6.size(0);
        loop_ub = r6.size(0);
        for (b_i = 0; b_i < loop_ub; b_i++) {
            e_tmp_data[b_i] = 1.0 / r6[b_i];
        }
        d_tmp_data.set(&e_tmp_data[0], b_loop_ub);
        coder::power(d_tmp_data, r6);
        ar = lpcas[13 * c];
        b_loop_ub = r6.size(0);
        loop_ub = r6.size(0);
        for (b_i = 0; b_i < loop_ub; b_i++) {
            e_tmp_data[b_i] = r6[b_i] / ar;
        }
        coder::b_sqrt(e_tmp_data, &b_loop_ub);
        if (0 <= b_loop_ub - 1) {
            memcpy(&mags_data[0], &e_tmp_data[0], b_loop_ub * sizeof(double));
        }
        // 'lpc2spec:35' [~, ix] = sort(ff);
        loop_ub = ff_size[1];
        b_lpcas.set_size(1, ff_size[1]);
        for (b_i = 0; b_i < loop_ub; b_i++) {
            b_lpcas[b_i] = ff_data[b_i];
        }
        coder::internal::sort(b_lpcas, iidx);
        b_lpcas.set_size(1, iidx.size(1));
        loop_ub = iidx.size(1);
        for (b_i = 0; b_i < loop_ub; b_i++) {
            trueCount = iidx[b_i];
            b_lpcas[b_i] = trueCount;
            ix_data[b_i] = trueCount;
        }
        // 'lpc2spec:36' keep = ff(ix) > 0;
        // 'lpc2spec:37' ix = ix(keep);
        b_loop_ub = b_lpcas.size(1) - 1;
        trueCount = 0;
        for (b_i = 0; b_i <= b_loop_ub; b_i++) {
            if (ff_data[static_cast<int>(b_lpcas[b_i]) - 1] > 0.0) {
                trueCount++;
            }
        }
        loop_ub = 0;
        for (b_i = 0; b_i <= b_loop_ub; b_i++) {
            if (ff_data[ix_data[b_i] - 1] > 0.0) {
                ix_data[loop_ub] = ix_data[b_i];
                loop_ub++;
            }
        }
        // 'lpc2spec:38' F(c, 1:length(ix)) = ff(ix);
        for (b_i = 0; b_i < trueCount; b_i++) {
            F[c + F.size(0) * b_i] = ff_data[ix_data[b_i] - 1];
        }
        // size(ix)
        // 'lpc2spec:40' M(c, 1:length(ix)) = mags(ix);
        for (b_i = 0; b_i < trueCount; b_i++) {
            M[c + M.size(0) * b_i] = mags_data[ix_data[b_i] - 1];
        }
    }
}

//
// File trailer for lpc2spec.cpp
//
// [EOF]
//
