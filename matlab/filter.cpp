//
// File: filter.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 22-Feb-2022 23:42:31
//

// Include Files
#include "filter.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace coder {
    void b_filter(const ::coder::array<double, 1U> &x,
                  ::coder::array<double, 1U> &y) {
        int i;
        int nx;
        int nx_m_nb;
        nx = x.size(0);
        y.set_size(x.size(0));
        nx_m_nb = x.size(0);
        for (i = 0; i < nx_m_nb; i++) {
            y[i] = 0.0;
        }
        if (x.size(0) >= 4) {
            for (int k = 0; k < 2; k++) {
                nx_m_nb = k + 1;
                for (int j = nx_m_nb; j <= nx; j++) {
                    y[j - 1] =
                            y[j - 1] + (-1.99 * static_cast<double>(k) + 1.0) * x[(j - k) - 1];
                }
            }
        } else {
            int k;
            int naxpy;
            if (x.size(0) > 2) {
                nx_m_nb = 0;
            } else {
                nx_m_nb = -1;
            }
            for (k = 0; k <= nx_m_nb; k++) {
                y[0] = y[0] + x[0];
                y[1] = y[1] + x[0] * -0.99;
            }
            naxpy = x.size(0) - nx_m_nb;
            i = nx_m_nb + 2;
            for (k = i; k <= nx; k++) {
                for (int j = 0; j <= naxpy - 2; j++) {
                    nx_m_nb = (k + j) - 1;
                    y[nx_m_nb] =
                            y[nx_m_nb] + x[k - 1] * (-1.99 * static_cast<double>(j) + 1.0);
                }
                naxpy--;
            }
        }
    }

//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
    void filter(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &y) {
        int i;
        int nx;
        int nx_m_nb;
        nx = x.size(0);
        y.set_size(x.size(0));
        nx_m_nb = x.size(0);
        for (i = 0; i < nx_m_nb; i++) {
            y[i] = 0.0;
        }
        if (x.size(0) >= 4) {
            for (int k = 0; k < 2; k++) {
                nx_m_nb = k + 1;
                for (int j = nx_m_nb; j <= nx; j++) {
                    y[j - 1] = y[j - 1] +
                               (-1.9375 * static_cast<double>(k) + 1.0) * x[(j - k) - 1];
                }
            }
        } else {
            int k;
            int naxpy;
            if (x.size(0) > 2) {
                nx_m_nb = 0;
            } else {
                nx_m_nb = -1;
            }
            for (k = 0; k <= nx_m_nb; k++) {
                y[0] = y[0] + x[0];
                y[1] = y[1] + x[0] * -0.9375;
            }
            naxpy = x.size(0) - nx_m_nb;
            i = nx_m_nb + 2;
            for (k = i; k <= nx; k++) {
                for (int j = 0; j <= naxpy - 2; j++) {
                    nx_m_nb = (k + j) - 1;
                    y[nx_m_nb] =
                            y[nx_m_nb] + x[k - 1] * (-1.9375 * static_cast<double>(j) + 1.0);
                }
                naxpy--;
            }
        }
    }

//
// Arguments    : const double b[7]
//                const double a[7]
//                const ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
    void filter(const double b[7], const double a[7],
                const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y) {
        array<double, 1U> b_b;
        array<double, 1U> b_y1;
        double b_a[7];
        double c_b[7];
        double a1;
        int k;
        int loop_ub;
        int naxpy;
        int nx;
        b_b.set_size(x.size(1));
        loop_ub = x.size(1);
        for (naxpy = 0; naxpy < loop_ub; naxpy++) {
            b_b[naxpy] = x[naxpy];
        }
        for (naxpy = 0; naxpy < 7; naxpy++) {
            c_b[naxpy] = b[naxpy];
            b_a[naxpy] = a[naxpy];
        }
        a1 = a[0];
        if ((!rtIsInf(a[0])) && (!rtIsNaN(a[0])) && (!(a[0] == 0.0)) &&
            (a[0] != 1.0)) {
            for (k = 0; k < 7; k++) {
                c_b[k] /= a1;
            }
            for (k = 0; k < 6; k++) {
                b_a[k + 1] /= a1;
            }
            b_a[0] = 1.0;
        }
        nx = b_b.size(0) - 1;
        b_y1.set_size(b_b.size(0));
        loop_ub = b_b.size(0);
        for (naxpy = 0; naxpy < loop_ub; naxpy++) {
            b_y1[naxpy] = 0.0;
        }
        for (k = 0; k <= nx; k++) {
            int j;
            int y1_tmp;
            loop_ub = nx - k;
            naxpy = loop_ub + 1;
            if (naxpy >= 7) {
                naxpy = 7;
            }
            for (j = 0; j < naxpy; j++) {
                y1_tmp = k + j;
                b_y1[y1_tmp] = b_y1[y1_tmp] + b_b[k] * c_b[j];
            }
            if (loop_ub < 6) {
                naxpy = loop_ub;
            } else {
                naxpy = 6;
            }
            a1 = -b_y1[k];
            for (j = 0; j < naxpy; j++) {
                y1_tmp = (k + j) + 1;
                b_y1[y1_tmp] = b_y1[y1_tmp] + a1 * b_a[j + 1];
            }
        }
        y.set_size(1, b_y1.size(0));
        loop_ub = b_y1.size(0);
        for (naxpy = 0; naxpy < loop_ub; naxpy++) {
            y[naxpy] = b_y1[naxpy];
        }
    }

} // namespace coder

//
// File trailer for filter.cpp
//
// [EOF]
//
