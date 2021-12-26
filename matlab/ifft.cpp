//
// File: ifft.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "SnoringRecognition_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
namespace coder {
void b_ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(2048, 0);
  } else {
    internal::FFTImplementationCallback::d_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void c_ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(4096, 0);
  } else {
    internal::FFTImplementationCallback::g_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void d_ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(8192, 0);
  } else {
    internal::FFTImplementationCallback::j_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void ifft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
{
  if (x.size(1) == 0) {
    y.set_size(1024, 0);
  } else {
    internal::FFTImplementationCallback::b_r2br_r2dit_trig(x, y);
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
void ifft(const ::coder::array<double, 1U> &x, ::coder::array<creal_T, 1U> &y)
{
  array<creal_T, 1U> b_fv;
  array<creal_T, 1U> fv;
  array<creal_T, 1U> wwc;
  array<double, 2U> costab;
  array<double, 2U> costab1q;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  creal_T nt;
  double b_ai;
  double im;
  int N2blue;
  int k;
  int nd2;
  int nfft;
  nfft = x.size(0);
  if (x.size(0) == 0) {
    y.set_size(0);
  } else {
    double e;
    int i;
    int nInt2m1;
    int rt;
    boolean_T useRadix2;
    useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
    internal::FFTImplementationCallback::get_algo_sizes(x.size(0), useRadix2,
                                                        &N2blue, &nd2);
    e = 6.2831853071795862 / static_cast<double>(nd2);
    nInt2m1 = nd2 / 2 / 2;
    costab1q.set_size(1, nInt2m1 + 1);
    costab1q[0] = 1.0;
    nd2 = nInt2m1 / 2 - 1;
    if (static_cast<int>(nd2 + 1 < 1200)) {
      for (k = 0; k <= nd2; k++) {
        costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = 0; k <= nd2; k++) {
        costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
      }
    }
    i = nd2 + 2;
    rt = nInt2m1 - 1;
    if (static_cast<int>((nInt2m1 - nd2) - 2 < 1200)) {
      for (k = i; k <= rt; k++) {
        costab1q[k] = std::sin(e * static_cast<double>(nInt2m1 - k));
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

      for (k = i; k <= rt; k++) {
        costab1q[k] = std::sin(e * static_cast<double>(nInt2m1 - k));
      }
    }
    costab1q[nInt2m1] = 0.0;
    if (!useRadix2) {
      double ai;
      nInt2m1 = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, nd2 + 1);
      if (static_cast<int>(costab1q.size(1) - 1 < 1200)) {
        for (k = 0; k < nInt2m1; k++) {
          sintabinv[k + 1] = costab1q[(nInt2m1 - k) - 1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

        for (k = 0; k < nInt2m1; k++) {
          sintabinv[k + 1] = costab1q[(nInt2m1 - k) - 1];
        }
      }
      i = costab1q.size(1);
      if (static_cast<int>((nd2 - costab1q.size(1)) + 1 < 1200)) {
        for (k = i; k <= nd2; k++) {
          sintabinv[k] = costab1q[k - nInt2m1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

        for (k = i; k <= nd2; k++) {
          sintabinv[k] = costab1q[k - nInt2m1];
        }
      }
      if (static_cast<int>(nInt2m1 < 1200)) {
        for (k = 0; k < nInt2m1; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(nInt2m1 - k) - 1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

        for (k = 0; k < nInt2m1; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(nInt2m1 - k) - 1];
        }
      }
      i = costab1q.size(1);
      if (static_cast<int>((nd2 - costab1q.size(1)) + 1 < 1200)) {
        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - nInt2m1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - nInt2m1];
        }
      }
      if ((x.size(0) != 1) && ((x.size(0) & 1) == 0)) {
        int b_k;
        int nInt2;
        nd2 = x.size(0) / 2;
        nInt2m1 = (nd2 + nd2) - 1;
        wwc.set_size(nInt2m1);
        rt = 0;
        wwc[nd2 - 1].re = 1.0;
        wwc[nd2 - 1].im = 0.0;
        nInt2 = nd2 << 1;
        for (b_k = 0; b_k <= nd2 - 2; b_k++) {
          int b_y;
          b_y = ((b_k + 1) << 1) - 1;
          if (nInt2 - rt <= b_y) {
            rt += b_y - nInt2;
          } else {
            rt += b_y;
          }
          nt.im = 3.1415926535897931 * static_cast<double>(rt) /
                  static_cast<double>(nd2);
          if (nt.im == 0.0) {
            nt.re = 1.0;
            nt.im = 0.0;
          } else {
            e = nt.im;
            ai = nt.im;
            nt.re = std::cos(e);
            nt.im = std::sin(ai);
          }
          i = (nd2 - b_k) - 2;
          wwc[i].re = nt.re;
          wwc[i].im = -nt.im;
        }
        i = nInt2m1 - 1;
        for (b_k = i; b_k >= nd2; b_k--) {
          wwc[b_k] = wwc[(nInt2m1 - b_k) - 1];
        }
      } else {
        int b_k;
        int nInt2;
        nInt2m1 = (x.size(0) + x.size(0)) - 1;
        wwc.set_size(nInt2m1);
        rt = 0;
        wwc[x.size(0) - 1].re = 1.0;
        wwc[x.size(0) - 1].im = 0.0;
        nInt2 = x.size(0) << 1;
        i = x.size(0);
        for (b_k = 0; b_k <= i - 2; b_k++) {
          int b_y;
          b_y = ((b_k + 1) << 1) - 1;
          if (nInt2 - rt <= b_y) {
            rt += b_y - nInt2;
          } else {
            rt += b_y;
          }
          nt.im = 3.1415926535897931 * static_cast<double>(rt) /
                  static_cast<double>(nfft);
          if (nt.im == 0.0) {
            nt.re = 1.0;
            nt.im = 0.0;
          } else {
            e = nt.im;
            ai = nt.im;
            nt.re = std::cos(e);
            nt.im = std::sin(ai);
          }
          wwc[(x.size(0) - b_k) - 2].re = nt.re;
          wwc[(x.size(0) - b_k) - 2].im = -nt.im;
        }
        i = nInt2m1 - 1;
        for (b_k = i; b_k >= nfft; b_k--) {
          wwc[b_k] = wwc[(nInt2m1 - b_k) - 1];
        }
      }
      y.set_size(x.size(0));
      if ((N2blue != 1) && ((x.size(0) & 1) == 0)) {
        internal::FFTImplementationCallback::b_doHalfLengthBluestein(
            x, y, x.size(0), x.size(0), N2blue, wwc, costab, sintab, costab,
            sintabinv);
      } else {
        nd2 = x.size(0);
        if (static_cast<int>(x.size(0) < 1200)) {
          for (k = 0; k < nd2; k++) {
            nt = wwc[(nfft + k) - 1];
            y[k].re = nt.re * x[k];
            y[k].im = nt.im * -x[k];
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(nt, k)

          for (k = 0; k < nd2; k++) {
            nt = wwc[(nfft + k) - 1];
            y[k].re = nt.re * x[k];
            y[k].im = nt.im * -x[k];
          }
        }
        i = x.size(0) + 1;
        if (static_cast<int>(nfft - x.size(0) < 1200)) {
          for (k = i; k <= nfft; k++) {
            y[k - 1].re = 0.0;
            y[k - 1].im = 0.0;
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

          for (k = i; k <= nfft; k++) {
            y[k - 1].re = 0.0;
            y[k - 1].im = 0.0;
          }
        }
        internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
            y, N2blue, costab, sintab, fv);
        internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
            wwc, N2blue, costab, sintab, b_fv);
        b_fv.set_size(fv.size(0));
        nd2 = fv.size(0);
        if (static_cast<int>(fv.size(0) < 1200)) {
          for (k = 0; k < nd2; k++) {
            e = fv[k].re * b_fv[k].im + fv[k].im * b_fv[k].re;
            b_fv[k].re = fv[k].re * b_fv[k].re - fv[k].im * b_fv[k].im;
            b_fv[k].im = e;
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k, im)

          for (k = 0; k < nd2; k++) {
            im = fv[k].re * b_fv[k].im + fv[k].im * b_fv[k].re;
            b_fv[k].re = fv[k].re * b_fv[k].re - fv[k].im * b_fv[k].im;
            b_fv[k].im = im;
          }
        }
        internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
            b_fv, N2blue, costab, sintabinv, fv);
        if (fv.size(0) > 1) {
          e = 1.0 / static_cast<double>(fv.size(0));
          nd2 = fv.size(0);
          if (static_cast<int>(fv.size(0) < 1200)) {
            for (k = 0; k < nd2; k++) {
              fv[k].re = e * fv[k].re;
              fv[k].im = e * fv[k].im;
            }
          } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

            for (k = 0; k < nd2; k++) {
              fv[k].re = e * fv[k].re;
              fv[k].im = e * fv[k].im;
            }
          }
        }
        i = x.size(0);
        rt = wwc.size(0);
        if (static_cast<int>((wwc.size(0) - x.size(0)) + 1 < 1200)) {
          for (k = i; k <= rt; k++) {
            e = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].im;
            ai = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].re;
            if (ai == 0.0) {
              nd2 = k - i;
              y[nd2].re = e / static_cast<double>(nfft);
              y[nd2].im = 0.0;
            } else if (e == 0.0) {
              nd2 = k - i;
              y[nd2].re = 0.0;
              y[nd2].im = ai / static_cast<double>(nfft);
            } else {
              nd2 = k - i;
              y[nd2].re = e / static_cast<double>(nfft);
              y[nd2].im = ai / static_cast<double>(nfft);
            }
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(nt, k, im, \
                                                                    b_ai)

          for (k = i; k <= rt; k++) {
            im = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].im;
            b_ai = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].re;
            if (b_ai == 0.0) {
              nt.re = im / static_cast<double>(nfft);
              nt.im = 0.0;
            } else if (im == 0.0) {
              nt.re = 0.0;
              nt.im = b_ai / static_cast<double>(nfft);
            } else {
              nt.re = im / static_cast<double>(nfft);
              nt.im = b_ai / static_cast<double>(nfft);
            }
            y[k - i] = nt;
          }
        }
      }
    } else {
      nInt2m1 = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      if (static_cast<int>(costab1q.size(1) - 1 < 1200)) {
        for (k = 0; k < nInt2m1; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = costab1q[(nInt2m1 - k) - 1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

        for (k = 0; k < nInt2m1; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = costab1q[(nInt2m1 - k) - 1];
        }
      }
      i = costab1q.size(1);
      if (static_cast<int>((nd2 - costab1q.size(1)) + 1 < 1200)) {
        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = costab1q[k - nInt2m1];
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = costab1q[k - nInt2m1];
        }
      }
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          x, x.size(0), costab, sintab, y);
      if (y.size(0) > 1) {
        e = 1.0 / static_cast<double>(y.size(0));
        nd2 = y.size(0);
        if (static_cast<int>(y.size(0) < 1200)) {
          for (k = 0; k < nd2; k++) {
            y[k].re = e * y[k].re;
            y[k].im = e * y[k].im;
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k)

          for (k = 0; k < nd2; k++) {
            y[k].re = e * y[k].re;
            y[k].im = e * y[k].im;
          }
        }
      }
    }
  }
}

} // namespace coder

//
// File trailer for ifft.cpp
//
// [EOF]
//
