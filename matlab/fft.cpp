//
// File: fft.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
namespace coder {
void b_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(2048, 0);
  } else {
    internal::FFTImplementationCallback::c_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void c_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(2048, 0);
  } else {
    internal::FFTImplementationCallback::e_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void d_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(4096, 0);
  } else {
    internal::FFTImplementationCallback::f_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void e_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(4096, 0);
  } else {
    internal::FFTImplementationCallback::h_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void f_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(8192, 0);
  } else {
    internal::FFTImplementationCallback::i_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(1024, 0);
  } else {
    internal::FFTImplementationCallback::r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
void fft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y)
{
  array<double, 2U> costab;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  int N2blue;
  int nRows;
  if (x.size(0) == 0) {
    y.set_size(0);
  } else {
    boolean_T useRadix2;
    useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
    internal::FFTImplementationCallback::get_algo_sizes(x.size(0), useRadix2,
                                                        &N2blue, &nRows);
    internal::FFTImplementationCallback::generate_twiddle_tables(
        nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          x, x.size(0), costab, sintab, y);
    } else {
      internal::FFTImplementationCallback::dobluesteinfft(
          x, N2blue, x.size(0), costab, sintab, sintabinv, y);
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void g_fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(8192, 0);
  } else {
    internal::FFTImplementationCallback::k_r2br_r2dit_trig(x, y);
  }
}

} // namespace coder

//
// File trailer for fft.cpp
//
// [EOF]
//
