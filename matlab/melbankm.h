#ifndef MELBANKM_H
#define MELBANKM_H

#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
class sparse;

}

void melbankm(double n, double fs, coder::sparse *x);

#endif
