//
// File: SnoringRecognition_types.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

#ifndef SNORINGRECOGNITION_TYPES_H
#define SNORINGRECOGNITION_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct b_struct_T {
    double mu[4160];
    double sigm[4160];
    double c[32];
};

struct SnoringRecognitionStackData {
    struct {
        double win[40320];
        double z[40320];
    } f0;
    struct {
        double win[36162];
        double z[36162];
    } f1;
    struct {
        double win[17280];
    } f2;
    struct {
        double win[15435];
    } f3;
    struct {
        b_struct_T s[2];
        b_struct_T b_s[2];
    } f4;
};

#endif
//
// File trailer for SnoringRecognition_types.h
//
// [EOF]
//
