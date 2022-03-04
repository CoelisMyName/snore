#include "zweight.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "octbank.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

void zweight(const coder::array<double, 1U> &x, double p[8], double f[8],
             double *s)
{
    double a[8];
    double y;
    int k;
    for (k = 0; k < 8; k++) {
        f[k] = iv[k];
    }
    octbank(x, p);
    for (k = 0; k < 8; k++) {
        a[k] = rt_powd_snf(10.0, 0.1 * p[k]);
    }
    y = a[0];
    for (k = 0; k < 7; k++) {
        y += a[k + 1];
    }
    *s = 10.0 * log10(y);
}
