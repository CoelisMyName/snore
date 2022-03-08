#include "eml_i64relops.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "mylock.h"

namespace coder {
boolean_T eml_i64relops(long long a, double b)
{
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
