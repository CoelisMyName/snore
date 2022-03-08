#include "aweight.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "octbank.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include <math.h>

void aweight(const coder::array<double, 1U> &x, double p[8], double f[8],
             double *s)
{
    static const double weight[8] = {-26.2, -16.1, -8.6, -3.2,
                                     0.0,   1.2,   1.0,  -1.1};
    double a[8];
    double y;
    int k;
    for (k = 0; k < 8; k++) {
        f[k] = iv[k];
    }
    octbank(x, p);
    for (k = 0; k < 8; k++) {
        y = p[k] + weight[k];
        p[k] = y;
        a[k] = rt_powd_snf(10.0, 0.1 * y);
    }
    y = a[0];
    for (k = 0; k < 7; k++) {
        y += a[k + 1];
    }
    *s = 10.0 * log10(y);
}
