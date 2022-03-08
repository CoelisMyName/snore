#include "vvarstd.h"
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"

namespace coder {
double vvarstd(const ::coder::array<double, 1U> &v, int n)
{
    double s;
    if (n == 0) {
        s = rtNaN;
    } else if (n == 1) {
        if ((!rtIsInf(v[0])) && (!rtIsNaN(v[0]))) {
            s = 0.0;
        } else {
            s = rtNaN;
        }
    } else {
        double xbar;
        xbar = blockedSummation(v, n) / static_cast<double>(n);
        s = 0.0;
        for (int k = 0; k < n; k++) {
            double t;
            t = v[k] - xbar;
            s += t * t;
        }
        s /= static_cast<double>(n - 1);
    }
    return s;
}

} // namespace coder
