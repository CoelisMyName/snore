#include "insertionsort.h"
#include "anonymous_function.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"

namespace coder {
namespace internal {
void insertionsort(::coder::array<int, 1U> &x, int xstart, int xend,
                   const anonymous_function *cmp)
{
    int i;
    i = xstart + 1;
    for (int k = i; k <= xend; k++) {
        int idx;
        int xc;
        boolean_T exitg1;
        xc = x[k - 1] - 1;
        idx = k - 2;
        exitg1 = false;
        while ((!exitg1) && (idx + 1 >= xstart)) {
            boolean_T varargout_1;
            varargout_1 =
                ((cmp->workspace.a[xc] < cmp->workspace.a[x[idx] - 1]) ||
                 ((cmp->workspace.a[xc] == cmp->workspace.a[x[idx] - 1]) &&
                  (cmp->workspace.b[xc] < cmp->workspace.b[x[idx] - 1])));
            if (varargout_1) {
                x[idx + 1] = x[idx];
                idx--;
            } else {
                exitg1 = true;
            }
        }
        x[idx + 1] = xc + 1;
    }
}

} // namespace internal
} // namespace coder
