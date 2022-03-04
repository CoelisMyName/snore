#ifndef XZGGEV_H
#define XZGGEV_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace reflapack {
void xzggev(creal_T A_data[], const int A_size[2], int *info,
            creal_T alpha1_data[], int *alpha1_size, creal_T beta1_data[],
            int *beta1_size);

}
} // namespace internal
} // namespace coder

#endif
