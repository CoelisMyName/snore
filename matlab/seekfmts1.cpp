//
// File: seekfmts1.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "seekfmts1.h"
#include "abs.h"
#include "atan2.h"
#include "floor.h"
#include "length.h"
#include "log.h"
#include "m_lpc.h"
#include "minOrMax.h"
#include "roots.h"
#include "round.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "coder_array.h"

// Function Definitions
//
// function [fmt] = seekfmts1(sig, Nt, fs, Nlpc)
//
// fmt:3*Nt的数组
// sig 输入声音信号
// Nt分帧后的总帧数
// fs采样频率
// Nlpc：lpc分析的阶数
//
// Arguments    : const coder::array<double, 1U> &sig
//                double Nt
//                double fs
//                coder::array<double, 2U> &fmt
// Return Type  : void
//
void seekfmts1(const coder::array<double, 1U> &sig, double Nt, double fs,
               coder::array<double, 2U> &fmt) {
    coder::array<double, 2U> yf;
    coder::array<double, 1U> b_sig;
    coder::array<int, 2U> b_yf;
    creal_T rts_data[10];
    double a_data[11];
    double F[3];
    double b_Nwin[2];
    double Nwin;
    double b_const;
    double b_fs;
    double d;
    int a_size[2];
    int i;
    int loop_ub;
    // 'seekfmts1:7' if nargin < 4
    // 'seekfmts1:8' Nt = round(Nt);
    coder::b_round(&Nt);
    // 'seekfmts1:9' ls = length(sig);
    //  数据长度
    // 'seekfmts1:10' Nwin = floor(ls / Nt);
    Nwin = static_cast<double>(sig.size(0)) / Nt;
    coder::b_floor(&Nwin);
    //  帧长
    // 'seekfmts1:12' fmt = zeros(3, Nt);
    i = static_cast<int>(Nt);
    fmt.set_size(3, i);
    // 'seekfmts1:14' for m = 1:Nt
    if (0 <= static_cast<int>(Nt) - 1) {
        b_Nwin[1] = sig.size(0);
        b_const = fs / 6.2831853071795862;
        b_fs = fs / 2.0;
    }
    for (int m = 0; m < i; m++) {
        double d1;
        int i1;
        int i2;
        // 'seekfmts1:15' lpcsig = sig((Nwin * (m - 1) + 1):min([(Nwin * m)
        // ls]));
        d = Nwin * ((static_cast<double>(m) + 1.0) - 1.0) + 1.0;
        b_Nwin[0] = Nwin * (static_cast<double>(m) + 1.0);
        d1 = coder::internal::minimum(b_Nwin);
        if (d > d1) {
            i1 = 0;
            i2 = 0;
        } else {
            i1 = static_cast<int>(d) - 1;
            i2 = static_cast<int>(d1);
        }
        //  取来一帧信号
        // 'seekfmts1:16' a = m_lpc(lpcsig, Nlpc);
        loop_ub = i2 - i1;
        b_sig.set_size(loop_ub);
        for (i2 = 0; i2 < loop_ub; i2++) {
            b_sig[i2] = sig[i1 + i2];
        }
        b_m_lpc(b_sig, a_data, a_size);
        //  计算LPC系数
        // 'seekfmts1:17' const = fs / (2 * pi);
        //  常数
        // 'seekfmts1:18' rts = roots(a(:));
        coder::roots(a_data, a_size[1], rts_data, &loop_ub);
        //  求根
        // 'seekfmts1:19' k = 1;
        //  初始化
        // 'seekfmts1:20' yf = [];
        yf.set_size(1, 0);
        // 'seekfmts1:21' bandw = [];
        // 'seekfmts1:22' coder.varsize('yf');
        // 'seekfmts1:23' coder.varsize('bandw');
        // 'seekfmts1:25' for i = 1:length(a) - 1
        i1 = coder::internal::intlength(a_size[1]);
        for (int b_i = 0; b_i <= i1 - 2; b_i++) {
            double formn;
            // 'seekfmts1:26' re = real(rts(i));
            //  取根之实部
            // 'seekfmts1:27' im = imag(rts(i));
            //  取根之虚部
            // 'seekfmts1:28' formn = const * atan2(im, re);
            formn =
                    b_const * coder::b_atan2(rts_data[b_i].im, rts_data[b_i].re);
            //  计算共振峰频率
            // 'seekfmts1:29' bw = -2 * const * log(abs(rts(i)));
            d = coder::b_abs(rts_data[b_i]);
            coder::b_log(&d);
            //  计算带宽
            // 'seekfmts1:31' if formn > 150 && bw < 700 && formn < fs / 2
            if ((formn > 150.0) && (-2.0 * b_const * d < 700.0) &&
                (formn < fs / 2.0)) {
                //  满足条件方能成共振峰和带宽
                // 'seekfmts1:32' yf = [yf formn];
                i2 = yf.size(1);
                yf.set_size(yf.size(0), yf.size(1) + 1);
                yf[i2] = formn;
                // 'seekfmts1:33' bandw = [bandw, bw];
                // 'seekfmts1:34' k = k + 1;
            }
        }
        // 'seekfmts1:39' [y, ind] = sort(yf);
        coder::internal::sort(yf, b_yf);
        //  排序
        // 'seekfmts1:40' bw = bandw(ind);
        // 'seekfmts1:41' F = [NaN NaN NaN];
        F[0] = rtNaN;
        F[1] = rtNaN;
        F[2] = rtNaN;
        //  初始化
        // 'seekfmts1:42' F(1:min(3, length(y))) = y(1:min(3, length(y)));
        d = coder::internal::minimum2(3.0, static_cast<double>(yf.size(1)));
        if (1.0 > d) {
            loop_ub = 0;
        } else {
            loop_ub = static_cast<int>(d);
        }
        for (i1 = 0; i1 < loop_ub; i1++) {
            F[i1] = yf[i1];
        }
        //  输出最多三个
        // 'seekfmts1:43' F = F(:);
        //  按列输出
        // 'seekfmts1:44' fmt(:, m) = F / (fs / 2);
        fmt[3 * m] = F[0] / b_fs;
        fmt[3 * m + 1] = F[1] / b_fs;
        fmt[3 * m + 2] = F[2] / b_fs;
        //  归一化频率
    }
}

//
// File trailer for seekfmts1.cpp
//
// [EOF]
//
