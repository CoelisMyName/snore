#ifndef PITCH_H
#define PITCH_H

#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

namespace coder {
void b_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0);

void c_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0);

void d_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0);

void e_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0);

void f_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0);

void g_pitch(const ::coder::array<double, 1U> &x,
             ::coder::array<double, 1U> &f0);

void pitch(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &f0);

} // namespace coder

#endif
