//
// File: lmultigauss.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef LMULTIGAUSS_H
#define LMULTIGAUSS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void lmultigauss(const coder::array<double, 2U> &x, const double mus[4160],
                 const double sigm[4160], const double c[32],
                 coder::array<double, 2U> &YM, coder::array<double, 1U> &Y);

#endif
//
// File trailer for lmultigauss.h
//
// [EOF]
//
