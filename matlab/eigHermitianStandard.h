#ifndef EIGHERMITIANSTANDARD_H
#define EIGHERMITIANSTANDARD_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void eigHermitianStandard(const creal_T A_data[], const int A_size[2],
                          creal_T V_data[], int *V_size);

void eigHermitianStandard(const double A_data[], const int A_size[2],
                          double V_data[], int *V_size);

} // namespace coder

#endif
