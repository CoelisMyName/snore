#include "pitch.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "getCandidates.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "fftw3.h"
#include "mylock.h"
#include <math.h>

namespace coder {
void b_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> b_x;
    array<creal_T, 2U> d_y;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> lag;
    array<double, 2U> xPadded;
    array<double, 2U> y;
    array<double, 1U> locs;
    array<double, 1U> peak;
    array<int, 2U> index_f2;
    array<int, 1U> b_r;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    double edge[2];
    int hop;
    int i;
    int itilerow;
    int loop_ub;
    int r;
    int yk;
    short sizes_idx_0;
    unsigned char input_sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    r = x.size(0);
    yk = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 551.0) / 275.0));
    y.set_size(551, yk + 1);
    loop_ub = 551 * (yk + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (hop = 0; hop <= yk; hop++) {
        unsigned int u0;
        unsigned int u1;
        i = 275 * hop;
        u0 = 275 * hop + 551U;
        u1 = static_cast<unsigned int>(r);
        if (u0 < u1) {
            u1 = u0;
        }
        if (static_cast<unsigned int>(i + 1) > u1) {
            i = 0;
            itilerow = 0;
        } else {
            itilerow = static_cast<int>(u1);
        }
        loop_ub = itilerow - i;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            y[itilerow + 551 * hop] = x[i + itilerow];
        }
    }
    edge[0] = 28.0;
    edge[1] = 221.0;
    if (y.size(1) == 0) {
        b_x.set_size(2048, 0);
    } else {
        r = MAX_int32_T;
        if (y.size(1) < MAX_int32_T) {
            r = y.size(1);
        }
        if (y.size(1) < r) {
            r = y.size(1);
        }
        xPadded.set_size(2048, y.size(1));
        loop_ub = y.size(1) << 11;
        for (i = 0; i < loop_ub; i++) {
            xPadded[i] = 0.0;
        }
        index_f2.set_size(1, r);
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        b_r.set_size(index_f2.size(1));
        loop_ub = index_f2.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_r[i] = index_f2[i];
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            itilerow = b_r[i];
            for (r = 0; r < 551; r++) {
                xPadded[r + 2048 * (itilerow - 1)] =
                    y[r + 551 * (itilerow - 1)];
            }
        }
        fftw_plan plan;
        iodims.n = 2048;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = xPadded.size(1);
        howmany_iodims.is = 2048;
        howmany_iodims.os = 2048;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        b_x.set_size(2048, xPadded.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&xPadded[0],
            (fftw_complex *)&b_x[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        r = xPadded.size(1);
        index_f2.set_size(1, xPadded.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        r = 1026;
        loop_ub = index_f2.size(1);
        do {
            b_r.set_size(index_f2.size(1));
            d_y.set_size(1, index_f2.size(1));
            for (i = 0; i < loop_ub; i++) {
                itilerow = index_f2[i];
                b_r[i] = itilerow - 1;
                d_y[i].re = b_x[(2048 * (itilerow - 1) - r) + 2049].re;
                d_y[i].im = -b_x[(2048 * (itilerow - 1) - r) + 2049].im;
            }
            yk = d_y.size(1);
            for (i = 0; i < yk; i++) {
                b_x[(r + 2048 * b_r[i]) - 1] = d_y[i];
            }
            r++;
        } while (!(r == 2049));
    }
    r = b_x.size(1) << 11;
    c1.set_size(2048, b_x.size(1));
    for (hop = 0; hop < r; hop++) {
        c1[hop] = rt_hypotd_snf(b_x[hop].re, b_x[hop].im);
    }
    b_y.set_size(2048, c1.size(1));
    r = c1.size(1) << 11;
    for (hop = 0; hop < r; hop++) {
        b_y[hop] = c1[hop] * c1[hop];
    }
    ifft(b_y, b_x);
    c1.set_size(2048, b_x.size(1));
    loop_ub = 2048 * b_x.size(1);
    for (i = 0; i < loop_ub; i++) {
        c1[i] = b_x[i].re / 45.254833995939045;
    }
    c_y.set_size(1, 221);
    for (i = 0; i < 221; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    loop_ub = c1.size(1);
    lag.set_size(221, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 221; itilerow++) {
            lag[itilerow + lag.size(0) * i] =
                c1[(static_cast<int>(c_y[itilerow] + 1827.0) + 2048 * i) - 1];
        }
    }
    if (c1.size(1) != 0) {
        yk = c1.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 221U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 222;
    } else {
        sizes_idx_0 = 0;
    }
    r = input_sizes_idx_0;
    loop_ub = c1.size(1);
    b_c1.set_size(222, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 222; itilerow++) {
            b_c1[itilerow + b_c1.size(0) * i] = c1[itilerow + 2048 * i];
        }
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < r; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] =
                lag[itilerow + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[itilerow + sizes_idx_0 * i];
        }
    }
    if (250 > Rt.size(0)) {
        i = -1;
        itilerow = -1;
    } else {
        i = 248;
        itilerow = Rt.size(0) - 1;
    }
    loop_ub = Rt.size(1);
    c_y.set_size(1, Rt.size(1));
    for (r = 0; r < loop_ub; r++) {
        c_y[r] = Rt[Rt.size(0) * r + 221];
    }
    r = Rt.size(1) - 1;
    for (hop = 0; hop <= r; hop++) {
        c_y[hop] = sqrt(c_y[hop]);
    }
    loop_ub = itilerow - i;
    lag.set_size(loop_ub, c_y.size(1));
    yk = c_y.size(1);
    for (hop = 0; hop < yk; hop++) {
        r = hop * loop_ub;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            lag[r + itilerow] = c_y[hop];
        }
    }
    yk = Rt.size(1);
    lag.set_size(loop_ub, Rt.size(1));
    for (itilerow = 0; itilerow < yk; itilerow++) {
        for (r = 0; r < loop_ub; r++) {
            lag[r + lag.size(0) * itilerow] =
                Rt[((i + r) + Rt.size(0) * itilerow) + 1] /
                lag[r + lag.size(0) * itilerow];
        }
    }
    if (lag.size(1) != 0) {
        yk = lag.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (lag.size(1) != 0)) {
        input_sizes_idx_0 = 27U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
        sizes_idx_0 = static_cast<short>(lag.size(0));
    } else {
        sizes_idx_0 = 0;
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        loop_ub = input_sizes_idx_0;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                lag[itilerow + sizes_idx_0 * i];
        }
    }
    audio::internal::pitch::getCandidates(Rt, edge, peak, locs);
    loop_ub = locs.size(0);
    for (i = 0; i < loop_ub; i++) {
        locs[i] = 11025.0 / locs[i];
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] < 50.0) {
            locs[yk] = 50.0;
        }
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] > 400.0) {
            locs[yk] = 400.0;
        }
    }
    locs.set_size(static_cast<int>(
                      ceil((static_cast<double>(x.size(0)) - 551.0) / 275.0)) +
                  1);
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 551.0) / 275.0));
    if (1 > r + 1) {
        loop_ub = -1;
    } else {
        loop_ub = r;
    }
    f0.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
        f0[i] = locs[i];
    }
}

void c_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> b_x;
    array<creal_T, 2U> d_y;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> lag;
    array<double, 2U> xPadded;
    array<double, 2U> y;
    array<double, 1U> locs;
    array<double, 1U> peak;
    array<int, 2U> index_f2;
    array<int, 1U> b_r;
    array<int, 1U> r1;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    double edge[2];
    int hop;
    int i;
    int itilerow;
    int loop_ub;
    int r;
    int yk;
    short sizes_idx_0;
    unsigned char input_sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    r = x.size(0);
    yk = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 600.0) / 300.0));
    y.set_size(600, yk + 1);
    loop_ub = 600 * (yk + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (hop = 0; hop <= yk; hop++) {
        unsigned int u0;
        unsigned int u1;
        i = 300 * hop;
        u0 = 300 * hop + 600U;
        u1 = static_cast<unsigned int>(r);
        if (u0 < u1) {
            u1 = u0;
        }
        if (static_cast<unsigned int>(i + 1) > u1) {
            i = 0;
            itilerow = 0;
        } else {
            itilerow = static_cast<int>(u1);
        }
        loop_ub = itilerow - i;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            y[itilerow + 600 * hop] = x[i + itilerow];
        }
    }
    edge[0] = 30.0;
    edge[1] = 240.0;
    if (y.size(1) == 0) {
        b_x.set_size(2048, 0);
    } else {
        r = MAX_int32_T;
        if (y.size(1) < MAX_int32_T) {
            r = y.size(1);
        }
        if (y.size(1) < r) {
            r = y.size(1);
        }
        xPadded.set_size(2048, y.size(1));
        loop_ub = y.size(1) << 11;
        for (i = 0; i < loop_ub; i++) {
            xPadded[i] = 0.0;
        }
        index_f2.set_size(1, r);
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        b_r.set_size(index_f2.size(1));
        loop_ub = index_f2.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_r[i] = index_f2[i];
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            itilerow = b_r[i];
            for (r = 0; r < 600; r++) {
                xPadded[r + 2048 * (itilerow - 1)] =
                    y[r + 600 * (itilerow - 1)];
            }
        }
        fftw_plan plan;
        iodims.n = 2048;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = xPadded.size(1);
        howmany_iodims.is = 2048;
        howmany_iodims.os = 2048;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        b_x.set_size(2048, xPadded.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&xPadded[0],
            (fftw_complex *)&b_x[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        r = xPadded.size(1);
        index_f2.set_size(1, xPadded.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        r = 1026;
        loop_ub = index_f2.size(1);
        do {
            r1.set_size(index_f2.size(1));
            d_y.set_size(1, index_f2.size(1));
            for (i = 0; i < loop_ub; i++) {
                itilerow = index_f2[i];
                r1[i] = itilerow - 1;
                d_y[i].re = b_x[(2048 * (itilerow - 1) - r) + 2049].re;
                d_y[i].im = -b_x[(2048 * (itilerow - 1) - r) + 2049].im;
            }
            yk = d_y.size(1);
            for (i = 0; i < yk; i++) {
                b_x[(r + 2048 * r1[i]) - 1] = d_y[i];
            }
            r++;
        } while (!(r == 2049));
    }
    r = b_x.size(1) << 11;
    c1.set_size(2048, b_x.size(1));
    for (hop = 0; hop < r; hop++) {
        c1[hop] = rt_hypotd_snf(b_x[hop].re, b_x[hop].im);
    }
    b_y.set_size(2048, c1.size(1));
    r = c1.size(1) << 11;
    for (hop = 0; hop < r; hop++) {
        b_y[hop] = c1[hop] * c1[hop];
    }
    ifft(b_y, b_x);
    c1.set_size(2048, b_x.size(1));
    loop_ub = 2048 * b_x.size(1);
    for (i = 0; i < loop_ub; i++) {
        c1[i] = b_x[i].re / 45.254833995939045;
    }
    c_y.set_size(1, 240);
    for (i = 0; i < 240; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    loop_ub = c1.size(1);
    lag.set_size(240, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 240; itilerow++) {
            lag[itilerow + lag.size(0) * i] =
                c1[(static_cast<int>(c_y[itilerow]) + 2048 * i) + 1807];
        }
    }
    if (c1.size(1) != 0) {
        yk = c1.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 240U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 241;
    } else {
        sizes_idx_0 = 0;
    }
    r = input_sizes_idx_0;
    loop_ub = c1.size(1);
    b_c1.set_size(241, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 241; itilerow++) {
            b_c1[itilerow + b_c1.size(0) * i] = c1[itilerow + 2048 * i];
        }
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < r; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] =
                lag[itilerow + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[itilerow + sizes_idx_0 * i];
        }
    }
    if (271 > Rt.size(0)) {
        i = -1;
        itilerow = -1;
    } else {
        i = 269;
        itilerow = Rt.size(0) - 1;
    }
    loop_ub = Rt.size(1);
    c_y.set_size(1, Rt.size(1));
    for (r = 0; r < loop_ub; r++) {
        c_y[r] = Rt[Rt.size(0) * r + 240];
    }
    r = Rt.size(1) - 1;
    for (hop = 0; hop <= r; hop++) {
        c_y[hop] = sqrt(c_y[hop]);
    }
    loop_ub = itilerow - i;
    lag.set_size(loop_ub, c_y.size(1));
    yk = c_y.size(1);
    for (hop = 0; hop < yk; hop++) {
        r = hop * loop_ub;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            lag[r + itilerow] = c_y[hop];
        }
    }
    yk = Rt.size(1);
    lag.set_size(loop_ub, Rt.size(1));
    for (itilerow = 0; itilerow < yk; itilerow++) {
        for (r = 0; r < loop_ub; r++) {
            lag[r + lag.size(0) * itilerow] =
                Rt[((i + r) + Rt.size(0) * itilerow) + 1] /
                lag[r + lag.size(0) * itilerow];
        }
    }
    if (lag.size(1) != 0) {
        yk = lag.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (lag.size(1) != 0)) {
        input_sizes_idx_0 = 29U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
        sizes_idx_0 = static_cast<short>(lag.size(0));
    } else {
        sizes_idx_0 = 0;
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        loop_ub = input_sizes_idx_0;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                lag[itilerow + sizes_idx_0 * i];
        }
    }
    audio::internal::pitch::getCandidates(Rt, edge, peak, locs);
    loop_ub = locs.size(0);
    for (i = 0; i < loop_ub; i++) {
        locs[i] = 12000.0 / locs[i];
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] < 50.0) {
            locs[yk] = 50.0;
        }
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] > 400.0) {
            locs[yk] = 400.0;
        }
    }
    locs.set_size(static_cast<int>(
                      ceil((static_cast<double>(x.size(0)) - 600.0) / 300.0)) +
                  1);
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 600.0) / 300.0));
    if (1 > r + 1) {
        loop_ub = -1;
    } else {
        loop_ub = r;
    }
    f0.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
        f0[i] = locs[i];
    }
}

void d_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> b_x;
    array<creal_T, 2U> d_y;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> lag;
    array<double, 2U> xPadded;
    array<double, 2U> y;
    array<double, 1U> locs;
    array<double, 1U> peak;
    array<int, 2U> index_f2;
    array<int, 1U> b_r;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    double edge[2];
    int hop;
    int i;
    int itilerow;
    int loop_ub;
    int r;
    int yk;
    short input_sizes_idx_0;
    short sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    r = x.size(0);
    yk = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 1103.0) / 552.0));
    y.set_size(1103, yk + 1);
    loop_ub = 1103 * (yk + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (hop = 0; hop <= yk; hop++) {
        unsigned int u0;
        unsigned int u1;
        i = 552 * hop;
        u0 = 552 * hop + 1103U;
        u1 = static_cast<unsigned int>(r);
        if (u0 < u1) {
            u1 = u0;
        }
        if (static_cast<unsigned int>(i + 1) > u1) {
            i = 0;
            itilerow = 0;
        } else {
            itilerow = static_cast<int>(u1);
        }
        loop_ub = itilerow - i;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            y[itilerow + 1103 * hop] = x[i + itilerow];
        }
    }
    edge[0] = 55.0;
    edge[1] = 441.0;
    if (y.size(1) == 0) {
        b_x.set_size(4096, 0);
    } else {
        r = MAX_int32_T;
        if (y.size(1) < MAX_int32_T) {
            r = y.size(1);
        }
        if (y.size(1) < r) {
            r = y.size(1);
        }
        xPadded.set_size(4096, y.size(1));
        loop_ub = y.size(1) << 12;
        for (i = 0; i < loop_ub; i++) {
            xPadded[i] = 0.0;
        }
        index_f2.set_size(1, r);
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        b_r.set_size(index_f2.size(1));
        loop_ub = index_f2.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_r[i] = index_f2[i];
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            itilerow = b_r[i];
            for (r = 0; r < 1103; r++) {
                xPadded[r + 4096 * (itilerow - 1)] =
                    y[r + 1103 * (itilerow - 1)];
            }
        }
        fftw_plan plan;
        iodims.n = 4096;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = xPadded.size(1);
        howmany_iodims.is = 4096;
        howmany_iodims.os = 4096;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        b_x.set_size(4096, xPadded.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&xPadded[0],
            (fftw_complex *)&b_x[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        r = xPadded.size(1);
        index_f2.set_size(1, xPadded.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        r = 2050;
        loop_ub = index_f2.size(1);
        do {
            b_r.set_size(index_f2.size(1));
            d_y.set_size(1, index_f2.size(1));
            for (i = 0; i < loop_ub; i++) {
                itilerow = index_f2[i];
                b_r[i] = itilerow - 1;
                d_y[i].re = b_x[(4096 * (itilerow - 1) - r) + 4097].re;
                d_y[i].im = -b_x[(4096 * (itilerow - 1) - r) + 4097].im;
            }
            yk = d_y.size(1);
            for (i = 0; i < yk; i++) {
                b_x[(r + 4096 * b_r[i]) - 1] = d_y[i];
            }
            r++;
        } while (!(r == 4097));
    }
    r = b_x.size(1) << 12;
    c1.set_size(4096, b_x.size(1));
    for (hop = 0; hop < r; hop++) {
        c1[hop] = rt_hypotd_snf(b_x[hop].re, b_x[hop].im);
    }
    b_y.set_size(4096, c1.size(1));
    r = c1.size(1) << 12;
    for (hop = 0; hop < r; hop++) {
        b_y[hop] = c1[hop] * c1[hop];
    }
    b_ifft(b_y, b_x);
    c1.set_size(4096, b_x.size(1));
    loop_ub = 4096 * b_x.size(1);
    for (i = 0; i < loop_ub; i++) {
        c1[i] = b_x[i].re / 64.0;
    }
    c_y.set_size(1, 441);
    for (i = 0; i < 441; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    loop_ub = c1.size(1);
    lag.set_size(441, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 441; itilerow++) {
            lag[itilerow + lag.size(0) * i] =
                c1[(static_cast<int>(c_y[itilerow]) + 4096 * i) + 3654];
        }
    }
    if (c1.size(1) != 0) {
        yk = c1.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 441;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 442;
    } else {
        sizes_idx_0 = 0;
    }
    r = input_sizes_idx_0;
    loop_ub = c1.size(1);
    b_c1.set_size(442, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 442; itilerow++) {
            b_c1[itilerow + b_c1.size(0) * i] = c1[itilerow + 4096 * i];
        }
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < r; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] =
                lag[itilerow + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[itilerow + sizes_idx_0 * i];
        }
    }
    if (497 > Rt.size(0)) {
        i = -1;
        itilerow = -1;
    } else {
        i = 495;
        itilerow = Rt.size(0) - 1;
    }
    loop_ub = Rt.size(1);
    c_y.set_size(1, Rt.size(1));
    for (r = 0; r < loop_ub; r++) {
        c_y[r] = Rt[Rt.size(0) * r + 441];
    }
    r = Rt.size(1) - 1;
    for (hop = 0; hop <= r; hop++) {
        c_y[hop] = sqrt(c_y[hop]);
    }
    loop_ub = itilerow - i;
    lag.set_size(loop_ub, c_y.size(1));
    yk = c_y.size(1);
    for (hop = 0; hop < yk; hop++) {
        r = hop * loop_ub;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            lag[r + itilerow] = c_y[hop];
        }
    }
    yk = Rt.size(1);
    lag.set_size(loop_ub, Rt.size(1));
    for (itilerow = 0; itilerow < yk; itilerow++) {
        for (r = 0; r < loop_ub; r++) {
            lag[r + lag.size(0) * itilerow] =
                Rt[((i + r) + Rt.size(0) * itilerow) + 1] /
                lag[r + lag.size(0) * itilerow];
        }
    }
    if (lag.size(1) != 0) {
        yk = lag.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (lag.size(1) != 0)) {
        input_sizes_idx_0 = 54;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
        sizes_idx_0 = static_cast<short>(lag.size(0));
    } else {
        sizes_idx_0 = 0;
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        loop_ub = input_sizes_idx_0;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                lag[itilerow + sizes_idx_0 * i];
        }
    }
    audio::internal::pitch::getCandidates(Rt, edge, peak, locs);
    loop_ub = locs.size(0);
    for (i = 0; i < loop_ub; i++) {
        locs[i] = 22050.0 / locs[i];
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] < 50.0) {
            locs[yk] = 50.0;
        }
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] > 400.0) {
            locs[yk] = 400.0;
        }
    }
    locs.set_size(static_cast<int>(
                      ceil((static_cast<double>(x.size(0)) - 1103.0) / 552.0)) +
                  1);
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 1103.0) / 552.0));
    if (1 > r + 1) {
        loop_ub = -1;
    } else {
        loop_ub = r;
    }
    f0.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
        f0[i] = locs[i];
    }
}

void e_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> b_x;
    array<creal_T, 2U> d_y;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> lag;
    array<double, 2U> xPadded;
    array<double, 2U> y;
    array<double, 1U> locs;
    array<double, 1U> peak;
    array<int, 2U> index_f2;
    array<int, 1U> b_r;
    array<int, 1U> r1;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    double edge[2];
    int hop;
    int i;
    int itilerow;
    int loop_ub;
    int r;
    int yk;
    short input_sizes_idx_0;
    short sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    r = x.size(0);
    yk = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 1200.0) / 600.0));
    y.set_size(1200, yk + 1);
    loop_ub = 1200 * (yk + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (hop = 0; hop <= yk; hop++) {
        unsigned int u0;
        unsigned int u1;
        i = 600 * hop;
        u0 = 600 * hop + 1200U;
        u1 = static_cast<unsigned int>(r);
        if (u0 < u1) {
            u1 = u0;
        }
        if (static_cast<unsigned int>(i + 1) > u1) {
            i = 0;
            itilerow = 0;
        } else {
            itilerow = static_cast<int>(u1);
        }
        loop_ub = itilerow - i;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            y[itilerow + 1200 * hop] = x[i + itilerow];
        }
    }
    edge[0] = 60.0;
    edge[1] = 480.0;
    if (y.size(1) == 0) {
        b_x.set_size(4096, 0);
    } else {
        r = MAX_int32_T;
        if (y.size(1) < MAX_int32_T) {
            r = y.size(1);
        }
        if (y.size(1) < r) {
            r = y.size(1);
        }
        xPadded.set_size(4096, y.size(1));
        loop_ub = y.size(1) << 12;
        for (i = 0; i < loop_ub; i++) {
            xPadded[i] = 0.0;
        }
        index_f2.set_size(1, r);
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        b_r.set_size(index_f2.size(1));
        loop_ub = index_f2.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_r[i] = index_f2[i];
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            itilerow = b_r[i];
            for (r = 0; r < 1200; r++) {
                xPadded[r + 4096 * (itilerow - 1)] =
                    y[r + 1200 * (itilerow - 1)];
            }
        }
        fftw_plan plan;
        iodims.n = 4096;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = xPadded.size(1);
        howmany_iodims.is = 4096;
        howmany_iodims.os = 4096;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        b_x.set_size(4096, xPadded.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&xPadded[0],
            (fftw_complex *)&b_x[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        r = xPadded.size(1);
        index_f2.set_size(1, xPadded.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        r = 2050;
        loop_ub = index_f2.size(1);
        do {
            r1.set_size(index_f2.size(1));
            d_y.set_size(1, index_f2.size(1));
            for (i = 0; i < loop_ub; i++) {
                itilerow = index_f2[i];
                r1[i] = itilerow - 1;
                d_y[i].re = b_x[(4096 * (itilerow - 1) - r) + 4097].re;
                d_y[i].im = -b_x[(4096 * (itilerow - 1) - r) + 4097].im;
            }
            yk = d_y.size(1);
            for (i = 0; i < yk; i++) {
                b_x[(r + 4096 * r1[i]) - 1] = d_y[i];
            }
            r++;
        } while (!(r == 4097));
    }
    r = b_x.size(1) << 12;
    c1.set_size(4096, b_x.size(1));
    for (hop = 0; hop < r; hop++) {
        c1[hop] = rt_hypotd_snf(b_x[hop].re, b_x[hop].im);
    }
    b_y.set_size(4096, c1.size(1));
    r = c1.size(1) << 12;
    for (hop = 0; hop < r; hop++) {
        b_y[hop] = c1[hop] * c1[hop];
    }
    b_ifft(b_y, b_x);
    c1.set_size(4096, b_x.size(1));
    loop_ub = 4096 * b_x.size(1);
    for (i = 0; i < loop_ub; i++) {
        c1[i] = b_x[i].re / 64.0;
    }
    c_y.set_size(1, 480);
    for (i = 0; i < 480; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    loop_ub = c1.size(1);
    lag.set_size(480, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 480; itilerow++) {
            lag[itilerow + lag.size(0) * i] =
                c1[(static_cast<int>(c_y[itilerow]) + 4096 * i) + 3615];
        }
    }
    if (c1.size(1) != 0) {
        yk = c1.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 480;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 481;
    } else {
        sizes_idx_0 = 0;
    }
    r = input_sizes_idx_0;
    loop_ub = c1.size(1);
    b_c1.set_size(481, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 481; itilerow++) {
            b_c1[itilerow + b_c1.size(0) * i] = c1[itilerow + 4096 * i];
        }
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < r; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] =
                lag[itilerow + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[itilerow + sizes_idx_0 * i];
        }
    }
    if (541 > Rt.size(0)) {
        i = -1;
        itilerow = -1;
    } else {
        i = 539;
        itilerow = Rt.size(0) - 1;
    }
    loop_ub = Rt.size(1);
    c_y.set_size(1, Rt.size(1));
    for (r = 0; r < loop_ub; r++) {
        c_y[r] = Rt[Rt.size(0) * r + 480];
    }
    r = Rt.size(1) - 1;
    for (hop = 0; hop <= r; hop++) {
        c_y[hop] = sqrt(c_y[hop]);
    }
    loop_ub = itilerow - i;
    lag.set_size(loop_ub, c_y.size(1));
    yk = c_y.size(1);
    for (hop = 0; hop < yk; hop++) {
        r = hop * loop_ub;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            lag[r + itilerow] = c_y[hop];
        }
    }
    yk = Rt.size(1);
    lag.set_size(loop_ub, Rt.size(1));
    for (itilerow = 0; itilerow < yk; itilerow++) {
        for (r = 0; r < loop_ub; r++) {
            lag[r + lag.size(0) * itilerow] =
                Rt[((i + r) + Rt.size(0) * itilerow) + 1] /
                lag[r + lag.size(0) * itilerow];
        }
    }
    if (lag.size(1) != 0) {
        yk = lag.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (lag.size(1) != 0)) {
        input_sizes_idx_0 = 59;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
        sizes_idx_0 = static_cast<short>(lag.size(0));
    } else {
        sizes_idx_0 = 0;
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        loop_ub = input_sizes_idx_0;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                lag[itilerow + sizes_idx_0 * i];
        }
    }
    audio::internal::pitch::getCandidates(Rt, edge, peak, locs);
    loop_ub = locs.size(0);
    for (i = 0; i < loop_ub; i++) {
        locs[i] = 24000.0 / locs[i];
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] < 50.0) {
            locs[yk] = 50.0;
        }
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] > 400.0) {
            locs[yk] = 400.0;
        }
    }
    locs.set_size(static_cast<int>(
                      ceil((static_cast<double>(x.size(0)) - 1200.0) / 600.0)) +
                  1);
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 1200.0) / 600.0));
    if (1 > r + 1) {
        loop_ub = -1;
    } else {
        loop_ub = r;
    }
    f0.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
        f0[i] = locs[i];
    }
}

void f_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> b_x;
    array<creal_T, 2U> d_y;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> lag;
    array<double, 2U> xPadded;
    array<double, 2U> y;
    array<double, 1U> locs;
    array<double, 1U> peak;
    array<int, 2U> index_f2;
    array<int, 1U> b_r;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    double edge[2];
    int hop;
    int i;
    int itilerow;
    int loop_ub;
    int r;
    int yk;
    short input_sizes_idx_0;
    short sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    r = x.size(0);
    yk = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 2205.0) / 1102.0));
    y.set_size(2205, yk + 1);
    loop_ub = 2205 * (yk + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (hop = 0; hop <= yk; hop++) {
        unsigned int u0;
        unsigned int u1;
        i = 1102 * hop;
        u0 = 1102 * hop + 2205U;
        u1 = static_cast<unsigned int>(r);
        if (u0 < u1) {
            u1 = u0;
        }
        if (static_cast<unsigned int>(i + 1) > u1) {
            i = 0;
            itilerow = 0;
        } else {
            itilerow = static_cast<int>(u1);
        }
        loop_ub = itilerow - i;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            y[itilerow + 2205 * hop] = x[i + itilerow];
        }
    }
    edge[0] = 110.0;
    edge[1] = 882.0;
    if (y.size(1) == 0) {
        b_x.set_size(8192, 0);
    } else {
        r = MAX_int32_T;
        if (y.size(1) < MAX_int32_T) {
            r = y.size(1);
        }
        if (y.size(1) < r) {
            r = y.size(1);
        }
        xPadded.set_size(8192, y.size(1));
        loop_ub = y.size(1) << 13;
        for (i = 0; i < loop_ub; i++) {
            xPadded[i] = 0.0;
        }
        index_f2.set_size(1, r);
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        b_r.set_size(index_f2.size(1));
        loop_ub = index_f2.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_r[i] = index_f2[i];
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            itilerow = b_r[i];
            for (r = 0; r < 2205; r++) {
                xPadded[r + 8192 * (itilerow - 1)] =
                    y[r + 2205 * (itilerow - 1)];
            }
        }
        fftw_plan plan;
        iodims.n = 8192;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = xPadded.size(1);
        howmany_iodims.is = 8192;
        howmany_iodims.os = 8192;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        b_x.set_size(8192, xPadded.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&xPadded[0],
            (fftw_complex *)&b_x[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        r = xPadded.size(1);
        index_f2.set_size(1, xPadded.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        r = 4098;
        loop_ub = index_f2.size(1);
        do {
            b_r.set_size(index_f2.size(1));
            d_y.set_size(1, index_f2.size(1));
            for (i = 0; i < loop_ub; i++) {
                itilerow = index_f2[i];
                b_r[i] = itilerow - 1;
                d_y[i].re = b_x[(8192 * (itilerow - 1) - r) + 8193].re;
                d_y[i].im = -b_x[(8192 * (itilerow - 1) - r) + 8193].im;
            }
            yk = d_y.size(1);
            for (i = 0; i < yk; i++) {
                b_x[(r + 8192 * b_r[i]) - 1] = d_y[i];
            }
            r++;
        } while (!(r == 8193));
    }
    r = b_x.size(1) << 13;
    c1.set_size(8192, b_x.size(1));
    for (hop = 0; hop < r; hop++) {
        c1[hop] = rt_hypotd_snf(b_x[hop].re, b_x[hop].im);
    }
    b_y.set_size(8192, c1.size(1));
    r = c1.size(1) << 13;
    for (hop = 0; hop < r; hop++) {
        b_y[hop] = c1[hop] * c1[hop];
    }
    c_ifft(b_y, b_x);
    c1.set_size(8192, b_x.size(1));
    loop_ub = 8192 * b_x.size(1);
    for (i = 0; i < loop_ub; i++) {
        c1[i] = b_x[i].re / 90.509667991878089;
    }
    c_y.set_size(1, 882);
    for (i = 0; i < 882; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    loop_ub = c1.size(1);
    lag.set_size(882, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 882; itilerow++) {
            lag[itilerow + lag.size(0) * i] =
                c1[(static_cast<int>(c_y[itilerow]) + 8192 * i) + 7309];
        }
    }
    if (c1.size(1) != 0) {
        yk = c1.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 882;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 883;
    } else {
        sizes_idx_0 = 0;
    }
    r = input_sizes_idx_0;
    loop_ub = c1.size(1);
    b_c1.set_size(883, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 883; itilerow++) {
            b_c1[itilerow + b_c1.size(0) * i] = c1[itilerow + 8192 * i];
        }
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < r; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] =
                lag[itilerow + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[itilerow + sizes_idx_0 * i];
        }
    }
    if (993 > Rt.size(0)) {
        i = -1;
        itilerow = -1;
    } else {
        i = 991;
        itilerow = Rt.size(0) - 1;
    }
    loop_ub = Rt.size(1);
    c_y.set_size(1, Rt.size(1));
    for (r = 0; r < loop_ub; r++) {
        c_y[r] = Rt[Rt.size(0) * r + 882];
    }
    r = Rt.size(1) - 1;
    for (hop = 0; hop <= r; hop++) {
        c_y[hop] = sqrt(c_y[hop]);
    }
    loop_ub = itilerow - i;
    lag.set_size(loop_ub, c_y.size(1));
    yk = c_y.size(1);
    for (hop = 0; hop < yk; hop++) {
        r = hop * loop_ub;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            lag[r + itilerow] = c_y[hop];
        }
    }
    yk = Rt.size(1);
    lag.set_size(loop_ub, Rt.size(1));
    for (itilerow = 0; itilerow < yk; itilerow++) {
        for (r = 0; r < loop_ub; r++) {
            lag[r + lag.size(0) * itilerow] =
                Rt[((i + r) + Rt.size(0) * itilerow) + 1] /
                lag[r + lag.size(0) * itilerow];
        }
    }
    if (lag.size(1) != 0) {
        yk = lag.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (lag.size(1) != 0)) {
        input_sizes_idx_0 = 109;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
        sizes_idx_0 = static_cast<short>(lag.size(0));
    } else {
        sizes_idx_0 = 0;
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        loop_ub = input_sizes_idx_0;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                lag[itilerow + sizes_idx_0 * i];
        }
    }
    audio::internal::pitch::getCandidates(Rt, edge, peak, locs);
    loop_ub = locs.size(0);
    for (i = 0; i < loop_ub; i++) {
        locs[i] = 44100.0 / locs[i];
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] < 50.0) {
            locs[yk] = 50.0;
        }
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] > 400.0) {
            locs[yk] = 400.0;
        }
    }
    locs.set_size(static_cast<int>(ceil(
                      (static_cast<double>(x.size(0)) - 2205.0) / 1102.0)) +
                  1);
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 2205.0) / 1102.0));
    if (1 > r + 1) {
        loop_ub = -1;
    } else {
        loop_ub = r;
    }
    f0.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
        f0[i] = locs[i];
    }
}

void g_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<creal_T, 2U> b_x;
    array<creal_T, 2U> d_y;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> c_y;
    array<double, 2U> lag;
    array<double, 2U> xPadded;
    array<double, 2U> y;
    array<double, 1U> locs;
    array<double, 1U> peak;
    array<int, 2U> index_f2;
    array<int, 1U> b_r;
    array<int, 1U> r1;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    double edge[2];
    int hop;
    int i;
    int itilerow;
    int loop_ub;
    int r;
    int yk;
    short input_sizes_idx_0;
    short sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    r = x.size(0);
    yk = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 2400.0) / 1200.0));
    y.set_size(2400, yk + 1);
    loop_ub = 2400 * (yk + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (hop = 0; hop <= yk; hop++) {
        unsigned int u0;
        unsigned int u1;
        i = 1200 * hop;
        u0 = 1200 * hop + 2400U;
        u1 = static_cast<unsigned int>(r);
        if (u0 < u1) {
            u1 = u0;
        }
        if (static_cast<unsigned int>(i + 1) > u1) {
            i = 0;
            itilerow = 0;
        } else {
            itilerow = static_cast<int>(u1);
        }
        loop_ub = itilerow - i;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            y[itilerow + 2400 * hop] = x[i + itilerow];
        }
    }
    edge[0] = 120.0;
    edge[1] = 960.0;
    if (y.size(1) == 0) {
        b_x.set_size(8192, 0);
    } else {
        r = MAX_int32_T;
        if (y.size(1) < MAX_int32_T) {
            r = y.size(1);
        }
        if (y.size(1) < r) {
            r = y.size(1);
        }
        xPadded.set_size(8192, y.size(1));
        loop_ub = y.size(1) << 13;
        for (i = 0; i < loop_ub; i++) {
            xPadded[i] = 0.0;
        }
        index_f2.set_size(1, r);
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        b_r.set_size(index_f2.size(1));
        loop_ub = index_f2.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_r[i] = index_f2[i];
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            itilerow = b_r[i];
            for (r = 0; r < 2400; r++) {
                xPadded[r + 8192 * (itilerow - 1)] =
                    y[r + 2400 * (itilerow - 1)];
            }
        }
        fftw_plan plan;
        iodims.n = 8192;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = xPadded.size(1);
        howmany_iodims.is = 8192;
        howmany_iodims.os = 8192;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        b_x.set_size(8192, xPadded.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &iodims, 1, &howmany_iodims, (double *)&xPadded[0],
            (fftw_complex *)&b_x[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        r = xPadded.size(1);
        index_f2.set_size(1, xPadded.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        r = 4098;
        loop_ub = index_f2.size(1);
        do {
            r1.set_size(index_f2.size(1));
            d_y.set_size(1, index_f2.size(1));
            for (i = 0; i < loop_ub; i++) {
                itilerow = index_f2[i];
                r1[i] = itilerow - 1;
                d_y[i].re = b_x[(8192 * (itilerow - 1) - r) + 8193].re;
                d_y[i].im = -b_x[(8192 * (itilerow - 1) - r) + 8193].im;
            }
            yk = d_y.size(1);
            for (i = 0; i < yk; i++) {
                b_x[(r + 8192 * r1[i]) - 1] = d_y[i];
            }
            r++;
        } while (!(r == 8193));
    }
    r = b_x.size(1) << 13;
    c1.set_size(8192, b_x.size(1));
    for (hop = 0; hop < r; hop++) {
        c1[hop] = rt_hypotd_snf(b_x[hop].re, b_x[hop].im);
    }
    b_y.set_size(8192, c1.size(1));
    r = c1.size(1) << 13;
    for (hop = 0; hop < r; hop++) {
        b_y[hop] = c1[hop] * c1[hop];
    }
    c_ifft(b_y, b_x);
    c1.set_size(8192, b_x.size(1));
    loop_ub = 8192 * b_x.size(1);
    for (i = 0; i < loop_ub; i++) {
        c1[i] = b_x[i].re / 90.509667991878089;
    }
    c_y.set_size(1, 960);
    for (i = 0; i < 960; i++) {
        c_y[i] = static_cast<double>(i) + 1.0;
    }
    loop_ub = c1.size(1);
    lag.set_size(960, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 960; itilerow++) {
            lag[itilerow + lag.size(0) * i] =
                c1[(static_cast<int>(c_y[itilerow]) + 8192 * i) + 7231];
        }
    }
    if (c1.size(1) != 0) {
        yk = c1.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 960;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        sizes_idx_0 = 961;
    } else {
        sizes_idx_0 = 0;
    }
    r = input_sizes_idx_0;
    loop_ub = c1.size(1);
    b_c1.set_size(961, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 961; itilerow++) {
            b_c1[itilerow + b_c1.size(0) * i] = c1[itilerow + 8192 * i];
        }
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < r; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] =
                lag[itilerow + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[itilerow + sizes_idx_0 * i];
        }
    }
    if (1081 > Rt.size(0)) {
        i = -1;
        itilerow = -1;
    } else {
        i = 1079;
        itilerow = Rt.size(0) - 1;
    }
    loop_ub = Rt.size(1);
    c_y.set_size(1, Rt.size(1));
    for (r = 0; r < loop_ub; r++) {
        c_y[r] = Rt[Rt.size(0) * r + 960];
    }
    r = Rt.size(1) - 1;
    for (hop = 0; hop <= r; hop++) {
        c_y[hop] = sqrt(c_y[hop]);
    }
    loop_ub = itilerow - i;
    lag.set_size(loop_ub, c_y.size(1));
    yk = c_y.size(1);
    for (hop = 0; hop < yk; hop++) {
        r = hop * loop_ub;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            lag[r + itilerow] = c_y[hop];
        }
    }
    yk = Rt.size(1);
    lag.set_size(loop_ub, Rt.size(1));
    for (itilerow = 0; itilerow < yk; itilerow++) {
        for (r = 0; r < loop_ub; r++) {
            lag[r + lag.size(0) * itilerow] =
                Rt[((i + r) + Rt.size(0) * itilerow) + 1] /
                lag[r + lag.size(0) * itilerow];
        }
    }
    if (lag.size(1) != 0) {
        yk = lag.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (lag.size(1) != 0)) {
        input_sizes_idx_0 = 119;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
        sizes_idx_0 = static_cast<short>(lag.size(0));
    } else {
        sizes_idx_0 = 0;
    }
    hop = sizes_idx_0;
    Rt.set_size(input_sizes_idx_0 + sizes_idx_0, yk);
    for (i = 0; i < yk; i++) {
        loop_ub = input_sizes_idx_0;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                lag[itilerow + sizes_idx_0 * i];
        }
    }
    audio::internal::pitch::getCandidates(Rt, edge, peak, locs);
    loop_ub = locs.size(0);
    for (i = 0; i < loop_ub; i++) {
        locs[i] = 48000.0 / locs[i];
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] < 50.0) {
            locs[yk] = 50.0;
        }
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] > 400.0) {
            locs[yk] = 400.0;
        }
    }
    locs.set_size(static_cast<int>(ceil(
                      (static_cast<double>(x.size(0)) - 2400.0) / 1200.0)) +
                  1);
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 2400.0) / 1200.0));
    if (1 > r + 1) {
        loop_ub = -1;
    } else {
        loop_ub = r;
    }
    f0.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
        f0[i] = locs[i];
    }
}

void pitch(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &f0)
{
    fftw_plan plan;
    array<creal_T, 2U> b_x;
    array<creal_T, 2U> c_y;
    array<creal_T, 2U> e_y;
    array<double, 2U> Rt;
    array<double, 2U> b_c1;
    array<double, 2U> b_y;
    array<double, 2U> c1;
    array<double, 2U> d_y;
    array<double, 2U> lag;
    array<double, 2U> xPadded;
    array<double, 2U> y;
    array<double, 1U> locs;
    array<double, 1U> peak;
    array<int, 2U> index_f2;
    array<int, 1U> b_r;
    fftw_iodim b_howmany_iodims;
    fftw_iodim b_iodims;
    fftw_iodim howmany_iodims;
    fftw_iodim iodims;
    double edge[2];
    int hop;
    int i;
    int itilerow;
    int loop_ub;
    int r;
    int yk;
    unsigned char input_sizes_idx_0;
    boolean_T empty_non_axis_sizes;
    r = x.size(0);
    yk = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 400.0) / 200.0));
    y.set_size(400, yk + 1);
    loop_ub = 400 * (yk + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (hop = 0; hop <= yk; hop++) {
        unsigned int u0;
        unsigned int u1;
        i = 200 * hop;
        u0 = 200 * hop + 400U;
        u1 = static_cast<unsigned int>(r);
        if (u0 < u1) {
            u1 = u0;
        }
        if (static_cast<unsigned int>(i + 1) > u1) {
            i = 0;
            itilerow = 0;
        } else {
            itilerow = static_cast<int>(u1);
        }
        loop_ub = itilerow - i;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            y[itilerow + 400 * hop] = x[i + itilerow];
        }
    }
    edge[0] = 20.0;
    edge[1] = 160.0;
    if (y.size(1) == 0) {
        b_x.set_size(1024, 0);
    } else {
        r = MAX_int32_T;
        if (y.size(1) < MAX_int32_T) {
            r = y.size(1);
        }
        if (y.size(1) < r) {
            r = y.size(1);
        }
        xPadded.set_size(1024, y.size(1));
        loop_ub = y.size(1) << 10;
        for (i = 0; i < loop_ub; i++) {
            xPadded[i] = 0.0;
        }
        index_f2.set_size(1, r);
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        b_r.set_size(index_f2.size(1));
        loop_ub = index_f2.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_r[i] = index_f2[i];
        }
        loop_ub = b_r.size(0);
        for (i = 0; i < loop_ub; i++) {
            itilerow = b_r[i];
            for (r = 0; r < 400; r++) {
                xPadded[r + 1024 * (itilerow - 1)] =
                    y[r + 400 * (itilerow - 1)];
            }
        }
        b_iodims.n = 1024;
        b_iodims.is = 1;
        b_iodims.os = 1;
        b_howmany_iodims.n = xPadded.size(1);
        b_howmany_iodims.is = 1024;
        b_howmany_iodims.os = 1024;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        b_x.set_size(1024, xPadded.size(1));
        mylock();
        plan = fftw_plan_guru_dft_r2c(
            1, &b_iodims, 1, &b_howmany_iodims, (double *)&xPadded[0],
            (fftw_complex *)&b_x[0],
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        r = xPadded.size(1);
        index_f2.set_size(1, xPadded.size(1));
        index_f2[0] = 1;
        yk = 1;
        for (hop = 2; hop <= r; hop++) {
            yk++;
            index_f2[hop - 1] = yk;
        }
        r = 514;
        loop_ub = index_f2.size(1);
        do {
            b_r.set_size(index_f2.size(1));
            e_y.set_size(1, index_f2.size(1));
            for (i = 0; i < loop_ub; i++) {
                itilerow = index_f2[i];
                b_r[i] = itilerow - 1;
                e_y[i].re = b_x[(1024 * (itilerow - 1) - r) + 1025].re;
                e_y[i].im = -b_x[(1024 * (itilerow - 1) - r) + 1025].im;
            }
            yk = e_y.size(1);
            for (i = 0; i < yk; i++) {
                b_x[(r + 1024 * b_r[i]) - 1] = e_y[i];
            }
            r++;
        } while (!(r == 1025));
    }
    r = b_x.size(1) << 10;
    c1.set_size(1024, b_x.size(1));
    for (hop = 0; hop < r; hop++) {
        c1[hop] = rt_hypotd_snf(b_x[hop].re, b_x[hop].im);
    }
    b_y.set_size(1024, c1.size(1));
    r = c1.size(1) << 10;
    for (hop = 0; hop < r; hop++) {
        b_y[hop] = c1[hop] * c1[hop];
    }
    if (b_y.size(1) == 0) {
        c_y.set_size(1024, 0);
    } else {
        b_x.set_size(1024, b_y.size(1));
        loop_ub = 1024 * b_y.size(1);
        for (i = 0; i < loop_ub; i++) {
            b_x[i].re = b_y[i];
            b_x[i].im = 0.0;
        }
        int b_sign;
        b_sign = FFTW_BACKWARD;
        iodims.n = 1024;
        iodims.is = 1;
        iodims.os = 1;
        howmany_iodims.n = b_x.size(1);
        howmany_iodims.is = 1024;
        howmany_iodims.os = 1024;
        mylock();
        fftw_init_threads();
        fftw_plan_with_nthreads(8);
        myunlock();
        c_y.set_size(1024, b_x.size(1));
        mylock();
        plan = fftw_plan_guru_dft(
            1, &iodims, 1, &howmany_iodims, (fftw_complex *)&b_x[0],
            (fftw_complex *)&c_y[0], b_sign,
            (unsigned int)FFTW_PRESERVE_INPUT | (unsigned int)FFTW_ESTIMATE);
        myunlock();
        fftw_execute(plan);
        mylock();
        fftw_destroy_plan(plan);
        myunlock();
        loop_ub = 1024 * c_y.size(1);
        c_y.set_size(1024, c_y.size(1));
        for (i = 0; i < loop_ub; i++) {
            double ai;
            double im;
            double re;
            im = c_y[i].re;
            ai = c_y[i].im;
            if (ai == 0.0) {
                re = im / 1024.0;
                im = 0.0;
            } else if (im == 0.0) {
                re = 0.0;
                im = ai / 1024.0;
            } else {
                re = im / 1024.0;
                im = ai / 1024.0;
            }
            c_y[i].re = re;
            c_y[i].im = im;
        }
    }
    c1.set_size(1024, c_y.size(1));
    loop_ub = 1024 * c_y.size(1);
    for (i = 0; i < loop_ub; i++) {
        c1[i] = c_y[i].re / 32.0;
    }
    d_y.set_size(1, 160);
    for (i = 0; i < 160; i++) {
        d_y[i] = static_cast<double>(i) + 1.0;
    }
    loop_ub = c1.size(1);
    lag.set_size(160, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 160; itilerow++) {
            lag[itilerow + lag.size(0) * i] =
                c1[(static_cast<int>(d_y[itilerow]) + 1024 * i) + 863];
        }
    }
    if (c1.size(1) != 0) {
        yk = c1.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        input_sizes_idx_0 = 160U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || (c1.size(1) != 0)) {
        r = 161;
    } else {
        r = 0;
    }
    hop = input_sizes_idx_0;
    loop_ub = c1.size(1);
    b_c1.set_size(161, c1.size(1));
    for (i = 0; i < loop_ub; i++) {
        for (itilerow = 0; itilerow < 161; itilerow++) {
            b_c1[itilerow + b_c1.size(0) * i] = c1[itilerow + 1024 * i];
        }
    }
    Rt.set_size(input_sizes_idx_0 + r, yk);
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < hop; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] =
                lag[itilerow + input_sizes_idx_0 * i];
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < r; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                b_c1[itilerow + r * i];
        }
    }
    if (181 > Rt.size(0)) {
        i = -1;
        itilerow = -1;
    } else {
        i = 179;
        itilerow = Rt.size(0) - 1;
    }
    loop_ub = Rt.size(1);
    d_y.set_size(1, Rt.size(1));
    for (r = 0; r < loop_ub; r++) {
        d_y[r] = Rt[Rt.size(0) * r + 160];
    }
    r = Rt.size(1) - 1;
    for (hop = 0; hop <= r; hop++) {
        d_y[hop] = sqrt(d_y[hop]);
    }
    loop_ub = itilerow - i;
    lag.set_size(loop_ub, d_y.size(1));
    yk = d_y.size(1);
    for (hop = 0; hop < yk; hop++) {
        r = hop * loop_ub;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            lag[r + itilerow] = d_y[hop];
        }
    }
    yk = Rt.size(1);
    lag.set_size(loop_ub, Rt.size(1));
    for (itilerow = 0; itilerow < yk; itilerow++) {
        for (r = 0; r < loop_ub; r++) {
            lag[r + lag.size(0) * itilerow] =
                Rt[((i + r) + Rt.size(0) * itilerow) + 1] /
                lag[r + lag.size(0) * itilerow];
        }
    }
    if (lag.size(1) != 0) {
        yk = lag.size(1);
    } else {
        yk = 0;
    }
    empty_non_axis_sizes = (yk == 0);
    if (empty_non_axis_sizes || (lag.size(1) != 0)) {
        input_sizes_idx_0 = 19U;
    } else {
        input_sizes_idx_0 = 0U;
    }
    if (empty_non_axis_sizes || ((lag.size(0) != 0) && (lag.size(1) != 0))) {
        r = lag.size(0);
    } else {
        r = 0;
    }
    Rt.set_size(input_sizes_idx_0 + r, yk);
    for (i = 0; i < yk; i++) {
        loop_ub = input_sizes_idx_0;
        for (itilerow = 0; itilerow < loop_ub; itilerow++) {
            Rt[itilerow + Rt.size(0) * i] = 0.0;
        }
    }
    for (i = 0; i < yk; i++) {
        for (itilerow = 0; itilerow < r; itilerow++) {
            Rt[(itilerow + input_sizes_idx_0) + Rt.size(0) * i] =
                lag[itilerow + r * i];
        }
    }
    audio::internal::pitch::getCandidates(Rt, edge, peak, locs);
    loop_ub = locs.size(0);
    for (i = 0; i < loop_ub; i++) {
        locs[i] = 8000.0 / locs[i];
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] < 50.0) {
            locs[yk] = 50.0;
        }
    }
    r = locs.size(0);
    for (yk = 0; yk < r; yk++) {
        if (locs[yk] > 400.0) {
            locs[yk] = 400.0;
        }
    }
    locs.set_size(static_cast<int>(
                      ceil((static_cast<double>(x.size(0)) - 400.0) / 200.0)) +
                  1);
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 400.0) / 200.0));
    if (1 > r + 1) {
        loop_ub = -1;
    } else {
        loop_ub = r;
    }
    f0.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
        f0[i] = locs[i];
    }
}

} // namespace coder
