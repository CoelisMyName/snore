#include "mtimes.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"

namespace coder {
namespace internal {
namespace blas {
void mtimes(const ::coder::array<double, 2U> &A,
            const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C)
{
    int inner;
    int mc;
    int nc;
    mc = A.size(0);
    inner = A.size(1);
    nc = B.size(1);
    C.set_size(A.size(0), B.size(1));
    for (int j = 0; j < nc; j++) {
        int boffset;
        int coffset;
        int i;
        coffset = j * mc;
        boffset = j * B.size(0);
        for (i = 0; i < mc; i++) {
            C[coffset + i] = 0.0;
        }
        for (int k = 0; k < inner; k++) {
            double bkj;
            int aoffset;
            aoffset = k * A.size(0);
            bkj = B[boffset + k];
            for (i = 0; i < mc; i++) {
                int b_i;
                b_i = coffset + i;
                C[b_i] = C[b_i] + A[aoffset + i] * bkj;
            }
        }
    }
}

} // namespace blas
} // namespace internal
} // namespace coder
