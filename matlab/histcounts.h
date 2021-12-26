//
// File: histcounts.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef HISTCOUNTS_H
#define HISTCOUNTS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void histcounts(const ::coder::array<double, 2U> &x, double n_data[],
                int n_size[2], double edges_data[], int edges_size[2]);

}

#endif
//
// File trailer for histcounts.h
//
// [EOF]
//
