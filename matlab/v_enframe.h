//
// File: v_enframe.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef V_ENFRAME_H
#define V_ENFRAME_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void v_enframe(const coder::array<double, 1U> &x, coder::array<double, 1U> &win,
               double hop, coder::array<double, 2U> &f);

#endif
//
// File trailer for v_enframe.h
//
// [EOF]
//
