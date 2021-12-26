//
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
class FFTImplementationCallback {
public:
  static void get_algo_sizes(int nfft, boolean_T useRadix2, int *n2blue,
                             int *nRows);
  static void r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                              ::coder::array<creal_T, 2U> &y);
  static void b_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void c_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void d_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void e_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void f_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void g_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void h_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void i_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void j_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void k_r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                                ::coder::array<creal_T, 2U> &y);
  static void generate_twiddle_tables(int nRows, boolean_T useRadix2,
                                      ::coder::array<double, 2U> &costab,
                                      ::coder::array<double, 2U> &sintab,
                                      ::coder::array<double, 2U> &sintabinv);
  static void r2br_r2dit_trig_impl(const ::coder::array<double, 1U> &x,
                                   int unsigned_nRows,
                                   const ::coder::array<double, 2U> &costab,
                                   const ::coder::array<double, 2U> &sintab,
                                   ::coder::array<creal_T, 1U> &y);
  static void dobluesteinfft(const ::coder::array<double, 1U> &x, int n2blue,
                             int nfft, const ::coder::array<double, 2U> &costab,
                             const ::coder::array<double, 2U> &sintab,
                             const ::coder::array<double, 2U> &sintabinv,
                             ::coder::array<creal_T, 1U> &y);
  static void r2br_r2dit_trig_impl(const ::coder::array<creal_T, 1U> &x,
                                   int unsigned_nRows,
                                   const ::coder::array<double, 2U> &costab,
                                   const ::coder::array<double, 2U> &sintab,
                                   ::coder::array<creal_T, 1U> &y);
  static void r2br_r2dit_trig(const ::coder::array<double, 2U> &x,
                              int n1_unsigned,
                              const ::coder::array<double, 2U> &costab,
                              const ::coder::array<double, 2U> &sintab,
                              ::coder::array<creal_T, 2U> &y);
  static void dobluesteinfft(const ::coder::array<double, 2U> &x, int n2blue,
                             int nfft, const ::coder::array<double, 2U> &costab,
                             const ::coder::array<double, 2U> &sintab,
                             const ::coder::array<double, 2U> &sintabinv,
                             ::coder::array<creal_T, 2U> &y);
  static void
  b_doHalfLengthBluestein(const ::coder::array<double, 1U> &x,
                          ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows,
                          int nfft, const ::coder::array<creal_T, 1U> &wwc,
                          const ::coder::array<double, 2U> &costab,
                          const ::coder::array<double, 2U> &sintab,
                          const ::coder::array<double, 2U> &costabinv,
                          const ::coder::array<double, 2U> &sintabinv);

protected:
  static void get_bitrevIndex(int bitrevIndex[4096]);
  static void get_bitrevIndex(int nRowsM1, int nfftLen,
                              ::coder::array<int, 1U> &bitrevIndex);
  static void b_generate_twiddle_tables(int nRows,
                                        ::coder::array<double, 2U> &costab,
                                        ::coder::array<double, 2U> &sintab,
                                        ::coder::array<double, 2U> &sintabinv);
  static void
  get_half_twiddle_tables(const ::coder::array<double, 2U> &costab,
                          const ::coder::array<double, 2U> &sintab,
                          const ::coder::array<double, 2U> &costabinv,
                          const ::coder::array<double, 2U> &sintabinv,
                          ::coder::array<double, 2U> &hcostab,
                          ::coder::array<double, 2U> &hsintab,
                          ::coder::array<double, 2U> &hcostabinv,
                          ::coder::array<double, 2U> &hsintabinv);
  static void doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                 int xoffInit, creal_T y[1024]);
  static void getback_radix2_fft(creal_T y[1024], const creal_T reconVar1[512],
                                 const creal_T reconVar2[512],
                                 const int wrapIndex[512]);
  static void b_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[1024]);
  static void c_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[2048]);
  static void b_getback_radix2_fft(creal_T y[2048],
                                   const creal_T reconVar1[1024],
                                   const creal_T reconVar2[1024],
                                   const int wrapIndex[1024]);
  static void d_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[2048]);
  static void e_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[2048]);
  static void f_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[4096]);
  static void c_getback_radix2_fft(creal_T y[4096],
                                   const creal_T reconVar1[2048],
                                   const creal_T reconVar2[2048],
                                   const int wrapIndex[2048]);
  static void g_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[4096]);
  static void h_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[4096]);
  static void i_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[8192]);
  static void d_getback_radix2_fft(creal_T y[8192],
                                   const creal_T reconVar1[4096],
                                   const creal_T reconVar2[4096],
                                   const int wrapIndex[4096]);
  static void j_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[8192]);
  static void k_doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                   int xoffInit, creal_T y[8192]);
  static void doHalfLengthRadix2(const ::coder::array<double, 1U> &x,
                                 ::coder::array<creal_T, 1U> &y,
                                 int unsigned_nRows,
                                 const ::coder::array<double, 2U> &costab,
                                 const ::coder::array<double, 2U> &sintab);
  static void getback_radix2_fft(::coder::array<creal_T, 1U> &y,
                                 const ::coder::array<creal_T, 1U> &reconVar1,
                                 const ::coder::array<creal_T, 1U> &reconVar2,
                                 const ::coder::array<int, 2U> &wrapIndex,
                                 int hnRows);
  static void
  doHalfLengthBluestein(const ::coder::array<double, 1U> &x,
                        ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows,
                        int nfft, const ::coder::array<creal_T, 1U> &wwc,
                        const ::coder::array<double, 2U> &costab,
                        const ::coder::array<double, 2U> &sintab,
                        const ::coder::array<double, 2U> &costabinv,
                        const ::coder::array<double, 2U> &sintabinv);
  static void doHalfLengthRadix2(const ::coder::array<double, 2U> &x,
                                 int xoffInit, ::coder::array<creal_T, 1U> &y,
                                 int unsigned_nRows,
                                 const ::coder::array<double, 2U> &costab,
                                 const ::coder::array<double, 2U> &sintab);
  static void
  doHalfLengthBluestein(const ::coder::array<double, 2U> &x, int xoffInit,
                        ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows,
                        int nfft, const ::coder::array<creal_T, 1U> &wwc,
                        const ::coder::array<double, 2U> &costab,
                        const ::coder::array<double, 2U> &sintab,
                        const ::coder::array<double, 2U> &costabinv,
                        const ::coder::array<double, 2U> &sintabinv);
};

} // namespace internal
} // namespace coder

#endif
//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
