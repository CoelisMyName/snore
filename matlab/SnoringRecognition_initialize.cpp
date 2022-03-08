#include "SnoringRecognition_initialize.h"
#include "rt_nonfinite.h"
#include "mylock.h"

void SnoringRecognition_initialize()
{
    rt_InitInfAndNaN();
    {
        mylock_initialize();
    }
}
