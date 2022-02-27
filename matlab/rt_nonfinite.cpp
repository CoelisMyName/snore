//
// File: rt_nonfinite.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Abstract:
//      MATLAB for code generation function to initialize non-finites,
//      (Inf, NaN and -Inf).
// Include Files
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

// Function: rt_InitInfAndNaN ==================================================
//  Abstract:
//  Initialize the rtInf, rtMinusInf, and rtNaN needed by the
// generated code. NaN is initialized as non-signaling. Assumes IEEE.
void rt_InitInfAndNaN() {
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
}

// Function: rtIsInf ==================================================
//  Abstract:
//  Test if value is infinite
boolean_T rtIsInf(real_T value) {
    return ((value == rtInf || value == rtMinusInf) ? true : false);
}

// Function: rtIsInfF =================================================
//  Abstract:
//  Test if single-precision value is infinite
boolean_T rtIsInfF(real32_T value) {
    return ((value == rtInfF || value == rtMinusInfF) ? true : false);
}

// Function: rtIsNaN ==================================================
//  Abstract:
//  Test if value is not a number
boolean_T rtIsNaN(real_T value) {
    return ((value != value) ? true : false);
}

// Function: rtIsNaNF =================================================
//  Abstract:
//  Test if single-precision value is not a number
boolean_T rtIsNaNF(real32_T value) {
    return ((value != value) ? true : false);
}

//
// File trailer for rt_nonfinite.cpp
//
// [EOF]
//
