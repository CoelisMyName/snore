#include "xnrm2.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "mylock.h"
#include <math.h>

namespace coder {
namespace internal {
namespace blas {
double b_xnrm2(int n, const double x_data[], int ix0)
{
    double y;
    y = 0.0;
    if (n >= 1) {
        if (n == 1) {
            y = fabs(x_data[ix0 - 1]);
        } else {
            double scale;
            int kend;
            scale = 3.3121686421112381E-170;
            kend = (ix0 + n) - 1;
            for (int k = ix0; k <= kend; k++) {
                double absxk;
                absxk = fabs(x_data[k - 1]);
                if (absxk > scale) {
                    double t;
                    t = scale / absxk;
                    y = y * t * t + 1.0;
                    scale = absxk;
                } else {
                    double t;
                    t = absxk / scale;
                    y += t * t;
                }
            }
            y = scale * sqrt(y);
        }
    }
    return y;
}

double xnrm2(int n, const creal_T x_data[], int ix0)
{
    double y;
    y = 0.0;
    if (n >= 1) {
        if (n == 1) {
            y = rt_hypotd_snf(x_data[ix0 - 1].re, x_data[ix0 - 1].im);
        } else {
            double scale;
            int kend;
            scale = 3.3121686421112381E-170;
            kend = (ix0 + n) - 1;
            for (int k = ix0; k <= kend; k++) {
                double absxk;
                double t;
                absxk = fabs(x_data[k - 1].re);
                if (absxk > scale) {
                    t = scale / absxk;
                    y = y * t * t + 1.0;
                    scale = absxk;
                } else {
                    t = absxk / scale;
                    y += t * t;
                }
                absxk = fabs(x_data[k - 1].im);
                if (absxk > scale) {
                    t = scale / absxk;
                    y = y * t * t + 1.0;
                    scale = absxk;
                } else {
                    t = absxk / scale;
                    y += t * t;
                }
            }
            y = scale * sqrt(y);
        }
    }
    return y;
}

double xnrm2(int n, const double x[36], int ix0)
{
    double y;
    y = 0.0;
    if (n >= 1) {
        if (n == 1) {
            y = fabs(x[ix0 - 1]);
        } else {
            double scale;
            int kend;
            scale = 3.3121686421112381E-170;
            kend = (ix0 + n) - 1;
            for (int k = ix0; k <= kend; k++) {
                double absxk;
                absxk = fabs(x[k - 1]);
                if (absxk > scale) {
                    double t;
                    t = scale / absxk;
                    y = y * t * t + 1.0;
                    scale = absxk;
                } else {
                    double t;
                    t = absxk / scale;
                    y += t * t;
                }
            }
            y = scale * sqrt(y);
        }
    }
    return y;
}

double xnrm2(int n, const double x[3])
{
    double y;
    y = 0.0;
    if (n >= 1) {
        if (n == 1) {
            y = fabs(x[1]);
        } else {
            double absxk;
            double scale;
            double t;
            scale = 3.3121686421112381E-170;
            absxk = fabs(x[1]);
            if (absxk > 3.3121686421112381E-170) {
                y = 1.0;
                scale = absxk;
            } else {
                t = absxk / 3.3121686421112381E-170;
                y = t * t;
            }
            absxk = fabs(x[2]);
            if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
            } else {
                t = absxk / scale;
                y += t * t;
            }
            y = scale * sqrt(y);
        }
    }
    return y;
}

} // namespace blas
} // namespace internal
} // namespace coder
