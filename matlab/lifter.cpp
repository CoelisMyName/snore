//
// File: lifter.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "lifter.h"
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function y = lifter(x, lift, invs)
//
// y = lifter(x, lift, invs)
//    Apply lifter to matrix of cepstra (one per column)
//    lift = exponent of x i^n liftering
//    or, as a negative integer, the length of HTK-style sin-curve liftering.
//    If inverse == 1 (default 0), undo the liftering.
//  2005-05-19 dpwe@ee.columbia.edu
//
// Arguments    : const coder::array<double, 2U> &x
//                coder::array<double, 2U> &y
// Return Type  : void
//
void lifter(const coder::array<double, 2U> &x, coder::array<double, 2U> &y) {
    // 'lifter:9' if nargin < 2
    //  liftering exponent
    // 'lifter:10' if nargin < 3
    // 'lifter:10' invs = 0;
    //  flag to undo liftering
    // 'lifter:12' [ncep, ~] = size(x);
    // 'lifter:14' if lift == 0
    // 'lifter:16' else
    // 'lifter:18' if lift > 0
    // 'lifter:20' if lift > 10
    // 'lifter:24' liftwts = [1, ([1:(ncep - 1)].^lift)];
    // 'lifter:36' if (invs)
    // 'lifter:40' y = diag(liftwts) * x;
    coder::internal::blas::mtimes(x, y);
}

//
// File trailer for lifter.cpp
//
// [EOF]
//
