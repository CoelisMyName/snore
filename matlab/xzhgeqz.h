#ifndef XZHGEQZ_H
#define XZHGEQZ_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace reflapack {
void xzhgeqz(const creal_T A_data[], const int A_size[2], int ilo, int ihi,
             int *info, creal_T alpha1_data[], int *alpha1_size,
             creal_T beta1_data[], int *beta1_size);

void xzhgeqz(const creal_T A[36], int ilo, int ihi, int *info,
             creal_T alpha1[6], creal_T beta1[6]);

} // namespace reflapack
} // namespace internal
} // namespace coder

#endif
