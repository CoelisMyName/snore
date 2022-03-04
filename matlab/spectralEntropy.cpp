#include "spectralEntropy.h"
#include "log2.h"
#include "rt_nonfinite.h"
#include "stft.h"
#include "coder_array.h"
#include "rt_nonfinite.h"

namespace coder {
void b_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy)
{
    array<double, 2U> X;
    array<double, 2U> b_X;
    array<double, 2U> e;
    array<double, 2U> r;
    int k;
    int npages;
    int xi;
    int xoffset;
    int xpageoffset;
    audio::internal::spectralDescriptors::b_stft(x, X);
    if (X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = X.size(1);
        e.set_size(1, X.size(1));
        for (xi = 0; xi < npages; xi++) {
            double d;
            xpageoffset = xi * 111;
            d = X[xpageoffset];
            for (k = 0; k < 110; k++) {
                d += X[(xpageoffset + k) + 1];
            }
            e[xi] = d;
        }
    }
    r.set_size(111, e.size(1));
    npages = e.size(1);
    for (xoffset = 0; xoffset < npages; xoffset++) {
        xpageoffset = xoffset * 111;
        for (xi = 0; xi < 111; xi++) {
            r[xpageoffset + xi] = e[xoffset];
        }
    }
    npages = 111 * X.size(1);
    X.set_size(111, X.size(1));
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        X[xpageoffset] = X[xpageoffset] / r[xpageoffset];
    }
    npages = 111 * X.size(1);
    r.set_size(111, X.size(1));
    for (k = 0; k < npages; k++) {
        r[k] = internal::scalar::b_log2(X[k]);
    }
    b_X.set_size(111, X.size(1));
    npages = 111 * X.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        b_X[xpageoffset] = X[xpageoffset] * r[xpageoffset];
    }
    if (b_X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = b_X.size(1);
        e.set_size(1, b_X.size(1));
        for (xi = 0; xi < npages; xi++) {
            xpageoffset = xi * 111;
            if (rtIsNaN(b_X[xpageoffset])) {
                e[xi] = 0.0;
            } else {
                e[xi] = b_X[xpageoffset];
            }
            for (k = 0; k < 110; k++) {
                xoffset = (xpageoffset + k) + 1;
                if (!rtIsNaN(b_X[xoffset])) {
                    e[xi] = e[xi] + b_X[xoffset];
                }
            }
        }
    }
    e.set_size(1, e.size(1));
    npages = e.size(1) - 1;
    for (xpageoffset = 0; xpageoffset <= npages; xpageoffset++) {
        e[xpageoffset] = -e[xpageoffset] / 6.7944158663501062;
    }
    entropy.set_size(e.size(1));
    npages = e.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        entropy[xpageoffset] = e[xpageoffset];
    }
}

void c_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy)
{
    array<double, 2U> X;
    array<double, 2U> b_X;
    array<double, 2U> e;
    array<double, 2U> r;
    int k;
    int npages;
    int xi;
    int xoffset;
    int xpageoffset;
    audio::internal::spectralDescriptors::c_stft(x, X);
    if (X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = X.size(1);
        e.set_size(1, X.size(1));
        for (xi = 0; xi < npages; xi++) {
            double d;
            xpageoffset = xi * 121;
            d = X[xpageoffset];
            for (k = 0; k < 120; k++) {
                d += X[(xpageoffset + k) + 1];
            }
            e[xi] = d;
        }
    }
    r.set_size(121, e.size(1));
    npages = e.size(1);
    for (xoffset = 0; xoffset < npages; xoffset++) {
        xpageoffset = xoffset * 121;
        for (xi = 0; xi < 121; xi++) {
            r[xpageoffset + xi] = e[xoffset];
        }
    }
    npages = 121 * X.size(1);
    X.set_size(121, X.size(1));
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        X[xpageoffset] = X[xpageoffset] / r[xpageoffset];
    }
    npages = 121 * X.size(1);
    r.set_size(121, X.size(1));
    for (k = 0; k < npages; k++) {
        r[k] = internal::scalar::b_log2(X[k]);
    }
    b_X.set_size(121, X.size(1));
    npages = 121 * X.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        b_X[xpageoffset] = X[xpageoffset] * r[xpageoffset];
    }
    if (b_X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = b_X.size(1);
        e.set_size(1, b_X.size(1));
        for (xi = 0; xi < npages; xi++) {
            xpageoffset = xi * 121;
            if (rtIsNaN(b_X[xpageoffset])) {
                e[xi] = 0.0;
            } else {
                e[xi] = b_X[xpageoffset];
            }
            for (k = 0; k < 120; k++) {
                xoffset = (xpageoffset + k) + 1;
                if (!rtIsNaN(b_X[xoffset])) {
                    e[xi] = e[xi] + b_X[xoffset];
                }
            }
        }
    }
    e.set_size(1, e.size(1));
    npages = e.size(1) - 1;
    for (xpageoffset = 0; xpageoffset <= npages; xpageoffset++) {
        e[xpageoffset] = -e[xpageoffset] / 6.9188632372745946;
    }
    entropy.set_size(e.size(1));
    npages = e.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        entropy[xpageoffset] = e[xpageoffset];
    }
}

void d_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy)
{
    array<double, 2U> X;
    array<double, 2U> b_X;
    array<double, 2U> e;
    array<double, 2U> r;
    int k;
    int npages;
    int xi;
    int xoffset;
    int xpageoffset;
    audio::internal::spectralDescriptors::d_stft(x, X);
    if (X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = X.size(1);
        e.set_size(1, X.size(1));
        for (xi = 0; xi < npages; xi++) {
            double d;
            xpageoffset = xi * 221;
            d = X[xpageoffset];
            for (k = 0; k < 220; k++) {
                d += X[(xpageoffset + k) + 1];
            }
            e[xi] = d;
        }
    }
    r.set_size(221, e.size(1));
    npages = e.size(1);
    for (xoffset = 0; xoffset < npages; xoffset++) {
        xpageoffset = xoffset * 221;
        for (xi = 0; xi < 221; xi++) {
            r[xpageoffset + xi] = e[xoffset];
        }
    }
    npages = 221 * X.size(1);
    X.set_size(221, X.size(1));
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        X[xpageoffset] = X[xpageoffset] / r[xpageoffset];
    }
    npages = 221 * X.size(1);
    r.set_size(221, X.size(1));
    for (k = 0; k < npages; k++) {
        r[k] = internal::scalar::b_log2(X[k]);
    }
    b_X.set_size(221, X.size(1));
    npages = 221 * X.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        b_X[xpageoffset] = X[xpageoffset] * r[xpageoffset];
    }
    if (b_X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = b_X.size(1);
        e.set_size(1, b_X.size(1));
        for (xi = 0; xi < npages; xi++) {
            xpageoffset = xi * 221;
            if (rtIsNaN(b_X[xpageoffset])) {
                e[xi] = 0.0;
            } else {
                e[xi] = b_X[xpageoffset];
            }
            for (k = 0; k < 220; k++) {
                xoffset = (xpageoffset + k) + 1;
                if (!rtIsNaN(b_X[xoffset])) {
                    e[xi] = e[xi] + b_X[xoffset];
                }
            }
        }
    }
    e.set_size(1, e.size(1));
    npages = e.size(1) - 1;
    for (xpageoffset = 0; xpageoffset <= npages; xpageoffset++) {
        e[xpageoffset] = -e[xpageoffset] / 7.7879025593914317;
    }
    entropy.set_size(e.size(1));
    npages = e.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        entropy[xpageoffset] = e[xpageoffset];
    }
}

void e_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy)
{
    array<double, 2U> X;
    array<double, 2U> b_X;
    array<double, 2U> e;
    array<double, 2U> r;
    int k;
    int npages;
    int xi;
    int xoffset;
    int xpageoffset;
    audio::internal::spectralDescriptors::e_stft(x, X);
    if (X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = X.size(1);
        e.set_size(1, X.size(1));
        for (xi = 0; xi < npages; xi++) {
            double d;
            xpageoffset = xi * 241;
            d = X[xpageoffset];
            for (k = 0; k < 240; k++) {
                d += X[(xpageoffset + k) + 1];
            }
            e[xi] = d;
        }
    }
    r.set_size(241, e.size(1));
    npages = e.size(1);
    for (xoffset = 0; xoffset < npages; xoffset++) {
        xpageoffset = xoffset * 241;
        for (xi = 0; xi < 241; xi++) {
            r[xpageoffset + xi] = e[xoffset];
        }
    }
    npages = 241 * X.size(1);
    X.set_size(241, X.size(1));
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        X[xpageoffset] = X[xpageoffset] / r[xpageoffset];
    }
    npages = 241 * X.size(1);
    r.set_size(241, X.size(1));
    for (k = 0; k < npages; k++) {
        r[k] = internal::scalar::b_log2(X[k]);
    }
    b_X.set_size(241, X.size(1));
    npages = 241 * X.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        b_X[xpageoffset] = X[xpageoffset] * r[xpageoffset];
    }
    if (b_X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = b_X.size(1);
        e.set_size(1, b_X.size(1));
        for (xi = 0; xi < npages; xi++) {
            xpageoffset = xi * 241;
            if (rtIsNaN(b_X[xpageoffset])) {
                e[xi] = 0.0;
            } else {
                e[xi] = b_X[xpageoffset];
            }
            for (k = 0; k < 240; k++) {
                xoffset = (xpageoffset + k) + 1;
                if (!rtIsNaN(b_X[xoffset])) {
                    e[xi] = e[xi] + b_X[xoffset];
                }
            }
        }
    }
    e.set_size(1, e.size(1));
    npages = e.size(1) - 1;
    for (xpageoffset = 0; xpageoffset <= npages; xpageoffset++) {
        e[xpageoffset] = -e[xpageoffset] / 7.9128893362299619;
    }
    entropy.set_size(e.size(1));
    npages = e.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        entropy[xpageoffset] = e[xpageoffset];
    }
}

void f_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy)
{
    array<double, 2U> X;
    array<double, 2U> b_X;
    array<double, 2U> e;
    array<double, 2U> r;
    int k;
    int npages;
    int xi;
    int xoffset;
    int xpageoffset;
    audio::internal::spectralDescriptors::f_stft(x, X);
    if (X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = X.size(1);
        e.set_size(1, X.size(1));
        for (xi = 0; xi < npages; xi++) {
            double d;
            xpageoffset = xi * 442;
            d = X[xpageoffset];
            for (k = 0; k < 441; k++) {
                d += X[(xpageoffset + k) + 1];
            }
            e[xi] = d;
        }
    }
    r.set_size(442, e.size(1));
    npages = e.size(1);
    for (xoffset = 0; xoffset < npages; xoffset++) {
        xpageoffset = xoffset * 442;
        for (xi = 0; xi < 442; xi++) {
            r[xpageoffset + xi] = e[xoffset];
        }
    }
    npages = 442 * X.size(1);
    X.set_size(442, X.size(1));
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        X[xpageoffset] = X[xpageoffset] / r[xpageoffset];
    }
    npages = 442 * X.size(1);
    r.set_size(442, X.size(1));
    for (k = 0; k < npages; k++) {
        r[k] = internal::scalar::b_log2(X[k]);
    }
    b_X.set_size(442, X.size(1));
    npages = 442 * X.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        b_X[xpageoffset] = X[xpageoffset] * r[xpageoffset];
    }
    if (b_X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = b_X.size(1);
        e.set_size(1, b_X.size(1));
        for (xi = 0; xi < npages; xi++) {
            xpageoffset = xi * 442;
            if (rtIsNaN(b_X[xpageoffset])) {
                e[xi] = 0.0;
            } else {
                e[xi] = b_X[xpageoffset];
            }
            for (k = 0; k < 441; k++) {
                xoffset = (xpageoffset + k) + 1;
                if (!rtIsNaN(b_X[xoffset])) {
                    e[xi] = e[xi] + b_X[xoffset];
                }
            }
        }
    }
    e.set_size(1, e.size(1));
    npages = e.size(1) - 1;
    for (xpageoffset = 0; xpageoffset <= npages; xpageoffset++) {
        e[xpageoffset] = -e[xpageoffset] / 8.7879025593914317;
    }
    entropy.set_size(e.size(1));
    npages = e.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        entropy[xpageoffset] = e[xpageoffset];
    }
}

void g_spectralEntropy(const ::coder::array<double, 1U> &x,
                       ::coder::array<double, 1U> &entropy)
{
    array<double, 2U> X;
    array<double, 2U> b_X;
    array<double, 2U> e;
    array<double, 2U> r;
    int k;
    int npages;
    int xi;
    int xoffset;
    int xpageoffset;
    audio::internal::spectralDescriptors::g_stft(x, X);
    if (X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = X.size(1);
        e.set_size(1, X.size(1));
        for (xi = 0; xi < npages; xi++) {
            double d;
            xpageoffset = xi * 481;
            d = X[xpageoffset];
            for (k = 0; k < 480; k++) {
                d += X[(xpageoffset + k) + 1];
            }
            e[xi] = d;
        }
    }
    r.set_size(481, e.size(1));
    npages = e.size(1);
    for (xoffset = 0; xoffset < npages; xoffset++) {
        xpageoffset = xoffset * 481;
        for (xi = 0; xi < 481; xi++) {
            r[xpageoffset + xi] = e[xoffset];
        }
    }
    npages = 481 * X.size(1);
    X.set_size(481, X.size(1));
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        X[xpageoffset] = X[xpageoffset] / r[xpageoffset];
    }
    npages = 481 * X.size(1);
    r.set_size(481, X.size(1));
    for (k = 0; k < npages; k++) {
        r[k] = internal::scalar::b_log2(X[k]);
    }
    b_X.set_size(481, X.size(1));
    npages = 481 * X.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        b_X[xpageoffset] = X[xpageoffset] * r[xpageoffset];
    }
    if (b_X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = b_X.size(1);
        e.set_size(1, b_X.size(1));
        for (xi = 0; xi < npages; xi++) {
            xpageoffset = xi * 481;
            if (rtIsNaN(b_X[xpageoffset])) {
                e[xi] = 0.0;
            } else {
                e[xi] = b_X[xpageoffset];
            }
            for (k = 0; k < 480; k++) {
                xoffset = (xpageoffset + k) + 1;
                if (!rtIsNaN(b_X[xoffset])) {
                    e[xi] = e[xi] + b_X[xoffset];
                }
            }
        }
    }
    e.set_size(1, e.size(1));
    npages = e.size(1) - 1;
    for (xpageoffset = 0; xpageoffset <= npages; xpageoffset++) {
        e[xpageoffset] = -e[xpageoffset] / 8.9098930837700419;
    }
    entropy.set_size(e.size(1));
    npages = e.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        entropy[xpageoffset] = e[xpageoffset];
    }
}

void spectralEntropy(const ::coder::array<double, 1U> &x,
                     ::coder::array<double, 1U> &entropy)
{
    array<double, 2U> X;
    array<double, 2U> b_X;
    array<double, 2U> e;
    array<double, 2U> r;
    int k;
    int npages;
    int xi;
    int xoffset;
    int xpageoffset;
    audio::internal::spectralDescriptors::stft(x, X);
    if (X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = X.size(1);
        e.set_size(1, X.size(1));
        for (xi = 0; xi < npages; xi++) {
            double d;
            xpageoffset = xi * 81;
            d = X[xpageoffset];
            for (k = 0; k < 80; k++) {
                d += X[(xpageoffset + k) + 1];
            }
            e[xi] = d;
        }
    }
    r.set_size(81, e.size(1));
    npages = e.size(1);
    for (xoffset = 0; xoffset < npages; xoffset++) {
        xpageoffset = xoffset * 81;
        for (xi = 0; xi < 81; xi++) {
            r[xpageoffset + xi] = e[xoffset];
        }
    }
    npages = 81 * X.size(1);
    X.set_size(81, X.size(1));
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        X[xpageoffset] = X[xpageoffset] / r[xpageoffset];
    }
    npages = 81 * X.size(1);
    r.set_size(81, X.size(1));
    for (k = 0; k < npages; k++) {
        r[k] = internal::scalar::b_log2(X[k]);
    }
    b_X.set_size(81, X.size(1));
    npages = 81 * X.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        b_X[xpageoffset] = X[xpageoffset] * r[xpageoffset];
    }
    if (b_X.size(1) == 0) {
        e.set_size(1, 0);
    } else {
        npages = b_X.size(1);
        e.set_size(1, b_X.size(1));
        for (xi = 0; xi < npages; xi++) {
            xpageoffset = xi * 81;
            if (rtIsNaN(b_X[xpageoffset])) {
                e[xi] = 0.0;
            } else {
                e[xi] = b_X[xpageoffset];
            }
            for (k = 0; k < 80; k++) {
                xoffset = (xpageoffset + k) + 1;
                if (!rtIsNaN(b_X[xoffset])) {
                    e[xi] = e[xi] + b_X[xoffset];
                }
            }
        }
    }
    e.set_size(1, e.size(1));
    npages = e.size(1) - 1;
    for (xpageoffset = 0; xpageoffset <= npages; xpageoffset++) {
        e[xpageoffset] = -e[xpageoffset] / 6.3398500028846243;
    }
    entropy.set_size(e.size(1));
    npages = e.size(1);
    for (xpageoffset = 0; xpageoffset < npages; xpageoffset++) {
        entropy[xpageoffset] = e[xpageoffset];
    }
}

} // namespace coder
