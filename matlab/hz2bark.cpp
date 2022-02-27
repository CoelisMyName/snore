//
// File: hz2bark.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "hz2bark.h"
#include "asinh.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// function z = hz2bark(f)
//
// HZ2BARK         Converts frequencies Hertz (Hz) to Bark
//  function z= hz2bark(f)
//  Uses
//          Traunmueller-formula    for    f >  200 Hz
//          linear mapping          for    f <= 200 Hz
//
//  Author:   Kyrill, Oct. 1996
//                  Kyrill, March 1997   (linear mapping added)
//
//
// Arguments    : const coder::array<double, 2U> &f
//                coder::array<double, 2U> &z
// Return Type  : void
//
void hz2bark(const coder::array<double, 2U> &f, coder::array<double, 2U> &z) {
    coder::array<double, 2U> r;
    int i;
    int loop_ub;
    // z_gt_200 = 26.81 .* f ./ (1960 + f) - 0.53;
    // z_le_200 = f ./ 102.9;
    //
    // z = (f>200) .* z_gt_200 + (f<=200) .* z_le_200;
    //  Inverse of Hynek's formula (see bark2hz)
    // 'hz2bark:18' z = 6 * asinh(f / 600);
    r.set_size(1, f.size(1));
    loop_ub = f.size(1);
    for (i = 0; i < loop_ub; i++) {
        r[i] = f[i] / 600.0;
    }
    coder::b_asinh(r);
    z.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
        z[i] = 6.0 * r[i];
    }
    //  Formula used in rasta/rasta.h
    // z = 6 * log(f/600 + sqrt(1+ ((f/600).^2)));
    //  They are the same!
}

//
// function z = hz2bark(f)
//
// HZ2BARK         Converts frequencies Hertz (Hz) to Bark
//  function z= hz2bark(f)
//  Uses
//          Traunmueller-formula    for    f >  200 Hz
//          linear mapping          for    f <= 200 Hz
//
//  Author:   Kyrill, Oct. 1996
//                  Kyrill, March 1997   (linear mapping added)
//
//
// Arguments    : double f
// Return Type  : double
//
double hz2bark(double f) {
    double d;
    // z_gt_200 = 26.81 .* f ./ (1960 + f) - 0.53;
    // z_le_200 = f ./ 102.9;
    //
    // z = (f>200) .* z_gt_200 + (f<=200) .* z_le_200;
    //  Inverse of Hynek's formula (see bark2hz)
    // 'hz2bark:18' z = 6 * asinh(f / 600);
    d = f / 600.0;
    coder::b_asinh(&d);
    return 6.0 * d;
    //  Formula used in rasta/rasta.h
    // z = 6 * log(f/600 + sqrt(1+ ((f/600).^2)));
    //  They are the same!
}

//
// File trailer for hz2bark.cpp
//
// [EOF]
//
