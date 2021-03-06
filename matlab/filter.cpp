#include "filter.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"

namespace coder {
void filter(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y)
{
    array<double, 2U> b;
    array<double, 2U> b_y1;
    int i;
    int i1;
    int nx;
    int nx_m_nb;
    b.set_size(x.size(1), 13);
    nx_m_nb = x.size(1);
    for (i = 0; i < 13; i++) {
        for (i1 = 0; i1 < nx_m_nb; i1++) {
            b[i1 + b.size(0) * i] = x[i + 13 * i1];
        }
    }
    nx = b.size(0);
    b_y1.set_size(b.size(0), 13);
    nx_m_nb = b.size(0) * 13;
    for (i = 0; i < nx_m_nb; i++) {
        b_y1[i] = 0.0;
    }
    for (int c = 0; c < 13; c++) {
        int offset;
        offset = c * nx;
        if (nx >= 18) {
            nx_m_nb = offset + nx;
            for (int k = 0; k < 9; k++) {
                int jp;
                jp = (offset + k) + 1;
                for (int j = jp; j <= nx_m_nb; j++) {
                    b_y1[j - 1] =
                        b_y1[j - 1] +
                        (-((static_cast<double>(k) + 1.0) - 1.0) + 4.0) *
                            b[(j - k) - 1];
                }
            }
        } else {
            int j;
            int jp;
            int k;
            int naxpy;
            if (nx > 9) {
                nx_m_nb = nx - 10;
            } else {
                nx_m_nb = -1;
            }
            for (k = 0; k <= nx_m_nb; k++) {
                jp = offset + k;
                for (j = 0; j < 9; j++) {
                    i = jp + j;
                    b_y1[i] =
                        b_y1[i] +
                        b[jp] * (-((static_cast<double>(j) + 1.0) - 1.0) + 4.0);
                }
            }
            naxpy = nx - nx_m_nb;
            i = nx_m_nb + 2;
            for (k = i; k <= nx; k++) {
                jp = (offset + k) - 1;
                for (j = 0; j <= naxpy - 2; j++) {
                    i1 = jp + j;
                    b_y1[i1] =
                        b_y1[i1] + b[jp] * (-static_cast<double>(j) + 4.0);
                }
                naxpy--;
            }
        }
    }
    y.set_size(13, b_y1.size(0));
    nx_m_nb = b_y1.size(0);
    for (i = 0; i < nx_m_nb; i++) {
        for (i1 = 0; i1 < 13; i1++) {
            y[i1 + 13 * i] = b_y1[i + b_y1.size(0) * i1];
        }
    }
}

void filter(double b[3], double a[3], const ::coder::array<double, 1U> &x,
            const double zi[2], ::coder::array<double, 1U> &y, double zf[2])
{
    int j;
    int k;
    int lb;
    int naxpy;
    int niccp;
    int nx;
    int y_tmp;
    if ((!rtIsInf(a[0])) && (!rtIsNaN(a[0])) && (!(a[0] == 0.0)) &&
        (a[0] != 1.0)) {
        b[0] /= a[0];
        b[1] /= a[0];
        b[2] /= a[0];
        a[1] /= a[0];
        a[2] /= a[0];
        a[0] = 1.0;
    }
    y.set_size(x.size(0));
    nx = x.size(0);
    zf[0] = 0.0;
    zf[1] = 0.0;
    if (x.size(0) < 2) {
        niccp = x.size(0) - 1;
    } else {
        niccp = 1;
    }
    for (k = 0; k <= niccp; k++) {
        y[k] = zi[k];
    }
    y_tmp = niccp + 2;
    for (k = y_tmp; k <= nx; k++) {
        y[k - 1] = 0.0;
    }
    for (k = 0; k < nx; k++) {
        double as;
        niccp = nx - k;
        if (niccp < 3) {
            naxpy = niccp;
        } else {
            naxpy = 3;
        }
        for (j = 0; j < naxpy; j++) {
            y_tmp = k + j;
            y[y_tmp] = y[y_tmp] + x[k] * b[j];
        }
        if (niccp - 1 < 2) {
            naxpy = niccp - 2;
        } else {
            naxpy = 1;
        }
        as = -y[k];
        for (j = 0; j <= naxpy; j++) {
            y_tmp = (k + j) + 1;
            y[y_tmp] = y[y_tmp] + as * a[j + 1];
        }
    }
    if (x.size(0) < 2) {
        niccp = 1 - x.size(0);
        for (k = 0; k <= niccp; k++) {
            zf[k] = zi[k + nx];
        }
    }
    if (x.size(0) >= 3) {
        lb = x.size(0) - 2;
    } else {
        lb = 0;
    }
    y_tmp = x.size(0) - 1;
    for (k = lb; k <= y_tmp; k++) {
        niccp = nx - k;
        naxpy = 2 - niccp;
        for (j = 0; j <= naxpy; j++) {
            zf[j] += x[k] * b[niccp + j];
        }
    }
    if (x.size(0) >= 3) {
        lb = x.size(0) - 2;
    } else {
        lb = 0;
    }
    y_tmp = x.size(0) - 1;
    for (k = lb; k <= y_tmp; k++) {
        niccp = nx - k;
        naxpy = 2 - niccp;
        for (j = 0; j <= naxpy; j++) {
            zf[j] += -y[k] * a[niccp + j];
        }
    }
}

} // namespace coder
