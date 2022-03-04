#include "any1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

namespace coder {
boolean_T any(const ::coder::array<double, 1U> &x)
{
    int ix;
    boolean_T exitg1;
    boolean_T y;
    y = false;
    ix = 0;
    exitg1 = false;
    while ((!exitg1) && (ix + 1 <= x.size(0))) {
        if ((x[ix] == 0.0) || rtIsNaN(x[ix])) {
            ix++;
        } else {
            y = true;
            exitg1 = true;
        }
    }
    return y;
}

} // namespace coder
