#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "mylock.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <math.h>

int div_s32_floor(int numerator, int denominator)
{
    int quotient;
    if (denominator == 0) {
        if (numerator >= 0) {
            quotient = MAX_int32_T;
        } else {
            quotient = MIN_int32_T;
        }
    } else {
        unsigned int absDenominator;
        unsigned int absNumerator;
        unsigned int tempAbsQuotient;
        boolean_T quotientNeedsNegation;
        if (numerator < 0) {
            absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
        } else {
            absNumerator = static_cast<unsigned int>(numerator);
        }
        if (denominator < 0) {
            absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
        } else {
            absDenominator = static_cast<unsigned int>(denominator);
        }
        quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
        tempAbsQuotient = absNumerator / absDenominator;
        if (quotientNeedsNegation) {
            absNumerator %= absDenominator;
            if (absNumerator > 0U) {
                tempAbsQuotient++;
            }
            quotient = -static_cast<int>(tempAbsQuotient);
        } else {
            quotient = static_cast<int>(tempAbsQuotient);
        }
    }
    return quotient;
}

double rt_atan2d_snf(double u0, double u1)
{
    double y;
    if (rtIsNaN(u0) || rtIsNaN(u1)) {
        y = rtNaN;
    } else if (rtIsInf(u0) && rtIsInf(u1)) {
        int b_u0;
        int b_u1;
        if (u0 > 0.0) {
            b_u0 = 1;
        } else {
            b_u0 = -1;
        }
        if (u1 > 0.0) {
            b_u1 = 1;
        } else {
            b_u1 = -1;
        }
        y = atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
    } else if (u1 == 0.0) {
        if (u0 > 0.0) {
            y = RT_PI / 2.0;
        } else if (u0 < 0.0) {
            y = -(RT_PI / 2.0);
        } else {
            y = 0.0;
        }
    } else {
        y = atan2(u0, u1);
    }
    return y;
}

double rt_hypotd_snf(double u0, double u1)
{
    double a;
    double y;
    a = fabs(u0);
    y = fabs(u1);
    if (a < y) {
        a /= y;
        y *= sqrt(a * a + 1.0);
    } else if (a > y) {
        y /= a;
        y = a * sqrt(y * y + 1.0);
    } else if (!rtIsNaN(y)) {
        y = a * 1.4142135623730951;
    }
    return y;
}

double rt_powd_snf(double u0, double u1)
{
    double y;
    if (rtIsNaN(u0) || rtIsNaN(u1)) {
        y = rtNaN;
    } else {
        double d;
        double d1;
        d = fabs(u0);
        d1 = fabs(u1);
        if (rtIsInf(u1)) {
            if (d == 1.0) {
                y = 1.0;
            } else if (d > 1.0) {
                if (u1 > 0.0) {
                    y = rtInf;
                } else {
                    y = 0.0;
                }
            } else if (u1 > 0.0) {
                y = 0.0;
            } else {
                y = rtInf;
            }
        } else if (d1 == 0.0) {
            y = 1.0;
        } else if (d1 == 1.0) {
            if (u1 > 0.0) {
                y = u0;
            } else {
                y = 1.0 / u0;
            }
        } else if (u1 == 2.0) {
            y = u0 * u0;
        } else if ((u1 == 0.5) && (u0 >= 0.0)) {
            y = sqrt(u0);
        } else if ((u0 < 0.0) && (u1 > floor(u1))) {
            y = rtNaN;
        } else {
            y = pow(u0, u1);
        }
    }
    return y;
}

double rt_roundd_snf(double u)
{
    double y;
    if (fabs(u) < 4.503599627370496E+15) {
        if (u >= 0.5) {
            y = floor(u + 0.5);
        } else if (u > -0.5) {
            y = u * 0.0;
        } else {
            y = ceil(u - 0.5);
        }
    } else {
        y = u;
    }
    return y;
}
