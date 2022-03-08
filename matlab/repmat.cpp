#include "repmat.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"

namespace coder {
void repmat(const double a[4160], const double varargin_1[3],
            ::coder::array<double, 3U> &b)
{
    int tile_size[3];
    int ibtile;
    int k;
    int ntilecols;
    tile_size[0] = 1;
    tile_size[1] = 1;
    ibtile = static_cast<int>(varargin_1[2]);
    tile_size[2] = static_cast<int>(varargin_1[2]);
    b.set_size(130, 32, ibtile);
    ntilecols = 1;
    k = 3;
    if (static_cast<int>(varargin_1[2]) == 1) {
        k = 2;
    }
    for (ibtile = 2; ibtile <= k; ibtile++) {
        ntilecols *= tile_size[ibtile - 1];
    }
    for (int jtilecol = 0; jtilecol < ntilecols; jtilecol++) {
        ibtile = jtilecol * 4160 - 1;
        for (int jcol = 0; jcol < 32; jcol++) {
            int iacol;
            int ibmat;
            iacol = jcol * 130;
            ibmat = ibtile + jcol * 130;
            for (k = 0; k < 130; k++) {
                b[(ibmat + k) + 1] = a[iacol + k];
            }
        }
    }
}

} // namespace coder
