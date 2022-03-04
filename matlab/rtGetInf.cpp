
#include "rtGetInf.h"
#include "rt_nonfinite.h"

real_T rtGetInf(void)
{
    real_T inf = 0.0;
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

        tmpVal.bitVal.words.wordH = 0x7FF00000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        inf = tmpVal.fltVal;
        break;
    }
    case BigEndian: {
        union {
            BigEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.bitVal.words.wordH = 0x7FF00000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        inf = tmpVal.fltVal;
        break;
    }
    }
    return inf;
}

real32_T rtGetInfF(void)
{
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
}

real_T rtGetMinusInf(void)
{
    real_T minf = 0.0;
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

        tmpVal.bitVal.words.wordH = 0xFFF00000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        minf = tmpVal.fltVal;
        break;
    }
    case BigEndian: {
        union {
            BigEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.bitVal.words.wordH = 0xFFF00000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        minf = tmpVal.fltVal;
        break;
    }
    }
    return minf;
}

real32_T rtGetMinusInfF(void)
{
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
}
