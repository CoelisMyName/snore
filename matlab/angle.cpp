//
// File: angle.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "angle.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const creal_T x_data[]
//                const int x_size[2]
//                double y_data[]
//                int y_size[2]
// Return Type  : void
//
namespace coder {
    void angle(const creal_T x_data[], const int x_size[2], double y_data[],
               int y_size[2]) {
        int nx;
        nx = x_size[1];
        y_size[0] = 1;
        y_size[1] = static_cast<signed char>(x_size[1]);
        for (int k = 0; k < nx; k++) {
            y_data[k] = rt_atan2d_snf(x_data[k].im, x_data[k].re);
        }
    }

} // namespace coder

//
// File trailer for angle.cpp
//
// [EOF]
//
