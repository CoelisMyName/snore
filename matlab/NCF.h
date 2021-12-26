//
// File: NCF.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef NCF_H
#define NCF_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace audio {
namespace internal {
namespace pitch {
void NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0);

void b_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0);

void c_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0);

void d_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0);

void e_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0);

void f_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0);

void g_NCF(const ::coder::array<double, 2U> &y, ::coder::array<double, 1U> &f0);

} // namespace pitch
} // namespace internal
} // namespace audio
} // namespace coder

#endif
//
// File trailer for NCF.h
//
// [EOF]
//
