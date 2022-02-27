//
// File: var.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef VAR_H
#define VAR_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void var(const ::coder::array<double, 2U> &x, double y_data[], int y_size[2]);

    void var(const ::coder::array<double, 2U> &x, double y[12]);

    double var(const ::coder::array<double, 2U> &x);

    double var(const ::coder::array<double, 1U> &x);

} // namespace coder

#endif
//
// File trailer for var.h
//
// [EOF]
//
