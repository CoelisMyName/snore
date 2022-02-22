//
// File: xdlanv2.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "xdlanv2.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double *a
//                double *b
//                double *c
//                double *d
//                double *rt1r
//                double *rt1i
//                double *rt2r
//                double *rt2i
//                double *cs
//                double *sn
// Return Type  : void
//
namespace coder {
    namespace internal {
        namespace reflapack {
            void xdlanv2(double *a, double *b, double *c, double *d, double *rt1r,
                         double *rt1i, double *rt2r, double *rt2i, double *cs, double *sn) {
                if (*c == 0.0) {
                    *cs = 1.0;
                    *sn = 0.0;
                } else if (*b == 0.0) {
                    double z;
                    *cs = 0.0;
                    *sn = 1.0;
                    z = *d;
                    *d = *a;
                    *a = z;
                    *b = -*c;
                    *c = 0.0;
                } else {
                    double tau;
                    tau = *a - *d;
                    if ((tau == 0.0) && ((*b < 0.0) != (*c < 0.0))) {
                        *cs = 1.0;
                        *sn = 0.0;
                    } else {
                        double bcmax;
                        double bcmis;
                        double p;
                        double scale;
                        double z;
                        int b_b;
                        int b_c;
                        p = 0.5 * tau;
                        scale = fabs(*b);
                        bcmis = fabs(*c);
                        if ((scale > bcmis) || rtIsNaN(bcmis)) {
                            bcmax = scale;
                        } else {
                            bcmax = bcmis;
                        }
                        if ((scale < bcmis) || rtIsNaN(bcmis)) {
                            bcmis = scale;
                        }
                        if (!(*b < 0.0)) {
                            b_b = 1;
                        } else {
                            b_b = -1;
                        }
                        if (!(*c < 0.0)) {
                            b_c = 1;
                        } else {
                            b_c = -1;
                        }
                        bcmis = bcmis * static_cast<double>(b_b) * static_cast<double>(b_c);
                        scale = fabs(p);
                        if ((!(scale > bcmax)) && (!rtIsNaN(bcmax))) {
                            scale = bcmax;
                        }
                        z = p / scale * p + bcmax / scale * bcmis;
                        if (z >= 8.8817841970012523E-16) {
                            *a = sqrt(scale) * sqrt(z);
                            if (p < 0.0) {
                                *a = -*a;
                            }
                            z = p + *a;
                            *a = *d + z;
                            *d -= bcmax / z * bcmis;
                            tau = rt_hypotd_snf(*c, z);
                            *cs = z / tau;
                            *sn = *c / tau;
                            *b -= *c;
                            *c = 0.0;
                        } else {
                            scale = *b + *c;
                            tau = rt_hypotd_snf(scale, tau);
                            *cs = sqrt(0.5 * (fabs(scale) / tau + 1.0));
                            if (!(scale < 0.0)) {
                                b_b = 1;
                            } else {
                                b_b = -1;
                            }
                            *sn = -(p / (tau * *cs)) * static_cast<double>(b_b);
                            bcmax = *a * *cs + *b * *sn;
                            bcmis = -*a * *sn + *b * *cs;
                            z = *c * *cs + *d * *sn;
                            scale = -*c * *sn + *d * *cs;
                            *b = bcmis * *cs + scale * *sn;
                            *c = -bcmax * *sn + z * *cs;
                            z = 0.5 * ((bcmax * *cs + z * *sn) + (-bcmis * *sn + scale * *cs));
                            *a = z;
                            *d = z;
                            if (*c != 0.0) {
                                if (*b != 0.0) {
                                    if ((*b < 0.0) == (*c < 0.0)) {
                                        scale = sqrt(fabs(*b));
                                        bcmis = sqrt(fabs(*c));
                                        *a = scale * bcmis;
                                        if (!(*c < 0.0)) {
                                            p = *a;
                                        } else {
                                            p = -*a;
                                        }
                                        tau = 1.0 / sqrt(fabs(*b + *c));
                                        *a = z + p;
                                        *d = z - p;
                                        *b -= *c;
                                        *c = 0.0;
                                        bcmax = scale * tau;
                                        scale = bcmis * tau;
                                        z = *cs * bcmax - *sn * scale;
                                        *sn = *cs * scale + *sn * bcmax;
                                        *cs = z;
                                    }
                                } else {
                                    *b = -*c;
                                    *c = 0.0;
                                    z = *cs;
                                    *cs = -*sn;
                                    *sn = z;
                                }
                            }
                        }
                    }
                }
                *rt1r = *a;
                *rt2r = *d;
                if (*c == 0.0) {
                    *rt1i = 0.0;
                    *rt2i = 0.0;
                } else {
                    *rt1i = sqrt(fabs(*b)) * sqrt(fabs(*c));
                    *rt2i = -*rt1i;
                }
            }

        } // namespace reflapack
    } // namespace internal
} // namespace coder

//
// File trailer for xdlanv2.cpp
//
// [EOF]
//
