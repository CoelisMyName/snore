//
// File: sparse1.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef SPARSE1_H
#define SPARSE1_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
    class sparse {
    public:
        void full(::coder::array<double, 2U> &y) const;

        array<double, 1U> d;
        array<int, 1U> colidx;
        array<int, 1U> rowidx;
        int n;
    };

} // namespace coder

#endif
//
// File trailer for sparse1.h
//
// [EOF]
//
