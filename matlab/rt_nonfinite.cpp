
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

void rt_InitInfAndNaN()
{
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
}

boolean_T rtIsInf(real_T value)
{
    return ((value == rtInf || value == rtMinusInf) ? true : false);
}

boolean_T rtIsInfF(real32_T value)
{
    return ((value == rtInfF || value == rtMinusInfF) ? true : false);
}

boolean_T rtIsNaN(real_T value)
{
    return ((value != value) ? true : false);
}

boolean_T rtIsNaNF(real32_T value)
{
    return ((value != value) ? true : false);
}
