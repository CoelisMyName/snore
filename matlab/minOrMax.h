//
// File: minOrMax.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef MINORMAX_H
#define MINORMAX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void maximum(const ::coder::array<double, 2U> &x, double ex_data[],
             int ex_size[2]);

double maximum(const ::coder::array<double, 1U> &x);

double maximum(const ::coder::array<double, 2U> &x);

void minimum(const ::coder::array<double, 2U> &x, double ex_data[],
             int ex_size[2]);

double minimum(const ::coder::array<double, 2U> &x);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for minOrMax.h
//
// [EOF]
//
