#include "ifft.h"
#include "SnoringRecognition_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "fftw3.h"
#include "mylock.h"

namespace coder {
void b_ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 2U> b_x;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if (x.size(1) == 0) {
        y.set_size(4096, 0);
    } else {
        int i;
        int loop_ub;
        b_x.set_size(4096, x.size(1));
        loop_ub = 4096 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_x[i].re = x[i];
            b_x[i].im = 0.0;
        }
        fftw_plan plan;
        int b_sign;
        b_sign = FFTW_BACKWARD;
        iodims.n = 4096;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = b_x.size(1);
        howmany_iodims.is = 4096;
        howmany_iodims.os = 4096;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(4096, b_x.size(1));
        mylock();
        plan = fftw_plan_guru_dft(
            1, &iodims, 1, &howmany_iodims, (fftw_complex *)&b_x[0],
            (fftw_complex *)&y[0], b_sign,
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        loop_ub = 4096 * y.size(1);
        y.set_size(4096, y.size(1));
        for (i = 0; i < loop_ub; i++) {
            double ai;
            double im;
            double re;
            im = y[i].re;
            ai = y[i].im;
            if (ai == 0.0) {
                re = im / 4096.0;
                im = 0.0;
            } else if (im == 0.0) {
                re = 0.0;
                im = ai / 4096.0;
            } else {
                re = im / 4096.0;
                im = ai / 4096.0;
            }
            y[i].re = re;
            y[i].im = im;
        }
    }
}

void c_ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 2U> b_x;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if (x.size(1) == 0) {
        y.set_size(8192, 0);
    } else {
        int i;
        int loop_ub;
        b_x.set_size(8192, x.size(1));
        loop_ub = 8192 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_x[i].re = x[i];
            b_x[i].im = 0.0;
        }
        fftw_plan plan;
        int b_sign;
        b_sign = FFTW_BACKWARD;
        iodims.n = 8192;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = b_x.size(1);
        howmany_iodims.is = 8192;
        howmany_iodims.os = 8192;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(8192, b_x.size(1));
        mylock();
        plan = fftw_plan_guru_dft(
            1, &iodims, 1, &howmany_iodims, (fftw_complex *)&b_x[0],
            (fftw_complex *)&y[0], b_sign,
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        loop_ub = 8192 * y.size(1);
        y.set_size(8192, y.size(1));
        for (i = 0; i < loop_ub; i++) {
            double ai;
            double im;
            double re;
            im = y[i].re;
            ai = y[i].im;
            if (ai == 0.0) {
                re = im / 8192.0;
                im = 0.0;
            } else if (im == 0.0) {
                re = 0.0;
                im = ai / 8192.0;
            } else {
                re = im / 8192.0;
                im = ai / 8192.0;
            }
            y[i].re = re;
            y[i].im = im;
        }
    }
}

void ifft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y)
{
    array<creal_T, 1U> b_x;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if (x.size(0) == 0) {
        y.set_size(0);
    } else {
        int i;
        int loop_ub;
        int x_re;
        b_x.set_size(x.size(0));
        loop_ub = x.size(0);
        for (i = 0; i < loop_ub; i++) {
            b_x[i].re = x[i];
            b_x[i].im = 0.0;
        }
        fftw_plan plan;
        int b_sign;
        b_sign = FFTW_BACKWARD;
        iodims.n = x.size(0);
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = 1;
        howmany_iodims.is = b_x.size(0);
        howmany_iodims.os = x.size(0);
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(x.size(0));
        mylock();
        plan = fftw_plan_guru_dft(
            1, &iodims, 1, &howmany_iodims, (fftw_complex *)&(b_x.data())[0],
            (fftw_complex *)&(y.data())[0], b_sign,
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        x_re = x.size(0);
        loop_ub = y.size(0);
        for (i = 0; i < loop_ub; i++) {
            double ai;
            double im;
            double re;
            im = y[i].re;
            ai = y[i].im;
            if (ai == 0.0) {
                re = im / static_cast<double>(x_re);
                im = 0.0;
            } else if (im == 0.0) {
                re = 0.0;
                im = ai / static_cast<double>(x_re);
            } else {
                re = im / static_cast<double>(x_re);
                im = ai / static_cast<double>(x_re);
            }
            y[i].re = re;
            y[i].im = im;
        }
    }
}

void ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
    array<creal_T, 2U> b_x;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    if (x.size(1) == 0) {
        y.set_size(2048, 0);
    } else {
        int i;
        int loop_ub;
        b_x.set_size(2048, x.size(1));
        loop_ub = 2048 * x.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_x[i].re = x[i];
            b_x[i].im = 0.0;
        }
        fftw_plan plan;
        int b_sign;
        b_sign = FFTW_BACKWARD;
        iodims.n = 2048;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = b_x.size(1);
        howmany_iodims.is = 2048;
        howmany_iodims.os = 2048;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        y.set_size(2048, b_x.size(1));
        mylock();
        plan = fftw_plan_guru_dft(
            1, &iodims, 1, &howmany_iodims, (fftw_complex *)&b_x[0],
            (fftw_complex *)&y[0], b_sign,
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        loop_ub = 2048 * y.size(1);
        y.set_size(2048, y.size(1));
        for (i = 0; i < loop_ub; i++) {
            double ai;
            double im;
            double re;
            im = y[i].re;
            ai = y[i].im;
            if (ai == 0.0) {
                re = im / 2048.0;
                im = 0.0;
            } else if (im == 0.0) {
                re = 0.0;
                im = ai / 2048.0;
            } else {
                re = im / 2048.0;
                im = ai / 2048.0;
            }
            y[i].re = re;
            y[i].im = im;
        }
    }
}

} // namespace coder
