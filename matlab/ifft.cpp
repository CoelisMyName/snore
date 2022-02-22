//
// File: ifft.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "SnoringRecognition_data.h"
#include "nextpow2.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
namespace coder {
    void ifft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y) {
        array<creal_T, 1U> fv;
        array<creal_T, 1U> fy;
        array<creal_T, 1U> wwc;
        array<double, 2U> costab;
        array<double, 2U> costab1q;
        array<double, 2U> sintab;
        array<double, 2U> sintabinv;
        int nfft;
        nfft = x.size(0);
        if (x.size(0) == 0) {
            y.set_size(0);
        } else {
            double nt_re;
            int N2blue;
            int i;
            int k;
            int nInt2;
            int nd2;
            int rt;
            boolean_T useRadix2;
            useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
            nd2 = x.size(0);
            N2blue = 1;
            if (!useRadix2) {
                if (nd2 > 0) {
                    k = nextpow2((nd2 + nd2) - 1);
                    if (k >= 0) {
                        if (k <= 31) {
                            N2blue = 1 << k;
                        } else {
                            N2blue = 0;
                        }
                    } else {
                        N2blue = 0;
                    }
                }
                nd2 = N2blue;
            }
            nt_re = 6.2831853071795862 / static_cast<double>(nd2);
            nInt2 = nd2 / 2 / 2;
            costab1q.set_size(1, nInt2 + 1);
            costab1q[0] = 1.0;
            nd2 = nInt2 / 2 - 1;
            for (k = 0; k <= nd2; k++) {
                costab1q[k + 1] = cos(nt_re * (static_cast<double>(k) + 1.0));
            }
            i = nd2 + 2;
            rt = nInt2 - 1;
            for (k = i; k <= rt; k++) {
                costab1q[k] = sin(nt_re * static_cast<double>(nInt2 - k));
            }
            costab1q[nInt2] = 0.0;
            if (!useRadix2) {
                nInt2 = costab1q.size(1) - 1;
                nd2 = (costab1q.size(1) - 1) << 1;
                costab.set_size(1, nd2 + 1);
                sintab.set_size(1, nd2 + 1);
                costab[0] = 1.0;
                sintab[0] = 0.0;
                sintabinv.set_size(1, nd2 + 1);
                for (k = 0; k < nInt2; k++) {
                    sintabinv[k + 1] = costab1q[(nInt2 - k) - 1];
                }
                i = costab1q.size(1);
                for (k = i; k <= nd2; k++) {
                    sintabinv[k] = costab1q[k - nInt2];
                }
                for (k = 0; k < nInt2; k++) {
                    costab[k + 1] = costab1q[k + 1];
                    sintab[k + 1] = -costab1q[(nInt2 - k) - 1];
                }
                i = costab1q.size(1);
                for (k = i; k <= nd2; k++) {
                    costab[k] = -costab1q[nd2 - k];
                    sintab[k] = -costab1q[k - nInt2];
                }
            } else {
                nInt2 = costab1q.size(1) - 1;
                nd2 = (costab1q.size(1) - 1) << 1;
                costab.set_size(1, nd2 + 1);
                sintab.set_size(1, nd2 + 1);
                costab[0] = 1.0;
                sintab[0] = 0.0;
                for (k = 0; k < nInt2; k++) {
                    costab[k + 1] = costab1q[k + 1];
                    sintab[k + 1] = costab1q[(nInt2 - k) - 1];
                }
                i = costab1q.size(1);
                for (k = i; k <= nd2; k++) {
                    costab[k] = -costab1q[nd2 - k];
                    sintab[k] = costab1q[k - nInt2];
                }
                sintabinv.set_size(1, 0);
            }
            if (useRadix2) {
                internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                        x, x.size(0), costab, sintab, y);
                if (y.size(0) > 1) {
                    nt_re = 1.0 / static_cast<double>(y.size(0));
                    nd2 = y.size(0);
                    for (i = 0; i < nd2; i++) {
                        y[i].re = nt_re * y[i].re;
                        y[i].im = nt_re * y[i].im;
                    }
                }
            } else {
                double nt_im;
                if ((x.size(0) != 1) && ((x.size(0) & 1) == 0)) {
                    int nRows;
                    nRows = x.size(0) / 2;
                    nd2 = (nRows + nRows) - 1;
                    wwc.set_size(nd2);
                    rt = 0;
                    wwc[nRows - 1].re = 1.0;
                    wwc[nRows - 1].im = 0.0;
                    nInt2 = nRows << 1;
                    for (k = 0; k <= nRows - 2; k++) {
                        int b_y;
                        b_y = ((k + 1) << 1) - 1;
                        if (nInt2 - rt <= b_y) {
                            rt += b_y - nInt2;
                        } else {
                            rt += b_y;
                        }
                        nt_im = 3.1415926535897931 * static_cast<double>(rt) /
                                static_cast<double>(nRows);
                        if (nt_im == 0.0) {
                            nt_re = 1.0;
                            nt_im = 0.0;
                        } else {
                            nt_re = cos(nt_im);
                            nt_im = sin(nt_im);
                        }
                        i = (nRows - k) - 2;
                        wwc[i].re = nt_re;
                        wwc[i].im = -nt_im;
                    }
                    i = nd2 - 1;
                    for (k = i; k >= nRows; k--) {
                        wwc[k] = wwc[(nd2 - k) - 1];
                    }
                } else {
                    nd2 = (x.size(0) + x.size(0)) - 1;
                    wwc.set_size(nd2);
                    rt = 0;
                    wwc[x.size(0) - 1].re = 1.0;
                    wwc[x.size(0) - 1].im = 0.0;
                    nInt2 = x.size(0) << 1;
                    i = x.size(0);
                    for (k = 0; k <= i - 2; k++) {
                        int b_y;
                        b_y = ((k + 1) << 1) - 1;
                        if (nInt2 - rt <= b_y) {
                            rt += b_y - nInt2;
                        } else {
                            rt += b_y;
                        }
                        nt_im = 3.1415926535897931 * static_cast<double>(rt) /
                                static_cast<double>(nfft);
                        if (nt_im == 0.0) {
                            nt_re = 1.0;
                            nt_im = 0.0;
                        } else {
                            nt_re = cos(nt_im);
                            nt_im = sin(nt_im);
                        }
                        wwc[(x.size(0) - k) - 2].re = nt_re;
                        wwc[(x.size(0) - k) - 2].im = -nt_im;
                    }
                    i = nd2 - 1;
                    for (k = i; k >= nfft; k--) {
                        wwc[k] = wwc[(nd2 - k) - 1];
                    }
                }
                y.set_size(x.size(0));
                if ((N2blue != 1) && ((x.size(0) & 1) == 0)) {
                    internal::FFTImplementationCallback::b_doHalfLengthBluestein(
                            x, 0, y, x.size(0), x.size(0), N2blue, wwc, costab, sintab, costab,
                            sintabinv);
                } else {
                    nd2 = x.size(0);
                    for (k = 0; k < nd2; k++) {
                        y[k].re = wwc[(nfft + k) - 1].re * x[k];
                        y[k].im = wwc[(nfft + k) - 1].im * -x[k];
                    }
                    i = x.size(0) + 1;
                    for (k = i; k <= nfft; k++) {
                        y[k - 1].re = 0.0;
                        y[k - 1].im = 0.0;
                    }
                    internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                            y, 0, N2blue, costab, sintab, fy);
                    internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                            wwc, N2blue, costab, sintab, fv);
                    nd2 = fy.size(0);
                    for (i = 0; i < nd2; i++) {
                        nt_re = fy[i].re * fv[i].im + fy[i].im * fv[i].re;
                        fy[i].re = fy[i].re * fv[i].re - fy[i].im * fv[i].im;
                        fy[i].im = nt_re;
                    }
                    internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                            fy, N2blue, costab, sintabinv, fv);
                    if (fv.size(0) > 1) {
                        nt_re = 1.0 / static_cast<double>(fv.size(0));
                        nd2 = fv.size(0);
                        for (i = 0; i < nd2; i++) {
                            fv[i].re = nt_re * fv[i].re;
                            fv[i].im = nt_re * fv[i].im;
                        }
                    }
                    i = x.size(0);
                    rt = wwc.size(0);
                    for (k = i; k <= rt; k++) {
                        nt_re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].im;
                        nt_im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].re;
                        if (nt_im == 0.0) {
                            nd2 = k - i;
                            y[nd2].re = nt_re / static_cast<double>(nfft);
                            y[nd2].im = 0.0;
                        } else if (nt_re == 0.0) {
                            nd2 = k - i;
                            y[nd2].re = 0.0;
                            y[nd2].im = nt_im / static_cast<double>(nfft);
                        } else {
                            nd2 = k - i;
                            y[nd2].re = nt_re / static_cast<double>(nfft);
                            y[nd2].im = nt_im / static_cast<double>(nfft);
                        }
                    }
                }
            }
        }
    }

} // namespace coder

//
// File trailer for ifft.cpp
//
// [EOF]
//
