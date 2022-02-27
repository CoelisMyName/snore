//
// File: repmat.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef REPMAT_H
#define REPMAT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
    void b_repmat(const double a[13], double b[26]);

    void b_repmat(const ::coder::array<double, 2U> &a,
                  ::coder::array<double, 2U> &b);

    void repmat(const ::coder::array<double, 1U> &a, double varargin_2,
                ::coder::array<double, 2U> &b);

    void repmat(const ::coder::array<double, 2U> &a, ::coder::array<double, 2U> &b);

    void repmat(const ::coder::array<double, 2U> &a, double varargin_1,
                ::coder::array<double, 2U> &b);

    void repmat(const double a[13], double b[52]);

    void repmat(const ::coder::array<double, 2U> &a, ::coder::array<double, 3U> &b);

    void repmat(const double a[32], const double varargin_1[2],
                ::coder::array<double, 2U> &b);

    void repmat(const double a[4160], const double varargin_1[3],
                ::coder::array<double, 3U> &b);

} // namespace coder

#endif
//
// File trailer for repmat.h
//
// [EOF]
//
