#include "colon.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

namespace coder {
void eml_float_colon(double a, double b, ::coder::array<double, 2U> &y)
{
    double apnd;
    double cdiff;
    double ndbl;
    double u0;
    double u1;
    int n;
    ndbl = floor((b - a) + 0.5);
    apnd = a + ndbl;
    cdiff = apnd - b;
    u0 = fabs(a);
    u1 = fabs(b);
    if ((u0 > u1) || rtIsNaN(u1)) {
        u1 = u0;
    }
    if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
        ndbl++;
        apnd = b;
    } else if (cdiff > 0.0) {
        apnd = a + (ndbl - 1.0);
    } else {
        ndbl++;
    }
    if (ndbl >= 0.0) {
        n = static_cast<int>(ndbl);
    } else {
        n = 0;
    }
    y.set_size(1, n);
    if (n > 0) {
        y[0] = a;
        if (n > 1) {
            int nm1d2;
            y[n - 1] = apnd;
            nm1d2 = (n - 1) / 2;
            for (int k = 0; k <= nm1d2 - 2; k++) {
                y[k + 1] = a + (static_cast<double>(k) + 1.0);
                y[(n - k) - 2] = apnd - (static_cast<double>(k) + 1.0);
            }
            if (nm1d2 << 1 == n - 1) {
                y[nm1d2] = (a + apnd) / 2.0;
            } else {
                y[nm1d2] = a + static_cast<double>(nm1d2);
                y[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
            }
        }
    }
}

} // namespace coder
