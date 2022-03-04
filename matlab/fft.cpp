#include "fft.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

namespace coder {
void b_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    if (x.size(1) == 0) {
        y.set_size(2048, 0);
    } else {
        int i;
        int loop_ub;
        int nChan;
        nChan = x.size(1);
        y.set_size(2048, x.size(1));
        loop_ub = 2048 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
        for (loop_ub = 0; loop_ub < nChan; loop_ub++) {
            for (i = 0; i < 2048; i++) {
                y[i + 2048 * loop_ub].re = 0.0;
                y[i + 2048 * loop_ub].im = 0.0;
            }
            internal::FFTImplementationCallback::c_doHalfLengthRadix2(
                x, loop_ub * 551, *(creal_T(*)[2048]) & y[2048 * loop_ub]);
        }
    }
}

void c_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    if (x.size(1) == 0) {
        y.set_size(2048, 0);
    } else {
        int i;
        int loop_ub;
        int nChan;
        nChan = x.size(1);
        y.set_size(2048, x.size(1));
        loop_ub = 2048 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
        for (loop_ub = 0; loop_ub < nChan; loop_ub++) {
            for (i = 0; i < 2048; i++) {
                y[i + 2048 * loop_ub].re = 0.0;
                y[i + 2048 * loop_ub].im = 0.0;
            }
            internal::FFTImplementationCallback::e_doHalfLengthRadix2(
                x, loop_ub * 600, *(creal_T(*)[2048]) & y[2048 * loop_ub]);
        }
    }
}

void d_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    if (x.size(1) == 0) {
        y.set_size(4096, 0);
    } else {
        int i;
        int loop_ub;
        int nChan;
        nChan = x.size(1);
        y.set_size(4096, x.size(1));
        loop_ub = 4096 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
        for (loop_ub = 0; loop_ub < nChan; loop_ub++) {
            for (i = 0; i < 4096; i++) {
                y[i + 4096 * loop_ub].re = 0.0;
                y[i + 4096 * loop_ub].im = 0.0;
            }
            internal::FFTImplementationCallback::f_doHalfLengthRadix2(
                x, loop_ub * 1103, *(creal_T(*)[4096]) & y[4096 * loop_ub]);
        }
    }
}

void e_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    if (x.size(1) == 0) {
        y.set_size(4096, 0);
    } else {
        int i;
        int loop_ub;
        int nChan;
        nChan = x.size(1);
        y.set_size(4096, x.size(1));
        loop_ub = 4096 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
        for (loop_ub = 0; loop_ub < nChan; loop_ub++) {
            for (i = 0; i < 4096; i++) {
                y[i + 4096 * loop_ub].re = 0.0;
                y[i + 4096 * loop_ub].im = 0.0;
            }
            internal::FFTImplementationCallback::h_doHalfLengthRadix2(
                x, loop_ub * 1200, *(creal_T(*)[4096]) & y[4096 * loop_ub]);
        }
    }
}

void f_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    if (x.size(1) == 0) {
        y.set_size(8192, 0);
    } else {
        int i;
        int loop_ub;
        int nChan;
        nChan = x.size(1);
        y.set_size(8192, x.size(1));
        loop_ub = 8192 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
        for (loop_ub = 0; loop_ub < nChan; loop_ub++) {
            for (i = 0; i < 8192; i++) {
                y[i + 8192 * loop_ub].re = 0.0;
                y[i + 8192 * loop_ub].im = 0.0;
            }
            internal::FFTImplementationCallback::i_doHalfLengthRadix2(
                x, loop_ub * 2205, *(creal_T(*)[8192]) & y[8192 * loop_ub]);
        }
    }
}

void fft(const ::coder::array<double, 1U> &x, double varargin_1,
         ::coder::array<creal_T, 1U> &y)
{
    array<double, 2U> costab;
    array<double, 2U> sintab;
    array<double, 2U> sintabinv;
    int N2blue;
    int nRows;
    if ((x.size(0) == 0) || (0 == static_cast<int>(varargin_1))) {
        N2blue = static_cast<int>(varargin_1);
        y.set_size(N2blue);
        for (nRows = 0; nRows < N2blue; nRows++) {
            y[nRows].re = 0.0;
            y[nRows].im = 0.0;
        }
    } else {
        boolean_T useRadix2;
        useRadix2 = ((static_cast<int>(varargin_1) > 0) &&
                     ((static_cast<int>(varargin_1) &
                       (static_cast<int>(varargin_1) - 1)) == 0));
        internal::FFTImplementationCallback::get_algo_sizes(
            static_cast<int>(varargin_1), useRadix2, &N2blue, &nRows);
        internal::FFTImplementationCallback::generate_twiddle_tables(
            nRows, useRadix2, costab, sintab, sintabinv);
        if (useRadix2) {
            internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                x, static_cast<int>(varargin_1), costab, sintab, y);
        } else {
            internal::FFTImplementationCallback::dobluesteinfft(
                x, N2blue, static_cast<int>(varargin_1), costab, sintab,
                sintabinv, y);
        }
    }
}

void fft(const ::coder::array<double, 2U> &x, double varargin_1,
         ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 1U> r;
    array<double, 2U> costab;
    array<double, 2U> sintab;
    array<double, 2U> sintabinv;
    int nRows;
    int ySize_idx_1;
    if ((x.size(0) == 0) || (x.size(1) == 0) ||
        (0 == static_cast<int>(varargin_1))) {
        y.set_size(static_cast<int>(varargin_1), x.size(1));
        nRows = static_cast<int>(varargin_1) * x.size(1);
        for (int i = 0; i < nRows; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
    } else {
        boolean_T useRadix2;
        useRadix2 = ((static_cast<int>(varargin_1) > 0) &&
                     ((static_cast<int>(varargin_1) &
                       (static_cast<int>(varargin_1) - 1)) == 0));
        internal::FFTImplementationCallback::get_algo_sizes(
            static_cast<int>(varargin_1), useRadix2, &ySize_idx_1, &nRows);
        internal::FFTImplementationCallback::generate_twiddle_tables(
            nRows, useRadix2, costab, sintab, sintabinv);
        if (useRadix2) {
            int i;
            ySize_idx_1 = x.size(1);
            y.set_size(static_cast<int>(varargin_1), x.size(1));
            if (static_cast<int>(varargin_1) > x.size(0)) {
                y.set_size(static_cast<int>(varargin_1), x.size(1));
                nRows = static_cast<int>(varargin_1) * x.size(1);
                for (i = 0; i < nRows; i++) {
                    y[i].re = 0.0;
                    y[i].im = 0.0;
                }
            }
            for (int chan = 0; chan < ySize_idx_1; chan++) {
                internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
                    x, chan * x.size(0), static_cast<int>(varargin_1), costab,
                    sintab, r);
                nRows = r.size(0);
                for (i = 0; i < nRows; i++) {
                    y[i + y.size(0) * chan] = r[i];
                }
            }
        } else {
            internal::FFTImplementationCallback::dobluesteinfft(
                x, ySize_idx_1, static_cast<int>(varargin_1), costab, sintab,
                sintabinv, y);
        }
    }
}

void fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    if (x.size(1) == 0) {
        y.set_size(1024, 0);
    } else {
        int i;
        int loop_ub;
        int nChan;
        nChan = x.size(1);
        y.set_size(1024, x.size(1));
        loop_ub = 1024 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
        for (loop_ub = 0; loop_ub < nChan; loop_ub++) {
            for (i = 0; i < 1024; i++) {
                y[i + 1024 * loop_ub].re = 0.0;
                y[i + 1024 * loop_ub].im = 0.0;
            }
            internal::FFTImplementationCallback::doHalfLengthRadix2(
                x, loop_ub * 400, *(creal_T(*)[1024]) & y[1024 * loop_ub]);
        }
    }
}

void g_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    if (x.size(1) == 0) {
        y.set_size(8192, 0);
    } else {
        int i;
        int loop_ub;
        int nChan;
        nChan = x.size(1);
        y.set_size(8192, x.size(1));
        loop_ub = 8192 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
        for (loop_ub = 0; loop_ub < nChan; loop_ub++) {
            for (i = 0; i < 8192; i++) {
                y[i + 8192 * loop_ub].re = 0.0;
                y[i + 8192 * loop_ub].im = 0.0;
            }
            internal::FFTImplementationCallback::k_doHalfLengthRadix2(
                x, loop_ub * 2400, *(creal_T(*)[8192]) & y[8192 * loop_ub]);
        }
    }
}

} // namespace coder
