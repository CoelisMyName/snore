#include "deltas.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

void deltas(const coder::array<double, 2U> &x, coder::array<double, 2U> &d)
{
    coder::array<double, 2U> b;
    coder::array<double, 2U> b_d;
    coder::array<double, 2U> b_y1;
    coder::array<double, 2U> y;
    double b_b[26];
    double c_b[26];
    if (x.size(1) == 0) {
        d.set_size(13, 0);
    } else {
        int i;
        int jp;
        int k;
        int naxpy;
        int nx;
        int nx_m_nb;
        for (nx_m_nb = 0; nx_m_nb < 2; nx_m_nb++) {
            jp = nx_m_nb * 13;
            for (k = 0; k < 13; k++) {
                naxpy = jp + k;
                b_b[naxpy] = x[k];
                c_b[naxpy] = x[k + 13 * (x.size(1) - 1)];
            }
        }
        b.set_size(x.size(1) + 4, 13);
        jp = x.size(1);
        for (i = 0; i < 13; i++) {
            b[b.size(0) * i] = b_b[i];
            b[b.size(0) * i + 1] = b_b[i + 13];
            for (nx_m_nb = 0; nx_m_nb < jp; nx_m_nb++) {
                b[(nx_m_nb + b.size(0) * i) + 2] = x[i + 13 * nx_m_nb];
            }
            b[(x.size(1) + b.size(0) * i) + 2] = c_b[i];
            b[(x.size(1) + b.size(0) * i) + 3] = c_b[i + 13];
        }
        nx = b.size(0);
        b_y1.set_size(b.size(0), 13);
        jp = b.size(0) * 13;
        for (i = 0; i < jp; i++) {
            b_y1[i] = 0.0;
        }
        for (int c = 0; c < 13; c++) {
            int offset;
            offset = c * nx;
            if (nx >= 10) {
                jp = offset + nx;
                for (k = 0; k < 5; k++) {
                    naxpy = (offset + k) + 1;
                    for (int j = naxpy; j <= jp; j++) {
                        b_y1[j - 1] =
                            b_y1[j - 1] +
                            (-((static_cast<double>(k) + 1.0) - 1.0) + 2.0) *
                                b[(j - k) - 1];
                    }
                }
            } else {
                int j;
                if (nx > 5) {
                    nx_m_nb = nx - 6;
                } else {
                    nx_m_nb = -1;
                }
                for (k = 0; k <= nx_m_nb; k++) {
                    jp = offset + k;
                    for (j = 0; j < 5; j++) {
                        i = jp + j;
                        b_y1[i] =
                            b_y1[i] +
                            b[jp] *
                                (-((static_cast<double>(j) + 1.0) - 1.0) + 2.0);
                    }
                }
                naxpy = nx - nx_m_nb;
                i = nx_m_nb + 2;
                for (k = i; k <= nx; k++) {
                    jp = (offset + k) - 1;
                    for (j = 0; j <= naxpy - 2; j++) {
                        nx_m_nb = jp + j;
                        b_y1[nx_m_nb] = b_y1[nx_m_nb] +
                                        b[jp] * (-static_cast<double>(j) + 2.0);
                    }
                    naxpy--;
                }
            }
        }
        d.set_size(13, b_y1.size(0));
        jp = b_y1.size(0);
        for (i = 0; i < jp; i++) {
            for (nx_m_nb = 0; nx_m_nb < 13; nx_m_nb++) {
                d[nx_m_nb + 13 * i] = b_y1[i + b_y1.size(0) * nx_m_nb];
            }
        }
        y.set_size(1, x.size(1));
        jp = x.size(1) - 1;
        for (i = 0; i <= jp; i++) {
            y[i] = static_cast<double>(i) + 1.0;
        }
        b_d.set_size(13, y.size(1));
        jp = y.size(1);
        for (i = 0; i < jp; i++) {
            for (nx_m_nb = 0; nx_m_nb < 13; nx_m_nb++) {
                b_d[nx_m_nb + 13 * i] =
                    d[nx_m_nb + 13 * (static_cast<int>(y[i]) + 3)];
            }
        }
        d.set_size(13, b_d.size(1));
        jp = 13 * b_d.size(1);
        for (i = 0; i < jp; i++) {
            d[i] = b_d[i];
        }
    }
}
