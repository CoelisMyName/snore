//
// File: levinson.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef LEVINSON_H
#define LEVINSON_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void b_levinson(const ::coder::array<creal_T, 1U> &R, creal_T A_data[],
                    int A_size[2], double E_data[], int E_size[2]);

    void levinson(const ::coder::array<double, 2U> &R,
                  ::coder::array<double, 2U> &A, ::coder::array<double, 1U> &E);

    void levinson(const ::coder::array<creal_T, 1U> &R, creal_T A_data[],
                  int A_size[2], double E_data[], int E_size[2]);

} // namespace coder

#endif
//
// File trailer for levinson.h
//
// [EOF]
//
