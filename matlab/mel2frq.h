//
// File: mel2frq.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

#ifndef MEL2FRQ_H
#define MEL2FRQ_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct SnoringRecognitionStackData;

// Function Declarations
void mel2frq(SnoringRecognitionStackData *SD, const double mel[4],
             double frq[4]);

void mel2frq_init(SnoringRecognitionStackData *SD);

#endif
//
// File trailer for mel2frq.h
//
// [EOF]
//
