//
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
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
            int nxin;
            int nxout;
            nxin = x.size(1);
            nxout = x.size(1) - 1;
            for (int k = 0; k < nxout; k++) {
                x[k] = x[k + 1];
            }
            if (1 > nxout) {
                nxin = 0;
            } else {
                nxin--;
            }
            x.set_size(x.size(0), nxin);
        }

//
// Arguments    : ::coder::array<double, 2U> &x
//                int idx
// Return Type  : void
//
        void nullAssignment(::coder::array<double, 2U> &x, int idx) {
            int nxin;
            int nxout;
            nxin = x.size(1);
            nxout = x.size(1) - 1;
            for (int k = idx; k <= nxout; k++) {
                x[k - 1] = x[k];
            }
            if (1 > nxout) {
                nxin = 0;
            } else {
                nxin--;
            }
            x.set_size(x.size(0), nxin);
        }

    } // namespace internal
} // namespace coder

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
