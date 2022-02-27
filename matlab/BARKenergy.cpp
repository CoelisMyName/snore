//
// File: BARKenergy.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "BARKenergy.h"
#include "abs.h"
#include "enframe.h"
#include "fft.h"
#include "fix.h"
#include "hamming.h"
#include "isinf.h"
#include "isnan.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// function [BPSEE1, BPS1, BPSEE2] = BARKenergy(x, fs)
//
// 提取bark子带能量，以及每个子带的修正频谱质心
// 输入为信号x，采样率fs
//
// Arguments    : const coder::array<double, 1U> &x
//                double fs
//                double BPSEE1[17]
//                double BPS1[17]
//                double BPSEE2[17]
// Return Type  : void
//
void BARKenergy(const coder::array<double, 1U> &x, double fs, double BPSEE1[17],
                double BPS1[17], double BPSEE2[17]) {
    static const short Fk[75] = {
            50, 150, 250, 350, 450, 570, 700, 840, 1000, 1170, 1370,
            1600, 1850, 2150, 2500, 2900, 3400, 4000, 4800, 5800, 7000, 8500,
            10500, 13500, 18775, 20, 100, 200, 300, 400, 510, 630, 770,
            920, 1080, 1270, 1480, 1720, 2000, 2320, 2700, 3150, 3700, 4400,
            5300, 6400, 7700, 9500, 12000, 15500, 100, 200, 300, 400, 510,
            630, 770, 920, 1080, 1270, 1480, 1720, 2000, 2320, 2700, 3150,
            3700, 4400, 5300, 6400, 7700, 9500, 12000, 15500, 22050};
    coder::array<creal_T, 2U> r2;
    coder::array<double, 2U> BPS;
    coder::array<double, 2U> BPSE;
    coder::array<double, 2U> Sr;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> freq;
    coder::array<double, 2U> r1;
    coder::array<double, 2U> sourfft1;
    coder::array<double, 2U> y;
    coder::array<double, 1U> r;
    double BPS1_tmp[17];
    double Src[17];
    double Srt_en[17];
    double b_dv[17];
    double b;
    double d;
    double d1;
    double ds;
    double wlen;
    int b_loop_ub;
    int i;
    int i1;
    int loop_ub;
    // 'BARKenergy:4' Fk = [50 20 100; 150 100 200; 250 200 300; 350 300 400;
    // 450 400 510; 570 510 630; 700 630 770; ... 'BARKenergy:5'         840 770
    // 920; 1000 920 1080; 1170 1080 1270; 1370 1270 1480; 1600 1480 1720; 1850
    // 1720 2000; ... 'BARKenergy:6'             2150 2000 2320; 2500 2320 2700;
    // 2900 2700 3150; 3400 3150 3700; 4000 3700 4400; ... 'BARKenergy:7' 4800
    // 4400 5300; 5800 5300 6400; 7000 6400 7700; 8500 7700 9500; 10500 9500
    // 12000; ... 'BARKenergy:8'             13500 12000 15500; 18775 15500
    // 22050]; bark子带表，分别包装了起始频率，中心频率，截止频率
    // 'BARKenergy:10' wlen = fix(0.05 * fs);
    wlen = 0.05 * fs;
    coder::b_fix(&wlen);
    // 'BARKenergy:11' inc = fix(0.5 * wlen);
    // 'BARKenergy:12' wnd = hamming(wlen);
    // 'BARKenergy:13' y = enframe(x, wnd, inc)';
    d = 0.5 * wlen;
    coder::b_fix(&d);
    coder::hamming(wlen, r);
    enframe(x, r, d, r1);
    y.set_size(r1.size(1), r1.size(0));
    loop_ub = r1.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_loop_ub = r1.size(1);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            y[i1 + y.size(0) * i] = r1[i + r1.size(0) * i1];
        }
    }
    // 由于不考虑高频部分能量，高频设置到2k为止，查找bark表可知17个子带即可
    // 'BARKenergy:15' fn = size(y, 2);
    //  fs2 = fix(fs/2);
    // 'BARKenergy:18' sourfft1 = abs(fft(y))';
    coder::fft(y, r2);
    coder::b_abs(r2, r1);
    sourfft1.set_size(r1.size(1), r1.size(0));
    loop_ub = r1.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_loop_ub = r1.size(1);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
            sourfft1[i1 + sourfft1.size(0) * i] = r1[i + r1.size(0) * i1];
        }
    }
    // 进行fft变化
    // 获得sourfft中存贮的是每一帧fft（只有正频率部分的值），将其对应的频率取出
    // 'BARKenergy:20' ds = fs / wlen;
    ds = fs / wlen;
    // 'BARKenergy:21' freq = (0:wlen / 2) * fs / wlen;
    b = wlen / 2.0;
    if (coder::b_isnan(b)) {
        b_y.set_size(1, 1);
        b_y[0] = rtNaN;
    } else if (b < 0.0) {
        b_y.set_size(1, 0);
    } else if (coder::b_isinf(b) && (0.0 == b)) {
        b_y.set_size(1, 1);
        b_y[0] = rtNaN;
    } else {
        loop_ub = static_cast<int>(floor(b));
        b_y.set_size(1, loop_ub + 1);
        for (i = 0; i <= loop_ub; i++) {
            b_y[i] = i;
        }
    }
    freq.set_size(1, b_y.size(1));
    loop_ub = b_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        freq[i] = b_y[i] * fs / wlen;
    }
    // 考虑到一半鼾声的频率，只取5khz及以下，18个子带即可
    // 'BARKenergy:23' BPSE = zeros(fn, 17);
    // 'BARKenergy:24' BPS = zeros(fn, 17);
    // 'BARKenergy:26' for i = 1:fn
    i = y.size(1);
    BPS.set_size(y.size(1), 17);
    BPSE.set_size(y.size(1), 17);
    for (int b_i = 0; b_i < i; b_i++) {
        // 'BARKenergy:27' Sr = sourfft1(i, :);
        loop_ub = sourfft1.size(1);
        Sr.set_size(1, sourfft1.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
            Sr[i1] = sourfft1[b_i + sourfft1.size(0) * i1];
        }
        // 取每一帧
        // 'BARKenergy:28' Srt_en = zeros(1, 17);
        // 'BARKenergy:29' Src = zeros(1, 17);
        // 'BARKenergy:31' for k = 1:17
        for (int k = 0; k < 17; k++) {
            double Sr_tmp;
            int i2;
            // 'BARKenergy:32' m1 = Fk(k, 2);
            // 'BARKenergy:33' m2 = Fk(k, 3);
            // 获得BARK滤波器组上下截止频率
            // 'BARKenergy:34' fx1 = fix(m1 / ds) + 1;
            d = static_cast<double>(Fk[k + 25]) / ds;
            coder::b_fix(&d);
            // 'BARKenergy:35' fx2 = fix(m2 / ds) + 1;
            d1 = static_cast<double>(Fk[k + 50]) / ds;
            coder::b_fix(&d1);
            // 转换为相应的点数
            // 'BARKenergy:36' Srt = Sr(fx1:fx2);
            if (d + 1.0 > d1 + 1.0) {
                i1 = 0;
                b_loop_ub = 0;
            } else {
                i1 = static_cast<int>(d + 1.0) - 1;
                b_loop_ub = static_cast<int>(d1 + 1.0);
            }
            // 取来对应子带的谱线
            //  设置每个子带的窗函数
            //         wind =  gausswin(length(Srt));%设置三角窗函数
            // 设置每个子带频域部分加窗
            //        Srt_wind =  wind'.* Srt;
            //        Srt_en(k) =Srt_wind*Srt_wind';
            //           Srt_en(k)
            //           =(Srt.*Srt)*wind;%对每个子带能量进行加窗，获得该帧子带的能量
            // 'BARKenergy:45' Srt_en(k) = Srt * Srt';
            b = 0.0;
            loop_ub = b_loop_ub - i1;
            for (b_loop_ub = 0; b_loop_ub < loop_ub; b_loop_ub++) {
                Sr_tmp = Sr[i1 + b_loop_ub];
                b += Sr_tmp * Sr_tmp;
            }
            Srt_en[k] = b;
            // 获得该帧子带的能量
            // 'BARKenergy:46' fre1 = freq(fx1:fx2);
            if (d + 1.0 > d1 + 1.0) {
                b_loop_ub = 0;
                i2 = 0;
            } else {
                b_loop_ub = static_cast<int>(d + 1.0) - 1;
                i2 = static_cast<int>(d1 + 1.0);
            }
            // 获得该子带的频率
            //         Src(k) =
            //         (fre1.*fre1)*(Srt.*Srt)';%获得子带修正频谱能量2阶矩
            // 'BARKenergy:48' Src(k) = fre1 * (Srt .* Srt)';
            b = 0.0;
            loop_ub = i2 - b_loop_ub;
            for (i2 = 0; i2 < loop_ub; i2++) {
                Sr_tmp = Sr[i1 + i2];
                b += freq[b_loop_ub + i2] * (Sr_tmp * Sr_tmp);
            }
            Src[k] = b;
            // 获得子带修正频谱质心
        }
        // 'BARKenergy:51' BPS(i, :) = Src;
        // 'BARKenergy:52' BPSE(i, :) = Srt_en;
        for (i1 = 0; i1 < 17; i1++) {
            BPS[b_i + BPS.size(0) * i1] = Src[i1];
            BPSE[b_i + BPSE.size(0) * i1] = Srt_en[i1];
        }
    }
    //  BPSE1= sum(BPSE,1);
    //  BPSE1 = BPSE1/sum(sum(BPSE));%计算归一化bark子带能量
    //  BPSE1 = log10(1+BPSE1/2);%取对数能量
    //  BPSE1  = BPSE1';
    //  计算归一化子带频谱质心
    // 'BARKenergy:60' BPS1 = sum(BPS, 1);
    coder::sum(BPS, BPS1_tmp);
    // 求取每个子带的修正频谱质心
    // 'BARKenergy:61' BPS1 = (BPS1 / sum(sum(BPS)))';
    coder::sum(BPS, b_dv);
    d = coder::b_sum(b_dv);
    // 进行归一化
    //     %%
    // 'BARKenergy:64' BPS2 = sum(BPS, 1);
    // 'BARKenergy:65' BPSEE1 = (BPS2 / sum(sum(BPSE)))';
    coder::sum(BPSE, b_dv);
    b = coder::b_sum(b_dv);
    // 'BARKenergy:67' BPS3 = sum(BPSE, 1);
    // 'BARKenergy:68' BPSEE2 = (BPS3 / sum(sum(BPSE)))';
    coder::sum(BPSE, b_dv);
    for (i = 0; i < 17; i++) {
        d1 = BPS1_tmp[i];
        BPS1[i] = d1 / d;
        BPSEE1[i] = d1 / b;
        BPSEE2[i] = b_dv[i] / b;
    }
    // 以上三种归一化bark子带特征方法 差别不大 使用了BPSEE1  分子为BPS的sum
    // 分母为BPSE
    //     %% 计算基于fisher子带频谱质心
    //
    //  bfr1=[0.376083873937847,0.139332330866792,1,0.274653815473444,0.0703376133209820,0.147590555951415,0.0955192719811358,0.0540638040060680,0.00674094721063561,3.47697085040573e-05,0.00908669178657100,0.0604927184469863,0.0762114611214894,0.143460079453536,0.0720217528833452,0.0745119261968838,0.0236728461659368];
    //  BPS1_weighted = bfr1'.*BPS1;%对各个分量填加权重
}

//
// File trailer for BARKenergy.cpp
//
// [EOF]
//
