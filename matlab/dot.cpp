//
// File: dot.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "dot.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 3U> &a
//                const ::coder::array<double, 3U> &b
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
namespace coder {
    void dot(const ::coder::array<double, 3U> &a,
             const ::coder::array<double, 3U> &b, ::coder::array<double, 2U> &c) {
        int i1;
        int vstride;
        c.set_size(a.size(0), 32);
        vstride = a.size(0) * 32;
        i1 = -1;
        for (int j = 0; j < vstride; j++) {
            double b_c;
            i1++;
            b_c = 0.0;
            for (int k = 0; k < 130; k++) {
                int c_tmp;
                c_tmp = i1 + k * vstride;
                b_c += a[c_tmp] * b[c_tmp];
            }
            c[j] = b_c;
        }
    }

} // namespace coder

//
// File trailer for dot.cpp
//
// [EOF]
//
