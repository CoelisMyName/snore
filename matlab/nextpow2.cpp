//
// File: nextpow2.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "nextpow2.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double n
// Return Type  : double
//
namespace coder {
    double nextpow2(double n) {
        double p;
        int eint;
        p = fabs(n);
        if ((!rtIsInf(p)) && (!rtIsNaN(p))) {
            double f;
            f = frexp(p, &eint);
            p = eint;
            if (f == 0.5) {
                p = static_cast<double>(eint) - 1.0;
            }
        }
        return p;
    }

//
// Arguments    : int n
// Return Type  : int
//
    int nextpow2(int n) {
        int b_n;
        int p;
        int pmax;
        b_n = n;
        pmax = 31;
        if (n > MIN_int32_T) {
            if (n < 0) {
                b_n = -n;
            }
            if (b_n <= 1) {
                pmax = 0;
            } else {
                int pmin;
                boolean_T exitg1;
                pmin = 0;
                exitg1 = false;
                while ((!exitg1) && (pmax - pmin > 1)) {
                    int pow2p;
                    p = (pmin + pmax) >> 1;
                    pow2p = 1 << p;
                    if (pow2p == b_n) {
                        pmax = p;
                        exitg1 = true;
                    } else if (pow2p > b_n) {
                        pmax = p;
                    } else {
                        pmin = p;
                    }
                }
            }
        }
        return pmax;
    }

} // namespace coder

//
// File trailer for nextpow2.cpp
//
// [EOF]
//
