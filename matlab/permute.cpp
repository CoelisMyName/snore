#include "permute.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "mylock.h"

namespace coder {
void permute(const ::coder::array<double, 2U> &a, ::coder::array<double, 2U> &b)
{
    static const signed char b_iv[3] = {2, 1, 3};
    int i;
    int k;
    int plast;
    boolean_T b_b;
    b_b = true;
    if (a.size(1) != 0) {
        boolean_T exitg1;
        plast = 0;
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k < 3)) {
            if (b_iv[k] <= 2) {
                i = a.size(b_iv[k] - 1);
            } else {
                i = 1;
            }
            if (i != 1) {
                if (plast > b_iv[k]) {
                    b_b = false;
                    exitg1 = true;
                } else {
                    plast = b_iv[k];
                    k++;
                }
            } else {
                k++;
            }
        }
    }
    if (b_b) {
        b.set_size(a.size(1), 20);
        plast = a.size(1) * 20;
        for (i = 0; i < plast; i++) {
            b[i] = a[i];
        }
    } else {
        b.set_size(a.size(1), 20);
        i = a.size(1);
        for (k = 0; k < i; k++) {
            for (plast = 0; plast < 20; plast++) {
                b[k + b.size(0) * plast] = a[plast + 20 * k];
            }
        }
    }
}

void permute(const ::coder::array<double, 3U> &a, ::coder::array<double, 3U> &b)
{
    int k;
    int plast;
    boolean_T b_b;
    b_b = true;
    if (a.size(2) != 0) {
        boolean_T exitg1;
        plast = 0;
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k < 3)) {
            if (a.size(2 - k) != 1) {
                if (plast > 3 - k) {
                    b_b = false;
                    exitg1 = true;
                } else {
                    plast = 3 - k;
                    k++;
                }
            } else {
                k++;
            }
        }
    }
    if (b_b) {
        b.set_size(a.size(2), 32, 130);
        plast = (a.size(2) << 5) * 130;
        for (int i = 0; i < plast; i++) {
            b[i] = a[i];
        }
    } else {
        int i;
        b.set_size(a.size(2), 32, 130);
        i = a.size(2);
        for (k = 0; k < i; k++) {
            for (plast = 0; plast < 32; plast++) {
                for (int b_k = 0; b_k < 130; b_k++) {
                    b[(k + b.size(0) * plast) + b.size(0) * 32 * b_k] =
                        a[(b_k + 130 * plast) + 4160 * k];
                }
            }
        }
    }
}

} // namespace coder
