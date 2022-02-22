//
// File: sign.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "sign.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &x
// Return Type  : void
//
namespace coder {
    void b_sign(::coder::array<double, 1U> &x) {
        int nx;
        nx = x.size(0);
        for (int k = 0; k < nx; k++) {
            double b_x;
            b_x = x[k];
            if (x[k] < 0.0) {
                b_x = -1.0;
            } else if (x[k] > 0.0) {
                b_x = 1.0;
            } else if (x[k] == 0.0) {
                b_x = 0.0;
            }
            x[k] = b_x;
        }
    }

//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
    void b_sign(::coder::array<double, 2U> &x) {
        int nx;
        nx = x.size(1);
        for (int k = 0; k < nx; k++) {
            double b_x;
            b_x = x[k];
            if (x[k] < 0.0) {
                b_x = -1.0;
            } else if (x[k] > 0.0) {
                b_x = 1.0;
            } else if (x[k] == 0.0) {
                b_x = 0.0;
            }
            x[k] = b_x;
        }
    }

//
// Arguments    : double x[2]
// Return Type  : void
//
    void b_sign(double x[2]) {
        double b_x;
        b_x = x[0];
        if (x[0] < 0.0) {
            b_x = -1.0;
        } else if (x[0] > 0.0) {
            b_x = 1.0;
        } else if (x[0] == 0.0) {
            b_x = 0.0;
        }
        x[0] = b_x;
        b_x = x[1];
        if (x[1] < 0.0) {
            b_x = -1.0;
        } else if (x[1] > 0.0) {
            b_x = 1.0;
        } else if (x[1] == 0.0) {
            b_x = 0.0;
        }
        x[1] = b_x;
    }

//
// Arguments    : double x[4]
// Return Type  : void
//
    void c_sign(double x[4]) {
        double b_x;
        b_x = x[0];
        if (x[0] < 0.0) {
            b_x = -1.0;
        } else if (x[0] > 0.0) {
            b_x = 1.0;
        } else if (x[0] == 0.0) {
            b_x = 0.0;
        }
        x[0] = b_x;
        b_x = x[1];
        if (x[1] < 0.0) {
            b_x = -1.0;
        } else if (x[1] > 0.0) {
            b_x = 1.0;
        } else if (x[1] == 0.0) {
            b_x = 0.0;
        }
        x[1] = b_x;
        b_x = x[2];
        if (x[2] < 0.0) {
            b_x = -1.0;
        } else if (x[2] > 0.0) {
            b_x = 1.0;
        } else if (x[2] == 0.0) {
            b_x = 0.0;
        }
        x[2] = b_x;
        b_x = x[3];
        if (x[3] < 0.0) {
            b_x = -1.0;
        } else if (x[3] > 0.0) {
            b_x = 1.0;
        } else if (x[3] == 0.0) {
            b_x = 0.0;
        }
        x[3] = b_x;
    }

} // namespace coder

//
// File trailer for sign.cpp
//
// [EOF]
//
