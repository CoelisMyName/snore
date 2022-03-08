#include "StandaloneFFTW3Interface.h"
#include "rt_nonfinite.h"
#include "fftw3.h"
#include "mylock.h"

namespace coder {
namespace fftw {
void StandaloneFFTW3Interface::fftwCleanUpThreads()
{
    fftw_cleanup_threads();
}

} // namespace fftw
} // namespace coder
