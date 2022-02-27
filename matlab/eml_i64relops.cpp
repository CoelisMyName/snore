//
// File: eml_i64relops.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Feb-2022 11:31:05
//

// Include Files
#include "eml_i64relops.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : long long a
//                double b
// Return Type  : boolean_T
//
namespace coder {
    boolean_T b_eml_i64relops(long long a, double b) {
        boolean_T p;
        p = false;
        if ((-9.2233720368547758E+18 <= b) && (b < 9.2233720368547758E+18)) {
            boolean_T alarge;
            boolean_T asmall;
            boolean_T blarge;
            boolean_T bsmall;
            blarge = (b >= 4.503599627370496E+15);
            alarge = (a >= 4503599627370496LL);
            bsmall = (b <= -4.503599627370496E+15);
            asmall = (a <= -4503599627370496LL);
            if (((!alarge) && blarge) || (asmall && (!bsmall))) {
                p = true;
            } else if (blarge || asmall) {
                p = (a < static_cast<long long>(rt_roundd_snf(b)));
            } else if ((!alarge) && (!bsmall)) {
                p = (a < b);
            }
        } else {
            p = (b >= 0.0);
        }
        return p;
    }

//
// Arguments    : long long a
//                double b
// Return Type  : boolean_T
//
    boolean_T eml_i64relops(long long a, double b) {
        boolean_T p;
        p = false;
        if ((-9.2233720368547758E+18 <= b) && (b < 9.2233720368547758E+18)) {
            boolean_T alarge;
            boolean_T asmall;
            boolean_T blarge;
            boolean_T bsmall;
            alarge = (b >= 4.503599627370496E+15);
            blarge = (a >= 4503599627370496LL);
            asmall = (b <= -4.503599627370496E+15);
            bsmall = (a <= -4503599627370496LL);
            if (((!alarge) && blarge) || (asmall && (!bsmall))) {
                p = true;
            } else if (blarge || asmall) {
                p = (static_cast<long long>(rt_roundd_snf(b)) < a);
            } else if ((!alarge) && (!bsmall)) {
                p = (b < a);
            }
        } else {
            p = (b < 0.0);
        }
        return p;
    }

} // namespace coder

//
// File trailer for eml_i64relops.cpp
//
// [EOF]
//
