#include "bark_feat.h"
#include "BARKenergy.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"

void bark_feat(const coder::array<double, 1U> &sig, double fs,
               double barkee[17])
{
    double a__1[17];
    double a__2[17];
    BARKenergy(sig, fs, barkee, a__1, a__2);
}
