#include "pr800_feat.h"
#include "PR800.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

void pr800_feat(const coder::array<double, 1U> &sig, double fs,
                double *PR800_mean, double *PR800_max, double *PR800_min,
                double *PR800_var)
{
    PR800(sig, fs, PR800_mean, PR800_max, PR800_min, PR800_var);
}
