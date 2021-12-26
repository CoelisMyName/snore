//
// File: xzlartg.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef XZLARTG_H
#define XZLARTG_H

// Include Files
#include "rtwtypes.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
void xzlartg(const creal_T f, const creal_T g, double *cs, creal_T *sn);

void xzlartg(const creal_T f, const creal_T g, double *cs, creal_T *sn,
             creal_T *r);

} // namespace reflapack
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xzlartg.h
//
// [EOF]
//
