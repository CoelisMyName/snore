//
// File: mfcc.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "mfcc.h"
#include "SnoringRecognition_rtwutil.h"
#include "audioDelta.h"
#include "cepstralCoefficients.h"
#include "combineVectorElements.h"
#include "designMelFilterBank.h"
#include "fft.h"
#include "gencoswin.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &audioIn
//                double fs
//                ::coder::array<double, 2U> &varargout_1
//                ::coder::array<double, 2U> &varargout_2
//                ::coder::array<double, 2U> &varargout_3
//                ::coder::array<double, 1U> &varargout_4
// Return Type  : void
//
namespace coder {
    void mfcc(const ::coder::array<double, 1U> &audioIn, double fs,
              ::coder::array<double, 2U> &varargout_1,
              ::coder::array<double, 2U> &varargout_2,
              ::coder::array<double, 2U> &varargout_3,
              ::coder::array<double, 1U> &varargout_4) {
        static const double b_dv[42] = {133.33333333333334,
                                        200.0,
                                        266.66666666666669,
                                        333.33333333333337,
                                        400.0,
                                        466.66666666666674,
                                        533.33333333333337,
                                        600.0,
                                        666.66666666666674,
                                        733.33333333333337,
                                        800.00000000000011,
                                        866.66666666666674,
                                        933.33333333333337,
                                        999.75894666666659,
                                        1070.9120908286172,
                                        1147.1292256065171,
                                        1228.7707567317004,
                                        1316.2227401195225,
                                        1409.8987074006509,
                                        1510.2416213759673,
                                        1617.725970641781,
                                        1732.8600132901477,
                                        1856.1881802940113,
                                        1988.29364994199,
                                        2129.8011054964563,
                                        2281.3796891149705,
                                        2443.7461660031895,
                                        2617.6683137614859,
                                        2803.9685529523849,
                                        3003.5278360565717,
                                        3217.2898132070686,
                                        3446.2652943999592,
                                        3691.5370292819921,
                                        3954.2648271171,
                                        4235.6910411424715,
                                        4537.1464432478933,
                                        4860.0565167577788,
                                        5205.9481970723846,
                                        5576.4570920424849,
                                        5973.3352162202755,
                                        6398.4592755592366,
                                        6853.83954173857};
        static const double bandEdges[42] = {133.33333333333334,
                                             200.0,
                                             266.66666666666669,
                                             333.33333333333337,
                                             400.0,
                                             466.66666666666674,
                                             533.33333333333337,
                                             600.0,
                                             666.66666666666674,
                                             733.33333333333337,
                                             800.00000000000011,
                                             866.66666666666674,
                                             933.33333333333337,
                                             999.75894666666659,
                                             1070.9120908286172,
                                             1147.1292256065171,
                                             1228.7707567317004,
                                             1316.2227401195225,
                                             1409.8987074006509,
                                             1510.2416213759673,
                                             1617.725970641781,
                                             1732.8600132901477,
                                             1856.1881802940113,
                                             1988.29364994199,
                                             2129.8011054964563,
                                             2281.3796891149705,
                                             2443.7461660031895,
                                             2617.6683137614859,
                                             2803.9685529523849,
                                             3003.5278360565717,
                                             3217.2898132070686,
                                             3446.2652943999592,
                                             3691.5370292819921,
                                             3954.2648271171,
                                             4235.6910411424715,
                                             4537.1464432478933,
                                             4860.0565167577788,
                                             5205.9481970723846,
                                             5576.4570920424849,
                                             5973.3352162202755,
                                             6398.4592755592366,
                                             6853.83954173857};
        static const signed char b_iv[3] = {1, 3, 2};
        array<creal_T, 2U> b_x;
        array<double, 3U> a;
        array<double, 2U> E;
        array<double, 2U> Z;
        array<double, 2U> b_coeffs;
        array<double, 2U> b_y;
        array<double, 2U> c_win;
        array<double, 2U> coeffs;
        array<double, 2U> filterBank;
        array<double, 2U> y;
        array<double, 1U> b_win;
        array<double, 1U> win;
        double edges_data[42];
        double bkj;
        double hopLength;
        double winLength;
        double x;
        int edges_size[2];
        int acoef;
        int b_i;
        int bcoef;
        int boffset;
        int csz_idx_1;
        int i;
        int j;
        int k;
        int nx;
        int subsa_idx_2;
        signed char input_sizes_idx_1;
        boolean_T c_x[42];
        boolean_T empty_non_axis_sizes;
        winLength = rt_roundd_snf(fs * 0.03);
        nx = 1;
        input_sizes_idx_1 = 0;
        csz_idx_1 = 0;
        if (winLength == 0.0) {
            nx = 0;
            csz_idx_1 = 1;
        } else if (winLength == 1.0) {
            input_sizes_idx_1 = 1;
            csz_idx_1 = 1;
        }
        win.set_size(nx);
        for (i = 0; i < nx; i++) {
            win[0] = input_sizes_idx_1;
        }
        if (csz_idx_1 == 0) {
            if (rtIsNaN(winLength + 1.0) || rtIsInf(winLength + 1.0)) {
                bkj = rtNaN;
            } else if (winLength + 1.0 == 0.0) {
                bkj = 0.0;
            } else {
                bkj = fmod(winLength + 1.0, 2.0);
                if (bkj == 0.0) {
                    bkj = 0.0;
                } else if (winLength + 1.0 < 0.0) {
                    bkj += 2.0;
                }
            }
            if (bkj == 0.0) {
                calc_window((winLength + 1.0) / 2.0, winLength + 1.0, win);
                if (2 > win.size(0)) {
                    i = 0;
                    j = 1;
                    acoef = -1;
                } else {
                    i = win.size(0) - 1;
                    j = -1;
                    acoef = 1;
                }
                bcoef = div_s32_floor(acoef - i, j);
                b_win.set_size((win.size(0) + bcoef) + 1);
                nx = win.size(0);
                for (acoef = 0; acoef < nx; acoef++) {
                    b_win[acoef] = win[acoef];
                }
                for (acoef = 0; acoef <= bcoef; acoef++) {
                    b_win[acoef + win.size(0)] = win[i + j * acoef];
                }
                win.set_size(b_win.size(0));
                bcoef = b_win.size(0);
                for (i = 0; i < bcoef; i++) {
                    win[i] = b_win[i];
                }
            } else {
                calc_window(((winLength + 1.0) + 1.0) / 2.0, winLength + 1.0, win);
                if (2 > win.size(0) - 1) {
                    i = 0;
                    j = 1;
                    acoef = -1;
                } else {
                    i = win.size(0) - 2;
                    j = -1;
                    acoef = 1;
                }
                bcoef = div_s32_floor(acoef - i, j);
                b_win.set_size((win.size(0) + bcoef) + 1);
                nx = win.size(0);
                for (acoef = 0; acoef < nx; acoef++) {
                    b_win[acoef] = win[acoef];
                }
                for (acoef = 0; acoef <= bcoef; acoef++) {
                    b_win[acoef + win.size(0)] = win[i + j * acoef];
                }
                win.set_size(b_win.size(0));
                bcoef = b_win.size(0);
                for (i = 0; i < bcoef; i++) {
                    win[i] = b_win[i];
                }
            }
        }
        hopLength = winLength - rt_roundd_snf(fs * 0.02);
        x = floor((static_cast<double>(audioIn.size(0)) - winLength) / hopLength);
        bkj = floor((static_cast<double>(audioIn.size(0)) - winLength) / hopLength);
        i = static_cast<int>(bkj + 1.0);
        y.set_size(static_cast<int>(winLength), i);
        bcoef = static_cast<int>(winLength) * static_cast<int>(bkj + 1.0);
        for (j = 0; j < bcoef; j++) {
            y[j] = 0.0;
        }
        for (csz_idx_1 = 0; csz_idx_1 < i; csz_idx_1++) {
            double d;
            double d1;
            d = hopLength * ((static_cast<double>(csz_idx_1) + 1.0) - 1.0);
            d1 = winLength + d;
            if (d + 1.0 > d1) {
                j = 0;
                acoef = 0;
            } else {
                j = static_cast<int>(d + 1.0) - 1;
                acoef = static_cast<int>(d1);
            }
            nx = static_cast<int>((static_cast<double>(csz_idx_1) + 1.0) +
                                  0.0 * (bkj + 1.0)) -
                 1;
            bcoef = acoef - j;
            for (acoef = 0; acoef < bcoef; acoef++) {
                y[acoef + y.size(0) * nx] = audioIn[j + acoef];
            }
        }
        Z.set_size(y.size(0), y.size(1));
        nx = y.size(0) * y.size(1);
        for (k = 0; k < nx; k++) {
            Z[k] = y[k] * y[k];
        }
        combineVectorElements(Z, E);
        nx = E.size(1);
        for (b_i = 0; b_i < nx; b_i++) {
            if (E[b_i] == 0.0) {
                E[b_i] = 2.2250738585072014E-308;
            }
        }
        nx = win.size(0);
        csz_idx_1 = y.size(0);
        if (nx < csz_idx_1) {
            csz_idx_1 = nx;
        }
        if (win.size(0) == 1) {
            csz_idx_1 = y.size(0);
        } else if (y.size(0) == 1) {
            csz_idx_1 = win.size(0);
        } else if (y.size(0) == win.size(0)) {
            csz_idx_1 = y.size(0);
        }
        Z.set_size(csz_idx_1, y.size(1));
        nx = win.size(0);
        csz_idx_1 = y.size(0);
        if (nx < csz_idx_1) {
            csz_idx_1 = nx;
        }
        if (win.size(0) == 1) {
            csz_idx_1 = y.size(0);
        } else if (y.size(0) == 1) {
            csz_idx_1 = win.size(0);
        } else if (y.size(0) == win.size(0)) {
            csz_idx_1 = y.size(0);
        }
        if ((csz_idx_1 != 0) && (y.size(1) != 0)) {
            nx = (y.size(1) != 1);
            i = y.size(1) - 1;
            for (k = 0; k <= i; k++) {
                csz_idx_1 = nx * k;
                acoef = (y.size(0) != 1);
                bcoef = (win.size(0) != 1);
                j = Z.size(0) - 1;
                for (boffset = 0; boffset <= j; boffset++) {
                    Z[boffset + Z.size(0) * k] =
                            y[acoef * boffset + y.size(0) * csz_idx_1] *
                            win[bcoef * boffset];
                }
            }
        }
        fft(Z, winLength, b_x);
        nx = b_x.size(0) * b_x.size(1);
        Z.set_size(b_x.size(0), b_x.size(1));
        for (k = 0; k < nx; k++) {
            Z[k] = rt_hypotd_snf(b_x[k].re, b_x[k].im);
        }
        bkj = fs / 2.0;
        for (i = 0; i < 42; i++) {
            c_x[i] = (bandEdges[i] <= bkj);
        }
        nx = c_x[0];
        for (k = 0; k < 41; k++) {
            nx += c_x[k + 1];
        }
        if (nx < 42) {
            if (1 > nx + 1) {
                bcoef = -1;
            } else {
                bcoef = nx;
            }
            edges_size[0] = 1;
            edges_size[1] = bcoef + 1;
            if (0 <= bcoef) {
                memcpy(&edges_data[0], &b_dv[0], (bcoef + 1) * sizeof(double));
            }
            edges_data[bcoef] = fs / 2.0;
        } else {
            edges_size[0] = 1;
            edges_size[1] = 42;
            memcpy(&edges_data[0], &bandEdges[0], 42U * sizeof(double));
        }
        audio::internal::designMelFilterBank(fs, edges_data, edges_size, winLength,
                                             filterBank);
        nx = filterBank.size(1);
        csz_idx_1 = filterBank.size(0);
        acoef = Z.size(1);
        b_y.set_size(filterBank.size(1), Z.size(1));
        for (j = 0; j < acoef; j++) {
            bcoef = j * nx;
            boffset = j * Z.size(0);
            for (b_i = 0; b_i < nx; b_i++) {
                b_y[bcoef + b_i] = 0.0;
            }
            for (k = 0; k < csz_idx_1; k++) {
                bkj = Z[boffset + k];
                for (b_i = 0; b_i < nx; b_i++) {
                    i = bcoef + b_i;
                    b_y[i] =
                            b_y[i] + filterBank[b_i * filterBank.size(0) + k] * bkj;
                }
            }
        }
        cepstralCoefficients(b_y, coeffs);
        nx = E.size(1);
        for (k = 0; k < nx; k++) {
            E[k] = log(E[k]);
        }
        win.set_size(E.size(1));
        bcoef = E.size(1);
        for (i = 0; i < bcoef; i++) {
            win[i] = E[i];
        }
        if (win.size(0) != 0) {
            nx = win.size(0);
        } else if (coeffs.size(0) != 0) {
            nx = coeffs.size(0);
        } else {
            nx = 0;
        }
        empty_non_axis_sizes = (nx == 0);
        if (empty_non_axis_sizes || (win.size(0) != 0)) {
            input_sizes_idx_1 = 1;
        } else {
            input_sizes_idx_1 = 0;
        }
        if (empty_non_axis_sizes || (coeffs.size(0) != 0)) {
            csz_idx_1 = 12;
        } else {
            csz_idx_1 = 0;
        }
        acoef = input_sizes_idx_1 + csz_idx_1;
        bcoef = coeffs.size(0);
        b_coeffs.set_size(coeffs.size(0), 12);
        for (i = 0; i < 12; i++) {
            for (j = 0; j < bcoef; j++) {
                b_coeffs[j + b_coeffs.size(0) * i] =
                        coeffs[j + coeffs.size(0) * (i + 1)];
            }
        }
        c_win.set_size(nx, acoef);
        bcoef = input_sizes_idx_1;
        for (i = 0; i < bcoef; i++) {
            for (j = 0; j < nx; j++) {
                c_win[j] = win[j];
            }
        }
        for (i = 0; i < csz_idx_1; i++) {
            for (j = 0; j < nx; j++) {
                c_win[j + c_win.size(0) * (i + input_sizes_idx_1)] =
                        b_coeffs[j + nx * i];
            }
        }
        a.set_size(nx, 1, acoef);
        bcoef = nx * acoef;
        for (i = 0; i < bcoef; i++) {
            a[i] = c_win[i];
        }
        empty_non_axis_sizes = true;
        if ((a.size(0) != 0) && (a.size(2) != 0)) {
            boolean_T exitg1;
            nx = 0;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < 3)) {
                if (a.size(b_iv[k] - 1) != 1) {
                    if (nx > b_iv[k]) {
                        empty_non_axis_sizes = false;
                        exitg1 = true;
                    } else {
                        nx = b_iv[k];
                        k++;
                    }
                } else {
                    k++;
                }
            }
        }
        if (empty_non_axis_sizes) {
            varargout_2.set_size(a.size(0), a.size(2));
            bcoef = a.size(0) * a.size(2);
            for (i = 0; i < bcoef; i++) {
                varargout_2[i] = a[i];
            }
        } else {
            varargout_2.set_size(a.size(0), a.size(2));
            i = a.size(2);
            for (k = 0; k < i; k++) {
                j = a.size(0);
                if (0 <= a.size(0) - 1) {
                    subsa_idx_2 = k + 1;
                }
                for (boffset = 0; boffset < j; boffset++) {
                    varargout_2[boffset + varargout_2.size(0) * (subsa_idx_2 - 1)] =
                            a[boffset + a.size(0) * (subsa_idx_2 - 1)];
                }
            }
        }
        varargout_1.set_size(varargout_2.size(0), varargout_2.size(1));
        bcoef = varargout_2.size(0) * varargout_2.size(1);
        for (i = 0; i < bcoef; i++) {
            varargout_1[i] = varargout_2[i];
        }
        audioDelta(varargout_2, c_win);
        varargout_2.set_size(c_win.size(0), c_win.size(1));
        bcoef = c_win.size(0) * c_win.size(1);
        for (i = 0; i < bcoef; i++) {
            varargout_2[i] = c_win[i];
        }
        audioDelta(varargout_2, c_win);
        varargout_3.set_size(c_win.size(0), c_win.size(1));
        bcoef = c_win.size(0) * c_win.size(1);
        for (i = 0; i < bcoef; i++) {
            varargout_3[i] = c_win[i];
        }
        if (rtIsNaN((x + 1.0) - 1.0)) {
            E.set_size(1, 1);
            E[0] = rtNaN;
        } else if ((x + 1.0) - 1.0 < 0.0) {
            E.set_size(1, 0);
        } else if (rtIsInf((x + 1.0) - 1.0) && (0.0 == (x + 1.0) - 1.0)) {
            E.set_size(1, 1);
            E[0] = rtNaN;
        } else {
            E.set_size(1, static_cast<int>((x + 1.0) - 1.0) + 1);
            bcoef = static_cast<int>((x + 1.0) - 1.0);
            for (i = 0; i <= bcoef; i++) {
                E[i] = i;
            }
        }
        varargout_4.set_size(E.size(1));
        bcoef = E.size(1);
        for (i = 0; i < bcoef; i++) {
            varargout_4[i] = E[i] * hopLength + winLength;
        }
    }

} // namespace coder

//
// File trailer for mfcc.cpp
//
// [EOF]
//
