#include "pitch.h"
#include "NCF.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

namespace coder {
void b_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<double, 2U> y;
    int b_x;
    int i;
    int loop_ub;
    int r;
    r = x.size(0);
    b_x = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 551.0) / 275.0));
    y.set_size(551, b_x + 1);
    loop_ub = 551 * (b_x + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (int hop = 0; hop <= b_x; hop++) {
        int i1;
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
            i1 = 0;
        } else {
            i1 = static_cast<int>(u1);
        }
        loop_ub = i1 - i;
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1 + 551 * hop] = x[i + i1];
        }
    }
    audio::internal::pitch::b_NCF(y, f0);
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] < 50.0) {
            f0[b_x] = 50.0;
        }
    }
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] > 400.0) {
            f0[b_x] = 400.0;
        }
    }
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 551.0) / 275.0));
    if (1 > r + 1) {
        r = -1;
    }
    f0.set_size(r + 1);
}

void c_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<double, 2U> y;
    int b_x;
    int i;
    int loop_ub;
    int r;
    r = x.size(0);
    b_x = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 600.0) / 300.0));
    y.set_size(600, b_x + 1);
    loop_ub = 600 * (b_x + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (int hop = 0; hop <= b_x; hop++) {
        int i1;
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
            i1 = 0;
        } else {
            i1 = static_cast<int>(u1);
        }
        loop_ub = i1 - i;
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1 + 600 * hop] = x[i + i1];
        }
    }
    audio::internal::pitch::c_NCF(y, f0);
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] < 50.0) {
            f0[b_x] = 50.0;
        }
    }
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] > 400.0) {
            f0[b_x] = 400.0;
        }
    }
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 600.0) / 300.0));
    if (1 > r + 1) {
        r = -1;
    }
    f0.set_size(r + 1);
}

void d_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<double, 2U> y;
    int b_x;
    int i;
    int loop_ub;
    int r;
    r = x.size(0);
    b_x = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 1103.0) / 552.0));
    y.set_size(1103, b_x + 1);
    loop_ub = 1103 * (b_x + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (int hop = 0; hop <= b_x; hop++) {
        int i1;
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
            i1 = 0;
        } else {
            i1 = static_cast<int>(u1);
        }
        loop_ub = i1 - i;
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1 + 1103 * hop] = x[i + i1];
        }
    }
    audio::internal::pitch::d_NCF(y, f0);
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] < 50.0) {
            f0[b_x] = 50.0;
        }
    }
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] > 400.0) {
            f0[b_x] = 400.0;
        }
    }
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 1103.0) / 552.0));
    if (1 > r + 1) {
        r = -1;
    }
    f0.set_size(r + 1);
}

void e_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<double, 2U> y;
    int b_x;
    int i;
    int loop_ub;
    int r;
    r = x.size(0);
    b_x = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 1200.0) / 600.0));
    y.set_size(1200, b_x + 1);
    loop_ub = 1200 * (b_x + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (int hop = 0; hop <= b_x; hop++) {
        int i1;
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
            i1 = 0;
        } else {
            i1 = static_cast<int>(u1);
        }
        loop_ub = i1 - i;
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1 + 1200 * hop] = x[i + i1];
        }
    }
    audio::internal::pitch::e_NCF(y, f0);
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] < 50.0) {
            f0[b_x] = 50.0;
        }
    }
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] > 400.0) {
            f0[b_x] = 400.0;
        }
    }
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 1200.0) / 600.0));
    if (1 > r + 1) {
        r = -1;
    }
    f0.set_size(r + 1);
}

void f_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<double, 2U> y;
    int b_x;
    int i;
    int loop_ub;
    int r;
    r = x.size(0);
    b_x = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 2205.0) / 1102.0));
    y.set_size(2205, b_x + 1);
    loop_ub = 2205 * (b_x + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (int hop = 0; hop <= b_x; hop++) {
        int i1;
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
            i1 = 0;
        } else {
            i1 = static_cast<int>(u1);
        }
        loop_ub = i1 - i;
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1 + 2205 * hop] = x[i + i1];
        }
    }
    audio::internal::pitch::f_NCF(y, f0);
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] < 50.0) {
            f0[b_x] = 50.0;
        }
    }
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] > 400.0) {
            f0[b_x] = 400.0;
        }
    }
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 2205.0) / 1102.0));
    if (1 > r + 1) {
        r = -1;
    }
    f0.set_size(r + 1);
}

void g_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0)
{
    array<double, 2U> y;
    int b_x;
    int i;
    int loop_ub;
    int r;
    r = x.size(0);
    b_x = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 2400.0) / 1200.0));
    y.set_size(2400, b_x + 1);
    loop_ub = 2400 * (b_x + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (int hop = 0; hop <= b_x; hop++) {
        int i1;
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
            i1 = 0;
        } else {
            i1 = static_cast<int>(u1);
        }
        loop_ub = i1 - i;
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1 + 2400 * hop] = x[i + i1];
        }
    }
    audio::internal::pitch::g_NCF(y, f0);
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] < 50.0) {
            f0[b_x] = 50.0;
        }
    }
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] > 400.0) {
            f0[b_x] = 400.0;
        }
    }
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 2400.0) / 1200.0));
    if (1 > r + 1) {
        r = -1;
    }
    f0.set_size(r + 1);
}

void pitch(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &f0)
{
    array<double, 2U> y;
    int b_x;
    int i;
    int loop_ub;
    int r;
    r = x.size(0);
    b_x = static_cast<int>(
        ceil((static_cast<double>(x.size(0)) - 400.0) / 200.0));
    y.set_size(400, b_x + 1);
    loop_ub = 400 * (b_x + 1);
    for (i = 0; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    for (int hop = 0; hop <= b_x; hop++) {
        int i1;
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
            i1 = 0;
        } else {
            i1 = static_cast<int>(u1);
        }
        loop_ub = i1 - i;
        for (i1 = 0; i1 < loop_ub; i1++) {
            y[i1 + 400 * hop] = x[i + i1];
        }
    }
    audio::internal::pitch::NCF(y, f0);
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] < 50.0) {
            f0[b_x] = 50.0;
        }
    }
    r = f0.size(0);
    for (b_x = 0; b_x < r; b_x++) {
        if (f0[b_x] > 400.0) {
            f0[b_x] = 400.0;
        }
    }
    r = static_cast<int>(
        floor((static_cast<double>(x.size(0)) - 400.0) / 200.0));
    if (1 > r + 1) {
        r = -1;
    }
    f0.set_size(r + 1);
}

} // namespace coder
