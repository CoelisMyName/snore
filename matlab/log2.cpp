#include "log2.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

namespace coder {
namespace internal {
namespace scalar {
double b_log2(double x)
{
    double f;
    int eint;
    if (x == 0.0) {
        f = rtMinusInf;
    } else if (x < 0.0) {
        f = rtNaN;
    } else if ((!rtIsInf(x)) && (!rtIsNaN(x))) {
        double t;
        t = frexp(x, &eint);
        if (t == 0.5) {
            f = static_cast<double>(eint) - 1.0;
        } else if ((eint == 1) && (t < 0.75)) {
            f = log(2.0 * t) / 0.69314718055994529;
        } else {
            f = log(t) / 0.69314718055994529 + static_cast<double>(eint);
        }
    } else {
        f = x;
    }
    return f;
}

} // namespace scalar
} // namespace internal
} // namespace coder
