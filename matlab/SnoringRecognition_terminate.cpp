#include "SnoringRecognition_terminate.h"
#include "StandaloneFFTW3Interface.h"
#include "rt_nonfinite.h"
#include "mylock.h"

static void customAtExit();

static void customAtExit()
{
    coder::fftw::StandaloneFFTW3Interface::fftwCleanUpThreads();
}

void SnoringRecognition_terminate()
{
    customAtExit();
}
