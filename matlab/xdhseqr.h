#ifndef XDHSEQR_H
#define XDHSEQR_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
namespace reflapack {
int eml_dlahqr(double h_data[], const int h_size[2]);

}
} // namespace internal
} // namespace coder

#endif
