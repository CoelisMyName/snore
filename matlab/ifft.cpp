#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "SnoringRecognition_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

namespace coder {
void ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 1U> b_fv;
    array<creal_T, 1U> fv;
    array<creal_T, 1U> r;
    array<creal_T, 1U> wwc;
    array<double, 2U> costab;
    array<double, 2U> sintab;
    array<double, 2U> sintabinv;
    int N2blue;
    int nRows;
    int nfft;
    boolean_T ishalflength;
    nfft = x.size(0);
    if (x.size(0) == 0) {
        y.set_size(0, x.size(1));
    } else {
        boolean_T useRadix2;
        useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
        internal::FFTImplementationCallback::get_algo_sizes(
            x.size(0), useRadix2, &N2blue, &nRows);
        internal::FFTImplementationCallback::c_generate_twiddle_tables(
            nRows, useRadix2, costab, sintab, sintabinv);
        if (useRadix2) {
            int i;
            int nChan;
            nChan = x.size(1);
            y.set_size(x.size(0), x.size(1));
            for (int nInt2 = 0; nInt2 < nChan; nInt2++) {
                internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                    x, nInt2 * x.size(0), nfft, costab, sintab, r);
                nRows = r.size(0);
                for (i = 0; i < nRows; i++) {
                    y[i + y.size(0) * nInt2] = r[i];
                }
            }
            if (y.size(0) > 1) {
                double nt_re;
                nt_re = 1.0 / static_cast<double>(y.size(0));
                nRows = y.size(0) * y.size(1);
                for (i = 0; i < nRows; i++) {
                    y[i].re = nt_re * y[i].re;
                    y[i].im = nt_re * y[i].im;
                }
            }
        } else {
            double nt_im;
            double nt_re;
            int i;
            int k;
            int nChan;
            int nInt2;
            int nInt2m1;
            int rt;
            nChan = x.size(1);
            if ((x.size(0) != 1) && ((x.size(0) & 1) == 0)) {
                nRows = x.size(0) / 2;
                nInt2m1 = (nRows + nRows) - 1;
                wwc.set_size(nInt2m1);
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
                i = nInt2m1 - 1;
                for (k = i; k >= nRows; k--) {
                    wwc[k] = wwc[(nInt2m1 - k) - 1];
                }
            } else {
                nInt2m1 = (x.size(0) + x.size(0)) - 1;
                wwc.set_size(nInt2m1);
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
                i = nInt2m1 - 1;
                for (k = i; k >= nfft; k--) {
                    wwc[k] = wwc[(nInt2m1 - k) - 1];
                }
            }
            rt = x.size(0);
            y.set_size(x.size(0), x.size(1));
            if (0 <= x.size(1) - 1) {
                rt = x.size(0);
                if ((N2blue != 1) && ((x.size(0) & 1) == 0)) {
                    ishalflength = true;
                } else {
                    ishalflength = false;
                }
            }
            for (nInt2 = 0; nInt2 < nChan; nInt2++) {
                nRows = nInt2 * x.size(0);
                r.set_size(rt);
                if (nfft > x.size(0)) {
                    r.set_size(rt);
                    for (i = 0; i < rt; i++) {
                        r[i].re = 0.0;
                        r[i].im = 0.0;
                    }
                }
                if (ishalflength) {
                    internal::FFTImplementationCallback::
                        b_doHalfLengthBluestein(x, nRows, r, x.size(0), nfft,
                                                N2blue, wwc, costab, sintab,
                                                costab, sintabinv);
                } else {
                    nInt2m1 = x.size(0);
                    if (nfft < nInt2m1) {
                        nInt2m1 = nfft;
                    }
                    for (k = 0; k < nInt2m1; k++) {
                        i = nRows + k;
                        r[k].re = wwc[(nfft + k) - 1].re * x[i];
                        r[k].im = wwc[(nfft + k) - 1].im * -x[i];
                    }
                    i = nInt2m1 + 1;
                    for (k = i; k <= nfft; k++) {
                        r[k - 1].re = 0.0;
                        r[k - 1].im = 0.0;
                    }
                    internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                        r, N2blue, costab, sintab, fv);
                    internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                        wwc, N2blue, costab, sintab, b_fv);
                    b_fv.set_size(fv.size(0));
                    nRows = fv.size(0);
                    for (i = 0; i < nRows; i++) {
                        nt_re = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
                        b_fv[i].re =
                            fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
                        b_fv[i].im = nt_re;
                    }
                    internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                        b_fv, N2blue, costab, sintabinv, fv);
                    if (fv.size(0) > 1) {
                        nt_re = 1.0 / static_cast<double>(fv.size(0));
                        nRows = fv.size(0);
                        for (i = 0; i < nRows; i++) {
                            fv[i].re = nt_re * fv[i].re;
                            fv[i].im = nt_re * fv[i].im;
                        }
                    }
                    i = wwc.size(0);
                    for (k = nfft; k <= i; k++) {
                        nt_re = wwc[k - 1].re * fv[k - 1].re +
                                wwc[k - 1].im * fv[k - 1].im;
                        nt_im = wwc[k - 1].re * fv[k - 1].im -
                                wwc[k - 1].im * fv[k - 1].re;
                        if (nt_im == 0.0) {
                            r[k - nfft].re = nt_re / static_cast<double>(nfft);
                            r[k - nfft].im = 0.0;
                        } else if (nt_re == 0.0) {
                            r[k - nfft].re = 0.0;
                            r[k - nfft].im = nt_im / static_cast<double>(nfft);
                        } else {
                            r[k - nfft].re = nt_re / static_cast<double>(nfft);
                            r[k - nfft].im = nt_im / static_cast<double>(nfft);
                        }
                    }
                }
                nRows = r.size(0);
                for (i = 0; i < nRows; i++) {
                    y[i + y.size(0) * nInt2] = r[i];
                }
            }
        }
    }
}

void ifft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y)
{
    array<creal_T, 1U> b_fv;
    array<creal_T, 1U> fv;
    array<creal_T, 1U> wwc;
    array<double, 2U> costab;
    array<double, 2U> sintab;
    array<double, 2U> sintabinv;
    int N2blue;
    int minNrowsNx;
    int nfft;
    nfft = x.size(0);
    if (x.size(0) == 0) {
        y.set_size(0);
    } else {
        boolean_T useRadix2;
        useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
        internal::FFTImplementationCallback::get_algo_sizes(
            x.size(0), useRadix2, &N2blue, &minNrowsNx);
        internal::FFTImplementationCallback::c_generate_twiddle_tables(
            minNrowsNx, useRadix2, costab, sintab, sintabinv);
        if (useRadix2) {
            internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                x, x.size(0), costab, sintab, y);
            if (y.size(0) > 1) {
                double nt_re;
                nt_re = 1.0 / static_cast<double>(y.size(0));
                minNrowsNx = y.size(0);
                for (int i = 0; i < minNrowsNx; i++) {
                    y[i].re = nt_re * y[i].re;
                    y[i].im = nt_re * y[i].im;
                }
            }
        } else {
            double nt_im;
            double nt_re;
            int i;
            int k;
            int nInt2m1;
            if ((x.size(0) != 1) && ((x.size(0) & 1) == 0)) {
                int nInt2;
                int rt;
                minNrowsNx = x.size(0) / 2;
                nInt2m1 = (minNrowsNx + minNrowsNx) - 1;
                wwc.set_size(nInt2m1);
                rt = 0;
                wwc[minNrowsNx - 1].re = 1.0;
                wwc[minNrowsNx - 1].im = 0.0;
                nInt2 = minNrowsNx << 1;
                for (k = 0; k <= minNrowsNx - 2; k++) {
                    int b_y;
                    b_y = ((k + 1) << 1) - 1;
                    if (nInt2 - rt <= b_y) {
                        rt += b_y - nInt2;
                    } else {
                        rt += b_y;
                    }
                    nt_im = 3.1415926535897931 * static_cast<double>(rt) /
                            static_cast<double>(minNrowsNx);
                    if (nt_im == 0.0) {
                        nt_re = 1.0;
                        nt_im = 0.0;
                    } else {
                        nt_re = cos(nt_im);
                        nt_im = sin(nt_im);
                    }
                    i = (minNrowsNx - k) - 2;
                    wwc[i].re = nt_re;
                    wwc[i].im = -nt_im;
                }
                i = nInt2m1 - 1;
                for (k = i; k >= minNrowsNx; k--) {
                    wwc[k] = wwc[(nInt2m1 - k) - 1];
                }
            } else {
                int nInt2;
                int rt;
                nInt2m1 = (x.size(0) + x.size(0)) - 1;
                wwc.set_size(nInt2m1);
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
                i = nInt2m1 - 1;
                for (k = i; k >= nfft; k--) {
                    wwc[k] = wwc[(nInt2m1 - k) - 1];
                }
            }
            y.set_size(x.size(0));
            if ((N2blue != 1) && ((x.size(0) & 1) == 0)) {
                internal::FFTImplementationCallback::b_doHalfLengthBluestein(
                    x, y, x.size(0), x.size(0), N2blue, wwc, costab, sintab,
                    costab, sintabinv);
            } else {
                minNrowsNx = x.size(0);
                for (k = 0; k < minNrowsNx; k++) {
                    y[k].re = wwc[(nfft + k) - 1].re * x[k];
                    y[k].im = wwc[(nfft + k) - 1].im * -x[k];
                }
                i = x.size(0) + 1;
                for (k = i; k <= nfft; k++) {
                    y[k - 1].re = 0.0;
                    y[k - 1].im = 0.0;
                }
                internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                    y, N2blue, costab, sintab, fv);
                internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                    wwc, N2blue, costab, sintab, b_fv);
                b_fv.set_size(fv.size(0));
                minNrowsNx = fv.size(0);
                for (i = 0; i < minNrowsNx; i++) {
                    nt_re = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
                    b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
                    b_fv[i].im = nt_re;
                }
                internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                    b_fv, N2blue, costab, sintabinv, fv);
                if (fv.size(0) > 1) {
                    nt_re = 1.0 / static_cast<double>(fv.size(0));
                    minNrowsNx = fv.size(0);
                    for (i = 0; i < minNrowsNx; i++) {
                        fv[i].re = nt_re * fv[i].re;
                        fv[i].im = nt_re * fv[i].im;
                    }
                }
                i = x.size(0);
                minNrowsNx = wwc.size(0);
                for (k = i; k <= minNrowsNx; k++) {
                    nt_re = wwc[k - 1].re * fv[k - 1].re +
                            wwc[k - 1].im * fv[k - 1].im;
                    nt_im = wwc[k - 1].re * fv[k - 1].im -
                            wwc[k - 1].im * fv[k - 1].re;
                    if (nt_im == 0.0) {
                        nInt2m1 = k - i;
                        y[nInt2m1].re = nt_re / static_cast<double>(nfft);
                        y[nInt2m1].im = 0.0;
                    } else if (nt_re == 0.0) {
                        nInt2m1 = k - i;
                        y[nInt2m1].re = 0.0;
                        y[nInt2m1].im = nt_im / static_cast<double>(nfft);
                    } else {
                        nInt2m1 = k - i;
                        y[nInt2m1].re = nt_re / static_cast<double>(nfft);
                        y[nInt2m1].im = nt_im / static_cast<double>(nfft);
                    }
                }
            }
        }
    }
}

} // namespace coder
