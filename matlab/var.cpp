#include "var.h"
#include "rt_nonfinite.h"
#include "vvarstd.h"
#include "coder_array.h"
#include "mylock.h"

namespace coder {
void var(const ::coder::array<double, 2U> &x, double y_data[], int y_size[2])
{
    array<double, 1U> xv;
    int loop_ub;
    int npages;
    int outsize_idx_0;
    int szy_idx_1;
    szy_idx_1 = x.size(1);
    y_size[0] = 1;
    y_size[1] = x.size(1);
    if (0 <= szy_idx_1 - 1) {
        y_data[0] = 0.0;
    }
    szy_idx_1 = x.size(0);
    npages = x.size(1);
    if (0 <= x.size(1) - 1) {
        outsize_idx_0 = x.size(0);
        loop_ub = x.size(0);
    }
    for (int p = 0; p < npages; p++) {
        int k;
        xv.set_size(outsize_idx_0);
        for (k = 0; k < loop_ub; k++) {
            xv[k] = 0.0;
        }
        for (k = 0; k < szy_idx_1; k++) {
            xv[k] = x[k];
        }
        y_data[0] = vvarstd(xv, x.size(0));
    }
}

} // namespace coder
