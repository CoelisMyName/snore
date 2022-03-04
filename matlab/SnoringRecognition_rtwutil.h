#ifndef SNORINGRECOGNITION_RTWUTIL_H
#define SNORINGRECOGNITION_RTWUTIL_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

extern int div_s32_floor(int numerator, int denominator);

extern double rt_atan2d_snf(double u0, double u1);

extern double rt_hypotd_snf(double u0, double u1);

extern double rt_powd_snf(double u0, double u1);

extern double rt_roundd_snf(double u);

#endif
