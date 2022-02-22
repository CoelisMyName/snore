//
// File: mfcc_m.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "mfcc_m.h"
#include "SnoringRecognition_types.h"
#include "abs.h"
#include "cos.h"
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
#include "v_enframe.h"
#include "coder_array.h"

// Function Definitions
//
// function ccc = mfcc_m(x, fs, p, frameSize, inc)
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//     function ccc=mfcc_m(x,fs,p,frameSize,inc)
// ���������������x����MFCC��������ȡ������MFCC������һ��
// ���MFCC������Mel�˲����ĸ���Ϊp������Ƶ��Ϊfs
// ��xÿframeSize���Ϊһ֡��������֮֡���֡��Ϊinc
//  FFT�ĳ���Ϊ֡��
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Arguments    : SnoringRecognitionStackData *SD
//                const coder::array<double, 1U> &x
//                double fs
//                double frameSize
//                double inc
//                coder::array<double, 2U> &ccc
// Return Type  : void
//
void mfcc_m(SnoringRecognitionStackData *SD, const coder::array<double, 1U> &x,
            double fs, double frameSize, double inc,
            coder::array<double, 2U> &ccc) {
    static const double b_dv1[8] = {0.4708715134557912, 0.74894866958846928,
                                    0.93475388500967427, 1.0,
                                    0.93475388500967427, 0.7489486695884694,
                                    0.47087151345579137, 0.14285714285714296};
    coder::sparse bank;
    coder::array<creal_T, 1U> r;
    coder::array<double, 2U> b_bank;
    coder::array<double, 2U> b_xx;
    coder::array<double, 2U> d_xx;
    coder::array<double, 2U> dtm;
    coder::array<double, 2U> m;
    coder::array<double, 1U> c_xx;
    coder::array<double, 1U> d_bank;
    coder::array<double, 1U> xx;
    double dctcoef[128];
    double b_dv[16];
    double maxval;
    int c_bank;
    int i;
    int i1;
    int i2;
    int loop_ub;
    signed char input_sizes_idx_1;
    signed char sizes_idx_1;
    boolean_T empty_non_axis_sizes;
    //  ��֡��ΪframeSize��Mel�˲����ĸ���Ϊp������Ƶ��Ϊfs
    //  ��ȡMel�˲����������ú���������
    // 'mfcc_m:12' bank = melbankm(p, frameSize, fs, 0, 0.5, 'm');
    melbankm(SD, frameSize, fs, &bank);
    //  ��һ��Mel�˲�����ϵ��
    // 'mfcc_m:14' bank = full(bank);
    bank.full(b_bank);
    // 'mfcc_m:15' bank = bank / max(bank(:));
    c_bank = b_bank.size(0) * b_bank.size(1);
    d_bank = b_bank.reshape(c_bank);
    maxval = coder::internal::maximum(d_bank);
    loop_ub = b_bank.size(0) * b_bank.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_bank[i] = b_bank[i] / maxval;
    }
    // 'mfcc_m:16' p2 = p / 2;
    //  DCTϵ��,p2*p
    // 'mfcc_m:18' dctcoef = zeros(p2, p);
    // 'mfcc_m:20' for k = 1:p2
    for (c_bank = 0; c_bank < 8; c_bank++) {
        // 'mfcc_m:21' n = 0:p - 1;
        // 'mfcc_m:22' dctcoef(k, :) = cos((2 * n + 1) * k * pi / (2 * p));
        for (i = 0; i < 16; i++) {
            b_dv[i] = static_cast<double>((2 * i + 1) * (c_bank + 1)) *
                      3.1415926535897931 / 32.0;
        }
        coder::b_cos(b_dv);
        for (i = 0; i < 16; i++) {
            dctcoef[c_bank + (i << 3)] = b_dv[i];
        }
    }
    //  ��һ��������������
    // 'mfcc_m:26' w = 1 + 6 * sin(pi * [1:p2] ./ p2);
    // 'mfcc_m:27' w = w / max(w);
    //  Ԥ�����˲���
    // 'mfcc_m:30' xx = double(x);
    // 'mfcc_m:31' xx = filter([1 -0.9375], 1, xx);
    //  �����źŷ�֡
    // 'mfcc_m:34' xx = v_enframe(xx, frameSize, inc);
    coder::filter(x, xx);
    v_enframe(xx, frameSize, inc, b_xx);
    // 'mfcc_m:35' n2 = fix(frameSize / 2) + 1;
    maxval = frameSize / 2.0;
    coder::b_fix(&maxval);
    //  ����ÿ֡��MFCC����
    // 'mfcc_m:37' fn = size(xx, 1);
    // 'mfcc_m:38' m = zeros(fn, p2);
    m.set_size(b_xx.size(0), 8);
    loop_ub = b_xx.size(0) << 3;
    for (i = 0; i < loop_ub; i++) {
        m[i] = 0.0;
    }
    // 'mfcc_m:40' for i = 1:size(xx, 1)
    i = b_xx.size(0);
    for (c_bank = 0; c_bank < i; c_bank++) {
        // 'mfcc_m:41' y = xx(i, :);
        // 'mfcc_m:42' s = y' .* hamming(frameSize);
        coder::hamming(frameSize, c_xx);
        // 'mfcc_m:43' t = abs(fft(s));
        loop_ub = b_xx.size(1);
        xx.set_size(b_xx.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            xx[i1] = b_xx[c_bank + b_xx.size(0) * i1] * c_xx[i1];
        }
        coder::fft(xx, r);
        // 'mfcc_m:44' t = t.^2;
        coder::b_abs(r, xx);
        coder::power(xx, c_xx);
        // 'mfcc_m:45' c1 = dctcoef * log(bank * t(1:n2));
        if (1.0 > maxval + 1.0) {
            loop_ub = 0;
        } else {
            loop_ub = static_cast<int>(maxval + 1.0);
        }
        d_xx.set_size(1, loop_ub);
        for (i1 = 0; i1 < loop_ub; i1++) {
            d_xx[i1] = c_xx[i1];
        }
        coder::internal::blas::mtimes(b_bank, d_xx, c_xx);
        // 'mfcc_m:46' c2 = c1 .* w';
        // 'mfcc_m:47' m(i, :) = c2';
        coder::b_log(c_xx);
        for (i1 = 0; i1 < 8; i1++) {
            double d;
            d = 0.0;
            for (i2 = 0; i2 < 16; i2++) {
                d += dctcoef[i1 + (i2 << 3)] * c_xx[i2];
            }
            m[c_bank + m.size(0) * i1] = d * b_dv1[i1];
        }
    }
    // ���ϵ��
    // 'mfcc_m:51' dtm = zeros(size(m));
    dtm.set_size(m.size(0), 8);
    loop_ub = m.size(0) << 3;
    for (i = 0; i < loop_ub; i++) {
        dtm[i] = 0.0;
    }
    // 'mfcc_m:53' for i = 3:size(m, 1) - 2
    i = m.size(0);
    for (c_bank = 0; c_bank <= i - 5; c_bank++) {
        // 'mfcc_m:54' dtm(i, :) = -2 * m(i - 2, :) - m(i - 1, :) + m(i + 1, :) + 2
        // * m(i + 2, :);
        for (i1 = 0; i1 < 8; i1++) {
            dtm[(c_bank + dtm.size(0) * i1) + 2] =
                    ((-2.0 * m[c_bank + m.size(0) * i1] -
                      m[(c_bank + m.size(0) * i1) + 1]) +
                     m[(c_bank + m.size(0) * i1) + 3]) +
                    2.0 * m[(c_bank + m.size(0) * i1) + 4];
        }
    }
    // 'mfcc_m:57' dtm = dtm / 3;
    loop_ub = dtm.size(0) * 8;
    dtm.set_size(dtm.size(0), 8);
    for (i = 0; i < loop_ub; i++) {
        dtm[i] = dtm[i] / 3.0;
    }
    // �ϲ�MFCC������һ�ײ��MFCC����
    // 'mfcc_m:59' ccc = [m dtm];
    if (m.size(0) != 0) {
        c_bank = m.size(0);
    } else if (dtm.size(0) != 0) {
        c_bank = dtm.size(0);
    } else {
        c_bank = 0;
    }
    empty_non_axis_sizes = (c_bank == 0);
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
    ccc.set_size(c_bank, input_sizes_idx_1 + sizes_idx_1);
    loop_ub = input_sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < c_bank; i1++) {
            ccc[i1 + ccc.size(0) * i] = m[i1 + c_bank * i];
        }
    }
    loop_ub = sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
        for (i1 = 0; i1 < c_bank; i1++) {
            ccc[i1 + ccc.size(0) * (i + input_sizes_idx_1)] = dtm[i1 + c_bank * i];
        }
    }
    // ȥ����β��֡����Ϊ����֡��һ�ײ�ֲ���Ϊ0
    // 'mfcc_m:61' ccc = ccc(3:size(m, 1) - 2, :);
    if (3 > m.size(0) - 2) {
        i = -1;
        i1 = -1;
    } else {
        i = 1;
        i1 = m.size(0) - 3;
    }
    c_bank = ccc.size(1) - 1;
    for (i2 = 0; i2 <= c_bank; i2++) {
        loop_ub = i1 - i;
        for (int i3 = 0; i3 < loop_ub; i3++) {
            ccc[i3 + loop_ub * i2] = ccc[((i + i3) + ccc.size(0) * i2) + 1];
        }
    }
    ccc.set_size(i1 - i, c_bank + 1);
}

//
// File trailer for mfcc_m.cpp
//
// [EOF]
//
