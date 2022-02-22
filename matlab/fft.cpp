//
// File: fft.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "nextpow2.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
namespace coder {
    void fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y) {
        array<creal_T, 1U> r;
        array<double, 2U> costab;
        array<double, 2U> sintab;
        array<double, 2U> sintabinv;
        int nfft;
        nfft = x.size(0);
        if ((x.size(0) == 0) || (x.size(1) == 0)) {
            int i2;
            y.set_size(x.size(0), x.size(1));
            i2 = x.size(0) * x.size(1);
            for (int iy = 0; iy < i2; iy++) {
                y[iy].re = 0.0;
                y[iy].im = 0.0;
            }
        } else {
            int i2;
            int iy;
            int k;
            boolean_T useRadix2;
            useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
            i2 = x.size(0);
            iy = 1;
            if (!useRadix2) {
                if (i2 > 0) {
                    k = nextpow2((i2 + i2) - 1);
                    if (k >= 0) {
                        if (k <= 31) {
                            iy = 1 << k;
                        } else {
                            iy = 0;
                        }
                    } else {
                        iy = 0;
                    }
                }
                i2 = iy;
            }
            internal::FFTImplementationCallback::generate_twiddle_tables(
                    i2, useRadix2, costab, sintab, sintabinv);
            if (useRadix2) {
                int nChan;
                int sz_idx_0;
                nChan = x.size(1);
                y.set_size(x.size(0), x.size(1));
                sz_idx_0 = x.size(0);
                useRadix2 = (x.size(0) != 1);
                for (int chan = 0; chan < nChan; chan++) {
                    int j;
                    j = chan * x.size(0);
                    r.set_size(sz_idx_0);
                    if (nfft > x.size(0)) {
                        r.set_size(sz_idx_0);
                        for (iy = 0; iy < sz_idx_0; iy++) {
                            r[iy].re = 0.0;
                            r[iy].im = 0.0;
                        }
                    }
                    if (useRadix2) {
                        internal::FFTImplementationCallback::doHalfLengthRadix2(
                                x, j, r, nfft, costab, sintab);
                    } else {
                        double temp_im;
                        double temp_re;
                        double twid_im;
                        double twid_re;
                        int i;
                        int iheight;
                        int ju;
                        int nRowsD2;
                        iheight = x.size(0);
                        if (iheight >= nfft) {
                            iheight = nfft;
                        }
                        nRowsD2 = nfft / 2;
                        k = nRowsD2 / 2;
                        iy = 0;
                        ju = 0;
                        for (i = 0; i <= iheight - 2; i++) {
                            boolean_T tst;
                            r[iy].re = x[j + i];
                            r[iy].im = 0.0;
                            i2 = nfft;
                            tst = true;
                            while (tst) {
                                i2 >>= 1;
                                ju ^= i2;
                                tst = ((ju & i2) == 0);
                            }
                            iy = ju;
                        }
                        r[iy].re = x[(j + iheight) - 1];
                        r[iy].im = 0.0;
                        i2 = nfft - 2;
                        if (nfft > 1) {
                            for (i = 0; i <= i2; i += 2) {
                                temp_re = r[i + 1].re;
                                temp_im = r[i + 1].im;
                                twid_re = r[i].re;
                                twid_im = r[i].im;
                                r[i + 1].re = r[i].re - r[i + 1].re;
                                r[i + 1].im = r[i].im - r[i + 1].im;
                                twid_re += temp_re;
                                twid_im += temp_im;
                                r[i].re = twid_re;
                                r[i].im = twid_im;
                            }
                        }
                        i2 = 2;
                        iy = 4;
                        iheight = ((k - 1) << 2) + 1;
                        while (k > 0) {
                            int temp_re_tmp;
                            for (i = 0; i < iheight; i += iy) {
                                temp_re_tmp = i + i2;
                                temp_re = r[temp_re_tmp].re;
                                temp_im = r[temp_re_tmp].im;
                                r[temp_re_tmp].re = r[i].re - temp_re;
                                r[temp_re_tmp].im = r[i].im - temp_im;
                                r[i].re = r[i].re + temp_re;
                                r[i].im = r[i].im + temp_im;
                            }
                            ju = 1;
                            for (j = k; j < nRowsD2; j += k) {
                                int ihi;
                                twid_re = costab[j];
                                twid_im = sintab[j];
                                i = ju;
                                ihi = ju + iheight;
                                while (i < ihi) {
                                    temp_re_tmp = i + i2;
                                    temp_re =
                                            twid_re * r[temp_re_tmp].re - twid_im * r[temp_re_tmp].im;
                                    temp_im =
                                            twid_re * r[temp_re_tmp].im + twid_im * r[temp_re_tmp].re;
                                    r[temp_re_tmp].re = r[i].re - temp_re;
                                    r[temp_re_tmp].im = r[i].im - temp_im;
                                    r[i].re = r[i].re + temp_re;
                                    r[i].im = r[i].im + temp_im;
                                    i += iy;
                                }
                                ju++;
                            }
                            k /= 2;
                            i2 = iy;
                            iy += iy;
                            iheight -= i2;
                        }
                    }
                    i2 = r.size(0);
                    for (iy = 0; iy < i2; iy++) {
                        y[iy + y.size(0) * chan] = r[iy];
                    }
                }
            } else {
                internal::FFTImplementationCallback::dobluesteinfft(
                        x, iy, x.size(0), costab, sintab, sintabinv, y);
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                double varargin_1
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
    void fft(const ::coder::array<double, 1U> &x, double varargin_1,
             ::coder::array<creal_T, 1U> &y) {
        array<double, 2U> costab;
        array<double, 2U> sintab;
        array<double, 2U> sintabinv;
        if ((x.size(0) == 0) || (0 == static_cast<int>(varargin_1))) {
            int N2blue;
            N2blue = static_cast<int>(varargin_1);
            y.set_size(N2blue);
            for (int nRows = 0; nRows < N2blue; nRows++) {
                y[nRows].re = 0.0;
                y[nRows].im = 0.0;
            }
        } else {
            int N2blue;
            int nRows;
            boolean_T useRadix2;
            useRadix2 = ((static_cast<int>(varargin_1) > 0) &&
                         ((static_cast<int>(varargin_1) &
                           (static_cast<int>(varargin_1) - 1)) == 0));
            N2blue = 1;
            if (useRadix2) {
                nRows = static_cast<int>(varargin_1);
            } else {
                if (static_cast<int>(varargin_1) > 0) {
                    N2blue = nextpow2(
                            (static_cast<int>(varargin_1) + static_cast<int>(varargin_1)) - 1);
                    if (N2blue >= 0) {
                        if (N2blue <= 31) {
                            N2blue = 1 << N2blue;
                        } else {
                            N2blue = 0;
                        }
                    } else {
                        N2blue = 0;
                    }
                }
                nRows = N2blue;
            }
            internal::FFTImplementationCallback::generate_twiddle_tables(
                    nRows, useRadix2, costab, sintab, sintabinv);
            if (useRadix2) {
                internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                        x, static_cast<int>(varargin_1), costab, sintab, y);
            } else {
                internal::FFTImplementationCallback::dobluesteinfft(
                        x, N2blue, static_cast<int>(varargin_1), costab, sintab, sintabinv,
                        y);
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
    void fft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y) {
        array<double, 2U> costab;
        array<double, 2U> sintab;
        array<double, 2U> sintabinv;
        if (x.size(0) == 0) {
            y.set_size(0);
        } else {
            int N2blue;
            int nfft;
            boolean_T useRadix2;
            useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
            nfft = x.size(0);
            N2blue = 1;
            if (!useRadix2) {
                if (nfft > 0) {
                    nfft = nextpow2((nfft + nfft) - 1);
                    if (nfft >= 0) {
                        if (nfft <= 31) {
                            N2blue = 1 << nfft;
                        } else {
                            N2blue = 0;
                        }
                    } else {
                        N2blue = 0;
                    }
                }
                nfft = N2blue;
            }
            internal::FFTImplementationCallback::generate_twiddle_tables(
                    nfft, useRadix2, costab, sintab, sintabinv);
            if (useRadix2) {
                internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                        x, x.size(0), costab, sintab, y);
            } else {
                internal::FFTImplementationCallback::dobluesteinfft(
                        x, N2blue, x.size(0), costab, sintab, sintabinv, y);
            }
        }
    }

} // namespace coder

//
// File trailer for fft.cpp
//
// [EOF]
//
