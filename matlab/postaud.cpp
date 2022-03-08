#include "postaud.h"
#include "SnoringRecognition_rtwutil.h"
#include "asinh.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include <math.h>

void postaud(const coder::array<double, 2U> &x, double b_fmax,
             coder::array<double, 2U> &y)
{
    coder::array<double, 2U> a;
    coder::array<double, 2U> b_z;
    coder::array<double, 2U> bandcfhz;
    coder::array<double, 2U> c_a;
    coder::array<double, 2U> fsq;
    coder::array<double, 2U> z;
    coder::array<double, 1U> b_a;
    coder::array<int, 1U> r;
    double delta1;
    int ibtile;
    int jtilecol;
    int k;
    int ntilecols;
    int nx;
    delta1 = b_fmax / 600.0;
    coder::internal::scalar::b_asinh(&delta1);
    delta1 *= 6.0;
    z.set_size(1, x.size(0));
    if (x.size(0) >= 1) {
        z[x.size(0) - 1] = delta1;
        if (z.size(1) >= 2) {
            z[0] = 0.0;
            if (z.size(1) >= 3) {
                if ((0.0 == -delta1) && (x.size(0) > 2)) {
                    delta1 /= static_cast<double>(x.size(0)) - 1.0;
                    jtilecol = x.size(0) - 1;
                    for (k = 2; k <= jtilecol; k++) {
                        z[k - 1] =
                            static_cast<double>(((k << 1) - x.size(0)) - 1) *
                            delta1;
                    }
                    if ((x.size(0) & 1) == 1) {
                        z[x.size(0) >> 1] = 0.0;
                    }
                } else if ((delta1 < 0.0) &&
                           (fabs(delta1) > 8.9884656743115785E+307)) {
                    delta1 /= static_cast<double>(z.size(1)) - 1.0;
                    jtilecol = z.size(1);
                    for (k = 0; k <= jtilecol - 3; k++) {
                        z[k + 1] = delta1 * (static_cast<double>(k) + 1.0);
                    }
                } else {
                    delta1 /= static_cast<double>(z.size(1)) - 1.0;
                    jtilecol = z.size(1);
                    for (k = 0; k <= jtilecol - 3; k++) {
                        z[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
                    }
                }
            }
        }
    }
    z.set_size(1, z.size(1));
    nx = z.size(1) - 1;
    for (jtilecol = 0; jtilecol <= nx; jtilecol++) {
        z[jtilecol] = z[jtilecol] / 6.0;
    }
    nx = z.size(1);
    for (k = 0; k < nx; k++) {
        z[k] = sinh(z[k]);
    }
    bandcfhz.set_size(1, z.size(1));
    nx = z.size(1);
    for (jtilecol = 0; jtilecol < nx; jtilecol++) {
        bandcfhz[jtilecol] = 600.0 * z[jtilecol];
    }
    if (1 > x.size(0)) {
        nx = 0;
    } else {
        nx = x.size(0);
    }
    bandcfhz.set_size(bandcfhz.size(0), nx);
    if (1 > x.size(0)) {
        nx = 0;
    } else {
        nx = x.size(0);
    }
    fsq.set_size(1, nx);
    nx = bandcfhz.size(1);
    for (k = 0; k < nx; k++) {
        delta1 = bandcfhz[k];
        fsq[k] = delta1 * delta1;
    }
    a.set_size(1, fsq.size(1));
    nx = fsq.size(1);
    for (jtilecol = 0; jtilecol < nx; jtilecol++) {
        delta1 = fsq[jtilecol];
        a[jtilecol] = delta1 / (delta1 + 160000.0);
    }
    z.set_size(1, a.size(1));
    nx = a.size(1);
    for (k = 0; k < nx; k++) {
        delta1 = a[k];
        z[k] = delta1 * delta1;
    }
    b_a.set_size(z.size(1));
    nx = z.size(1);
    for (jtilecol = 0; jtilecol < nx; jtilecol++) {
        delta1 = fsq[jtilecol];
        b_a[jtilecol] = z[jtilecol] * ((delta1 + 1.44E+6) / (delta1 + 9.61E+6));
    }
    c_a.set_size(b_a.size(0), x.size(1));
    nx = b_a.size(0);
    ntilecols = x.size(1);
    for (jtilecol = 0; jtilecol < ntilecols; jtilecol++) {
        ibtile = jtilecol * nx;
        for (k = 0; k < nx; k++) {
            c_a[ibtile + k] = b_a[k];
        }
    }
    nx = c_a.size(0) * c_a.size(1);
    for (jtilecol = 0; jtilecol < nx; jtilecol++) {
        c_a[jtilecol] = c_a[jtilecol] * x[jtilecol];
    }
    b_z.set_size(c_a.size(0), c_a.size(1));
    nx = c_a.size(0) * c_a.size(1);
    for (k = 0; k < nx; k++) {
        b_z[k] = rt_powd_snf(c_a[k], 0.33);
    }
    if (x.size(0) - 1 < 2) {
        z.set_size(1, 0);
    } else {
        z.set_size(
            1,
            static_cast<int>((static_cast<double>(x.size(0)) - 1.0) - 2.0) + 1);
        nx = static_cast<int>((static_cast<double>(x.size(0)) - 1.0) - 2.0);
        for (jtilecol = 0; jtilecol <= nx; jtilecol++) {
            z[jtilecol] = static_cast<double>(jtilecol) + 2.0;
        }
    }
    r.set_size(z.size(1) + 2);
    r[0] = 1;
    nx = z.size(1);
    for (jtilecol = 0; jtilecol < nx; jtilecol++) {
        r[jtilecol + 1] = static_cast<int>(z[jtilecol]) - 1;
    }
    r[z.size(1) + 1] = x.size(0) - 2;
    nx = b_z.size(1);
    y.set_size(r.size(0), b_z.size(1));
    for (jtilecol = 0; jtilecol < nx; jtilecol++) {
        ntilecols = r.size(0);
        for (ibtile = 0; ibtile < ntilecols; ibtile++) {
            y[ibtile + y.size(0) * jtilecol] =
                b_z[r[ibtile] + b_z.size(0) * jtilecol];
        }
    }
}
