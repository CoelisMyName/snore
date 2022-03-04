#include "nanmean.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

namespace coder {
double nanmean(const ::coder::array<double, 2U> &varargin_1)
{
    double y;
    if (varargin_1.size(1) == 0) {
        y = rtNaN;
    } else {
        int c;
        int vlen;
        vlen = varargin_1.size(1);
        y = 0.0;
        c = 0;
        for (int k = 0; k < vlen; k++) {
            double d;
            d = varargin_1[k];
            if (!rtIsNaN(d)) {
                y += d;
                c++;
            }
        }
        if (c == 0) {
            y = rtNaN;
        } else {
            y /= static_cast<double>(c);
        }
    }
    return y;
}

} // namespace coder
