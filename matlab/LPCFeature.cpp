#include "LPCFeature.h"
#include "SnoringRecognition_data.h"
#include "SnoringRecognition_rtwutil.h"
#include "callLevinson.h"
#include "enframe.h"
#include "fft.h"
#include "hamming.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "vvarstd.h"
#include "coder_array.h"
#include "mylock.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

void LPCFeature(const coder::array<double, 1U> &x, double Fs,
                coder::array<double, 2U> &LPC, double LPC_mean[12],
                double LPC_max[12], double LPC_min[12], double LPC_var[12])
{
    coder::array<creal_T, 1U> R;
    coder::array<creal_T, 1U> X;
    coder::array<double, 2U> b_LPC;
    coder::array<double, 2U> c_LPC;
    coder::array<double, 2U> r;
    coder::array<double, 2U> y;
    coder::array<double, 1U> c_y;
    coder::array<double, 1U> xv;
    coder::array<double, 1U> z_new;
    creal_T K_data[13];
    creal_T a_data[13];
    double b_y[12];
    double bsum;
    double inc;
    double re;
    double wlen;
    int K_size[2];
    int a_size[2];
    int tempE_size[2];
    int b_i;
    int hi;
    int i;
    int k;
    int lastBlockLength;
    int naxpy;
    int nx_m_nb;
    int xblockoffset;
    int xpageoffset;
    wlen = 0.02 * Fs;
    if (wlen < 0.0) {
        wlen = ceil(wlen);
    } else {
        wlen = floor(wlen);
    }
    inc = 0.5 * wlen;
    if (inc < 0.0) {
        inc = ceil(inc);
    } else {
        inc = floor(inc);
    }
    coder::hamming(wlen, xv);
    enframe(x, xv, inc, r);
    y.set_size(r.size(1), r.size(0));
    naxpy = r.size(0);
    for (i = 0; i < naxpy; i++) {
        nx_m_nb = r.size(1);
        for (hi = 0; hi < nx_m_nb; hi++) {
            y[hi + y.size(0) * i] = r[i + r.size(0) * hi];
        }
    }
    b_LPC.set_size(13, y.size(1));
    naxpy = 13 * y.size(1);
    for (i = 0; i < naxpy; i++) {
        b_LPC[i] = 0.0;
    }
    i = y.size(1);
    for (b_i = 0; b_i < i; b_i++) {
        hi = y.size(0);
        z_new.set_size(y.size(0));
        naxpy = y.size(0);
        for (xpageoffset = 0; xpageoffset < naxpy; xpageoffset++) {
            z_new[xpageoffset] = 0.0;
        }
        if (y.size(0) >= 4) {
            for (k = 0; k < 2; k++) {
                nx_m_nb = k + 1;
                for (xblockoffset = nx_m_nb; xblockoffset <= hi;
                     xblockoffset++) {
                    z_new[xblockoffset - 1] =
                        z_new[xblockoffset - 1] +
                        (-1.99 * static_cast<double>(k) + 1.0) *
                            y[((xblockoffset - k) + y.size(0) * b_i) - 1];
                }
            }
        } else {
            if (y.size(0) > 2) {
                nx_m_nb = 0;
            } else {
                nx_m_nb = -1;
            }
            for (k = 0; k <= nx_m_nb; k++) {
                z_new[0] = z_new[0] + y[y.size(0) * b_i];
                z_new[1] = z_new[1] + y[y.size(0) * b_i] * -0.99;
            }
            naxpy = (y.size(0) - nx_m_nb) - 2;
            xpageoffset = nx_m_nb + 2;
            for (k = xpageoffset; k <= hi; k++) {
                for (xblockoffset = 0; xblockoffset <= naxpy; xblockoffset++) {
                    nx_m_nb = (k + xblockoffset) - 1;
                    z_new[nx_m_nb] =
                        z_new[nx_m_nb] +
                        y[(k + y.size(0) * b_i) - 1] *
                            (-1.99 * static_cast<double>(xblockoffset) + 1.0);
                }
                naxpy--;
            }
        }
        bsum = frexp(static_cast<double>(static_cast<unsigned int>(
                         fabs(2.0 * static_cast<double>(z_new.size(0)) - 1.0))),
                     &lastBlockLength);
        nx_m_nb = lastBlockLength;
        if (bsum == 0.5) {
            nx_m_nb = lastBlockLength - 1;
        }
        coder::fft(z_new, rt_powd_snf(2.0, static_cast<double>(nx_m_nb)), X);
        nx_m_nb = X.size(0);
        xv.set_size(X.size(0));
        for (k = 0; k < nx_m_nb; k++) {
            xv[k] = rt_hypotd_snf(X[k].re, X[k].im);
        }
        c_y.set_size(xv.size(0));
        nx_m_nb = xv.size(0);
        for (k = 0; k < nx_m_nb; k++) {
            c_y[k] = xv[k] * xv[k];
        }
        coder::ifft(c_y, R);
        nx_m_nb = z_new.size(0);
        naxpy = R.size(0);
        for (hi = 0; hi < naxpy; hi++) {
            double ai;
            bsum = R[hi].re;
            ai = R[hi].im;
            if (ai == 0.0) {
                re = bsum / static_cast<double>(nx_m_nb);
                bsum = 0.0;
            } else if (bsum == 0.0) {
                re = 0.0;
                bsum = ai / static_cast<double>(nx_m_nb);
            } else {
                re = bsum / static_cast<double>(nx_m_nb);
                bsum = ai / static_cast<double>(nx_m_nb);
            }
            R[hi].re = re;
            R[hi].im = bsum;
        }
        nx_m_nb = 12;
        if ((12 == R.size(0)) || (12 > R.size(0))) {
            nx_m_nb = R.size(0) - 1;
        }
        coder::signal::internal::levinson::callLevinson(
            R, static_cast<double>(nx_m_nb), a_data, a_size, (double *)&bsum,
            tempE_size, K_data, K_size);
        for (hi = 0; hi < 13; hi++) {
            b_LPC[hi + 13 * b_i] = a_data[hi].re;
        }
    }
    c_LPC.set_size(b_LPC.size(1), 13);
    naxpy = b_LPC.size(1);
    for (i = 0; i < 13; i++) {
        for (hi = 0; hi < naxpy; hi++) {
            c_LPC[hi + c_LPC.size(0) * i] = b_LPC[i + 13 * hi];
        }
    }
    naxpy = c_LPC.size(0);
    LPC.set_size(c_LPC.size(0), 12);
    for (i = 0; i < 12; i++) {
        for (hi = 0; hi < naxpy; hi++) {
            LPC[hi + LPC.size(0) * i] = c_LPC[hi + c_LPC.size(0) * (i + 1)];
        }
    }
    if (c_LPC.size(0) == 0) {
        memset(&b_y[0], 0, 12U * sizeof(double));
    } else {
        if (c_LPC.size(0) <= 1024) {
            nx_m_nb = c_LPC.size(0);
            lastBlockLength = 0;
            naxpy = 1;
        } else {
            nx_m_nb = 1024;
            naxpy = c_LPC.size(0) / 1024;
            lastBlockLength = c_LPC.size(0) - (naxpy << 10);
            if (lastBlockLength > 0) {
                naxpy++;
            } else {
                lastBlockLength = 1024;
            }
        }
        for (int xi = 0; xi < 12; xi++) {
            xpageoffset = xi * c_LPC.size(0);
            b_y[xi] = c_LPC[xpageoffset % c_LPC.size(0) +
                            c_LPC.size(0) * (xpageoffset / c_LPC.size(0) + 1)];
            for (k = 2; k <= nx_m_nb; k++) {
                i = (xpageoffset + k) - 1;
                b_y[xi] += c_LPC[i % c_LPC.size(0) +
                                 c_LPC.size(0) * (i / c_LPC.size(0) + 1)];
            }
            for (int ib = 2; ib <= naxpy; ib++) {
                xblockoffset = xpageoffset + ((ib - 1) << 10);
                bsum =
                    c_LPC[xblockoffset % c_LPC.size(0) +
                          c_LPC.size(0) * (xblockoffset / c_LPC.size(0) + 1)];
                if (ib == naxpy) {
                    hi = lastBlockLength;
                } else {
                    hi = 1024;
                }
                for (k = 2; k <= hi; k++) {
                    i = (xblockoffset + k) - 1;
                    bsum += c_LPC[i % c_LPC.size(0) +
                                  c_LPC.size(0) * (i / c_LPC.size(0) + 1)];
                }
                b_y[xi] += bsum;
            }
        }
    }
    i = c_LPC.size(0);
    hi = c_LPC.size(0);
    xpageoffset = c_LPC.size(0);
    naxpy = c_LPC.size(0);
    for (xblockoffset = 0; xblockoffset < 12; xblockoffset++) {
        boolean_T p;
        LPC_mean[xblockoffset] =
            b_y[xblockoffset] / static_cast<double>(c_LPC.size(0));
        bsum = c_LPC[c_LPC.size(0) * (xblockoffset + 1)];
        LPC_max[xblockoffset] = bsum;
        for (b_i = 2; b_i <= i; b_i++) {
            re = c_LPC[(b_i + c_LPC.size(0) * (xblockoffset + 1)) - 1];
            if (rtIsNaN(re)) {
                p = false;
            } else if (rtIsNaN(LPC_max[xblockoffset])) {
                p = true;
            } else {
                p = (LPC_max[xblockoffset] < re);
            }
            if (p) {
                LPC_max[xblockoffset] = re;
            }
        }
        LPC_min[xblockoffset] = bsum;
        for (b_i = 2; b_i <= hi; b_i++) {
            re = c_LPC[(b_i + c_LPC.size(0) * (xblockoffset + 1)) - 1];
            if (rtIsNaN(re)) {
                p = false;
            } else if (rtIsNaN(LPC_min[xblockoffset])) {
                p = true;
            } else {
                p = (LPC_min[xblockoffset] > re);
            }
            if (p) {
                LPC_min[xblockoffset] = re;
            }
        }
        nx_m_nb = xblockoffset * xpageoffset;
        xv.set_size(xpageoffset);
        for (lastBlockLength = 0; lastBlockLength < naxpy; lastBlockLength++) {
            xv[lastBlockLength] = 0.0;
        }
        for (k = 0; k < xpageoffset; k++) {
            lastBlockLength = nx_m_nb + k;
            xv[k] =
                c_LPC[lastBlockLength % c_LPC.size(0) +
                      c_LPC.size(0) * (lastBlockLength / c_LPC.size(0) + 1)];
        }
        LPC_var[xblockoffset] = coder::vvarstd(xv, c_LPC.size(0));
    }
}
