//
// File: nanmean.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "nanmean.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &varargin_1
// Return Type  : double
//
namespace coder {
    double nanmean(const ::coder::array<double, 2U> &varargin_1) {
        double y;
        if (varargin_1.size(1) == 0) {
            y = rtNaN;
        } else {
            int c;
            int vlen;
            vlen = varargin_1.size(1);
            y = 0.0;
            c = 0;
            for (int k = 0; k < vlen; k++) {
                double d;
                d = varargin_1[k];
                if (!rtIsNaN(d)) {
                    y += d;
                    c++;
                }
            }
            if (c == 0) {
                y = rtNaN;
            } else {
                y /= static_cast<double>(c);
            }
        }
        return y;
    }

} // namespace coder

//
// File trailer for nanmean.cpp
//
// [EOF]
//
