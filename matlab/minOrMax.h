#ifndef MINORMAX_H
#define MINORMAX_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
namespace internal {
void maximum(const ::coder::array<double, 2U> &x, double ex_data[],
             int ex_size[2]);

double maximum(const ::coder::array<double, 2U> &x);

double maximum(const ::coder::array<double, 1U> &x);

void minimum(const ::coder::array<double, 2U> &x,
             ::coder::array<double, 2U> &ex);

void minimum(const ::coder::array<double, 2U> &x, double ex_data[],
             int ex_size[2]);

double minimum(const ::coder::array<double, 1U> &x);

double minimum(const ::coder::array<double, 2U> &x);

} // namespace internal
} // namespace coder

#endif
