#include "mod.h"
#include "rt_nonfinite.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <math.h>

namespace coder {
double b_mod(double x)
{
    double r;
    if (rtIsNaN(x) || rtIsInf(x)) {
        r = rtNaN;
    } else if (x == 0.0) {
        r = 0.0;
    } else {
        r = fmod(x, 2.0);
        if (r == 0.0) {
            r = 0.0;
        } else if (x < 0.0) {
            r += 2.0;
        }
    }
    return r;
}

} // namespace coder
