//
// File: xhseqr.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 25-Dec-2021 13:54:41
//

// Include Files
#include "xhseqr.h"
#include "SnoringRecognition_rtwutil.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xnrm2.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : double h[36]
// Return Type  : int
//
namespace coder {
namespace internal {
namespace lapack {
int xhseqr(double h[36])
{
  double v[3];
  double aa;
  double ab;
  double ba;
  double bb;
  double rt1r;
  double rt2r;
  double s;
  double s_tmp;
  double tst;
  int i;
  int info;
  int iy;
  int j;
  boolean_T exitg1;
  info = 0;
  v[0] = 0.0;
  h[2] = 0.0;
  h[3] = 0.0;
  v[1] = 0.0;
  h[9] = 0.0;
  h[10] = 0.0;
  v[2] = 0.0;
  h[16] = 0.0;
  h[17] = 0.0;
  h[23] = 0.0;
  i = 5;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    int L;
    int b_i;
    int hoffset;
    int its;
    int k;
    int knt;
    int nr;
    boolean_T exitg2;
    boolean_T goto150;
    L = 1;
    goto150 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      boolean_T exitg3;
      k = i;
      exitg3 = false;
      while ((!exitg3) && (k + 1 > L)) {
        b_i = k + 6 * (k - 1);
        ba = std::abs(h[b_i]);
        if (ba <= 6.0125050800269183E-292) {
          exitg3 = true;
        } else {
          iy = k + 6 * k;
          bb = std::abs(h[iy]);
          tst = std::abs(h[b_i - 1]) + bb;
          if (tst == 0.0) {
            if (k - 1 >= 1) {
              tst = std::abs(h[(k + 6 * (k - 2)) - 1]);
            }
            if (k + 2 <= 6) {
              tst += std::abs(h[iy + 1]);
            }
          }
          if (ba <= 2.2204460492503131E-16 * tst) {
            tst = std::abs(h[iy - 1]);
            if (ba > tst) {
              ab = ba;
              ba = tst;
            } else {
              ab = tst;
            }
            tst = std::abs(h[b_i - 1] - h[iy]);
            if (bb > tst) {
              aa = bb;
              bb = tst;
            } else {
              aa = tst;
            }
            s = aa + ab;
            if (ba * (ab / s) <=
                std::fmax(6.0125050800269183E-292,
                          2.2204460492503131E-16 * (bb * (aa / s)))) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }
      L = k + 1;
      if (k + 1 > 1) {
        h[k + 6 * (k - 1)] = 0.0;
      }
      if (k + 1 >= i) {
        goto150 = true;
        exitg2 = true;
      } else {
        int m;
        if (its == 10) {
          iy = k + 6 * k;
          s = std::abs(h[iy + 1]) + std::abs(h[(k + 6 * (k + 1)) + 2]);
          tst = 0.75 * s + h[iy];
          aa = -0.4375 * s;
          ab = s;
          bb = tst;
        } else if (its == 20) {
          s = std::abs(h[i + 6 * (i - 1)]) + std::abs(h[(i + 6 * (i - 2)) - 1]);
          tst = 0.75 * s + h[i + 6 * i];
          aa = -0.4375 * s;
          ab = s;
          bb = tst;
        } else {
          iy = i + 6 * (i - 1);
          tst = h[iy - 1];
          ab = h[iy];
          aa = h[(i + 6 * i) - 1];
          bb = h[i + 6 * i];
        }
        s = ((std::abs(tst) + std::abs(aa)) + std::abs(ab)) + std::abs(bb);
        if (s == 0.0) {
          rt1r = 0.0;
          ba = 0.0;
          rt2r = 0.0;
          bb = 0.0;
        } else {
          tst /= s;
          ab /= s;
          aa /= s;
          bb /= s;
          ba = (tst + bb) / 2.0;
          tst = (tst - ba) * (bb - ba) - aa * ab;
          ab = std::sqrt(std::abs(tst));
          if (tst >= 0.0) {
            rt1r = ba * s;
            rt2r = rt1r;
            ba = ab * s;
            bb = -ba;
          } else {
            rt1r = ba + ab;
            rt2r = ba - ab;
            if (std::abs(rt1r - bb) <= std::abs(rt2r - bb)) {
              rt1r *= s;
              rt2r = rt1r;
            } else {
              rt2r *= s;
              rt1r = rt2r;
            }
            ba = 0.0;
            bb = 0.0;
          }
        }
        m = i - 1;
        exitg3 = false;
        while ((!exitg3) && (m >= k + 1)) {
          iy = m + 6 * (m - 1);
          tst = h[iy];
          s_tmp = h[iy - 1];
          ab = s_tmp - rt2r;
          s = (std::abs(ab) + std::abs(bb)) + std::abs(tst);
          aa = tst / s;
          iy = m + 6 * m;
          v[0] = (aa * h[iy - 1] + (s_tmp - rt1r) * (ab / s)) - ba * (bb / s);
          tst = h[iy];
          v[1] = aa * (((s_tmp + tst) - rt1r) - rt2r);
          v[2] = aa * h[iy + 1];
          s = (std::abs(v[0]) + std::abs(v[1])) + std::abs(v[2]);
          v[0] /= s;
          v[1] /= s;
          v[2] /= s;
          if (m == k + 1) {
            exitg3 = true;
          } else {
            b_i = m + 6 * (m - 2);
            if (std::abs(h[b_i - 1]) * (std::abs(v[1]) + std::abs(v[2])) <=
                2.2204460492503131E-16 * std::abs(v[0]) *
                    ((std::abs(h[b_i - 2]) + std::abs(s_tmp)) +
                     std::abs(tst))) {
              exitg3 = true;
            } else {
              m--;
            }
          }
        }
        for (int b_k{m}; b_k <= i; b_k++) {
          nr = (i - b_k) + 2;
          if (3 < nr) {
            nr = 3;
          }
          if (b_k > m) {
            hoffset = (b_k + 6 * (b_k - 2)) - 1;
            for (j = 0; j < nr; j++) {
              v[j] = h[j + hoffset];
            }
          }
          ab = v[0];
          ba = 0.0;
          if (nr > 0) {
            tst = blas::xnrm2(nr - 1, v);
            if (tst != 0.0) {
              aa = rt_hypotd_snf(v[0], tst);
              if (v[0] >= 0.0) {
                aa = -aa;
              }
              if (std::abs(aa) < 1.0020841800044864E-292) {
                knt = -1;
                do {
                  knt++;
                  for (iy = 2; iy <= nr; iy++) {
                    v[iy - 1] *= 9.9792015476736E+291;
                  }
                  aa *= 9.9792015476736E+291;
                  ab *= 9.9792015476736E+291;
                } while (!(std::abs(aa) >= 1.0020841800044864E-292));
                aa = rt_hypotd_snf(ab, blas::xnrm2(nr - 1, v));
                if (ab >= 0.0) {
                  aa = -aa;
                }
                ba = (aa - ab) / aa;
                tst = 1.0 / (ab - aa);
                for (iy = 2; iy <= nr; iy++) {
                  v[iy - 1] *= tst;
                }
                for (iy = 0; iy <= knt; iy++) {
                  aa *= 1.0020841800044864E-292;
                }
                ab = aa;
              } else {
                ba = (aa - v[0]) / aa;
                tst = 1.0 / (v[0] - aa);
                for (iy = 2; iy <= nr; iy++) {
                  v[iy - 1] *= tst;
                }
                ab = aa;
              }
            }
          }
          v[0] = ab;
          if (b_k > m) {
            h[(b_k + 6 * (b_k - 2)) - 1] = ab;
            b_i = b_k + 6 * (b_k - 2);
            h[b_i] = 0.0;
            if (b_k < i) {
              h[b_i + 1] = 0.0;
            }
          } else if (m > k + 1) {
            h[(b_k + 6 * (b_k - 2)) - 1] *= 1.0 - ba;
          }
          s = v[1];
          ab = ba * v[1];
          if (nr == 3) {
            rt1r = v[2];
            tst = ba * v[2];
            for (j = b_k; j < 7; j++) {
              iy = b_k + 6 * (j - 1);
              aa = (h[iy - 1] + s * h[iy]) + rt1r * h[iy + 1];
              h[iy - 1] -= aa * ba;
              h[iy] -= aa * ab;
              h[iy + 1] -= aa * tst;
            }
            if (b_k + 3 < i + 1) {
              b_i = b_k + 2;
            } else {
              b_i = i;
            }
            for (j = 0; j <= b_i; j++) {
              iy = j + 6 * (b_k - 1);
              hoffset = j + 6 * b_k;
              knt = j + 6 * (b_k + 1);
              aa = (h[iy] + s * h[hoffset]) + rt1r * h[knt];
              h[iy] -= aa * ba;
              h[hoffset] -= aa * ab;
              h[knt] -= aa * tst;
            }
          } else if (nr == 2) {
            for (j = b_k; j < 7; j++) {
              iy = b_k + 6 * (j - 1);
              tst = h[iy - 1];
              aa = tst + s * h[iy];
              h[iy - 1] = tst - aa * ba;
              h[iy] -= aa * ab;
            }
            for (j = 0; j <= i; j++) {
              iy = j + 6 * (b_k - 1);
              hoffset = j + 6 * b_k;
              aa = h[iy] + s * h[hoffset];
              h[iy] -= aa * ba;
              h[hoffset] -= aa * ab;
            }
          }
        }
        its++;
      }
    }
    if (!goto150) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((L != i + 1) && (L == i)) {
        b_i = i + 6 * i;
        s = h[b_i - 1];
        nr = 6 * (i - 1);
        iy = i + nr;
        rt1r = h[iy];
        tst = h[b_i];
        reflapack::xdlanv2(&h[(i + 6 * (i - 1)) - 1], &s, &rt1r, &tst, &ab, &aa,
                           &ba, &bb, &s_tmp, &rt2r);
        h[b_i - 1] = s;
        h[iy] = rt1r;
        h[b_i] = tst;
        if (6 > i + 1) {
          iy = 4 - i;
          hoffset = i + (i + 1) * 6;
          for (k = 0; k <= iy; k++) {
            knt = hoffset + k * 6;
            tst = h[knt];
            ab = h[knt - 1];
            h[knt] = s_tmp * tst - rt2r * ab;
            h[knt - 1] = s_tmp * ab + rt2r * tst;
          }
        }
        if (i - 1 >= 1) {
          iy = i * 6;
          for (k = 0; k <= i - 2; k++) {
            hoffset = iy + k;
            knt = nr + k;
            tst = s_tmp * h[knt] + rt2r * h[hoffset];
            h[hoffset] = s_tmp * h[hoffset] - rt2r * h[knt];
            h[knt] = tst;
          }
        }
      }
      i = L - 2;
    }
  }
  iy = 4;
  for (j = 0; j < 3; j++) {
    if (iy <= 6) {
      std::memset(&h[(j * 6 + iy) + -1], 0, (7 - iy) * sizeof(double));
    }
    iy++;
  }
  return info;
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xhseqr.cpp
//
// [EOF]
//
