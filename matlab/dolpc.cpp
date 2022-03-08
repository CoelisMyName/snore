#include "dolpc.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "fftw3.h"
#include "mylock.h"
#include <string.h>

void dolpc(const coder::array<double, 2U> &x, coder::array<double, 2U> &y)
{
    coder::array<creal_T, 2U> d_x;
    coder::array<creal_T, 2U> r;
    coder::array<double, 2U> b_r;
    coder::array<double, 2U> b_x;
    coder::array<double, 2U> b_y;
    coder::array<double, 2U> c_x;
    coder::array<double, 2U> c_y;
    coder::array<double, 2U> temp_A;
    coder::array<double, 2U> temp_E;
    coder::array<double, 1U> e;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    double temp_a_data[12];
    double temp_auf_data[12];
    double re;
    double temp_J;
    double temp_kprod;
    int b_i;
    int i;
    int i1;
    int i4;
    int i5;
    int input_sizes_idx_0;
    int loop_ub;
    int ncols;
    int result;
    int sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    if (2 > x.size(0) - 1) {
        i = 0;
        i1 = 1;
        ncols = -1;
    } else {
        i = x.size(0) - 2;
        i1 = -1;
        ncols = 1;
    }
    if ((x.size(0) != 0) && (x.size(1) != 0)) {
        result = x.size(1);
    } else if ((div_s32_floor(ncols - i, i1) + 1 != 0) && (x.size(1) != 0)) {
        result = x.size(1);
    } else {
        result = x.size(1);
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((x.size(0) != 0) && (x.size(1) != 0))) {
        input_sizes_idx_0 = x.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes ||
        ((div_s32_floor(ncols - i, i1) + 1 != 0) && (x.size(1) != 0))) {
        sizes_idx_0 = div_s32_floor(ncols - i, i1) + 1;
    } else {
        sizes_idx_0 = 0;
    }
    loop_ub = x.size(1);
    b_x.set_size(div_s32_floor(ncols - i, i1) + 1, x.size(1));
    for (int i2 = 0; i2 < loop_ub; i2++) {
        b_i = div_s32_floor(ncols - i, i1);
        for (int i3 = 0; i3 <= b_i; i3++) {
            b_x[i3 + b_x.size(0) * i2] = x[(i + i1 * i3) + x.size(0) * i2];
        }
    }
    c_x.set_size(input_sizes_idx_0 + sizes_idx_0, result);
    for (i = 0; i < result; i++) {
        for (i1 = 0; i1 < input_sizes_idx_0; i1++) {
            c_x[i1 + c_x.size(0) * i] = x[i1 + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < result; i++) {
        for (i1 = 0; i1 < sizes_idx_0; i1++) {
            c_x[(i1 + input_sizes_idx_0) + c_x.size(0) * i] =
                b_x[i1 + sizes_idx_0 * i];
        }
    }
    if ((c_x.size(0) == 0) || (c_x.size(1) == 0)) {
        r.set_size(c_x.size(0), c_x.size(1));
        loop_ub = c_x.size(0) * c_x.size(1);
        for (i = 0; i < loop_ub; i++) {
            r[i].re = 0.0;
            r[i].im = 0.0;
        }
    } else {
        d_x.set_size(c_x.size(0), c_x.size(1));
        loop_ub = c_x.size(0) * c_x.size(1);
        for (i = 0; i < loop_ub; i++) {
            d_x[i].re = c_x[i];
            d_x[i].im = 0.0;
        }
        fftw_plan plan;
        int b_sign;
        b_sign = FFTW_BACKWARD;
        iodims.n = c_x.size(0);
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = d_x.size(1);
        howmany_iodims.is = d_x.size(0);
        howmany_iodims.os = c_x.size(0);
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        r.set_size(c_x.size(0), d_x.size(1));
        mylock();
        plan = fftw_plan_guru_dft(
            1, &iodims, 1, &howmany_iodims, (fftw_complex *)&d_x[0],
            (fftw_complex *)&r[0], b_sign,
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        loop_ub = r.size(0) * r.size(1);
        ncols = c_x.size(0);
        for (i = 0; i < loop_ub; i++) {
            temp_kprod = r[i].re;
            temp_J = r[i].im;
            if (temp_J == 0.0) {
                re = temp_kprod / static_cast<double>(ncols);
                temp_kprod = 0.0;
            } else if (temp_kprod == 0.0) {
                re = 0.0;
                temp_kprod = temp_J / static_cast<double>(ncols);
            } else {
                re = temp_kprod / static_cast<double>(ncols);
                temp_kprod = temp_J / static_cast<double>(ncols);
            }
            r[i].re = re;
            r[i].im = temp_kprod;
        }
    }
    b_r.set_size(r.size(0), r.size(1));
    loop_ub = r.size(0) * r.size(1);
    for (i = 0; i < loop_ub; i++) {
        b_r[i] = r[i].re;
    }
    ncols = b_r.size(1) - 1;
    loop_ub = x.size(0);
    for (i = 0; i <= ncols; i++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
            b_r[i1 + loop_ub * i] = b_r[i1 + b_r.size(0) * i];
        }
    }
    b_r.set_size(x.size(0), ncols + 1);
    input_sizes_idx_0 = 12;
    if (ncols + 1 == 1) {
        b_r.set_size(x.size(0), 1);
        for (i = 0; i < 1; i++) {
            for (i1 = 0; i1 < loop_ub; i1++) {
                b_r[i1] = b_r[i1];
            }
        }
    }
    if ((12 == b_r.size(0)) || (12 > b_r.size(0))) {
        input_sizes_idx_0 = b_r.size(0) - 1;
    }
    if (input_sizes_idx_0 == 0) {
        loop_ub = b_r.size(1);
        e.set_size(b_r.size(1));
        for (i = 0; i < loop_ub; i++) {
            e[i] = b_r[b_r.size(0) * i];
        }
        b_y.set_size(e.size(0), 1);
        loop_ub = e.size(0);
        for (i = 0; i < loop_ub; i++) {
            b_y[i] = 1.0;
        }
    } else if ((b_r.size(0) == 1) && (b_r.size(1) == 1)) {
        b_y.set_size(1, 1);
        b_y[0] = 1.0;
        e.set_size(1);
        e[0] = b_r[0];
    } else {
        signed char b_input_sizes_idx_0;
        signed char b_sizes_idx_0;
        temp_E.set_size(1, b_r.size(1));
        temp_A.set_size(input_sizes_idx_0, b_r.size(1));
        if (0 <= input_sizes_idx_0 - 1) {
            memset(&temp_a_data[0], 0, input_sizes_idx_0 * sizeof(double));
            memset(&temp_auf_data[0], 0, input_sizes_idx_0 * sizeof(double));
        }
        i = b_r.size(1);
        if (0 <= b_r.size(1) - 1) {
            if (2 > input_sizes_idx_0 + 1) {
                i4 = -1;
            } else {
                i4 = 0;
            }
            i5 = input_sizes_idx_0;
        }
        for (b_i = 0; b_i < i; b_i++) {
            temp_J = b_r[b_r.size(0) * b_i];
            temp_a_data[0] = -temp_J;
            for (sizes_idx_0 = 0; sizes_idx_0 < i5; sizes_idx_0++) {
                temp_kprod = 0.0;
                for (ncols = 0; ncols < sizes_idx_0; ncols++) {
                    re = temp_a_data[ncols];
                    temp_auf_data[ncols] = re;
                    temp_kprod +=
                        re *
                        b_r[((i4 + sizes_idx_0) - ncols) + b_r.size(0) * b_i];
                }
                temp_kprod =
                    -(b_r[((i4 + sizes_idx_0) + b_r.size(0) * b_i) + 1] +
                      temp_kprod) /
                    temp_J;
                temp_J *= 1.0 - temp_kprod * temp_kprod;
                for (ncols = 0; ncols < sizes_idx_0; ncols++) {
                    temp_a_data[ncols] =
                        temp_auf_data[ncols] +
                        temp_kprod * temp_auf_data[(sizes_idx_0 - ncols) - 1];
                }
                temp_a_data[sizes_idx_0] = temp_kprod;
            }
            temp_E[b_i] = temp_J;
            loop_ub = temp_A.size(0);
            for (i1 = 0; i1 < loop_ub; i1++) {
                temp_A[i1 + temp_A.size(0) * b_i] = temp_a_data[i1];
            }
        }
        if (1 > temp_A.size(0)) {
            loop_ub = 0;
        } else {
            loop_ub = temp_A.size(0);
        }
        if (b_r.size(1) != 0) {
            result = b_r.size(1);
        } else if ((loop_ub != 0) && (temp_A.size(1) != 0)) {
            result = temp_A.size(1);
        } else {
            result = 0;
            if (temp_A.size(1) > 0) {
                result = temp_A.size(1);
            }
        }
        empty_non_axis_sizes = (result == 0);
        if (empty_non_axis_sizes || (b_r.size(1) != 0)) {
            b_input_sizes_idx_0 = 1;
        } else {
            b_input_sizes_idx_0 = 0;
        }
        if (empty_non_axis_sizes || ((loop_ub != 0) && (temp_A.size(1) != 0))) {
            b_sizes_idx_0 = static_cast<signed char>(loop_ub);
        } else {
            b_sizes_idx_0 = 0;
        }
        ncols = temp_A.size(1) - 1;
        for (i = 0; i <= ncols; i++) {
            for (i1 = 0; i1 < loop_ub; i1++) {
                temp_A[i1 + loop_ub * i] = temp_A[i1 + temp_A.size(0) * i];
            }
        }
        temp_A.set_size(loop_ub, ncols + 1);
        ncols = b_sizes_idx_0;
        b_y.set_size(result, b_input_sizes_idx_0 + b_sizes_idx_0);
        loop_ub = b_input_sizes_idx_0;
        for (i = 0; i < loop_ub; i++) {
            for (i1 = 0; i1 < result; i1++) {
                b_y[i1] = 1.0;
            }
        }
        for (i = 0; i < ncols; i++) {
            for (i1 = 0; i1 < result; i1++) {
                b_y[i1 + b_y.size(0) * (i + b_input_sizes_idx_0)] =
                    temp_A[i + b_sizes_idx_0 * i1];
            }
        }
        e.set_size(temp_E.size(1));
        loop_ub = temp_E.size(1);
        for (i = 0; i < loop_ub; i++) {
            e[i] = temp_E[i];
        }
    }
    c_y.set_size(13, e.size(0));
    ncols = e.size(0);
    for (sizes_idx_0 = 0; sizes_idx_0 < ncols; sizes_idx_0++) {
        input_sizes_idx_0 = sizes_idx_0 * 13;
        for (b_i = 0; b_i < 13; b_i++) {
            c_y[input_sizes_idx_0 + b_i] = e[sizes_idx_0];
        }
    }
    y.set_size(b_y.size(1), b_y.size(0));
    loop_ub = b_y.size(0);
    for (i = 0; i < loop_ub; i++) {
        b_i = b_y.size(1);
        for (i1 = 0; i1 < b_i; i1++) {
            y[i1 + 13 * i] = b_y[i + b_y.size(0) * i1] / c_y[i1 + 13 * i];
        }
    }
}
