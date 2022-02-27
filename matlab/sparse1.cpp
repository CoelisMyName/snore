//
// File: sparse1.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "sparse1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
    void sparse::full(::coder::array<double, 2U> &y) const {
        int cend;
        int i;
        y.set_size(16, this->n);
        cend = this->n << 4;
        for (i = 0; i < cend; i++) {
            y[i] = 0.0;
        }
        i = this->n;
        for (int c = 0; c < i; c++) {
            int i1;
            cend = this->colidx[c + 1] - 1;
            i1 = this->colidx[c];
            for (int idx = i1; idx <= cend; idx++) {
                y[(this->rowidx[idx - 1] + 16 * c) - 1] = this->d[idx - 1];
            }
        }
    }

} // namespace coder

//
// File trailer for sparse1.cpp
//
// [EOF]
//
