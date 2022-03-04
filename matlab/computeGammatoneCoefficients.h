#ifndef COMPUTEGAMMATONECOEFFICIENTS_H
#define COMPUTEGAMMATONECOEFFICIENTS_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace audio {
namespace internal {
void b_computeGammatoneCoefficients(double fs, const double cf[29],
                                    double coeffs[696]);

void c_computeGammatoneCoefficients(double fs, const double cf[35],
                                    double coeffs[840]);

void computeGammatoneCoefficients(double fs, const double cf[26],
                                  double coeffs[624]);

void d_computeGammatoneCoefficients(double fs, const double cf[36],
                                    double coeffs[864]);

void e_computeGammatoneCoefficients(double fs, const double cf[41],
                                    double coeffs[984]);

void f_computeGammatoneCoefficients(double fs, const double cf[42],
                                    double coeffs[1008]);

} // namespace internal
} // namespace audio
} // namespace coder

#endif
