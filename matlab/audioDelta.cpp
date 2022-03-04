#include "audioDelta.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

namespace coder {
void audioDelta(const ::coder::array<double, 2U> &x,
                ::coder::array<double, 2U> &delta)
{
    static const double b_dv[9] = {
        0.13333333333333333,   0.1,  0.066666666666666666,
        0.033333333333333333,  0.0,  -0.033333333333333333,
        -0.066666666666666666, -0.1, -0.13333333333333333};
    array<double, 1U> r;
    int nc;
    int nx;
    delta.set_size(x.size(0), x.size(1));
    nx = x.size(0);
    nc = x.size(1) - 1;
    if (x.size(1) >= 2) {
        for (int c = 0; c <= nc; c++) {
            int i;
            int i1;
            int nx_m_nb;
            i = x.size(0);
            r.set_size(x.size(0));
            nx_m_nb = x.size(0);
            for (i1 = 0; i1 < nx_m_nb; i1++) {
                r[i1] = 0.0;
            }
            if (x.size(0) >= 18) {
                for (int k = 0; k < 9; k++) {
                    nx_m_nb = k + 1;
                    for (int j = nx_m_nb; j <= i; j++) {
                        r[j - 1] = r[j - 1] +
                                   b_dv[k] * x[((j - k) + x.size(0) * c) - 1];
                    }
                }
            } else {
                int j;
                int k;
                int naxpy;
                if (x.size(0) > 9) {
                    nx_m_nb = x.size(0) - 10;
                } else {
                    nx_m_nb = -1;
                }
                for (k = 0; k <= nx_m_nb; k++) {
                    for (j = 0; j < 9; j++) {
                        i1 = k + j;
                        r[i1] = r[i1] + x[k + x.size(0) * c] * b_dv[j];
                    }
                }
                naxpy = (x.size(0) - nx_m_nb) - 2;
                i1 = nx_m_nb + 2;
                for (k = i1; k <= i; k++) {
                    for (j = 0; j <= naxpy; j++) {
                        nx_m_nb = (k + j) - 1;
                        r[nx_m_nb] =
                            r[nx_m_nb] + x[(k + x.size(0) * c) - 1] * b_dv[j];
                    }
                    naxpy--;
                }
            }
            nx_m_nb = r.size(0);
            for (i = 0; i < nx_m_nb; i++) {
                delta[i + delta.size(0) * c] = r[i];
            }
        }
    } else {
        int i;
        int nx_m_nb;
        delta.set_size(x.size(0), x.size(1));
        nx_m_nb = x.size(0) * x.size(1);
        for (i = 0; i < nx_m_nb; i++) {
            delta[i] = 0.0;
        }
        for (int c = 0; c <= nc; c++) {
            if (nx >= 18) {
                for (int k = 0; k < 9; k++) {
                    nx_m_nb = k + 1;
                    for (int j = nx_m_nb; j <= nx; j++) {
                        delta[j - 1] = delta[j - 1] + b_dv[k] * x[(j - k) - 1];
                    }
                }
            } else {
                int j;
                int k;
                int naxpy;
                if (nx > 9) {
                    nx_m_nb = nx - 10;
                } else {
                    nx_m_nb = -1;
                }
                for (k = 0; k <= nx_m_nb; k++) {
                    for (j = 0; j < 9; j++) {
                        i = k + j;
                        delta[i] = delta[i] + x[k] * b_dv[j];
                    }
                }
                naxpy = nx - nx_m_nb;
                i = nx_m_nb + 2;
                for (k = i; k <= nx; k++) {
                    for (j = 0; j <= naxpy - 2; j++) {
                        int i1;
                        i1 = (k + j) - 1;
                        delta[i1] = delta[i1] + x[k - 1] * b_dv[j];
                    }
                    naxpy--;
                }
            }
        }
    }
}

} // namespace coder
