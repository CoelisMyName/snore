//
// File: log10.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "log10.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double x_data[]
//                const int x_size[2]
// Return Type  : void
//
namespace coder {
    void b_log10(double x_data[], const int x_size[2]) {
        int nx;
        nx = x_size[1];
        for (int k = 0; k < nx; k++) {
            x_data[k] = log10(x_data[k]);
        }
    }

//
// Arguments    : double *x
// Return Type  : void
//
    void b_log10(double *x) {
        *x = log10(*x);
    }

} // namespace coder

//
// File trailer for log10.cpp
//
// [EOF]
//
