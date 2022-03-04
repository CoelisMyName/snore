#ifndef XZHSEQR_H
#define XZHSEQR_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace reflapack {
int eml_zlahqr(creal_T h_data[], const int h_size[2]);

}
} // namespace internal
} // namespace coder

#endif
