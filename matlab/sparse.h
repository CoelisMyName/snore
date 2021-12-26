//
// File: sparse.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef SPARSE_H
#define SPARSE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class sparse;

}

// Function Declarations
namespace coder {
void b_sparse(const ::coder::array<double, 2U> &varargin_1,
              const ::coder::array<double, 2U> &varargin_2,
              const ::coder::array<double, 2U> &varargin_3, double varargin_5,
              sparse *y);

}

#endif
//
// File trailer for sparse.h
//
// [EOF]
//
