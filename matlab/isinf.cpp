//
// File: isinf.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "isinf.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : double x
// Return Type  : boolean_T
//
namespace coder {
    boolean_T b_isinf(double x) {
        return rtIsInf(x);
    }

} // namespace coder

//
// File trailer for isinf.cpp
//
// [EOF]
//
