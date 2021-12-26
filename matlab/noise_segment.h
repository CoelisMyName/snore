//
// File: noise_segment.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef NOISE_SEGMENT_H
#define NOISE_SEGMENT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void noise_segment(const coder::array<double, 2U> &w_starts,
                          const coder::array<double, 2U> &w_ends, double fs,
                          double min_gap, double margin, double *n_start,
                          double *n_length);

#endif
//
// File trailer for noise_segment.h
//
// [EOF]
//
