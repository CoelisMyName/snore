//
// File: bark2hz.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "bark2hz.h"
#include "rt_nonfinite.h"
#include "sinh.h"
#include "coder_array.h"

// Function Definitions
//
// function hz = bark2hz(z)
//
// BARK2HZ         Converts frequencies Bark to Hertz (Hz)
//  function hz=bark2hz(z)
//          Traunmueller-formula    for    z >  2 Bark
//          linear mapping          for    z <= 2 Bark
//
//  Author:   Kyrill, Oct. 1996
//                  Kyrill, March 1997   (linear mapping added)
//
//
// Arguments    : const coder::array<double, 2U> &z
//                coder::array<double, 2U> &hz
// Return Type  : void
//
void bark2hz(const coder::array<double, 2U> &z, coder::array<double, 2U> &hz) {
    coder::array<double, 2U> r;
    int i;
    int loop_ub;
    // hz_gt_2 = 1960 .* (z + 0.53) ./ (26.28 - z);
    // hz_le_2 = z .* 102.9;
    //
    // hz = (z>2) .* hz_gt_2 + (z<=2) .* hz_le_2;
    //  Hynek's formula (2003-04-11 dpwe@ee.columbia.edu)
    //  (taken from rasta/audspec.c)
    // 'bark2hz:18' hz = 600 * sinh(z / 6);
    r.set_size(1, z.size(1));
    loop_ub = z.size(1);
    for (i = 0; i < loop_ub; i++) {
        r[i] = z[i] / 6.0;
    }
    coder::b_sinh(r);
    hz.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
        hz[i] = 600.0 * r[i];
    }
}

//
// File trailer for bark2hz.cpp
//
// [EOF]
//
