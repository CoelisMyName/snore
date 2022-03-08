#ifndef STANDALONEFFTW3INTERFACE_H
#define STANDALONEFFTW3INTERFACE_H

#include "rtwtypes.h"
#include "fftw3.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace fftw {
class StandaloneFFTW3Interface {
  public:
    static void fftwCleanUpThreads();
};

} // namespace fftw
} // namespace coder

#endif
