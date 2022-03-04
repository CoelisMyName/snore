#ifndef GTCCVALIDATOR_H
#define GTCCVALIDATOR_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace audio {
namespace internal {
class GTCCValidator {
  public:
    double Window[160];
};

class b_GTCCValidator {
  public:
    double Window[221];
};

class c_GTCCValidator {
  public:
    double Window[240];
};

class d_GTCCValidator {
  public:
    double Window[441];
};

class e_GTCCValidator {
  public:
    double Window[480];
};

class f_GTCCValidator {
  public:
    double Window[882];
};

class g_GTCCValidator {
  public:
    double Window[960];
};

} // namespace internal
} // namespace audio
} // namespace coder

#endif
