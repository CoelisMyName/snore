//
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "nullAssignment.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
namespace coder {
    namespace internal {
        void nullAssignment(::coder::array<double, 2U> &x) {
            array<double, 2U> b_x;
            int nxin;
            int nxout;
            nxin = x.size(1) - 1;
            nxout = x.size(1);
            for (int k = 0; k <= nxout - 2; k++) {
                x[k] = x[k + 1];
            }
            if (1 > nxin) {
                nxin = 0;
            }
            b_x.set_size(1, nxin);
            for (nxout = 0; nxout < nxin; nxout++) {
                b_x[nxout] = x[nxout];
            }
            x.set_size(1, b_x.size(1));
            nxin = b_x.size(1);
            for (nxout = 0; nxout < nxin; nxout++) {
                x[nxout] = b_x[nxout];
            }
        }

//
// Arguments    : ::coder::array<double, 2U> &x
//                int idx
// Return Type  : void
//
        void nullAssignment(::coder::array<double, 2U> &x, int idx) {
            array<double, 2U> b_x;
            int nxin;
            int nxout;
            nxin = x.size(1) - 1;
            nxout = x.size(1) - 1;
            for (int k = idx; k <= nxout; k++) {
                x[k - 1] = x[k];
            }
            if (1 > nxin) {
                nxin = 0;
            }
            b_x.set_size(1, nxin);
            for (nxout = 0; nxout < nxin; nxout++) {
                b_x[nxout] = x[nxout];
            }
            x.set_size(1, b_x.size(1));
            nxin = b_x.size(1);
            for (nxout = 0; nxout < nxin; nxout++) {
                x[nxout] = b_x[nxout];
            }
        }

    } // namespace internal
} // namespace coder

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
