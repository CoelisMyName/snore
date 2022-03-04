
#include "rtGetNaN.h"
#include "rt_nonfinite.h"

real_T rtGetNaN(void)
{
    real_T nan = 0.0;
    uint16_T one = 1U;
    enum
    {
        LittleEndian,
        BigEndian
    } machByteOrder = (*((uint8_T *)&one) == 1U) ? LittleEndian : BigEndian;
    switch (machByteOrder) {
    case LittleEndian: {
        union {
            LittleEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.bitVal.words.wordH = 0xFFF80000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        nan = tmpVal.fltVal;
        break;
    }
    case BigEndian: {
        union {
            BigEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.bitVal.words.wordH = 0x7FFFFFFFU;
        tmpVal.bitVal.words.wordL = 0xFFFFFFFFU;
        nan = tmpVal.fltVal;
        break;
    }
    }
    return nan;
}

real32_T rtGetNaNF(void)
{
    IEEESingle nanF = {{0}};
    uint16_T one = 1U;
    enum
    {
        LittleEndian,
        BigEndian
    } machByteOrder = (*((uint8_T *)&one) == 1U) ? LittleEndian : BigEndian;
    switch (machByteOrder) {
    case LittleEndian: {
        nanF.wordL.wordLuint = 0xFFC00000U;
        break;
    }

    case BigEndian: {
        nanF.wordL.wordLuint = 0x7FFFFFFFU;
        break;
    }
    }

    return nanF.wordL.wordLreal;
}
