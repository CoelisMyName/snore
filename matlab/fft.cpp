#include "fft.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "fftw3.h"
#include "mylock.h"

namespace coder {
void b_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 2U> b_y;
    array<int, 2U> index_f2;
    array<int, 1U> r;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if (x.size(1) == 0) {
        y.set_size(221, 0);
    } else {
        fftw_plan plan;
        int k;
        int n;
        int yk;
        iodims.n = 221;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = x.size(1);
        howmany_iodims.is = 221;
        howmany_iodims.os = 221;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(221, x.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(1, &iodims, 1, &howmany_iodims,
                                      (double *)&x[0], (fftw_complex *)&y[0],
                                      (unsigned int)FFTW_PRESERVE_INPUT |
                                          (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        n = x.size(1);
        index_f2.set_size(1, x.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (k = 2; k <= n; k++) {
            yk++;
            index_f2[k - 1] = yk;
        }
        yk = 112;
        k = index_f2.size(1);
        do {
            int i;
            r.set_size(index_f2.size(1));
            b_y.set_size(1, index_f2.size(1));
            for (i = 0; i < k; i++) {
                n = index_f2[i];
                r[i] = n - 1;
                b_y[i].re = y[(221 * (n - 1) - yk) + 222].re;
                b_y[i].im = -y[(221 * (n - 1) - yk) + 222].im;
            }
            n = b_y.size(1);
            for (i = 0; i < n; i++) {
                y[(yk + 221 * r[i]) - 1] = b_y[i];
            }
            yk++;
        } while (!(yk == 222));
    }
}

void c_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 2U> b_y;
    array<int, 2U> index_f2;
    array<int, 1U> r;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if (x.size(1) == 0) {
        y.set_size(441, 0);
    } else {
        fftw_plan plan;
        int k;
        int n;
        int yk;
        iodims.n = 441;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = x.size(1);
        howmany_iodims.is = 441;
        howmany_iodims.os = 441;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(441, x.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(1, &iodims, 1, &howmany_iodims,
                                      (double *)&x[0], (fftw_complex *)&y[0],
                                      (unsigned int)FFTW_PRESERVE_INPUT |
                                          (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        n = x.size(1);
        index_f2.set_size(1, x.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (k = 2; k <= n; k++) {
            yk++;
            index_f2[k - 1] = yk;
        }
        yk = 222;
        k = index_f2.size(1);
        do {
            int i;
            r.set_size(index_f2.size(1));
            b_y.set_size(1, index_f2.size(1));
            for (i = 0; i < k; i++) {
                n = index_f2[i];
                r[i] = n - 1;
                b_y[i].re = y[(441 * (n - 1) - yk) + 442].re;
                b_y[i].im = -y[(441 * (n - 1) - yk) + 442].im;
            }
            n = b_y.size(1);
            for (i = 0; i < n; i++) {
                y[(yk + 441 * r[i]) - 1] = b_y[i];
            }
            yk++;
        } while (!(yk == 442));
    }
}

void fft(const ::coder::array<double, 1U> &x, double varargin_1,
         ::coder::array<creal_T, 1U> &y)
{
    array<double, 1U> xPadded;
    array<int, 2U> b_y;
    array<int, 1U> r;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if ((x.size(0) == 0) || (0 == static_cast<int>(varargin_1))) {
        int xSize_idx_0;
        xSize_idx_0 = static_cast<int>(varargin_1);
        y.set_size(xSize_idx_0);
        for (int k = 0; k < xSize_idx_0; k++) {
            y[k].re = 0.0;
            y[k].im = 0.0;
        }
    } else if (x.size(0) < static_cast<int>(varargin_1)) {
        int conjIndex_idx_0;
        int k;
        int xSize_idx_0;
        xSize_idx_0 = x.size(0);
        if (static_cast<int>(varargin_1) < x.size(0)) {
            xSize_idx_0 = static_cast<int>(varargin_1);
        }
        xPadded.set_size(static_cast<int>(varargin_1));
        conjIndex_idx_0 = static_cast<int>(varargin_1);
        for (k = 0; k < conjIndex_idx_0; k++) {
            xPadded[k] = 0.0;
        }
        if (xSize_idx_0 < 1) {
            xSize_idx_0 = 0;
        }
        b_y.set_size(1, xSize_idx_0);
        if (xSize_idx_0 > 0) {
            b_y[0] = 1;
            conjIndex_idx_0 = 1;
            for (k = 2; k <= xSize_idx_0; k++) {
                conjIndex_idx_0++;
                b_y[k - 1] = conjIndex_idx_0;
            }
        }
        r.set_size(b_y.size(1));
        conjIndex_idx_0 = b_y.size(1);
        for (k = 0; k < conjIndex_idx_0; k++) {
            r[k] = b_y[k];
        }
        conjIndex_idx_0 = r.size(0);
        for (k = 0; k < conjIndex_idx_0; k++) {
            xPadded[r[k] - 1] = x[r[k] - 1];
        }
        fftw_plan plan;
        iodims.n = static_cast<int>(varargin_1);
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = 1;
        howmany_iodims.is = xPadded.size(0);
        howmany_iodims.os = static_cast<int>(varargin_1);
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(static_cast<int>(varargin_1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&(xPadded.data())[0],
            (fftw_complex *)&(y.data())[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        xSize_idx_0 = static_cast<int>(varargin_1) / 2 + 2;
        if (xSize_idx_0 <= static_cast<int>(varargin_1)) {
            do {
                conjIndex_idx_0 =
                    (static_cast<int>(varargin_1) - xSize_idx_0) + 2;
                if (conjIndex_idx_0 == static_cast<int>(varargin_1) + 1) {
                    conjIndex_idx_0 = 1;
                }
                y[xSize_idx_0 - 1].re = y[conjIndex_idx_0 - 1].re;
                y[xSize_idx_0 - 1].im = -y[conjIndex_idx_0 - 1].im;
                xSize_idx_0++;
            } while (!(xSize_idx_0 == static_cast<int>(varargin_1) + 1));
        }
    } else {
        fftw_plan plan;
        int xSize_idx_0;
        iodims.n = static_cast<int>(varargin_1);
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = 1;
        howmany_iodims.is = x.size(0);
        howmany_iodims.os = static_cast<int>(varargin_1);
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(static_cast<int>(varargin_1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims,
            (double *)&(((::coder::array<double, 1U> *)&x)->data())[0],
            (fftw_complex *)&(y.data())[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        xSize_idx_0 = static_cast<int>(varargin_1) / 2 + 2;
        if (xSize_idx_0 <= static_cast<int>(varargin_1)) {
            int conjIndex_idx_0;
            do {
                conjIndex_idx_0 =
                    (static_cast<int>(varargin_1) - xSize_idx_0) + 2;
                if (conjIndex_idx_0 == static_cast<int>(varargin_1) + 1) {
                    conjIndex_idx_0 = 1;
                }
                y[xSize_idx_0 - 1].re = y[conjIndex_idx_0 - 1].re;
                y[xSize_idx_0 - 1].im = -y[conjIndex_idx_0 - 1].im;
                xSize_idx_0++;
            } while (!(xSize_idx_0 == static_cast<int>(varargin_1) + 1));
        }
    }
}

void fft(const ::coder::array<double, 2U> &x, double varargin_1,
         ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 2U> b_y;
    array<double, 2U> xPadded;
    array<int, 2U> index_f2;
    array<int, 1U> r;
    array<int, 1U> r1;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if ((x.size(0) == 0) || (x.size(1) == 0) ||
        (0 == static_cast<int>(varargin_1))) {
        int yk;
        y.set_size(static_cast<int>(varargin_1), x.size(1));
        yk = static_cast<int>(varargin_1) * x.size(1);
        for (int i = 0; i < yk; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
        }
    } else if (x.size(0) < static_cast<int>(varargin_1)) {
        int i;
        int index_f1;
        int k;
        int n;
        int yk;
        n = x.size(0);
        if (static_cast<int>(varargin_1) < x.size(0)) {
            n = static_cast<int>(varargin_1);
        }
        index_f1 = MAX_int32_T;
        if (x.size(1) < MAX_int32_T) {
            index_f1 = x.size(1);
        }
        if (x.size(1) < index_f1) {
            index_f1 = x.size(1);
        }
        xPadded.set_size(static_cast<int>(varargin_1), x.size(1));
        yk = static_cast<int>(varargin_1) * x.size(1);
        for (i = 0; i < yk; i++) {
            xPadded[i] = 0.0;
        }
        if (n < 1) {
            n = 0;
        }
        index_f2.set_size(1, n);
        if (n > 0) {
            index_f2[0] = 1;
            yk = 1;
            for (k = 2; k <= n; k++) {
                yk++;
                index_f2[k - 1] = yk;
            }
        }
        r.set_size(index_f2.size(1));
        yk = index_f2.size(1);
        for (i = 0; i < yk; i++) {
            r[i] = index_f2[i];
        }
        index_f2.set_size(1, index_f1);
        index_f2[0] = 1;
        yk = 1;
        for (k = 2; k <= index_f1; k++) {
            yk++;
            index_f2[k - 1] = yk;
        }
        r1.set_size(index_f2.size(1));
        yk = index_f2.size(1);
        for (i = 0; i < yk; i++) {
            r1[i] = index_f2[i];
        }
        yk = r1.size(0);
        for (i = 0; i < yk; i++) {
            n = r.size(0);
            for (k = 0; k < n; k++) {
                xPadded[(r[k] + xPadded.size(0) * (r1[i] - 1)) - 1] =
                    x[(r[k] + x.size(0) * (r1[i] - 1)) - 1];
            }
        }
        fftw_plan plan;
        iodims.n = static_cast<int>(varargin_1);
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = xPadded.size(1);
        howmany_iodims.is = xPadded.size(0);
        howmany_iodims.os = static_cast<int>(varargin_1);
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(static_cast<int>(varargin_1), xPadded.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&xPadded[0],
            (fftw_complex *)&y[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        index_f1 = static_cast<int>(varargin_1) / 2 + 2;
        if (index_f1 <= static_cast<int>(varargin_1)) {
            n = xPadded.size(1);
            index_f2.set_size(1, xPadded.size(1));
            index_f2[0] = 1;
            yk = 1;
            for (k = 2; k <= n; k++) {
                yk++;
                index_f2[k - 1] = yk;
            }
            yk = index_f2.size(1);
            do {
                n = (static_cast<int>(varargin_1) - index_f1) + 1;
                if (n + 1 == static_cast<int>(varargin_1) + 1) {
                    n = 0;
                }
                r.set_size(index_f2.size(1));
                b_y.set_size(1, index_f2.size(1));
                for (i = 0; i < yk; i++) {
                    k = index_f2[i];
                    r[i] = k - 1;
                    b_y[i].re = y[n + y.size(0) * (k - 1)].re;
                    b_y[i].im = -y[n + y.size(0) * (k - 1)].im;
                }
                n = b_y.size(1);
                for (i = 0; i < n; i++) {
                    y[(index_f1 + y.size(0) * r[i]) - 1] = b_y[i];
                }
                index_f1++;
            } while (!(index_f1 == static_cast<int>(varargin_1) + 1));
        }
    } else {
        fftw_plan plan;
        int index_f1;
        iodims.n = static_cast<int>(varargin_1);
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = x.size(1);
        howmany_iodims.is = x.size(0);
        howmany_iodims.os = static_cast<int>(varargin_1);
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(static_cast<int>(varargin_1), x.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(1, &iodims, 1, &howmany_iodims,
                                      (double *)&x[0], (fftw_complex *)&y[0],
                                      (unsigned int)FFTW_PRESERVE_INPUT |
                                          (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        index_f1 = static_cast<int>(varargin_1) / 2 + 2;
        if (index_f1 <= static_cast<int>(varargin_1)) {
            int k;
            int n;
            int yk;
            n = x.size(1);
            index_f2.set_size(1, x.size(1));
            index_f2[0] = 1;
            yk = 1;
            for (k = 2; k <= n; k++) {
                yk++;
                index_f2[k - 1] = yk;
            }
            yk = index_f2.size(1);
            do {
                int i;
                n = (static_cast<int>(varargin_1) - index_f1) + 1;
                if (n + 1 == static_cast<int>(varargin_1) + 1) {
                    n = 0;
                }
                r.set_size(index_f2.size(1));
                b_y.set_size(1, index_f2.size(1));
                for (i = 0; i < yk; i++) {
                    k = index_f2[i];
                    r[i] = k - 1;
                    b_y[i].re = y[n + y.size(0) * (k - 1)].re;
                    b_y[i].im = -y[n + y.size(0) * (k - 1)].im;
                }
                n = b_y.size(1);
                for (i = 0; i < n; i++) {
                    y[(index_f1 + y.size(0) * r[i]) - 1] = b_y[i];
                }
                index_f1++;
            } while (!(index_f1 == static_cast<int>(varargin_1) + 1));
        }
    }
}

void fft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y)
{
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    int nfft;
    nfft = x.size(0) + 1;
    if (x.size(0) == 0) {
        y.set_size(0);
    } else {
        fftw_plan plan;
        int xSize_idx_0;
        iodims.n = x.size(0);
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = 1;
        howmany_iodims.is = x.size(0);
        howmany_iodims.os = x.size(0);
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(x.size(0));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims,
            (double *)&(((::coder::array<double, 1U> *)&x)->data())[0],
            (fftw_complex *)&(y.data())[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        xSize_idx_0 = x.size(0) / 2 + 2;
        if (xSize_idx_0 <= x.size(0)) {
            int conjIndex_idx_0;
            do {
                conjIndex_idx_0 = (nfft - xSize_idx_0) + 1;
                if (conjIndex_idx_0 == nfft) {
                    conjIndex_idx_0 = 1;
                }
                y[xSize_idx_0 - 1].re = y[conjIndex_idx_0 - 1].re;
                y[xSize_idx_0 - 1].im = -y[conjIndex_idx_0 - 1].im;
                xSize_idx_0++;
            } while (!(xSize_idx_0 == nfft));
        }
    }
}

void fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 2U> b_y;
    array<int, 2U> index_f2;
    array<int, 1U> r;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if (x.size(1) == 0) {
        y.set_size(160, 0);
    } else {
        fftw_plan plan;
        int k;
        int n;
        int yk;
        iodims.n = 160;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = x.size(1);
        howmany_iodims.is = 160;
        howmany_iodims.os = 160;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(160, x.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(1, &iodims, 1, &howmany_iodims,
                                      (double *)&x[0], (fftw_complex *)&y[0],
                                      (unsigned int)FFTW_PRESERVE_INPUT |
                                          (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        n = x.size(1);
        index_f2.set_size(1, x.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (k = 2; k <= n; k++) {
            yk++;
            index_f2[k - 1] = yk;
        }
        yk = 82;
        k = index_f2.size(1);
        do {
            int i;
            r.set_size(index_f2.size(1));
            b_y.set_size(1, index_f2.size(1));
            for (i = 0; i < k; i++) {
                n = index_f2[i];
                r[i] = n - 1;
                b_y[i].re = y[(160 * (n - 1) - yk) + 161].re;
                b_y[i].im = -y[(160 * (n - 1) - yk) + 161].im;
            }
            n = b_y.size(1);
            for (i = 0; i < n; i++) {
                y[(yk + 160 * r[i]) - 1] = b_y[i];
            }
            yk++;
        } while (!(yk == 161));
    }
}

} // namespace coder
