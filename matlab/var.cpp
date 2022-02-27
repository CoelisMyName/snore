//
// File: var.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "var.h"
#include "rt_nonfinite.h"
#include "vvarstd.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                double y_data[]
//                int y_size[2]
// Return Type  : void
//
namespace coder {
    void var(const ::coder::array<double, 2U> &x, double y_data[], int y_size[2]) {
        array<double, 1U> xv;
        int loop_ub;
        int npages;
        int outsize_idx_0;
        int szy_idx_1;
        szy_idx_1 = x.size(1);
        y_size[0] = 1;
        y_size[1] = x.size(1);
        if (0 <= szy_idx_1 - 1) {
            y_data[0] = 0.0;
        }
        szy_idx_1 = x.size(0);
        npages = x.size(1);
        if (0 <= x.size(1) - 1) {
            outsize_idx_0 = x.size(0);
            loop_ub = x.size(0);
        }
        for (int p = 0; p < npages; p++) {
            int k;
            xv.set_size(outsize_idx_0);
            for (k = 0; k < loop_ub; k++) {
                xv[k] = 0.0;
            }
            for (k = 0; k < szy_idx_1; k++) {
                xv[k] = x[k];
            }
            y_data[0] = vvarstd(xv, x.size(0));
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
//                double y[12]
// Return Type  : void
//
    void var(const ::coder::array<double, 2U> &x, double y[12]) {
        array<double, 1U> xv;
        int loop_ub;
        int nx;
        nx = x.size(0);
        loop_ub = x.size(0);
        for (int p = 0; p < 12; p++) {
            int k;
            int workspace_ixfirst;
            workspace_ixfirst = p * nx;
            xv.set_size(nx);
            for (k = 0; k < loop_ub; k++) {
                xv[k] = 0.0;
            }
            for (k = 0; k < nx; k++) {
                xv[k] = x[workspace_ixfirst + k];
            }
            y[p] = vvarstd(xv, x.size(0));
        }
    }

//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
    double var(const ::coder::array<double, 2U> &x) {
        array<double, 1U> c_x;
        int b_x;
        b_x = x.size(1);
        c_x = x.reshape(b_x);
        return vvarstd(c_x, x.size(1));
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
    double var(const ::coder::array<double, 1U> &x) {
        return vvarstd(x, x.size(0));
    }

} // namespace coder

//
// File trailer for var.cpp
//
// [EOF]
//
