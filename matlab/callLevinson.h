#ifndef CALLLEVINSON_H
#define CALLLEVINSON_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace signal {
namespace internal {
namespace levinson {
void callLevinson(const ::coder::array<creal_T, 1U> &R, double N,
                  creal_T A_data[], int A_size[2], double E_data[],
                  int E_size[2], creal_T K_data[], int K_size[2]);

}
} // namespace internal
} // namespace signal
} // namespace coder

#endif
